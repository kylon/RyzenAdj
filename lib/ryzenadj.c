// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com>
 * 2025 kylon - 0.20
 */
#ifdef _WIN32
#include <intrin.h>
#else
#include <cpuid.h>
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "ryzenadj.h"
#include "smu_access.h"
#include "ryzen_opts.h"

#ifndef _WIN32
#define Sleep(x) usleep((x) * 1000)
#endif

typedef struct {
    uint32_t arg0;
    unsigned msg;
} transfer_table_req_t;

typedef struct {
    os_access_obj_t *os_access;
    smu_access_t *mp1_smu;
    smu_access_t *psmu;
    RYZEN_FAMILY family;
    uint32_t bios_if_ver;
    ryzen_adj_opt_t *opt_list;
    uintptr_t table_addr;
    uint32_t table_ver;
    size_t table_size;
    float *table_values;
    transfer_table_req_t transfer_table_req;
} ryzen_access_t;

static ryzen_access_t *ry = NULL;

static void getcpuid(unsigned CPUInfo[4], const unsigned InfoType) {
#ifdef _WIN32
    __cpuid((int*)(void*)CPUInfo, (int)InfoType);
#else
    __cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#endif
}

static RYZEN_FAMILY cpuid_load_family() {
    char vendor[4 * 4];
    uint32_t regs[4];
    int family, model;

    getcpuid(regs, 0);

    /* Hack Alert! Put into str buffer */
    *(uint32_t *) &vendor[0] = regs[1];
    *(uint32_t *) &vendor[4] = regs[3];
    *(uint32_t *) &vendor[8] = regs[2];

    if (strncmp(vendor, "AuthenticAMD", strlen("AuthenticAMD")) != 0) {
        DBG("Not AMD processor\n");
        return FAM_UNKNOWN;
    }

    getcpuid(regs, 1);

    family = ((regs[0] >> 8) & 0xf) + ((regs[0] >> 20) & 0xff);
    model = ((regs[0] >> 4) & 0xf) | ((regs[0] >> 12) & 0xf0);

    switch (family) {
        case 0x17: { /* Zen, Zen+, Zen2 */
            switch (model) {
                case 17: return FAM_RAVEN;
                case 24: return FAM_PICASSO;
                case 32: return FAM_DALI;
                case 96: return FAM_RENOIR;
                case 104: return FAM_LUCIENNE;
                case 144:
                case 145: return FAM_VANGOGH;
                case 160: return FAM_MENDOCINO;
                default: break;
            }
        }
            break;
        case 0x19: { /* Zen3, Zen4 */
            switch (model) {
                case 80: return FAM_CEZANNE;
                case 64:
                case 68: return FAM_REMBRANDT;
                case 116:
                case 120: return FAM_PHOENIX;
                case 117: return FAM_HAWKPOINT;
                default: break;
            }
        }
            break;
        case 0x1A: { /* Zen5, Zen6 */
            switch (model) {
                case 32:
                case 36: return FAM_STRIXPOINT;
                case 112: return FAM_STRIXHALO;
                default: break;
            }
        }
            break;
        default:
            break;
    }

    DBG("Unsupported APU: family: %xh, model: %d\n", family, model);
    return FAM_UNKNOWN;
}

static ADJ_ERROR request_table_ver_and_size() {
    smu_service_args_t args = {0, 0, 0, 0, 0, 0};
    unsigned get_table_ver_msg;
    ADJ_ERROR ret;

    switch (ry->family) {
        case FAM_RAVEN:
        case FAM_PICASSO:
        case FAM_DALI:
            get_table_ver_msg = 0xC;
            break;
        case FAM_RENOIR:
        case FAM_LUCIENNE:
        case FAM_CEZANNE:
        case FAM_REMBRANDT:
        case FAM_PHOENIX:
        case FAM_HAWKPOINT:
        case FAM_STRIXPOINT:
        case FAM_STRIXHALO:
            get_table_ver_msg = 0x6;
            break;
        default:
            DBG("%s is not supported on this family\n", __func__);
            return ADJ_FAM_UNSUPPORTED;
    }

    ret = smu_service_req(ry->psmu, get_table_ver_msg, &args);
    if (ret != ADJ_OK)
        return ADJ_SMU_REQ_FAILED;

    ry->table_ver = args.arg0;
    if (!ry->table_ver) {
        DBG("%s did not return anything\n", __func__);
        return ADJ_SMU_UNSUPPORTED;
    }

    switch (ry->table_ver) {
        case 0x1E0001: ry->table_size = 0x568; break;
        case 0x1E0002: ry->table_size = 0x580; break;
        case 0x1E0003: ry->table_size = 0x578; break;
        case 0x1E0004:
        case 0x1E0005:
        case 0x1E000A:
        case 0x1E0101: ry->table_size = 0x608; break;
        case 0x370000: ry->table_size = 0x794; break;
        case 0x370001: ry->table_size = 0x884; break;
        case 0x370002: ry->table_size = 0x88C; break;
        case 0x370003:
        case 0x370004: ry->table_size = 0x8AC; break;
        case 0x370005: ry->table_size = 0x8C8; break;
        case 0x3F0000: ry->table_size = 0x7AC; break;
        case 0x400001: ry->table_size = 0x910; break;
        case 0x400002: ry->table_size = 0x928; break;
        case 0x400003: ry->table_size = 0x94C; break;
        case 0x400004:
        case 0x400005: ry->table_size = 0x944; break;
        case 0x450004:
        case 0x450005: ry->table_size = 0xA44; break;
        case 0x4C0006:
        case 0x4C0009: ry->table_size = 0xAA0; break;
        case 0x64020c: ry->table_size = 0xE50; break;

        // use a larger size then the largest known table to be able to test real table size of unknown tables
        default: ry->table_size = 0x1000; break;
    }

    return ADJ_OK;
}

