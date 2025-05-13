// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
#include <stdlib.h>

#include "ryzen_opts.h"

static void setRavenOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x18;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x19;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x1a;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x1b;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x1c;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x1d;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x1e;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x1f;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x20;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x21;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x22;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x23;
    optList[ADJ_OPT_PSI0_CURRENT].opt = 0x24;
    optList[ADJ_OPT_PSI0_SOC_CURRENT].opt = 0x25;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x26;
    optList[ADJ_OPT_MAX_GFXCLK_FREQ].opt = 0x46;
    optList[ADJ_OPT_MIN_GFXCLK_FREQ].opt = 0x47;
    optList[ADJ_OPT_MAX_SOCCLK_FREQ].opt = 0x48;
    optList[ADJ_OPT_MIN_SOCCLK_FREQ].opt = 0x49;
    optList[ADJ_OPT_MAX_FCLK_FREQ].opt = 0x4A;
    optList[ADJ_OPT_MIN_FCLK_FREQ].opt = 0x4B;
    optList[ADJ_OPT_MAX_VCN].opt = 0x4C;
    optList[ADJ_OPT_MIN_VCN].opt = 0x4D;
    optList[ADJ_OPT_MAX_LCLK].opt = 0x4E;
    optList[ADJ_OPT_MIN_LCLK].opt = 0x4F;
}

static void setPicassoOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x18;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x19;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x1a;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x1b;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x1c;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x1d;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x1e;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x1f;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x20;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x21;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x22;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x23;
    optList[ADJ_OPT_PSI0_CURRENT].opt = 0x24;
    optList[ADJ_OPT_PSI0_SOC_CURRENT].opt = 0x25;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x26;
    optList[ADJ_OPT_MAX_GFXCLK_FREQ].opt = 0x46;
    optList[ADJ_OPT_MIN_GFXCLK_FREQ].opt = 0x47;
    optList[ADJ_OPT_MAX_SOCCLK_FREQ].opt = 0x48;
    optList[ADJ_OPT_MIN_SOCCLK_FREQ].opt = 0x49;
    optList[ADJ_OPT_MAX_FCLK_FREQ].opt = 0x4A;
    optList[ADJ_OPT_MIN_FCLK_FREQ].opt = 0x4B;
    optList[ADJ_OPT_MAX_VCN].opt = 0x4C;
    optList[ADJ_OPT_MIN_VCN].opt = 0x4D;
    optList[ADJ_OPT_MAX_LCLK].opt = 0x4E;
    optList[ADJ_OPT_MIN_LCLK].opt = 0x4F;
}

static void setDaliOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x18;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x19;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x1a;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x1b;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x1c;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x1d;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x1e;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x1f;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x20;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x21;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x22;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x23;
    optList[ADJ_OPT_PSI0_CURRENT].opt = 0x24;
    optList[ADJ_OPT_PSI0_SOC_CURRENT].opt = 0x25;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x26;
    optList[ADJ_OPT_MAX_GFXCLK_FREQ].opt = 0x46;
    optList[ADJ_OPT_MIN_GFXCLK_FREQ].opt = 0x47;
    optList[ADJ_OPT_MAX_SOCCLK_FREQ].opt = 0x48;
    optList[ADJ_OPT_MIN_SOCCLK_FREQ].opt = 0x49;
    optList[ADJ_OPT_MAX_FCLK_FREQ].opt = 0x4A;
    optList[ADJ_OPT_MIN_FCLK_FREQ].opt = 0x4B;
    optList[ADJ_OPT_MAX_VCN].opt = 0x4C;
    optList[ADJ_OPT_MIN_VCN].opt = 0x4D;
    optList[ADJ_OPT_MAX_LCLK].opt = 0x4E;
    optList[ADJ_OPT_MIN_LCLK].opt = 0x4F;
}

