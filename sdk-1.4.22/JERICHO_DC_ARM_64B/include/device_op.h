/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DEVICE_OP_H
#define __DEVICE_OP_H

#include "kbp_portable.h"
#include "errors.h"
#include "device.h"
#include "instruction.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file device_op.h
 *
 * Defines enums and structures for registers and various software-visible
 * fields for Optimus Prime
 */

/** The number of LTRs */
#define KBP_OP_NUM_LTRS                      128

/** Master key width in bytes */
#define KBP_OP_MASTER_KEY_SIZE_8              80

/** Number of KPUs */
#define KBP_OP_NUM_KPUS                        4

/** Number of bytes output by one KPU */
#define KBP_OP_KPU_WIDTH_8                    80

/** Number of range units present in Optimus Prime */
#define KBP_OP_NUM_RANGE_UNITS                16

/** Number of MCOR configuration registers per range unit */
#define KBP_OP_MCOR_REGS_PER_UNIT              8

/** Number of configuration registers for DIRPE encoding per range unit */
#define KBP_OP_DIRPE_REGS_PER_UNIT             2

/** Maximum number of bytes output by one range unit */
#define KBP_OP_MAX_RANGE_OUTPUT_8              4

/** Maximum number of ABs in DBA for any member of the Optimus family */
#define KBP_OP_MAX_NUM_ABS                   256

/** Number of ABs in each superblock of Optimus Prime */
#define KBP_OP_NUM_ABS_PER_SB                  4

/** Number of 320-bit ternary entries in one DBA array block */
#define KBP_OP_NUM_320_IN_AB                            1024

/** Number of 80-bit ternary entries in one DBA array block */
#define KBP_OP_NUM_80_IN_AB  (KBP_OP_NUM_320_IN_AB * 4)

/** Number of BMRs */
#define KBP_OP_NUM_BMR                         4

/** Number of rows in a single 64-wide bank of UDA memory */
#define KBP_OP_UDA_BANK_DEPTH               8192

/** Number of banks of memory making up a UDA superblock */
#define KBP_OP_BANKS_PER_USB                   4

/** Number of 64-bit words in an USB */
#define KBP_OP_USB_SIZE_64 (KBP_OP_BANKS_PER_USB * KBP_OP_UDA_BANK_DEPTH)

/** Number of UDA superblocks per UDM */
#define KBP_OP_USBS_PER_UDM                    4

/** Number of 64-bit words in an UDM */
#define KBP_OP_UDM_SIZE_64 (KBP_OP_USBS_PER_UDM * KBP_OP_USB_SIZE_64)

/** Maximum number of AD databases per DB */
#define KBP_OP_MAX_AD_PER_DB                    2

/** Max possible number of UDCs in UDA */
#define KBP_OP_MAX_UDCS                       16

/** Max possible number of UDMs in UDA */
#define KBP_OP_MAX_UDMS                       64

/** Number of UDMs in one UDC */
#define KBP_OP_UDM_PER_UDC                     4

/** Total number of independent pieces of associated data the Optimus pipeline can generate */
#define KBP_OP_TOTAL_PIPELINE_ADS              8

/** Maximum width in bytes for the associated data read on-chip in response to one search */
#define KBP_OP_MAX_AD_WIDTH_8                 32

/** Maximum number of DBA results */
#define KBP_OP_NUM_DBA_RESULTS                16

/** Offset of parent AB for 640 bits configuration. */
#define KBP_OP_PARENT_AB_OFFSET_640           512

/** Maximum number of ABs per AC */
#define KBP_OP_NUM_ABS_PER_AC                 8

/** Maximum number of DBs per device */
#define KBP_OP_NUM_DB_PER_DEVICE              64

/** Resources Type */
#define DBA_RESOURCE     1
#define UDA_RESOURCE     2
#define HBB_RESOURCE     5

/**
 * @brief OP Device ID Register
 */

struct op_dev_id_reg {
    uint64_t bits;  /**< [31:0] JTAG ID, [43:40] Device Format (silicon or emulation)
                         TODO: fill other fields */
};

/**
 * @addtogroup LTR
 * @{
 */

/**
 * @brief LTR register describing KPU parsing
 */

struct op_kpu_segs_0_4 {
    __EO_18(uint32_t fill00:1,        /**< If set, segment 0 filled with 0s not read from master key */
            uint32_t start0:7,        /**< Start position of segment 0 in master key */
            uint32_t len_minus_1_0:4, /**< Length of segment 0 (0 means 1 byte, 15 means 16) */
            uint32_t fill01:1,        /**< If set, segment 1 filled with 0s not read from master key */
            uint32_t start1:7,        /**< Start position of segment 1 in master key */
            uint32_t len_minus_1_1:4, /**< Length of segment 1 (0 means 1 byte, 15 means 16) */
            uint32_t fill02:1,        /**< If set, segment 2 filled with 0s not read from master key */
            uint32_t start2:7,        /**< Start position of segment 2 in master key */
            uint32_t len_minus_1_2:4, /**< Length of segment 2 (0 means 1 byte, 15 means 16) */
            uint32_t fill03:1,        /**< If set, segment 3 filled with 0s not read from master key */
            uint32_t start3:7,        /**< Start position of segment 3 in master key */
            uint32_t len_minus_1_3:4, /**< Length of segment 3 (0 means 1 byte, 15 means 16) */
            uint32_t fill04:1,        /**< If set, segment 4 filled with 0s not read from master key */
            uint32_t start4:7,        /**< Start position of segment 4 in master key */
            uint32_t len_minus_1_4:4, /**< Length of segment 4 (0 means 1 byte, 15 means 16) */
            uint32_t enable:1,        /**< Whether this KPU is used by the LTR */
            uint32_t keyb_start_offset:2, /**< Where key b starts in KPU output (0 = unused, 1 = bit 160, ... ,  3 = bit 480) */
            uint32_t unused:1);       /**< Unused, for aligning to 64b register */
};

/**
 * @brief LTR register describing KPU parsing
 */

struct op_kpu_segs_5_9 {
    __EO_16(uint32_t fill05:1,        /**< If set, segment 5 filled with 0s not read from master key */
            uint32_t start5:7,        /**< Start position of segment 5 in master key */
            uint32_t len_minus_1_5:4, /**< Length of segment 5 (0 means 1 byte, 15 means 16) */
            uint32_t fill06:1,        /**< If set, segment 6 filled with 0s not read from master key */
            uint32_t start6:7,        /**< Start position of segment 6 in master key */
            uint32_t len_minus_1_6:4, /**< Length of segment 6 (0 means 1 byte, 15 means 16) */
            uint32_t fill07:1,        /**< If set, segment 7 filled with 0s not read from master key */
            uint32_t start7:7,        /**< Start position of segment 7 in master key */
            uint32_t len_minus_1_7:4, /**< Length of segment 7 (0 means 1 byte, 15 means 16) */
            uint32_t fill08:1,        /**< If set, segment 8 filled with 0s not read from master key */
            uint32_t start8:7,        /**< Start position of segment 8 in master key */
            uint32_t len_minus_1_8:4, /**< Length of segment 8 (0 means 1 byte, 15 means 16) */
            uint32_t fill09:1,        /**< If set, segment 9 filled with 0s not read from master key */
            uint32_t start9:7,        /**< Start position of segment 9 in master key */
            uint32_t len_minus_1_9:4, /**< Length of segment 9 (0 means 1 byte, 15 means 16) */
            uint32_t unused:4);       /**< Unused, for aligning to 64b register */
};

