/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __XPT_OP2_H
#define __XPT_OP2_H

#include <stdint.h>
#include "xpt_op.h"
#include "errors.h"
#include "allocator.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file xpt_op2.h
 *
 * Transport layer implementation for Optimus Prime 2.
 */


/**
 * @brief Transport layer interface for Optimus Prime 2
 */

struct op2_xpt
{
    struct op_xpt op_xpt_info; /**< Transport layer interface details common to both OP and OP2 */

    /**
     * Optimus Prime 2 control plane based search function. A single search key can
     * be sent from either thread to produce the expected result.
     *
     * @param handle Opaque user handle.
     * @param core_id0 The input core id for key0.
     * @param bank_id0 The input bank_id for key0.
     * @param cascade0 The input cascade bit for key0.
     * @param ltr0 The LTR N#0 to search key0.
     * @param ctx0 The context buffer ID to use with key0.
     * @param key0 The first master key bytes.
     * @param key_len0 The number of valid bytes in key0.
     * @param result0 If AD is expected, fill the expected response type. Default is KBP_INDEX_AND_NO_AD
     *        and get the expected results
     * @param core_id1 The input core id for key1.
     * @param bank_id1 The input bank_id for key1.
     * @param cascade1 The input cascade bit for key1.
     * @param ltr1 The LTR N#1 to search key1.
     * @param ctx1 The context buffer ID to use with key1.
     * @param key1 The second master key bytes.
     * @param key_len1 The number of valid bytes in key1.
     * @param result1 If AD is expected, fill the expected response type. Default is KBP_INDEX_AND_NO_AD
     *        and get the expected results
     *
     * @return KBP_OK on successful completion of call and result contents are valid. Or an error code
     */

    kbp_status (*op2_search)(void *handle,
                             uint32_t port_id0, int32_t ltr0, uint32_t ctx0, const uint8_t *key0, uint32_t key_len0,
                             struct kbp_search_result *result0,
                             uint32_t port_id1, int32_t ltr1, uint32_t ctx1, const uint8_t *key1, uint32_t key_len1,
                             struct kbp_search_result *result1);

    /**
     *
     * Optimus Prime 2 control plane based Stats counter command function.
     * A single stats master record can be sent from either thread to update a stat/counter table.
     *
     * @param handle Opaque user handle.
     * @param records A stream of bytes that represents a 64B Ethernet packet that has multiple OP2 stats records.
     * @param num_bytes N# valid bytes in current 512b data.
     * @param pipe_id Pipe ID for SRE & SCE modules: either 0 or 1.
     * @param port_id Stats Port ID to identify the right set of SRE/SCE registers to extract stats commands.
     *
     * @return KBP_OK on successful completion of call or an error code
     */

    kbp_status (*op2_stats_process)(void *handle, uint8_t *records, uint32_t num_bytes, uint8_t pipe_id, uint8_t port_id);

    /**
     * Writes 64b aligned stats/counter to UDA.
     *
     * @param handle Opaque OP2 user handle.
     * @param address_64 The 64b aligned UDA stats/counter address.
     * @param value The 64b value to write into UDA.
     * @param core_bitmap The core IDs where we are writing stats/counter.
     *
     * @return KBP_OK if successfully dispatched to device
     */

    kbp_status (*op2_stats_write)(void *handle, uint32_t address_64, uint8_t *value, uint32_t core_bitmap);

    /**
     * Read 64b aligned stats/counter from UDA.
     *
     * @param handle Opaque OP2 user handle.
     * @param address_64 The 64b aligned UDA stats/counter address.
     * @param value The 64b value to read back from UDA.
     * @param core_id The core ID from where we are reading stats/counter.
     *
     * @return KBP_OK if successfully read from device and value is valid.
     */

    kbp_status (*op2_stats_read)(void *handle, uint32_t address_64, uint8_t *value, uint32_t core_id);

    /**
     * API to scrub the DMA buffer. Basically copies 64b response messages from Kernel space
     * to User space DMA buffer.
     *
     * @param handle Opaque OP2 user handle.
     * @param ch_num Tx DMA channel number.
     * @param buffer Host-side buffer handle to write the BLKREAD data into.
     * @param buffer_size The size of the host-side buffer in num# 64b words.
     * @param num_scrubbed_64b_words Output the number of 64b words read into the host-side buffer.
     *
     * @return KBP_OK on success else an error code
     */

    kbp_status (*op2_scrub_dma_buffer)(void *handle, int32_t ch_num, uint64_t *buffer, uint32_t buffer_size, uint32_t *num_scrubbed_64b_words);
};

#ifdef __cplusplus
}
#endif
#endif /*__XPT_OP2_H */
