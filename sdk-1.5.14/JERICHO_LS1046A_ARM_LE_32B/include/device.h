/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DEVICE_H
#define __DEVICE_H

/**
 * @file device.h
 *
 * This module provides the hardware-abstraction layer (HAL)
 * for the user.
 */

#include <stdint.h>
#include <stdio.h>

#include "errors.h"
#include "init.h"
#include "hw_limits.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
 * @addtogroup DEVICE_API
 * @{
 */

/**
 * Opaque KBP device handle.
 */

struct kbp_device;

/**
 * Opaque allocator handle.
 */

struct kbp_allocator;

/**
 * Opaque user handle to the database stored in the KBP.
 */

struct kbp_db;

/**
 * Opaque handle to an entry within a database.
 */

struct kbp_entry;

/**
 * Opaque handles for algo use
 */
struct kbp_stats_db;

/**
 * KBP SDK version string.
 */

#define KBP_SDK_VERSION "KBP SDK 1.5.14"

/**
 * KBP Error List Version number.
 */
#define KBP_ERROR_LIST_VERSION (2)

/*#define BRCM_FIX_ERR_DBG_PRINTS*/


/**
 * Type of databases supported by software.
 */

enum kbp_db_type {
    KBP_DB_INVALID, /**< Error database type. */
    KBP_DB_ACL,     /**< Algorithmic and non-algorithmic ACL databases. */
    KBP_DB_LPM,     /**< Longest-prefix-match databases. */
    KBP_DB_EM,      /**< Exact-match databases. */
    KBP_DB_AD,      /**< Associated data databases. */
    KBP_DB_DMA,     /**< Direct Memory Access databases. */
    KBP_DB_HB,      /**< Hit Bits databases. */
    KBP_DB_COUNTER, /**< Search-dependent-Counter databases */
    KBP_DB_TAP,     /**< TAP databases */
    KBP_DB_END      /**< This should be the last entry. */
};

/**
 * @brief Hardware resources that can be partitioned
 *
 * The available hardware resources that can be partitioned between databases. The following functions
 * can be invoked with the hardware resources to limit the databases to use
 * the specified resources only:
 *
 * @li kbp_db_set_resource()
 * @li kbp_ad_db_set_resource()
 *
 * can be invoked with the HW resources to limit the databases to use
 * the specified resources only. Optionally, the resource compiler can
 * be used to automatically assign hardware resources to the various databases
 * and functions. For LPM only databases, the database handle must be used to
 * set both UDA and DBA. For all other databases, the
 * database handle is used to set DBA, and the AD Database handle
 * is used to set UDA
 *
 * | RESOURCE | NUMBER OF ARGS | ARGUMENTS |
 * |:---: | :---: | :---: |
 * | KBP_HW_RESOURCE_DBA | 1 | uint32_t value specifying the number of ABs to use (for LPM, EM, ACL databases). |
 * | KBP_HW_RESOURCE_UDA | 1 | uint32_t value specifying the UDA in megabits (for algorithmic LPM, EM, ACL databases and for AD databases). |
 * | KBP_HW_RESOURCE_RANGE_UNITS | 1 | uint32_t value specifying the number of range units to use for MCOR/DIRPE (ACL databases only). |
 */

enum kbp_hw_resource {
    KBP_HW_RESOURCE_DBA,  /**< The number of ABs to use. */
    KBP_HW_RESOURCE_UDA,  /**< The UDA in megabits. */
    KBP_HW_RESOURCE_DBA_CORE,  /**< The number of ABs to use. */
    KBP_HW_RESOURCE_UDA_CORE,  /**< The UDA in megabits. */
    KBP_HW_RESOURCE_RANGE_UNITS, /**< The number of range units to use. */
    KBP_HW_RESOURCE_INVALID      /**< This should be the last entry. */
};


/**
 * @brief Specifies the range encoding types supported
 */
enum kbp_range_encoding_type {
    KBP_RANGE_3B_ENCODING,  /**< 2 bit to 3 bit encoding usually configured to DIRPE */
    KBP_RANGE_2B_ENCODING,  /**< 2 bit to 2 bit encoding */
    KBP_RANGE_NO_ENCODING   /**< No encoding */
};

/**
 * @brief The list of flags to control the level of device flush
 */
enum kbp_device_flush_flags {
    KBP_DEVICE_FLUSH_DEVICE_RESET = 1,      /**< Reset the device (resets the LTRs, that are being used) */
    KBP_DEVICE_FLUSH_DEVICE_HARD_RESET = 2, /**< Hard reset (resets all the LTRs) */
    KBP_DEVICE_FLUSH_CONFIG_RESOURCE = 4,   /**< Configures the resource: AB, UDA, range, LPT, etc. */
    KBP_DEVICE_FLUSH_ENTRIES = 8,           /**< Flush the entries */
    KBP_DEVICE_FLUSH_LTRS = 16,             /**< Flush the LTRs */
    KBP_DEVICE_FLUSH_PARALLEL = 32          /**< Enables parallel flush, to flush entries and LTRs of that SMT handle */
};

/**
 * @brief The list of error types (w.r.t memory modules)
 */
enum kbp_device_parity_inject_type {
    KBP_DBA_ERR_INJECT,     /* for DBA */
    KBP_UDA_ERR_INJECT,     /* for UDA */
    KBP_UIT_ERR_INJECT,     /* for UDR/UIT */
    KBP_RPT_ERR_INJECT,     /* for Advance DBA */
    KBP_ERR_INJECT_END
};

/*#define BRCM_DBG_PRINTS*/


#define EMU_CORE_CLEAR_BIT(value, reg, bit)                         \
    if (value) {                                                    \
        reg &= ~ (1ULL << bit);                                     \
    }

#define EMU_INTF_CLEAR_BIT(val1, val2, val3, val4, reg, bit)        \
{                                                                   \
    if (val1)                                                       \
        reg &= ~(1ULL << bit);                                      \
    if (val2)                                                       \
        reg &= ~(1ULL << (bit + 16));                               \
    if (val3)                                                       \
        reg &= ~(1ULL << (bit + 32));                               \
    if (val4)                                                       \
        reg &= ~(1ULL << (bit + 48));                               \
}

#define CORE_SET_BIT(value, reg, bit)                               \
    if (value) {                                                    \
        reg |= (1ULL << bit);                                       \
    }

#define CORE_SET_VALUE(value, reg, bit)                             \
    if ((reg >> bit) & 1ULL) {                                      \
        value = 1;                                                  \
    }


#define INTF_SET_BIT(val1, val2, val3, val4, reg, bit)              \
{                                                                   \
    if (val1)                                                       \
        reg |= (1ULL << bit);                                       \
    if (val2)                                                       \
        reg |= (1ULL << (bit + 16));                                \
    if (val3)                                                       \
        reg |= (1ULL << (bit + 32));                                \
    if (val4)                                                       \
        reg |= (1ULL << (bit + 48));                                \
}

#define INTF_CHECK_AND_SET_BIT(val1, val2, val3, val4, reg, bit)    \
{                                                                   \
    if (val1 || val2 || val3 || val4)                               \
        reg |= (1ULL << bit);                                       \
}

#define INTF_CHECK_AND_SET_BIT_2(val1, val2, val3, val4, reg, op2, bit)     \
{                                                                           \
    if (val1 || val2 || val3 || val4) {                                     \
        if (op2)                                                          \
            reg |= (1ULL << bit);                                           \
        else                                                                \
            reg |= (1ULL << (bit + 2));                                     \
    }                                                                       \
}

/**
 * @brief The list of error types:
 *
 * used with kbp_device_inject_errors() as input parameter to Inject/Emulate the error/s
 * used with kbp_device_get_errors() as output parameter to get the ESR status
 */

struct kbp_status_errors {

    /* Memory errors */
    uint8_t dba_soft_error; //1         bit 48, 49
    uint8_t uda_soft_error; //2         bit 47 (W1C), 52, 56
    uint8_t uit_soft_error; //3         bit 43 (W1C), 53
    uint8_t rpt_soft_error; //4         bit 50, 51

    /* interface errors. */
    uint8_t intf0_host_transmit;        //5         bit 15 (W1C)                      [OP: 17]
    uint8_t intf0_host_receive;         //          bit 14 (W1C),   bits 12: 13 res   [OP: 16]
    uint8_t intf0_instr_len_receive;    //          bit 11 (W1C)
    uint8_t intf0_illegal_instr;        //          bit 10 (W1C)
    uint8_t intf0_eop_receive_1;        //          bit 9  (W1C)
    uint8_t intf0_burst_max;            //          bit 8  (W1C)
    uint8_t intf0_burst_short;          //          bit 7  (W1C)
    uint8_t intf0_protocol;             //          bit 6  (W1C)
    uint8_t intf0_start_of_packet;      //          bit 5  (W1C)
    uint8_t intf0_mac_fifo_parity;      //          bit 4  (W1C)
    uint8_t intf0_eop_receive_2;        //          bit 3  (W1C)
    uint8_t intf0_framing;              //          bit 2  (W1C)
    uint8_t intf0_crc24;                //17        bit 1  (W1C), bit 0 res

    uint8_t intf1_host_transmit;        //18
    uint8_t intf1_host_receive;
    uint8_t intf1_instr_len_receive;
    uint8_t intf1_illegal_instr;
    uint8_t intf1_eop_receive_1;
    uint8_t intf1_burst_max;
    uint8_t intf1_burst_short;
    uint8_t intf1_protocol;
    uint8_t intf1_start_of_packet;
    uint8_t intf1_mac_fifo_parity;
    uint8_t intf1_eop_receive_2;
    uint8_t intf1_framing;
    uint8_t intf1_crc24;                //30

    uint8_t intf2_host_transmit;        //31
    uint8_t intf2_host_receive;
    uint8_t intf2_instr_len_receive;
    uint8_t intf2_illegal_instr;
    uint8_t intf2_eop_receive_1;
    uint8_t intf2_burst_max;
    uint8_t intf2_burst_short;
    uint8_t intf2_protocol;
    uint8_t intf2_start_of_packet;
    uint8_t intf2_mac_fifo_parity;
    uint8_t intf2_eop_receive_2;
    uint8_t intf2_framing;
    uint8_t intf2_crc24;                //43

    uint8_t intf3_host_transmit;        //44
    uint8_t intf3_host_receive;
    uint8_t intf3_instr_len_receive;
    uint8_t intf3_illegal_instr;
    uint8_t intf3_eop_receive_1;
    uint8_t intf3_burst_max;
    uint8_t intf3_burst_short;
    uint8_t intf3_protocol;
    uint8_t intf3_start_of_packet;
    uint8_t intf3_mac_fifo_parity;
    uint8_t intf3_eop_receive_2;
    uint8_t intf3_framing;
    uint8_t intf3_crc24;                //56

    /* other core bits */
    uint8_t rcb2emc_resp_fifo_err;       //57       bit 23 [W1C],  bit 16-22 res
    uint8_t pci_req_fifo_err;            //         bit 24 [W1C]
    uint8_t cmp_with_no_rslt;            //         bit 25 [W1C],  bit 26, 27, 28 res
    uint8_t stats_non_pkt_err;           //         bit 29
    uint8_t stats_rec_extract_pkt_err;   //         bit 30 [W1C]
    uint8_t stats_cmd_extract_pkt_err;   //         bit 31 [W1C]
    uint8_t err_in_req_inst_to_cpu;      //         bit 32 [W1C]
    uint8_t prosr_area_pio_resp_fifo_err;//         bit 33 [W1C]
    uint8_t prosr_mem_read_err;          //         bit 34 [W1C]
    uint8_t icb_input_fifo_err;          //         bit 35 [W1C]
    uint8_t power_cntl_mem_par_err;      //         bit 36 [W1C]
    uint8_t key_cntl_ltr_reg_err;        //         bit 37 [W1C]
    uint8_t cb_parity_err;               //         bit 38 [W1C]                    [39 mem errors]
    uint8_t db_intf_ltr_par_err;         //         bit 40 [W1C]
    uint8_t user_data_if_rslt_fifo_err;  //         bit 41 [W1C]
    uint8_t user_data_if_rslt_err;       //         bit 42 [W1C]                    [43 mem errors]
    uint8_t age_hb_or_vbit_mem_par_err_on_read; //  bit 44 [W1C],  bit 45 res
    uint8_t uda_ltr_par_err;             //         bit 46 [W1C]                    [47-53 mem errors]
    uint8_t proc_err_fatal;              //         bit 54
    uint8_t proc_err_non_fatal;          //         bit 55                          [56 mem errors]
    uint8_t arm_attention0;              //         bit 57 [W1C],  bit 58, 59 60, 61 res
    uint8_t block_cmp_timeout;           //         bit 62 [W1C]
    uint8_t type2_otp_ecc_err;           //79       bit 63 [W1C]


    /* Enable Interrupt in PDC */
    uint8_t crb_error_interrupt;         //80
};

/**
 * Initialize the KBP device. A valid transport layer is required.
 * On initialization, the device is dynamically queried to ascertain
 * its capabilities and the resources available.
 *
 * @param alloc Valid non-NULL allocator handle for portability.
 * @param type The device type ::kbp_device_type.
 * @param flags Flags OR'd together that allow the device to be set into specific modes. See ::kbp_device_flags.
 * @param xpt NULL or valid transport layer handle. Transport-layer functions are used to
 *              establish communication with the device.
 * @param config SerDes and lane-configuration information. Can be NULL to indicate the initialization
 *              has already occurred.
 * @param device Device handle initialized and returned on success. This handle can be used to
 *        address the global device.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_init(struct kbp_allocator *alloc, enum kbp_device_type type, uint32_t flags,
                           void *xpt, struct kbp_device_config *config, struct kbp_device **device);

/**
 * Destroys the device handle and frees up resources. The physical
 * device is left undisturbed.
 *
 * @param device The device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_destroy(struct kbp_device *device);

/**
 * Locks the device. Once the device is locked, new databases/instructions
 * cannot be created.
 *
 * @param device Initialized pointer to the device.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_lock(struct kbp_device *device);

/**
 * Crash Recovery Status
 */
enum kbp_restore_status {
    KBP_RESTORE_NO_CHANGE,            /* The SDK was restored with no change in config, no pending actions */
    KBP_RESTORE_CHANGES_COMMITTED,    /* The SDK was restored and the pending actions were committed */
    KBP_RESTORE_CHANGES_ABORTED       /* The SDK was restored and the pending actions were aborted */
};


/**
 * IFSR parity error location status
 */
enum parity_row_status {
    KBP_ROW_INVALID,
    KBP_ROW_UNTOUCHED,          /* this row un-touched neither re-written nor repaired */
    KBP_ROW_RE_WRITE,           /* this row touched and re-written by the internal db's, but not yet repaired */
    KBP_ROW_REPAIRED,           /* this row touched and repaired by the s/w, and not re-written by the internal db's */
    KBP_ROW_REPAIRED_RE_WRITE   /* this row touched and repaired by the s/w, and re-written this location belongs to internal db's */
};


/**
 * Properties that can be set on the device.
 */
enum kbp_device_properties {
    KBP_DEVICE_PROP_DESCRIPTION,                /**< A string description for the device. */
    KBP_DEVICE_PROP_TOTAL_NUM_BB,               /**< Total number of Bucket Blocks. */
    KBP_DEVICE_PROP_RESOURCE_FN,                /**< Callback for resource processing. */
    KBP_DEVICE_PROP_LTR_SM_UPDATE,              /**< LTR Shadow Memory Update. */
    KBP_DEVICE_PROP_INTERRUPT,                  /**< Enable for supported device interrupts */
    KBP_DEVICE_PROP_IFSR_THRESHOLD,             /**< Threshold for initiating a soft repair of DBA */
    KBP_DEVICE_PROP_LAST_PARITY_ERRORS,         /**< Last seen DBA parity error address of specific device [updated by kbp_device_fix_errors] */
    KBP_DEVICE_PROP_LAST_PARITY_ERRORS_STATUS,  /**< Last seen DBA parity error address' status of specific device
                                                     [updated by kbp_device_fix_errors] for the status code refer to the
                                                     enum parity_row_status above */
    KBP_DEVICE_PROP_INJECT_PARITY_ERRORS,       /**< Inject parity errors by using debug regs, few bits in both X,Y row are flipped
                                                     during the PIO writes on the DBA */
    KBP_DEVICE_PROP_NON_REPAIRABLE_ABS,         /**< Once all the redundant rows are used up, AB cannot repaired
                                                     further, this prop will list those ABs on query (DBA) */
    KBP_DEVICE_PROP_READ_TYPE,                  /**< read type, 0: read from SM,
                                                                1: read from device/model,
                                                                2: read from device and compare against SM data
                                                     Note: in blackhole mode read type cannot be other than 0, will return error */
    KBP_DEVICE_PROP_DEBUG_LEVEL,                /**< debug level, default 0, non zero value represents the level of debug prints
                                                     Note: must be set before kbp_device_lock() and debug print APIs must be called after
                                                     the kbp_device_lock() as instruction(s), entries might be in inconsistent state */
    KBP_DEVICE_PROP_INST_LATENCY,               /**< Value between zero/one, two and eight, where the zero(==1) means issue instructions
                                                     that take minimum amount of data bandwidth, and eight means maximum
                                                     update rate, as longer latency control instructions can be issued. */
    KBP_DEVICE_PRE_CLEAR_ABS,                   /**< Clear the ABs at the time of device init */
    KBP_DEVICE_PROP_LAST_UDA_PARITY_ERRORS,     /**< Last seen UDA parity error address of specific device [updated by kbp_device_fix_errors] */
    KBP_DEVICE_ADD_BROADCAST,                   /**< Configures a device as broadcast device */
    KBP_DEVICE_ADD_SELECTIVE_BROADCAST,         /**< Configures a device as a selective broadcast device */
    KBP_DEVICE_BROADCAST_AT_XPT,                /**< If this property is set, then broadcast happens at XPT level,
                                                     else it happens at hardware device driver level */
    KBP_DEVICE_PROP_CRASH_RECOVERY,             /**< Register the NV Read/Write callbacks required to support Crash Recovery */
    KBP_DEVICE_PROP_DEFER_LTR_WRITES,           /**< Defer LTR writes. use it for ISSU */
    KBP_DEVICE_PROP_CLR_DEV_ERR_BITS,           /**< Clears only device error/parity bits, else all bits in ESR : default all*/
    KBP_DEVICE_PROP_DUMP_ON_ASSERT,             /**< Dump software state to a file before asserting */
    KBP_DEVICE_PROP_CLOCK_RATE,                 /**< OP2 specific, set the device clock rate */
    KBP_DEVICE_PROP_ADV_UDA_WRITE,              /**< Enable/Disable advanced UDA write. This is O3S specific, for OP it's the default*/
    KBP_DEVICE_PROP_RETURN_ERROR_ON_ASSERTS,    /**< Return error code on assert hit */
    KBP_DEVICE_PROP_COUNTER_COMPRESSION,        /**< To enable compression on counters */
    KBP_DEVICE_PROP_TAP_NULL_REC_SIZE,          /**< TAP NULL record size */
    KBP_DEVICE_PROP_TAP_INGRESS_REC_SIZE,       /**< TAP Ingress record size */
    KBP_DEVICE_PROP_TAP_EGRESS_REC_SIZE,        /**< TAP Egress record size */
    KBP_DEVICE_PROP_TAP_INGRESS_OPCODE_EXT_START_LOC, /**< Start location of Opcode Extension field for all ingress records */
    KBP_DEVICE_PROP_TAP_EGRESS_OPCODE_EXT_START_LOC, /**< Start location of Opcode Extension field for all egress records */
    KBP_DEVICE_PROP_TAP_INGRESS_OPCODE_EXT_LEN, /**< Number of valid bits for opcode extension field all ingress records */
    KBP_DEVICE_PROP_TAP_EGRESS_OPCODE_EXT_LEN,  /**< Number of valid bits for opcode extension field all egress records */
    KBP_DEVICE_PROP_TAP_RESERVE_UDM,            /**< Reserve a global UDM for all TAP databases */
    KBP_DEVICE_PROP_MIN_RESOURCE,               /**< To enable min resources (low density) module usage */
    KBP_DEVICE_PROP_FORCE_INVALIDATE_LOC,       /**< Forcibly invalidate the parity location belonging to magic db
                                                     (reserved/used by external resource) [used by only kbp_device_fix_errors]*/
    KBP_DEVICE_PROP_HANDLE_INTERFACE_ERRORS,    /**< 0: Disable interface error handling functionality
                                                     in SDK (in case application handling itself)  [default its turn on] */
    KBP_DEVICE_PROP_RESOURCE_PROFILE,                    /**< Set the scenario profile*/
    KBP_DEVICE_PROP_INVALID                     /**< This should be the last entry. */
};

/**
 * Sets a specific property for the device..
 *
 * @param device Valid device handle
 * @param property Device properties ::kbp_device_properties.
 * @param ... Variable arguments based on property.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_set_property(struct kbp_device *device, enum kbp_device_properties property, ...);

/**
 * Gets a specific property of the device.
 *
 * @param device Valid device handle.
 * @param property Device properties being queried ::kbp_device_properties.
 * @param ... Variable arguments based on property.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_get_property(struct kbp_device *device, enum kbp_device_properties property, ...);

/**
 * Obtains the SMT thread device handle. The device must have been initialized in SMT
 * mode. Databases and instructions must be created using the appropriate thread's device
 * handle.
 *
 * @param device Valid device handle returned by kbp_device_init().
 * @param tid The SMT thread ID. Currently supported IDs are zero and one.
 * @param thr_device The thread's device handle returned on success.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_thread_init(struct kbp_device *device, uint32_t tid, struct kbp_device **thr_device);

/**
 * Prints the device information. A visual HTML format with SVG
 * is dumped that works well on Firefox and Chrome browsers only.
 *
 * This function should be called only after the device is locked.
 * Calling on an unlocked device will result in an error being
 * returned and no HTML being generated.
 *
 * @param device Valid KBP device handle.
 * @param fp The file pointer to dump to.
 *
 * @retval KBP_OK On success.
 * @retval KBP_DEVICE_UNLOCKED when called on a device which has not been locked.
 */

kbp_status kbp_device_print_html(struct kbp_device *device, FILE *fp);


/**
 * Prints the current sw state
 *
 * This function should be called only after the device is locked.
 * Calling on an unlocked device will result in an error being
 * returned and no HTML being generated.
 *
 * @param device Valid KBP device handle.
 * @param fp The file pointer to dump to.
 *
 * @retval KBP_OK On success.
 * @retval KBP_DEVICE_UNLOCKED when called on a device which has not been locked.
 */
kbp_status kbp_device_print_sw_state(struct kbp_device * device, FILE * fp);


/**
 * Prints device information in text to the specified file.
 *
 * @param device Valid KBP device handle.
 * @param fp The file pointer to dump to.
 *
 * @retval KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_print(struct kbp_device *device, FILE *fp);

/**
 * Returns the KBP SDK version string which should not be modified and freed
 *
 *
 * @retval KBP SDK version string
 */

const char * kbp_device_get_sdk_version(void);

/**
 * Repair errors on device. The API will read the error status register
 * on all the devices (if cascade is enabled) and correct errors
 * on them if any are present. Currently all correctable errors by SDK are
 * corrected. On successful return errors are fixed if present, or an
 * error code is returned.
 *
 * @param device Valid KBP device handle.
 *
 * @retval KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_fix_errors(struct kbp_device *device);

/**
 * This function inject/emulate a error in the device
 * Non emulation mode supported only for DBA/UDA/UIT memory
 *
 * Note:
 *        Emulation mode supported only with OP2 device
 *
 * @param device valid device handle.
 * @param err valid input structure of type kbp_status_errors to inject/emulate given error type [only one error type should be set per call]
 * @param emulate if set will emulate the error, else error is injected. [supported only for OP2 device]
 *
 * @return KBP_OK On success or an error code otherwise.
 * @return KBP_UNSUPPORTED on fail, if xpt/mdio handles were not set during kbp_device_init().
 * @return KBP_MULTIPLE_ERRORS_SELECTED on fail, if multiple params of the err are set.
 * @return KBP_INVALID_INJECT_TYPE on fail, if none of DBA/UDA/UIT parameters not set.
 *
 */
kbp_status kbp_device_inject_errors(struct kbp_device *device, struct kbp_status_errors *err, uint32_t emulate);

/**
 * Get the current error status in the device.
 *
 * @param device Initialized pointer to the device.
 * @param o_errors filled with the current errors read from the device.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_get_errors(struct kbp_device *device, struct kbp_status_errors *o_errors);

/**
 * This function sets the masks for the errors that will trigger interrupt. each call will overwrite the previous values
 *
 * @param device Initialized pointer to the device.
 * @param en_err valid input structure of type kbp_status_errors to enable the interrupts. setting 1 to an error will trigger the
 *                                             interrupt when error occurs.
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_enable_interrupt(struct kbp_device *device, struct kbp_status_errors *en_err);

/**
 * This function clears the errors in the device.
 *
 * @param device Initialized pointer to the device.
 * @param sel_clr : selective clear, clear error for the bit set, if sel_clr = NULL, clear all error bits
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_clear_errors(struct kbp_device *device, struct kbp_status_errors *sel_clr);

/**
 * Returns the list of error codes for the errors addressed during the last kbp_device_fix_errors() call.
 * This function is for debug purpose only
 *
 * @param device Initialized pointer to the device.
 * @param error_buffer output param to hold the 64bit error codes.
 * @param buffer_size input param, the size of the user allocated buffer (error_buffer).
 * @param filled_count output param, the actual number of error codes filled in the error_buffer.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_get_error_list(struct kbp_device *device, uint64_t *error_buffer, uint32_t buffer_size, uint32_t *filled_count);


/**
 * Configures AC (array column) to bank mapping
 *
 * @param device Valid KBP device handle.
 * @param smt_sb_map bit map for AC to bank mapping.
 *
 * @retval KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_config_smt(struct kbp_device *device, uint16_t smt_sb_map);

/**
 * Application should call this API to scrub the TAP DMA buffer, to
 * refresh TAP Entry Master copy in the host memory. This API can be invoked
 * from a periodic thread context to refresh counter entries in the host memory.
 * This API is useful when there are dynamic evictions with the compressed entries.
 * This API processes both TAP entry evictions and search-dependent-counter entry
 * evictions.
 *
 * @param device Valid device handle
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_scrub_tap_dma_buffer(struct kbp_device *device);

/**
 * @}
 */

/**
 * @addtogroup ISSU_API
 * @{
 */

/**
 * Callback function to read saved state from nonvolatile memory.
 * The user implements this function as specified in the prototype.
 *
 * @param handle Handle passed to API kbp_device_save_state()/ kbp_device_restore_state()
 * @param buffer Valid buffer memory in which to read the data. Only the specified size must be copied, or a buffer overrun can result.
 * @param size The number of bytes to read.
 * @param offset The offset in nonvolatile memory to read from.
 *
 * @retval 0 On success and contents of buffer are valid.
 * @retval Nonzero on failure reading data; buffer contains garbage.
 */
typedef int32_t (*kbp_device_issu_read_fn) (void *handle, uint8_t *buffer, uint32_t size, uint32_t offset);

/**
 * Callback function to write state into nonvolatile memory.
 * The user implements this function as specified in the prototype.
 *
 * @param handle Handle passed to API kbp_device_save_state()/ kbp_device_restore_state()
 * @param buffer Valid buffer memory to take the data from and write into nonvolatile memory.
 * @param size The number of bytes to write.
 * @param offset The offset in the nonvolatile memory to write to.
 *
 * @retval 0 On success and contents of buffer were written out.
 * @retval Nonzero on failure writing data. This result is fatal.
 */
typedef int32_t (*kbp_device_issu_write_fn) (void *handle, uint8_t *buffer, uint32_t size, uint32_t offset);

/**
 * Perform a warm boot/ISSU. Save device state to nonvolatile memory. The
 * user is expected to provide implementations of read/write callbacks.
 * These callbacks are used to write out state into the nonvolatile
 * memory. Once the function is invoked, no further control-plane
 * operations are permitted. API kbp_device_destroy() can be called afterwards
 * to recover control-plane heap resources.
 *
 * @param device Valid device handle.
 * @param read_fn Callback to read data from nonvolatile memory.
 * @param write_fn Callback to write data to nonvolatile memory.
 * @param handle User handle which will be passed back through read_fn and write_fn.
 *
 * @return KBP_OK on success, or an error code otherwise.
 */

kbp_status kbp_device_save_state(struct kbp_device *device, kbp_device_issu_read_fn read_fn, kbp_device_issu_write_fn write_fn, void *handle);

/**
 * Perform a warm boot/ISSU. Save device state to nonvolatile memory. The
 * user is expected to provide implementations of read/write callbacks.
 * These callbacks are used to write out state into the nonvolatile
 * memory. Control plane operations are permitted after invoking this API.
 *
 * @param device Valid device handle.
 * @param read_fn Callback to read data from nonvolatile memory.
 * @param write_fn Callback to write data to nonvolatile memory.
 * @param handle User handle which will be passed back through read_fn and write_fn.
 *
 * @return KBP_OK on success, or an error code otherwise.
 */

kbp_status kbp_device_save_state_and_continue(struct kbp_device *device, kbp_device_issu_read_fn read_fn, kbp_device_issu_write_fn write_fn, void *handle);


/**
 * Perform a warm boot/ISSU restore. Restore device state from nonvolatile memory. The
 * user is expected to provide implementations of read/write callbacks.
 * These callbacks are used to read state from the nonvolatile
 * memory. The user is expected to know where the data was stored during
 * the save operation; the offsets specified in the callback are relative to this.
 *
 * @param device Valid device handle.
 * @param read_fn Callback to read data from nonvolatile memory.
 * @param write_fn Callback to write data to nonvolatile memory.
 * @param handle User handle which will be passed back through read_fn and write_fn
 *
 * @return KBP_OK on success, or an error code otherwise.
 */

kbp_status kbp_device_restore_state(struct kbp_device *device, kbp_device_issu_read_fn read_fn, kbp_device_issu_write_fn write_fn, void *handle);

/**
 * Signal start of reconciliation phase for ISSU. This is an
 * optional phase that signals marking all entries alive
 * in the user's software as visited. The window is demarked
 * by kbp_device_reconcile_start() and kbp_device_reconcile_end().
 * Also see kbp_entry_set_used().
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_reconcile_start(struct kbp_device *device);

/**
 * Signal end of reconciliation phase for ISSU. This is an
 * optional phase that signals marking all entries alive
 * in the users software as visited. The window is demarked
 * by kbp_device_reconcile_start() and kbp_device_reconcile_end().
 * Also see kbp_entry_set_used().
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_reconcile_end(struct kbp_device *device);

/**
 * @}
 */

/**
 * This is debug API
 * Given hardware index, will do look up and give the DB and Entry handle for ACLs
 * Only DB handle is returned back for LPM databases.
 *
 * @param device Valid KBP device handle.
 * @param hw_index The device index for with the handles are returned, for cascade devices, hw_index must include device_id.
 * @param db The database handle returned if hw_index lookup found, else NULL.
 * @param entry The entry handle returned if hw_index lookup and db found, else NULL.
 *   user can still use the db handle if it is not NULL
 *
 * @retval KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_lookup_index(struct kbp_device *device, uint32_t hw_index, struct kbp_db **db, struct kbp_entry **entry);

/**
 * Dumps the current state of the s/w (Key, Database properties, Entries,
 * Instructions, Resources) in the XML Format.
 *
 * @param device Valid KBP device handle
 * @param dump_xml_data_with_entries will the print the entries in the given XML file
 * @param fp Valid XML file pointer to dump the contents to
 *
 */

kbp_status kbp_device_dump(struct kbp_device * device, uint32_t dump_xml_data_with_entries, FILE *fp);

/**
 * @addtogroup CRASH_RECOVERY_API
 * @{
 */

/**
 * This API call marks the start of the transaction in the code flow when Crash Recovery is enabled.
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_start_transaction(struct kbp_device *device);

/**
 * This API call marks the end of the transaction in the code flow when Crash Recovery is enabled.
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_device_end_transaction(struct kbp_device *device);

/**
 * This API returns the action taken on the pending entries during crash recovery.
 *
 * @param device Valid device handle.
 * @param status Status of pending entries
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_query_restore_status(struct kbp_device *device, enum kbp_restore_status *status);

/**
 * This API clears the status of pending entries being maintained.
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_clear_restore_status(struct kbp_device *device);

/**
 * @}
 */

/**
 * This API will enable to defer all the writes to device.
 * And the cached writes can be flushed using flush API.
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_cache_writes(struct kbp_device *device);

/**
 * This API will flush the LTR writes to device
 *
 * @param device Valid device handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_flush_ltr_writes(struct kbp_device *device);

/**
 * This API will disable the blocks provided in the bitmap (bit set is considered to disable that block)
 *
 * @param device valid device handle.
 * @param dba_bmp bitmap blocks to be disabled represented in bitmap. [1 means disable block, 0 means nothing changed]
 * @param length_1 length of the bitmap.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_selective_shutdown(struct kbp_device *device, uint8_t *dba_bmp, uint32_t length_1);

/**
 * This API will flush all the pending writes to device
 *
 * @param device Valid device handle.
 * @param flags defines the level of flush to the device
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_flush_all_writes(struct kbp_device *device, uint32_t flags);

/**
 * This API will return the last error of the device
 *
 * @param device Valid device handle.
 *
 * @return verbose_error_string if any error or empty string if no error. DO NOT FREE THE RETURN STRING
 */

const char *kbp_device_get_last_error(struct kbp_device *device);

/**
 * Dumps the device core registers in address, data and name format
 *
 * @param device Valid device handle.
 * @param fp file to log the dump
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_dump_core_regs(struct kbp_device *device, FILE *fp);

/**
 * Dumps the serdes registers in address, data and name format
 *
 * @param device Valid device handle.
 * @param fp file to log the dump
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_dump_interface_regs(struct kbp_device *device, FILE *fp);

/**
 * Dumps Last result register data
 *
 * @param device Valid device handle.
 * @param only_reg_data 1:dumps only the last result register content, 0:dumps data in readable format
 * @param fp file to log the dump
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_read_last_result(struct kbp_device *device, uint32_t only_reg_data, FILE *fp);

/**
 * Read DIE Temperature
 *
 * @param device valid device handle.
 * @param temperature DIE temperature value in degree centigrade
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_read_die_temperature(struct kbp_device *device, int32_t *temperature);

/**
 * Read DIE Voltage
 *
 * @param device valid device handle.
 * @param voltage DIE voltage value in milli volts
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_read_die_voltage(struct kbp_device *device, int32_t *voltage);

/**
 * Read DIE Voltage or temperature
 * @param  device      valid device handle.
 * @param  data_out    temperature DIE temperature value in degree centigrade OR-
 *                     voltage DIE voltage value in milli volts
 * @param  is_voltage  1: read_die_voltage; 0: read_die_temperature.
 * @param  delay_in_ms delay in ms.
 *
 * @return             KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_read_die_voltage_temperature(struct kbp_device *device, int32_t *data_out, int32_t is_voltage, int32_t delay_in_ms);

/**
 * API to get the SDK memory stats
 *
 * @param device valid device handle.
 * @param fp log file pointer
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_memory_stats(struct kbp_device *device, FILE *fp);

/**
 * API to write device register, Supported only for 64b register, OP and OP2 devices supported
 *
 * @param device Valid device handle.
 * @param address valid address to write
 * @param data which holds the data to write
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_pio_register_write(struct kbp_device * device, uint32_t address, uint64_t data);

/**
 * API to read device register, Supported only for 64b register, OP and OP2 devices supported
 *
 * @param device Valid device handle.
 * @param address valid address to read
 * @param o_data which holds the read data
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_pio_register_read(struct kbp_device * device, uint32_t address, uint64_t *o_data);

/**
 * API to set a resource profile string
 *
 * @param device valid device handle.
 * @param resource_str resource profile string
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_load_resource_profile(struct kbp_device * device, char *resource_str);

/**
 * API to get the current resource profile string
 *
 * @param device valid device handle.
 * @param resource_str resource profile string where output should be copied
 * @param resource_str_size size of the given resource profile string buffer
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_device_get_resource_profile(struct kbp_device *device, char *resource_str, uint32_t resource_str_size);


#ifdef __cplusplus
}
#endif
#endif /*__DEVICE_H */

