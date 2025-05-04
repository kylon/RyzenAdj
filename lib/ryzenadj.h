// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
#pragma once

#include <stdint.h>

#define RYZENADJ_REVISION_VER 0
#define RYZENADJ_MAJOR_VER 20
#define RYZENADJ_MINIOR_VER 0

#ifdef _WIN32
#define CALL __stdcall

#ifdef LIBRYZENADJ_EXPORT
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

#else
#define CALL

#ifdef LIBRYZENADJ_EXPORT
#define EXP __attribute__((visibility("default")))
#else
#define EXP
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FAM_UNKNOWN = -1,
    FAM_RAVEN = 0,
    FAM_PICASSO,
    FAM_RENOIR,
    FAM_CEZANNE,
    FAM_DALI,
    FAM_LUCIENNE,
    FAM_VANGOGH,
    FAM_REMBRANDT,
    FAM_MENDOCINO,
    FAM_PHOENIX,
    FAM_HAWKPOINT,
    FAM_STRIXPOINT,
    FAM_STRIXHALO
} RYZEN_FAMILY;

typedef enum {
    ADJ_OPT_STAPM_LIMIT = 0, // \_SB.ALIB (0x0c, [size, 0x05, val])
    ADJ_OPT_FAST_LIMIT, // \_SB.ALIB (0x0c, [size, 0x06, val])
    ADJ_OPT_SLOW_LIMIT, // \_SB.ALIB (0x0c, [size, 0x07, val])
    ADJ_OPT_SLOW_TIME, // \_SB.ALIB (0x0c, [size, 0x08, val])
    ADJ_OPT_STAPM_TIME, // \_SB.ALIB (0x0c, [size, 0x01, val])
    ADJ_OPT_TCTL_TEMP, // \_SB.ALIB (0x0c, [size, 0x03, val])
    ADJ_OPT_VRM_CURRENT, // \_SB.ALIB (0x0c, [size, 0x0b, val])
    ADJ_OPT_VRMSOC_CURRENT, // \_SB.ALIB (0x0c, [size, 0x0e, val])
    ADJ_OPT_VRMGFX_CURRENT,
    ADJ_OPT_VRMCVIP_CURRENT,
    ADJ_OPT_VRMMAX_CURRENT, // \_SB.ALIB (0x0c, [size, 0x0c, val])
    ADJ_OPT_VRMGFXMAX_CURRENT,
    ADJ_OPT_VRMSOCMAX_CURRENT, // \_SB.ALIB (0x0c, [size, 0x11, val])
    ADJ_OPT_PSI0_CURRENT,
    ADJ_OPT_PSI3_CPU_CURRENT,
    ADJ_OPT_PSI0_SOC_CURRENT,
    ADJ_OPT_PSI3_GFX_CURRENT,
    ADJ_OPT_MAX_GFXCLK_FREQ,
    ADJ_OPT_MIN_GFXCLK_FREQ,
    ADJ_OPT_MAX_SOCCLK_FREQ,
    ADJ_OPT_MIN_SOCCLK_FREQ,
    ADJ_OPT_MAX_FCLK_FREQ,
    ADJ_OPT_MIN_FCLK_FREQ,
    ADJ_OPT_MAX_VCN,
    ADJ_OPT_MIN_VCN,
    ADJ_OPT_MAX_LCLK,
    ADJ_OPT_MIN_LCLK,
    ADJ_OPT_PROCHOT_DEASSERTION_RAMP, // \_SB.ALIB (0x0c, [size, 0x09, val])
    ADJ_OPT_APU_SKIN_TEMP_LIMIT, // \_SB.ALIB (0x0c, [size, 0x22, val])
    ADJ_OPT_DGPU_SKIN_TEMP_LIMIT, // \_SB.ALIB (0x0c, [size, 0x23, val])
    ADJ_OPT_APU_SLOW_LIMIT, // \_SB.ALIB (0x0c, [size, 0x13, val])
    ADJ_OPT_SKIN_TEMP_POWER_LIMIT, // \_SB.ALIB (0x0c, [size, 0x2e, val])
    ADJ_OPT_GFX_CLK,
    ADJ_OPT_OC_CLK,
    ADJ_OPT_PER_CORE_OC_CLK,
    ADJ_OPT_OC_VOLT,
    ADJ_OPT_DISABLE_OC,
    ADJ_OPT_ENABLE_OC,
    ADJ_OPT_CCLK_SETPOINT, // \_SB.ALIB (0x01, [size, 0x1]) power-saving
    ADJ_OPT_CCLK_BUSY, // \_SB.ALIB (0x01, [size, 0x0]) max-performance
    ADJ_OPT_COALL,
    ADJ_OPT_COPER,
    ADJ_OPT_COGFX,
    ADJ_OPT_CORE_0_POWER,
    ADJ_OPT_CORE_1_POWER,
    ADJ_OPT_CORE_2_POWER,
    ADJ_OPT_CORE_3_POWER,
    ADJ_OPT_CORE_4_POWER,
    ADJ_OPT_CORE_5_POWER,
    ADJ_OPT_CORE_6_POWER,
    ADJ_OPT_CORE_7_POWER,
    ADJ_OPT_CORE_8_POWER,
    ADJ_OPT_CORE_9_POWER,
    ADJ_OPT_CORE_10_POWER,
    ADJ_OPT_CORE_11_POWER,
    ADJ_OPT_CORE_12_POWER,
    ADJ_OPT_CORE_13_POWER,
    ADJ_OPT_CORE_14_POWER,
    ADJ_OPT_CORE_15_POWER,
    ADJ_OPT_CORE_0_VOLT,
    ADJ_OPT_CORE_1_VOLT,
    ADJ_OPT_CORE_2_VOLT,
    ADJ_OPT_CORE_3_VOLT,
    ADJ_OPT_CORE_4_VOLT,
    ADJ_OPT_CORE_5_VOLT,
    ADJ_OPT_CORE_6_VOLT,
    ADJ_OPT_CORE_7_VOLT,
    ADJ_OPT_CORE_8_VOLT,
    ADJ_OPT_CORE_9_VOLT,
    ADJ_OPT_CORE_10_VOLT,
    ADJ_OPT_CORE_11_VOLT,
    ADJ_OPT_CORE_12_VOLT,
    ADJ_OPT_CORE_13_VOLT,
    ADJ_OPT_CORE_14_VOLT,
    ADJ_OPT_CORE_15_VOLT,
    ADJ_OPT_CORE_0_TEMP,
    ADJ_OPT_CORE_1_TEMP,
    ADJ_OPT_CORE_2_TEMP,
    ADJ_OPT_CORE_3_TEMP,
    ADJ_OPT_CORE_4_TEMP,
    ADJ_OPT_CORE_5_TEMP,
    ADJ_OPT_CORE_6_TEMP,
    ADJ_OPT_CORE_7_TEMP,
    ADJ_OPT_CORE_8_TEMP,
    ADJ_OPT_CORE_9_TEMP,
    ADJ_OPT_CORE_10_TEMP,
    ADJ_OPT_CORE_11_TEMP,
    ADJ_OPT_CORE_12_TEMP,
    ADJ_OPT_CORE_13_TEMP,
    ADJ_OPT_CORE_14_TEMP,
    ADJ_OPT_CORE_15_TEMP,
    ADJ_OPT_CORE_0_CLK,
    ADJ_OPT_CORE_1_CLK,
    ADJ_OPT_CORE_2_CLK,
    ADJ_OPT_CORE_3_CLK,
    ADJ_OPT_CORE_4_CLK,
    ADJ_OPT_CORE_5_CLK,
    ADJ_OPT_CORE_6_CLK,
    ADJ_OPT_CORE_7_CLK,
    ADJ_OPT_CORE_8_CLK,
    ADJ_OPT_CORE_9_CLK,
    ADJ_OPT_CORE_10_CLK,
    ADJ_OPT_CORE_11_CLK,
    ADJ_OPT_CORE_12_CLK,
    ADJ_OPT_CORE_13_CLK,
    ADJ_OPT_CORE_14_CLK,
    ADJ_OPT_CORE_15_CLK,
    ADJ_OPT_L3_CLK,
    ADJ_OPT_L3_LOGIC,
    ADJ_OPT_L3_VDDM,
    ADJ_OPT_L3_TEMP,
    ADJ_OPT_GFX_VOLT,
    ADJ_OPT_GFX_TEMP,
    ADJ_OPT_FCLK,
    ADJ_OPT_MEM_CLK,
    ADJ_OPT_SOC_VOLT,
    ADJ_OPT_SOC_POWER,
    ADJ_OPT_SOCKET_POWER,

    ADJ_OPT_COUNT
} ADJ_OPT;