static void setRenoirOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PSI0_CURRENT].opt = 0x1e;
    optList[ADJ_OPT_PSI0_SOC_CURRENT].opt = 0x1f;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x20;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x21;
    optList[ADJ_OPT_ENABLE_OC].opt = 0x2F;
    optList[ADJ_OPT_DISABLE_OC].opt = 0x30;
    optList[ADJ_OPT_OC_CLK].opt = 0x31;
    optList[ADJ_OPT_PER_CORE_OC_CLK].opt = 0x32;
    optList[ADJ_OPT_OC_VOLT].opt = 0x33;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x38;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x39;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x53;
    optList[ADJ_OPT_COPER].opt = 0x54;
    optList[ADJ_OPT_COALL].opt = 0x55;
    optList[ADJ_OPT_COGFX].opt = 0x64;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;

}

static void setLucienneOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PSI0_CURRENT].opt = 0x1e;
    optList[ADJ_OPT_PSI0_SOC_CURRENT].opt = 0x1f;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x20;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x21;
    optList[ADJ_OPT_ENABLE_OC].opt = 0x2F;
    optList[ADJ_OPT_DISABLE_OC].opt = 0x30;
    optList[ADJ_OPT_OC_CLK].opt = 0x31;
    optList[ADJ_OPT_PER_CORE_OC_CLK].opt = 0x32;
    optList[ADJ_OPT_OC_VOLT].opt = 0x33;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x38;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x39;
    optList[ADJ_OPT_MAX_GFXCLK_FREQ].opt = 0x46;
    optList[ADJ_OPT_MIN_GFXCLK_FREQ].opt = 0x47;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x53;
    optList[ADJ_OPT_COPER].opt = 0x54;
    optList[ADJ_OPT_COALL].opt = 0x55;
    optList[ADJ_OPT_COGFX].opt = 0x64;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
}

static void setCezanneOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PSI0_CURRENT].opt = 0x1e;
    optList[ADJ_OPT_PSI0_SOC_CURRENT].opt = 0x1f;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x20;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x21;
    optList[ADJ_OPT_ENABLE_OC].opt = 0x2F;
    optList[ADJ_OPT_DISABLE_OC].opt = 0x30;
    optList[ADJ_OPT_OC_CLK].opt = 0x31;
    optList[ADJ_OPT_PER_CORE_OC_CLK].opt = 0x32;
    optList[ADJ_OPT_OC_VOLT].opt = 0x33;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x38;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x39;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x53;
    optList[ADJ_OPT_COPER].opt = 0x54;
    optList[ADJ_OPT_COALL].opt = 0x55;
    optList[ADJ_OPT_COGFX].opt = 0x64;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
}

static void setVangoghOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMGFX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMCVIP_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1e;
    optList[ADJ_OPT_VRMGFXMAX_CURRENT].opt = 0x1f;
    optList[ADJ_OPT_PSI3_CPU_CURRENT].opt = 0x20;
    optList[ADJ_OPT_PSI3_GFX_CURRENT].opt = 0x21;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x22;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x33;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x34;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;
    optList[ADJ_OPT_COPER].opt = 0x4b;
    optList[ADJ_OPT_COALL].opt = 0x4C;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
    optList[ADJ_OPT_COGFX].opt_psmu = 0xB7;
}

static void setRembrandtOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x1f;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x23;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x33;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x34;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;
    optList[ADJ_OPT_COPER].opt = 0x4b;
    optList[ADJ_OPT_COALL].opt = 0x4C;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_ENABLE_OC].opt_psmu = 0x17;
    optList[ADJ_OPT_DISABLE_OC].opt_psmu = 0x18;
    optList[ADJ_OPT_OC_CLK].opt_psmu = 0x19;
    optList[ADJ_OPT_PER_CORE_OC_CLK].opt_psmu = 0x1a;
    optList[ADJ_OPT_OC_VOLT].opt_psmu = 0x1b;
    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
    optList[ADJ_OPT_COGFX].opt_psmu = 0xB7;
}

static void setMendocinoOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x1f;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x33;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x34;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
}

static void setPhoenixOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x1f;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x23;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x33;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x34;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;
    optList[ADJ_OPT_COPER].opt = 0x4b;
    optList[ADJ_OPT_COALL].opt = 0x4C;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
    optList[ADJ_OPT_COGFX].opt_psmu = 0xB7;
}

static void setHawkpointOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x1f;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x23;
    optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].opt = 0x33;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x34;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;
    optList[ADJ_OPT_COPER].opt = 0x4b;
    optList[ADJ_OPT_COALL].opt = 0x4C;
    optList[ADJ_OPT_GFX_CLK].opt = 0x89;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
    optList[ADJ_OPT_COGFX].opt_psmu = 0xB7;
}

