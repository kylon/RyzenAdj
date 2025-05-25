// SPDX-License-Identifier: LGPL
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
#include <stdlib.h>

#include "smu_access.h"

#define MP1_C2PMSG_MESSAGE_ADDR_1		0x3B10528
#define MP1_C2PMSG_RESPONSE_ADDR_1		0x3B10564
#define MP1_C2PMSG_ARG_BASE_1			0x3B10998

/* For Vangogh and Rembrandt */
#define MP1_C2PMSG_MESSAGE_ADDR_2		0x3B10528
#define MP1_C2PMSG_RESPONSE_ADDR_2		0x3B10578
#define MP1_C2PMSG_ARG_BASE_2			0x3B10998

/* For Strix Point */
#define MP1_C2PMSG_MESSAGE_ADDR_3		0x3b10928
#define MP1_C2PMSG_RESPONSE_ADDR_3		0x3b10978
#define MP1_C2PMSG_ARG_BASE_3			0x3b10998

#define PSMU_C2PMSG_MESSAGE_ADDR		0x3B10a20
#define PSMU_C2PMSG_RESPONSE_ADDR		0x3B10a80
#define PSMU_C2PMSG_ARG_BASE			0x3B10a88

/* All the SMU have the same TestMessage as of now, correct me if they don't */
#define SMU_TEST_MSG 0x1

static int smu_service_test(const smu_access_t *smu) {
	uint32_t response = 0;

	/* Clear the response */
	smn_reg_write(smu->os_access, smu->rep, 0);

	/* Test message with unique argument */
	smn_reg_write(smu->os_access, smu->arg_base, 0x47);

	if (smn_reg_read(smu->os_access, smu->arg_base) != 0x47) {
		DBG("PCI Bus is not writeable, check secure boot\n");
		return 0;
	}

	/* Send message ID */
	smn_reg_write(smu->os_access, smu->msg, SMU_TEST_MSG);

	/* Wait until reponse changed */
	while (response == 0)
		response = smn_reg_read(smu->os_access, smu->rep);

	return response == REP_MSG_OK;
}

static void init_type_mp1(smu_access_t *smu, const RYZEN_FAMILY family) {
	switch (family) {
		case FAM_REMBRANDT:
		case FAM_VANGOGH:
		case FAM_MENDOCINO:
		case FAM_PHOENIX:
		case FAM_HAWKPOINT: {
			smu->msg = MP1_C2PMSG_MESSAGE_ADDR_2;
			smu->rep = MP1_C2PMSG_RESPONSE_ADDR_2;
			smu->arg_base = MP1_C2PMSG_ARG_BASE_2;
		}
			break;
		case FAM_KRACKANPOINT:
		case FAM_STRIXPOINT:
		case FAM_STRIXHALO: {
			smu->msg = MP1_C2PMSG_MESSAGE_ADDR_3;
			smu->rep = MP1_C2PMSG_RESPONSE_ADDR_3;
			smu->arg_base = MP1_C2PMSG_ARG_BASE_3;
		}
			break;
		default: {
			smu->msg = MP1_C2PMSG_MESSAGE_ADDR_1;
			smu->rep = MP1_C2PMSG_RESPONSE_ADDR_1;
			smu->arg_base = MP1_C2PMSG_ARG_BASE_1;
		}
			break;
	}
}

static uint32_t c2pmsg_argX_addr(const uint32_t y, const uint32_t x) {
	return (y + 4 * x);
}

smu_access_t *get_smu(os_access_obj_t *obj, const SMU_TYPE type, const RYZEN_FAMILY family) {
	smu_access_t *smu = malloc(sizeof(smu_access_t));

	if (smu == NULL)
		return NULL;

	smu->os_access = obj;
	smu->last_error = 0;

	/* Fill SMU information */
	switch (type) {
		case TYPE_MP1:
			init_type_mp1(smu, family);
			break;
		case TYPE_PSMU: {
			smu->msg = PSMU_C2PMSG_MESSAGE_ADDR;
			smu->rep = PSMU_C2PMSG_RESPONSE_ADDR;
			smu->arg_base = PSMU_C2PMSG_ARG_BASE;
		}
			break;
		default: {
			DBG("Failed to get SMU, unknown SMU_TYPE: %i\n", type);
			goto err;
		}
	}

	if (smu_service_test(smu))
		return smu;

	DBG("Faild to get SMU, SMU_TYPE: %i\n", type);

err:
	free(smu);
	return NULL;
}

ADJ_ERROR smu_service_req(smu_access_t *smu, const uint32_t id , smu_service_args_t *args) {
	uint32_t response = 0x0;

	DBG("SMU_SERVICE REQ_ID:0x%x\n", id);
	DBG("SMU_SERVICE REQ: arg0: 0x%x, arg1:0x%x, arg2:0x%x, arg3:0x%x, arg4: 0x%x, arg5: 0x%x\n",  \
		args->arg0, args->arg1, args->arg2, args->arg3, args->arg4, args->arg5);

	/* Clear the response */
	smn_reg_write(smu->os_access, smu->rep, 0x0);

	/* Pass arguments */
	smn_reg_write(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 0), args->arg0);
	smn_reg_write(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 1), args->arg1);
	smn_reg_write(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 2), args->arg2);
	smn_reg_write(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 3), args->arg3);
	smn_reg_write(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 4), args->arg4);
	smn_reg_write(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 5), args->arg5);

	/* Send message ID */
	smn_reg_write(smu->os_access, smu->msg, id);

	/* Wait until reponse changed */
	while(response == 0x0)
		response = smn_reg_read(smu->os_access, smu->rep);

	/* Read back arguments */
	args->arg0 = smn_reg_read(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 0));
	args->arg1 = smn_reg_read(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 1));
	args->arg2 = smn_reg_read(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 2));
	args->arg3 = smn_reg_read(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 3));
	args->arg4 = smn_reg_read(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 4));
	args->arg5 = smn_reg_read(smu->os_access, c2pmsg_argX_addr(smu->arg_base, 5));

	DBG("SMU_SERVICE REP: 0x%x, arg0: 0x%x, arg1:0x%x, arg2:0x%x, arg3:0x%x, arg4: 0x%x, arg5: 0x%x\n",  \
		response, args->arg0, args->arg1, args->arg2, args->arg3, args->arg4, args->arg5);

	smu->last_error = response;

	return response == REP_MSG_OK ? ADJ_OK : ADJ_SMU_REQ_FAILED;
}