typedef enum {
    ADJ_OK = 0,
    ADJ_NOT_INITIALIZED,
    ADJ_OUT_OF_MEMORY,
    ADJ_INVALID_OPT,
    ADJ_OPT_NOT_SUPPORTED,
    ADJ_FAM_UNSUPPORTED,
    ADJ_ERR_MEMORY_ACCESS,
    ADJ_OPTLIST_FAIL,
    ADJ_PCI_OBJ_FAIL,
    ADJ_NB_FAIL,
    ADJ_MP1_SMU_FAIL,
    ADJ_PSMU_FAIL,
    ADJ_SMU_UNSUPPORTED,
    ADJ_SMU_REQ_FAILED
} ADJ_ERROR;

EXP ADJ_ERROR CALL ryzenadj_init();
EXP void CALL ryzenadj_cleanup();
EXP ADJ_ERROR CALL ryzenadj_refresh_table();
EXP ADJ_ERROR CALL ryzenadj_can_write(ADJ_OPT opt);
EXP ADJ_ERROR CALL ryzenadj_can_read(ADJ_OPT opt);
EXP ADJ_ERROR CALL ryzenadj_can_read_value(ADJ_OPT opt);
EXP ADJ_ERROR CALL ryzenadj_set(ADJ_OPT opt, uint32_t value);
EXP float CALL ryzenadj_get(ADJ_OPT opt, ADJ_ERROR *error);
EXP float CALL ryzenadj_get_value(ADJ_OPT opt, ADJ_ERROR *error);
EXP RYZEN_FAMILY CALL ryzenadj_get_cpu_family();
EXP uint32_t CALL ryzenadj_get_bios_if_ver();
EXP uintptr_t CALL ryzenadj_get_table_addr();
EXP uint32_t CALL ryzenadj_get_table_ver();
EXP size_t CALL ryzenadj_get_table_size();
EXP float * CALL ryzenadj_get_table_values();
EXP uint32_t CALL ryzenadj_get_mp1_smu_last_error();
EXP uint32_t CALL ryzenadj_get_psmu_last_error();
EXP char * CALL ryzenadj_error_str(ADJ_ERROR error);

#ifdef __cplusplus
}
#endif