static ADJ_ERROR request_table_addr() {
    smu_service_args_t args = {0, 0, 0, 0, 0, 0};
    unsigned get_table_addr_msg;
    ADJ_ERROR ret;

    switch (ry->family) {
        case FAM_RAVEN:
        case FAM_PICASSO:
        case FAM_DALI:
            args.arg0 = 3;
            get_table_addr_msg = 0xB;
            break;
        case FAM_RENOIR:
        case FAM_LUCIENNE:
        case FAM_CEZANNE:
        case FAM_REMBRANDT:
        case FAM_PHOENIX:
        case FAM_HAWKPOINT:
        case FAM_STRIXPOINT:
        case FAM_STRIXHALO:
            get_table_addr_msg = 0x66;
            break;
        default:
            DBG("%s is not supported on this family\n", __func__);
            return ADJ_FAM_UNSUPPORTED;
    }

    ret = smu_service_req(ry->psmu, get_table_addr_msg, &args);
    if (ret != ADJ_OK)
        return ADJ_SMU_REQ_FAILED;

    switch (ry->family) {
        case FAM_REMBRANDT:
        case FAM_PHOENIX:
        case FAM_HAWKPOINT:
        case FAM_STRIXPOINT:
        case FAM_STRIXHALO:
            ry->table_addr = (uint64_t) args.arg1 << 32 | args.arg0;
            break;
        default:
            ry->table_addr = args.arg0;
            break;
    }

    if (!ry->table_addr) {
        DBG("%s did not return anything\n", __func__);
        return ADJ_SMU_UNSUPPORTED;
    }

    return ADJ_OK;
}

static ADJ_ERROR set_transfer_table_req_data() {
    switch (ry->family) {
        case FAM_RAVEN:
        case FAM_PICASSO:
        case FAM_DALI:
            ry->transfer_table_req.arg0 = 3;
            ry->transfer_table_req.msg = 0x3D;
            break;
        case FAM_RENOIR:
        case FAM_LUCIENNE:
        case FAM_CEZANNE:
        case FAM_REMBRANDT:
        case FAM_PHOENIX:
        case FAM_HAWKPOINT:
        case FAM_STRIXPOINT:
        case FAM_STRIXHALO:
            ry->transfer_table_req.msg = 0x65;
            break;
        default:
            DBG("%s is not supported on this family\n", __func__);
            return ADJ_FAM_UNSUPPORTED;
    }

    return ADJ_OK;
}

static ADJ_ERROR request_transfer_table() {
    if (ry->transfer_table_req.msg == 0)
        return ADJ_FAM_UNSUPPORTED;

    smu_service_args_t args = {ry->transfer_table_req.arg0, 0, 0, 0, 0, 0};
    ADJ_ERROR ret = smu_service_req(ry->psmu, ry->transfer_table_req.msg, &args);

    if (ry->psmu->last_error == REP_MSG_CmdRejectedPrereq) {
        //2nd try is needed for 2 usecase: if SMU got interrupted or first call after boot on Zen2
        //we need to wait because if we don't wait 2nd call will fail, too: similar to Raven and Picasso issue but with real reject instead of 0 data response
        //but because we don't have to check any physical memory values, don't waste CPU cycles and use sleep instead
        Sleep(10);

        ret = smu_service_req(ry->psmu, ry->transfer_table_req.msg, &args);
        if (ry->psmu->last_error == REP_MSG_CmdRejectedPrereq) {
            DBG("%s was rejected twice\n", __func__);
            Sleep(100);

            ret = smu_service_req(ry->psmu, ry->transfer_table_req.msg, &args);
        }
    }

    return ret;
}