static void setStrixpointOpts(ryzen_adj_opt_t *optList) {
    optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
    optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
    optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
    optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
    optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
    optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
    optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
    optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
    optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
    optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
    optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
    optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
    optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x1f;
    optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x23;
    optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].opt = 0x34;
    optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;

    optList[ADJ_OPT_STAPM_LIMIT].opt_psmu = 0x31;
}

static void setStrixhaloOpts(ryzen_adj_opt_t *optList) {
	optList[ADJ_OPT_CCLK_BUSY].opt = 0x11;
	optList[ADJ_OPT_CCLK_SETPOINT].opt = 0x12;
	optList[ADJ_OPT_STAPM_LIMIT].opt = 0x14;
	optList[ADJ_OPT_FAST_LIMIT].opt = 0x15;
	optList[ADJ_OPT_SLOW_LIMIT].opt = 0x16;
	optList[ADJ_OPT_SLOW_TIME].opt = 0x17;
	optList[ADJ_OPT_STAPM_TIME].opt = 0x18;
	optList[ADJ_OPT_TCTL_TEMP].opt = 0x19;
	optList[ADJ_OPT_VRM_CURRENT].opt = 0x1a;
	optList[ADJ_OPT_VRMSOC_CURRENT].opt = 0x1b;
	optList[ADJ_OPT_VRMMAX_CURRENT].opt = 0x1c;
	optList[ADJ_OPT_VRMSOCMAX_CURRENT].opt = 0x1d;
	optList[ADJ_OPT_PROCHOT_DEASSERTION_RAMP].opt = 0x1f;
	optList[ADJ_OPT_APU_SLOW_LIMIT].opt = 0x23;
	optList[ADJ_OPT_SKIN_TEMP_POWER_LIMIT].opt = 0x4a;
	optList[ADJ_OPT_COPER].opt = 0x4b;
	optList[ADJ_OPT_COALL].opt = 0x4c;
}

static int get_apu_slow_limit_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x003F0000:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
		case 0x0064020c: // StrixHalo - looks correct from dumping table, defaults to 70W
			return 0x18;
		default:
			break;
	}

	return -1;
}
static int get_apu_slow_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x003F0000:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0009:
		case 0x0064020c: // StrixHalo - untested!
			return 0x1C;
		default:
			break;
	}

	return -1;
}
static int get_vrm_current_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x18;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x20;
		default:
			break;
	}

	return -1;
}
static int get_vrm_current_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x1C;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x24;
		default:
			break;
	}

	return -1;
}
static int get_vrmsoc_current_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x20;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x28;
		default:
			break;
	}

	return -1;
}
static int get_vrmsoc_current_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x24;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x2C;
		default:
			break;
	}

	return -1;
}
static int get_vrmmax_current_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x28;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x30;
		default:
			break;
	}

	return -1;
}
static int get_vrmmax_current_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x2C;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x34;
		default:
			break;
	}

	return -1;
}
static int get_vrmsocmax_current_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x34;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x38;
		default:
			break;
	}

	return -1;
}
static int get_vrmsocmax_current_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x38;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x3C;
		default:
			break;
	}

	return -1;
}
static int get_tctl_temp_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
		case 0x0064020c:
			return 0x58; //use core1 because core0 is not reported on dual core cpus
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x003F0000:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x40;
		default:
			break;
	}

	return -1;
}
static int get_tctl_temp_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
		case 0x0064020c:
			return 0x5C; //use core1 because core0 is not reported on dual core cpus
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x003F0000:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x44;
		default:
			break;
	}

	return -1;
}
static int get_apu_skin_temp_limit_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x003F0000:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
		case 0x0064020c:
			return 0x58;
		default:
			break;
	}

	return -1;
}
static int get_apu_skin_temp_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x003F0000:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
		case 0x0064020c:
			return 0x5C;
		default:
			break;
	}

	return -1;
}
static int get_dgpu_skin_temp_limit_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
		case 0x0064020c:
			return 0x60;
		default:
			break;
	}

	return -1;
}
static int get_dgpu_skin_temp_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x00450004:
		case 0x00450005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
		case 0x0064020c:
			return 0x64;
		default:
			break;
	}

	return -1;
}