/**
 * @brief Range encoding possibilities
 */

enum op_range_ctrl
{
    OP_RANGE_DISABLE = 0,    /**< Range unit is not used by this LTR */
    OP_MCOR_ONLY = 1,        /**< 8-bit output consisting of MCOR bits only */
    OP_DIRPE2_ONLY = 2,      /**< 16-bit output consisting of DIRPE-2 encodes 16-bit port number */
    OP_DIRPE3_ONLY = 3,      /**< 24-bit output consisting of DIRPE-3 encodes 16-bit port number */
    OP_DIRPE2_AND_MCOR = 4,  /**< 24-bit output with DIRPE-2 in lower 16 bits and MCOR in higher 8 */
    OP_DIRPE3_AND_MCOR = 5   /**< 32-bit output with DIRPE-3 in lower 24 bits and MCOR in higher 8 */
};

/**
 * @brief LTR register for range extraction information of up to 6 range fields extracted from master key
 */

struct op_range_ext {
    __EO_14(uint32_t extract_byte_0:7, /**< Start range extraction at this byte, 16b are extracted */
            uint32_t ctl_0:3,          /**< Enable and range encoding type defined by ::op_range_ctrl */
            uint32_t extract_byte_1:7, /**< Start range extraction at this byte, 16b are extracted */
            uint32_t ctl_1:3,          /**< Enable and range encoding type defined by ::op_range_ctrl */
            uint32_t extract_byte_2:7, /**< Start range extraction at this byte, 16b are extracted */
            uint32_t ctl_2:3,          /**< Enable and range encoding type defined by ::op_range_ctrl */
            uint32_t unused_lo:2,      /**< Unused */
            uint32_t extract_byte_3:7, /**< Start range extraction at this byte, 16b are extracted */
            uint32_t ctl_3:3,          /**< Enable and range encoding type defined by ::op_range_ctrl */
            uint32_t extract_byte_4:7, /**< Start range extraction at this byte, 16b are extracted */
            uint32_t ctl_4:3,          /**< Enable and range encoding type defined by ::op_range_ctrl */
            uint32_t extract_byte_5:7, /**< Start range extraction at this byte, 16b are extracted */
            uint32_t ctl_5:3,          /**< Enable and range encoding type defined by ::op_range_ctrl */
            uint32_t unused_hi:2);     /**< Unused */
};

/**
 * @brief Manipulation of a key between KPU one one side and DBA and UDA on the other
 */

enum op_key_proc
{
    OP_KEY_UNCHANGED = 0, /**< No changes to search key */
    OP_KEY_1_RANGE   = 1, /**< Overwriting the highest bits with the output from one range unit */
    OP_KEY_2_RANGES  = 2  /**< Overwriting the highest bits with the output from two range units */
};

/**
 * @brief Position where the output of range units is inserted into the DBA key
 */

enum op_range_ins_pos
{
    OP_RANGE_160 = 0, /**< Range unit outputs inserted in bits 159:x of key */
    OP_RANGE_320 = 1, /**< Range unit outputs inserted in bits 319:x of key */
    OP_RANGE_480 = 2, /**< Range unit outputs inserted in bits 479:x of key */
    OP_RANGE_640 = 3  /**< Range unit outputs inserted in bits 639:x of key */
};

/**
 * @brief LTR register controlling post-KPU processing of 640 bits of key generated by the KPU and BMR selection
 */

struct op_post_kpu_proc {
    __EO_14(uint32_t dba_key_words_a:6,  /**< Number of non-range words of key Xa sent to DBA (reducing power on DBA key bus) */
            uint32_t key_build_a:3,      /**< Type of post-kpu key processing for key Xa ::op_key_proc */
            uint32_t range_ins_pos_a:2,  /**< Where in key Xa ranges are written ::op_range_ins_pos */
            uint32_t range_select_0_a:4, /**< Which of the 16 range units' output goes to DBA in highest bits of key Xa */
            uint32_t range_select_1_a:4, /**< Which of the 16 range units' output goes to DBA as second range of key Xa */
            uint32_t bmr_sel_a:3,        /**< BMR used by DBA superblocks comparing against key Xa */
            uint32_t unused_a:10,        /**< Unused */
            uint32_t dba_key_words_b:6,  /**< Number of non-range words of key Xb sent to DBA (reducing power on DBA key bus) */
            uint32_t key_build_b:3,      /**< Type of post-kpu key processing for key Xb ::op_key_proc */
            uint32_t range_ins_pos_b:2,  /**< Where in key Xb ranges are written ::op_range_ins_pos */
            uint32_t range_select_0_b:4, /**< Which of the 16 range units' output goes to DBA in highest bits of key Xb */
            uint32_t range_select_1_b:4, /**< Which of the 16 range units' output goes to DBA as second range of key Xb */
            uint32_t bmr_sel_b:3,        /**< BMR used by DBA superblocks comparing against key Xb */
            uint32_t unused_b:10);       /**< Unused */
};

/**
 * @brief LTR register controlling resolution of overflow results from DBA
 */

struct op_srch_attr_ctrl {
    __EO_10(uint32_t res_map_dba_0:3,    /**< Hits from DBA result 0 are resolved into this result */
            uint32_t res_map_dba_1:3,    /**< Hits from DBA result 1 are resolved into this result */
            uint32_t res_map_dba_2:3,    /**< Hits from DBA result 2 are resolved into this result */
            uint32_t res_map_dba_3:3,    /**< Hits from DBA result 3 are resolved into this result */
            uint32_t res_map_dba_4:3,    /**< Hits from DBA result 4 are resolved into this result */
            uint32_t res_map_dba_5:3,    /**< Hits from DBA result 5 are resolved into this result */
            uint32_t res_map_dba_6:3,    /**< Hits from DBA result 6 are resolved into this result */
            uint32_t res_map_dba_7:3,    /**< Hits from DBA result 7 are resolved into this result */
            uint32_t rsv0:8,             /**< Reserved */
            uint32_t rsv1);              /**< Unused */
};

/**
 * @brief LTR register controlling AD read & MP behavior
 */

