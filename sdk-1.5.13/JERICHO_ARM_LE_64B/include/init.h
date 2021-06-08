/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __INIT_H
#define __INIT_H

/**
 * @file init.h
 *
 * This module provides the SerDes and lane-initialization code.
 */

#include <stdint.h>
#include <stdio.h>

#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DEVICE_CONFIG_APIS
 * @{
 */

/**
 * Type of device.
 */

enum kbp_device_type {
    KBP_DEVICE_UNKNOWN,       /**< Invalid device */
    KBP_DEVICE_12K,           /**< Algorithmic 12K class of devices */
    KBP_DEVICE_OP,            /**< Algorithmic Optimus Prime class of devices */
    KBP_DEVICE_OP2,           /**< Algorithmic Optimus Prime 2 class of devices. */
    KBP_DEVICE_KAPS,          /**< KAPS class of devices */
    KBP_DEVICE_INVALID        /**< This should be the last entry */
};

/**
 * When initializing the device the following flags can be
 * OR'd together to specify the operating mode of the device.
 */

enum kbp_device_flags {
    KBP_DEVICE_DEFAULT = 0,           /**< Single port, non-SMT, non-network byte order, no cascade mode. */
    KBP_DEVICE_SMT = 1,               /**< SMT mode in device enabled. Use kbp_device_thread_init() to obtain the thread's device handle. */
    KBP_DEVICE_DUAL_PORT = 2,         /**< Enable dual-port operation. */
    KBP_DEVICE_NBO = 4,               /**< Enable network byte order. */
    KBP_DEVICE_SUPPRESS_INDEX = 8,    /**< Suppress index generation in result when AD is present. */
    KBP_DEVICE_ISSU = 16,             /**< In-service software upgrade enabled. */
    KBP_DEVICE_CASCADE = 32,          /**< Cascading of KBPs is enabled */
    KBP_DEVICE_SKIP_INIT = 64,        /**< Skip the device init. To be used before ISSU restore. */
    KBP_DEVICE_SUPPRESS_PARITY = 128, /**< Disable Parity scan */
    KBP_DEVICE_QUAD_PORT = 256,       /**< Up to four port support (Optimus Prime and beyond only) */
    KBP_DEVICE_HST_DIG_LPBK = 512,    /**< hst digital loopback */
    KBP_DEVICE_THREAD_SAFETY = 1024   /**< To enable thread-safety at transport layer */
};

/**
 * SerDes lane speeds
 */

enum kbp_device_lane_speed {
    KBP_INIT_LANE_12_5 = 0,     /**< 12.5G SerDes. */
    KBP_INIT_LANE_3_125 = 1,    /**< 3.125G SerDes. */
    KBP_INIT_LANE_6_25 = 2,     /**< 6.25G SerDes. */
    KBP_INIT_LANE_10_3 = 3,     /**< 10.3G SerDes. */
    KBP_INIT_LANE_1_25 = 4,     /**< 1.25G SerDes. */

    KBP_INIT_LANE_15 = 5,       /**< 15G SerDes. */
    KBP_INIT_LANE_25_78125 = 6, /**< 25.78125G SerDes. */
    KBP_INIT_LANE_27_34375 = 7, /**< 27.34375G SerDes */
    KBP_INIT_LANE_28_125 = 8,   /**< 28.125G SerDes. */
    KBP_INIT_LANE_51_5625 = 9,  /**< 51.5625G SerDes. */
    KBP_INIT_LANE_56_25 = 10,   /**< 56.25G SerDes. */
    KBP_INIT_LANE_30 = 11,      /**< 30G SerDes. */
    KBP_INIT_LANE_46 = 12,      /**< 46G SerDes. */
    KBP_INIT_LANE_53_125 = 13,  /**< 53.125G SerDes. */
    KBP_INIT_LANE_INVALID = 14
};

/**
 * ILA burst short length.
 */

enum kbp_device_ila_burst_short {
    KBP_INIT_BURST_SHORT_8_BYTES = 0,  /**< 8-byte burst length. */
    KBP_INIT_BURST_SHORT_16_BYTES = 1, /**< 16-byte burst length. */
    KBP_INIT_BURST_SHORT_INVALID
};

/** TXFIR Tap Enable Enum */
enum blackhawk_tsc_txfir_tap_enable_enum {
    NRZ_LP_3TAP  = 0,
    NRZ_6TAP     = 1,
    PAM4_LP_3TAP = 2,
    PAM4_6TAP    = 3
};

/**
 * PRBS polynomial types
 */
enum kbp_prbs_polynomial {
    KBP_PRBS_7  = 0,
    KBP_PRBS_9  = 1,
    KBP_PRBS_11 = 2,
    KBP_PRBS_15 = 3,
    KBP_PRBS_23 = 4,
    KBP_PRBS_31 = 5,
    KBP_PRBS_58 = 6
};


/**
 * type def for kbp_blackhawk_tsc_txfir_tap_enable_enum.
 */
#define kbp_blackhawk_tsc_txfir_tap_enable_enum blackhawk_tsc_txfir_tap_enable_enum

/**
 * SerDes TXFIR tap settings.
 */
struct kbp_serdes_tap_settings {
    int16_t enable_taps;
    int16_t pre2;
    int16_t pre1;
    int16_t mainx;
    int16_t post1;
    int16_t post2;
    int16_t post3;
};

/**
 * Device interface settings.
 */
struct kbp_device_interface_settings {
    struct kbp_serdes_tap_settings tap_settings;
    uint16_t user_tap_settings;
    uint16_t link_training_enable;
    uint16_t media_type;
    uint16_t dfe_mode;
    uint16_t dfe_lp_mode;
    uint16_t silent_logs;
    uint16_t disable_restart_linktrn;
    uint16_t hst_pcs_poll_delay;            /** Delay polling PCS ready for port status for number of seconds. */    
};

/**
 * Device configuration structure used to initialize the device.
 */

struct kbp_device_config {
    struct
    {
        uint32_t start_lane;   /**< Start lane number for the port. */
        uint32_t num_lanes;    /**< Number of lanes for the port, must be a multiple of four (Quad). */
    } port_map[4];             /**< The flags argument to kbp_device_init() or kbp_device_interface_init() must be OR'd with KBP_DEVICE_DUAL_PORT, to honor second port info. */

    enum kbp_device_lane_speed speed;      /**< SerDes speed. */
    enum kbp_device_ila_burst_short burst; /**< Short burst size */
    uint32_t meta_frame_len;               /**< Metaframe length. */
    uint32_t reset_only;                   /**< Bitmap to do not enable Rx lanes per port, One bit per port */

    void *handle;                          /**< Opaque handle passed to MDIO read/write routines as first argument. */
    void *misc_handle;                     /**< Opaque handle passed to reset/pre-linkup callbacks. If NULL MDIO handle above will be passed in for backward compatibility */
    uint32_t reverse_lanes;                /**< Bitmap to enable reverse lane per port, One bit per port */

    /**
     * Total number of devices. Default is 1. When KBP_DEVICE_CASCADE
     * is specified, the requested number of devices are brought up.
     * The devices are addressed logically from 0 - 3. The user must
     * translate it to actual MDIO MPID
     */

    uint32_t num_devices;
    /**
     * Callback for asserting SerDes and core resets. A value of one
     * means asserted low (0V); a value of zero means deasserted. Function returns
     * zero on success or indicates an error otherwise. When KBP devices
     * are in cascade, the asserts are expected to be applied to
     * all devices
     *
     * @param handle Opaque user provided handle passed to the callback.
     * @param s_reset_low Assert S_RESET. A value of one means asserted low (0V); a value of zero means deasserted.
     * @param c_reset_low Assert C_RESET. A value of one means asserted low (0V); a value of zero means deasserted.
     */

    int32_t (*assert_kbp_resets) (void *misc_handle, int32_t s_reset_low, int32_t c_reset_low);

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

    int32_t (*mdio_read) (void *handle, int32_t chip_no, uint8_t dev, uint16_t reg, uint16_t *value);

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

    int32_t (*mdio_write) (void *handle, int32_t chip_no, uint8_t dev, uint16_t reg, uint16_t value);

    /**
     * Implementation of usleep provided by the user. The function is
     * expected to sleep for the requested micro seconds.
     *
     * @param handle Opaque user provided handle passed to the callback.
     * @param value The number of micro seconds to sleep
     *
     * @retval 0 on success
     * @retval non-zero on failure or not able to sleep for requested time
     */
    int32_t (*usleep) (void *misc_handle, uint32_t value);

    /**
     * Option callback from the initialization code that is
     * called if provided before the TX/RX links are enabled.
     * Optionally NPUs may use this to perform specific
     * operations on their side or change KBP Serdes configurations.
     * On successful return the links will be enabled and active on the KBP
     *
     * @param handle Opaque user provided handle passed to the callback.
     *
     * @retval 0 on success
     * @retval non-zero on failure
     */
    int32_t (*pre_enable_link_callback) (void *misc_handle);

    /**
     * Starting Optimus Prime, load serdes uCode through DMA if available
     * This callback can be NULL, in which case the uCode will be loaded
     * using MDIO callbacks.
     *
     * This callback is filled in by the KBP PCIE device driver
     *
     * @param handle Opaque user provided handle passed to the callback
     * @param ucode The uCode to be downloaded
     * @param len The uCode length in bytes
     *
     * @retval 0 on success
     * @retval non-zero on failure
     */
    int32_t (*ucode_dma_load) (void *handle, const uint8_t *ucode, uint32_t len);

    /**
     * Optional callback function, it should be used only when asymmetric lane usage is required,
     * Also the num lanes for each port in the above configuration should be set to the max lane count to start off with.
     * Each bit set to one enables the lane.
     *
     * @param rx_lanes_bmp Rx Lanes Bitmap
     * @param tx_lanes_bmp Tx Lanes Bitmap
     *
     * @retval 0 on success
     * @retval non-zero on failure
     */
    int32_t (*get_rx_tx_lanes_bmp) (uint64_t *rx_lanes_bmp, uint64_t *tx_lanes_bmp);

    /**
     * Optional callback function, it should be used only when polarity inversion is required for a lane.
     *
     * @param lanes_bmp lane bitmap to enable the polarity inversion, One bit per lane
     *
     * @retval 0 on success
     * @retval non-zero on failure
     */
    int32_t (*get_polarity_invert_lanes_bmp) (uint64_t *lanes_bmp);

    /* AVS */
    uint32_t init_avs;                      /**< Flag to init AVS */
    int32_t max_avs_voltage;                /**< Upper limit for die convergence voltage */
    int32_t min_avs_voltage;                /**< Lower limit for die convergence voltage */
    FILE *debug_fp;                         /**< File to log debug dump */

    uint32_t reset_done;                    /**< Reset done flag */
    uint16_t fec_frame_length;              /**< FEC Frame Length */
    struct kbp_device_interface_settings settings; /**< interface settings */
};

/**
 * Default initializer for the configuration structure.
 */

#define KBP_DEVICE_CONFIG_DEFAULT                       \
    {                                                   \
        { { 0, 12 }, /* Port 0 lanes */                 \
          { 0, 0  }, /* Port 1 lanes */                 \
          { 0, 0  }, /* Port 2 lanes */                 \
          { 0, 0  }  /* Port 3 lanes */                 \
        },                                              \
        KBP_INIT_LANE_12_5, /* 12.5G SerDes */          \
        KBP_INIT_BURST_SHORT_8_BYTES, /* burst */       \
        0x80, /* meta frame */                          \
        0,    /* Reset only */                          \
        0,    /* MDIO Read/Write handle */              \
        0,    /* Reset/sleep handle */                  \
        0,    /* reverse lanes */                       \
        1,    /* Number of devices */                   \
        0,    /* reset function */                      \
        0,    /* MDIO read */                           \
        0,    /* MDIO write */                          \
        0,    /* uSleep */                              \
        0,    /* Pre link up callback */                \
        0,    /* uCode DMA load */                      \
        0,    /* get Rx Tx lanes bitmap */              \
        0,    /* get polarity invert lanes bitmap */    \
        0,    /* Init AVS flag */                       \
        0,    /* AVS Max Voltage */                     \
        0,    /* AVS Min Voltage */                     \
        NULL, /* File to log debug dump */              \
        0x1000 /* FEC Frame Length */                   \
    }

/**
 * Initialize the SerDes, and configure the device.
 * Do not assign reset callbacks if you are using
 * kbp_device_interface_reset API
 *
 * @param type The device type ::kbp_device_type.
 * @param flags ::kbp_device_flags OR'd together.
 * @param config Configuration structure initialized appropriately.
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_init(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config);

/**
 * Configure SMT in the Device Config Register
 * This API is applicable for only 12K.
 *
 * @param type The device type ::kbp_device_type.
 * @param config Configuration structure
 * @param device_no cascade device number
 * @param smt_sb_map bitmap indicating the bank for consecutive super block pairs. If LS bit is set to 1, then SB-0 and SB-1
 *                                 will belong to SMT-1 otherwise they will belong to SMT-0
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_config_smt(enum kbp_device_type type, struct kbp_device_config *config, uint32_t device_no, uint16_t smt_sb_map);


/**
 * Logs configuration and interface registers in verbose format
 *
 * Currently supports Optimus Prime only
 *
 * @param type the device type
 * @param flags the same flags used to initialize the device/interface
 * @param config Configuration structure initialized appropriately.
 * @param fp the file pointer to dump into
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_print_regs(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config, FILE *fp);

/**
 * Enable PRBS generation on RX and TX side
 *
 * @param type The device type
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 * @param prbs_poly PRBS polynomial type
 * @param enable If one, PRBS is enabled, if zero disabled
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_prbs(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config,
                                     enum kbp_prbs_polynomial prbs_poly, uint32_t enable);

/**
 * Print verbose PRBS information
 *
 * @param type The device type
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_prbs_print(enum kbp_device_type type, uint32_t flags,
                                           struct kbp_device_config *config);

/**
 * Print eye scan information for specific lane
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime 2 are supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_eyescan_print(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config);

/**
 * Enable PRBS generation on RX and TX side
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime 2 are supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 * @param prbs_poly PRBS polynomial type
 * @param enable If one, PRBS is enabled, if zero disabled
 * @param lane_bitmap enable/disable prbs based on lane bitmap, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_per_lane_prbs(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config,
                                              enum kbp_prbs_polynomial prbs_poly, uint32_t enable, uint64_t lane_bitmap);

/**
 * Print verbose PRBS information
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime 2 are supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 * @param lane_bitmap print prbs based on lane bitmap, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_per_lane_prbs_print(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config, uint64_t lane_bitmap);

/**
 * Print eye scan information for specific lane
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime 2 are supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 * @param lane_bitmap print eyescan based on lane bitmap, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_per_lane_eyescan_print(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config, uint64_t lane_bitmap);

/**
 * Writes Serdes TXFIR tap settings
 *
 * @param type The device type, currently only Optimus Prime is supported
 * @param config Interface configuration structure initialized correctly
 * @param lane_bmp bitmap to program TXFIR settings, One bit per lane
 * @param pre     TXFIR pre tap value (0..31)
 * @param main    TXFIR main tap value (0..127)
 * @param post1   TXFIR post tap value (-63..63)
 * @param post2   TXFIR post2 tap value (-15..15)
 * @param post3   TXFIR post3 tap value (-15..15)
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_tx_serdes_emphasize(enum kbp_device_type type, struct kbp_device_config *config, uint64_t lane_bmp,
                                                    int8_t pre, int8_t main, int8_t post1, int8_t post2, int8_t post3);

/**
 * Enable/Disable Tx link
 *
 * @param type The device type ::kbp_device_type
 * @param config Interface configuration structure initialized correctly
 * @param port_bmp port bitmap
 * @param enable 1. enable, 0. disable
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_enable_tx_link(enum kbp_device_type type, struct kbp_device_config *config,
                                               uint8_t port_bmp, uint8_t enable);

/**
 * Enable/Disable Rx link
 *
 * @param type The device type ::kbp_device_type
 * @param config Interface configuration structure initialized correctly
 * @param port_bmp port bitmap
 * @param enable 1. enable, 0. disable
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_enable_rx_link(enum kbp_device_type type, struct kbp_device_config *config,
                                               uint8_t port_bmp, uint8_t enable);
/**
 * PRBS Error Count and Lock Lost status
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime 2 are supported
 * @param config Interface configuration structure initialized correctly
 * @param lane_no lane number
 * @param *prbs_err_cnt 32bit Error count value
 * @param *lock_lost Lock Lost status (1 = if lock was ever lost)
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_prbs_error(enum kbp_device_type type, struct kbp_device_config *config,
                                           uint32_t lane_no, uint32_t *prbs_err_cnt, uint8_t *lock_lost);

/**
 * Inject PRBS Error
 *
 * @param type The device type, currently only 12K is supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 * @param error_count number of errors to inject
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_prbs_inject_error(enum kbp_device_type type, uint32_t flags, struct kbp_device_config *config,
                                                  uint32_t error_count);

/**
 * Serdes loopback type
 */

enum kbp_serdes_loopback_type {
    KBP_SERDES_DIGITAL_LOOPBACK,
    KBP_SERDES_REMOTE_LOOPBACK
};

/**
 * Serdes Loopback
 *
 * @param type The device type, currently only OP is supported
 * @param config Interface configuration structure initialized correctly
 * @param loopback_type Digital/Remote loopback
 * @param enable enable/disable loopback
 * @param lane_bmp enable/disable loopback per lane, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_serdes_loopback(enum kbp_device_type type, struct kbp_device_config *config,
                                                enum kbp_serdes_loopback_type loopback_type, uint8_t enable,
                                                uint64_t lane_bmp);

/**
 * Read DIE Temperature
 *
 * @param type The device type, currently only OP is supported
 * @param config Interface configuration structure initialized correctly
 * @param temperature DIE temperature value in degree centigrade
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_interface_read_die_temperature(enum kbp_device_type type, struct kbp_device_config *config,
                                                     int32_t *temperature);

/**
 * Read DIE Voltage
 *
 * @param type The device type, currently only OP is supported
 * @param config Interface configuration structure initialized correctly
 * @param voltage DIE voltage value in milli volts
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_interface_read_die_voltage(enum kbp_device_type type, struct kbp_device_config *config,
                                                 int32_t *voltage);

/**
 * Print DIAG information for configured lanes
 *
 * @param type The device type, currently only Optimus Prime is supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_diag_print(enum kbp_device_type type, uint32_t flags,
                                           struct kbp_device_config *config);

/**
 * Print DIAG information for specific lane
 *
 * @param type The device type, currently only Optimus Prime is supported
 * @param flags The device configuration flags
 * @param config Interface configuration structure initialized correctly
 * @param lane_bmp print BER based on lane bitmap, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_per_lane_diag_print(enum kbp_device_type type, uint32_t flags,
                                                    struct kbp_device_config *config, uint64_t lane_bmp);

/**
 * Apply System reset
 *
 * @param type The device type, currently only Optimus Prime is supported
 * @param config Interface configuration structure initialized correctly
 *
 */
kbp_status kbp_device_interface_reset(enum kbp_device_type type, struct kbp_device_config *config);

/**
 * Programs DFE settings
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime 2 are supported
 * @param config Interface configuration structure initialized correctly
 * @param lane_bmp print BER based on lane bitmap, one bit per lane
 * @param dfe_on 1. DFE ON 0. DFE OFF
 * @param dfe_lp_mode 1. DFE LP Mode ON 0. DFE LP MODE OFF
 *
 * @retval KBP_OK on success or an error code
 */
kbp_status kbp_device_interface_dfe_setting(enum kbp_device_type type, struct kbp_device_config *config, uint64_t lane_bmp,
                                            uint8_t dfe_on, uint8_t dfe_lp_mode);
/**
 * Initialize the Port Macro
 *
 * @param unit OP2 unit number
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param port_speed Supported speeds are 40G, 100G and 200G
 * @param port_bmp Bitmap to initialize port macro
 * @param is_nrz flag for NRZ or PAM4 mode
 * @param link_training 1. Enable 0. Disable
 * @param emph_vals User serdes TXFIR tap settings
 *
 * @return KBP_OK on success or an error code.
 */
kbp_status kbp_device_pm_interface_init(int unit, void *xpt, int32_t port_speed, int32_t port_bmp,
                                        int32_t is_nrz, int32_t link_training,
                                        struct kbp_serdes_tap_settings *emph_vals);

/**
 * Read the Port Macro Config
 *
 * @param unit OP2 unit number
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 *
 * @return KBP_OK on success or an error code.
 */
kbp_status kbp_op_tap_device_pm_info_get(int unit, void *xpt);

/**
 * Read DIE Voltage or temperature
 *
 * @param type The device type, currently only OP is supported
 * @param config Interface configuration structure initialized correctly
 * @param data_out temperature DIE temperature value in degree centigrade OR-
 *                 voltage DIE voltage value in milli volts
 * @param is_voltage 1: read_die_voltage; 0: read_die_temperature.
 * @param delay_in_ms delay in ms.
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_device_interface_read_die_voltage_temperature(enum kbp_device_type type, struct kbp_device_config *config,
                                                             int32_t *data_out, int32_t is_voltage, int32_t delay_in_ms);

/**
 * Writes Serdes TXFIR tap settings
 *
 * @param type The device type, currently only Optimus Prime 2 is supported
 * @param config Interface configuration structure initialized correctly
 * @param lane_bmp bitmap to program TXFIR settings, One bit per lane
 * @param tap_settings TXFIR settings
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_interface_serdes_tap_settings(enum kbp_device_type type, struct kbp_device_config *config,
                                                    uint32_t lane_bmp, struct kbp_serdes_tap_settings *tap_settings);

/**
 * Writes PM Serdes TXFIR tap settings
 *
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param lane_bmp bitmap to program TXFIR settings, One bit per lane
 * @param tap_settings TXFIR settings
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_pm_interface_serdes_tap_settings(void *xpt, uint16_t lane_bmp,
                                                       struct kbp_serdes_tap_settings *tap_settings);

/**
 * Display PM Serdes lanestate
 *
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param lane_bmp bitmap to display serdes lanestate, One bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_pm_interface_serdes_lanestate(void *xpt, uint16_t lane_bmp);

/**
 * Enable PRBS generation
 *
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param prbs_poly PRBS polynomial type
 * @param enable If one, PRBS is enabled, if zero disabled
 * @param lane_bitmap enable/disable prbs based on lane bitmap, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_pm_interface_serdes_prbs(void *xpt, enum kbp_prbs_polynomial prbs_poly,
                                               uint32_t enable, uint16_t lane_bitmap);

/**
 * Print verbose PM serdes PRBS information
 *
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param lane_bitmap enable/disable prbs based on lane bitmap, one bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_pm_interface_serdes_prbs_print(void *xpt, uint16_t lane_bitmap);

/**
 * Display PM Serdes eyescan
 *
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param lane_bmp bitmap to display serdes lanestate, One bit per lane
 *
 * @retval KBP_OK on success or an error code
 */

kbp_status kbp_device_pm_interface_serdes_eyescan(void *xpt, uint16_t lane_bmp);

/**
 * Prints PM interface port related registers data
 *
 * @param xpt pointer to the op2_xpt struct that contains the handle pointer
 * @param port_id PM interface port number
 * @param fp Valid file pointer to dump the contents to
 *
 * @returns KBP_OK on success or an error code otherwise
 */

kbp_status kbp_device_pm_interface_dump_port_regs(void *xpt, uint32_t port_id, FILE *fp);

/**
 * MDIO Read function
 *
 * @param config Interface configuration structure initialized correctly
 * @param size register size valid sizes are 16, 64 and 80
 * @param base_addr address of the register
 * @param data write data
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_mdio_write(struct kbp_device_config *config, uint32_t size, uint32_t base_addr, uint8_t *data);

/**
 * MDIO Read function
 *
 * @param config Interface configuration structure initialized correctly
 * @param size register size valid sizes are 16, 64 and 80
 * @param base_addr address of the register
 * @param data pointer to read data
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_mdio_read(struct kbp_device_config *config, uint32_t size, uint32_t base_addr, uint8_t *data);

/**
 * Program PHMF FIFO value
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime2 are supported
 * @param config Configuration structure initialized appropriately.
 * @param lane_bitmap lane bitmap
 * @param reset 1. reset the FIFO, 0. program the default value
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_program_PHMF_FIFO(enum kbp_device_type type, struct kbp_device_config *config,
                                                  uint64_t lane_bitmap, uint8_t reset);

/**
 * API to toggle PHMF FIFO
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime2 are supported
 * @param config Configuration structure initialized appropriately.
 * @param port_bmp port bitmap.
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_PHMF_FIFO_toggle(enum kbp_device_type type, struct kbp_device_config *config, uint8_t port_bmp);

/**
 * API to toggle TXPCS
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime2 are supported.
 * @param config Configuration structure initialized appropriately.
 * @param port_bmp port bitmap.
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_TXPCS_soft_reset_toggle(enum kbp_device_type type, struct kbp_device_config *config,
                                                        uint8_t port_bmp);

/**
 * API to toggle TX & RX
 *
 * @param config Configuration structure initialized appropriately.
 * @param flags The device configuration flags
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_tx_rx_toggle(enum kbp_device_type type, struct kbp_device_config *config, uint32_t flags);

/**
 * API to fix device interface errors which are addressed by SDK
 *
 * @param type The device type, currently Optimus Prime and Optimus Prime2 are supported
 * @param config Configuration structure initialized appropriately.
 * @param error_counters output buffer were all error information is populated
 *
 * @return KBP_OK on success or an error code.
 */

kbp_status kbp_device_interface_fix_errors(enum kbp_device_type type, struct kbp_device_config *config,
                                           uint64_t *error_counters);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*__INIT_H */