static int get_psi0_current_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x40;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x78;
		default:
			break;
	}

	return -1;
}

static int get_psi0soc_current_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x48;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x80;
		default:
			break;
	}

	return -1;
}

static int get_cclk_setpoint_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x98; //use core1 because core0 is not reported on dual core cpus;
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
			return 0xFC;
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
			return 0x100;
		default:
			break;
	}

	return -1;
}

static int get_cclk_busy_value_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0001:
		case 0x001E0002:
		case 0x001E0003:
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x9C; //use core1 because core0 is not reported on dual core cpus
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
			return 0x100;
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
			return 0x104;
		default:
			break;
	}

	return -1;
}

static int get_stapm_time_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0002:
			return 0x564;
		case 0x001E0003:
			return 0x55C;
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x5E0;
		case 0x00370000:
			return 0x768;
		case 0x00370001:
			return 0x858;
		case 0x00370002:
			return 0x860;
		case 0x00370003:
		case 0x00370004:
			return 0x880;
		case 0x00370005:
			return 0x89C;
		case 0x00400001:
			return 0x8E4;
		case 0x00400002:
			return 0x8FC;
		case 0x00400003:
			return 0x920;
		case 0x00400004:
		case 0x00400005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x918;
		default:
			break;
	}

	return -1;
}

static int get_slow_time_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x001E0002:
			return 0x568;
		case 0x001E0003:
			return 0x560;
		case 0x001E0004:
		case 0x001E0005:
		case 0x001E000A:
		case 0x001E0101:
			return 0x5E4;
		case 0x00370000:
			return 0x76C;
		case 0x00370001:
			return 0x85C;
		case 0x00370002:
			return 0x864;
		case 0x00370003:
		case 0x00370004:
			return 0x884;
		case 0x00370005:
			return 0x8A0;
		case 0x00400001:
			return 0x8E8;
		case 0x00400002:
			return 0x900;
		case 0x00400003:
			return 0x924;
		case 0x00400004:
		case 0x00400005:
		case 0x004C0006:
		case 0x004C0007:
		case 0x004C0008:
		case 0x004C0009:
			return 0x91C;
		default:
			break;
	}

	return -1;
}

static int is_core_available_in_table(const uint32_t table_ver, const int core) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400004:
		case 0x00400005: {
			if (core > 7)
				break;

			return 1;
		}
		case 0x003F0000: { // Van Gogh
			if (core > 3)
				break;

			return 1;
		}
		case 0x0064020c: { // Strix Halo
			if (core > 15)
				break;

			return 1;
		}
		default:
			break;
	}

	return 0;
}

static int get_core_power_table_offset(const uint32_t table_ver, const int core) {
	int baseOffset;

	if (is_core_available_in_table(table_ver, core) == 0)
		return -1;

	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			baseOffset = 0x300;
			break;
		case 0x00370005:
			baseOffset = 0x31C;
			break;
		case 0x003F0000: // Van Gogh
			baseOffset = 0x238;
			break;
		case 0x00400001:
			baseOffset = 0x304;
			break;
		case 0x00400004:
		case 0x00400005:
			baseOffset = 0x320;
			break;
		case 0x0064020c: // Strix Halo
			baseOffset = 0xB90;
			break;
		default:
			return -1;
	}

	return (baseOffset + (core * 4));
}

static int get_core_volt_table_offset(const uint32_t table_ver, const int core) {
	int baseOffset;

	if (is_core_available_in_table(table_ver, core) == 0)
		return -1;

	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			baseOffset = 0x320;
			break;
		case 0x00370005:
			baseOffset = 0x33C;
			break;
		case 0x003F0000: // Van Gogh
			baseOffset = 0x248;
			break;
		case 0x00400004:
		case 0x00400005:
			baseOffset = 0x340;
			break;
		case 0x0064020c: // Strix Halo
			baseOffset = 0xBD0;
			break;
		default:
			return -1;
	}

	return (baseOffset + (core * 4));
}

