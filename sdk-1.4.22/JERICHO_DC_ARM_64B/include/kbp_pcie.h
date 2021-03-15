/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_PCIE_H
#define __KBP_PCIE_H

#include <stdint.h>

#include "errors.h"
#include "init.h"
#include "allocator.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Opaque user handle to the search result returned by the instruction search.
 */

struct kbp_search_result;

/**
 * Properties that can be set with kbp_pcie_set_property()
 */
enum kbp_pcie_properties {
    KBP_PCIE_NON_DMA,            /**< Enable NON DMA mode */
    KBP_PCIE_VERBOSE_LEVEL,      /**< Set Vebose Level */
    KBP_PCIE_NEED_RESPONSE,      /**< Wait for response */
    KBP_PCIE_INTERRUPT,          /**< If called pass the signal number to raise interrupt against */
    KBP_PCIE_REPLACE_SEARCH,     /**< To replace the PCIe search path */
    KBP_PCIE_SAT_BUS_DELAY,      /**< Delay in micro seconds */
    KBP_PCIE_PROP_INVALID        /**< Invalid. This should be the last entry */
};

/**
 * PCIE advanced Settings
 */

struct kbp_pcie_settings
{
    uint32_t req_q_size;   /**< DMA request buffer size 0x1 - 0xd */
    uint32_t resp_q_size;  /**< DMA response buffer size 0x1 - 0xd */
};

/**
 * Properties to tailor the transport layer. Supported properties
 * are defined in ::kbp_pcie_properties
 *
 * |PROPERTY|VALUES|DEFAULT|
 * |:---:|:---:|:---:|
 * |KBP_PCIE_NON_DMA| Use non-DMA mode of comunication | False. Default is DMA enabled |
 * |KBP_PCIE_VERBOSE_LEVEL| Enable verbose printing to stdout | Default zero |
 * |KBP_PCIE_NEED_RESPONSE| Request response for every update | Default only reads/compares get responses |
 * |KBP_PCIE_INTERRUPT|Provide signal number to interrupt against. Enables MSI based interrupts|Disabled by default|
 * |KBP_PCIE_REPLACE_SEARCH| To replace the PCIe search path
 *
 * @param xpt pointer to the transport layer initialized by the function on success
 * @param ... variable arguments related to the property
 *
 * @returns KBP_OK on success or an error code
 */

kbp_status kbp_pcie_set_property(void *xpt, enum kbp_pcie_properties property, ...);

/**
 * Initialize the PCIe Driver and return transport layer handle
 *
 * @param type The device type. Currently only suported device is KBP_DEVICE_OP
 * @param flags The device configuration flags
 * @param device_no The device number on the board to connect to
 * @param alloc valid allocator handle
 * @param config Optional parameter if passed in the MDIO read/write callback function are populated
 * @param driver_settings Optional parameters required to configure the PCIe
 * @param xpt pointer to the transport layer initialized by the function on success
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_init(enum kbp_device_type type, uint32_t flags, uint32_t device_no, struct kbp_allocator *alloc,
                         struct kbp_device_config *config, struct kbp_pcie_settings *driver_settings,
                         void **xpt);

/**
 * Destroy the resources allocated for the pcie Driver
 *
 * @param alloc valid allocator handle
 * @param xpt valid initialized transport layer handle returned by kbp_op_pcie_init()
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_destroy(struct kbp_allocator *alloc, void *xpt);

/**
 * PCIe soft reset reset
 *
 * @param xpt pointer to the op_xpt struct that contains the
 *            handle pointer
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_soft_reset(void *xpt);

/**
* Property to replace the PCIe search path.
*
* @param handle pointer to the search handle
* @param ltr ltr number
* @param ctx context id
* @param key pointer to the search key
* @param key_len search key length
* @param result pointer to the search result structure
* @return KBP_OK on success or an error code
*/

typedef kbp_status (*kbp_op_search)(void *handle, uint32_t ltr, uint32_t ctx,
                                    const uint8_t *key, uint32_t key_len,
                                    struct kbp_search_result *result);

#ifdef __cplusplus
}
#endif
#endif /*__KBP_PCIE_H */

