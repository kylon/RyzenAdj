// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
/* Access PCI Config Space - libpci */

#include <sys/mman.h>
#include <pci/pci.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "osdep.h"

bool mem_obj_obj = false;
int pm_table_fd = 0;
void *phy_map = MAP_FAILED;

pci_obj_t init_pci_obj() {
	pci_obj_t obj = pci_alloc();

	pci_init(obj);
	return obj;
}

nb_t get_nb(pci_obj_t obj) {
	nb_t nb = pci_get_dev(obj, 0, 0, 0, 0);

	pci_fill_info(nb, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
	return nb;
}

void free_nb(nb_t nb) {
	if (!nb)
		return;

	pci_free_dev(nb);
}

void free_pci_obj(pci_obj_t obj) {
	if (!obj)
		return;

	pci_cleanup(obj);
}

uint32_t smn_reg_read(nb_t nb, const uint32_t addr) {
	pci_write_long(nb, NB_PCI_REG_ADDR_ADDR, addr & (~0x3));
	return pci_read_long(nb, NB_PCI_REG_DATA_ADDR);
}

void smn_reg_write(nb_t nb, const uint32_t addr, const uint32_t data) {
	pci_write_long(nb, NB_PCI_REG_ADDR_ADDR, addr);
	pci_write_long(nb, NB_PCI_REG_DATA_ADDR, data);
}

mem_obj_t init_mem_obj(const uintptr_t physAddr) {
	const int dev_mem_fd = open("/dev/mem", O_RDONLY);
	const int dev_mem_errno = errno;
	int mmap_errno;

	// It is too complicated to check PAT, CONFIG_NONPROMISC_DEVMEM, CONFIG_STRICT_DEVMEM or other dependencies, just try to open /dev/mem
	if (dev_mem_fd > 0) {
		phy_map = mmap(NULL, 0x1000, PROT_READ, MAP_SHARED, dev_mem_fd, (long)physAddr);
		mmap_errno = errno;
		close(dev_mem_fd);
	}

	if (phy_map == MAP_FAILED) { //only complain about mmap errors if we don't have access to alternative smu driver
		pm_table_fd = open("/sys/kernel/ryzen_smu_drv/pm_table", O_RDONLY);

		if (pm_table_fd < 0) {
			DBG("failed to get /sys/kernel/ryzen_smu_drv/pm_table: %s\n", strerror(errno));

			// show either fd error or mmap error, depending on which was the problem
			if (dev_mem_errno)
				DBG("failed to get /dev/mem: %s\n", strerror(dev_mem_errno));
			else
				DBG("failed to map /dev/mem: %s\n", strerror(mmap_errno));

			// we are already superuser if memory access is requested because we did successfully do the other smu calls.
			// missing /dev/mem or missing permissions can only mean memory access policy
			if (mmap_errno == EPERM || dev_mem_fd < 0)
				DBG("If you don't want to change your memory access policy, you need a kernel module for this task.\n"
						"We do support usage of this kernel module https://gitlab.com/leogx9r/ryzen_smu\n");

			return NULL;
		}
	}

	mem_obj_obj = true;

	return &mem_obj_obj;
}

void free_mem_obj(mem_obj_t obj) {
	if (!mem_obj_obj)
		return;

	if (phy_map != MAP_FAILED)
		munmap(phy_map, 0x1000);

	if (pm_table_fd > 0)
		close(pm_table_fd);

	mem_obj_obj = false;
	pm_table_fd = 0;
	phy_map = MAP_FAILED;
}

int copy_pm_table(void *buffer, const size_t size) {
	if (pm_table_fd > 0) {
		lseek(pm_table_fd, 0, SEEK_SET);

		const ssize_t read_size = read(pm_table_fd, buffer, size);

		if (read_size == -1) {
			DBG("failed to get pm_table from ryzen_smu kernel module: %s\n", strerror(errno));
			return -1;
		}

		return 0;
	}

	if (phy_map != MAP_FAILED) {
		memcpy(buffer, phy_map, size);
		return 0;
	}

	DBG("failed to get pm_table from /dev/mem\n");
	return -1;
}

int compare_pm_table(const void *buffer, const size_t size) {
	if (pm_table_fd > 0) // we can't compare to physial pm table location because we don't have direct memory access via SMU driver
		return 0;

	return memcmp(buffer, phy_map, size);
}

bool is_using_smu_driver() {
	return pm_table_fd > 0;
}