static int get_core_temp_table_offset(const uint32_t table_ver, const int core) {
	int baseOffset;

	if (is_core_available_in_table(table_ver, core) == 0)
		return -1;

	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			baseOffset = 0x340;
			break;
		case 0x00370005:
			baseOffset = 0x35C;
			break;
		case 0x003F0000: // Van Gogh
			baseOffset = 0x258;
			break;
		case 0x00400004:
		case 0x00400005:
			baseOffset = 0x360;
			break;
		case 0x0064020c: // Strix Halo
			baseOffset = 0xC10;
			break;
		default:
			return -1;
	}

	return (baseOffset + (core * 4));
}

static int get_core_clk_table_offset(const uint32_t table_ver, const int core) {
	int baseOffset;

	if (is_core_available_in_table(table_ver, core) == 0)
		return -1;

	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			baseOffset = 0x3A0;
			break;
		case 0x00370005:
			baseOffset = 0x3BC;
			break;
		case 0x003F0000: // Van Gogh
			baseOffset = 0x288;
			break;
		case 0x00400004:
		case 0x00400005:
			baseOffset = 0x3c0;
			break;
		case 0x0064020c:
			baseOffset = 0xc50;
			break;
		default:
			return -1;
	}

	return (baseOffset + (core *4));
}

static int get_l3_clk_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x568;
		case 0x00370005:
			return 0x584;
		case 0x003F0000: //Van Gogh
			return 0x35C;
		case 0x00400004:
		case 0x00400005:
			return 0x614;
		default:
			break;
	}

	return -1;
}

static int get_l3_logic_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x540;
		case 0x00370005:
			return 0x55C;
		case 0x003F0000: //Van Gogh
			return 0x348;
		case 0x00400004:
		case 0x00400005:
			return 0x600;
		default:
			break;
	}

	return -1;
}

static int get_l3_vddm_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x548;
		case 0x00370005:
			return 0x564;
		case 0x003F0000: //Van Gogh
			return 0x34C;
		case 0x00400004:
		case 0x00400005:
			return 0x604;
		default:
			break;
	}

	return -1;
}

static int get_l3_temp_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x550;
		case 0x00370005:
			return 0x56C;
		case 0x003F0000: //Van Gogh
			return 0x350;
		case 0x00400004:
		case 0x00400005:
			return 0x608;
		default:
			break;
	}

	return -1;
}

static int get_gfx_clk_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x5B4;
		case 0x00370005:
			return 0x5D0;
		case 0x00400001:
			return 0x60C;
		case 0x00400002:
			return 0x624;
		case 0x00400003:
			return 0x644;
		case 0x00400004:
		case 0x00400005:
			return 0x648;
		case 0x003F0000: //Van Gogh
			return 0x388;
		case 0x0064020c: // Strix Halo
			return 0x558;
		default:
			break;
	}

	return -1;
}

static int get_gfx_volt_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x5A8;
		case 0x00370005:
			return 0x5C4;
		case 0x00400001:
			return 0x600;
		case 0x00400002:
			return 0x618;
		case 0x00400003:
			return 0x638;
		case 0x00400004:
		case 0x00400005:
			return 0x63C;
		case 0x003F0000: //Van Gogh
			return 0x37C;
		case 0x0064020c: // Strix Halo
			return 0x54C;
		default:
			break;
	}

	return -1;
}

static int get_gfx_temp_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x5AC;
		case 0x00370005:
			return 0x5C8;
		case 0x00400001:
			return 0x604;
		case 0x00400002:
			return 0x61C;
		case 0x00400003:
			return 0x63C;
		case 0x00400004:
		case 0x00400005:
			return 0x640;
		case 0x003F0000: //Van Gogh
			return 0x380;
		case 0x0064020c: // Strix Halo
			return 0x550;
		default:
			break;
	}

	return -1;
}

static int get_fclk_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x5CC;
		case 0x00370005:
			return 0x5E8;
		case 0x003F0000: //Van Gogh
			return 0x3C5;
		case 0x00400004:
		case 0x00400005:
			return 0x664;
		default:
			break;
	}

	return -1;
}

