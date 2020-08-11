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

/**
 * @file kbp_pcie.h
 *
 * This module provides the pcie interface configuration and initialization code.
 */

#include <stdint.h>

#include "errors.h"
#include "init.h"
#include "allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DEVICE_PCIE_INTERFACE_APIS
 * @{
 */

/**
 * @brief Opaque user handle to the search result returned by the instruction search.
 */

struct kbp_search_result;

/**
 * Properties that can be set with kbp_pcie_set_property()
 */
enum kbp_pcie_properties {
    KBP_PCIE_NON_DMA,            /**< Enable Non-DMA mode */
    KBP_PCIE_VERBOSE_LEVEL,      /**< Set verbose level */
    KBP_PCIE_NEED_RESPONSE,      /**< Wait for response */
    KBP_PCIE_INTERRUPT,          /**< If called pass the signal number to raise interrupt against */
    KBP_PCIE_REPLACE_SEARCH,     /**< To replace the PCIe search path */
    KBP_PCIE_PROP_INVALID        /**< Invalid. This should be the last entry */
};

/**
 * Resets/Disable through PCIe.
 * ORed together to do multiple types of resets/disable to the device.
 *
 * Currently only supported device is KBP_DEVICE_OP2.
 */

enum kbp_pcie_reset_type {
    KBP_PCIE_SW_SRST,           /**< SRST */
    KBP_PCIE_SW_CRST,           /**< CRST */
    KBP_PCIE_SW_DIS_EVIC,       /**< Disable Stats counter dynamic eviction */
    KBP_PCIE_SW_DIS_RSPF_FC,    /**< Disable Response fifo Flow Control to EMC. */
    KBP_PCIE_PM0_SW_SRST,       /**< Port Macro0 Reset */
    KBP_PCIE_PM1_SW_SRST,       /**< Port Macro1 Reset */
    KBP_PCIE_SOFT_SRST,         /**< Soft Reset */
    KBP_PCIE_DMA_RST,           /**< DMA Reset */
    KBP_PCIE_RST_INVALID        /**< Invalid */
};

/**
 * PCIE advanced settings
 */

struct kbp_pcie_settings {
    uint32_t req_q_size;      /**< DMA request buffer size 0x1 - 0xd */
    uint32_t resp_q_size[5];  /**< DMA response buffer size 0x1 - 0xd */
};

/**
 * Properties to tailor the transport layer. Supported properties
 * are defined in ::kbp_pcie_properties
 *
 * |PROPERTY|VALUES|DEFAULT|
 * |:---:|:---:|:---:|
 * |KBP_PCIE_NON_DMA| Use non-DMA mode of communication | False. Default is DMA enabled |
 * |KBP_PCIE_VERBOSE_LEVEL| Enable verbose printing to stdout | Default zero |
 * |KBP_PCIE_NEED_RESPONSE| Request response for every update | Default only reads/compares get responses |
 * |KBP_PCIE_INTERRUPT|Provide signal number to interrupt against. Enables MSI based interrupts|Disabled by default|
 * |KBP_PCIE_REPLACE_SEARCH| To replace the PCIe search path
 *
 * @param xpt Pointer to the transport layer initialized by the function on success
 * @param property PCIe property to be set
 * @param ... Variable arguments related to the property
 *
 * @returns KBP_OK on success or an error code
 */

kbp_status kbp_pcie_set_property(void *xpt, enum kbp_pcie_properties property, ...);

/**
 * Initialize the PCIe driver and return transport layer handle.
 *
 * @param type The device type. Currently only supported device types are KBP_DEVICE_OP and KBP_DEVICE_OP2
 * @param flags The device configuration flags
 * @param device_no The device number on the board to connect to
 * @param alloc Valid allocator handle
 * @param config Optional parameter if passed in the MDIO read/write callback functions are populated
 * @param driver_settings Optional parameters required to configure the PCIe
 * @param xpt Pointer to the transport layer initialized by the function on success
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_init(enum kbp_device_type type, uint32_t flags, uint32_t device_no, struct kbp_allocator *alloc,
                         struct kbp_device_config *config, struct kbp_pcie_settings *driver_settings,
                         void **xpt);

/**
 * Destroy the resources allocated for the PCIe driver.
 *
 * @param alloc Valid allocator handle
 * @param xpt Valid initialized transport layer handle returned by kbp_pcie_init()
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_destroy(struct kbp_allocator *alloc, void *xpt);

/**
 * Do PCIe soft reset.
 *
 * @param xpt Pointer to the op_xpt struct that contains the
 *            handle pointer
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_soft_reset(void *xpt);

/**
* Property to replace the PCIe search path.
*
* @param handle Pointer to the search handle
* @param ltr LTR number
* @param ctx Context id
* @param key Pointer to the search key
* @param key_len Search key length
* @param result Pointer to the search result structure
* @return KBP_OK on success or an error code
*/

typedef kbp_status (*kbp_op_search) (void *handle, uint32_t ltr, uint32_t ctx,
                                     const uint8_t *key, uint32_t key_len,
                                     struct kbp_search_result *result);


/**
 * SRST, CRST, PM Reset through PCIe
 *
 * @param type The device type. Currently only supported device is KBP_DEVICE_OP2
 * @param xpt Valid xpt handle
 * @param reset_type Reset Type
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_reset(enum kbp_device_type type, void *xpt, enum kbp_pcie_reset_type reset_type);

/**
 * PCIe-SAT Read function to read SAT/MDIO register through PCIe-SAT BUS Path
 *
 * @param xpt Valid xpt handle
 * @param size Register size. Valid sizes are 16, 64 and 80
 * @param addr Address of the register
 * @param data Pointer to read data
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_sat_bus_read(void *xpt, uint32_t size, uint32_t addr, uint8_t *data);

/**
 * PCIe-SAT Write function to write SAT/MDIO register through PCIe-SAT BUS Path
 *
 * @param xpt Valid xpt handle
 * @param size Register size. Valid sizes are 16, 64 and 80
 * @param base_addr Address of the register
 * @param data Data to write
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_pcie_sat_bus_write(void *xpt, uint32_t size, uint32_t base_addr, uint8_t *data);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*__KBP_PCIE_H */

