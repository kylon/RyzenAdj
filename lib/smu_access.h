// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
#pragma once

#include "osdep.h"
#include "ryzenadj.h"

#define REP_MSG_OK                    0x1
#define REP_MSG_Failed                0xFF
#define REP_MSG_UnknownCmd            0xFE
#define REP_MSG_CmdRejectedPrereq     0xFD
#define REP_MSG_CmdRejectedBusy       0xFC

typedef enum {
    TYPE_MP1,
    TYPE_PSMU,
    TYPE_COUNT,
} SMU_TYPE;

typedef struct {
    os_access_obj_t *os_access;
    uint32_t msg;
    uint32_t rep;
    uint32_t arg_base;
    uint32_t last_error;
} smu_access_t;

typedef struct {
    uint32_t arg0;
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
    uint32_t arg4;
    uint32_t arg5;
} smu_service_args_t;

smu_access_t *get_smu(os_access_obj_t *obj, SMU_TYPE type, RYZEN_FAMILY family);
ADJ_ERROR smu_service_req(smu_access_t *smu, uint32_t id , smu_service_args_t *args);