static ADJ_ERROR refresh_table() {
    if (ry == NULL || !ry->table_values)
        return ADJ_NOT_INITIALIZED;

    DBG("refresh table\n");

    // only execute request table if we don't use SMU driver
    if (!is_using_smu_driver()) {
        //if other tools call tables transfer, we may already find new data inside the memory and can avoid calling transfer table twice
        //avoiding transfer table twice is important because SMU tend to reject transfer table calls if you repeat them too fast
        //transfer table rejection happens even if we did correctly wait for response register change
        //if multiple tools retry transfer table in a loop, both will get rejections, avoid this issue by checking if we need to transfer table
        //refresh table if this is the first call (table is empty) or if the first 6 table values in memory doesn't have new values (compare result = 0)
        if (ry->table_values[0] == 0 || compare_pm_table(ry->table_values, 6 * 4) == 0) {
            const int ret = request_transfer_table();

            if (ret != ADJ_OK)
                return ret;
        }
    }

    if (copy_pm_table(ry->os_access, ry->table_values, ry->table_size)) {
        DBG("%s failed\n", __func__);
        return ADJ_ERR_MEMORY_ACCESS;
    }

    return ADJ_OK;
}

static ADJ_ERROR init_table() {
    if (ry == NULL)
        return ADJ_NOT_INITIALIZED;
    else if (ry->table_addr > 0)
        return ADJ_OK;

    DBG("init_table\n");

    ADJ_ERROR ret = request_table_ver_and_size();

    if (ret != ADJ_OK)
        return ret;

    ret = request_table_addr();
    if (ret != ADJ_OK)
        return ret;

    ret = set_transfer_table_req_data();
    if (ret != ADJ_OK)
        return ret;

    // init memory object because it is prerequiremt to woring with physical memory address
    if (init_mem_obj(ry->os_access, ry->table_addr) < 0) {
        DBG("Unable to get memory access\n");
        return ADJ_ERR_MEMORY_ACCESS;
    }

    adj_init_pm_table_offsets(ry->opt_list, ry->table_ver);

    // hold copy of table value in memory for our single value getters
    ry->table_values = calloc(ry->table_size / 4, 4);
    if (ry->table_values == NULL)
        return ADJ_OUT_OF_MEMORY;

    ret = refresh_table();
    if (ret != ADJ_OK)
        return ret;

    if (!ry->table_values[0]) {
        //Raven and Picasso don't get table refresh on the very first transfer call after boot, but respond with OK
        //if we detact 0 data, do an initial 2nd call after a small delay
        //transfer, transfer, wait, wait longer; don't work
        //transfer, wait, wait longer; don't work
        //transfer, wait, transfer; does work
        DBG("empty table detected, try again\n");
        Sleep(10);

        return refresh_table();
    }

    return ADJ_OK;
}

static float read_float_value(const uint32_t offset) {
    if (!ry->table_values)
        return NAN;

    return ry->table_values[offset / 4];
}

static char *get_smu_error_str(const uint32_t error) {
    char buf[100] = {0};
    size_t bufLen;
    char *ret;

    switch (error) {
        case REP_MSG_OK:
            snprintf(buf, sizeof(buf), "SMU request success");
            break;
        case REP_MSG_UnknownCmd:
            snprintf(buf, sizeof(buf), "SMU unknown cmd");
            break;
        case REP_MSG_CmdRejectedPrereq:
            snprintf(buf, sizeof(buf), "SMU cmd was rejected");
            break;
        case REP_MSG_CmdRejectedBusy:
            snprintf(buf, sizeof(buf), "SMU cmd was rejected - busy");
            break;
        case REP_MSG_Failed:
            snprintf(buf, sizeof(buf), "SMU failed");
            break;
        default:
            snprintf(buf, sizeof(buf), "SMU unknown response %x", error);
            break;
    }

    bufLen = strlen(buf) + 1;
    ret = malloc(bufLen);

    if (ret == NULL)
        return NULL;

    strncpy(ret, buf, bufLen);
    return ret;
}

