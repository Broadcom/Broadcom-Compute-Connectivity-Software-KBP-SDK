/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __FW_COMPLEX_H
#define __FW_COMPLEX_H

#include <stdint.h>
#include "fw_endian.h"

#ifdef __cplusplus
extern "C" {
#endif


#define OP_FW_NUM_ROWS_IN_AB        4096
#define OP_FW_NUM_BLKS              256
#define OP_FW_MAX_LSNNW_LENGTH_1    256
#define OP_FW_MAX_LSNNW_LENGTH_8    (OP_FW_MAX_LSNNW_LENGTH_1 / 8)

#define POLL_COUNT 1000

/** Marker/signature for Bulk Read of Counters */
#define KBP_OP2_COUNTER_BULK_READ_MARKER            (1)


/**
 * @brief Common header for all instructions
 */
struct op_command_hdr
{
    __EO_7(uint32_t data_length:4,    /**< data present count in multiple of 64b words */
            uint32_t no_dummy_resp:1, /**< Dummy response from HST is suppressed, ARM may be expected to generate resp */
            uint32_t absolute_addr:1, /**< IOCW specific */
            uint32_t resv0:1,         /*PAD */
            uint32_t xor_entry:1,     /**< Indicates if XOR should be performed after the write*/
            uint32_t opcode:5,        /**< Instruction type ::op_instruction */
            uint32_t resv1:19);       /**< PAD */
            uint32_t resv2;           /**< PAD */
};


enum op_complex_instruction
{
    KBP_OP_INSTR_HBB_READ = 0x6,
    KBP_OP_INSTR_UDA_WRITE = 0x7,
    KBP_OP_INSTR_BLKCPY = 0x8,
    KBP_OP_INSTR_BLKMV = 0x9,
    KBP_OP_INSTR_BLKCLR = 0xA,
    KBP_OP_INSTR_BLKENV = 0xB,
    KBP_OP_INSTR_NATIVE_TYPE1 = 0xC,
    KBP_OP_INSTR_DBA_SCAN = 0xD,
    KBP_OP_INSTR_UDA_COPY = 0xE,
    KBP_OP_INSTR_UDA_AD_WRITE = 0xF,
    KBP_OP_INSTR_UPDATE_UDA_REGION = 0x10,
    KBP_OP_INSTR_READ_UDA_REGION = 0x11,
    KBP_OP_INSTR_UDA_CHUNK_COPY = 0x12,
    KBP_OP_INSTR_COUNTER_SCAN = 0x13
};

/**
 * @brief Software representation of resources for Bulk Read and Bulk Write instructions for OP2
 */
enum op2_resource_identifier
{
    KBP_OP2_RES_ID_RPT = 1,
    KBP_OP2_RES_ID_KPC_REGS = 2,
    KBP_OP2_RES_ID_DBI_REGS = 3,
    KBP_OP2_RES_ID_DBA_MEMORY = 4,
    KBP_OP2_RES_ID_DBA_REGS = 5,
    KBP_OP2_RES_ID_UDA_MEMORY = 6,
    KBP_OP2_RES_ID_UDA_REGS = 7,
    KBP_OP2_RES_ID_UIT_REGS = 8,
    KBP_OP2_RES_ID_UDR_REGS = 9,
    KBP_OP2_RES_ID_AGING_MEMORY = 10,
    KBP_OP2_RES_ID_SRE = 11,
    KBP_OP2_RES_ID_SCE = 12,
    KBP_OP2_RES_ID_SCP = 13,
    KBP_OP2_RES_ID_INVALID
};

/**
 * @brief Software representation of SW DBA Scan
 */
struct op_sw_dba_scan {
    __EO_7(uint32_t data_length:4,      /**< DataPresentCnt */
           uint32_t flags:4,            /**< NoDummyResp */
           uint32_t opcode:5,           /**< Internal Opcode */
           uint32_t initiate_dba_scan:1,/**< Enable/disable SW DBA scan */
           uint32_t performance_test:2, /**< Performance test */
           uint32_t num_abs:8,          /**< number of ABs */
           uint32_t resv0:8);           /**< PAD */
    uint32_t fw_par_scan_intvl;         /**< FW Parity Scan interval */
};

/**
 * @brief Software representation of HitBit Bank read complex instruction
 */
struct op_hb_bank_read {
    __EO_8(uint32_t data_length:4,    /**< data present count */
           uint32_t no_dummy_resp:1,  /**< Dummy response from HST is suppressed, ARM may be expected to generate resp */
           uint32_t dbc:1,            /**< Internal use */
           uint32_t resv:2,           /**< Reserved */
           uint32_t opcode:5,         /**< Instruction type ::op_instruction */
           uint32_t bank_no:4,        /**< Hitbit Bank to read */
           uint32_t start_word:11,    /**< Hitbit bank start index */
           uint32_t nwords_0_3:4);     /**< Number of words to read (3:0) */

    __EO_3(uint32_t nwords_4:1,       /**< Number of words to read (10:7) */
           uint32_t read_valid_memory:1,  /**< Bit to indicate from valid memory */
           uint32_t resv1:30);        /**< Reserved */

    uint64_t data[31];
};

/**
 * @brief structure for block_cpy and block move
 */

/*{64'b0, 4'b0, DstAddr[19:0], 4'b0, SrcAddr[19:0], N[11:0], 3'b0, Dir} */

struct op_blk_cpy_move {
    __EO_7(uint32_t direction:1,     /**< 0 ==> increasing address order,  1 ==> decreasing address order */
           uint32_t dbc:1,
           uint32_t resv0:2,
           uint32_t num_rows_3_0:4,
           uint32_t num_rows_11_4:8,
           uint32_t src_addr_7_0:8,
           uint32_t src_addr_15_8:8);

    __EO_6(uint32_t src_addr_19_16:4,
           uint32_t resv1:4,
           uint32_t dest_addr_7_0:8,
           uint32_t dest_addr_15_8:8,
           uint32_t dest_addr_19_16:4,
           uint32_t resv2:4);
};


/**
 * @brief structure for block_clr
 */
/*{64'b0, 24'b0, 4'b0, Addr[19:0], N[11:0], 3'b0, SetNotClear}*/

struct op_blk_clr_env {
    __EO_7(uint32_t setnotclear:1,
           uint32_t dbc:1,
           uint32_t resv0:2,
           uint32_t num_rows_3_0:4,
           uint32_t num_rows_11_4:8,
           uint32_t addr_7_0:8,
           uint32_t addr_15_8:8);

    __EO_3(uint32_t addr_19_16:4,
           uint32_t resv1:4,
           uint32_t resv2:24);
};


/**
 *@brief structure for writing data to the UDA
 */
struct op_uda_write {
    __EO_7(uint32_t data_length:4,     /**< data present count */
           uint32_t no_dummy_resp:1,   /**< Dummy response from HST is suppressed, ARM may be expected to generate resp */
           uint32_t intrl_inst_done:1, /**< Internal Inst done flag 0: set inst done bit, 1: don't set inst done bit */
           uint32_t dbc:1,             /**< Internal use */
           uint32_t is_multi_wr:1,     /**< Indicates if advanced write is required or not*/
           uint32_t opcode:5,          /**< Instruction type ::op_instruction */
           uint32_t nbytes:19);        /**< The number of bytes (oversized, really need only 9 bits) */
           uint32_t address_32;        /**< Address in the UDA where to write*/

    uint8_t dw[32];
};

struct op_uda_copy {
    __EO_9(uint32_t data_length:4,       /**< data present count */
           uint32_t no_dummy_resp:1,     /**< Dummy response from HST is suppressed, ARM may be expected to generate resp */
           uint32_t absolute_addr:1,     /**< IOCW specific */
           uint32_t dbc:1,               /**< Internal use */
           uint32_t xor_entry:1,         /**< Indicates if XOR should be performed after the write*/
           uint32_t opcode:5,            /**< Instruction type ::op_instruction */
           uint32_t num_units:9,         /**< Number of units to be copied */
           uint32_t each_unit_len:2,     /**< 0 == 32b 1 == 64b 2 == 128b 3 == 256b */
           uint32_t resv0:8);            /**< Reserved bits */

            /* Second 32b */
    __EO_2(uint32_t src_uda_address:24,  /**< Source UDA Address */
           uint32_t resv1:8);            /**< Reserved bits */

           /* Third 32b */
    __EO_2(uint32_t dest_uda_address:24,  /**< Destination UDA Address */
           uint32_t resv2:8);             /**< Reserved bits */
};

/**
 * @brief Software representation of Native LSN NibbleWrite complex instruction
 */

struct op_native_lsnnw {
    __EO_7(uint32_t dbc:1,                     /**< Internal use */
           uint32_t resv0:6,                   /**< PAD */
           uint32_t is_multi_wr:1,             /**< Indicates if advanced write is required or not */
           uint32_t num_nibbles:6,             /**< Length of the entry in nibbles */
           uint32_t resv1:2,                   /**< PAD */
           uint32_t start_nibble:8,            /**< Start nibble location of the entry */
           uint32_t addr_7_0:8);                /**< Physical address of the UDM */

           /* Second 32b */
    __EO_4(uint32_t addr_15_8:8,               /**< Physical address of the UDM */
           uint32_t addr_18_16:3,              /**< Physical address of the UDM */
           uint32_t resv2:5,                   /**< PAD */
           uint32_t resv3:16);                 /**< PAD */

    uint8_t data[OP_FW_MAX_LSNNW_LENGTH_8];    /**< Entry data */
};

#define OP2_FW_MAX_LSNNW_LENGTH_8 (104) /* UDA data max bytes(64) + HitBit data max bytes(40) */

struct op2_native_lsnnw {
    __EO_8(uint32_t multi_cast:1,              /**< Multicast */
            uint32_t lsnnwa:1,                  /**< is LSNNWa instr present */
            uint32_t resv0:2,                   /**< PAD */
            uint32_t hitbit_update:2,           /**< Hitbit update mode */
            uint32_t xor_entry:2,               /**< Indicates if advanced write is required or not */
            uint32_t num_nibbles:8,             /**< Length of the entry in nibbles */
            uint32_t start_nibble:8,            /**< Start nibble location of the entry */
            uint32_t addr_7_0:8);                /**< Physical address of the UDM */

            /* Second 32b */
    __EO_5(uint32_t addr_15_8:8,               /**< Physical address of the UDM */
            uint32_t addr_18_16:3,              /**< Physical address of the UDM */
            uint32_t resv1:5,                   /**< PAD */
            uint32_t nibble_mask:8,             /**< Nibble mask */
            uint32_t resv2:8);                  /**< PAD */

    uint8_t data[OP2_FW_MAX_LSNNW_LENGTH_8];    /**< data. If HB is present 1st 24/40 bytes is Hitbit data
                                                     remaining bytes are UDA data of size (num_nibbles / 2) */
};

struct op2_bulk_read {
    __EO_3(uint32_t address:27,             /**< Address */
           uint32_t core_id:1,              /**< Core ID */
           uint32_t resv0:4);               /**< PAD */

    /* Second 32b */
    __EO_7(uint32_t read_size:20,           /**< Read Size(number of locations) */
           uint32_t send_to_ddma:1,         /**< Send to direct DMA channel */
           uint32_t sts_sel_path:1,         /**< Stats select path flag(internal use) */
           uint32_t res_identifier:4,       /**< Resource Identifier */
           uint32_t resv2:1,                /**< PAD */
           uint32_t splfun:1,               /**< Special Function bit */
           uint32_t marker:4);              /**< Marker or notifier field */
};

#define OP2_HWA_BLKWRITE_MAX_DATA_LEN_8 240

struct op2_bulk_write {
    __EO_2(uint32_t address:27,             /**< Address */
           uint32_t resv0:5);               /**< PAD */

    /* Second 32b */
    __EO_7(uint32_t write_size:20,          /**< Write size(number of locations) */
           uint32_t write_data_size:2,      /**< 0: <= 64b, 1:128b (like for Aging data with mask), 2: 192b (like for RPT/DBA */
           uint32_t res_identifier:4,       /**< Resource Identifier */
           uint32_t multicast:1,            /**< Multicast flag */
           uint32_t splfun:1,               /**< Special Function */
           uint32_t is_xor:2,               /**< XOR attribute: 0: No XOR; 1: UDM level XOR(AD); 2: XOR at UDC Level */
           uint32_t resv1:2);               /**< PAD */

    uint8_t data[OP2_HWA_BLKWRITE_MAX_DATA_LEN_8];
};

/**
 * @brief Software representation of Individual Counter Scan complex instruction
 */
struct op2_counter_scan {
    __EO_4(uint32_t data_length:4,          /**< DataPresentCnt */
           uint32_t flags:4,                /**< NoDummyResp */
           uint32_t opcode:5,               /**< Internal Opcode */
           uint32_t address_0_18:19);       /**< STS register [0-18] */

    __EO_2(uint32_t address_19_23:5,        /**< STS register [19-23] */
           uint32_t resv:27);               /**< PAD */
};

#ifdef __cplusplus
}
#endif

#endif

