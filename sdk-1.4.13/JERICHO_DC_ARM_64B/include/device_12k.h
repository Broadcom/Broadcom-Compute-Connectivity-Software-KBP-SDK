/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DEVMGR_H
#define __DEVMGR_H

#include <stdint.h>
#include "errors.h"
#include "kbp_legacy.h"
#include "device.h"

/**
 * @file device_12k.h
 *
 * Provides low-level access to device registers. These
 * APIs are not portable between devices.
 *
 * @addtogroup O3S_REG_APIS
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

struct kbp_search_result;

/* device defines */

/* enum definition for 4 parallel searches */
enum kbp_dev_12k_parallel_srch_type {
    KBP_DEV_12K_PARALLEL_SEARCH_0 = 0,
    KBP_DEV_12K_PARALLEL_SEARCH_1,
    KBP_DEV_12K_PARALLEL_SEARCH_2,
    KBP_DEV_12K_PARALLEL_SEARCH_3,
    KBP_DEV_12K_PARALLEL_SEARCH_END  /* invalid parallel search, must be last element */
};

/* enum definition for 4 keys searched in parallel */
enum kbp_dev_12k_key_type {
    KBP_DEV_12K_KEY_0 = 0,
    KBP_DEV_12K_KEY_1,
    KBP_DEV_12K_KEY_2,
    KBP_DEV_12K_KEY_3,
    KBP_DEV_12K_KEY_END              /* invalid key, must be last element */
};

enum kbp_dev_12k_addrtype {
    KBP_DEV_12K_ADDR_TYPE_REG = 0,
    KBP_DEV_12K_ADDR_TYPE_DBA = 1,
    KBP_DEV_12K_ADDR_TYPE_UDA = 2
};

enum kbp_dev_12k_banknum {
    KBP_DEV_12K_BANK_0 = 0,
    KBP_DEV_12K_BANK_1
};

enum kbp_dev_12k_portnum {
    KBP_DEV_12K_PORT_0 = 0,
    KBP_DEV_12K_PORT_1
};

enum kbp_dev_12k_smtnum{
    KBP_DEV_12K_SMT_0 = 0,
    KBP_DEV_12K_SMT_1
};

enum kbp_dev_12k_portmode {
    KBP_DEV_12K_SINGLE_PORT = 0,
    KBP_DEV_12K_DUAL_PORT
};

enum kbp_dev_12k_smt_mode {
    KBP_DEV_12K_NO_SMT_MODE = 0,
    KBP_DEV_12K_DUAL_SMT_MODE
};

enum kbp_dev_12k_blk_count_dir {
    KBP_DEV_12K_BLK_COUNT_UP = 0,
    KBP_DEV_12K_BLK_COUNT_DOWN
} ;

enum kbp_dev_12k_blk_inst_type {
    KBP_DEV_12K_BLK_COPY_INST = 0,
    KBP_DEV_12K_BLK_MOVE_INST,
    KBP_DEV_12K_BLK_CLEAR_INST,
    KBP_DEV_12K_BLK_ENTRY_VALIDATE_INST
} ;

/*
 * Operation mode for the 11K device
 */
enum kbp_dev_12k_operation_mode {
    KBP_DEV_12K_OPR_STANDARD,
    KBP_DEV_12K_OPR_SAHASRA
};

enum kbp_dev_12k_em_write_mode {
    KBP_DEV_12K_EM_WRITE_MODE_A,        /* The write mode is WRA */
    KBP_DEV_12K_EM_WRITE_MODE_B         /* The write mode is WRB */
};

enum kbp_dev_12k_em_read_mode {
    KBP_DEV_12K_EM_READ_MODE_A,         /* The read mode is RDA */
    KBP_DEV_12K_EM_READ_MODE_B          /* The read mode is RDB */
} ;


#define KBP_DEV_12K_REG_ADDR_LEN_IN_BYTES                    (4)
#define KBP_DEV_12K_AB_ENTRY_VALID_BIT_IN_ADDR               (30)
#define KBP_DEV_12K_AB_ENTRY_WR_MODE_BIT_IN_ADDR             (31)
#define KBP_DEV_12K_ADDR_TYPE_BIT_IN_PIO_WRITE               (25)    /* 26b-25b:  00->REG, 01->DBA, 10->UDA */

/* Global Register definitions */
#define KBP_DEV_12K_REG_ADDR_DEVICE_ID                          (0x00000000)
#define KBP_DEV_12K_REG_ADDR_DEVICE_CONFIG                      (0x00000001)
#define KBP_DEV_12K_REG_ADDR_DEVICE_STATUS                      (0x00000002)
#define KBP_DEV_12K_REG_ADDR_SOFT_SCAN_WRITE                    (0x00000004)
#define KBP_DEV_12K_REG_ADDR_SOFT_ERROR_FIFO                    (0x00000005)

#define KBP_DEV_12K_REG_ADDR_LPT_ENABLE                         (0x00000101)
#define KBP_DEV_12K_REG_ADDR_SCRATCH_PAD0                       (0x00000102)
#define KBP_DEV_12K_REG_ADDR_SCRATCH_PAD1                       (0x00000103)
#define KBP_DEV_12K_RESULT_REG_ADDRESS_START                    (0x00000104)
#define KBP_DEV_12K_RESULT_REG_ADDRESS_END                      (0x00000106)

#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_COUNT_PORT0         (0x00000186)
#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_FIFO_PORT0          (0x00000187)
#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_RD_PTR_PORT0        (0x00000188)
#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_WR_PTR_PORT0        (0x00000189)

#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_COUNT_PORT1         (0x0000018A)
#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_FIFO_PORT1          (0x0000018B)
#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_RD_PTR_PORT1        (0x0000018C)
#define KBP_DEV_12K_REG_ADDR_UDA_SOFT_ERROR_WR_PTR_PORT1        (0x0000018D)

#define KBP_DEV_12K_REG_ADDR_UDA_CONFIG                         (0x0000010B)

#define KBP_DEV_12K_REG_ADDR_ERROR_STATUS_PORT_0                (0x00000180)
#define KBP_DEV_12K_REG_ADDR_ERROR_STATUS_PORT_1                (0x00000182)
#define KBP_DEV_12K_REG_ADDR_INTERRUPT_MASK_PORT_0              (0x00000181)
#define KBP_DEV_12K_REG_ADDR_INTERRUPT_MASK_PORT_1              (0x00000183)

/* Block Registers */
#define KBP_DEV_12K_REG_ADDR_BLK_CONFIG(x)                  (0x00001000 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR0_79_0(x)                   (0x00001001 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR0_159_80(x)                 (0x00001002 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR0_239_160(x)                (0x00001003 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR0_319_240(x)                (0x00001004 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR1_79_0(x)                   (0x00001005 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR1_159_80(x)                 (0x00001006 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR1_239_160(x)                (0x00001007 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR1_319_240(x)                (0x00001008 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR2_79_0(x)                   (0x00001009 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR2_159_80(x)                 (0x0000100A + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR2_239_160(x)                (0x0000100B + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR2_319_240(x)                (0x0000100C + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR3_79_0(x)                   (0x0000100D + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR3_159_80(x)                 (0x0000100E + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR3_239_160(x)                (0x0000100F + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR3_319_240(x)                (0x00001010 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR4_79_0(x)                   (0x00001011 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR4_159_80(x)                 (0x00001012 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR4_239_160(x)                (0x00001013 + ((x) * 0x20))
#define KBP_DEV_12K_REG_ADDR_BMR4_319_240(x)                (0x00001014 + ((x) * 0x20))
#define KBP_DEV_12K_NO_MASK_BMR_NUM                         (7)

#define KBP_DEV_12K_BLK_REGISTERS_START_ADDR                KBP_DEV_12K_REG_ADDR_BLK_CONFIG(0)
#define KBP_DEV_12K_BLK_REGISTERS_END_ADDR                  KBP_DEV_12K_REG_ADDR_BMR4_319_240(KBP_DEV_12K_NUM_ARRAY_BLOCKS-1)

