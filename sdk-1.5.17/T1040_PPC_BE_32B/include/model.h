/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __MODEL_H
#define __MODEL_H

#include <stdint.h>

#include "device.h"
#include "errors.h"
#include "init.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Statistics obtained from the C-Model
 */
struct kbp_sw_model_stats
{
    /**< Maximum number of DBA blocks lit by any key during a compare, per LTR */
    uint32_t max_num_dba_blocks_lit_per_key[KBP_HW_MAX_LTRS][KBP_HW_MAX_KPUS];
};

/**
 * Model properties that can be set by user
 */
enum kbp_sw_model_property
{
    KBP_SW_MODEL_DUMP,    /**< Dump PIO writes to file, a valid file pointer must be provided */
    KBP_SW_MODEL_UNROLL_COMPLEX_INST, /**< Logs the unrolled complex instruction by issuing
                                                                broken up instructions*/
    KBP_SW_MODEL_TRACE,   /**< Trace print the search results */
    KBP_SW_MODEL_TRIG_EVENTS,  /** Trigger callbacks for HW write events */
    KBP_SW_MODEL_INVALID  /**< This should be the last entry */
};


/**
 * @brief Configuration details for the KAPS model
 */
struct kbp_sw_model_kaps_config
{
    uint8_t id; /**< Device id */
    uint8_t sub_type;   /**< Device sub type */
    uint16_t total_num_rpb; /**< Total number of root blocks in the KAPS device*/
    uint16_t total_num_small_bb; /**< Total number of small bucket blocks in KAPS device */
    uint16_t total_num_bb;  /**< Total number of bucket blocks in the KAPS device */
    uint16_t num_rows_in_rpb; /**< Number of rows in one root block */
    uint16_t num_rows_in_small_bb; /**< Number of rows in one small bucket block */
    uint16_t num_rows_in_bb; /**< Number of rows in one bucket block */
    uint16_t profile;        /**< profile in which the device will be used */
};

/**
 * @brief configuration for 12K model
 */
struct kbp_sw_model_12k_config
{
    uint32_t num_devices;     /**< Number of cascaded devices */
    uint32_t dba_mb;          /**< 40 or 80Mb device */
    uint32_t algorithmic_lpm; /**< Algorithmic LPM support on device */
    uint32_t algorithmic_acl; /**< Algorithmic ACL support on device */
};

/**
 * @brief Configuration details for the OP model
 */
struct kbp_sw_model_op2_config
{
    uint32_t dev_type;         /**< 3:0   : 0 - Silicon , Non-zero values between <0x1-0x14> for internal Model testing
                                    7-4   : are internal use [device types]
                                   11-8   : are internal use [small density device types] */
    int32_t num_cores;
};

/**
 * @brief Configuration details for the supported devices
 */
struct kbp_sw_model_config
{
    union {
        struct kbp_sw_model_kaps_config config_kaps;    /**< Configuration details for the KAPS model */
        struct kbp_sw_model_12k_config config_12k;      /**< Configuration details for 12K model */
        struct kbp_sw_model_op2_config config_op2;      /**< Configuration details for OP2 model*/
    } u;
};

/**
 * Initialize the software model and return a transport layer
 *
 * @param alloc valid allocator handle
 * @param type the device type to initialize the model for ::kbp_device_type
 * @param flags ::kbp_device_flags OR'd together.
 * @param config has the configuration input details for creating the Model. If NULL, the default config is chosen
 * @param xpt pointer to the transport layer initialized by the function on success
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_sw_model_init(struct kbp_allocator *alloc, enum kbp_device_type type,
                             uint32_t flags, struct kbp_sw_model_config *config, void **xpt);

/**
 * Destroy the resources allocated by the software model
 *
 * @param xpt valid initialized transport layer handle returned by kbp_sw_model_init()
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_sw_model_destroy(void *xpt);

/**
 * Obtain the Model Statistics
 *
 * @param xpt valid initialized transport layer handle returned by kbp_sw_model_init()
 * @param stats the model statistics will be  returned here
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_sw_model_get_stats(void *xpt, struct kbp_sw_model_stats *stats);

/**
 * Set property attributes on the model
 *
 * @param xpt the model handle
 * @param property the model property to set in ::kbp_sw_model_property
 * @param ... the property value
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_sw_model_set_property(void *xpt, enum kbp_sw_model_property property, ...);

#ifdef __cplusplus
}
#endif
#endif /*__MODEL_H */
