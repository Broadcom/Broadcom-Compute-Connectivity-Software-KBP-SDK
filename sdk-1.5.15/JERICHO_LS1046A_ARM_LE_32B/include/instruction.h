/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

/**
 * @file instruction.h
 *
 * This module helps to construct instructions that are used to search
 * multiple databases in parallel and abstracts LTR
 * and KPU programming for the user.
 */

#include <stdint.h>

#include "errors.h"
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup INSTRUCTION_API
 * @{
 */

/**
 * Maximum number of results for an instruction.
 */
#define KBP_INSTRUCTION_MAX_RESULTS    (8)

/**
 * Maximum number of AD bytes returned for a search.
 */
#define KBP_INSTRUCTION_MAX_AD_BYTES    (32)

/**
 * Opaque instruction handle.
 */

struct kbp_instruction;
struct kbp_db;
struct kbp_key;

/**
 * Specifies if the result is valid or invalid.
 */

enum kbp_result_valid
{
    KBP_RESULT_IS_INVALID,    /**< Search result is invalid */
    KBP_RESULT_IS_VALID       /**< Search result is valid */
};

/**
 * Specifies if the search resulted in a hit or miss.
 */

enum kbp_hit_or_miss
{
    KBP_MISS,               /**< There is no entry in the database that matches the search key. */
    KBP_HIT                 /**< Entry matching the search key found in the database. */
};

/**
 * Properties that can be set on the instruction.
 */

enum kbp_instruction_properties
{
    KBP_INST_PROP_RESULT_DATA_LEN, /**< To set the result length in bytes (OP specific) */
    KBP_INST_PROP_INVALID
};


/**
 * Specifies if the returned response has associated data and its size.
 */

enum kbp_search_resp_type
{
    /* ONLY INDEX */
    KBP_INDEX_AND_NO_AD = 0,    /**< Only index is returned in the search result.*/

    /* INDEX AND ASSOCIATED DATA */
    KBP_INDEX_AND_32B_AD  = 4,   /**< Index and 32-bit AD is returned in the search result. */
    KBP_INDEX_AND_64B_AD  = 8,   /**< Index and 64-bit AD is returned in the search result. */
    KBP_INDEX_AND_96B_AD  = 12,  /**< Index and 96-bit AD is returned in the search result. */
    KBP_INDEX_AND_128B_AD = 16,  /**< Index and 128-bit AD is returned in the search result. */
    KBP_INDEX_AND_160B_AD = 20,  /**< Index and 160-bit AD is returned in the search result. */
    KBP_INDEX_AND_192B_AD = 24,  /**< Index and 192-bit AD is returned in the search result. */
    KBP_INDEX_AND_256B_AD = 31,  /**< Index and 256-bit AD is returned in the search result. */

    /* ONLY ASSOCIATED DATA */
    KBP_ONLY_AD_24B  =  3 + KBP_INDEX_AND_256B_AD, /**< Only 24-bit AD is returned in the search result. */
    KBP_ONLY_AD_32B  =  4 + KBP_INDEX_AND_256B_AD, /**< Only 32-bit AD is returned in the search result. */
    KBP_ONLY_AD_64B  =  8 + KBP_INDEX_AND_256B_AD, /**< Only 64-bit AD is returned in the search result. */
    KBP_ONLY_AD_96B  = 12 + KBP_INDEX_AND_256B_AD, /**< Only 96-bit AD is returned in the search result. */
    KBP_ONLY_AD_128B = 16 + KBP_INDEX_AND_256B_AD, /**< Only 128-bit AD is returned in the search result. */
    KBP_ONLY_AD_160B = 20 + KBP_INDEX_AND_256B_AD, /**< Only 160-bit AD is returned in the search result. */
    KBP_ONLY_AD_192B = 24 + KBP_INDEX_AND_256B_AD, /**< Only 192-bit AD is returned in the search result. */
    KBP_ONLY_AD_256B = 31 + KBP_INDEX_AND_256B_AD  /**< Only 256-bit AD is returned in the search result. */
};

/**
 * The layout of the search result returned by the instruction search
 * operation.
 */

struct kbp_search_result
{
    enum kbp_result_valid result_valid[KBP_INSTRUCTION_MAX_RESULTS];   /**< Indicates whether the result is valid or invalid. */
    enum kbp_hit_or_miss  hit_or_miss[KBP_INSTRUCTION_MAX_RESULTS];    /**< Indicates whether the search is a hit or miss. */
    enum kbp_search_resp_type resp_type[KBP_INSTRUCTION_MAX_RESULTS];  /**< Indicates the type of AD returned. */
    uint8_t hit_dev_id[KBP_INSTRUCTION_MAX_RESULTS];  /**< Specifies the hit dev id, relevant when multiple KBPs are cascaded. The hit may occur on a cascaded device */
    uint32_t hit_index[KBP_INSTRUCTION_MAX_RESULTS];  /**< Specifies the hit index for ACLs, LPM and EM */
    /**
        *Associated Data. The number of valid bytes in the assoc_data array depends on the length of the AD returned.
        *- If 32b AD is returned for result-0 and user AD is 32 bits,
        *    then the AD will be in assoc_data[0][0] (MS AD byte) to assoc_data[0][3] (LS AD byte)
        *
        *- If 64b AD is returned for result-0 and user AD is 64 bits,
        *   then the AD will be in assoc_data[0][0] (MS AD byte) to assoc_data[0][7] (LS AD byte)
        *
        *- If 32b AD is returned for result-0 and the user AD is only 8 bits,
        *    then AD is stored in assoc_data[0][3].
        *
        *- If 32b AD is returned for result-0 and the user AD is only 24 bits,
        *     then AD is stored in from assoc_data[0][1] (MS byte of AD) to assoc_data[0][3] (LS byte of AD)
        *
        *- If 20b AD is returned for result-0 and the user AD is 20 bits,
        *     then AD is stored in from assoc_data[0][0] (MS byte of AD) to assoc_data[0][2] (LS byte of AD, only bits 7-4 will be valid)
        *
        */
    uint8_t assoc_data[KBP_INSTRUCTION_MAX_RESULTS][KBP_INSTRUCTION_MAX_AD_BYTES];
};

/**
 * Creates a new instruction
 *
 * @param device Valid device handle.
 * @param id Nonzero instruction ID. This is a control-plane identifier only
 * @param ltr Logical table register (LTR) number. This is the number transmitted by NPU on the data plane to enable this instruction.
 * @param instruction Instruction, initialized and returned on success.
 *
 * @retval KBP_OK On success.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 * @retval KBP_OUT_OF_MEMORY if out of heap resources.
 * @retval KBP_DUPLICATE_INSTRUCTION_ID if the control plane ID has already been encountered.
 * @retval KBP_LTR_BUSY if the LTR number requested is already being used.
 */

kbp_status kbp_instruction_init(struct kbp_device *device, uint32_t id, uint32_t ltr,
                                struct kbp_instruction **instruction);

/**
 * Destroys the instruction, LTR is freed.
 *
 * @param instruction Valid instruction handle.
 *
 * @retval KBP_OK On success
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */

kbp_status kbp_instruction_destroy(struct kbp_instruction *instruction);

/**
 * Adds a database to the instruction
 *
 * @param instruction Valid instruction handle.
 * @param db Valid database handle.
 * @param result The expected position in the packed result on the interface where the user wishes to see the search result for this database.
 *
 * @retval KBP_OK if the database key can be derived from the master key.
 * @retval KBP_INVALID_ARGUMENT to indicate invalid or null parameters.
 * @retval KBP_KEY_FIELD_MISSING if a field specified in the database key is missing from the master key.
 * @retval KBP_KEY_GRAN_ERROR if the database key can be derived from the master key only from byte boundaries.
 * @retval KBP_NUM_SEARCHES_EXCEEDED if too many searches have been specified.
 * @retval KBP_RESULT_NOT_VALID if the specified result number cannot be honored. This is treated as a warning.
 */

kbp_status kbp_instruction_add_db(struct kbp_instruction *instruction, struct kbp_db *db, uint32_t result);

/**
 * Sets the master key for the instruction. This
 * defines the various fields the user will
 * transmit over the interface. This information,
 * in combination with the database keys, will
 * program the KPU.
 *
 * @see KEY
 *
 * @param instruction Valid instruction handle.
 * @param master_key Valid initialized key handle.
 *
 * @retval KBP_OK if the database key can be derived from the master key.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */

kbp_status kbp_instruction_set_key(struct kbp_instruction *instruction, struct kbp_key *master_key);

/**
 * Installs the instruction onto the device. The LTR is active from
 * this point for data-plane instructions.
 *
 * @param instruction Valid instruction handle.
 *
 * @retval KBP_OK if the database key can be derived from the master key.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 * @retval KBP_EXCEEDED_AGGREGATE_AD_WIDTH if the amount of associated data returned exceeds interface capability.
 */

kbp_status kbp_instruction_install(struct kbp_instruction *instruction);

/**
 * Pretty-prints the instruction.
 *
 * @param instruction Valid instruction handle.
 * @param fp Pointer to the file where contents are to be dumped.
 *
 * @retval KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_instruction_print(struct kbp_instruction *instruction, FILE *fp);

/**
 * Sets a specific property for the instruction.
 *  Property - KBP_INST_PROP_RESULT_DATA_LEN: User can set the AD length and the same will be used to configure the result length register in OP.
 *
 * @param inst Valid instruction handle
 * @param property Instruction properties ::kbp_instruction_properties.
 * @param ... Variable arguments based on property.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_instruction_set_property(struct kbp_instruction *inst, enum kbp_instruction_properties property, ...);

/**
 * Exercises the instruction and searches the hardware/model. The real
 * hardware or model must be available. If no transport layer is
 * associated with the device, the API returns an error code.
 * This API can be used to validate the database in HW by comparing the
 * returned hit-index/AD with expected. The expected value must be calculated
 * taking into account that the returned Index/AD depends on the priority
 * of stored entries / longest matched prefix. Multiple such searches with
 * the right keys can validate all the components of the database stored in HW.

 *
 * @param instruction Valid instruction handle.
 * @param master_key The master key.
 * @param cb_addrs Address of the context buffer.
 * @param result The search result, returned for the instruction.
 *
 * @retval KBP_OK On success and result structure is populated.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */

kbp_status kbp_instruction_search(struct kbp_instruction *instruction, uint8_t *master_key, uint32_t cb_addrs, struct kbp_search_result *result);

/**
 * @}
 */

/**
 * @addtogroup ISSU_API
 * @{
 */

/**
 * Returns the new Instruction Handle after ISSU operation
 *
 *
 * @param device Valid KBP device handle
 * @param stale_ptr Instruction pointer before ISSU.
 * @param instruction New instruction handle.
 *
 * @retval KBP_OK On success and result structure is populated.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */

kbp_status kbp_instruction_refresh_handle(struct kbp_device *device, struct kbp_instruction *stale_ptr, struct kbp_instruction **instruction);

/**
 * Exercises the instruction layout. User can give the proper database key and get back the
 * master key. This API just takes the instruction (master key layout), database key to be
 * searched and the master key to get back for the device/instruction search. This won't do
 * search.
 *
 * Note: User has to pass array of 80 bytes (640b master key), where the valid database key
 * is filled in with the master key and user can use it for the search.
 *
 * For parallel search, same master_key needs to be passed to function, so that only required
 * fields are updated, in case of overlapping fields; the recent db_key values are
 * over-written.
 *
 * @param instruction Valid instruction handle.
 * @param db Valid database handle.
 * @param db_key Valid database key.
 * @param search_key output key, filled with database key and used for device search.
 *
 * @retval KBP_OK On success and result structure is populated.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */

kbp_status kbp_instruction_master_key_from_db_key(struct kbp_instruction *instruction, struct kbp_db * db, uint8_t *db_key, uint8_t *search_key);

/**
 * This API allows user to set the LUT opcode for the instruction. It should be called after instruction install
 * and the same will be used to do LUT write from the KBP SDK.
 *
 * @param instruction Valid instruction handle.
 * @param opcode Opcode for this instruction
 *
 * @retval KBP_OK on success.
 */
kbp_status kbp_instruction_set_opcode(struct kbp_instruction *instruction, int32_t opcode);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*__INSTRUCTION_H */
