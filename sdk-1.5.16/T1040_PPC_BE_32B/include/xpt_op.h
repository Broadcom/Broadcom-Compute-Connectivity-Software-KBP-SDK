/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __XPT_OP_H
#define __XPT_OP_H

#include <stdint.h>
#include <stdio.h>

#include "errors.h"
#include "allocator.h"


#ifdef __cplusplus
extern "C" {
#endif

/** The opcode of register/database_entry/UDA write through
 *  PCIE and ILA */
#define KBP_OPCODE_WRITE_LOW         (0x1)
#define KBP_OPCODE_READX_LOW         (0x2)
#define KBP_OPCODE_READY_LOW         (0x3)
#define KBP_OPCODE_FREADX_LOW        (0x4)

#define KBP_OPCODE_WRITE_READ_X_Y_HIGH       (0x0)

/** The opcode of various compare request through PCIE and
 *  ILA */
#define KBP_OPCODE_CMP1_HIGH        (0x1)
#define KBP_OPCODE_CMP2_HIGH        (0x2)
#define KBP_OPCODE_STAT_COUNT       (0x3)
#define KBP_OPCODE_CBW_HIGH         (0x4)
#define KBP_OPCODE_CBWLPM_HIGH      (0x5)
#define KBP_OPCODE_CBNWCMP_HIGH     (0x6)
#define KBP_OPCODE_NCBCMP_HIGH      (0x7)

/** The opcode of Bulk instructions */
#define KBP_OPCODE_BULK_READ        (0x6)
#define KBP_OPCODE_BULK_WRITE       (0x7)
/** The opcode of block instructions */
#define KBP_OPCODE_BLKCP            (0x8)
#define KBP_OPCODE_BLKMV            (0x9)
#define KBP_OPCODE_BLKCLR           (0xa)
#define KBP_OPCODE_BLKINV           (0xb)

#define KBP_COMMAND_OPCODE          (0x20)


/**
 * @file xpt_op.h
 *
 * Transport layer implementation for Optimus Prime
 */
struct kbp_search_result;

/**
 * @brief Transport layer interface for Optimus Prime
 */

struct op_xpt {
    uint32_t device_type;              /**< The device type. Should always be the first member of the structure */
    void *handle;                      /**< The actual handle passed to APIs below */
    void *search_handle;               /**< The handle to be passed to the search function.
                                            This is same as the handle, unless the search path is overridden by KBP_PCIE_REPLACE_SEARCH property */
    struct kbp_allocator *alloc;       /**< Allocator handle */


    /**
     * Generic device register write function
     *
     * @param handle Opaque user handle
     * @param address the device address to write
     * @param data the register contents. Must be 80b wide

     * @return KBP_OK if successfully dispatched to device
     */

    kbp_status (*op_write_reg)(void *handle, uint32_t address, const uint8_t *data, uint32_t core_bitmap);

    /**
     * Generic device register read function
     *
     * @param handle Opaque user handle
     * @param address the device address to write
     * @param data the register contents read into. Must be 80b wide

     * @return KBP_OK if successfully read back, and data is valid
     */

    kbp_status (*op_read_reg)(void *handle, uint32_t address, uint8_t *data, uint32_t core_bitmap);

    /**
     * Generic DBA write function
     *
     * @param handle Opaque user handle
     * @param address the DBA address to write
     * @param data the 80b of data
     * @param mask the 80b of mask
     * @param is_xy whether the data/mask is in DM mode or in XY mode
     * @param valid_bit whether to set the valid bit on the entry or not
     *
     * @return KBP_OK if successfully dispatched to device
     */

    kbp_status (*op_write_dba_entry)(void *handle, uint32_t address, const uint8_t *data,
                                     const uint8_t *mask, uint32_t is_xy, uint32_t valid_bit, uint32_t core_bitmap);
    /**
     * Generic DBA read function
     *
     * @param handle Opaque user handle
     * @param address the DBA address to read
     * @param read_x_or_y read the X/Y part of the DBA record
     * @param entry_x_or_y returned data which contains the X/Y depending on request
     * @param valid_bit returned whether the valid bit was set or not
     *
     * @return KBP_OK if successfully read back and the entry and valid bit contents are usable
     */

    kbp_status (*op_read_dba_entry)(void *handle, uint32_t address, uint32_t read_x_or_y,
                                    uint8_t *entry_x_or_y, uint32_t *valid_bit, uint32_t *parity, uint32_t core_bitmap);

    /**
     * Writes 64 aligned bits to UDA using AD-compatible 32-bit-granular addressing
     *
     * @param handle Opaque user handle
     * @param address_32 the 32b granular UDA address
     * @param is_uda_64b 1: 64b value, 0: 32b value
     * @param value the 64b value to write
     *
     * @return KBP_OK if successfully dispatched to device
     */

    kbp_status (*op_write_uda)(void *handle, uint32_t address_32, uint8_t is_uda_64b, uint64_t value, uint32_t core_bitmap);

    /**
     * Read 64 aligned bits to UDA using AD-compatible 32-bit-granular addressing
     *
     * @param handle Opaque user handle
     * @param address_32 the 32b granular UDA address
     * @param is_uda_64b 1: 64b value, 0: 32b value
     * @param value the 64b value read back
     *
     * @return KBP_OK if successfully read from device and value is valid
     */

    kbp_status (*op_read_uda)(void *handle, uint32_t address_32, uint8_t is_uda_64b, uint64_t *value, uint32_t core_bitmap);

    /**
     * Function to send various private commands to KBP
     *
     * @param handle Opaque user handle
     * @param opcode, opcode for the instruction
     * @param nbytes the number of bytes in payload
     * @param bytes the payload
     *
     * @return KBP_OK if successfully dispatched to device
     */

    kbp_status (*op_kbp_command)(void *handle, uint32_t opcode, uint32_t nbytes, uint8_t *bytes, uint32_t core_bitmap);

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

    /**
     * Control plane based search function. A single search key can
     * be sent from either thread to produce the expected result
     *
     * @param handle Opaque user handle
     * @param ltr The LTR to search
     * @param ctx The context buffer ID to use
     * @param key The master key bytes
     * @param key_len The number of valid bytes in key
     * @param result if AD is expected, fill the expected response type default is KBP_INDEX_AND_NO_AD
     *        and get the expected the results
     *
     * @return KBP_OK on successful completion of call and result contents are valid. Or an error code
     */

    kbp_status (*op_search)(void *handle, uint32_t ltr, uint32_t ctx,
                            const uint8_t *key, uint32_t key_len,
                            struct kbp_search_result *result);

    /**
     * SW Resets
     *
     * @param device_type 3: KBP_DEVICE_OP2, Only OP2 is supported
     * @param handle Opaque user handle
     * @param rest_type 0:SRST, 1:CRST, 2:Disable Stats counter dynamic eviction
     *                  3:Disable Response fifo Flow Control to EMC
     *                  4:Port Macro0 Reset 5:Port Macro1 Reset
     *                  6:Soft Reset 7:DMA Reset
     *
     * @return KBP_OK on successful completion of call
     */

    kbp_status (*sw_reset)(uint32_t device_type, void *handle, uint32_t reset_type);

    /**
     * External MDIO read function.
     * Implemented by the user. Returns a 16b read value as part of the last argument
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

    int32_t (*ext_mdio_read)(void *handle, int32_t chip_no, uint8_t dev, uint16_t reg, uint16_t *value);

    /**
     * External MDIO write function. Implemented by the user. Writes a 16b value to the specified MDIO register
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

    int32_t (*ext_mdio_write)(void *handle, int32_t chip_no, uint8_t dev, uint16_t reg, uint16_t value);

    FILE *debug_fp;                         /**< File to log debug dump */
    uint8_t device_number;                  /**< Device Number */
    int32_t misc_flag;                      /* MISC Flag for internal use */
};

#ifdef __cplusplus
}
#endif
#endif /*__XPT_OP_H */