struct op_ad_hb_ctrl {
    __EO_13(uint32_t ad_enable_bmp:8,   /**< Whether extra read for AD located on Optimus is needed */
            uint32_t ad_size_0:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128, 3 == 256 */
            uint32_t ad_size_1:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128, 3 == 256 */
            uint32_t ad_size_2:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128, 3 == 256 */
            uint32_t ad_size_3:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128, 3 == 256 */
            uint32_t ad_size_4:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128 */
            uint32_t ad_size_5:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128 */
            uint32_t ad_size_6:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128 */
            uint32_t ad_size_7:2,       /**< Width of AD 0 == 32, 1 == 64, 2 == 128 */
            uint32_t mp_bmp:8,          /**< Whether the lookup is massively parallel */
            uint32_t hit_bit_bmp:8,     /**< If bit X is set, a hit on result X leads to a hitbit update */
            uint32_t idx_disable_bmp:8, /**< If bit X is set, no index is returned with result X if AD enabled */
            uint32_t unused:16);        /**< Unused */
};

/**
 * @brief LTR register controlling result generation
 */

struct op_res_ctrl {
    __EO_17(uint32_t res_bmp:8,                /**< Bitmap defining which of the 8 results to send back through the interface */
           uint32_t ad_tx_offset_32_0:3,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_0:5,    /**< Bytes returned (0 means 1 byte, 31 means 32 (256b), 248b not supported) */
           uint32_t ad_tx_offset_32_1:3,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_1:5,    /**< Bytes returned (0 means 1 byte, 31 means 32 (256b), 248b not supported) */
           uint32_t ad_tx_offset_32_2:3,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_2:5,    /**< Bytes returned (0 means 1 byte, 31 means 32 (256b), 248b not supported) */
           uint32_t ad_tx_offset_32_3:3,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_3:5,    /**< Bytes returned (0 means 1 byte, 31 means 32 (256b), 248b not supported) */
           uint32_t ad_tx_offset_32_4:2,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_4:4,    /**< Bytes returned (0 means 1 byte, 15 means 16 (128b)) */
           uint32_t ad_tx_offset_32_5:2,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_5:4,    /**< Bytes returned (0 means 1 byte, 15 means 16 (128b)) */
           uint32_t ad_tx_offset_32_6:2,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_6:4,    /**< Bytes returned (0 means 1 byte, 15 means 16 (128b)) */
           uint32_t ad_tx_offset_32_7:2,      /**< Which 32b word of AD to start with when building response */
           uint32_t ad_tx_len_minus_1_7:4);    /**< Bytes returned (0 means 1 byte, 15 means 16 (128b)) */
};

/**
 * @}
 */

/**

  @addtogroup RANGE
  @{

  Each range unit receives a 16-bit input and produces 3 outputs: 8 bits of MCOR, 16 bits of DIRPE2 and 8 bits of DIRPE3
  delta which together with the DIRPE2 bits give the DIRPE3 encoding of the input. Depending on the LTR controls it can
  produce between 0 and 32 bits of output.

  | LTR for range unit  | Output size (bits) | Output structure (lsb on left) |
  | :---:               | :---:              | :---:                          |
  | 0 (RANGE_DISABLE)   |                  0 |                              - |
  | 1 (MCOR_ONLY)       |                  8 |                           MCOR |
  | 2 (DIRPE2_ONLY)     |                 16 |                         DIRPE2 |
  | 3 (DIRPE3_ONLY)     |                 24 |            DIRPE2, DIRPE3DELTA |
  | 4 (DIRPE2_AND_MCOR) |                 24 |                   DIRPE2, MCOR |
  | 5 (DIRPE3_AND_MCOR) |                 32 |      DIRPE2, DIRPE3DELTA, MCOR |

 */

/**
 * @brief 48-bit configuration register for DIRPE range encoding with cumbersome legacy format
 */

/** 12 bits of data constitute lookup data for each 2-bit segment in the input i.e. 3 bit lookup for value of 0, 3 bit
    lookup for value of 1, 3 bit lookup for value of 2, 3 bit lookup for value of 3. Bits are interleaved in a contorted
    way.

    Bits  8, 4 and 0 of the segment give lookup for value of 0,
    Bits  9, 5 and 1 of the segment give lookup for value of 1,
    Bits 10, 6 and 2 of the segment give lookup for value of 2,
    Bits 11, 7 and 3 of the segment give lookup for value of 3 */

struct op_dirpe_reg {
    uint64_t bits; /**< 48 lsb are used to store useful 3-bit DIRPE information for 4 segments */
};

/** Reading a code from a DIRPE register */

#define GET_DIRPE_CODE(reg, seg_num, seg_val) (( (reg).bits >> ((seg_num) * 12 + (seg_val) + 6) & 4 ) \
                                               |((reg).bits >> ((seg_num) * 12 + (seg_val) + 3) & 2 ) \
                                               |((reg).bits >> ((seg_num) * 12 + (seg_val) + 0) & 1 ))

/** Writing a code to a DIRPE register */

#define SET_DIRPE_CODE(reg, seg_num, seg_val, code) {                   \
        (reg).bits &= ~(0x111ull << ((seg_num) * 12 + (seg_val)));      \
        (reg).bits |= ((uint64_t)(code) & 4)  << ((seg_num) * 12 + (seg_val) + 6); \
        (reg).bits |= ((uint64_t)(code) & 2)  << ((seg_num) * 12 + (seg_val) + 3); \
        (reg).bits |= ((uint64_t)(code) & 1)  << ((seg_num) * 12 + (seg_val) + 0); \
    }

/**
 * @brief MCOR register defining when one of the MCOR bits will be set by the range unit in the DBA search key
 */

struct op_mcor_reg {
    __EO_4(uint16_t lowest,               /**< The lowest value that causes the MCOR bit to get set in the DBA search key */
           uint16_t highest,              /**< The highest value that causes the MCOR bit to get set in the DBA search key */
           uint32_t width_minus_one_4:2,  /**< The number of nibbles of key compared against bounds (must be 3) */
           uint32_t unused:30);           /**< Unused */
};

/**
 * @}
 */

/**

  @addtogroup DBA
  @{

  The bits in the DBA can be configured into ABs of different physical shapes and logical configurations (entry
  widths). This enables area-efficient high-speed support for single-cycle searches in entries wider than 640 (480 and
  640) and efficient storage of entries 480 bits wide when the chip stores a mix of databases of width 480 and databases
  of width of 160 or smaller. It is possible to mix various shapes within the same superblock, but all ABs in a
  superblock that are searched in the same cycle have to have the same shape and the same entry width.

  @image html dba_configurations.png

  The possible configurations for an individual AB are defined by ::op_ab_confs. A pair of neighboring ABs divide
  the ternary bits amongst themselves differently depending on their configurations. Some combinations of configurations
  for the two ABs are invalid.

  | AB4 conf       | AB0 = 0 | AB0 = 1 | AB0 = 2 | AB0 = 3 | AB0 = 4 | AB0 = 5 | AB0 = 6 |
  | :---:          | :---:   | :---:   | :---:   | :---:   | :---:   | :---:   | :---:   |
  | 0 (normal 80)  |   valid |   valid |   valid | invalid | invalid | invalid | invalid |
  | 1 (normal 160) |   valid |   valid |   valid | invalid | invalid | invalid | invalid |
  | 2 (normal 320) |   valid |   valid |   valid | invalid | invalid | invalid | invalid |
  | 3 (wide 640)   | invalid | invalid | invalid |   valid | invalid | invalid | invalid |
  | 4 (small 80)   |   valid |   valid |   valid | invalid | invalid | invalid |   valid |
  | 5 (small 160)  |   valid |   valid |   valid | invalid | invalid | invalid |   valid |
  | 6 (big 480)    | invalid | invalid | invalid | invalid | invalid | invalid | invalid |

 */