EXP ADJ_ERROR CALL ryzenadj_init() {
    if (ry != NULL)
        return ADJ_OK;

    const size_t ryzen_access_sz = sizeof(ryzen_access_t);

    ry = malloc(ryzen_access_sz);
    if (ry == NULL)
        return ADJ_OUT_OF_MEMORY;

    memset(ry, 0, ryzen_access_sz);

    ry->family = cpuid_load_family();
    if (ry->family == FAM_UNKNOWN) {
        ryzenadj_cleanup();
        return ADJ_FAM_UNSUPPORTED;
    }

    ry->opt_list = adj_init_opt_list(ry->family);
    if (!ry->opt_list) {
        DBG("Unable to get options list\n");
        ryzenadj_cleanup();
        return ADJ_OPTLIST_FAIL;
    }

    ry->os_access = init_os_access_obj();
    if (!ry->os_access) {
        ryzenadj_cleanup();
        return ADJ_OS_ACCESS_OBJ_FAIL;
    }

    ry->mp1_smu = get_smu(ry->os_access, TYPE_MP1, ry->family);
    if (!ry->mp1_smu) {
        DBG("Unable to get MP1 SMU Obj\n");
        ryzenadj_cleanup();
        return ADJ_MP1_SMU_FAIL;
    }

    ry->psmu = get_smu(ry->os_access, TYPE_PSMU, ry->family);
    if (!ry->psmu) {
        DBG("Unable to get RSMU Obj\n");
        ryzenadj_cleanup();
        return ADJ_PSMU_FAIL;
    }

    return ADJ_OK;
}

EXP void CALL ryzenadj_cleanup() {
    if (ry == NULL)
        return;

    free(ry->opt_list);
    free(ry->mp1_smu);
    free(ry->psmu);
    free_os_access_obj(ry->os_access);
    free(ry->table_values);
    free(ry);

    ry = NULL;
}

EXP ADJ_ERROR CALL ryzenadj_refresh_table() {
    ADJ_ERROR ret = refresh_table();

    if (ret == ADJ_NOT_INITIALIZED)
        ret = init_table();

    return ret;
}

EXP ADJ_ERROR CALL ryzenadj_can_write(const ADJ_OPT opt) {
    if (ry == NULL)
        return ADJ_NOT_INITIALIZED;
    else if (opt >= ADJ_OPT_COUNT)
        return ADJ_INVALID_OPT;

    return (ry->opt_list[opt].opt != -1 || ry->opt_list[opt].opt_psmu != -1) ? ADJ_OK : ADJ_OPT_NOT_SUPPORTED;
}

EXP ADJ_ERROR CALL ryzenadj_can_read(const ADJ_OPT opt) {
    if (ry == NULL)
        return ADJ_NOT_INITIALIZED;
    else if (opt >= ADJ_OPT_COUNT)
        return ADJ_INVALID_OPT;

    return ry->opt_list[opt].pm_table_opt_offt != -1 ? ADJ_OK : ADJ_OPT_NOT_SUPPORTED;
}

EXP ADJ_ERROR CALL ryzenadj_can_read_value(const ADJ_OPT opt) {
    if (ry == NULL)
        return ADJ_NOT_INITIALIZED;
    else if (opt >= ADJ_OPT_COUNT)
        return ADJ_INVALID_OPT;

    return ry->opt_list[opt].pm_table_opt_value_offt != -1 ? ADJ_OK : ADJ_OPT_NOT_SUPPORTED;
}

EXP ADJ_ERROR CALL ryzenadj_set(const ADJ_OPT opt, const uint32_t value) {
    const ADJ_ERROR check = ryzenadj_can_write(opt);

    if (check != ADJ_OK)
        return check;

    smu_service_args_t args = {value, 0, 0, 0, 0, 0};
    ADJ_ERROR ret = ADJ_OPT_NOT_SUPPORTED;

    if (ry->opt_list[opt].opt != -1)
        ret = smu_service_req(ry->mp1_smu, ry->opt_list[opt].opt, &args);

    if (ret != ADJ_OK && ry->opt_list[opt].opt_psmu != -1) // try psmu
        ret = smu_service_req(ry->psmu, ry->opt_list[opt].opt_psmu, &args);

    return ret;
}

EXP float CALL ryzenadj_get(const ADJ_OPT opt, ADJ_ERROR *error) {
    const ADJ_ERROR check = ryzenadj_can_read(opt);

    if (error != NULL)
        *error = check;

    return check != ADJ_OK ? NAN : read_float_value(ry->opt_list[opt].pm_table_opt_offt);
}