/* Logical Table Registers */
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT0(x)           (0x00040000 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT1(x)           (0x00040001 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT2(x)           (0x00040002 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT3(x)           (0x00040003 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT4(x)           (0x00040004 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT5(x)           (0x00040005 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT6(x)           (0x00040006 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_BLOCK_SELECT7(x)           (0x00040007 + ((x) * 0x100))

#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH0(x)        (0x00040010 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH1(x)        (0x00040011 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH2(x)        (0x00040012 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH3(x)        (0x00040013 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH4(x)        (0x00040014 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH5(x)        (0x00040015 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH6(x)        (0x00040016 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH7(x)        (0x00040017 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH8(x)        (0x00040018 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH9(x)        (0x00040019 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH10(x)       (0x0004001A + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH11(x)       (0x0004001B + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH12(x)       (0x0004001C + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH13(x)       (0x0004001D + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH14(x)       (0x0004001E + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_PARALLEL_SEARCH15(x)       (0x0004001F + ((x) * 0x100))

#define KBP_DEV_12K_REG_ADDR_LTR_SB_KPU_SELECT(x)           (0x00040050 + ((x) * 0x100))

#define KBP_DEV_12K_REG_ADDR_LTR_RANGE_INSERTION0(x)        (0x00040058 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_RANGE_INSERTION1(x)        (0x00040059 + ((x) * 0x100))

#define KBP_DEV_12K_REG_ADDR_LTR_EXTENDED0(x)               (0x0004005A + ((x) * 0x100))

#define KBP_DEV_12K_REG_ADDR_LTR_KPU0_KEY_CONSTRUCTION0(x)  (0x0004005C + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU0_KEY_CONSTRUCTION1(x)  (0x0004005D + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU1_KEY_CONSTRUCTION0(x)  (0x0004005E + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU1_KEY_CONSTRUCTION1(x)  (0x0004005F + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU2_KEY_CONSTRUCTION0(x)  (0x00040060 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU2_KEY_CONSTRUCTION1(x)  (0x00040061 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU3_KEY_CONSTRUCTION0(x)  (0x00040062 + ((x) * 0x100))
#define KBP_DEV_12K_REG_ADDR_LTR_KPU3_KEY_CONSTRUCTION1(x)  (0x00040063 + ((x) * 0x100))

#define KBP_DEV_12K_REG_ADDR_LTR_OP_CODE_EXT(x)             (0x00040070 + ((x) * 0x100))

#define KBP_DEV_12K_LTR_REG_GROUP_ADDRESS_START             (0x00040000)
#define KBP_DEV_12K_LTR_REG_GROUP_ADDRESS_END               (KBP_DEV_12K_REG_ADDR_LTR_OP_CODE_EXT(KBP_DEV_12K_MAX_NUM_LTRS-1))
#define KBP_DEV_12K_LTR_NUM_OF_KCR_PER_KPU                  (2)
#define KBP_DEV_12K_LTR_NUM_OF_SEGMENT_PER_KCR              (5)

#define KBP_DEV_12K_MAX_KEY_LEN_IN_BITS                  (640)
#define KBP_DEV_12K_MAX_KEY_LEN_IN_BYTES                 (KBP_DEV_12K_MAX_KEY_LEN_IN_BITS / 8)

#define KBP_DEV_12K_NUM_BLKS_PER_BLOCK_SELECT_REG           (64)
#define KBP_DEV_12K_NUM_SB_PER_BLOCK_SELECT_REG             (KBP_DEV_12K_NUM_BLKS_PER_BLOCK_SELECT_REG/KBP_DEV_12K_NUM_AB_PER_SUPER_BLOCK)
#define KBP_DEV_12K_NUM_BLKS_PER_PS_REG                     (32)

/* Context Buffer address range */
#define KBP_DEV_12K_MC_CB_REG_ADDRESS_RANGE_START        (0x00020000)
#define KBP_DEV_12K_MC_CB_REG_ADDRESS_RANGE_END          (0x00027FFF)
#define KBP_DEV_12K_REG_ADDR_CONTEXT_BUFFER(x)              (0x00020000 + (x))

/* Device (Global) Register field definitions */
#define KBP_DEV_12K_DEVICE_CONFIG_REG_PORT1_CTXID_SHIFT_END_BIT     (50)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_PORT1_CTXID_SHIFT_START_BIT   (48)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_AC_TO_BANK_MAPPING_END_BIT    (47)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_AC_TO_BANK_MAPPING_START_BIT  (32)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_SUPRESS_INDEX_ENABLE_BIT      (30)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_RANGE_ENABLE_BIT              (28)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_NW_BYTE_ORDER_ENABLE_BIT      (27)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_PORT1_ENABLE_BIT              (26)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_PORT0_ENABLE_BIT              (25)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_DUAL_PORT_MODE_BIT            (24)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_DUAL_BANK_MODE_BIT            (23)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_CB_CONFIG_END_BIT             (22)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_CB_CONFIG_START_BIT           (15)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_DB_PEEI_BIT                   (7)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_SOFT_ES_ENABLE_BIT            (6)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_PORT0_ERR_INTR_ON_PORT1       (5)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_PORT1_ERR_INTR_ON_PORT0       (4)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_MC_SEGMT_CAS_ENBL_BIT         (3)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_LAST_DEVICE_BIT               (1)
#define KBP_DEV_12K_DEVICE_CONFIG_REG_FIRST_DEVICE_BIT              (0)

/* UDA Configuration Register */
#define KBP_DEV_12K_UDA_CONFIG_REG_uSBENABLE_END_BIT                (15)
#define KBP_DEV_12K_UDA_CONFIG_REG_uSBENABLE_START_BIT              (0)

/* Device Status Register */
#define KBP_DEV_12K_DEV_STATUS_REG_uSBENABLE_END_BIT                (15)
#define KBP_DEV_12K_DEV_STATUS_REG_uSBENABLE_START_BIT              (0)

/* Database Soft error scan Register */
#define KBP_DEV_12K_DEV_DB_SOFT_ERR_SCAN_WRITE_INTVL_VAL_HI_END_BIT         (59)
#define KBP_DEV_12K_DEV_DB_SOFT_ERR_SCAN_WRITE_INTVL_VAL_HI_START_BIT       (44)
#define KBP_DEV_12K_DEV_DB_SOFT_ERR_SCAN_WRITE_INTVL_VAL_LO_END_BIT         (43)
#define KBP_DEV_12K_DEV_DB_SOFT_ERR_SCAN_WRITE_INTVL_VAL_LO_START_BIT       (12)
#define KBP_DEV_12K_DEV_DB_SOFT_ERR_SCAN_WRITE_ADDR_END_BIT                 (11)
#define KBP_DEV_12K_DEV_DB_SOFT_ERR_SCAN_WRITE_ADDR_START_BIT               (0)

/* Block Configuration Register */
#define KBP_DEV_12K_BLOCK_CONFIG_REG_ENABLE_BIT_POS         (0)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_WIDTH_START_BIT        (1)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_WIDTH_END_BIT          (2)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_SHIFT_VAL_START_BIT    (4)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_SHIFT_VAL_END_BIT      (5)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_BASE_ADDR_START_BIT    (6)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_BASE_ADDR_END_BIT      (19)
#define KBP_DEV_12K_BLOCK_CONFIG_REG_SHIFT_DIR_BIT_POS      (24)

/* super block configuration  depending on sb number x*/
#define KBP_DEV_12K_SB_CONFIG_START_BIT(x)          (2*x)
#define KBP_DEV_12K_SB_CONFIG_END_BIT(x)            ((2*x) + 1)

/* parallel search configure depending on block number x */
#define KBP_DEV_12K_PS_CONFIG_BLK_START_BIT(x)      (2*x)
#define KBP_DEV_12K_PS_CONFIG_BLK_END_BIT(x)        ((2*x) + 1)

/*x is the parallel search number*//* RRJ check 4x */
#define KBP_DEV_12K_EXTENDED_REG_BMR_SELECT_START_BIT(x)        ((3*x))
#define KBP_DEV_12K_EXTENDED_REG_BMR_SELECT_END_BIT(x)          ((3*x) + 2)

#define KBP_DEV_12K_EXTENDED_REG_RANGE_A_EXTRACTION_START_BIT   (24)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_A_EXTRACTION_END_BIT     (30)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_B_EXTRACTION_START_BIT   (31)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_B_EXTRACTION_END_BIT     (37)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_C_EXTRACTION_START_BIT   (38)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_C_EXTRACTION_END_BIT     (44)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_D_EXTRACTION_START_BIT   (45)
#define KBP_DEV_12K_EXTENDED_REG_RANGE_D_EXTRACTION_END_BIT     (51)

#define KBP_DEV_12K_EXTENDED_REG_NUM_RESULTS_START_BIT          (56)
#define KBP_DEV_12K_EXTENDED_REG_NUM_RESULTS_END_BIT            (57)
#define KBP_DEV_12K_EXTENDED_REG_AD_RESOLUTION_BIT              (58)

/* x is result number */
#define KBP_DEV_12K_OP_CODE_EXT_REG_LCL_OP_CODE_START_BIT   (0)
#define KBP_DEV_12K_OP_CODE_EXT_REG_LCL_OP_CODE_END_BIT     (7)
#define KBP_DEV_12K_OP_CODE_EXT_REG_RETURN_AD_BIT_POS(x)    (8 + (4*x))
#define KBP_DEV_12K_OP_CODE_EXT_REG_AD_SIZE_START_BIT(x)    (9 + (4*x))
#define KBP_DEV_12K_OP_CODE_EXT_REG_AD_SIZE_END_BIT(x)      (10 + (4*x))
#define KBP_DEV_12K_OP_CODE_EXT_REG_TRANS_ADDR_BIT_POS(x)   (11 + (4*x))

/*Key Construction Register */
#define KBP_DEV_12K_KPU_KCR_NUM_BITS_FOR_START_LOC          (7)
#define KBP_DEV_12K_KPU_KCR_NUM_BITS_FOR_NUM_BYTES          (4)
#define KBP_DEV_12K_KPU_KCR_NUM_BITS_FOR_ZERO_FILL          (1)
#define KBP_DEV_12K_KPU_KCR_NUM_BITS_PER_SEGMENT            (12)

#define KBP_DEV_12K_UDA_NUM_ROWS_SHIFT_VALUE            (13)

/* default AC to Bank Mapping value */
#define KBP_DEV_12K_AC_2_BANK_MAPPING                   (0xFF00)
#define KBP_DEV_12K_P1CTXID_SHIFT_VALUE                 (0x4)

/* Range Manager related */
#define KBP_DEV_12K_RANGE_DO_NOT_INSERT              (0x7F)
#define KBP_DEV_12K_RANGE_NUM_RANGE_TYPES            (4)
#define KBP_DEV_12K_RANGE_NUM_MCOR_PER_RANGE_TYPE    (8)
#define KBP_DEV_12K_RANGE_NUM_RANGE_CODE_REGS        (8)
#define KBP_DEV_12K_NUM_RANGE_REG                    (40)

/* Range Registers */
#define KBP_DEV_12K_REG_RANGE_A_BOUNDS(x)               (0x00085000 + ((x) * 0x01))
#define KBP_DEV_12K_REG_RANGE_B_BOUNDS(x)               (0x00085008 + ((x) * 0x01))
#define KBP_DEV_12K_REG_RANGE_C_BOUNDS(x)               (0x00085010 + ((x) * 0x01))
#define KBP_DEV_12K_REG_RANGE_D_BOUNDS(x)               (0x00085018 + ((x) * 0x01))

#define KBP_DEV_12K_REG_RANGE_A_CODE0                   (0x00085020)
#define KBP_DEV_12K_REG_RANGE_A_CODE1                   (0x00085021)
#define KBP_DEV_12K_REG_RANGE_B_CODE0                   (0x00085022)
#define KBP_DEV_12K_REG_RANGE_B_CODE1                   (0x00085023)
#define KBP_DEV_12K_REG_RANGE_C_CODE0                   (0x00085024)
#define KBP_DEV_12K_REG_RANGE_C_CODE1                   (0x00085025)
#define KBP_DEV_12K_REG_RANGE_D_CODE0                   (0x00085026)
#define KBP_DEV_12K_REG_RANGE_D_CODE1                   (0x00085027)

#define KBP_DEV_12K_MAX_DEV_NUM                      (4)
#define KBP_DEV_12K_MAX_DEV_NUM_SCG4                 (2)

#define KBP_DEV_12K_MAX_DEV_NUM_11K                  (4)

/* DevId is at Bits[24:23] of Address */
#define KBP_DEV_12K_GET_DEV_ID(address)              ((uint8_t)(((address) >>  23) & 0x3))

#define KBP_DEV_12K_NUM_ARRAY_BLOCKS                 (256)
#define KBP_DEV_12K_TOTAL_NUM_AC                     (16)
#define KBP_DEV_12K_NUM_SUPER_BLOCKS                 (32)

#define KBP_DEV_12K_NUM_AB_PER_SUPER_BLOCK           (KBP_DEV_12K_NUM_ARRAY_BLOCKS / KBP_DEV_12K_NUM_SUPER_BLOCKS)

#define KBP_DEV_12K_NUM_SB_PER_AC                    (2)
#define KBP_DEV_12K_NUM_AB_PER_AC                    (KBP_DEV_12K_NUM_SB_PER_AC * KBP_DEV_12K_NUM_AB_PER_SUPER_BLOCK)

/* 40M device specifications */
#define KBP_DEV_12K_TOTAL_NUM_AC_40M                 (16)  /* RJ to check */
#define KBP_DEV_12K_NUM_ARRAY_BLOCKS_40M             (128)
#define KBP_DEV_12K_NUM_AB_PER_SUPER_BLOCK_40M       (KBP_DEV_12K_NUM_ARRAY_BLOCKS_40M/KBP_DEV_12K_NUM_SUPER_BLOCKS)
#define KBP_DEV_12K_NUM_AB_PER_AC_40M                (KBP_DEV_12K_NUM_SB_PER_AC * KBP_DEV_12K_NUM_AB_PER_SUPER_BLOCK_40M)

/* Array Block (AB) width and depth */
#define KBP_DEV_12K_AB_WIDTH_IN_BITS                 (80)
#define KBP_DEV_12K_AB_WIDTH_IN_BYTES                (KBP_DEV_12K_AB_WIDTH_IN_BITS / 8)

#define KBP_DEV_12K_AB_MIN_WIDTH_IN_BITS             (80)
#define KBP_DEV_12K_AB_MIN_WIDTH_IN_BYTES            (KBP_DEV_12K_AB_MIN_WIDTH_IN_BITS / 8)

#define KBP_DEV_12K_AB_DEPTH                         (4096)

#define KBP_DEV_12K_MAX_AB_WIDTH_IN_BITS             (640)
#define KBP_DEV_12K_MAX_AB_WIDTH_IN_BYTES            (KBP_DEV_12K_MAX_AB_WIDTH_IN_BITS / 8)

#define KBP_DEV_12K_MAX_NUM_DBA_ENTRIES              (KBP_DEV_12K_AB_DEPTH * KBP_DEV_12K_NUM_ARRAY_BLOCKS)

#define KBP_DEV_12K_BYTES_IN_AB                      (KBP_DEV_12K_AB_DEPTH * KBP_DEV_12K_AB_MIN_WIDTH_IN_BYTES)

#define KBP_DEV_12K_NUM_BMRS_PER_AB                  (5)
#define KBP_DEV_12K_NUM_80BIT_SEGMENTS_PER_BMR       (4)

#define KBP_DEV_12K_NUM_KEYS_PER_INST                (4)
#define KBP_DEV_12K_NUM_KEYS                         (KBP_DEV_12K_NUM_KEYS_PER_INST)
#define KBP_DEV_12K_NUM_KPU                          (4)
#define KBP_DEV_12K_NUM_OF_KCR_PER_KEY               (2)
#define KBP_DEV_12K_NUM_OF_SEGMENTS_PER_KCR          (5)
#define KBP_DEV_12K_NUM_OF_SEGMENTS_PER_KEY          (KBP_DEV_12K_NUM_OF_SEGMENTS_PER_KCR * KBP_DEV_12K_NUM_OF_KCR_PER_KEY)
#define KBP_DEV_12K_MAX_NUM_BYTES_PER_KCR_SEG        (16)

#define KBP_DEV_12K_NUM_PARALLEL_SEARCHES_PER_INST   (4)
#define KBP_DEV_12K_NUM_PARALLEL_SEARCHES            (KBP_DEV_12K_NUM_PARALLEL_SEARCHES_PER_INST)

#define KBP_DEV_12K_MAX_NUM_RESULT_PORTS                (4)
#define KBP_DEV_12K_MAX_NUM_RESULTS                     (6)

#define KBP_DEV_12K_DATA_WIDTH_BYTES                    (10)

#define KBP_DEV_12K_EM_RECORD_WIDTH_IN_BYTES            (8)
#define KBP_DEV_12K_EM_RECORD_WIDTH_IN_BITS             (64)
#define KBP_DEV_12K_EM_HW_INPUT_LEN_IN_BYTES            (10)

#define KBP_DEV_12K_EM_HW_OUTPUT_LEN_IN_BYTES           (KBP_DEV_12K_EM_HW_INPUT_LEN_IN_BYTES + 2)

#define KBP_DEV_12K_MAX_UDA_REQUESTS_PER_CYCLE          (5)

#define KBP_DEV_12K_MIN_SRAM_WIDTH_IN_BITS              (32)
#define KBP_DEV_12K_MIN_SRAM_WIDTH_IN_BYTES             (KBP_DEV_12K_MIN_SRAM_WIDTH_IN_BITS/8)
#define KBP_DEV_12K_MAX_SRAM_SB_WIDTH_IN_BITS           (256)
#define KBP_DEV_12K_MAX_SRAM_SB_WIDTH_IN_BYTES          (KBP_DEV_12K_MAX_SRAM_SB_WIDTH_IN_BITS/8)

#define KBP_DEV_12K_NUM_SRAM_SUPER_BLOCKS            (64)
#define KBP_DEV_12K_NUM_SRAM_BLOCKS_IN_SB            (8)

#define KBP_DEV_12K_SRAM_BASE_ADDR_SHIFT_NUM_BITS    (9)

#define KBP_DEV_12K_NUM_ENTRIES_PER_SRAM_BLOCK       (8192)
#define KBP_DEV_12K_TOTAL_NUM_SRAM_BLOCKS            (KBP_DEV_12K_NUM_SRAM_SUPER_BLOCKS * KBP_DEV_12K_NUM_SRAM_BLOCKS_IN_SB)
#define KBP_DEV_12K_TOTAL_NUM_SRAM_ENTRIES           (KBP_DEV_12K_TOTAL_NUM_SRAM_BLOCKS * KBP_DEV_12K_NUM_ENTRIES_PER_SRAM_BLOCK)
#define KBP_DEV_12K_NUM_SRAM_ENTRIES_PER_SB          (KBP_DEV_12K_NUM_SRAM_BLOCKS_IN_SB * KBP_DEV_12K_NUM_ENTRIES_PER_SRAM_BLOCK)
#define KBP_DEV_12K_USB_DEPTH                        (KBP_DEV_12K_NUM_ENTRIES_PER_SRAM_BLOCK)
#define KBP_DEV_12K_USB_WIDTH_IN_BITS                (256)
#define KBP_DEV_12K_USB_WIDTH_IN_BYTES               (KBP_DEV_12K_USB_WIDTH_IN_BITS / 8)

/* Processor's registers are 80 bit length */
#define KBP_DEV_12K_REG_LEN_IN_BITS                  (80)
#define KBP_DEV_12K_REG_LEN_IN_BYTES                 (KBP_DEV_12K_REG_LEN_IN_BITS / 8)

/*24-bit external memory */
#define KBP_DEV_12K_MAX_MEM_SIZE                        (0x1000000)

#define KBP_DEV_12K_FIB_MAX_PFX_LEN_IN_BITS          (160)
#define KBP_DEV_12K_FIB_MAX_PFX_LEN_IN_BYTES         (KBP_DEV_12K_FIB_MAX_PFX_LEN_IN_BITS/8)

/* index range increased from "0x7FFFFF" ~= 8.2M to ~=16M we use > 8.2M index range for 4000 rows */
#define KBP_DEV_12K_FIB_MAX_INDEX_RANGE              (0xFFFFFF)

/* Local opcode value used with Compare3 instruction */
#define KBP_DEV_12K_OPCODE_EXT_LCLOPCODE_LPM         (0x5)

/* Maximum shift value for UDA address calculations */
#define KBP_DEV_12K_INDEX_SHIFT_VALUE_MAX                       (3)

#define KBP_DEV_12K_MAX_CMP_DATA_LEN_BYTES                      (80)

/* Context Buffer */
/* Context Buffer Memory has  32k 80b locations */
#define KBP_DEV_12K_CB_DEPTH                                 (32768)

/* Maximum number of Context ids */
#define KBP_DEV_12K_MAX_NR_OF_CONTEXTS                       (KBP_DEV_12K_CB_DEPTH / 8)

/* Context Buffer Memory has data chunk size of 80 bit*/
#define KBP_DEV_12K_CB_WIDTH_IN_BITS                         (80)
#define KBP_DEV_12K_CB_WIDTH_IN_BYTES                        (KBP_DEV_12K_CB_WIDTH_IN_BITS/8)
#define KBP_DEV_12K_CB_KEYLEN                                (640)
#define KBP_DEV_12K_CB_KEYLEN_BYTES                          (KBP_DEV_12K_CB_KEYLEN/8)
#define KBP_DEV_12K_MAX_CB_WRITE_IN_BYTES                    (KBP_DEV_12K_CB_KEYLEN_BYTES)

/* Context Buffer owns memory with size 16k*80   */
#define KBP_DEV_12K_CB_MEMSIZE                               (KBP_DEV_12K_CB_DEPTH * KBP_DEV_12K_CB_WIDTH_IN_BYTES)

/*x is the result Nr within the register*/
#define KBP_DEV_12K_RESULT_REG_MATCH_ADDRESS_START_BIT(x)   ((40*x)+ 0)
#define KBP_DEV_12K_RESULT_REG_MATCH_ADDRESS_END_BIT(x)     ((40*x)+ 23)
#define KBP_DEV_12K_RESULT_REG_MATCH_FLAG_BIT_POS(x)        ((40*x)+ 39)

/*Result Block Related Macros */
#define KBP_DEV_12K_RB_NUM_RESULT_REG                           (3)
#define KBP_DEV_12K_RB_NUM_RESULTS_PER_REG                      (2)

/*LTR related macros */
#define KBP_DEV_12K_MAX_NUM_LTRS                             (128)
#define KBP_DEV_12K_ADDR_SPACE_FOR_REGS_PER_LTR                 (256)
#define KBP_DEV_12K_NUM_BITS_FOR_REG_ADDR_SPACE_PER_LTR         (8)

/*SMT related macros*/
#define KBP_DEV_12K_MAX_NUM_SMT                                 (2)
#define KBP_DEV_12K_MAX_NUM_LTR_PER_SMT                         (KBP_DEV_12K_MAX_NUM_LTRS / 2)
#define KBP_DEV_12K_MAX_NUM_PORT                                (2)
#define KBP_DEV_12K_DEFAULT_SMT_NUM                             (0)


/*Device address ranges from 0 to 7FFFFF, 23 bits*/
#define KBP_DEV_12K_MAX_NUM_DEVICE_ADDR                         (0x800000)
#define KBP_DEV_12K_ADDR_OP_TYPE_BIT_START_POS                  (25)
#define KBP_DEV_12K_NUM_ADDR_TYPES                              (4)

/* Bit posistions in 32b result value */
#define KBP_DEV_12K_CMP_RESULT_RV_BIT_POS                    (31)
#define KBP_DEV_12K_CMP_RESULT_SMF_BIT_POS                   (30)
#define KBP_DEV_12K_CMP_RESULT_RESP_FORMAT_END_BIT           (29)
#define KBP_DEV_12K_CMP_RESULT_RESP_FORMAT_START_BIT         (27)
#define KBP_DEV_12K_CMP_RESULT_DEVID_END_BIT                 (22)
#define KBP_DEV_12K_CMP_RESULT_DEVID_START_BIT               (21)
#define KBP_DEV_12K_CMP_LPM_RESULT_INDEX_END_BIT             (23)
#define KBP_DEV_12K_CMP_LPM_RESULT_INDEX_START_BIT           (0)
#define KBP_DEV_12K_CMP_RESULT_INDEX_END_BIT                 (20)
#define KBP_DEV_12K_CMP_RESULT_INDEX_START_BIT               (0)

/* Exact Match related definitions */
#define KBP_DEV_12K_EM_ENTRY_VALID_BIT_IN_ADDR               (30)
#define KBP_DEV_12K_ADDR_TYPE_BIT_IN_EM_WRITE                (25)

/* Maximum response message length for Compare instructions */
#define KBP_DEV_12K_MAX_RESP_LEN_IN_BITS                     (640)
#define KBP_DEV_12K_MAX_RESP_LEN_IN_BYTES                    (KBP_DEV_12K_MAX_RESP_LEN_IN_BITS / 8)

/* Maximum Associated Data Length */
#define KBP_DEV_12K_MAX_AD_LEN_IN_BITS                       (256)
#define KBP_DEV_12K_MAX_AD_LEN_IN_BYTES                      (KBP_DEV_12K_MAX_AD_LEN_IN_BITS / 8)

#define NLM_REG_ADDR_NETLOGIC_ADDRESS                   (0x000007FE)
#define NLM_REG_ADDR_NETLOGIC_DATA                      (0x000007FF)

#define KBP_DEV_12K_NUM_RPTS                            (4)

/* device defines ends */

/**
 * Opaque top-level device handle.
 */

struct kbp_device;

/**
 * Legacy device type definitions for existing software.
 */

enum kbp_dev_12k_dev_type {
    KBP_DEV_12K_DEVTYPE_3,              /**< 12K class of devices */
    KBP_DEV_12K_DEVTYPE_3_N,            /**< NetRoute-capable device */
    KBP_DEV_12K_DEVTYPE_3_A,            /**< 12K B0 Device capable of NetRoute and algorithmic ACL power control */

    KBP_DEV_12K_DEVTYPE_3_40M,          /**< 40Mb ACL only device */
    KBP_DEV_12K_DEVTYPE_3_N_40M,        /**< 40Mb NetRoute-capable device */
    KBP_DEV_12K_DEVTYPE_3_A_40M,        /**< 12K 40Mb Device capable of NetRoute and algorithmic ACL power control */

    KBP_DEV_12K_DEVTYPE_3_20M,          /**< 20Mb ACL only device */
    KBP_DEV_12K_DEVTYPE_3_N_20M,        /**< 20Mb NetRoute-capable device */
    KBP_DEV_12K_DEVTYPE_3_A_20M,        /**< 12K 20Mb Device capable of NetRoute and algorithmic ACL power control */
    KBP_DEV_12K_DEVTYPE_END             /**< must be the last element */
};

/**
 * MDIO definations
 */
#define KBP_DEV_12K_MDIO_WRITE_LEN_IN_BYTES (6)
#define KBP_DEV_12K_MDIO_READ_LEN_IN_BYTES (4)

/**
 * Number of KPUs in 12K.
 */
#define KBP_DEV_12K_DEV_NUM_KEYS    4


/**
 * LUT index/AD specification.
 */
struct kbp_lut_rslt_IdxADCfg {
    uint8_t m_numBytes;          /**< number of bytes to be transfered in Index/Asso-Data
                                    0 = 16Bytes AD/ 4Bytes Index, 1Bytes ... 15Bytes */
    int32_t m_IdxOrAD;          /**< Result will be either Index or Asso-Data */
};

/**
 * Device manager logging type.
 */
enum kbp_dev_12k_log_type {
    KBP_DEV_12K_SM_DUMP_REG = 0,
    KBP_DEV_12K_SM_DUMP_DBA,
    KBP_DEV_12K_SM_DUMP_UDA,
    KBP_DEV_12K_SM_DUMP_ALL,

    KBP_DEV_12K_DEV_DUMP_REG = 10,
    KBP_DEV_12K_DEV_DUMP_DBA,
    KBP_DEV_12K_DEV_DUMP_UDA,
    KBP_DEV_12K_DEV_DUMP_ALL
};

/**
 * Super-block range for DBA and UDA. The definitions
 * of super-block for DBA and UDA are different.
 */
struct kbp_dev_12k_sb_range {
    uint16_t m_stSBNr;           /**< DBA/UDA start super-block number. */
    uint16_t m_endSBNr;          /**< DBA/UDA end super-block number. */
};

/**
 * 12K search response hit/miss.
 */
enum kbp_dev_12k_miss_hit {
    KBP_DEV_12K_MISS = 0,
    KBP_DEV_12K_HIT
};

/**
 * 12K search result valid/invalid flag.
 */
enum kbp_dev_12k_resultvalid{
    KBP_DEV_12K_RESULT_INVALID = 0,
    KBP_DEV_12K_RESULT_VALID
};

/**
 * 12K search response type with/without associated data.
 */
enum kbp_dev_12k_resp_type {
    KBP_DEV_12K_INDEX_AND_NO_AD,
    KBP_DEV_12K_INDEX_AND_32B_AD,
    KBP_DEV_12K_INDEX_AND_64B_AD,
    KBP_DEV_12K_INDEX_AND_128B_AD,
    KBP_DEV_12K_INDEX_AND_256B_AD
};

/**
 * Enumerated type for enable/disable bitfields.
 */
enum kbp_dev_12k_disable_enable {
    KBP_DEV_12K_DISABLE = 0,
    KBP_DEV_12K_ENABLE
};

/**
 * Enumerated type for validate/invalidate entry.
 */
enum kbp_dev_12k_validate_invalidate {
    KBP_DEV_12K_INVALIDATE = 0,   /**< Invalidate */
    KBP_DEV_12K_VALIDATE          /**< Validate */
};

/**
 * Enumerated type for AB entries write modes. Data can be written in DM or XY mode.
 */
enum kbp_dev_12k_write_mode {
    KBP_DEV_12K_DM = 0,  /**< Write is ad data/mask format */
    KBP_DEV_12K_XY       /**< Write is in X/Y format */
};

/**
 * 12K device ID. A maximum of four devices is supported for cascading in a channel.
 */
enum kbp_dev_12k_dev_id {
    KBP_DEV_12K_DEV_ID0 = 0,
    KBP_DEV_12K_DEV_ID1,
    KBP_DEV_12K_DEV_ID2,
    KBP_DEV_12K_DEV_ID3
};

/**
 * 12K Global Register Definitions.
 */
enum kbp_dev_12k_global_reg_type {
    KBP_DEV_12K_DEVICE_ID_REG,       /**< Read-only register. */
    KBP_DEV_12K_DEVICE_CONFIG_REG,

    KBP_DEV_12K_SCRATCH_PAD0_REG,
    KBP_DEV_12K_SCRATCH_PAD1_REG,

    KBP_DEV_12K_RESULT0_REG,         /**< Read-only register. */
    KBP_DEV_12K_RESULT1_REG,         /**< Read-only register. */
    KBP_DEV_12K_RESULT2_REG,         /**< Read-only register. */

    KBP_DEV_12K_DEVICE_STATUS_REG,

    KBP_DEV_12K_SOFT_SCAN_WRITE_REG,
    KBP_DEV_12K_SOFT_ERROR_FIFO_REG,

    KBP_DEV_12K_LPT_ENABLE_REG,

    KBP_DEV_12K_UDA_SOFT_ERROR_COUNT_REG_PORT0,
    KBP_DEV_12K_UDA_SOFT_ERROR_COUNT_REG_PORT1,
    KBP_DEV_12K_UDA_SOFT_ERROR_FIFO_REG_PORT0,
    KBP_DEV_12K_UDA_SOFT_ERROR_FIFO_REG_PORT1,

    KBP_DEV_12K_UDA_CONFIG_REG,

    KBP_DEV_12K_ERROR_STATUS_REG_PORT_0,     /**< Read-only register. Reading of this register clears the set bits. */
    KBP_DEV_12K_ERROR_STATUS_REG_PORT_1,

    KBP_DEV_12K_INTERRUPT_MASK_REG_PORT_0,   /**< Write register. Writing of this register clears the set bits. */
    KBP_DEV_12K_INTERRUPT_MASK_REG_PORT_1,

    KBP_DEV_12K_GLOBALREG_END        /**< Must be the last element */
};

/**
 *   The device-identification register contains information regarding database size
 *   of the device and major and minor revision number of the device. This is a
 *   read-only register.
 */
struct kbp_dev_12k_id_reg {
    uint8_t m_databaseSize;      /**< Specifies the size of the device. Can have a value of 2 (512K) or 3 (1024K). */
    uint32_t m_jtag_id;          /**< 32-bit JTAG identification register. */
};

/**
 *   This structure encapsulates the Error Status register.
 *   The error-status register should be read to determine the type of error that has occurred.
 *   Errors are reported via an interrupt signal on the GIO_L pin of the device.
 *   The same structure can be used to write to the Error Status Mask Register
 *   to mask off the specified errors that are reported. For each field, a value of 0 disables
 *   error reporting while a value of 1 enables error reporting.
 *   Note: The Error Status register is a read-only register.
 */
struct kbp_dev_12k_err_status_reg {
    /* for Mask register only, all bits are  R/W */
    int32_t m_gioL0Enable;      /**< 79: R/W */
    int32_t m_gioL1Enable;      /**< 0: R/W */

    /* Interface errors */
    int32_t m_interfaceErr;     /**< 65: R/clear */
    int32_t m_casInterfaceErr;  /**< 64: R/clear */
    int32_t m_CRxBnk0FifoOverflowErr;   /**< 63: R/clear */
    int32_t m_CRxBnk1FifoOverflowErr;   /**< 62: R/clear */
    int32_t m_RxBnk0FifoOverflowErr;    /**< 61: R/clear */
    int32_t m_RxBnk1FifoOverflowErr;    /**< 60: R/clear */

    /* Packet errors */
    int32_t m_PCTMemParityErr;  /**< 43: R/clear */
    int32_t m_UDFifoParityErr;  /**< 42: R/clear */
    int32_t m_seqIdMisMatchErr; /**< 41: R/clear */

    int32_t m_RBFifoParityErr;  /**< 40: R/clear */
    int32_t m_IBPipeRegFileParityErr;   /**< 39: R/clear */
    int32_t m_ctxBuffParityErr; /**< 38: R/clear */
    int32_t m_ltrParityErr;     /**< 36: R/clear */
    int32_t m_devIdMisMatchErr; /**< 35: R/clear */
    int32_t m_illigalInstErr;   /**< 34: R/clear */
    int32_t m_chnlNoErrOnCasRply;       /**< 33: R/clear */
    int32_t m_protocoErrOnCasRply;      /**< 32: R/clear */

    int32_t m_instBurstErrOnCasRply;    /**< 31: R/clear */
    int32_t m_rxNMACFifoParityCasErr;   /**< 30: R/clear */
    int32_t m_frammingErrOnCsRply;      /**< 29: R/clear */
    int32_t m_burstMaxErrOnCxRply;      /**< 28: R/clear */
    int32_t m_eopErrOnCasRply;  /**< 27: R/clear */
    int32_t m_sopErrOnCasRply;  /**< 26: R/clear */
    int32_t m_crc24ErrOnasCasRply;      /**< 25: R/clear */
    int32_t m_chnlNumErr;       /**< 24: R/clear */
    int32_t m_protocolErr;      /**< 23: R/clear */
    int32_t m_instBurstErr;     /**< 22: R/clear */
    int32_t m_rxNMACFifoParityErr;      /**< 21: R/clear */
    int32_t m_framingErrOnRqt;  /**< 20: R/clear */
    int32_t m_burstMaxErr;      /**< 19: R/clear */
    int32_t m_eopErr;           /**< 18: R/clear */
    int32_t m_sopErr;           /**< 17: R/clear */
    int32_t m_crc24Err;         /**< 16: R/clear */

    /* Device errors specific to port */
    int32_t m_UDASoftErrFifoOverflow;   /**< 10: W/Clear */
    int32_t m_UDASoftErrFifoFull;       /**< 9: R */
    int32_t m_UDASoftErr;               /**< 8: R */
    int32_t m_RBFifoOverflow;           /**< 7: R */
    int32_t m_ADVSoftErrFifoOverflow;   /**< 6: W/Clear */
    int32_t m_ADVSoftErrFifoFull;       /**< 5: R/Clear */
    int32_t m_ADVsoftErr;               /**< 4: R/Clear */
    int32_t m_parityScanFifoOverflow;   /**< 3: W/Clear */
    int32_t m_dbSoftErrFifoFull;        /**< 2: R */
    int32_t m_dbSoftErr;                /**< 1: R */
} ;

/**
 * Structure for advanced-feature soft-error register.
 *   Note: The advanced-feature soft-error register is a read-only register
 */
struct kbp_dev_12k_advanced_soft_err_reg {
    uint16_t m_cbParityErrAddr;  /**< Indicates the location of Ctx Buffer with parity error. */
    uint16_t m_sahasraParityErrAddr0;    /**< Indicates the location of Sahasra Engine parity error 0. */
    uint16_t m_sahasraParityErrAddr1;    /**< Indicates the location of Sahasra Engine parity error 1. */
    uint16_t m_ltrParityErrAddr; /**< Indicates the location of LTR parity error.
                                    Bits[10:5] indicate the LTR number
                                    and Bits[4:0] indicate the LTR register type.
                                    Example: If the value of this field is b'0111100004??,
                                    a parity error has occurred for LTR #15,
                                    and Reg Type KBP_DEV_12K_PARALLEL_SEARCH_1_LTR
                                    Note: For compare operations, LTR Reg Type is not specified. */

};

/**
 *   Structure for database soft-parity-error FIFO register.
 */
struct kbp_dev_12k_db_soft_err_scan_reg {
    uint32_t m_softScanIntvl_hi; /**< 59:12 out of 48b (47:32) soft scan interval value. */
    uint32_t m_softScanIntvl_lo; /**<                  (31: 0) soft scan interval value. */
    uint32_t m_softScanAddr;     /**< 11: 0 soft scan address. */
};

/**
 *   Structure for UDA soft (ECC) error counter register.
 *   Contains the values for 32 error detections and corrections in UDA memory, also
 *   gives a maximum of 32 error locations stored in FIFO.
 */
struct kbp_dev_12k_uda_soft_err_counter_reg {
    uint32_t m_udaEccErrLoc;             /**< 38:32 (7'b)   total 32 locations. */
    uint32_t m_udaEccErrCorrectCnt;      /**< 31:16 (16'b)  ECC error-correction count. */
    uint32_t m_udaEccErrDetectCnt;       /**< 15:0  (16'b)  ECC error-detection count. */
};

/**
 *   Structure for UDA soft (ECC) Error FIFO register.
 *   Contains the details of ECC detections and corrections in UDA memory.
 */
struct kbp_dev_12k_uda_soft_err_fifo_reg {
    uint32_t m_udaEccEntryValid; /**< 31: 1 = UDA ECC error address entry valid */
    uint32_t m_udaEccErrAddr;    /**< 30:4:  (27'b)  ECC error-detection count. */
    int32_t m_2bMultiErr;        /**< 3: More than 3-bit correctable error in cycle. */
    int32_t m_2bErr;             /**< 2: 2-bit correctable error */
    int32_t m_1bMultiErr;        /**< 1: More than 1-bit correctable error in cycle. */
    int32_t m_1bErr;             /**< 0:  1-bit correctable error. */
} ;

/**
 * Structure for database soft-parity-error FIFO register.
 */
struct kbp_dev_12k_db_soft_err_fifo_reg {
    uint32_t m_errorAddr;       /**< 20:0 Address of the database entry with parity error. This Field is read-only. */
    int32_t m_pErrorX;          /**< 21:  If set to 1, indicates that the error is in the X part of the entry.
                                   This field is read-only. */
    int32_t m_pErrorY;          /**< 22:  If set to 1, indicates that the error is in the Y part of the entry.
                                   This field is read-only. */
    int32_t m_errorAddrValid;   /**< 23:  If set to 1, indicates this is a valid error address.
                                   If set to 0, indicates this FIFO is empty.
                                   This field is read-only. */
    int32_t m_eraseFifoEntry;   /**< 40:  Writing 1 to this field will erase the current entry.
                                   and advance the pointer to next FIFO entry.
                                   This field is write-only. */
    int32_t m_eraseFifo;        /**< 41:  Writing 1 to this field erases all the entries in the FIFO.
                                   This field is write-only. */
};

/**
 *   The device-configuration register stores basic configuration attributes of the
 *   device such as low-power-mode status, soft-parity-error mode, range-matching-engine enable, and so on.
 */
struct kbp_dev_12k_db_config_reg {
    uint8_t m_port1CtxIDShift;   /**< 50:48 */
    uint16_t m_ACtoBankMapping;  /**< 47:32 */
    int32_t m_supressIdxOnAD;    /**< 30  if set, index will be suppressed.
                                    Thus if ad+index is configured, only AD is returned. */
    enum kbp_dev_12k_disable_enable m_rangeEnable;  /**< 28 */
    enum kbp_dev_12k_disable_enable m_nwByteOrderEnable;    /**< 27: 0 = NNBO mode; 1 = NBO mode. */
    enum kbp_dev_12k_disable_enable m_port1Enable;  /**< 26 */
    enum kbp_dev_12k_disable_enable m_port0Enable;  /**< 25 */
    enum kbp_dev_12k_portmode m_dualPortMode; /**< 24 */
    enum kbp_dev_12k_smt_mode m_dualBankMode;  /**< 23 */
    uint8_t m_CBConfig;         /**< 22:15 */

    enum kbp_dev_12k_disable_enable m_dbParityErrEntryInvalidate;   /**< 7 */
    enum kbp_dev_12k_disable_enable m_softErrorScanEnable;  /**< 6: */

    enum kbp_dev_12k_disable_enable m_port0ErrIntrEnblForPrt1;      /**< 5: 0 disables port-0 errors from generating
                                                                       interrupts on port 1; 1 enables them. */
    enum kbp_dev_12k_disable_enable m_port1ErrIntrEnblForPrt0;      /**< 4: 0 disables port-1 errors from generating
                                                                       interrupts on port 0; 1 enables them. */

    enum kbp_dev_12k_disable_enable m_MCSegCasEnable;       /**< 3: 0 disables; 1 enables segment cascade in MC. */
    int32_t m_lastDevice;       /**< 1: 0 means not last device; 1 means last device. */
    int32_t m_firstDevice;      /**< 0:  0 means not first device; 1 means first device. */
};

/*
 *   Structure for scratch-pad registers 0 and 1.
 */
struct kbp_dev_12k_scratch_pad_reg {
    uint8_t m_data[KBP_DEV_12K_REG_LEN_IN_BYTES]; /**< Scratch data. */
};

/**
 *   Structure for result registers 0 and 1.
 *   It stores the result of the latest compare instruction done on the device.
 *   The result registers are read-only registers.
 */
struct kbp_dev_12k_result_reg {
    enum kbp_dev_12k_miss_hit m_hitOrMiss[KBP_DEV_12K_NUM_PARALLEL_SEARCHES / 2]; /**< Specifies hit or miss status for the search */
    uint32_t m_hitAddress[KBP_DEV_12K_NUM_PARALLEL_SEARCHES / 2];     /**< For hit status, contains hit address for the search */
};

/**
 *   Structure for UDA configuration register to enable/disable super-blocks (SBs).
 */
struct kbp_dev_12k_uda_config_reg {
    enum kbp_dev_12k_disable_enable m_uSBEnable[KBP_DEV_12K_NUM_SRAM_SUPER_BLOCKS / 4]; /**< SB enable/disable bitmap. */
};

/**
 *   Structure for device-status register to check the UDA SB status.
 *   This register read can be done after writing the UDA configuration register, to check whether the
 *   status of SBs are enabled or disabled.
 */
struct kbp_dev_12k_status_reg {
    enum kbp_dev_12k_disable_enable m_uSBEnable[KBP_DEV_12K_NUM_SRAM_SUPER_BLOCKS / 4]; /**< SB enable/disable status. */
};

/**
 *   Structure definition for accessing the context buffer as a register.
 */
struct kbp_dev_ctx_buffer_reg {
    uint8_t m_data[KBP_DEV_12K_REG_LEN_IN_BYTES];     /**< 80-bit CB register data. */
};

/**
 *   Structure definition for accessing Range-Global register.
 */
struct kbp_dev_12k_range_reg {
    uint8_t m_data[KBP_DEV_12K_REG_LEN_IN_BYTES];
};

/**
 *   LTR Register Types.
 */
enum kbp_dev_12k_ltr_reg_type {
    KBP_DEV_12K_BLOCK_SELECT_0_LTR,
    KBP_DEV_12K_BLOCK_SELECT_1_LTR,
    KBP_DEV_12K_BLOCK_SELECT_2_LTR,
    KBP_DEV_12K_BLOCK_SELECT_3_LTR,

    KBP_DEV_12K_PARALLEL_SEARCH_0_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_1_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_2_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_3_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_4_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_5_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_6_LTR,
    KBP_DEV_12K_PARALLEL_SEARCH_7_LTR,

    KBP_DEV_12K_SUPER_BLK_KEY_MAP_LTR,

    KBP_DEV_12K_EXT_CAPABILITY_REG_0_LTR,
    KBP_DEV_12K_EXT_CAPABILITY_REG_1_LTR,

    KBP_DEV_12K_KEY_0_KCR_0_LTR,
    KBP_DEV_12K_KEY_0_KCR_1_LTR,
    KBP_DEV_12K_KEY_1_KCR_0_LTR,
    KBP_DEV_12K_KEY_1_KCR_1_LTR,
    KBP_DEV_12K_KEY_2_KCR_0_LTR,
    KBP_DEV_12K_KEY_2_KCR_1_LTR,
    KBP_DEV_12K_KEY_3_KCR_0_LTR,
    KBP_DEV_12K_KEY_3_KCR_1_LTR,

    KBP_DEV_12K_OPCODE_EXT_LTR,

    KBP_DEV_12K_RANGE_INSERTION_0_LTR,
    KBP_DEV_12K_RANGE_INSERTION_1_LTR,

    KBP_DEV_12K_SS_LTR,              /**< 11K-specific. */

    KBP_DEV_12K_REG_END          /**< Must be the last element. */
};

/**
 *   Structure for block-select registers 0, 1, 2, and 3. Each block-select register indicates whether
 *   the corresponding block is disabled or enabled for search operations.
 */
struct kbp_dev_12k_blk_select_reg {
    enum kbp_dev_12k_disable_enable m_blkEnable[KBP_DEV_12K_NUM_ARRAY_BLOCKS / 4];
};

/**
 *   Structure for Super-Block-to-Key mapping register .
 *   This register indicates which super-block is mapped to
 *   which key.
 */
struct kbp_dev_12k_super_blk_key_map_reg {
    enum kbp_dev_12k_key_type m_keyNum[KBP_DEV_12K_NUM_SUPER_BLOCKS];
};

/**
 *   Structure for parallel-search registers 0,1,2 and 3.
 *   These registers indicate which array block is mapped to
 *   which parallel search.
 */
struct kbp_dev_12k_parallel_srch_reg {
    enum kbp_dev_12k_parallel_srch_type m_psNum[KBP_DEV_12K_NUM_ARRAY_BLOCKS / 8];

};

/**
 * Enumerated type that specifies range-encoding types.
 */
enum kbp_dev_12k_range_encoding_type {
    KBP_DEV_12K_3BIT_RANGE_ENCODING,
    KBP_DEV_12K_2BIT_RANGE_ENCODING,
    KBP_DEV_12K_NO_RANGE_ENCODING
};

/**
 * Enumerated type that specifies the number of bytes of range-encoding value to be used.
 */
enum kbp_dev_12k_range_encoded_value_bytes {
    KBP_DEV_12K_1BYTE_RANGE_ENCODED_VALUE,
    KBP_DEV_12K_2BYTE_RANGE_ENCODED_VALUE,
    KBP_DEV_12K_3BYTE_RANGE_ENCODED_VALUE,
    KBP_DEV_12K_4BYTE_RANGE_ENCODED_VALUE
};

/**
 * Structure for Range Insertion 0 and Range Insertion 1 registers.
 * Contains information about the type of encoding to be used:
 * the location of Range Encoding Insertion in various keys, and the number of bytes of range-encoded value
 * to be inserted.
 */
struct kbp_dev_12k_range_insertion0_reg {
    enum kbp_dev_12k_range_encoding_type m_rangeAEncodingType;       /**< Specifies type of range encoding to be used for Range A. */
    enum kbp_dev_12k_range_encoding_type m_rangeBEncodingType;       /**< Specifies type of range encoding to be used for Range B. */
    enum kbp_dev_12k_range_encoded_value_bytes m_rangeAEncodedBytes;  /**< Specifies the number of bytes of Range-A encoding to be
                                                                         inserted into the key(s). Supported values are 0 to 3(1 byte to 4 bytes). */
    enum kbp_dev_12k_range_encoded_value_bytes m_rangeBEncodedBytes;  /**< Specifies the number of bytes of Range-B encoding to be
                                                                         inserted into the key(s). Supported values are 0 to 3(1 byte to 4 bytes). */

    uint8_t m_rangeAInsertStartByte[KBP_DEV_12K_NUM_KEYS];   /**< Specifies the start byte where the Range-A encoding needs to be inserted
                                                                in each key. Supported values are 0 to 79.
                                                                A value of KBP_DEV_12K_RANGE_DO_NOT_INSERT means "Do not insert". */
    uint8_t m_rangeBInsertStartByte[KBP_DEV_12K_NUM_KEYS];   /**< Specifies the start byte where the Range-B encoding needs to be inserted
                                                                in each key. Supported values are 0 to 79.
                                                                A value of KBP_DEV_12K_RANGE_DO_NOT_INSERT means "Do not insert". */
};

/**
 * Structure for Range-Insertion 0 and Range-Insertion 1 registers.
 * Contains information about type of encoding to be used:
 * the location of Range Encoding Insertion in various keys, and the number of bytes of range-encoded value
 * to be inserted.
 */
struct kbp_dev_12k_range_insertion1_reg {
    enum kbp_dev_12k_range_encoding_type m_rangeCEncodingType;       /**< Specifies type of range encoding to be used for Range C. */
    enum kbp_dev_12k_range_encoding_type m_rangeDEncodingType;       /**< Specifies type of range encoding to be used for Range D. */
    enum kbp_dev_12k_range_encoded_value_bytes m_rangeCEncodedBytes;  /**< Specifies number of bytes of Range-C encoding to be
                                                                         inserted in to the key(s). Supported values are 0 to 3(1 byte to 4 bytes). */
    enum kbp_dev_12k_range_encoded_value_bytes m_rangeDEncodedBytes;  /**< Specifies number of bytes of Range-D encoding to be
                                                                         inserted in to the key(s). Supported values are 0 to 3(1 byte to 4 bytes). */

    uint8_t m_rangeCInsertStartByte[KBP_DEV_12K_NUM_KEYS];   /**< Specifies the start byte where the Range-C encoding needs to be inserted
                                                                in each key. Supported values are 0 to 79.
                                                                A value of KBP_DEV_12K_RANGE_DO_NOT_INSERT means Do Not Insert */
    uint8_t m_rangeDInsertStartByte[KBP_DEV_12K_NUM_KEYS];   /**< Specifies the start byte where the Range D Encoding needs to be inserted
                                                                in each key; Supported values 0 - 79;
                                                                Value of KBP_DEV_12K_RANGE_DO_NOT_INSERT means "Do not insert". */
};

/**
 *   The Key-Construction register stores information about how the individual parallel search keys
 *   need to be generated from the master(compare) key passed with the compare instruction(s).
 */
struct kbp_dev_12k_key_construct_reg {
    uint8_t m_startByteLoc[KBP_DEV_12K_NUM_OF_SEGMENTS_PER_KCR];      /**< Specifies the start byte of each segment in the compare key.
                                                                         Valid values  are 0 to 79. */
    uint8_t m_numOfBytes[KBP_DEV_12K_NUM_OF_SEGMENTS_PER_KCR];        /**< Specifies the number of bytes comprising each segment.
                                                                         Valid values are 1 to 16. A value of zero indicates that there
                                                                         are no more valid segments and the device manager can ignore
                                                                         the following segments. */
    uint8_t m_isZeroFill[KBP_DEV_12K_NUM_OF_SEGMENTS_PER_KCR];        /**< Specifies if the key should be filled with zeros. */
};


/**
 * Extended Capability-0 Register.
 */
struct kbp_dev_12k_ext_cap0_reg {
    uint8_t m_bmrSelect[KBP_DEV_12K_NUM_PARALLEL_SEARCHES];   /**< Specifies the Block-Mask Register (BMR) number to be used for each parallel search.
                                                                 Valid values are 0 to 4 and KBP_DEV_12K_NO_MASK_BMR_NUM. */

    uint8_t m_rangeAExtractStartByte;    /**< Specifies the start byte in the compare key from which the 16-bit range-A value,
                                            to be used for encoding, needs to be picked. Supported values are 0 to 78. */
    uint8_t m_rangeBExtractStartByte;    /**< Specifies the start byte in the compare key from which the 16-bit range-B value,
                                            to be used for encoding, needs to be picked. Supported values are 0 to 78. */
    uint8_t m_rangeCExtractStartByte;    /**< Specifies the start byte in the compare key from which the 16-bit range-C value,
                                            to be used for encoding, needs to be picked. Supported values are 0 to 78. */
    uint8_t m_rangeDExtractStartByte;    /**< Specifies the start byte in the compare key from which the 16-bit range-D value,
                                            to be used for encoding, needs to be picked. Supported values are 0 to 78. */
    uint8_t m_numOfValidSrchRslts;       /**< Specifies the number of search results that are valid:
                                            0 - All four search results are valid.
                                            1 - Only one search result is valid
                                            2 - Only two search results are valid
                                            3 - Only three search results are valid */

    uint8_t m_enbADResolution;   /**< For revision-B Only. Used by enhanced ACL Power Control. */
};

/**
 * Generic register definition.
 */

struct kbp_dev_12k_general_reg {
    uint8_t m_data[KBP_DEV_12K_REG_LEN_IN_BYTES];
};

/*
 * Result-type enumerated types.
 */
enum kbp_dev_12k_result_type {
    KBP_DEV_12K_INDEX_ONLY,          /**< Return only the hit index. */
    KBP_DEV_12K_INDEX_AND_AD         /**< Return associated data and hit index. */
};

/*
 * Associated data lengths.
 */
enum kbp_dev_12k_ad_length {
    KBP_DEV_12K_ADLEN_32B,
    KBP_DEV_12K_ADLEN_64B,
    KBP_DEV_12K_ADLEN_128B,
    KBP_DEV_12K_ADLEN_256B
};

/**
 * Hit-index type: DBA-hit index or translated address.
 */
enum kbp_dev_12k_index_type {
    KBP_DEV_12K_DBA_INDEX,
    KBP_DEV_12K_TRANSLATED_ADDR
};

/**
 * OpCodeExt Register.
 */
struct kbp_dev_12k_opcode_ext_reg {
    enum kbp_dev_12k_result_type m_resultType[KBP_DEV_12K_NUM_PARALLEL_SEARCHES];/**< Just index or index + AD. */
    enum kbp_dev_12k_ad_length m_ADLen[KBP_DEV_12K_NUM_PARALLEL_SEARCHES];       /**< Associated data length. */
    enum kbp_dev_12k_index_type index_type[KBP_DEV_12K_NUM_PARALLEL_SEARCHES];   /**< Should index be translated */
    uint32_t m_lclOpCode;
};

/**
 *   Block Register Set.
 */
enum kbp_dev_12k_block_reg_type {
    KBP_DEV_12K_BLOCK_CONFIG_REG,
    KBP_DEV_12K_BLOCK_MASK_0_0_REG,  /**< BMR 0, segment[79:0]. */
    KBP_DEV_12K_BLOCK_MASK_0_1_REG,  /**< BMR 0, segment[159:80]. */
    KBP_DEV_12K_BLOCK_MASK_0_2_REG,  /**< BMR 0, segment[239:160].  */
    KBP_DEV_12K_BLOCK_MASK_0_3_REG,  /**< BMR 0, segment[319:240]. */

    KBP_DEV_12K_BLOCK_MASK_1_0_REG,  /**< BMR 1, segment[79:0].  */
    KBP_DEV_12K_BLOCK_MASK_1_1_REG,  /**< BMR 1, segment[159:80].  */
    KBP_DEV_12K_BLOCK_MASK_1_2_REG,  /**< BMR 1, segment[239:160].  */
    KBP_DEV_12K_BLOCK_MASK_1_3_REG,  /**< BMR 1, segment[319:240].  */

    KBP_DEV_12K_BLOCK_MASK_2_0_REG,
    KBP_DEV_12K_BLOCK_MASK_2_1_REG,
    KBP_DEV_12K_BLOCK_MASK_2_2_REG,
    KBP_DEV_12K_BLOCK_MASK_2_3_REG,

    KBP_DEV_12K_BLOCK_MASK_3_0_REG,
    KBP_DEV_12K_BLOCK_MASK_3_1_REG,
    KBP_DEV_12K_BLOCK_MASK_3_2_REG,
    KBP_DEV_12K_BLOCK_MASK_3_3_REG,

    KBP_DEV_12K_BLOCK_MASK_4_0_REG,
    KBP_DEV_12K_BLOCK_MASK_4_1_REG,
    KBP_DEV_12K_BLOCK_MASK_4_2_REG,
    KBP_DEV_12K_BLOCK_MASK_4_3_REG,

    KBP_DEV_12K_BLOCK_REG_END        /**< Must be the last element. */
};

/**
 * Enumerated type for block widths.
 */
enum kbp_dev_12k_block_width {
    KBP_DEV_12K_WIDTH_80,
    KBP_DEV_12K_WIDTH_160,
    KBP_DEV_12K_WIDTH_320,
    KBP_DEV_12K_WIDTH_640
};

/**
 * Enumerated type for shift direction.
 */
enum kbp_dev_12k_shift_dir {
    KBP_DEV_12K_SHIFT_RIGHT = 0,
    KBP_DEV_12K_SHIFT_LEFT
};

/**
 * Enumerated type for shift count.
 */
enum kbp_dev_12k_shift_count {
    KBP_DEV_12K_SHIFT_CNT_0 = 0,
    KBP_DEV_12K_SHIFT_CNT_1,
    KBP_DEV_12K_SHIFT_CNT_2,
    KBP_DEV_12K_SHIFT_CNT_3
};

/**
 * Block configuration register stores information about block-enable status
 *   and block width. There is only one BCR per array block.
 */
struct kbp_dev_12k_block_config_reg {
    enum kbp_dev_12k_disable_enable m_blockEnable;  /**< Specifies whether the block is enabled or disabled. */
    enum kbp_dev_12k_block_width m_blockWidth;      /**< Specifies the width of the block. */
    enum kbp_dev_12k_shift_dir m_shiftDir;          /**< 0 for shift right, 1 for shift left */
    uint32_t m_baseAddr;
    enum kbp_dev_12k_shift_count m_shiftCount;      /**< 0 for no shift, 1 to shift one bit, 2 to shift two bits, and 3 to shift three bits. */
};

/**
 * Block mask register stores mask bits that mask specified bits of the database from compare operations.
 *   Each block can have 5 BMRs, where each BMR has four 80-bit segments.
 *   Segment 0 -- Used to mask bits[79:0].
 *   Segment 1 -- Used to mask bits[159:80].
 *   Segment 2 -- Used to mask bits[239:160].
 *   Segment 3 -- Used to mask bits[319:240].
 */
struct kbp_dev_12k_block_mask_reg {
    uint8_t m_mask[KBP_DEV_12K_REG_LEN_IN_BYTES];
};


/**
 * Structure for exact-match write/read.
 */
struct kbp_dev_12k_em_entry{
    uint8_t m_data[KBP_DEV_12K_EM_RECORD_WIDTH_IN_BYTES]; /**< Up to 64 bits of EM data. */
    uint8_t m_vbit;              /**< For a read operation, specifies whether the entry is valid or deleted. */
};

/**
 * enum for parity injection type
 */
 enum kbp_dev_12k_parity_inject_type {
    KBP_DEV_12K_DISABLE_ERR_INJECT = 0,

    KBP_DEV_12K_DBA_ERR_X = 1,    /* for DBA and Advance DBA x row*/
    KBP_DEV_12K_DBA_ERR_Y = 2,    /* for DBA and Advance DBA y row */
    KBP_DEV_12K_DBA_ERR_BOTH = 4, /* for both X and Y rows */
    KBP_DEV_12K_DBA_ERR_END
};

/**
 * Compare instruction type.
 */
enum kbp_dev_12k_cb_inst_type {
    KBP_DEV_12K_CB_INST_CMP1,        /**< Context buffer (CB) write-and-compare 1. */
    KBP_DEV_12K_CB_INST_CMP2,        /**< CB write-and-compare 2. */
    KBP_DEV_12K_CB_INST_LPM,         /**< CB write-and-LPM. */
    KBP_DEV_12K_CB_INST_NONE         /**< This does not represent any instruction and is used for marking the end of the enum. */
};

/**
 *   Structure that contains the CB Data passed with CB Write, Compare-1, and Compare-2 operations.
 */
struct kbp_dev_12k_ctx_buffer_info {
    uint16_t m_cbStartAddr;      /**< Specifies the CB Address where the data is to be written.
                                    For cmp operations, it also specifies the 40-bit segment of
                                    CB memory used for the compare key. */
    uint8_t m_datalen;           /**< Specifies the amount of data in terms of bytes to be written to CB memory. */
    uint8_t m_data[KBP_DEV_12K_CB_KEYLEN_BYTES];      /**< A maximum of 640 bits (80 bytes) of CB data can be written. */
};

/**
 * Structure used for performing two compares on both SMTs simultaneously.
 */
struct kbp_dev_12k_cb_write_cmp_param {
    enum kbp_dev_12k_cb_inst_type m_cbInstType0;     /**<  Instruction type for SMT-0. */
    enum kbp_dev_12k_cb_inst_type m_cbInstType1;     /**<  Instruction type for SMT-1. */
    uint8_t m_ltrNum0;                  /**<  LTR number for SMT-0 compare. */
    uint8_t m_ltrNum1;                  /**<  LTR number for SMT-1 compare. */
    struct kbp_dev_12k_ctx_buffer_info m_cbData0;      /**<  Context-buffer information for SMT-0 compare. */
    struct kbp_dev_12k_ctx_buffer_info m_cbData1;      /**<  Context-buffer information for SMT-1 compare. */
};

/* Shadow Memory definitions */
/**
 * Global registers.
 */
struct kbp_dev_12k_shadowglobal {
    struct kbp_dev_12k_db_config_reg m_devConfig;
    struct kbp_dev_12k_uda_config_reg m_devUDAConfig;
} ;

/**
 * LTR registers.
 */
struct kbp_dev_12k_shadow_ltr {
    struct kbp_dev_12k_blk_select_reg m_blockSelect[KBP_DEV_12K_NUM_ARRAY_BLOCKS / 64];
    struct kbp_dev_12k_super_blk_key_map_reg m_superBlkKeyMap;
    struct kbp_dev_12k_parallel_srch_reg m_parallelSrch[KBP_DEV_12K_NUM_ARRAY_BLOCKS / 32];
    struct kbp_dev_12k_key_construct_reg m_keyConstruct[KBP_DEV_12K_NUM_KEYS * KBP_DEV_12K_LTR_NUM_OF_KCR_PER_KPU];
    struct kbp_dev_12k_ext_cap0_reg m_extCap0; /* m_miscelleneous */
    struct kbp_dev_12k_opcode_ext_reg m_opCodeExt;
    struct kbp_dev_12k_general_reg m_internalReg1;
    struct kbp_dev_12k_range_insertion0_reg m_rangeInsert0;
    struct kbp_dev_12k_range_insertion1_reg m_rangeInsert1;
} ;

/**
 * Contents of rows within an AB
 */
struct kbp_dev_12k_ab {
    uint8_t m_x[KBP_DEV_12K_BYTES_IN_AB];     /**< Entry data in X format */
    uint8_t m_y[KBP_DEV_12K_BYTES_IN_AB];     /**< Entry mask in Y format */
    uint8_t m_ev[KBP_DEV_12K_AB_DEPTH / 8];   /**< Entry valid bit */
};

/**
 * Contents of Array Block.
 */
struct kbp_dev_12k_shadow_ab {
    struct kbp_dev_12k_block_config_reg m_blkConfig;
    struct kbp_dev_12k_block_mask_reg m_bmr[KBP_DEV_12K_NUM_BMRS_PER_AB][KBP_DEV_12K_NUM_80BIT_SEGMENTS_PER_BMR];
    struct kbp_dev_12k_ab *m_ab;
};

struct kbp_dev_12k_shadow_row {
    uint8_t m_data[KBP_DEV_12K_USB_WIDTH_IN_BYTES];
};

/**
 * UDA Super block
 */
struct kbp_dev_12k_shadow_usb {
    struct kbp_dev_12k_shadow_row m_row[KBP_DEV_12K_USB_DEPTH];
};


/**
 * Shadow chip structure - contains everything as actual chip except global registers and range registers.
 */
struct kbp_dev_12k_shadowdevice {
    struct kbp_dev_12k_shadow_ltr *m_ltr;       /**<  Pointer to an array of "KBP_DEV_12K_MAX_NUM_LTRS" struct kbp_dev_12k_shadow_ltr structures. */
    struct kbp_dev_12k_shadow_ab *m_arrayBlock; /**<  Pointer to an array of "KBP_DEV_12K_NUM_ARRAY_BLOCKS" struct kbp_dev_12k_shadow_ab structures. */
    struct kbp_dev_12k_shadow_usb *m_usb;       /**<  Pointer to UDA */
    struct kbp_dev_12k_range_reg *m_rangeReg;   /**<  Pointer to range registers. */
    struct kbp_dev_12k_shadowglobal *m_global;  /**<  Pointer to struct kbp_dev_12k_shadowglobal structure. */
};

/**
 * Function that helps the application or device manager to access a shadow device.
 *
 * @param device Valid KBP device handle.
 * @param devNum The device number for primary and cascaded KBPs.
 *
 * @retval shadow Device memory.
 * @retval NULL on error.
 */

struct kbp_dev_12k_shadowdevice *kbp_dm_12k_get_shadow_memory(struct kbp_device *device, uint8_t devNum);

/**
 *   Resets all the devices in cascade to have initial values.
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_reset_devices(struct kbp_device *device);

/**
 *   Reads any global register, depending upon the register type, and specified address
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param regType valid global register type
 * @param o_data array of 10B which holds the read data (Global register structure pointer as output)
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_global_reg_read(struct kbp_device *device, uint8_t devNum,
                                      enum kbp_dev_12k_global_reg_type regType,
                                      void *o_data);


/**
 *   Writes any global register, depending upon the register type, and specified address
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param regType valid global register type
 * @param data array of 10B which holds the data to write (Global register structure pointer as input)
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_dm_12k_global_reg_write(struct kbp_device *device, uint8_t devNum,
                                       enum kbp_dev_12k_global_reg_type regType,
                                       const void *data);


/**
 *   Reads a context buffer as a register read, offset address of the CB needs to be provided,
 *   range from  0 - (KBP_DEV_12K_CB_DEPTH - 1). Only 80b read at time
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param cbAddr valid context buffer address
 * @param o_cbRegData array of 10B which holds the read data from CB
 *
 */
kbp_status kbp_dm_12k_cb_reg_read(struct kbp_device *device, uint8_t devNum, uint16_t cbAddr,
                                  struct kbp_dev_ctx_buffer_reg * o_cbRegData);

/**
 *   Writes a context buffer as a register read, offset address of the CB needs to be provided,
 *   range from  0 - (KBP_DEV_12K_CB_DEPTH - 1). Only 80b read at time
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param cbAddr valid context buffer address
 * @param cbRegData array of 10B which holds the data to written to CB
 *
 */
kbp_status kbp_dm_12k_cb_reg_write(struct kbp_device *device, uint8_t devNum, uint16_t cbAddr,
                                   struct kbp_dev_ctx_buffer_reg * cbRegData);

/**
 *   Reads from an LTR register depending on LTR register type.
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param ltrNum valid LTR number
 * @param regType valid LTR register type
 * @param o_data array of 10B which holds the data to write to LTR (LTR register type structure pointer as output)
 *
 */
kbp_status kbp_dm_12k_ltr_read(struct kbp_device *device, uint8_t devNum, uint8_t ltrNum,
                               enum kbp_dev_12k_ltr_reg_type regType, void *o_data);

/**
 *   Writes to an LTR register depending on LTR register type.
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param ltrNum valid LTR number
 * @param regType valid LTR register type
 * @param data array of 10B which holds the data to write to LTR (LTR register type structure pointer as input)
 *
 */
kbp_status kbp_dm_12k_ltr_write(struct kbp_device *device, uint8_t devNum, uint8_t ltrNum,
                                enum kbp_dev_12k_ltr_reg_type regType, const void *data);

/**
 *   Reads from a block register depending on block register type
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param abNum valid array block number
 * @param regType valid BCR register type
 * @param o_data array of 10B which holds the read data from BCR (Block register structure pointer as output)
 *
 */
kbp_status kbp_dm_12k_block_reg_read(struct kbp_device *device, uint8_t devNum, uint16_t abNum,
                                     enum kbp_dev_12k_block_reg_type regType, void *o_data);

/**
 *   Writes to a block register depending on block register type
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param abNum valid array block number
 * @param regType valid BCR register type
 * @param data array of 10B which holds the data to write to BCR (Block register structure pointer as input)
 *
 */
kbp_status kbp_dm_12k_block_reg_write(struct kbp_device *device, uint8_t devNum, uint16_t abNum,
                                      enum kbp_dev_12k_block_reg_type regType, const void *data);

/**
 *   Writes a data/mask of specified length (80b/160b/320b/640b) to the specified row and abNum.
 *   The address has to MSB location. The data and mask are passed in as pointers, and the length
 *   is in bytes. The array is read from MSB down to LSB. Data can be written in either DM or XY mode.
 *   vbit is set for all the entries written via this API
 *
 * @param device Valid device handle.
 * @param devNum device number (reprasent device number if cascaded devices).
 * @param abNum  array block number.
 * @param abAddr MSB row number.
 * @param data valid data pointer to write (which will writeen to device as checnks of 80b from MSB to LSB)
 * @param mask valid data pointer to write (which will written to device as checnks of 80b from MSB to LSB)
 * @param length length of the array to be write (multiple of 10B)
 * @param writeMode Write mode, 0 means DM and 1 is XY
 * @param vbit Valid Bit, 0 means entry is invalid and 1 is entry valid
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_dba_write(struct kbp_device *device, uint8_t devNum, uint16_t abNum,
                                uint16_t abAddr, uint8_t *data, uint8_t *mask,
                                uint32_t length, enum kbp_dev_12k_write_mode writeMode, uint8_t vbit);

/**
 *   Reads a single Array Block database locations either X/Y data from the specified address and abNum.
 *   Returns:
 *   if read_y = 0 (v_bit, parity, 2b parity error, data_x)
 *      read_y = 1 (parity, 2b parity error, data_y)
 *
 * @param device Valid device handle.
 * @param devNum device number (reprasent device number if cascaded devices).
 * @param abNum  array block number.
 * @param abAddr number.
 * @param v_bit which holds the read vbit (only if read_y == 0)
 * @param parity which holds the parity error occured or not
 * @param parity_err which holds whether even/odd parity error
 * @param o_data which holds the read data (either X or Y)
 * @param read_y, if set reads Y else X location
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_dm_12k_dba_read_x_or_y(struct kbp_device *device, uint8_t devNum, uint16_t abNum,
                                      uint16_t abAddr, uint8_t *v_bit, uint8_t *parity,
                                      uint8_t *parity_err, uint8_t *o_data, uint8_t read_y);

/**
 *   Reads a data/mask of specified length (80b/160b/320b/640b) from the specified row and abNum.
 *   The address has to MSB location. The data and mask are passed in as pointers, and the length
 *   is in bytes. The array is read from MSB down to LSB. Data read is always in XY mode.
 *
 * @param device Valid device handle.
 * @param devNum device number (reprasent device number if cascaded devices).
 * @param abNum  array block number.
 * @param abAddr MSB row number.
 * @param o_data valid data pointer to read (which will be read from device as checnks of 80b from MSB to LSB)
 * @param o_mask valid mask pointer to read (which will be read from device as checnks of 80b from MSB to LSB)
 * @param length length of the array to be read (multiple of 10B)
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_dba_read(struct kbp_device *device, uint8_t devNum, uint16_t abNum,
                               uint16_t abAddr, uint8_t *o_data, uint8_t *o_mask, uint32_t length);

/**
 *   Invalidates a specified Array Block database entry.
 *
 * @param device Valid device handle.
 * @param devNum device number (reprasent device number if cascaded devices).
 * @param abNum  array block number.
 * @param abAddr row number.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_dba_invalidate(struct kbp_device *device, uint8_t devNum,
                                     uint16_t abNum, uint16_t abAddr);

/**
 *   Writes a stream of associated data (must be 32b/64b/128b/256b)to the specified UDA address,
 *   the associated data written form MSB to LSB, so udaAddr has to be MSB address
 *
 * @param device Valid device handle.
 * @param devNum device number (reprasent device number if cascaded devices).
 * @param address MSB uda address location.
 * @param data valid associated data (which will be written to device as checnks of 32b from MSB to LSB)
 * @param length length of the associated data to be written (must be 4/8/16/32)
 * @is_adv_write enables advanced uda write
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_uda_write(struct kbp_device *device, uint8_t devNum,
                                uint32_t address, uint8_t *data, uint8_t length, uint8_t is_adv_write);

/**
 *   Reads a stream of associated data (must be 32b/64b/128b/256b) from the specified UDA address,
 *   the associated data read form MSB to LSB, so udaAddr has to be MSB address
 *
 * @param device Valid device handle.
 * @param devNum device number (reprasent device number if cascaded devices).
 * @param address MSB uda address location.
 * @param o_data valid associated data read (which will be read  from device as checnks of 32b from MSB to LSB)
 * @param length length of the associated data to be read (must be 4/8/16/32)
 * @param parity_err set when ECC parity error detected
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_uda_read(struct kbp_device *device, uint8_t devNum,
                               uint32_t address, uint8_t *o_data, uint8_t length, uint8_t *parity_err);

/**
 *   Implements a search instruction. It searches the input key into the
 *   database depending on LTR profile set number. This instruction can be used for searches
 *   with individual search-key lengths of up to 320 bits.
 *   (Note: cant issue NetRoute search
 *       128 sets of LTR, 4 keys, and 4 result ports are available.
 *       Single Bank mode:
 *           0-127 for BANK 0, 4 keys, and 4 result ports.
 *
 *       Dual Bank:
 *           0-63   for BANK 0, 2 keys (KEY 0/1), and 2 result ports (0/1).
 *           64-127 for BANK 1, 2 keys (KEY 2/3), and 2 result ports (2/3).
 *   )
 *
 * @param device Valid device handle.
 * @param ltrNum LTR number for the search
 * @param cbInfo Contains the valid parametes like, masterkey, width, context addressvalid address for search
 * @param o_search_results Structure which holds the results
 *                  (VBit, SMT, ADWidth, HitIdx, Asso-data) for upto 6 results
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_cbwcmp1(struct kbp_device *device, uint8_t ltrNum,
                              struct kbp_dev_12k_ctx_buffer_info * cbInfo,
                              struct kbp_search_result * o_search_results);

/**
 *   Implements a search instruction. It searches the input key into the
 *   database depending on LTR profile set number. This instruction can be used for searches with
 *   individual search-key lengths of up to 640 bits.
 *   (Note: cant issue NetRoute search
 *       128 sets of LTR, 4 keys, and 4 result ports are available.
 *       Single Bank mode:
 *           0-127 for BANK 0, 4 keys, and 4 result ports.
 *
 *       Dual Bank:
 *           0-63   for BANK 0, 2 keys (KEY 0/1), and 2 result ports (0/1).
 *          64-127 for BANK 1, 2 keys (KEY 2/3), and 2 result ports (2/3).
 *   )
 *
 * @param device Valid device handle.
 * @param ltrNum LTR number for the search
 * @param cbInfo Contains the valid parametes like, masterkey, width, context addressvalid address for search
 * @param o_search_results Structure which holds the results
 *                  (VBit, SMT, ADWidth, HitIdx, Asso-data) for upto 6 results
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_cbwcmp2(struct kbp_device *device, uint8_t ltrNum,
                              struct kbp_dev_12k_ctx_buffer_info * cbInfo,
                              struct kbp_search_result * o_search_results);

/**
 *   Implements a special search instruction. It searches the input key into the
 *   database depending on LTR profile set number. This instruction can be used for searches
 *   with individual search key lengths of up to 640 bits.
 *   (Note: can issue NetRoute only on resupt port-0
 *       128 sets of LTR, 4 keys, and 4 result ports are available.
 *       Single Bank mode:
 *           0-127 for BANK 0, 4 keys, and 4 result ports.
 *
 *       Dual Bank:
 *           0-63   for BANK 0, 2 keys (KEY 0/1), and 2 result ports (0/1).
 *          64-127 for BANK 1, 2 keys (KEY 2/3), and 2 result ports (2/3).
 *   )
 *
 * @param device Valid device handle.
 * @param ltrNum LTR number for the search
 * @param cbInfo Contains the valid parametes like, masterkey, width, context addressvalid address for search
 * @param o_search_results Structure which holds the results
 *                  (VBit, SMT, ADWidth, HitIdx, Asso-data) for upto 6 results
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_dm_12k_cbwlpm(struct kbp_device *device, uint8_t ltrNum,
                             struct kbp_dev_12k_ctx_buffer_info * cbInfo,
                             struct kbp_search_result * o_search_results);

/**
 *   Implements a special search instruction. It searches the input key into the
 *   database depending on LTR profile set number. This instruction can be used for searches
 *   with individual search key lengths of up to 640 bits. This API used to get upto 6 results
 *
 *   Compare 3 makes use of 2 LTR profiles, first LTR will return upto 4 results and the LTR+1
 *   will return the 2 results; LTRn key2/3 must of > 320b
 *   NetRoute can be searched only on result port 0 or 2
 *   LTR wrap wil happen form 127 to 0 (non SMT), 63 - 0: 127 - 64 (SMT mode)
 *
 * @param device Valid device handle.
 * @param ltrNum LTR number for the search
 * @param cbInfo Contains the valid parametes like, masterkey, width, context addressvalid address for search
 * @param o_search_results Structure which holds the results
 *                  (VBit, SMT, ADWidth, HitIdx, Asso-data) for upto 6 results
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_cbwcmp3(struct kbp_device *device, uint8_t ltrNum,
                              struct kbp_dev_12k_ctx_buffer_info * cbInfo,
                              struct kbp_search_result * o_search_results);

/**
 *   Flat 80b generic write to the specified address (mainly used for 80b reg write)
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param address valid address to write
 * @param data array of 10B which holds the data to write
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_generic_reg_write(struct kbp_device *device, uint8_t devNum,
                                        uint32_t address, void *data);

/**
 *   Flat 80b generic read from the specified address (mainly used for 80b reg reads)
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param address valid address to read
 * @param o_data array of 10B which holds the read data
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_generic_reg_read(struct kbp_device *device, uint8_t devNum,
                                       uint32_t address, void *o_data);

/**
 *   Handling of special NetRoute instuctions (Type1/2/3).
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param bank_num reflects the bank this write belongs to (SMT: 0/1, nonSMT: 0)
 * @param opcode_high Opcode value bit 8-6
 * @param opcode_low Opcode value bit 5-0
 * @param data Valid data to be written for the above 3 types of oparations
 * @param data_len Length of the data array
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_cmd_send(struct kbp_device *device, uint8_t devNum,
                               uint8_t bank_num, uint8_t opcode_high,
                               uint8_t opcode_low, void *data, uint8_t data_len);

/**
 *   Perofrm NOP operation for specified number of times
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param numTimes Number of times to have the NOPs
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_send_nop(struct kbp_device *device, uint8_t devNum, uint32_t numTimes);


/**
 *   Flat 80b write to the specified Range address
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param address Range address to write
 * @param blk_width width of the block (80/160/320/640)
 * @param rangeRegData array of 10B which holds the data to write
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_range_reg_write(struct kbp_device *device, uint8_t devNum,
                                      uint32_t address, struct kbp_dev_12k_range_reg * rangeRegData);

/**
 *   Flat 80b read from the specified Range address
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param address Range address to read
 * @param blk_width width of the block (80/160/320/640)
 * @param o_rangeRegData array of 10B which holds the read data
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_range_reg_read(struct kbp_device *device, uint8_t devNum,
                                     uint32_t address, struct kbp_dev_12k_range_reg * o_rangeRegData);

/**
 *   Peformas the supported Block operations, these can be Block 1. Move 2. Clear 3. Copy
 *   4. entry invalidate. Block operations are per device basis.
 *
 * @param device Valid device handle.
 * @param m_srcAddr source address
 * @param m_destAddr destination address
 * @param m_instType type of operation
 * @param m_numOfWords number of 80b words
 * @param m_countDir Count Direction, used only with BLKCPY and BLKMV
 * @param m_setOrClear Entry validate or invalidate, used only with BLKEVI
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_block_operation(struct kbp_device *device, uint32_t m_srcAddr, uint32_t m_destAddr,
                                      enum kbp_dev_12k_blk_inst_type m_instType, uint16_t m_numOfWords,
                                      enum kbp_dev_12k_blk_count_dir m_countDir, enum kbp_dev_12k_validate_invalidate m_setOrClear);

/**
 *   Refreshes the LTR register with use of shadow memory. This refreshes the LTR register data
 *   depending on LTR register type. It reads the data from Shadow Memory the data of specified
 *   register and writes it to device. This function will be useful to re-write the LTR Register
 *   Data which have suffered from soft parity error
 *
 * @param device Valid device handle.
 * @param devNum device number
 * @param ltrNum Ltr number which need to be refresh
 * @param regType type pf LTR: refer the DS
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_ltr_refresh(struct kbp_device *device, uint8_t devNum, uint8_t ltrNum,
                                  enum kbp_dev_12k_ltr_reg_type regType);

/**
 * This API used to sync the Shadow Memory LTRs. Its reads the necessary LTRs of specified
 * device and update the SM accordingly.
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_ltr_sm_update(struct kbp_device *device);

/**
 * This API used to inject the parity errors by programming the NETL debug registed (0x7FE, 0x7FF).
 * as of now we are currupting both X/Y [D/M] rows by flipping the X: b:1 and Y: b:5,4, and 2 of 80b
 * When its enabled it will flips the above mentioned bits before writing to the DBA

 * Note:
 *    There must be of 3 NOPs delay to make this work. after enabling this have 3 NOPs

 * @param device Valid device handle.
 * @param parity_type injecting the parity errors as of enum kbp_dev_12k_parity_inject_type
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_inject_parity(struct kbp_device *device, uint32_t parity_type);


/**
 * This API used to inject the parity errors by programming the NETL debug registed (0x7FE, 0x7FF).
 * as of now we are currupting both X/Y [D/M] rows by flipping the X: b:1 and Y: b:5,4, and 2 of 80b
 * When its enabled it will flips the above mentioned bits before writing to the DBA

 * Note:
 *    There must be of 3 NOPs delay to make this work. after enabling this have 3 NOPs

 * @param device Valid device handle.
 * @param ltr_num LTR number selected to print the details; by reading all LTR#n registers
 * @param fp File pionter to print the data to console or to file (default console)
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_print_ltrs_info(struct kbp_device *device, uint32_t ltr_num, FILE *fp);

/**
 * This API used to do soft reset by programming the NETL debug register (0x7FE, 0x7FF).
 * This one resets whole chip including DB registers and Vbit of MC and RPT,
 * LUT memory (ROP mode only) and reset LTR contents, power off the UDA
 *
 * @param device Valid device handle.
 * @param hard_reset 0: clears only active LTR content, 1: clears all LTR content
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_12k_soft_reset(struct kbp_device *device, uint8_t hard_reset);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif                          /* INCLUDED_NLMDEVMGR_H */