/**
 * @brief Configurations supported for ABs in the Optimus Prime DBA
 */

enum op_ab_confs {
    KBP_OP_NORMAL_80 = 0,   /**< AB of normal physical shape configured as 4K 80-wide entries */
    KBP_OP_NORMAL_160 = 1,  /**< AB of normal physical shape configured as 2K 160-wide entries */
    KBP_OP_NORMAL_320 = 2,  /**< AB of normal physical shape configured as 1K 320-wide entries */
    KBP_OP_WIDE_640 = 3,    /**< AB of wide physical shape configured as 512 640-wide entries */
    KBP_OP_BIG_480 = 4,     /**< Big AB configured as 1K 480-wide entries */
    KBP_OP_SMALL_80 = 5,    /**< Small AB configured as 2K 80-wide entries */
    KBP_OP_SMALL_160 = 6    /**< Small AB configured as 1K 160-wide entries */
};

/**
 * @brief Post-AB shifts supported in the Optimus Prime DBA (no new information content w.r.t. ::op_ab_conf_reg)
 */

enum op_ab_shift {
    KBP_OP_SHIFT_0 = 0,       /**< 80 normal, 480 big require no index shift */
    KBP_OP_SHIFT_1 = 1,       /**< 160 normal requires right shift by 1 */
    KBP_OP_SHIFT_2 = 2,       /**< 320 normal and 160 narrow require right shift by 2 */
    KBP_OP_SHIFT_3 = 3,       /**<  640 wide require shift by 3*/
    KBP_OP_FUNNY_SHIFT = 4    /**< 80 narrow keeps the lsb and right-shifts by 1 the others */
};

/**
 * @brief The configuration register for the AB
 */

struct op_ab_conf_reg {
    __EO_9(uint32_t ena:1,         /**< Block is enabled for searches */
           uint32_t conf:3,        /**< Shape of block and width of entries ::op_ab_confs */
           uint32_t shift_count:3, /**< Redundant backwards-compatible description of shift ::op_ab_shift */
           uint32_t reserved_1:1,  /**< Reserved */
           uint32_t base_512:15,   /**< Number added to the 15 msb */
           uint32_t shift_dir:1,   /**< Unused, must be 0 */
           uint32_t reserved_2:5,  /**< Unused */
           uint32_t conf_copy:3,   /**< Must be same as conf */
           uint32_t unused);       /**< Software padding */
};

/**
 * @brief Hitbit bank select register
 */

struct op_udr_atr_reg {
    __EO_5(uint32_t data:8,    /**< MS Index bits */
           uint32_t mask:8,    /**< MS Index mask bits */
           uint32_t valid:1,   /**< hitbit Bank validity */
           uint32_t resv1:15,
           uint32_t resv2:32);  /**< Reserved Bits */
};



/**
 * @}
 */

/* OP Shadow LTR */
struct op_shadow_ltr
{
    uint64_t conflict_bitmap;       /**< Aid for instruction arbitration */
    struct op_kpu_segs_0_4 kpu_0_0; /**< 63 bits controlling parsing, enable,keyb_st_offset */
    struct op_kpu_segs_5_9 kpu_0_1; /**< 60 bits controlling parsing */
    struct op_kpu_segs_0_4 kpu_1_0; /**< 63 bits controlling parsing, enable,keyb_st_offset */
    struct op_kpu_segs_5_9 kpu_1_1; /**< 60 bits controlling parsing */
    struct op_kpu_segs_0_4 kpu_2_0; /**< 63 bits controlling parsing, enable,keyb_st_offset */
    struct op_kpu_segs_5_9 kpu_2_1; /**< 60 bits controlling parsing */
    struct op_kpu_segs_0_4 kpu_3_0; /**< 63 bits controlling parsing, enable,keyb_st_offset */
    struct op_kpu_segs_5_9 kpu_3_1; /**< 60 bits controlling parsing */
    struct op_range_ext r_e[3];     /**< 2 60-bit and one 40-bit registers controlling 16 range units total */
    uint64_t misc1;                 /**< 64-bit miscellaneous register */
    uint64_t misc2;                 /**< 64-bit miscellaneous register */
    uint64_t misc3;                 /**< 64-bit miscellaneous register */
    struct op_post_kpu_proc pkp[4]; /**< 4 42-bit registers define how outputs of the 4 KPUs are processed, BMRs */
    uint64_t ab_enable[4];          /**< 256b bitmap for enabling ABs, 63-0, 127-64, 191-128, 255-192 */
    uint64_t sb_key_sel[4];         /**< 4 48-bit registers with 16*3b selecting one of 8 keys for SBs 15-0, 31-16, 47-32, 63-48 */
    uint64_t res_map[16];           /**< 256*4b control which of the 16 priority encoders each AB feeds */
    struct op_res_ctrl res;         /**< 56-bit register controlling result generation */
    uint64_t misc4;                 /**< 64-bit miscellaneous register */
    uint64_t misc6[KBP_OP_MAX_UDCS];/**< 16 64-bit miscellaneous register */
    uint64_t misc7;                 /**< 64-bit miscellaneous register */
};


/* FIFO : DBA-> CR/UR */
struct op_dev_dba_fifo_reg
{
    __EO_6(uint32_t location:20,                      /**< 19: 0 location */
           uint32_t reserved1:10,                     /**< 29:20 reserved, write 0,s; on read unknown values */
           uint32_t error_type:2,                     /**< 31:30 error type from ECC: 0: 1b, 1: 2b, 2: 1b ECC: > 1b from parity, 3: reserve */
           uint32_t err_addrs_valid:1,                /**< 32    error address is valid or not */
           uint32_t clear_fifo:1,                     /**< 33    writing 1 will clear all FIFO entries */
           uint32_t reserved2:30);                    /**< 63:34 Reserved2 */
};