EXP float CALL ryzenadj_get_value(const ADJ_OPT opt, ADJ_ERROR *error) {
    const ADJ_ERROR check = ryzenadj_can_read_value(opt);

    if (error != NULL)
        *error = check;

    return check != ADJ_OK ? NAN : read_float_value(ry->opt_list[opt].pm_table_opt_value_offt);
}

EXP RYZEN_FAMILY CALL ryzenadj_get_cpu_family() {
    if (ry == NULL)
        return FAM_UNKNOWN;

    return ry->family;
}

EXP uint32_t CALL ryzenadj_get_bios_if_ver() {
    if (ry == NULL)
        return 0;
    else if (ry->bios_if_ver)
        return ry->bios_if_ver;

    smu_service_args_t args = {0, 0, 0, 0, 0, 0};
    const ADJ_ERROR resp = smu_service_req(ry->mp1_smu, 0x3, &args);

    if (resp != ADJ_OK)
        return 0;

    ry->bios_if_ver = args.arg0;

    return ry->bios_if_ver;
}

EXP uintptr_t CALL ryzenadj_get_table_addr() {
    if (ry == NULL)
        return 0;

    return ry->table_addr;
}

EXP uint32_t CALL ryzenadj_get_table_ver() {
    if (ry == NULL)
        return 0;

    return ry->table_ver;
}

EXP size_t CALL ryzenadj_get_table_size() {
    if (ry == NULL)
        return 0;

    return ry->table_size;
}

EXP float * CALL ryzenadj_get_table_values() {
    if (ry == NULL)
        return NULL;

    return ry->table_values;
}

EXP uint32_t CALL ryzenadj_get_mp1_smu_last_error() {
    if (ry == NULL)
        return -1;

    return ry->mp1_smu->last_error;
}

EXP uint32_t CALL ryzenadj_get_psmu_last_error() {
    if (ry == NULL)
        return -1;

    return ry->psmu->last_error;
}

EXP char * CALL ryzenadj_error_str(const ADJ_ERROR error) {
    if (ry == NULL)
        return NULL;

    char buf[256] = {0};
    size_t bufLen;
    char *ret;

    switch (error) {
        case ADJ_OK:
            snprintf(buf, sizeof(buf), "RyzenAdj: success");
            break;
        case ADJ_NOT_INITIALIZED:
            snprintf(buf, sizeof(buf), "RyzenAdj: init function not called");
            break;
        case ADJ_OUT_OF_MEMORY:
            snprintf(buf, sizeof(buf), "RyzenAdj: failed to alloc memory");
            break;
        case ADJ_INVALID_OPT:
            snprintf(buf, sizeof(buf), "RyzenAdj: invalid option ID");
            break;
        case ADJ_OPT_NOT_SUPPORTED:
            snprintf(buf, sizeof(buf), "RyzenAdj: unsupported operation");
            break;
        case ADJ_FAM_UNSUPPORTED:
            snprintf(buf, sizeof(buf), "RyzenAdj: unsupported ryzen family");
            break;
        case ADJ_ERR_MEMORY_ACCESS:
            snprintf(buf, sizeof(buf), "RyzenAdj: unable to get memory access");
            break;
        case ADJ_OPTLIST_FAIL:
            snprintf(buf, sizeof(buf), "RyzenAdj: failed to create options list");
            break;
        case ADJ_OS_ACCESS_OBJ_FAIL:
            snprintf(buf, sizeof(buf), "RyzenAdj: failed to initialize os_access Obj");
            break;
        case ADJ_MP1_SMU_FAIL:
            snprintf(buf, sizeof(buf), "RyzenAdj: unable to get MP1 SMU Obj");
            break;
        case ADJ_PSMU_FAIL:
            snprintf(buf, sizeof(buf), "RyzenAdj: unable to get PSMU Obj");
            break;
        case ADJ_SMU_UNSUPPORTED:
            snprintf(buf, sizeof(buf), "RyzenAdj: unsupported SMU");
            break;
        case ADJ_SMU_REQ_FAILED: {
            char *mp1_err = get_smu_error_str(ry->mp1_smu->last_error);
            char *psmu_err = get_smu_error_str(ry->psmu->last_error);

            snprintf(buf, sizeof(buf), "RyzenAdj:\nMP1_SMU last error: %s\nPSMU last error: %s", mp1_err, psmu_err);
            free(mp1_err);
            free(psmu_err);
        }
            break;
        default:
            snprintf(buf, sizeof(buf), "RyzenAdj: Unknown error code %d", error);
            break;
    }

    bufLen = strlen(buf) + 1;
    ret = malloc(bufLen);

    if (ret == NULL)
        return NULL;

    strncpy(ret, buf, bufLen);
    return ret;
}
