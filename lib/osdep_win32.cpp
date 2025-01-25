// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
/* Access PCI Config Space - winring0 */
extern "C" {
#include "osdep.h"
}
#include "OlsApi.h"
#include "OlsDef.h"

bool nb_pci_obj = true;
uint32_t nb_pci_address = 0x0;
HINSTANCE hInpOutDll;

typedef BOOL (__stdcall *lpIsInpOutDriverOpen)(void);
typedef PBYTE (__stdcall *lpMapPhysToLin)(uintptr_t pbPhysAddr, size_t dwPhysSize, HANDLE *pPhysicalMemoryHandle);
typedef BOOL (__stdcall *lpUnmapPhysicalMemory)(HANDLE PhysicalMemoryHandle, uintptr_t pbLinAddr);
typedef BOOL (__stdcall *lpGetPhysLong)(uintptr_t pbPhysAddr, uint32_t *pdwPhysVal);
lpIsInpOutDriverOpen gfpIsInpOutDriverOpen;
lpGetPhysLong gfpGetPhysLong;
lpMapPhysToLin gfpMapPhysToLin;
lpUnmapPhysicalMemory gfpUnmapPhysicalMemory;
uint32_t *pdwLinAddr;
HANDLE physicalMemoryHandle;

#ifdef __cplusplus
extern "C" {
#endif

pci_obj_t init_pci_obj() {
    InitializeOls();

    const DWORD dllStatus = GetDllStatus();

    switch (dllStatus) {
        case OLS_DLL_NO_ERROR:
            return &nb_pci_obj;
        case OLS_DLL_UNSUPPORTED_PLATFORM:
            DBG("WinRing0 Err: Unsupported Plattform\n");
            break;
        case OLS_DLL_DRIVER_NOT_LOADED:
            DBG("WinRing0 Err: Driver not loaded\n");
            break;
        case OLS_DLL_DRIVER_NOT_FOUND:
            DBG("WinRing0 Err: Driver not found\n");
            break;
        case OLS_DLL_DRIVER_UNLOADED:
            DBG("WinRing0 Err: Driver unloaded\n");
            break;
        case OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK:
            DBG("WinRing0 Err: Driver not loaded on network\n");
            break;
        case OLS_DLL_UNKNOWN_ERROR:
            DBG("WinRing0 Err: unknown error\n");
            break;
        default:
            DBG("WinRing0 Err: unknown status code %lu\n", dllStatus);
            break;
    }

    return NULL;
}

nb_t get_nb(pci_obj_t obj) {
    return &nb_pci_address;
}

void free_nb(nb_t) {}

void free_pci_obj(pci_obj_t obj) {
  	if (!obj)
    	return;

    DeinitializeOls();
}

uint32_t smn_reg_read(nb_t nb, uint32_t addr) {
    WritePciConfigDword(*nb, NB_PCI_REG_ADDR_ADDR, addr & (~0x3));
    return ReadPciConfigDword(*nb, NB_PCI_REG_DATA_ADDR);
}

void smn_reg_write(nb_t nb, uint32_t addr, uint32_t data) {
    WritePciConfigDword(*nb, NB_PCI_REG_ADDR_ADDR, addr);
    WritePciConfigDword(*nb, NB_PCI_REG_DATA_ADDR, data);
}

mem_obj_t init_mem_obj(uintptr_t physAddr) {
    hInpOutDll = LoadLibrary ("inpoutx64.DLL");

    if (hInpOutDll == NULL) {
        DBG("Could not load inpoutx64.DLL\n");
        return NULL;
    }

    gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
    gfpGetPhysLong = (lpGetPhysLong)GetProcAddress(hInpOutDll, "GetPhysLong");
    gfpMapPhysToLin = (lpMapPhysToLin)GetProcAddress(hInpOutDll, "MapPhysToLin");
    gfpUnmapPhysicalMemory = (lpUnmapPhysicalMemory)GetProcAddress(hInpOutDll, "UnmapPhysicalMemory");

    if (!gfpIsInpOutDriverOpen()) {
        DBG("Could not open inpoutx64 driver\n");
        return NULL;
    }

    pdwLinAddr = (uint32_t*)gfpMapPhysToLin(physAddr, 0x1000, &physicalMemoryHandle);
    if (pdwLinAddr == NULL) {
        DBG("failed to map memory\n");
        return NULL;
    }

    return &hInpOutDll;
}

void free_mem_obj(mem_obj_t obj) {
	if (!obj)
		return;

    gfpUnmapPhysicalMemory(physicalMemoryHandle, *pdwLinAddr);
    FreeLibrary((HINSTANCE)obj);
}

int copy_pm_table(void *buffer, const size_t size) {
    memcpy(buffer, pdwLinAddr, size);
    return 0;
}

int compare_pm_table(const void *buffer, const size_t size) {
    return memcmp(buffer, pdwLinAddr, size);
}

bool is_using_smu_driver() {
    return false;
}

#ifdef __cplusplus
}
#endif