/* FIFO : UDA-> CR/UR */
struct op_dev_uda_fifo_reg
{
    __EO_9(uint32_t location:23,                     /**< 22: 0 location */
           uint32_t reserved1:5,                     /**< 27:23 reserved, write 0,s; on read unknown values */
           uint32_t m_error:1,                       /**< 28    Indicates more than one error of same type in the same cycle */
           uint32_t c_error:1,                       /**< 29    Indicates correctable error */
           uint32_t nc_error:1,                      /**< 30    Indicates non-correctable error */
           uint32_t reserved2:1,                     /**< 31    reserved, write 0,s; on read unknown values */
           uint32_t err_addrs_valid:1,               /**< 32    error address is valid or not */
           uint32_t clear_fifo:1,                    /**< 33    Writing 1 will flush the fifo. Its self clearing; read always returns 1'b0. */
           uint32_t reserved3:30);                   /**< 63:34 Reserved3 */
};

/* FIFO Status  : DBA-> CR/UR     RPT->UR     UIT-> CR/UR     UDA-> CR/UR */
struct op_dev_fifo_status_reg
{
    __EO_10(uint32_t fifo_rd_ptr:5,                       /**<  4: 0 FIFO read pointer; ECC error fifo read pointer */
            uint32_t reserved1:3,                         /**<  7: 5 reserved, write 0,s; on read unknown values */
            uint32_t fifo_wr_ptr:5,                       /**< 12: 8 FIFO write pointer; ECC error fifo write pointer */
            uint32_t reserved2:3,                         /**< 15:13 reserved, write 0,s; on read unknown values */
            uint32_t fifo_entry_cnt:6,                    /**< 21:16 FIFO count; number of entries in ECC FIFO */
            uint32_t reserved3:2,                         /**< 23:22 reserved, write 0,s; on read unknown values */
            uint32_t fifo_overflow:1,                     /**< 24    overflow on ECC error FIFO */
            uint32_t fifo_full:1,                         /**< 25    ECC error FIFO full */
            uint32_t reserved4:6,                         /**< 31:26 reserved, write 0,s; on read unknown values */
            uint32_t reserved5);                          /**< 63:32 Reserved5 */
};


/*
 * Defines addresses in the Optimus register space
 */

/** Address of the debug register : internal purpose */
#define KBP_OP_DEVICE_INDIRECT_DEBUG_CFG_REG 0x00000001
#define KBP_OP_DEVICE_INDIRECT_DEBUG_REG     0x00000002


/** Address of the device id register*/
#define KBP_OP_DEVICE_ID_REG                      0x00000000
/** Address of the device config register RO [update via MDIO]*/
#define KBP_OP_DEVICE_CONFIG_REG                  0x00000001


/** Address of the error status register port#0 and port#1 */
#define KBP_OP_DEVICE_ERROR_STATUS_PORT0          0x00000002
#define KBP_OP_DEVICE_ERROR_STATUS_PORT1          0x00000003

/** Address of the interrupt mask enable register port#0 and port#1 */
#define KBP_OP_DEVICE_INTR_MASK_ENABLE_PORT0      0x00000004
#define KBP_OP_DEVICE_INTR_MASK_ENABLE_PORT1      0x00000005

/** Address of the error enable register port#0 and port#1 */
#define KBP_OP_DEVICE_ERR_ENABLE_PORT0      0x00000006
#define KBP_OP_DEVICE_ERR_ENABLE_PORT1      0x00000007

/** Address of the interrupt mask enable register of CPU and PCIE */
#define KBP_OP_DEVICE_INTR_MASK_ENABLE_CPU      0x00000008
#define KBP_OP_DEVICE_INTR_MASK_ENABLE_PCIE     0x00000009

/** Address of the Parity intv register */
#define KBP_OP_DEVICE_PAR_INTV_REG             0x0000000A

/** Address of the Rate Control register */
#define KBP_OP_DEVICE_RATE_CTRL_REG            0x0000000B

/** Address of the scratch pad registers */
#define KBP_OP_DEVICE_SCRATCH_PAD_REG0             0x0000000E
#define KBP_OP_DEVICE_SCRATCH_PAD_REG1             0x0000000F

/** Start of address space for post-resolution index translation registers */
#define KBP_OP_REG_ITR_START                       0x0000C100
/** End of address space for post-resolution index translation registers */
#define KBP_OP_REG_ITR_END                         0x0000C13F

/** DBA UC ERROR FIFO register */
#define KBP_OP_REG_DBA_UC_FIFO                    0x00008000

/** DBA UC ERROR FIFO status register */
#define KBP_OP_REG_DBA_UC_FIFO_STS                0x00008001

/** DBA CR ERROR FIFO register */
#define KBP_OP_REG_DBA_CR_FIFO                    0x00008002

/** DBA CR ERROR FIFO status register */
#define KBP_OP_REG_DBA_CR_FIFO_STS                0x00008003


/** UDA CR ERROR FIFO register */
#define KBP_OP_REG_UDA_CR_FIFO                    0x0000C010

/** UDA CR ERROR FIFO status register */
#define KBP_OP_REG_UDA_CR_FIFO_STS                0x0000C011

/** UDA UC ERROR FIFO register */
#define KBP_OP_REG_UDA_UC_FIFO                    0x0000C012

/** UDA UC ERROR FIFO status register */
#define KBP_OP_REG_UDA_UC_FIFO_STS                0x0000C013

/** Start of the Age Translation Registers for HitBits */
#define KBP_OP_UDR_ATR_START                      0x0000C300

/** End of the Age Translation Registers for HitBits */
#define KBP_OP_UDR_ATR_END                        0x0000C30F

/** Start of the HitBits Bank register address space */
#define KBP_OP_UDR_HB_START                       0x001C0000

/** End of the HitBits Bank register address space */
#define KBP_OP_UDR_HB_END                         0x001CFFFF

/** LPT mode register */
#define KBP_OP_REG_LPT_MODE                       0x00008007

/** Base address of UDC register space */
#define KBP_OP_UDC_CFG_REG(udc_no)                 (0x0000C800 + (udc_no))

/** Start of address space for UDC config registers (bitmaps for which UDM used for alg nodes, which for AD) */
#define KBP_OP_REG_UDC_START                       0x0000C300
/** End of address space for UDC config registers (bitmaps for which UDM used for alg nodes, which for AD) */
#define KBP_OP_REG_UDC_END                         0x0000C30F

/** Start of address space for DBA-related registers */
#define KBP_OP_REG_DBA_START                       0x000F0000
/** Block configuration registers */
#define KBP_OP_REG_ADDR_BLK_CONFIG(bl_num)         (KBP_OP_REG_DBA_START + (bl_num) * 0x20)
/** Block mask register start */
#define KBP_OP_REG_BMR_START                       (KBP_OP_REG_DBA_START + 1)
/** Block mask registers */
#define KBP_OP_REG_ADDR_BMR(bl_num, bmr_num, pos)  (KBP_OP_REG_BMR_START + (bl_num) * 0x20 + (bmr_num) * 0x4 + (pos))
/** End of address space for DBA-related registers */
#define KBP_OP_REG_DBA_END                         0x000F1FFF

