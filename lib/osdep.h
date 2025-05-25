// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef RYZENADJ_DEBUG
#define DBG(...) fprintf(stderr, __VA_ARGS__)
#else
#define DBG(...)
#endif

#define NB_PCI_REG_ADDR_ADDR			0xB8
#define NB_PCI_REG_DATA_ADDR			0xBC

typedef struct {
#ifdef _WIN32
    uint32_t pci_address;
    HINSTANCE inpoutDll;
#else
    union {
        struct {
            struct pci_access *pci_acc;
            struct pci_dev *pci_dev;
        } mem;
        struct {
            int smn_fd;
            int pm_table_fd;
            size_t pm_table_size;
        } kmod;
    } access;
#endif
} os_access_obj_t;

os_access_obj_t *init_os_access_obj();
int init_mem_obj(os_access_obj_t *os_access, uintptr_t physAddr);
int copy_pm_table(const os_access_obj_t *obj, void *buffer, size_t size);
int compare_pm_table(const void *buffer, size_t size);
void free_os_access_obj(os_access_obj_t *obj);

uint32_t smn_reg_read(const os_access_obj_t *obj, uint32_t addr);
void smn_reg_write(const os_access_obj_t *obj, uint32_t addr, uint32_t data);
bool is_using_smu_driver();
