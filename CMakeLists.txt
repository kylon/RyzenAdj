CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

project(ryzenadj)

string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(CheckIPOSupported)
check_ipo_supported(RESULT has_ipo OUTPUT error)

set(PROJECT_SOURCES
    lib/osdep.h
    lib/smu_access.h
    lib/smu_access.c
    lib/ryzen_opts.h
    lib/ryzen_opts.c
    lib/ryzenadj.c
)

set(PUB_HEADERS
    lib/ryzenadj.h
)

if (WIN32)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(LINK_LIBS WinRing0x64)

    list(APPEND PROJECT_SOURCES
        lib/osdep_win32.cpp
    )

elseif (LINUX)
    set(LINK_LIBS pci)

    list(APPEND PROJECT_SOURCES
        lib/osdep_linux.c
    )

else ()
    message(FATAL_ERROR "!Unsupported OS!")
endif ()

add_library(${PROJECT_NAME} ${PUB_HEADERS} ${PROJECT_SOURCES})
add_library("RYADJ::RyzenAdjLib" ALIAS ${PROJECT_NAME})

if (build_type MATCHES debug)
    message(STATUS "${PROJECT_NAME}: debug prints are enabled")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RYZENADJ_DEBUG)
endif ()

if (has_ipo)
    message(STATUS "${PROJECT_NAME}: IPO / LTO enabled")
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "libryzenadj")
    target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/win32")
endif ()

target_compile_definitions(${PROJECT_NAME} PUBLIC LIBRYZENADJ_EXPORT)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET rylib_headers
    TYPE HEADERS
    FILES ${PUB_HEADERS}
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    FILE_SET rylib_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