/** Start of address space for Logical Table Registers */
#define KBP_OP_REG_LTR_START                       0x00040000
/** AB enable bits -- one register per 64 array blocks */
#define KBP_OP_LTR_ADDR_BLOCK_SELECT(ltr, bl_64)    (0x00040000 + (ltr) * 0x100 + (bl_64))
/** Result map -- 4 bits per array block, 16 array blocks per register */
#define KBP_OP_LTR_ADDR_PARALLEL_SEARCH(ltr, bl_16) (0x00040010 + (ltr) * 0x100 + (bl_16))
/** DBA superblock key select -- 3 bits per superblock, 16 superblocks per register */
#define KBP_OP_LTR_ADDR_SB_KEY_SELECT(ltr, sb_16)   (0x00040050 + (ltr) * 0x100 + (sb_16))
/** First logical table register for given KPU */
#define KBP_OP_LTR_ADDR_KPU_0(ltr, kpu)             (0x0004005C + (ltr) * 0x100 + (kpu) * 2)
/** Second logical table register for given KPU */
#define KBP_OP_LTR_ADDR_KPU_1(ltr, kpu)             (0x0004005D + (ltr) * 0x100 + (kpu) * 2)
/** Range extraction */
#define KBP_OP_LTR_ADDR_RANGE_EXT(ltr, rng_6)       (0x00040070 + (ltr) * 0x100 + (rng_6))
/** Post-KPU key processing data for output of given KPU */
#define KBP_OP_LTR_ADDR_PKP(ltr, kpu)               (0x00040074 + (ltr) * 0x100 + (kpu))
/** Logical table register defining the widths of UDA keys */
#define KBP_OP_LTR_ADDR_UDA_KEY(ltr)                (0x00040080 + (ltr) * 0x100)
/** Search attribute register */
#define KBP_OP_LTR_ADDR_SRCH_ATTR(ltr)              (0x00040082 + (ltr) * 0x100)
/** AD hit bit configuration register */
#define KBP_OP_LTR_ADDR_AD_HB(ltr)                  (0x00040083 + (ltr) * 0x100)
/** Logical table register controlling result generation including AD */
#define KBP_OP_LTR_ADDR_AD_RES(ltr)                 (0x00040084 + (ltr) * 0x100)
/** One control register for each UDC */
#define KBP_OP_LTR_ADDR_UDC(ltr, udc)               (0x00040090 + (ltr) * 0x100 + (udc))
/** Conflict bitmap */
#define KBP_OP_LTR_ADDR_CONFLICT_BMP(ltr)           (0x000400F0 + (ltr) * 0x100)
/** End of address space for LTR-related registers */
#define KBP_OP_REG_LTR_END                         0x00047FFF

/** Start of address space for the registers used by range units */
#define KBP_OP_REG_RANGE_START                     0x00080000
/** Register with MCOR bounds for given bit produced by given unit */
#define KBP_OP_REG_MCOR(unit, bit)                 (0x00080000 + (unit) * 8  + (bit))
/** Register with DIRPE encoding data given byte in the 16-bit key used by given unit */
#define KBP_OP_REG_DIRPE(unit, byte)               (0x00080080 + (unit) * 2  + (byte))
/** End of address space for the registers used by range units */
#define KBP_OP_REG_RANGE_END                       0x0008009F
/** KBP_OP_REG_RANGE_START + KBP_OP_NUM_RANGE_UNITS * KBP_OP_MCOR_REGS_PER_UNIT
   + KBP_OP_NUM_RANGE_UNITS * KBP_OP_DIRPE_REGS_PER_UNIT - 1 */

/** Start of address space for context buffer : 40K of 80b, 5K of 640b      0-0xA000 */
#define KBP_OP_CB_DEPTH                           (40960)
#define KBP_OP_REG_CB_START                        0x00140000
/** End of address space for context buffer */
#define KBP_OP_REG_CB_END                          0x00149FFF
#define KBP_OP_ADDR_CONTEXT_BUFFER(x)             (0x00140000 + (x))

#define KBP_OP_ADDR_TYPE_BIT_IN_PIO_WRITE          (25)
/**Insert address type bit in the address */
#define KBP_OP_ADD_ADDR_TYPE(address, type)        ((address) + ((type) << KBP_OP_ADDR_TYPE_BIT_IN_PIO_WRITE))
/**Mask address type bit in the address */
#define KBP_OP_MASK_ADDR_TYPE(address, type)       ((address) - ((type) << KBP_OP_ADDR_TYPE_BIT_IN_PIO_WRITE))

/** UDA Scratchpad register */
#define KBP_OP_REG_UDA_SCRATCH_REG                 0x0000C000

/** UDA ECC Errors count register */
#define KBP_OP_REG_UDA_ECC_ERR_COUNTERS            0x0000C014

/** UDA ECC Errors count register */
#define KBP_OP_REG_UDR_HDR_FIFO_PERR_FIFO          0x0000C01A

/** UDR Key Fifo Perror Fifo register */
#define KBP_OP_REG_UDR_KEY_FIFO_PERR_FIFO          0x0000C01B

#define KBP_OP_R5_CONTROL_REG     0x00000812
#define KBP_OP_CPU_STATUS_REG     0x00000833
#define KBP_OP_GLOBAL_EVENT_EN    0x00000801
#define KBP_OP_ATCM_START_ADDR    0x06800000
#define KBP_OP_ATCM_END_ADDR      0x06804000

/* Start and End of EMC registers */
#define KBP_OP_EMC_REGS_START     0x7fe
#define KBP_OP_EMC_REGS_END       0x835

/* CPU Status register */
#define KBP_OP_CPU_EMC_STATUS_REG (0xb)

/* UTR Start and End registers */
#define KBP_OP_UTR_REG_START    0xc200
#define KBP_OP_UTR_REG_END      0xc2ff

enum kbp_dev_op_parity_inject_type {
    KBP_OP_DISABLE_ERR_INJECT = 0,

    KBP_OP_DBA_ERR_INJECT = 1, /* for DBA and Advance DBA */
    KBP_OP_UDA_ERR_INJECT = 2, /* associated data or advance LSN instructions */
    KBP_OP_UIT_ERR_INJECT = 4, /* for UDR/UIT */
    KBP_OP_ALL_ERR_INJECT = 8, /* generic one for all error above */
    KBP_OP_ERR_INJECT_END
};


