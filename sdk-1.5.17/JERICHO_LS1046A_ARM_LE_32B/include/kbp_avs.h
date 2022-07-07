/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_AVS_H
#define __KBP_AVS_H

/**
 * @file kbp_avs.h
 *
 * This module is to find AVS convergence voltage.
 */

#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Default VMAX, VMIN values
 */
#define DEFAULT_VMAX_AVS    (920)
#define DEFAULT_VMIN_AVS    (750)

/**
 * AVS configuration structure
 */

struct kbp_avs_config
{
    void *handle;                    /**< Opaque handle passed to MDIO reset routines as first argument. */

    /**
     * MDIO read function. Implemented by the user. Returns a 16b read value as part of the last argument
     *
     * @param handle Opaque user provided handle passed to the callback.
     * @param chip_no Virtual chip number to address the device on cascade. The user is responsible to translate to the real MPID select.
     * @param dev The MDIO device ID.
     * @param reg The MDIO register to be read.
     * @param value Returned by the call. Valid if function returns zero
     *
     * @retval 0 On success, the contents of value are valid
     * @retval non-zero On failure. The contents of value are ignored.
     */

    int32_t (*mdio_read)(void *handle, int32_t chip_no, uint8_t dev, uint16_t reg, uint16_t *value);

    /**
     * MDIO write function. Implemented by the user. Writes a 16b value to the specified MDIO register
     *
     * @param handle Opaque user provided handle passed to the callback.
     * @param chip_no Virtual chip number to address the device on cascade. The user is responsible to translate to the real MPID select.
     * @param dev The MDIO device ID.
     * @param reg The MDIO register to write to.
     * @param value The value to write to the register.
     *
     * @retval 0 On success, the value has been written.
     * @retval non-zero On failure. Value could not be written to the register.
     */

    int32_t (*mdio_write)(void *handle, int32_t chip_no, uint8_t dev, uint16_t reg, uint16_t value);

    int32_t max_avs_voltage; /**< Upper limit for die convergence voltage */
    int32_t min_avs_voltage; /**< Lower limit for die convergence voltage */
};

/**
 * Find out the AVS convergence voltage
 *
 * @param device Valid device handle.
 * @param vmax Maximum voltage limit
 * @param vmin Minimum voltage limit
 * @param fp file to log the dump
 * @return KBP_OK on success or an error code otherwise
 *
 */
kbp_status kbp_device_init_avs(struct kbp_device *device, int32_t vmax, int32_t vmin, FILE *fp);

/**
 * Find out the AVS convergence voltage
 * Expected S_RST and C_SRT are already deasserted or device interface init is called
 * before calling this API
 *
 * @param type The device type, currently only Optimus Prime is supported
 * @param config Interface configuration structure initialized correctly
 * @param fp file to log the dump
 *
 * @retval KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_interface_init_avs(enum kbp_device_type type, struct kbp_avs_config *config,
                                         FILE *fp);

/**
 * Find out if the AVS is enabled or not
 *
 * @param type The device type, currently only Optimus Prime is supported
 * @param config Interface configuration structure initialized correctly
 * @param is_enabled set to 1 if AVS is enabled else to 0
 *
 * @retval KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_interface_is_avs_enabled(enum kbp_device_type type, struct kbp_avs_config *config,
                                               uint32_t *is_enabled);

#ifdef __cplusplus
}
#endif
#endif /*__KBP_AVS_H */
