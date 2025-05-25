// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
#pragma once

#include "ryzenadj.h"

typedef struct {
    int opt;
    int opt_psmu;
    int pm_table_opt_offt;
    int pm_table_opt_value_offt;
} ryzen_adj_opt_t;

ryzen_adj_opt_t *adj_init_opt_list(RYZEN_FAMILY family);
void adj_init_pm_table_offsets(ryzen_adj_opt_t *optList, uint32_t table_ver);