enum kbp_dev_op_ltr_reg_type {
    /** Conflict bitmap Register*/
    KBP_OP_LTR_CONFLICT_BITMAP_REG = 0,
    /** KCR-0 logical table register for given KPU */
    KBP_OP_LTR_KPU0_KCR0_REG,
    KBP_OP_LTR_KPU1_KCR0_REG,
    KBP_OP_LTR_KPU2_KCR0_REG,
    KBP_OP_LTR_KPU3_KCR0_REG,
    /** KCR-1 logical table register for given KPU */
    KBP_OP_LTR_KPU0_KCR1_REG,
    KBP_OP_LTR_KPU1_KCR1_REG,
    KBP_OP_LTR_KPU2_KCR1_REG,
    KBP_OP_LTR_KPU3_KCR1_REG,
    /** Range extraction registers */
    KBP_OP_LTR_RANGE_EXT_0_REG,
    KBP_OP_LTR_RANGE_EXT_1_REG,
    KBP_OP_LTR_RANGE_EXT_2_REG,
    /** AB enable bits -- one register per 64 array blocks */
    KBP_OP_LTR_AB_ENABLE_0_REG,
    KBP_OP_LTR_AB_ENABLE_1_REG,
    KBP_OP_LTR_AB_ENABLE_2_REG,
    KBP_OP_LTR_AB_ENABLE_3_REG,
    /** DBA superblock key select registers */
    KBP_OP_LTR_SB_KEY_SELECT_0_REG,
    KBP_OP_LTR_SB_KEY_SELECT_1_REG,
    KBP_OP_LTR_SB_KEY_SELECT_2_REG,
    KBP_OP_LTR_SB_KEY_SELECT_3_REG,
    /** Result map registers */
    KBP_OP_LTR_PARALLEL_SEARCH_0_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_1_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_2_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_3_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_4_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_5_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_6_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_7_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_8_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_9_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_10_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_11_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_12_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_13_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_14_REG,
    KBP_OP_LTR_PARALLEL_SEARCH_15_REG,
    /** Logical table register controlling result generation including AD */
    KBP_OP_LTR_AD_RESULT_REG,
    /** Miscellaneous Registers */
    KBP_OP_LTR_MISC1_REG,
    KBP_OP_LTR_MISC2_REG,
    KBP_OP_LTR_MISC3_REG,
    KBP_OP_LTR_MISC4_REG,
    KBP_OP_LTR_PKP_0_REG,
    KBP_OP_LTR_PKP_1_REG,
    KBP_OP_LTR_PKP_2_REG,
    KBP_OP_LTR_PKP_3_REG,
    KBP_OP_LTR_MISC6_0_REG,
    KBP_OP_LTR_MISC6_1_REG,
    KBP_OP_LTR_MISC6_2_REG,
    KBP_OP_LTR_MISC6_3_REG,
    KBP_OP_LTR_MISC6_4_REG,
    KBP_OP_LTR_MISC6_5_REG,
    KBP_OP_LTR_MISC6_6_REG,
    KBP_OP_LTR_MISC6_7_REG,
    KBP_OP_LTR_MISC6_8_REG,
    KBP_OP_LTR_MISC6_9_REG,
    KBP_OP_LTR_MISC6_10_REG,
    KBP_OP_LTR_MISC6_11_REG,
    KBP_OP_LTR_MISC6_12_REG,
    KBP_OP_LTR_MISC6_13_REG,
    KBP_OP_LTR_MISC6_14_REG,
    KBP_OP_LTR_MISC6_15_REG,
    KBP_OP_LTR_MISC7_REG,
    /** Register end value */
    KBP_OP_LTR_REG_END
};

/**
 *   Writes a data/mask of specified length (80b/160b/320b/480b/640b) to the specified row and ab_num.
 *   The address has to be MSB location. The data and mask are passed in as pointers, and the length
 *   in bytes. The array is read from MSB down to LSB. Data can be written in either DM or XY mode.
 *   valid_bit is set 1 to validate, 0 to invalidate the entries via this API
 *
 * @param device Valid device handle.
 * @param blk_num DBA block number
 * @param entry_nr Location of the entry in the DBA block
 * @param length Length of rows occupied by entry (multiple of 10B)
 * @param data Valid data pointer to write
 * @param mask Valid mask pointer to write
 * @param is_xy Whether data and mask are specified in XY format or not
 * @param valid_bit 1 to validate the entry, 0 to invalidate
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_op_dba_write(struct kbp_device * device, int32_t blk_num, int32_t entry_nr,
                               uint32_t length, uint8_t *data, uint8_t *mask, uint8_t is_xy,
                               uint32_t valid_bit);

/**
 *   Writes a data/mask of length 80b (single row) to the specified row and ab_num.
 *   The data and mask are passed in as pointers, and default length is 10 bytes.
 *   Data can be written in either DM or XY mode. valid_bit is set 1 to validate,
 *   0 to invalidate the entries via this API
 *
 * @param device Valid device handle.
 * @param blk_num DBA block number
 * @param entry_nr Location of the entry in the DBA block
 * @param data Valid data pointer to write
 * @param mask Valid mask pointer to write
 * @param is_xy Whether data and mask are specified in XY format or not
 * @param valid_bit 1 to validate the entry, 0 to invalidate
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_dm_op_dba_write_row(struct kbp_device * device, int32_t blk_num, int32_t entry_nr,
                                   uint8_t *data, uint8_t *mask, uint8_t is_xy, uint32_t valid_bit);

/**
 * @param device Valid device handle.
 * @param blk_num valid AB no
 * @param row_num valid row number ti invalidate entry
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op_dba_invalidate_hw_row(struct kbp_device *device, int32_t blk_num, int32_t row_num);


/**
 *   Reads a data/mask of specified length (80b/160b/320b/480b/640b) from the specified row and ab_num.
 *   The address has to MSB location. The data and mask are passed in as pointers, and the length
 *   is in bytes. The array is read from MSB down to LSB. Data read is always in XY mode.
 *
 * @param device Valid device handle.
 * @param blk_num Array block number.
 * @param entry_nr MSB row number.
 * @param length Length of the array to be read (multiple of 10B)
 * @param o_data Valid data pointer to read
 * @param o_mask Valid mask pointer to read
 * @param valid_bit 1 indicates valid entry, 0 invalid
 *
 * @return KBP_OK on success or an error code otherwise.
 */


kbp_status kbp_dm_op_dba_read(struct kbp_device *device, uint16_t blk_num, uint32_t entry_nr,
                              uint32_t length, uint32_t *valid_bit, uint8_t *o_data, uint8_t *o_mask);


