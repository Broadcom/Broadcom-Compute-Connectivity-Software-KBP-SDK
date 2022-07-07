/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_MEM_TEST_H
#define __KBP_MEM_TEST_H

/* include header */
#include "kbp_portable.h"
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

struct kbp_mem_test_info {
    uint32_t debug_prints; /**< enable debug prints. */
    void *handle;          /**< Opaque handle passed to MDIO reset routines as first argument. */

    uint64_t test_duration_in_usec;  /**< time duration in microseconds (1e-6) for each pass of a test pattern */
    uint32_t modified_addr_length;   /**< length of array to store addresses. additional addresses will not be 
                                         recorded if all array entries are used */
    uint32_t modified_addr_count;    /**< record number of address entries */
    uint32_t *modified_addr;         /**< pointer to an array to store failed addresses */

    uint32_t inject_error_addr_length; /**< length of array containing addresses to inject error */
    uint32_t *inject_error_addr;      /**< pointer to an array containing addresses to inject error */

    /* callback for the delay, implemented by the application */
    kbp_status (*kbp_mem_test_usleep)(void *handle, uint64_t);

    /* callback for write to KBP 80-bit MDIO registers, implemented by the application */
    kbp_status (*kbp_mdio_register_write_80)(void *handle, uint8_t kbp_select, uint8_t device_id, uint16_t addr, uint16_t* wr_data);

    /* callback for read KBP 80-bit MDIO registers, implemented by the application */
    kbp_status (*kbp_mdio_register_read_80)(void *handle, uint8_t kbp_select, uint8_t device_id, uint16_t addr, uint16_t* rd_data);

    /* callback for write to KBP 64-bit MDIO registers, implemented by the application */
    kbp_status (*kbp_mdio_register_write_64)(void *handle, uint8_t kbp_select, uint8_t device_id, uint16_t addr, uint16_t* wr_data);

    /* callback for read KBP 64-bit MDIO registers, implemented by the application */
    kbp_status (*kbp_mdio_register_read_64)(void *handle, uint8_t kbp_select, uint8_t device_id, uint16_t addr, uint16_t* rd_data);
};

/**
 * @brief test X, Y and valid bit for each database entry (Error Injection and Detection)
 *
 * @param [in] device - valid KBP device handle
 * @param info Opaque user provided handle passed to the callback, with additional information.
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_dba(struct kbp_device *device, struct kbp_mem_test_info *info);


/**
 * @brief test to test user data array (Error Injection and Detection)
 *
 * @param [in] device - valid KBP device handle
 * @param info Opaque user provided handle passed to the callback, with additional information.
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_uda(struct kbp_device *device, struct kbp_mem_test_info *info);

/**
 * @brief test to test R-Block memory area (Error Injection and Detection)
 *
 * @param [in] device - valid KBP device handle
 * @param info Opaque user provided handle passed to the callback, with additional information.
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_rblock(struct kbp_device *device, struct kbp_mem_test_info *info);

/**
 * @brief test to test U-Block register area (Error Injection and Detection)
 *
 * @param [in] device - valid KBP device handle
 * @param info Opaque user provided handle passed to the callback, with additional information.
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_ublock(struct kbp_device *device, struct kbp_mem_test_info *info);


/**
 * @brief test to test full chip for DBA of the device
 *
 * @param [in] device  - valid KBP device handle
 * @param debug_prints - debug prints 0 disable, 1 enable
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_rw_dba(struct kbp_device *device, uint32_t debug_prints);


/**
 * @brief test to test full chip for UDA of the device
 *
 * @param [in] device - valid KBP device handle
 * @param debug_prints - debug prints 0 disable, 1 enable
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_rw_uda(struct kbp_device *device, uint32_t debug_prints);


/**
 * @brief test to test full internal blocks of the device
 *
 * @param [in] device - valid KBP device handle
 * @param debug_prints - debug prints 0 disable, 1 enable
 *
 * @return KBP_OK on success or an error code
 */
kbp_status kbp_mem_test_rw_advance( struct kbp_device *device, uint32_t debug_prints);
kbp_status kbp_mem_test_rw_rblock(struct kbp_device *device, uint32_t debug_prints);
kbp_status kbp_mem_test_rw_ublock(struct kbp_device *device, uint32_t debug_prints);
kbp_status kbp_mem_test_rw_pblock(struct kbp_device *device, uint32_t debug_prints);
kbp_status kbp_mem_test_rw_ctx_buffer(struct kbp_device *device, uint32_t debug_prints);
kbp_status kbp_mem_test_rw_ltr(struct kbp_device *device, uint32_t debug_prints);

#ifdef __cplusplus
}
#endif

#endif /* __KBP_MEM_TEST_H */

