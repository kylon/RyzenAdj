# libRyzenAdj
reworked libRyzenAdj for easier integration in apps (cli and gui) and better performance.

### Changes
- checks everywhere, for ex. you can no longer call init multiple times, leaking memory, by accident or crash for null deref
- query options availability and capabilities (read/write), no need to duplicate code in apps to check family etc..
- 1 set function
- 1 get/get_value function
- RYZENADJ_DEBUG def to enable debug prints to stderr, enabled by default in cmake debug builds
- ADJ_ERROR type for error checks in apps and error_str function (you must free() error string to avoid mem leaks after) (see sources)
- faster build
- more, see sources

Adjust power management settings for Ryzen Mobile Processors.

Based on: [FlyGoat/ryzen_nb_smu](https://github.com/flygoat/ryzen_nb_smu)

### Documentation
- [Supported Models](https://github.com/FlyGoat/RyzenAdj/wiki/Supported-Models)
- [Renoir Tuning Guide](https://github.com/FlyGoat/RyzenAdj/wiki/Renoir-Tuning-Guide)
- [Options](https://github.com/FlyGoat/RyzenAdj/wiki/Options)
- [FAQ](https://github.com/FlyGoat/RyzenAdj/wiki/FAQ)

## Build

### Build Requirements

Building this tool requires C & C++ compilers as well as **cmake**. It
requires privileged access to NB PCI config space, in order to compile it
one must have pcilib library & headers available.

### Linux

Please make sure that you have libpci dependency before compiling. On
Debian-based distros this is covered by installing **pcilib-dev** package:

    sudo apt install build-essential cmake libpci-dev

On Fedora:

    sudo dnf install cmake gcc-c++ pciutils-devel

On Arch:

    sudo pacman -S base-devel pciutils cmake

If your Distribution is not supported, try finding the packages or use [Distrobox](https://github.com/89luca89/distrobox) or [Toolbox](https://docs.fedoraproject.org/en-US/fedora-silverblue/toolbox/) instead.

The simplest way to build it:

    git clone https://github.com/FlyGoat/RyzenAdj.git
    cd RyzenAdj
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cd build
    make

To install to your system

    make install

### Windows

It can be built by Visual Studio + MSVC automaticaly, or Clang + Nmake in command line.
However, as for now, MingW-gcc can't be used to compile for some reason.

Required dll is included in ./win32 of source tree. Please put the dll
library and sys driver in the same folder with ryzenadj.exe.

We don't recommend you to build by yourself on Windows since the environment configuarion
may be convoluted.
The easier way is to use an IDE like QT Creator, CLion or Visual Studio.

A new option is [Windows Terminal](https://github.com/microsoft/terminal) (pre-installed in Windows 11 and above) and VS 2022.

- Run terminal and open a new `Developer Command Prompt for VS 2022` or `Developer PowerSchell for VS 2022`
- cd to ryzenadj folder
- run `cmake -B build -G Ninja`
- run `ninja -C build`

### Library

If you would like to use ryzenadj functions in your program, see libryzenadj.

If you would like to use ryzenadj in your project, you can add it as submodule or import the folder.

Add ryzenadj library to your CMakeLists.txt

    add_subdirectory(PathTo/RyzenAdj/lib EXCLUDE_FROM_ALL)

If building for Windows, add

    target_link_directories(${PROJECT_NAME} PRIVATE PathTo/RyzenAdj/win32)

Finally, link libryzenadj

    target_link_libraries(${PROJECT_NAME} PRIVATE RYADJ::RyzenAdjLib)