/**
 *   Reads a data/mask of length 80b from the specified row and ab_num.
 *   The address has to MSB location. The data and mask are passed in as pointers, and the length
 *   is in bytes. The array is read from MSB down to LSB. Data read is always in XY mode and returns the vbit (for X loc) and parity if any.
 *
 * @param device Valid device handle.
 * @param blk_num Array block number.
 * @param entry_nr MSB row number.
 * @param x_or_y data/mask of the array to be read (10B)
 * @param valid_bit Valid bit of read data (for mask its same as of the data)
 * @param o_par any parity on the particular data/mask row on read
 * @param o_data read data/mask
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_dm_op_dba_read_x_or_y(struct kbp_device *device, uint16_t blk_num, uint32_t entry_nr,
                                     uint8_t x_or_y, uint32_t *valid_bit, uint32_t *o_par, uint8_t *o_data);

/**
 *   Writes a stream of associated data (must be 32b/64b/128b/256b)to the specified UDA address,
 *   the associated data written from MSB to LSB, so udaAddr has to be MSB address
 *
 * @param device Valid device handle.
 * @param address MSB UDA address location.
 * @param data Valid associated data
 * @param length Length of the associated data to be written (must be 32b/64b/128b/256b)
 * @param algo_ad Whether regular AD write or algorithmic AD write
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_op_uda_write(struct kbp_device *device, uint32_t address, uint8_t *data,
                               uint8_t length, uint32_t algo_ad);

/**
 *   Reads a stream of associated data (must be 32b/64b/128b/256b) from the specified UDA address,
 *   the associated data read form MSB to LSB, so udaAddr has to be MSB address
 *
 * @param device Valid device handle.
 * @param address MSB UDA address location.
 * @param o_data Valid associated data read (which will be read from device as chunks of 32b from MSB to LSB)
 * @param length Length of the associated data to be read (must be 32b/64b/128b/256b)
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_op_uda_read(struct kbp_device *device, uint32_t address, uint8_t length,
                              uint8_t *o_data);

/**
 *   Performs the Operations, these can be Block and LSN operations
 *
 * @param device Valid device handle.
 * @param opcode Operation code
 * @param bytes Stream of data
 * @param length Length of data stream
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_op_command_send(struct kbp_device *device, uint32_t opcode, uint32_t length,
                                  uint8_t *bytes);

/**
 *   Reads from an LTR register depending on LTR register type.
 *
 * @param device Valid device handle.
 * @param ltr_num valid LTR number
 * @param reg_type Valid LTR register type
 * @param o_data Array which will hold the data read from LTR
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op_ltr_read(struct kbp_device * device, uint8_t ltr_num,
                              enum kbp_dev_op_ltr_reg_type reg_type, struct op_shadow_ltr * o_data);

/**
 *   Writes to an LTR register depending on LTR register type.
 *
 * @param device Valid device handle.
 * @param ltr_num Valid LTR number
 * @param reg_type Valid LTR register type
 * @param data Array which holds the data to write to LTR
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op_ltr_write(struct kbp_device * device, uint8_t ltr_num,
                               enum kbp_dev_op_ltr_reg_type reg_type, struct op_shadow_ltr * data);

/**
 *   Performs search. A single search key can be sent from either thread
 *   to produce the expected result
 *
 * @param device Valid device handle.
 * @param ltr_num Valid LTR number
 * @param cb_addrs The Context buffer address
 * @param key The Master key bytes
 * @param key_len The number of valid bytes in key
 * @param o_search_results The parsed search result returned from the device
 *
 * @return KBP_OK on successful completion of call and result contents are valid. Or an error code
 */
kbp_status kbp_dm_op_cbwcmp(struct kbp_device * device, uint8_t ltr_num, uint32_t cb_addrs,
                            const uint8_t *key, uint32_t key_len,
                            struct kbp_search_result * o_search_results);

/**
 * @param device Valid device handle.
 * @param address valid address to read
 * @param data array which holds the data to write
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op_reg_write(struct kbp_device * device, uint32_t address, uint8_t *data);

/**
 * @param device Valid device handle.
 * @param address valid address to read
 * @param o_data array which holds the read data
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op_reg_read(struct kbp_device * device, uint32_t address, uint8_t *o_data);

/**
 * Poll the register for maximum "count" times until data at specific bit
 * positions specified by mask read from the register is equal to
 * 1 for power up and 0 for power down
 * Specific bit positions are those where mask has bit value 0.
 * Power up:
 * e.g. data = 0x00000000_20000000, mask = 0xFFFFFFFF_dFFFFFFF
 * Poll until bit 28 becomes 1.
 *
 * Power down:
 * e.g. data = 0xFFFFFFFF_ FFFFFFFE, mask = 0xFFFFFFFF_FFFFFFFE
 * Poll until bit 0 becomes 0.
*
 * @param device Valid device handle.
 * @param address Address of the status register to poll
 * @param data array which holds the data
 * @param mask Valid mask to compare
 * @param count Number of times to poll reg
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op_poll_reg(struct kbp_device * device, uint32_t address, uint64_t data,
                              uint64_t mask, uint32_t count);

/**
 * parity injection for OP is always done from the advanced error injection mechanism
 *
 * @param device Valid device handle.
 * @param inject type for DBA/RPT/UDA/UIT of type enum kbp_dev_op_parity_inject_type (bit fields)
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op_inject_parity(struct kbp_device *device, uint32_t inject_type);

/**
 * Logs the Data
 *
 * @param f File pointer to log the data
 * @param data array of bytes to log
 * @param len_8 length of the array in bytes
 */

void kbp_dm_op_log_data(FILE *f, uint8_t *data, uint32_t len_8, uint8_t log_bkdoor_api);

/**
 * Logs the address
 *
 * @param f File pointer to log the address
 * @param data array of bytes to log
 * @param len_8 length of the array in bytes
 */

void kbp_dm_op_log_address(FILE *f, uint8_t *data, uint32_t len_8);

/**
 * Logs the Data and address
 *
 * @param f File pointer to log the data
 * @param text Type of logging
 * @param address address to log
 * @param data array of bytes to log
 * @param len_8 length of the array in bytes
 */

void kbp_dm_op_log_addr_data(FILE *f, char *text, uint32_t address, uint8_t *data, uint32_t len_8);

/**
 * Logs the Register data, address and name
 *
 * @param device Valid device handle
 * @param address register address
 * @param fp file pointer to log the data
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op_log_reg(struct kbp_device *device, uint32_t address, FILE *fp);

/**
 * Logs the EMC Register data, address and name
 *
 * @param device Valid device handle
 * @param address register address
 * @param fp file pointer to log the data
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op_log_emc_regs(struct kbp_device *device, FILE *f);

/**
 * Read the Device Identification Register (DIR) and get the resources according to the device type
 *
 * @param device Valid device handle
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op_query_capabilities(struct kbp_device *device);

/**
 * Read the Interrupt Mask Enable, Device Errors (#port0 and #port), Interrupt mask PCIE/CPU
 * registers and set the default DBA, UDA and KCR interrupts. Application can set needed bits by PIO writes
 *
 * @param device Valid device handle
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op_set_interrupt_state(struct kbp_device *device);

/**
 * Clear the Error status registers (#port0 and #port)
 *
 * @param device Valid device handle
 * @param is_all_bits register address
 *
 *  if is_all_bits = 1: write on clear and read FIFO only parity bits 53:32  (parity)
 *  if is_all_bits = 2: write on clear all bits other than parity bits       (interface)
 *  if is_all_bits = 3: clear all bits
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op_clear_errors(struct kbp_device *device, uint32_t is_all_bits);


#ifdef __cplusplus
}
#endif

#endif /* __DEVICE_OP_H */