static int get_mem_clk_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
			return 0x5D4;
		case 0x00370005:
			return 0x5F0;
		case 0x003F0000: //Van Gogh
			return 0x3C4;
		case 0x00400004:
		case 0x00400005:
			return 0x66c;
		default:
			break;
	}

	return -1;
}

static int get_soc_volt_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
			return 0x198;
		case 0x003F0000: //Van Gogh
			return 0x1A0;
		case 0x00400004:
		case 0x00400005:
			return 0x19c;
		default:
			break;
	}

	return -1;
}

static int get_soc_power_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
			return 0x1A0;
		case 0x003F0000: //Van Gogh
			return 0x1A8;
		case 0x00400004:
		case 0x00400005:
			return 0x1a4;
		default:
			break;
	}

	return -1;
}

static int get_socket_power_table_offset(const uint32_t table_ver) {
	switch (table_ver) {
		case 0x00370000:
		case 0x00370001:
		case 0x00370002:
		case 0x00370003:
		case 0x00370004:
		case 0x00370005:
		case 0x00400001:
		case 0x00400002:
		case 0x00400003:
		case 0x00400004:
		case 0x00400005:
			return 0x98;
		case 0x003F0000: //Van Gogh
			return 0xA8;
		default:
			break;
	}

	return -1;
}

static void init_opts(ryzen_adj_opt_t *optList) {
	for (int i=0; i<ADJ_OPT_COUNT; ++i) {
		optList[i].opt = -1;
		optList[i].opt_psmu = -1;
		optList[i].pm_table_opt_offt = -1;
		optList[i].pm_table_opt_value_offt = -1;
	}
}

ryzen_adj_opt_t *adj_init_opt_list(const RYZEN_FAMILY family) {
    ryzen_adj_opt_t *optList = malloc(sizeof(ryzen_adj_opt_t) * ADJ_OPT_COUNT);

    if (optList == NULL)
        return NULL;

    init_opts(optList);

    switch (family) {
		case FAM_RAVEN:         setRavenOpts(optList); break;
		case FAM_PICASSO:       setPicassoOpts(optList); break;
		case FAM_DALI:          setDaliOpts(optList); break;
		case FAM_RENOIR:        setRenoirOpts(optList); break;
		case FAM_LUCIENNE:      setLucienneOpts(optList); break;
		case FAM_CEZANNE:       setCezanneOpts(optList); break;
		case FAM_VANGOGH:       setVangoghOpts(optList); break;
		case FAM_REMBRANDT:     setRembrandtOpts(optList); break;
		case FAM_MENDOCINO:     setMendocinoOpts(optList); break;
		case FAM_PHOENIX:       setPhoenixOpts(optList); break;
		case FAM_HAWKPOINT:     setHawkpointOpts(optList); break;
		case FAM_STRIXPOINT:    setStrixpointOpts(optList); break;
		case FAM_STRIXHALO:     setStrixhaloOpts(optList); break;
        default: break;
    }

    return optList;
}

