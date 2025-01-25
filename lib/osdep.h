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

#define NB_PCI_REG_ADDR_ADDR			0xB8
#define NB_PCI_REG_DATA_ADDR			0xBC

#ifdef RYZENADJ_DEBUG
#define DBG(...) fprintf(stderr, __VA_ARGS__)
#else
#define DBG(...)
#endif

#ifdef _WIN32
typedef uint32_t *nb_t;
typedef bool *pci_obj_t;
typedef HINSTANCE *mem_obj_t;
#else
typedef struct pci_dev *nb_t;
typedef struct pci_access *pci_obj_t;
typedef bool *mem_obj_t;
#endif

pci_obj_t init_pci_obj();
mem_obj_t init_mem_obj(uintptr_t physAddr);
nb_t get_nb(pci_obj_t obj);
int copy_pm_table(void *buffer, size_t size);
int compare_pm_table(const void *buffer, size_t size);

void free_pci_obj(pci_obj_t obj);
void free_nb(nb_t nb);
void free_mem_obj(mem_obj_t obj);

uint32_t smn_reg_read(nb_t nb, uint32_t addr);
void smn_reg_write(nb_t nb, uint32_t addr, uint32_t data);
bool is_using_smu_driver();