void adj_init_pm_table_offsets(ryzen_adj_opt_t *optList, const uint32_t table_ver) {
    // offset of first lines are stable across multiple PM Table versions
    optList[ADJ_OPT_STAPM_LIMIT].pm_table_opt_offt = 0;
    optList[ADJ_OPT_STAPM_LIMIT].pm_table_opt_value_offt = 0x4;
    optList[ADJ_OPT_FAST_LIMIT].pm_table_opt_offt = 0x8;
    optList[ADJ_OPT_FAST_LIMIT].pm_table_opt_value_offt = 0xc;
    optList[ADJ_OPT_SLOW_LIMIT].pm_table_opt_offt = 0x10;
    optList[ADJ_OPT_SLOW_LIMIT].pm_table_opt_value_offt = 0x14;
	optList[ADJ_OPT_SLOW_TIME].pm_table_opt_offt = get_slow_time_table_offset(table_ver);
	optList[ADJ_OPT_STAPM_TIME].pm_table_opt_offt = get_stapm_time_table_offset(table_ver);
	optList[ADJ_OPT_TCTL_TEMP].pm_table_opt_offt = get_tctl_temp_table_offset(table_ver);
	optList[ADJ_OPT_TCTL_TEMP].pm_table_opt_value_offt = get_tctl_temp_value_table_offset(table_ver);
	optList[ADJ_OPT_VRM_CURRENT].pm_table_opt_offt = get_vrm_current_table_offset(table_ver);
	optList[ADJ_OPT_VRM_CURRENT].pm_table_opt_value_offt = get_vrm_current_value_table_offset(table_ver);
	optList[ADJ_OPT_VRMSOC_CURRENT].pm_table_opt_offt = get_vrmsoc_current_table_offset(table_ver);
	optList[ADJ_OPT_VRMSOC_CURRENT].pm_table_opt_value_offt = get_vrmsoc_current_value_table_offset(table_ver);
	optList[ADJ_OPT_VRMMAX_CURRENT].pm_table_opt_offt = get_vrmmax_current_table_offset(table_ver);
	optList[ADJ_OPT_VRMMAX_CURRENT].pm_table_opt_value_offt = get_vrmmax_current_value_table_offset(table_ver);
	optList[ADJ_OPT_VRMSOCMAX_CURRENT].pm_table_opt_offt = get_vrmsocmax_current_table_offset(table_ver);
	optList[ADJ_OPT_VRMSOCMAX_CURRENT].pm_table_opt_value_offt = get_vrmsocmax_current_value_table_offset(table_ver);
	optList[ADJ_OPT_PSI0_CURRENT].pm_table_opt_offt = get_psi0_current_table_offset(table_ver);
	optList[ADJ_OPT_PSI0_SOC_CURRENT].pm_table_opt_offt = get_psi0soc_current_table_offset(table_ver);
	optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].pm_table_opt_offt = get_apu_skin_temp_limit_table_offset(table_ver);
	optList[ADJ_OPT_APU_SKIN_TEMP_LIMIT].pm_table_opt_value_offt = get_apu_skin_temp_value_table_offset(table_ver);
	optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].pm_table_opt_offt = get_dgpu_skin_temp_limit_table_offset(table_ver);
	optList[ADJ_OPT_DGPU_SKIN_TEMP_LIMIT].pm_table_opt_value_offt = get_dgpu_skin_temp_value_table_offset(table_ver);
	optList[ADJ_OPT_APU_SLOW_LIMIT].pm_table_opt_offt = get_apu_slow_limit_table_offset(table_ver);
	optList[ADJ_OPT_APU_SLOW_LIMIT].pm_table_opt_value_offt = get_apu_slow_value_table_offset(table_ver);
	optList[ADJ_OPT_GFX_CLK].pm_table_opt_offt = get_gfx_clk_table_offset(table_ver);
	optList[ADJ_OPT_CCLK_SETPOINT].pm_table_opt_offt = get_cclk_setpoint_table_offset(table_ver);
	optList[ADJ_OPT_CCLK_BUSY].pm_table_opt_offt = get_cclk_busy_value_table_offset(table_ver);
	optList[ADJ_OPT_CORE_0_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 0);
	optList[ADJ_OPT_CORE_1_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 1);
	optList[ADJ_OPT_CORE_2_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 2);
	optList[ADJ_OPT_CORE_3_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 3);
	optList[ADJ_OPT_CORE_4_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 4);
	optList[ADJ_OPT_CORE_5_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 5);
	optList[ADJ_OPT_CORE_6_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 6);
	optList[ADJ_OPT_CORE_7_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 7);
	optList[ADJ_OPT_CORE_8_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 8);
	optList[ADJ_OPT_CORE_9_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 9);
	optList[ADJ_OPT_CORE_10_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 10);
	optList[ADJ_OPT_CORE_11_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 11);
	optList[ADJ_OPT_CORE_12_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 12);
	optList[ADJ_OPT_CORE_13_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 13);
	optList[ADJ_OPT_CORE_14_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 14);
	optList[ADJ_OPT_CORE_15_POWER].pm_table_opt_offt = get_core_power_table_offset(table_ver, 15);
	optList[ADJ_OPT_CORE_0_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 0);
	optList[ADJ_OPT_CORE_1_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 1);
	optList[ADJ_OPT_CORE_2_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 2);
	optList[ADJ_OPT_CORE_3_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 3);
	optList[ADJ_OPT_CORE_4_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 4);
	optList[ADJ_OPT_CORE_5_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 5);
	optList[ADJ_OPT_CORE_6_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 6);
	optList[ADJ_OPT_CORE_7_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 7);
	optList[ADJ_OPT_CORE_8_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 8);
	optList[ADJ_OPT_CORE_9_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 9);
	optList[ADJ_OPT_CORE_10_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 10);
	optList[ADJ_OPT_CORE_11_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 11);
	optList[ADJ_OPT_CORE_12_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 12);
	optList[ADJ_OPT_CORE_13_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 13);
	optList[ADJ_OPT_CORE_14_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 14);
	optList[ADJ_OPT_CORE_15_VOLT].pm_table_opt_offt = get_core_volt_table_offset(table_ver, 15);
	optList[ADJ_OPT_CORE_0_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 0);
	optList[ADJ_OPT_CORE_1_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 1);
	optList[ADJ_OPT_CORE_2_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 2);
	optList[ADJ_OPT_CORE_3_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 3);
	optList[ADJ_OPT_CORE_4_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 4);
	optList[ADJ_OPT_CORE_5_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 5);
	optList[ADJ_OPT_CORE_6_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 6);
	optList[ADJ_OPT_CORE_7_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 7);
	optList[ADJ_OPT_CORE_8_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 8);
	optList[ADJ_OPT_CORE_9_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 9);
	optList[ADJ_OPT_CORE_10_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 10);
	optList[ADJ_OPT_CORE_11_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 11);
	optList[ADJ_OPT_CORE_12_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 12);
	optList[ADJ_OPT_CORE_13_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 13);
	optList[ADJ_OPT_CORE_14_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 14);
	optList[ADJ_OPT_CORE_15_TEMP].pm_table_opt_offt = get_core_temp_table_offset(table_ver, 15);
	optList[ADJ_OPT_CORE_0_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 0);
	optList[ADJ_OPT_CORE_1_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 1);
	optList[ADJ_OPT_CORE_2_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 2);
	optList[ADJ_OPT_CORE_3_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 3);
	optList[ADJ_OPT_CORE_4_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 4);
	optList[ADJ_OPT_CORE_5_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 5);
	optList[ADJ_OPT_CORE_6_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 6);
	optList[ADJ_OPT_CORE_7_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 7);
	optList[ADJ_OPT_CORE_8_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 8);
	optList[ADJ_OPT_CORE_9_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 9);
	optList[ADJ_OPT_CORE_10_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 10);
	optList[ADJ_OPT_CORE_11_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 11);
	optList[ADJ_OPT_CORE_12_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 12);
	optList[ADJ_OPT_CORE_13_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 13);
	optList[ADJ_OPT_CORE_14_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 14);
	optList[ADJ_OPT_CORE_15_CLK].pm_table_opt_offt = get_core_clk_table_offset(table_ver, 15);
	optList[ADJ_OPT_L3_CLK].pm_table_opt_offt = get_l3_clk_table_offset(table_ver);
	optList[ADJ_OPT_L3_LOGIC].pm_table_opt_offt = get_l3_logic_table_offset(table_ver);
	optList[ADJ_OPT_L3_VDDM].pm_table_opt_offt = get_l3_vddm_table_offset(table_ver);
	optList[ADJ_OPT_L3_TEMP].pm_table_opt_offt = get_l3_temp_table_offset(table_ver);
	optList[ADJ_OPT_GFX_VOLT].pm_table_opt_offt = get_gfx_volt_table_offset(table_ver);
	optList[ADJ_OPT_GFX_TEMP].pm_table_opt_offt = get_gfx_temp_table_offset(table_ver);
	optList[ADJ_OPT_FCLK].pm_table_opt_offt = get_fclk_table_offset(table_ver);
	optList[ADJ_OPT_MEM_CLK].pm_table_opt_offt = get_mem_clk_table_offset(table_ver);
	optList[ADJ_OPT_SOC_VOLT].pm_table_opt_offt = get_soc_volt_table_offset(table_ver);
	optList[ADJ_OPT_SOC_POWER].pm_table_opt_offt = get_soc_power_table_offset(table_ver);
	optList[ADJ_OPT_SOCKET_POWER].pm_table_opt_offt = get_socket_power_table_offset(table_ver);
}
