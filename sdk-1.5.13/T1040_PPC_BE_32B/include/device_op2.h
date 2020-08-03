/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DEVICE_OP2_H
#define __DEVICE_OP2_H

#include "kbp_portable.h"
#include "errors.h"
#include "device.h"
#include "instruction.h"

#ifdef __cplusplus
extern "C" {
#endif

 /**
  * Common Index Range Allocation Granularity
  */
#define KBP_CIR_GRANULARITY                                 65536

 /**
  * Common Index Range Bitmap Size
  */
#define KBP_CIR_BITMAP_SIZE                                 1024


/**
 * @cond STATS
 *
 * @file device_op2.h
 *
 * Defines enums and structures for registers and various software-visible
 * fields for Optimus Prime 2 KBP chip.
 */


/**
 * @addtogroup STATS_SLTR
 * @{
 */

/** Number of cores per OP2 chip */
#define KBP_OP2_NUM_CORES                                   (2)

/** Number of UDCs per OP2 chip. */
#define KBP_OP2_TOTAL_NUM_UDCS                              32

/** Number of UDMs per OP2 chip. */
#define KBP_OP2_TOTAL_NUM_UDMS                              128

/** Number of USBs per OP2 chip. */
#define KBP_OP2_TOTAL_NUM_USBS                              (KBP_OP2_TOTAL_NUM_UDMS * KBP_OP_USBS_PER_UDM)

/** Number (total) of SLTR registers per OP2 KBP chip. */
#define KBP_OP2_TOTAL_NUM_SLTRS                             128

/** Number of counter register groups in each SLTR. */
#define KBP_OP2_NUM_SLTRS_REGISTER_GROUPS                   4

/** The Number of SLTR Registers Rows in each of the SCE Core Ingress/Egress. */
#define KBP_OP2_NUM_SLTR_REGS_PER_SCE_CORE                  64

/** The Number of SLTR Registers Rows in each of the SCE Pipes Ingress/Egress. */
#define KBP_OP2_NUM_SLTR_REGS_PER_SCE_PIPE                  16

/** The default length of a value VSF inside stats record. */
#define KBP_OP2_STATS_DEFAULT_VALUE_FIELD_LENGTH            14

/** Supported minimum length for Value field inside Stats record */
#define KBP_OP2_STATS_VALUE_FIELD_MIN_NUM_BITS              10

/** Supported maximum length for Value field inside Stats record */
#define KBP_OP2_STATS_VALUE_FIELD_MAX_NUM_BITS              14

/** Supported minimum opcode extension length in bits */
#define KBP_OP2_STATS_MIN_OPCODE_EXT_LEN                    1

/** Supported maximum opcode extension length in bits */
#define KBP_OP2_STATS_MAX_OPCODE_EXT_LEN                    8

/** Supported maximum opcode extension value */
#define KBP_OP2_STATS_MAX_OPCODE_EXT_VALUE                  255

/** The default OPCODE length for OP2. */
#define KBP_OP2_STATS_RECORD_OPCODE_LEN                     2

/** The default set index size for OP2. */
#define KBP_OP2_STATS_DEFAULT_SET_INDEX_SIZE                8

/** The max set index attribute value for OP2. */
#define KBP_OP2_STATS_MAX_SET_INDEX_ATTR_VALUE              ((1 << KBP_OP2_STATS_DEFAULT_SET_INDEX_SIZE) - 1)

/** Minimum Stats database set size supported */
#define KBP_OP2_STATS_MIN_SET_SIZE                          1

/** Maximum Stats database set size supported */
#define KBP_OP2_STATS_MAX_SET_SIZE                          8

/** The Max stats pointer VSF length for OP2. */
#define KBP_OP2_STATS_MAX_PTR_LEN                           21

/** The 64b OP2 address space length. */
#define KBP_OP2_STATS_64b_ADDRESS_SPACE_LEN                 26

/** The max values in incoming record for each group */
#define KBP_OP2_STATS_GROUP_MAX_VALUES                      1

/** The max set indexes in incoming record for each group */
#define KBP_OP2_STATS_GROUP_MAX_SET_INDEXES                 6

/** The max pointers in incoming record for each group */
#define KBP_OP2_STATS_GROUP_MAX_PTRS                        4

/** Maximum number of counter updates per stats record */
#define KBP_OP2_STATS_MAX_UPDATES_PER_RECORD                4

/** Threshold for SRE Record FIFOs */
#define KBP_OP2_STATS_REC_FIFO_THRESHOLD                    4

/** The # Rows in Stats/CT address translation CAM. */
#define KBP_OP2_NUM_STATS_ADDR_CAM_ROWS                     64

/** The # SRE lookup Registers per core (NULL, Ingress, Egress and Reserved records). */
#define KBP_OP2_NUM_SRE_LOOKUP_REGS_CORE                    4

/** The # Ingress/Egress Registers per SRE Core. */
#define KBP_OP2_NUM_SRE_ING_LOOKUP_REGS_CORE                256
#define KBP_OP2_NUM_SRE_EGR_LOOKUP_REGS_CORE                KBP_OP2_NUM_SRE_ING_LOOKUP_REGS_CORE

/** Max number of stats tables supported by device */
#define KBP_OP2_MAX_NUM_STATS_TABLES                        64

/** Total counter operations in parallel. */
#define KBP_OP2_TOTAL_PIPELINE_COUNTERS                     8

/** Number of UDC SCP CTRL Registers per core. */
#define KBP_OP2_NUM_UDC_SCP_CTRL_REG_PER_CORE               16

/** Number of SCP_STACE_LFSR_MASK Registers per core */
#define KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE                  16

/** Number of SCP_STACE_LFSR Registers per core */
#define KBP_OP2_NUM_LFSR_REG_PER_CORE                       16

/** Number of SIA LUTs per SLTR Group. */
#define KBP_OP2_NUM_SIA_LUTS_PER_SLTR_GROUP                 16

/** Number of SIA LUT Registers (each is 64b) per LUT. */
#define KBP_OP2_NUM_SIA_LUT_REGS_PER_LUT                    16

/** Number of SIA per LUT register */
#define KBP_OP2_NUM_SIA_PER_LUT_REGISTER                    16

/** Valid bit position in the 4b SIA data */
#define KBP_OP2_SIA_VALID_BIT_POSITION                      0

/** Number of bits for SIA data */
#define KBP_OP2_SIA_NUM_DATA_BITS                           4

/** Number of 64b registers per SLTR group */
#define KBP_OP2_NUM_REG_PER_SLTR_GROUP                      3

/** Maximum length of OP2 Stats record in bytes/bits. */
#define KBP_OP2_MAX_STATS_RECORD_SIZE_IN_BYTES              12
#define KBP_OP2_MAX_STATS_RECORD_SIZE_IN_BITS               96

/** SRE port macro data burst size. This is for DNX (Jericho) only. */
#define KBP_OP2_SRE_PORT_MACRO_BURST_SIZE_IN_BYTES          64
#define KBP_OP2_SRE_PORT_MACRO_BURST_SIZE_IN_BITS           512
#define KBP_OP2_SRE_OPCODE_MASK                             0xC0
#define KBP_OP2_SRE_MIN_STATS_RECORD_SIZE_IN_BYTES          8
#define KBP_OP2_SRE_MAX_STATS_RECORD_SIZE_IN_BYTES          12

/** Number of rows in reverse counters/stats address translation (lookup) table (RCATT). */
#define KBP_OP2_NUM_RCATT_ROWS                              512

/** Number of supported counter types for OP2. */
#define KBP_OP2_NUM_SUPPORTED_COUNTER_TYPES                 4

/** Counter Eviction message notification bit mask */
#define KBP_OP2_COUNTER_NOTIFICATION_BIT_MASK               (0x4ULL)

/** Mask for Counter type within Counter Eviction message */
#define KBP_OP2_COUNTER_MESSAGE_COUNTER_TYPE_MASK           (0x3ULL)

/** Inverted Mask for 61b Host Memory address within Counter Eviction Message */
#define KBP_OP2_COUNTER_MESSAGE_HOST_ADDR_MASK              (~0x7ULL)

/** Shift for 61b Host Memory address within Counter Eviction Message */
#define KBP_OP2_COUNTER_MESSAGE_HOST_ADDR_SHIFT             (3)

/** Mask for 15b counter offset for the 64b Counter Eviction Message Addr */
#define KBP_OP2_COUNTER_MESSAGE_COUNTER_OFFSET_MASK         (0x3FFF8ULL)

/** Values for Notification types */
#define KBP_OP2_NOTIFICATION_TYPE_ERROR                     (0x0)
#define KBP_OP2_NOTIFICATION_TYPE_DONE                      (0x2)
#define KBP_OP2_NOTIFICATION_TYPE_DONE_WITH_ERROR           (0x3)

/** Various types of Notification Sources */
#define KBP_OP2_NOTIF_SOURCE_INDIVIDUAL_INSTR               (0x0)
#define KBP_OP2_NOTIF_SOURCE_BLK_INSTR                      (0x1)
#define KBP_OP2_NOTIF_SOURCE_DYN_EVICT_AGE_SCAN_INSTR       (0x2)
#define KBP_OP2_NOTIF_SOURCE_CRM_EVICT_INSTR                (0x3)

/** Various types for Notification data types */
#define KBP_OP2_NOTIF_DATA_TYPE_AGE                         (0x1)
#define KBP_OP2_NOTIF_DATA_TYPE_COUNTER                     (0x2)

/** Maximum Tx DMA Channels supported by OP2 */
#define KBP_OP2_NUM_TX_DMA_CHANNELS                         (5)

/** Counter Scan Bulkread size */
#define KBP_OP2_COUNTER_SCAN_BULK_READ_SIZE                 (32767)

/** Age Scan Bulkread size */
#define KBP_OP2_AGE_SCAN_BULK_READ_SIZE                     (KBP_OP2_COUNTER_SCAN_BULK_READ_SIZE)

/** DMA Buffer sizes in OP2. Buffer is 64b wide */
#define KBP_OP2_TX_DMA_BUFFER_SIZE_CP_TRAFFIC               (1  * 1024)
#define KBP_OP2_TX_DMA_BUFFER_SIZE_REQSRC1                  (32 * 1024)
#define KBP_OP2_TX_DMA_BUFFER_SIZE_COUNTER_EVICTION         (8  * 1024)
#define KBP_OP2_TX_DMA_BUFFER_SIZE_NON_SCAN_BULK_READ       (1  * 1024)
#define KBP_OP2_TX_DMA_BUFFER_SIZE_COUNTER_BULK_READ        (64 * 1024)
#define KBP_OP2_TX_DMA_BUFFER_SIZE_AGE_SCAN                 (32 * 1024)

/** Default DMA channels assigned for different operations */
#define KBP_OP2_TX_DMA_CHANNEL_CP_TRAFFIC                   (0)
#define KBP_OP2_TX_DMA_CHANNEL_REQSRC1                      (1)
#define KBP_OP2_TX_DMA_CHANNEL_COUNTER_EVICTION             (2)
#define KBP_OP2_TX_DMA_CHANNEL_NON_SCAN_BULK_READ           (3)
#define KBP_OP2_TX_DMA_CHANNEL_COUNTER_BULK_READ            (4)
#define KBP_OP2_TX_DMA_CHANNEL_AGE_SCAN                     (1)

/** Hardware Accelerator related configuration values */
#define KBP_OP2_HWA_NON_BULK_READ_TIMEOUT_COUNT             (0x40000)
#define KBP_OP2_HWA_BULK_READ_TIMEOUT_COUNT                 (0x40000)
#define KBP_OP2_HWA_OUTSTANDING_READ_COUNT                  (1)


/** SRE STATS AND COUNTER REGISTERS */
#define FRAME0_DROP_CNT_REG                     0x404022
#define PARTIAL_FRAME0_DROP_CNT_REG             0x404023
#define FRAME0_DROP_STATUS_REG                  0x404024
#define FRAME1_DROP_CNT_REG                     0x404025
#define PARTIAL_FRAME1_DROP_CNT_REG             0x404026
#define FRAME1_DROP_STATUS_REG                  0x404027
#define REC_FIFO_THRESHOLD_REG                  0x404028
#define FRAME0_ACC_CNT_REG                      0x40402A
#define FRAME0_REC_CNT_REG                      0x40402B
#define FRAME1_ACC_CNT_REG                      0x40402C
#define FRAME1_REC_CNT_REG                      0x40402D
#define FRAME0_DROP_CNT_FIFO_FULL_REG           0x40402E
#define FRAME1_DROP_CNT_FIFO_FULL_REG           0x40402F
#define KBP_OP2_STATS_EVENT_COUNTER_ENABLE_REG  0x40FFFF

#define SRE_STATS_AND_COUNTER_REG_BASE 0x4D4000
#define INGRESS_REC0_REG (SRE_STATS_AND_COUNTER_REG_BASE + 0)     /** Total number of ingress records send to SCE for pipe 0 */
#define INGRESS_REC1_REG (SRE_STATS_AND_COUNTER_REG_BASE + 1)     /** Total number of ingress records send to SCE for pipe 1 */
#define EGRESS_REC0_REG  (SRE_STATS_AND_COUNTER_REG_BASE + 2)     /** Total number of egress records send to SCE for pipe 0 */
#define EGRESS_REC1_REG  (SRE_STATS_AND_COUNTER_REG_BASE + 3)     /** Total number of egress records send to SCE for pipe 1 */

/** SCE STATS AND COUNTER REGISTERS */
#define SCE_STATS_AND_COUNTER_REG_BASE 0x4D8000
#define XSW_NUM_CMD_SENT_REG SCE_STATS_AND_COUNTER_REG_BASE + 0   /** total number of commands sent out of Switch */
#define SCE_NUM_CMD_SENT_REG SCE_STATS_AND_COUNTER_REG_BASE + 0x2000  /** total number of commands sent for one sce_core */

#define SCE_NUM_CMD_SENT_REG SCE_STATS_AND_COUNTER_REG_BASE + 0x2000  /** total number of commands sent for one sce_core */

#define SCE_XSW_CONF_REG_BASE 0x408000
#define XSW_CONF_REG_BASE (SCE_XSW_CONF_REG_BASE + 0x2000)
#define XSW_ERR_REG (XSW_CONF_REG_BASE + 0x100)
#define XSW_NUM_CMD_DROP_REG (XSW_CONF_REG_BASE + 0x102)

#define UDR_REGISTERS_BASE                    0xC000
#define Age_Scan_Control_Register            (UDR_REGISTERS_BASE + 0xE)

#define RATE_CNTROL_STATS_REG (0x6)
#define RATE_CNTROL_REG_SEARCH  (0xc)

/** Start of the HitBits Bank register address space */
#define KBP_OP2_UDR_HB_VALID_START                 0x001D0000

/** End of the HitBits Bank register address space */
#define KBP_OP2_UDR_HB_VALID_END                   0x001DFFFF

struct op2_hb_trans_table
{
    uint32_t cam_addr:10;               /* Cam Address bits */
    uint32_t cam_maskaddr:10;           /* Cam Mask Address bits */
    uint32_t valid:1;                   /* Valid Bit */
    uint32_t pad:11;                    /* PAD 0 */
    uint32_t pad1;                      /* PAD 1 */
};

/**
 * @brief Enumeration to supported OP2 Stats/Counters Storage Granularities.
 *
 */
enum op2_stats_storage_granularity {
    OP2_STATS_STORAGE_GRANULARITY_64K = 0,
    OP2_STATS_STORAGE_GRANULARITY_128K = 1,
    OP2_STATS_STORAGE_GRANULARITY_256K = 2,
    OP2_STATS_STORAGE_GRANULARITY_512K = 3
};

/**
 * @brief Enumeration to supported OP2 Stats/Counters eviction methods.
 *
 */
enum op2_counter_eviction_type {
    OP2_COUNTER_EVICTION_TYPE_DYNAMIC = 0,      /**< STACE or dynamic eviction. */
    OP2_COUNTER_EVICTION_TYPE_BLK_READ = 1,     /**< Stats Bulk Read. */
};


/**
 *   @brief Defines the Set Index Lookup Table (LuT) for SCE.
 *   There are 256 per pointer group.
 *
 */
struct op2_sia_lut {
    __EO_32(uint64_t vld_bit_0:1,                  /**< Valid bit for sia[3:0]==15. */
    uint64_t set_idx_0:3,          /**< Set index for sia[3:0]==15.  */
    uint64_t vld_bit_1:1,                  /**< Valid bit for sia[3:0]==14. */
    uint64_t set_idx_1:3,                  /**< Set index for sia[3:0]==14.  */
    uint64_t vld_bit_2:1,                  /**< Valid bit for sia[3:0]==13. */
    uint64_t set_idx_2:3,                  /**< Set index for sia[3:0]==13.  */
    uint64_t vld_bit_3:1,                  /**< Valid bit for sia[3:0]==12. */
    uint64_t set_idx_3:3,                  /**< Set index for sia[3:0]==12.  */
    uint64_t vld_bit_4:1,                  /**< Valid bit for sia[3:0]==11. */
    uint64_t set_idx_4:3,                  /**< Set index for sia[3:0]==11.  */
    uint64_t vld_bit_5:1,                  /**< Valid bit for sia[3:0]==10. */
    uint64_t set_idx_5:3,                  /**< Set index for sia[3:0]==10.  */
    uint64_t vld_bit_6:1,                   /**< Valid bit for sia[3:0]==9. */
    uint64_t set_idx_6:3,                   /**< Set index for sia[3:0]==9.  */
    uint64_t vld_bit_7:1,                   /**< Valid bit for sia[3:0]==8. */
    uint64_t set_idx_7:3,                   /**< Set index for sia[3:0]==8.  */
    uint64_t vld_bit_8:1,                   /**< Valid bit for sia[3:0]==7. */
    uint64_t set_idx_8:3,                   /**< Set index for sia[3:0]==7.  */
    uint64_t vld_bit_9:1,                   /**< Valid bit for sia[3:0]==6. */
    uint64_t set_idx_9:3,                   /**< Set index for sia[3:0]==6.  */
    uint64_t vld_bit_10:1,                   /**< Valid bit for sia[3:0]==5. */
    uint64_t set_idx_10:3,                   /**< Set index for sia[3:0]==5.  */
    uint64_t vld_bit_11:1,                   /**< Valid bit for sia[3:0]==4. */
    uint64_t set_idx_11:3,                   /**< Set index for sia[3:0]==4.  */
    uint64_t vld_bit_12:1,                   /**< Valid bit for sia[3:0]==3. */
    uint64_t set_idx_12:3,                   /**< Set index for sia[3:0]==3.  */
    uint64_t vld_bit_13:1,                   /**< Valid bit for sia[3:0]==2. */
    uint64_t set_idx_13:3,                   /**< Set index for sia[3:0]==2.  */
    uint64_t vld_bit_14:1,                   /**< Valid bit for sia[3:0]==1. */
    uint64_t set_idx_14:3,                   /**< Set index for sia[3:0]==1.  */
    uint64_t vld_bit_15:1,                  /**< Valid bit for sia[3:0]==0. */
    uint64_t set_idx_15:3);                   /**< Set index for sia[3:0]==0.  */
    };

/**
 *   @brief Defines the stats table property inside SLTR per each counter
 *   pointer group.
 *
 *   Each SLTR register has multiple counter pointer groups. In Jericho case
 *   it's 2 but expected to be up to 4.
 */

struct op2_stats_cntr_reg2
{
    __EO_12(uint64_t ptr_vsf0_inv_if_zeros:1,   /**< If PTR VSF 0 is zero, and this bit is 1, then drop the command. */
            uint64_t ptr_vsf1_inv_if_zeros:1,   /**< If PTR VSF 1 is zero, and this bit is 1, then drop the command. */
            uint64_t ptr_vsf2_inv_if_zeros:1,   /**< If PTR VSF 2 is zero, and this bit is 1, then drop the command. */
            uint64_t ptr_vsf3_inv_if_zeros:1,   /**< If PTR VSF 3 is zero, and this bit is 1, then drop the command. */
            uint64_t ptr_min:16,                /**< 16b MSBs of the minimum value of a pointer in this group. */
            uint64_t val_len_sel:3,             /**< Value length selector. */
            uint64_t val_start:7,               /**< Start position of value 0 in stats record. */
            uint64_t stats_tbl_id:6,            /**< The stats table ID used to check at the address translation. */
            uint64_t cntr_tbl_base_idx:16,      /**< The base index of the counter pointer generated by this group.
                                                         Assume 26b/25b address length for 32b/64b words respectively. */
            int64_t cntr_pkt_size_adj:8,        /**< Packet size adjustment (8-bit signed). */
            uint64_t cntr_set_size:3,           /**< Set size of each counter.  */
            uint64_t rsrvd_bit:1);              /**< Valid bit for the counter group (reserved in HW, i.e., not used by HW). */
};


/**
 *
 * @brief The VSF value and set index descriptor describes the value and set
 *  index fields per one stats counter group.
 */

struct op2_stats_cntr_reg1
{
    __EO_16(uint64_t set_idx_start_0:7,     /**< Set idx bit#0 location. */
            uint64_t set_idx_valid_0:1,     /**< Set idx bit# 0 valid bit. */
            uint64_t set_idx_start_1:7,     /**< Set idx bit# 1 location. */
            uint64_t set_idx_valid_1:1,     /**< Set idx bit# 1 valid bit. */
            uint64_t set_idx_start_2:7,     /**< Set idx bit# 2 location. */
            uint64_t set_idx_valid_2:1,     /**< Set idx bit# 2 valid bit. */
            uint64_t set_idx_start_3:7,     /**< Set idx bit# 3 location. */
            uint64_t set_idx_valid_3:1,     /**< Set idx bit# 3 valid bit. */
            uint64_t set_idx_start_4:7,     /**< Set idx bit# 4 location. */
            uint64_t set_idx_valid_4:1,     /**< Set idx bit# 4 valid bit. */
            uint64_t set_idx_start_5:7,     /**< Set idx bit# 5 location. */
            uint64_t set_idx_valid_5:1,     /**< Set idx bit# 5 valid bit. */
            uint64_t set_idx_start_6:7,     /**< Set idx bit# 6 location. */
            uint64_t set_idx_valid_6:1,     /**< Set idx bit# 6 valid bit. */
            uint64_t set_idx_start_7:7,     /**< Set idx bit# 7 location. */
            uint64_t set_idx_valid_7:1);    /**< Set idx bit# 7 valid bit. */
};

/**
 *   @brief The VSF pointer descriptor describes the pointer parts
 *    fields per one stats counter group.
 */

struct op2_stats_cntr_reg0
{
    __EO_9 (uint64_t ptr_len_0:5,           /**< Length of ptr part 0 in stats record. */
            uint64_t ptr_start_0:7,         /**< Start of ptr part 0 in stats record. */
            uint64_t ptr_len_1:5,           /**< Length of ptr part 1 in stats record. */
            uint64_t ptr_start_1:7,         /**< Start of ptr part 1 in stats record. */
            uint64_t ptr_len_2:5,           /**< Length of ptr part 2 in stats record. */
            uint64_t ptr_start_2:7,         /**< Start of ptr part 2 in stats record. */
            uint64_t ptr_len_3:5,           /**< Length of ptr part 3 in stats record. */
            uint64_t ptr_start_3:7,         /**< Start of ptr part 3 in stats record. */
            uint64_t ptr_max:16);           /**< 16b MSBs of the maximum value of a pointer in this group.  */
};


enum op2_stats_search_bit {
    OP2_STATS_SEARCH_BIT_STATS = 0,
    OP2_STATS_SEARCH_BIT_SRCH  = 1,
};


/**
 *
 * @addtogroup STATS_SNC_INST_GEN_LTR
 * @{
 *
 */

/**
 *
 * @brief Misc LTR Result control register controls the Priority-over AD.
 * If the 8b of priority need to go out as part of AD data.
 *
 */

struct op2_res_misc_ctrl
{
    __EO_3(uint32_t send_priority_bmp:8,     /**< Send the Priority bmp for 8 results */
           uint32_t resv0:24,
           uint32_t resv1:32);
};


/**
 *
 * @brief Search LTR register controlling the SnC and its counter types.
 * It defines which of the 8 results need be counted and what if so, what is counterTableID. The CounterTableID is used only error checking (by Counter Index Translation logic).
 * In OP2 we support only the 32b single and 64b single types.
 *
 */

struct op2_srch_cnt_ctrl
{
    __EO_24(uint64_t cntr_tbl_id_rslt0:6,    /**< Result#0 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt0:1,  /**< Result#0 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt0:1,      /**< Result#0 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt1:6,   /**< Result#1 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt1:1,  /**< Result#1 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt1:1,      /**< Result#1 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt2:6,   /**< Result#2 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt2:1,  /**< Result#2 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt2:1,      /**< Result#2 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt3:6,   /**< Result#3 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt3:1,  /**< Result#3 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt3:1,      /**< Result#3 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt4:6,   /**< Result#4 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt4:1,  /**< Result#4 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt4:1,      /**< Result#4 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt5:6,   /**< Result#5 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt5:1,  /**< Result#5 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt5:1,      /**< Result#5 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt6:6,   /**< Result#6 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt6:1,  /**< Result#6 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt6:1,      /**< Result#6 corresponding counter enable bit. */
            uint64_t cntr_tbl_id_rslt7:6,   /**< Result#7 counter table ID, used for sanity check. */
            uint64_t cntr_core_id_rslt7:1,  /**< Result#7 core ID of the UDA where concerned counter is located. */
            uint64_t cntr_enb_rslt7:1);     /**< Result#7 corresponding counter enable bit. */
};

/**
 *
 * @brief Q Control LTR register controlling cascade and core ID bits for each port.
 * Each port has 2 bits: MSB is Cascade Bit and LSB is Core ID Bit.
 * The core ID bit is used to specify which core does the LTR search key belongs to.
 * The cascade bit is used to specify whether or not cascading (i.e.m copying the key) will happen for this key.
 *
 */

struct op2_addr_port_qctrl
{
    __EO_9(
            uint64_t port0_q_ctrl:2,       /**< Q control of port # 0: [0]: CoreId and [1]: CascadeBit (aka Copy bit). */
            uint64_t future_use0:2,         /**< Future use padding bits, reset value is 0x0. */
            uint64_t port1_q_ctrl:2,        /**< Q control of port # 1: [0]: CoreId and [1]: CascadeBit (aka Copy bit). */
            uint64_t future_use1:2,         /**< Future use padding bits, reset value is 0x0. */
            uint64_t port2_q_ctrl:2,        /**< Q control of port # 2: [0]: CoreId and [1]: CascadeBit (aka Copy bit). */
            uint64_t future_use2:2,         /**< Future use padding bits, reset value is 0x0. */
            uint64_t port3_q_ctrl:2,        /**< Q control of port # 3: [0]: CoreId and [1]: CascadeBit (aka Copy bit). */
            uint64_t future_use3:2,         /**< Future use padding bits, reset value is 0x0. */
            uint64_t rsrvd:48);             /**< Reserved bits. */
};

/** Actual OP2 Device ID Register. */

struct op2_dev_id_reg
{
    uint64_t bits;  /**< [31:0] JTAG ID, [35:32] BasicModeBits, [36:36] SilentRev,
                       * [43:40] Device Format (silicon or emulation).
                       */
};

/** Actual OP2 Config Register. */

struct op2_device_cfg_reg
{
    __EO_32(uint64_t global_dev_err_en_port0:1,  /**< Creates DevError condition on Port0. Refer to RDB. */
    uint64_t global_dev_err_en_port1:1,         /**< Same like GlobalDevErrorEnablePort0 for Port1. */
    uint64_t global_dev_err_en_port2:1,         /**< Same like GlobalDevErrorEnablePort0 for Port2. */
    uint64_t global_dev_err_en_port3:1,         /**< Same like GlobalDevErrorEnablePort0 for Port3. */
    uint64_t rsrvd_bit0:1,                      /**< Reserved bit. */
    uint64_t global_inter_en_pcie_and_giol:1,   /**< Creates an interrupt condition on GIOL. Refer to RDB. */
    uint64_t db_soft_err_scan_en:1,             /**< The DBA has ECC Scan. Refer to RDB. */
    uint64_t db_err_ent_invalidate:1,           /** Controls the invalidation of DBA entry. Refer to RDB. */
    uint64_t db_err_ent_auto_fix_update:1,      /** Controls the invalidation of DBA entry. Refer to RDB. */
    uint64_t age_scan_enable:1,                 /**< Enables Parity Scan Slot generation. Refer to RDB. */
    uint64_t rsrvd_bits1:5,                     /**< Reserved 5 bits. */
    uint64_t context_buffer_config:8,           /**<  The register is used for master key construction. Refer to RDB. */
    uint64_t cb_bypass:1,                       /**< If set to 1'b1, each compare instruction is treated as if it is NCBCMP. */
    uint64_t rpt_db_soft_err_scan_en:1,         /**< Refer to RDB. */
    uint64_t rpt_db_err_entry_invalidate:1,     /**< Refer to RDB. */
    uint64_t en_uda_single_err_status_bit:1,    /**< Refer to RDB. */
    uint64_t rsrvd_bit2:1,                      /**< Reserved bit. */
    uint64_t extended_cb_config:2,              /**< Provide 2MS bits of Context Buffer Configuration (only when more than 4K CBs are used). */
    uint64_t rsrvd_bit3:1,                      /**< Reserved bit. */
    uint64_t copy_index_2_ad:1,                 /**< Supports priority addition to in-place AD & to allow the expansion of the field to fixed size AD. */
    uint64_t two_srch_port_mode:1,              /**< If set to 1'b1--> means that only two ports are used for search. These two ports need be Port0 and Port2. */
    uint64_t send_prior_on_msb:1,               /**< If this bit is 1'b0 and if the LTR indicates so, the search core
                                                 * sends the 8b priority on the LSB side of Associated Data.
                                                 * If set to 1'b1 and if the LTR indicates so, the search core sends
                                                 * the 8b priority on the MSB side of Associated Data.
                                                 */
    uint64_t flip_port_ltr6:4,                  /**< Port 0 to Port 3 +64 LTR reprogramming bit. It flips LTR address bit#6.
                                                 * In typical case, usage is as follows:
                                                 * - In case of 4 ports configuration, set the bit for Port1 and Port3.
                                                 * - In case of 2 ports configuration, set the bit for Port2.
                                                 * By default, there are no flipping to bit#6 takes place.
                                                 * Note that in case of JR2 connected systems, LUT can be programmed
                                                 * to change the LTRs on port basis as well.
                                                 */
    uint64_t sts_mem_pwr_dwn:2,                 /**< If set to 1'b1, it indicates that corresponding Stats Core memories
                                                 * need be powered down. Once it is powered down, it cannot be powered up by this bit.
                                                 */
    uint64_t reqsrc1_chl_id:3,                  /**< Request Source 1 Tx Chl id. */
    uint64_t dyn_evication_chl_id:3,            /**< Dynamic eviction Tx Chl id. */
    uint64_t pio_evication_chl_id:3,            /**< PIORD base eviction Tx Chl id. */
    uint64_t age_scan_chl_id:3,                 /**< Age Scan Tx Chl id. */
    uint64_t non_scan_chl_id:3,                 /**< non-scan bulk read Tx Chl id. */
    uint64_t resv0_chl_id:3,                    /**< reserve Tx Chl id. */
    uint64_t resv1_chl_id:3,                    /**< reserve Tx Chl id. */
    uint64_t resv:3);                           /**< Padding. */
};

/** Global OP2 configuration registers that is common to both cores. */
struct op2_device_crb_registers
{
    struct op2_dev_id_reg dev_id;           /**< OP2 Device ID register */
    struct op2_device_cfg_reg dcr;          /**< OP2 Device Config Register. */
    uint64_t err_status_core0;              /**< OP2 Error Status on Core 0. */
    uint64_t err_status_core1;              /**< OP2 Error Status on Core 1. */
    uint64_t interface_err_status;          /**< Interface Error status.*/
    uint64_t cpsel_register;                /**< CPSEL_REGISTER. */
    uint64_t rate_control_stats;            /**< RATE_CNTROL_STATS_REG. */
    uint64_t core_error_enable;             /**< DEV_CORE_ERROR_ENABLE.*/
    uint64_t interrupt_enable_reg_arm;      /**< INTERRUPT_ENABLE_REG_ARM */
    uint64_t interrupt_enable_reg_pcie;     /**< INTERRUPT_ENABLE_REG_PCIE */
    uint64_t par_intv_reg;                  /**< PAR_INTV_REG. */
    uint64_t arm_emc_status_reg;            /**< ARM_EMC_STATUS_REG. */
    uint64_t rate_cntrl_reg_search;         /**< RATE_CNTROL_REG_SEARCH. */
    uint64_t scratch_pad_reg0;              /**< Scratch Pad Register 0. */
    uint64_t scratch_pad_reg1;              /**< Scratch Pad Register 1. */
};

/** EMC Registers */
struct op2_device_emc_registers {
    uint64_t hwa_timer_ctrl0;  /**< Register for non-BulkRead timeout value */
    uint64_t hwa_timer_ctrl1;  /**< Register for Counter Scan BulkRead timeout value */
    uint64_t hwa_blkrd_cntr_scan_ctrl; /**< Threshold value for BlkRd Counter Scans */
};


/**
 * @}
 */


/**
 * @endcond
 */

/**
 * @}
 */

/**
 * @addtogroup STATS_CE_CT_MGMT_SCHM
 * @{
 */

/**
 *
 * @brief The SCP to SCB sends evicted counter info which has the counter value, index and type.
 * It also contains error indication bit and eviction type field.
 *
 */

struct op2_evicted_cntr_info
{
    uint64_t error_indication:1;            /**< First bit is error indication: 0b'1 = no error, 1b'1 = error. */
    uint64_t ctr_value:64;                  /**< 64b value of the evicted counter(s). */
    uint64_t ctr_idx:23;                    /**< 23b counter index in OP2 (it is 64b aligned index). */
    uint64_t ctr_hst_adrs:64;               /**< 64b counter address in host memory returned by RCAT. */
    uint64_t evic_type:2;                   /**< Eviction type: 0 = dynamic eviction, 1 Stats Bulk Read. */
    uint64_t ctr_type:2;                    /**< OP2 Counter type. */
};


/**
 * @}
 */


/**
 *
 * @cond STATS_INTERNAL
 * @addtogroup STATS_SGCR
 * @{
 *
 * @brief STATS Global Configuration Register or Stats Common Block Control
 * (SCB_MFB_SCB_CTRL0) register.
 * It used to be called "op_sgcr_reg".
 *
 */
struct op2_scb_mfb_scb_ctrl0
{
    __EO_5(uint64_t stats_core0_en:1,               /**< Enable Stats Core 0 */
           uint64_t stats_core1_en:1,               /**< Enables Stats Core 1. */
           uint64_t rsrvd_bit:1,                    /**< Reserved, used to be 2CRMW enable bit. */
           uint64_t stats_gnt_over_drive:1,         /**< Overdrives the grant for all SCPs. Should be disabled when compressed counters are used. */
           uint64_t rsrvd:60);
};

/**
 * Register to configure clock count between two eviction grant commands
 * generated by SCB.
 */
struct op2_evict_grant_rate_limiter
{
    __EO_2(uint64_t grant_rate_count:20,            /**< Clock count between two eviction grant command generated by SCB. */
           uint64_t rsrvd: 44);
};

/**
 * Stats Common Block (SCB) eviction enable control register.
 */
struct op2_mfb_scb_scp_core_evic_en
{
    __EO_4(uint64_t sts_core0_scp_en:16,            /**< When disabled no eviction grant is provided on a eviction request for Core 0. */
           uint64_t rsvd1: 16,
           uint64_t sts_core1_scp_en:16,            /**< When disabled no eviction grant is provided on a eviction request for Core 1. */
           uint64_t rsvd2: 16);
};

struct op2_mfb_scb_xlt_tbl_parity_error_loc_addr
{
    __EO_2(uint64_t prty_err_adrs_loc:9,            /**< Address of location where parity error detected in Address translation table. */
        uint64_t rsrvd:55);
};

struct op2_mfb_scb_xlt_tbl_parity_err
{
    __EO_2(uint64_t scb_addr_lkup_parity_err:1,     /**< Parity error detected on reverse address translation look up table. */
    uint64_t rsrvd:63);
};

struct op2_mfb_scb_sts_core_err_status
{
    __EO_12(uint64_t pm_error_core0:1,              /**< Error Encountered Inside Core 0 PM. */
    uint64_t sre_error_core0:1,                     /**< Error Encountered Inside Core 0 SRE. */
    uint64_t sce_error_core0:1,                     /** Error Encountered Inside Core 0 SCE. */
    uint64_t xlw_error_core0:1,                     /** Error Encountered Inside Core 0 XLW. */
    uint64_t scp_error_core0:1,                     /** Error encountered inside core 0 scps. */
    uint64_t pm_error_core1:1,                      /** Error encountered inside core 1 pm. */
    uint64_t sre_error_core1:1,                     /** Error encountered inside core 1 sre. */
    uint64_t sce_error_core1:1,                     /** Error encountered inside core 1 sce. */
    uint64_t xlw_error_core1:1,                     /** Error encountered inside core 1 xlw. */
    uint64_t scp_error_core1:1,                     /** Error encountered inside core 1 scp. */
    uint64_t scb_error_core:1,                      /** Error Encountered Inside common SCB. */
    uint64_t rsrvd:52);
};

struct op2_mfb_scb_sts_pwr_status
{
    __EO_17(uint64_t sts_core0_pwr_state:2,         /** Current state of core0 power state fsm. */
    uint64_t sts_core1_pwr_state:2,                 /** Current state of core1 power state fsm. */
    uint64_t sts_core0_mem_pwr_on_status:1,         /** Core0 memory power on status. */
    uint64_t sts_core0_mem_pwr_ok_status:1,         /** Core0 memory power ok status. */
    uint64_t sts_core1_mem_pwr_on_status:1,         /** Core1 memory power on status. */
    uint64_t sts_core1_mem_pwr_ok_status:1,         /** Core1 memory power ok status. */
    uint64_t sts_core0_test_mem_pwr_state:4,        /** Current state of core0 test mem power fsm. */
    uint64_t sts_core1_test_mem_pwr_state:4,        /** Current state of core0 test mem power fsm. */
    uint64_t sts_core0_test_mem_arr_pwr_on_status:1, /** Core0 test memory array power on status. */
    uint64_t sts_core0_test_mem_arr_pwr_ok_status:1, /** Core0 test memory array power ok status. */
    uint64_t sts_core0_test_mem_pwr_on_status:1,    /** Core0 test memory power on status. */
    uint64_t sts_core0_test_mem_pwr_ok_status:1,    /** Core0 test memory power ok status. */
    uint64_t sts_core1_test_mem_arr_pwr_on_status:1, /** Core1 test memory array power on status. */
    uint64_t sts_core1_test_mem_arr_pwr_ok_status:1, /** Core1 test memory array power ok status. */
    uint64_t sts_core1_test_mem_pwr_on_status:1,    /** Core1 test memory power on status. */
    uint64_t sts_core1_test_mem_pwr_ok_status:1,    /** Core1 test memory power ok status. */
    uint64_t rsrvd:40);
};

struct op2_mfb_scb_num_evic_pend_rqst {
    __EO_3(uint64_t core0_scp_evic_pend_rqst:1,     /** Core0 SCP's with pending eviction requests. */
    uint64_t core1_scp_evic_pending:1,              /** Core1 SCP's with pending eviction requests. */
    uint64_t rsrvd:32);
};

/**
 * @}
 */


/**
 *
 * @addtogroup SRE_LOOKUP_REG
 * @{
 *
 * @brief STATS SRE Lookup Configuration Register for each MAC port.
 *
 */
struct op2_sre_lookup_reg // Three new registers: SRE_LOOKUP_REG, SRE_INGRESS_LOOKUP_REG and SRE_EGRESS_LOOKUP_REG
{
    __EO_4(uint64_t record_size:2,          /**< Record size: 64b, 72b, 80b and 96b. */
            uint64_t record_type:2,         /**< Record type: Ingress/Egress, Null or Invalid. */
            uint64_t opcode_ext_start:7,    /**< OPCODE extension start bit. The length of the OPCODE length is fixed at 8 bits. */
            uint64_t rsrvd:53);             /**< Reserved. */
};

/**
 * @}
 */


/**
 *
 * @addtogroup SRE_INGRESS_LOOKUP_REG
 * @{
 *
 * @brief STATS SRE Ingress Lookup Register to select SLTR bits for Ingress records (per MAC port).
 *
 */
struct op2_sre_ingress_lookup_reg
{
    __EO_3(uint64_t sltr_idx:4,             /**< SLTR register index. */
           uint64_t valid_grp_id:4,         /**< Bitmap for the valid groups IDs for the selected SLTR. */
           uint64_t unused:56);             /**< Unused bits. */
};

/**
 * @}
 */


/**
 *
 * @addtogroup SRE_EGRESS_LOOKUP_REG
 * @{
 *
 * @brief STATS SRE Ingress Lookup Register to select SLTR bits for Ingress records (per MAC port).
 *
 */
struct op2_sre_egress_lookup_reg
{
    __EO_3(uint64_t sltr_idx:4,             /**< SLTR register index. */
           uint64_t valid_grp_id:4,         /**< Bitmap for the valid groups IDs for the selected SLTR. */
           uint64_t unused:56);             /**< Unused bits. */
};

/**
 * SRE Frames and Partial Frames Drop Count for Pipe 0/1.
 */
struct op2_sre_frm_drp_cnt_reg
{
    __EO_2(uint64_t drop_cnt:48,             /**< Frame drop count due to CRC, CDC FIFO parity error and I/F FIFO full condition for Pipe 0/1.
                                                 *  Also, Frame drop count due to partial record for Pipe 0/1.
                                                 */
            uint64_t unused:16);            /**< Unused bits. */
};

/**
 * SRE Frames Drop Count due to FIFO Full for Pipe 0/1.
 */
struct op2_sre_frm_drp_cnt_fifo_full_reg
{
    __EO_2(uint64_t drop_cnt_fifo_full:48,             /**< Total number of frames dropped due to I/F FIFO FULL in Pipe 0/1. */
            uint64_t unused:16);            /**< Unused bits. */
};


/**
 * SRE Frames Drop Status Register.
 */
struct op2_sre_frm_drp_cnt_status_reg
{
    __EO_8(uint64_t crc_status:1,
           uint64_t parity_status:1,
           uint64_t fifo_full_status:1,
           uint64_t int_vio_rec_status:1,
           uint64_t partial_rec_status:1,
           uint64_t parity_err_status:1,
           uint64_t pram_parity_status:1,
           uint64_t rsvd:57);
};

/**
 * @}
 */


/**
 *
 * @addtogroup STATS_ADDR_LUT
 * @{
 *
 * @brief STATS/Counters Address Translation CAM entry definition.
 *
 */
struct op2_stats_ct_addr_cam_entry
{
    __EO_9 (uint32_t lgc_idx_25_16:10,     /**< The 10 bits logical index from 16 to 25. */
            uint32_t srch_or_stats:1,       /**< Stats or search_n_count type. */
            uint32_t srch_stats_mask:1,     /**< Stats or search_n_count bit mask. */
            uint32_t phy_usb_addr:9,        /**< The 9 bit physical address including USB. */
            uint32_t str_gran:2,            /**< Storage Granularity:
                                            - 2b00: 64K
                                            - 2b01: 128K
                                            - 2b10: 256K
                                            - 2b11: 512K   */
            uint32_t cntr_type:2,           /**< Counter type: 32b/64b single and 64b/128 pair.*/
            uint32_t cntr_tbl_id:6,         /**< Counter address translation data. */
            uint32_t enable:1,              /**< Valid bit for entry. */
            uint32_t rsvd);                 /**< Padding for 64b alignment */
};

/**
 *
 * @addtogroup STATS_ADDR_LUT
 * @{
 *
 * @brief STATS/Counters 1CRMW config register.
 *
 */
struct op2_2crmw_cfg_reg {
    __EO_33 (uint32_t scp_0_2crmw:1,             /**< SCP #0 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_1_2crmw:1,             /**< SCP #1 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_2_2crmw:1,             /**< SCP #2 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_3_2crmw:1,             /**< SCP #3 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_4_2crmw:1,             /**< SCP #4 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_5_2crmw:1,             /**< SCP #5 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_6_2crmw:1,             /**< SCP #6 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_7_2crmw:1,             /**< SCP #7 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_8_2crmw:1,             /**< SCP #8 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_9_2crmw:1,             /**< SCP #9 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_10_2crmw:1,            /**< SCP #10 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_11_2crmw:1,            /**< SCP #11 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_12_2crmw:1,            /**< SCP #12 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_13_2crmw:1,            /**< SCP #13 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_14_2crmw:1,            /**< SCP #14 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_15_2crmw:1,            /**< SCP #15 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_16_2crmw:1,            /**< SCP #16 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_17_2crmw:1,            /**< SCP #17 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_18_2crmw:1,            /**< SCP #18 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_19_2crmw:1,            /**< SCP #19 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_20_2crmw:1,            /**< SCP #20 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_21_2crmw:1,            /**< SCP #21 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_22_2crmw:1,            /**< SCP #22 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_23_2crmw:1,            /**< SCP #23 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_24_2crmw:1,            /**< SCP #24 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_25_2crmw:1,            /**< SCP #25 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_26_2crmw:1,            /**< SCP #26 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_27_2crmw:1,            /**< SCP #27 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_28_2crmw:1,            /**< SCP #28 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_29_2crmw:1,            /**< SCP #29 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_30_2crmw:1,            /**< SCP #30 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t scp_31_2crmw:1,            /**< SCP #31 2CRMW bit: 1'b1 means 2CRMW and 0'b1 means 1CRMW.*/
             uint32_t rsvd);                     /**< Padding for 64b alignment */
};

/**
 *
 * @addtogroup STATS_ADDR_LUT
 * @{
 *
 * @brief STATS/Counters Reverse Address Translation Table entry definition.
 * It has 512 entries: one per USP.
 *
 */

struct op2_stats_ct_addr_rvs_cam_entry
{
    __EO_2 (uint64_t sys_msb_addr:46,       /**< The 46 MSBs of host memory counter address. */
            uint64_t rsrvd:18);             /**< Reserved. */
};


/**
 * @endcond
 */


/**
  * @brief OP Shadow SLTR for internal consumption.
  *
  */
struct op2_sltr
{
    struct op2_stats_cntr_reg0 grp0_reg0;      /**< group0 register0. */
    struct op2_stats_cntr_reg1 grp0_reg1;      /**< group0 register1. */
    struct op2_stats_cntr_reg2 grp0_reg2;      /**< group0 register2. */

    struct op2_stats_cntr_reg0 grp1_reg0;      /**< group1 register0. */
    struct op2_stats_cntr_reg1 grp1_reg1;      /**< group1 register1. */
    struct op2_stats_cntr_reg2 grp1_reg2;      /**< group1 register2. */

    struct op2_stats_cntr_reg0 grp2_reg0;      /**< group2 register0. */
    struct op2_stats_cntr_reg1 grp2_reg1;      /**< group2 register1. */
    struct op2_stats_cntr_reg2 grp2_reg2;      /**< group2 register2. */

    struct op2_stats_cntr_reg0 grp3_reg0;       /**< group3 register0. */
    struct op2_stats_cntr_reg1 grp3_reg1;       /**< group3 register1. */
    struct op2_stats_cntr_reg2 grp3_reg2;       /**< group3 register2. */
};

/**
 * Defines new addresses in the OP2 register space.
 */
/** Address of OP2 Device ID Register. */
#define KBP_OP2_DEVICE_ID_REG                           (0x00000000)
/** Address of OP2 Device Config Register (DCR) [update via MDIO]. */
#define KBP_OP2_DEVICE_CONFIG_REG                       (0x00000001)
//TBD: Add definitions for each.
#define KBP_OP2_DEV_CORE_ERR_STATUS_CORE0               (0x00000002)
#define KBP_OP2_DEV_CORE_ERR_STATUS_CORE1               (0x00000003)
#define KBP_OP2_DEV_INTERFACE_ERR_STATUS                (0x00000004)
#define KBP_OP2_DEV_CPSEL_REGISTER                      (0x00000005)
#define KBP_OP2_DEV_RATE_CNTROL_STATS                   (0x00000006)
#define KBP_OP2_DEV_CORE_ERROR_ENABLE                   (0x00000007)
#define KBP_OP2_DEV_INTERRUPT_ENABLE_REG_ARM            (0x00000008)
#define KBP_OP2_DEV_INTERRUPT_ENABLE_REG_PCIE           (0x00000009)
#define KBP_OP2_DEV_PAR_INTV_REG                        (0x0000000A)
#define KBP_OP2_DEV_ARM_EMC_STATUS_REG                  (0x0000000B)
#define KBP_OP2_DEV_RATE_CNTROL_REG_SEARCH              (0x0000000C)
#define KBP_OP2_DEV_SCRATCH_PAD_REG0                    (0x0000000E)
#define KBP_OP2_DEV_SCRATCH_PAD_REG1                    (0x0000000F)
#define KBP_OP2_DEV_HWA_TIMER_CTRL0                     (0x00000837)
#define KBP_OP2_DEV_HWA_TIMER_CTRL1                     (0x00000838)
#define KBP_OP2_DEV_HWA_OUTSTANDING_COUNT_REG           (0x0000083A)

/** Start of address space for Stats/Counters Logical Table Registers SLTRs. */
/** SCE Core 0 has 16 x 2 = 32 registers. */
#define KBP_OP2_REG_SCE0_ING_SLTR_START                 (0x00448200)
#define KBP_OP2_REG_SCE0_ING_SLTR_END                   (0x004482FB)

/** Start of address space for Stats/Counters Logical Table Registers SLTRs. */
#define KBP_OP2_REG_SCE0_EGR_SLTR_START                 (0x00448300)
#define KBP_OP2_REG_SCE0_EGR_SLTR_END                   (0x004483FB)

/** SCE Core 1 has 16 x 2 = 32 registers. */
#define KBP_OP2_REG_SCE1_ING_SLTR_START                 (0x00449200)
#define KBP_OP2_REG_SCE1_ING_SLTR_END                   (0x004492FB)

/** Start of address space for Stats/Counters Logical Table Registers SLTRs. */
#define KBP_OP2_REG_SCE1_EGR_SLTR_START                 (0x00449300)
#define KBP_OP2_REG_SCE1_EGR_SLTR_END                   (0x004493FB)

/** The Absolute Global SLTR Registers End --> KBP_OP2_REG_SCE1_EGR_SLTR_END + 12. */
#define KBP_OP2_REG_SLTR_END                            (0x004493FB)

/** Stats logical table register address for a given SCE Core Ing/Egr. */
/** Each SCE SLTR Register has 4 groups, each group has 3 registers to define 4 stats commands. */
/** Example: KBP_OP2_SLTR_ADDR_SCE(KBP_OP2_REG_SCE0_EGR_SLTR_START, 3, 2, 1) = fourth EGR SLTR of SCE Pipe0, third group, 2nd register.*/
#define KBP_OP2_SLTR_ADDR_SCE(sltr_st, idx, grp, reg)   (sltr_st + (idx * 0x10) + (grp * 3) + reg)
/** This is for kbp_stat.c. */
#define KBP_OP2_REG_SCE0_ING_SLTR_ADDR_1(idx, grp, reg) ((KBP_OP2_REG_SCE0_ING_SLTR_START) + (idx *0x10) + (grp * 3) + reg)
#define KBP_OP2_REG_SCE0_EGR_SLTR_ADDR_1(idx, grp, reg) ((KBP_OP2_REG_SCE0_EGR_SLTR_START) + (idx *0x10) + (grp * 3) + reg)
#define KBP_OP2_REG_SCE1_ING_SLTR_ADDR_1(idx, grp, reg) ((KBP_OP2_REG_SCE1_ING_SLTR_START) + (idx *0x10) + (grp * 3) + reg)
#define KBP_OP2_REG_SCE1_EGR_SLTR_ADDR_1(idx, grp, reg) ((KBP_OP2_REG_SCE1_EGR_SLTR_START) + (idx *0x10) + (grp * 3) + reg)

/*********************************** SCB Stats Common Block Regs. *********************************/
/** The address Stats/Counters Global Configuration Register (SGCR) (or mfb_scb_ctrl0 in uArch doc). */
#define KBP_OP2_REG_SGCR_ADRS                           (0x00400000)
#define KBP_OP2_REG_MFB_SCB_CTRL0_ADRS                  KBP_OP2_REG_SGCR_ADRS
/** Register to configure clock count between two eviction grant command generated by SCB */
#define KBP_OP2_REG_EVICT_GRANT_RATE_LIMITER            (0x00400001)
#define KBP_OP2_REG_MFB_SCB_XLT_TBL_PARTY_ERR_LOC_ADDR  (0x00400002)
#define KBP_OP2_REG_MFB_SCB_XLT_TBL_PARTY_ERR           (0x00400003)
#define KBP_OP2_REG_MFB_SCB_STS_CORE_ERR_STATUS         (0x00400004)
#define KBP_OP2_REG_MFB_SCB_STS_CORE_ERR_MASK           (0x00400005)
#define KBP_OP2_REG_MFB_SCB_SCP_CORE_EVIC_EN            (0x00400006)
#define KBP_OP2_REG_MFB_SCB_STS_PWR_STATUS              (0x00400007)
#define KBP_OP2_REG_MFB_SCB_NUM_EVIC_REQ_CNT            (0x00400008)
#define KBP_OP2_REG_MFB_SCB_NUM_EVIC_GRANT_CNT          (0x00400009)
#define KBP_OP2_REG_MFB_SCB_NUM_EVIC_BURST_DATA_CNT     (0x0040000A)
#define KBP_OP2_REG_MFB_SCB_NUM_EVIC_DATA_CNT           (0x0040000B)
#define KBP_OP2_REG_MFB_SCB_NUM_EVIC_PEND_RQST          (0x0040000C)

/** Start of address space for Stats/CT Address Translation LUT registers. */
#define KBP_OP2_STATS_REG_ADDR_CAM_START                (0x0040A000)
/** End of address space for Stats/CT Address Translation LUT registers. */
#define KBP_OP2_STATS_REG_ADDR_CAM_END                  (KBP_OP2_STATS_REG_ADDR_CAM_START + KBP_OP2_NUM_STATS_ADDR_CAM_ROWS - 1) //(0x0040a03F)
/** Address of STATS/CT Address Translation CAM Entry given its Index. */
#define KBP_OP2_STATS_CAM_REG_ENTRY_ADDR(idx)           (KBP_OP2_STATS_REG_ADDR_CAM_START + (idx))

/** The 2CRMW configuration register: 1b per SCP. Note that each 2b pair has same value. */
#define KBP_OP2_STATS_2CRMW_CFG_REG                     (0x0040A202)

/** Third logical table register for given KPU */
#define KBP_OP2_LTR_ADDR_KPU_2(ltr, kpu)                (0x0004000E + (ltr) * 0x100 + (kpu) * 3)

/** Address for Core 0/Core 1 Stats SRE Global Lookup Register. */
#define KBP_OP2_REG_SRE_LOOKUP0                         (0x00404000)
#define KBP_OP2_REG_SRE_LOOKUP1                         (0x00404001)
#define KBP_OP2_REG_SRE_LOOKUP2                         (0x00404002)
#define KBP_OP2_REG_SRE_LOOKUP3                         (0x00404003)

/** Address for Core 0 / Core 1 Stats SRE Ingress Registers. */
#define KBP_OP2_REG_SRE_INGRESS_START                   (0x00404100)
#define KBP_OP2_REG_SRE_INGRESS_END                     (0x004041FF)

#define KBP_OP2_REG_SRE_INGRESS_ADDRESS(idx)            (KBP_OP2_REG_SRE_INGRESS_START+ idx)
#define KBP_OP2_REG_SRE_EGRESS_ADDRESS(idx)             (KBP_OP2_REG_SRE_EGRESS_START+ idx)

/** Address for Core 0 / Core 1 Stats SRE Egress Registers. */
#define KBP_OP2_REG_SRE_EGRESS_START                    (0x00404200)
#define KBP_OP2_REG_SRE_EGRESS_END                      (0x004042FF)

/** Address for Pipe0/Pipe1 Ingress/Egress record counts registers. */
#define KBP_OP2_REG_SRE_INGRESS_REC0_REG                (0x004D4000)
#define KBP_OP2_REG_SRE_INGRESS_REC1_REG                (0x004D4001)
#define KBP_OP2_REG_SRE_EGRESS_REC0_REG                 (0x004D4002)
#define KBP_OP2_REG_SRE_EGRESS_REC1_REG                 (0x004D4003)

/** Address for debug SRE registers: Pipe 0. */
#define KBP_OP2_REG_SRE_FRAME0_DROP_CNT_REG             (0x00404022)
#define KBP_OP2_REG_SRE_PARTIAL_FRAME0_DROP_CNT_REG     (0x00404023)
#define KBP_OP2_REG_SRE_FRAME0_DROP_STATUS_REG          (0x00404024)
#define KBP_OP2_REG_SRE_FRAME0_DROP_CNT_FIFO_FULL_REG   (0x0040402E)

/** Address for debug SRE registers: Pipe 1. */
#define KBP_OP2_REG_SRE_FRAME1_DROP_CNT_REG             (0x00404025)
#define KBP_OP2_REG_SRE_PARTIAL_FRAME1_DROP_CNT_REG     (0x00404026)
#define KBP_OP2_REG_SRE_FRAME1_DROP_STATUS_REG          (0x00404027)
#define KBP_OP2_REG_SRE_FRAME1_DROP_CNT_FIFO_FULL_REG   (0x0040402F)

/** SCP-pair power up configuration register. Each bit corresponds to 1 SCP-pair per UDC. */
#define KBP_OP2_SCPC_PWR_CFG_REG                        (0x0040A200)
#define KBP_OP2_SCPC_PWR_STS_REG                        (0x0040A201)

/** SCP-pair enable and dynamic eviction configuration register per UDC per core. */
#define KBP_OP2_UDC_SCP_CTRL0_START                     (0x0040C000)
#define KBP_OP2_UDC_SCP_CTRL0_END                       (KBP_OP2_UDC_SCP_CTRL0_START + KBP_OP2_NUM_UDC_SCP_CTRL_REG_PER_CORE - 1)   // 0x0040c00f
#define KBP_OP2_UDC_SCP_CTRL0_ADDR(idx)                 (KBP_OP2_UDC_SCP_CTRL0_START + (idx))

/** uSBPair counter type register per UDC per core. */
#define KBP_OP2_UDC_SCP_CTRL1_START                     (0x0040C020)
#define KBP_OP2_UDC_SCP_CTRL1_END                       (KBP_OP2_UDC_SCP_CTRL1_START + KBP_OP2_NUM_UDC_SCP_CTRL_REG_PER_CORE - 1)   // 0x0040c02f
#define KBP_OP2_UDC_SCP_CTRL1_ADDR(idx)                 (KBP_OP2_UDC_SCP_CTRL1_START + (idx))

/** SCP0 LFSR seed registers */
#define KBP_OP2_UDC_SCP0_STACE_LFSR1_START              (0x0040C200)
#define KBP_OP2_UDC_SCP0_STACE_LFSR1_END                (KBP_OP2_UDC_SCP0_STACE_LFSR1_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)    // 0x0040c20f
#define KBP_OP2_UDC_SCP0_STACE_LFSR1_ADDR(idx)          (KBP_OP2_UDC_SCP0_STACE_LFSR1_START + (idx))
#define KBP_OP2_UDC_SCP0_STACE_LFSR2_START              (0x0040C220)
#define KBP_OP2_UDC_SCP0_STACE_LFSR2_END                (KBP_OP2_UDC_SCP0_STACE_LFSR2_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)    // 0x0040c22f
#define KBP_OP2_UDC_SCP0_STACE_LFSR2_ADDR(idx)          (KBP_OP2_UDC_SCP0_STACE_LFSR2_START + (idx))
#define KBP_OP2_UDC_SCP0_STACE_LFSR3_START              (0x0040C240)
#define KBP_OP2_UDC_SCP0_STACE_LFSR3_END                (KBP_OP2_UDC_SCP0_STACE_LFSR3_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)    // 0x0040c24f
#define KBP_OP2_UDC_SCP0_STACE_LFSR3_ADDR(idx)          (KBP_OP2_UDC_SCP0_STACE_LFSR3_START + (idx))

/** SCP1 LFSR seed registers */
#define KBP_OP2_UDC_SCP1_STACE_LFSR1_START              (0x0040C260)
#define KBP_OP2_UDC_SCP1_STACE_LFSR1_END                (KBP_OP2_UDC_SCP1_STACE_LFSR1_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)    // 0x0040c26f
#define KBP_OP2_UDC_SCP1_STACE_LFSR1_ADDR(idx)          (KBP_OP2_UDC_SCP1_STACE_LFSR1_START + (idx))
#define KBP_OP2_UDC_SCP1_STACE_LFSR2_START              (0x0040C280)
#define KBP_OP2_UDC_SCP1_STACE_LFSR2_END                (KBP_OP2_UDC_SCP1_STACE_LFSR2_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)    // 0x0040c28f
#define KBP_OP2_UDC_SCP1_STACE_LFSR2_ADDR(idx)          (KBP_OP2_UDC_SCP1_STACE_LFSR2_START + (idx))
#define KBP_OP2_UDC_SCP1_STACE_LFSR3_START              (0x0040C2A0)
#define KBP_OP2_UDC_SCP1_STACE_LFSR3_END                (KBP_OP2_UDC_SCP1_STACE_LFSR3_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)    // 0x0040c2Af
#define KBP_OP2_UDC_SCP1_STACE_LFSR3_ADDR(idx)          (KBP_OP2_UDC_SCP1_STACE_LFSR3_START + (idx))

/** Register to force early dynamic evictions for debug purposes. */
#define KBP_OP2_UDC_SCP_STACE_LFSR_MASK_START           (0x0040C2C0)
#define KBP_OP2_UDC_SCP_STACE_LFSR_MASK_END             (KBP_OP2_UDC_SCP_STACE_LFSR_MASK_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c2cf
#define KBP_OP2_UDC_SCP_STACE_LFSR_MASK_ADDR(idx)       (KBP_OP2_UDC_SCP_STACE_LFSR_MASK_START + (idx))

/** SCP0 Command Drop0 Count register. */
#define KBP_OP2_SCP_UDC_SCP0_CMD_DROP0_CNT_START        (0x0040C100)
#define KBP_OP2_SCP_UDC_SCP0_CMD_DROP0_CNT_END          (KBP_OP2_SCP_UDC_SCP0_CMD_DROP0_CNT_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c10f
#define KBP_OP2_SCP_UDC_SCP0_CMD_DROP0_CNT_ADDR(idx)    (KBP_OP2_SCP_UDC_SCP0_CMD_DROP0_CNT_START + (idx))

/** SCP0 Command Drop1 Count register. */
#define KBP_OP2_SCP_UDC_SCP0_CMD_DROP1_CNT_START        (0x0040C120)
#define KBP_OP2_SCP_UDC_SCP0_CMD_DROP1_CNT_END          (KBP_OP2_SCP_UDC_SCP0_CMD_DROP1_CNT_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c10f
#define KBP_OP2_SCP_UDC_SCP0_CMD_DROP1_CNT_ADDR(idx)    (KBP_OP2_SCP_UDC_SCP0_CMD_DROP1_CNT_START + (idx))

/** SCP1 Command Drop0 Count register. */
#define KBP_OP2_SCP_UDC_SCP1_CMD_DROP0_CNT_START        (0x0040C140)
#define KBP_OP2_SCP_UDC_SCP1_CMD_DROP0_CNT_END          (KBP_OP2_SCP_UDC_SCP1_CMD_DROP0_CNT_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c14f
#define KBP_OP2_SCP_UDC_SCP1_CMD_DROP0_CNT_ADDR(idx)    (KBP_OP2_SCP_UDC_SCP1_CMD_DROP0_CNT_START + (idx))

/** SCP1 Command Drop0 Count register. */
#define KBP_OP2_SCP_UDC_SCP1_CMD_DROP1_CNT_START        (0x0040C160)
#define KBP_OP2_SCP_UDC_SCP1_CMD_DROP1_CNT_END          (KBP_OP2_SCP_UDC_SCP1_CMD_DROP1_CNT_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c14f
#define KBP_OP2_SCP_UDC_SCP1_CMD_DROP1_CNT_ADDR(idx)    (KBP_OP2_SCP_UDC_SCP1_CMD_DROP1_CNT_START + (idx))

/** SCP0 FIFO Occupancy Count register. */
#define KBP_OP2_SCP_UDC_SCP0_FIFO_OCCP_CNT_START        (0x0040C180)
#define KBP_OP2_SCP_UDC_SCP0_FIFO_OCCP_CNT_END          (KBP_OP2_SCP_UDC_SCP0_FIFO_OCCP_CNT_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c18f
#define KBP_OP2_SCP_UDC_SCP0_FIFO_OCCP_CNT_ADDR(idx)    (KBP_OP2_SCP_UDC_SCP0_FIFO_OCCP_CNT_START + (idx))

/** SCP1 FIFO Occupancy Count register. */
#define KBP_OP2_SCP_UDC_SCP1_FIFO_OCCP_CNT_START        (0x0040C1A0)
#define KBP_OP2_SCP_UDC_SCP1_FIFO_OCCP_CNT_END          (KBP_OP2_SCP_UDC_SCP1_FIFO_OCCP_CNT_START + KBP_OP2_NUM_LFSR_MASK_REG_PER_CORE - 1)    // 0x0040c1af
#define KBP_OP2_SCP_UDC_SCP1_FIFO_OCCP_CNT_ADDR(idx)    (KBP_OP2_SCP_UDC_SCP1_FIFO_OCCP_CNT_START + (idx))

#define KBP_OP2_UDC_SCP0_INTR_STATUS_START              (0x40cC040)
#define KBP_OP2_UDC_SCP0_INTR_STATUS_END                (KBP_OP2_UDC_SCP0_INTR_STATUS_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)
#define KBP_OP2_UDC_SCP0_INTR_STATUS_START_ADDR(idx)    (KBP_OP2_UDC_SCP0_INTR_STATUS_START + (idx))

#define KBP_OP2_UDC_SCP1_INTR_STATUS_START              (0x40C060)
#define KBP_OP2_UDC_SCP1_INTR_STATUS_END                (KBP_OP2_UDC_SCP1_INTR_STATUS_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)
#define KBP_OP2_UDC_SCP1_INTR_STATUS_START_ADDR(idx)    (KBP_OP2_UDC_SCP1_INTR_STATUS_START + (idx))

#define KBP_OP2_UDC_SCP0_INTR_ENABLE_START              (0x40C080)
#define KBP_OP2_UDC_SCP0_INTR_ENABLE_END                (KBP_OP2_UDC_SCP0_INTR_ENABLE_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)
#define KBP_OP2_UDC_SCP0_INTR_ENABLE_START_ADDR(idx)    (KBP_OP2_UDC_SCP0_INTR_ENABLE_START + (idx))

#define KBP_OP2_UDC_SCP1_INTR_ENABLE_START              (0x40C0A0)
#define KBP_OP2_UDC_SCP1_INTR_ENABLE_END                (KBP_OP2_UDC_SCP1_INTR_ENABLE_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)
#define KBP_OP2_UDC_SCP1_INTR_ENABLE_START_ADDR(idx)    (KBP_OP2_UDC_SCP1_INTR_ENABLE_START + (idx))

#define KBP_OP2_UDC_SCP0_INTR_STATUS2_START             (0x40C0C0)
#define KBP_OP2_UDC_SCP0_INTR_STATUS2_END               (KBP_OP2_UDC_SCP0_INTR_STATUS2_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)
#define KBP_OP2_UDC_SCP0_INTR_STATUS2_START_ADDR(idx)   (KBP_OP2_UDC_SCP0_INTR_STATUS2_START + (idx))

#define KBP_OP2_UDC_SCP1_INTR_STATUS2_START             (0x40C0E0)
#define KBP_OP2_UDC_SCP1_INTR_STATUS2_END               (KBP_OP2_UDC_SCP1_INTR_STATUS2_START + KBP_OP2_NUM_LFSR_REG_PER_CORE - 1)
#define KBP_OP2_UDC_SCP1_INTR_STATUS2_START_ADDR(idx)   (KBP_OP2_UDC_SCP1_INTR_STATUS2_START + (idx))

#define scp0_stace_lfsr1_udc(n)                         (KBP_OP2_UDC_SCP_CTRL0_START + 0x200 + n)
#define scp0_stace_lfsr2_udc(n)                         (KBP_OP2_UDC_SCP_CTRL0_START + 0x220 + n)
#define scp0_stace_lfsr3_udc(n)                         (KBP_OP2_UDC_SCP_CTRL0_START + 0x240 + n)
#define scp1_stace_lfsr1_udc(n)                         (KBP_OP2_UDC_SCP_CTRL0_START + 0x260 + n)
#define scp1_stace_lfsr2_udc(n)                         (KBP_OP2_UDC_SCP_CTRL0_START + 0x280 + n)
#define scp1_stace_lfsr3_udc(n)                         (KBP_OP2_UDC_SCP_CTRL0_START + 0x2A0 + n)
#define scp_stace_lfsr_mask_udc(n)                      (KBP_OP2_UDC_SCP_CTRL0_START + 0x2C0 + n)

/**
 * SIA LUT Registers for both Pipes, Ingress/Egress, 16 SLTRs,
 * and 4 Groups per SLR.
 *
 */
/** Ingress, Pipe 0 LUTs. */
/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR0_START  (0x00418000)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR0_END    (0x0041800F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR1_START  (0x00418010)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR1_END    (0x0041801F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR2_START  (0x00418020)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR2_END    (0x0041802F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR3_START  (0x00418030)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR3_END    (0x0041803F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR4_START  (0x00418040)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR4_END    (0x0041804F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR5_START  (0x00418050)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR5_END    (0x0041805F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR6_START  (0x00418060)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR6_END    (0x0041806F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR7_START  (0x00418070)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR7_END    (0x0041807F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR8_START  (0x00418080)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR8_END    (0x0041808F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR9_START  (0x00418090)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR9_END    (0x0041809F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR10_START (0x004180A0)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR10_END   (0x004180AF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR11_START (0x004180B0)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR11_END   (0x004180BF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR12_START (0x004180C0)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR12_END   (0x004180CF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR13_START (0x004180D0)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR13_END   (0x004180DF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR14_START (0x004180E0)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR14_END   (0x004180EF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 0, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR15_START (0x004180F0)
#define SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR15_END   (0x004180FF)

/****************/

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR0_START  (0x00418100)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR0_END    (0x0041810F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR1_START  (0x00418110)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR1_END    (0x0041811F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR2_START  (0x00418120)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR2_END    (0x0041812F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR3_START  (0x00418130)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR3_END    (0x0041813F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR4_START  (0x00418140)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR4_END    (0x0041814F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR5_START  (0x00418150)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR5_END    (0x0041815F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR6_START  (0x00418160)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR6_END    (0x0041816F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR7_START  (0x00418170)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR7_END    (0x0041817F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR8_START  (0x00418180)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR8_END    (0x0041818F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR9_START  (0x00418190)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR9_END    (0x0041819F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR10_START (0x004181A0)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR10_END   (0x004181AF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR11_START (0x004181B0)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR11_END   (0x004181BF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR12_START (0x004181C0)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR12_END   (0x004181CF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR13_START (0x004181D0)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR13_END   (0x004181DF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR14_START (0x004181E0)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR14_END   (0x004181EF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 1, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR15_START (0x004181F0)
#define SCE_SIA_LUT_PIPE0_ING_GRP1_SLTR15_END   (0x004181FF)

/****************/

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR0_START  (0x00418200)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR0_END    (0x0041820F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR1_START  (0x00418210)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR1_END    (0x0041821F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR2_START  (0x00418220)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR2_END    (0x0041822F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR3_START  (0x00418230)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR3_END    (0x0041823F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR4_START  (0x00418240)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR4_END    (0x0041824F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR5_START  (0x00418250)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR5_END    (0x0041825F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR6_START  (0x00418260)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR6_END    (0x0041826F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR7_START  (0x00418270)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR7_END    (0x0041827F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR8_START  (0x00418280)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR8_END    (0x0041828F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR9_START  (0x00418290)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR9_END    (0x0041829F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR10_START (0x004182A0)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR10_END   (0x004182AF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR11_START (0x004182B0)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR11_END   (0x004182BF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR12_START (0x004182C0)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR12_END   (0x004182CF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR13_START (0x004182D0)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR13_END   (0x004182DF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR14_START (0x004182E0)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR14_END   (0x004182EF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 2, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR15_START (0x004182F0)
#define SCE_SIA_LUT_PIPE0_ING_GRP2_SLTR15_END   (0x004182FF)

/****************/

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR0_START  (0x00418300)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR0_END    (0x0041830F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR1_START  (0x00418310)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR1_END    (0x0041831F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR2_START  (0x00418320)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR2_END    (0x0041832F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR3_START  (0x00418330)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR3_END    (0x0041833F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR4_START  (0x00418340)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR4_END    (0x0041834F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR5_START  (0x00418350)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR5_END    (0x0041835F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR6_START  (0x00418360)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR6_END    (0x0041836F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR7_START  (0x00418370)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR7_END    (0x0041837F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR8_START  (0x00418380)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR8_END    (0x0041838F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR9_START  (0x00418390)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR9_END    (0x0041839F)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR10_START (0x004183A0)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR10_END   (0x004183AF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR11_START (0x004183B0)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR11_END   (0x004183BF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR12_START (0x004183C0)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR12_END   (0x004183CF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR13_START (0x004183D0)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR13_END   (0x004183DF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR14_START (0x004183E0)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR14_END   (0x004183EF)

/** SIA LUT Registers for Ingress, Pipe 0, Group 3, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR15_START (0x004183F0)
#define SCE_SIA_LUT_PIPE0_ING_GRP3_SLTR15_END   (0x004183FF)

/** Egress, Pipe 0 LUTs. */
/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR0_START  (0x00418400)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR0_END    (0x0041840F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR1_START  (0x00418410)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR1_END    (0x0041841F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR2_START  (0x00418420)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR2_END    (0x0041842F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR3_START  (0x00418430)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR3_END    (0x0041843F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR4_START  (0x00418440)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR4_END    (0x0041844F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR5_START  (0x00418450)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR5_END    (0x0041845F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR6_START  (0x00418460)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR6_END    (0x0041846F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR7_START  (0x00418470)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR7_END    (0x0041847F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR8_START  (0x00418480)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR8_END    (0x0041848F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR9_START  (0x00418490)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR9_END    (0x0041849F)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR10_START (0x004184A0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR10_END   (0x004184AF)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR11_START (0x004184B0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR11_END   (0x004184BF)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR12_START (0x004184C0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR12_END   (0x004184CF)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR13_START (0x004184D0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR13_END   (0x004184DF)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR14_START (0x004184E0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR14_END   (0x004184EF)

/** SIA LUT Registers for Egress, Pipe 0, Group 0, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR15_START (0x004184F0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR15_END   (0x004184FF)

/****************/

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR0_START  (0x00418500)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR0_END    (0x0041850F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR1_START  (0x00418510)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR1_END    (0x0041851F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR2_START  (0x00418520)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR2_END    (0x0041852F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR3_START  (0x00418530)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR3_END    (0x0041853F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR4_START  (0x00418540)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR4_END    (0x0041854F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR5_START  (0x00418550)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR5_END    (0x0041855F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR6_START  (0x00418560)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR6_END    (0x0041856F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR7_START  (0x00418570)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR7_END    (0x0041857F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR8_START  (0x00418580)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR8_END    (0x0041858F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR9_START  (0x00418590)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR9_END    (0x0041859F)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR10_START (0x004185A0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR10_END   (0x004185AF)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR11_START (0x004185B0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR11_END   (0x004185BF)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR12_START (0x004185C0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR12_END   (0x004185CF)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR13_START (0x004185D0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR13_END   (0x004185DF)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR14_START (0x004185E0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR14_END   (0x004185EF)

/** SIA LUT Registers for Egress, Pipe 0, Group 1, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR15_START (0x004185F0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP1_SLTR15_END   (0x004185FF)

/****************/

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR0_START  (0x00418600)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR0_END    (0x0041860F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR1_START  (0x00418610)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR1_END    (0x0041861F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR2_START  (0x00418620)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR2_END    (0x0041862F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR3_START  (0x00418630)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR3_END    (0x0041863F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR4_START  (0x00418640)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR4_END    (0x0041864F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR5_START  (0x00418650)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR5_END    (0x0041865F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR6_START  (0x00418660)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR6_END    (0x0041866F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR7_START  (0x00418670)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR7_END    (0x0041867F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR8_START  (0x00418680)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR8_END    (0x0041868F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR9_START  (0x00418690)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR9_END    (0x0041869F)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR10_START (0x004186A0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR10_END   (0x004186AF)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR11_START (0x004186B0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR11_END   (0x004186BF)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR12_START (0x004186C0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR12_END   (0x004186CF)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR13_START (0x004186D0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR13_END   (0x004186DF)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR14_START (0x004186E0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR14_END   (0x004186EF)

/** SIA LUT Registers for Egress, Pipe 0, Group 2, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR15_START (0x004186F0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP2_SLTR15_END   (0x004186FF)

/****************/

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR0. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR0_START  (0x00418700)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR0_END    (0x0041870F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR1. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR1_START  (0x00418710)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR1_END    (0x0041871F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR2. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR2_START  (0x00418720)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR2_END    (0x0041872F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR3. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR3_START  (0x00418730)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR3_END    (0x0041873F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR4. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR4_START  (0x00418740)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR4_END    (0x0041874F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR5. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR5_START  (0x00418750)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR5_END    (0x0041875F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR6. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR6_START  (0x00418760)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR6_END    (0x0041876F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR7. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR7_START  (0x00418770)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR7_END    (0x0041877F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR8. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR8_START  (0x00418780)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR8_END    (0x0041878F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR9. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR9_START  (0x00418790)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR9_END    (0x0041879F)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR10. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR10_START (0x004187A0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR10_END   (0x004187AF)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR11. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR11_START (0x004187B0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR11_END   (0x004187BF)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR12. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR12_START (0x004187C0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR12_END   (0x004187CF)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR13. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR13_START (0x004187D0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR13_END   (0x004187DF)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR14. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR14_START (0x004187E0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR14_END   (0x004187EF)

/** SIA LUT Registers for Egress, Pipe 0, Group 3, and SLTR15. */
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR15_START (0x004187F0)
#define SCE_SIA_LUT_PIPE0_EGR_GRP3_SLTR15_END   (0x004187FF)

/** Ingress Pipe 1 LUTs. */
/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR0_START  (0x00418800)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR0_END    (0x0041880F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR1_START  (0x00418810)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR1_END    (0x0041881F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR2_START  (0x00418820)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR2_END    (0x0041882F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR3_START  (0x00418830)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR3_END    (0x0041883F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR4_START  (0x00418840)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR4_END    (0x0041884F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR5_START  (0x00418850)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR5_END    (0x0041885F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR6_START  (0x00418860)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR6_END    (0x0041886F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR7_START  (0x00418870)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR7_END    (0x0041887F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR8_START  (0x00418880)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR8_END    (0x0041888F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR9_START  (0x00418890)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR9_END    (0x0041889F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR10_START (0x004188A0)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR10_END   (0x004188AF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR11_START (0x004188B0)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR11_END   (0x004188BF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR12_START (0x004188C0)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR12_END   (0x004188CF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR13_START (0x004188D0)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR13_END   (0x004188DF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR14_START (0x004188E0)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR14_END   (0x004188EF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 0, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR15_START (0x004188F0)
#define SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR15_END   (0x004188FF)

/****************/

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR0_START  (0x00418900)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR0_END    (0x0041890F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR1_START  (0x00418910)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR1_END    (0x0041891F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR2_START  (0x00418920)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR2_END    (0x0041892F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR3_START  (0x00418930)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR3_END    (0x0041893F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR4_START  (0x00418940)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR4_END    (0x0041894F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR5_START  (0x00418950)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR5_END    (0x0041895F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR6_START  (0x00418960)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR6_END    (0x0041896F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR7_START  (0x00418970)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR7_END    (0x0041897F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR8_START  (0x00418980)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR8_END    (0x0041898F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR9_START  (0x00418990)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR9_END    (0x0041899F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR10_START (0x004189A0)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR10_END   (0x004189AF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR11_START (0x004189B0)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR11_END   (0x004189BF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR12_START (0x004189C0)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR12_END   (0x004189CF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR13_START (0x004189D0)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR13_END   (0x004189DF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR14_START (0x004189E0)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR14_END   (0x004189EF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 1, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR15_START (0x004189F0)
#define SCE_SIA_LUT_PIPE1_ING_GRP1_SLTR15_END   (0x004189FF)

/****************/

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR0_START  (0x00418A00)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR0_END    (0x00418A0F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR1_START  (0x00418A10)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR1_END    (0x00418A1F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR2_START  (0x00418A20)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR2_END    (0x00418A2F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR3_START  (0x00418A30)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR3_END    (0x00418A3F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR4_START  (0x00418A40)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR4_END    (0x00418A4F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR5_START  (0x00418A50)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR5_END    (0x00418A5F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR6_START  (0x00418A60)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR6_END    (0x00418A6F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR7_START  (0x00418A70)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR7_END    (0x00418A7F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR8_START  (0x00418A80)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR8_END    (0x00418A8F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR9_START  (0x00418A90)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR9_END    (0x00418A9F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR10_START (0x00418AA0)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR10_END   (0x00418AAF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR11_START (0x00418AB0)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR11_END   (0x00418ABF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR12_START (0x00418AC0)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR12_END   (0x00418ACF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR13_START (0x00418AD0)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR13_END   (0x00418ADF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR14_START (0x00418AE0)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR14_END   (0x00418AEF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 2, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR15_START (0x00418AF0)
#define SCE_SIA_LUT_PIPE1_ING_GRP2_SLTR15_END   (0x00418AFF)

/****************/

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR0_START  (0x00418B00)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR0_END    (0x00418B0F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR1_START  (0x00418B10)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR1_END    (0x00418B1F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR2_START  (0x00418B20)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR2_END    (0x00418B2F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR3_START  (0x00418B30)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR3_END    (0x00418B3F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR4_START  (0x00418B40)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR4_END    (0x00418B4F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR5_START  (0x00418B50)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR5_END    (0x00418B5F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR6_START  (0x00418B60)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR6_END    (0x00418B6F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR7_START  (0x00418B70)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR7_END    (0x00418B7F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR8_START  (0x00418B80)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR8_END    (0x00418B8F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR9_START  (0x00418B90)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR9_END    (0x00418B9F)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR10_START (0x00418BA0)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR10_END   (0x00418BAF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR11_START (0x00418BB0)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR11_END   (0x00418BBF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR12_START (0x00418BC0)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR12_END   (0x00418BCF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR13_START (0x00418BD0)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR13_END   (0x00418BDF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR14_START (0x00418BE0)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR14_END   (0x00418BEF)

/** SIA LUT Registers for Ingress, Pipe 1, Group 3, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR15_START (0x00418BF0)
#define SCE_SIA_LUT_PIPE1_ING_GRP3_SLTR15_END   (0x00418BFF)

/** Egress, Pipe 1 LUTs. */
/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR0_START  (0x00418C00)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR0_END    (0x00418C0F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR1_START  (0x00418C10)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR1_END    (0x00418C1F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR2_START  (0x00418C20)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR2_END    (0x00418C2F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR3_START  (0x00418C30)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR3_END    (0x00418C3F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR4_START  (0x00418C40)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR4_END    (0x00418C4F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR5_START  (0x00418C50)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR5_END    (0x00418C5F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR6_START  (0x00418C60)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR6_END    (0x00418C6F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR7_START  (0x00418C70)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR7_END    (0x00418C7F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR8_START  (0x00418C80)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR8_END    (0x00418C8F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR9_START  (0x00418C90)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR9_END    (0x00418C9F)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR10_START (0x00418CA0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR10_END   (0x00418CAF)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR11_START (0x00418CB0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR11_END   (0x00418CBF)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR12_START (0x00418CC0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR12_END   (0x00418CCF)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR13_START (0x00418CD0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR13_END   (0x00418CDF)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR14_START (0x00418CE0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR14_END   (0x00418CEF)

/** SIA LUT Registers for Egress, Pipe 1, Group 0, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR15_START (0x00418CF0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR15_END   (0x00418CFF)

/****************/

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR0_START  (0x00418D00)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR0_END    (0x00418D0F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR1_START  (0x00418D10)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR1_END    (0x00418D1F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR2_START  (0x00418D20)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR2_END    (0x00418D2F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR3_START  (0x00418D30)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR3_END    (0x00418D3F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR4_START  (0x00418D40)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR4_END    (0x00418D4F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR5_START  (0x00418D50)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR5_END    (0x00418D5F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR6_START  (0x00418D60)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR6_END    (0x00418D6F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR7_START  (0x00418D70)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR7_END    (0x00418D7F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR8_START  (0x00418D80)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR8_END    (0x00418D8F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR9_START  (0x00418D90)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR9_END    (0x00418D9F)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR10_START (0x00418DA0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR10_END   (0x00418DAF)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR11_START (0x00418DB0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR11_END   (0x00418DBF)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR12_START (0x00418DC0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR12_END   (0x00418DCF)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR13_START (0x00418DD0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR13_END   (0x00418DDF)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR14_START (0x00418DE0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR14_END   (0x00418DEF)

/** SIA LUT Registers for Egress, Pipe 1, Group 1, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR15_START (0x00418DF0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP1_SLTR15_END   (0x00418DFF)

/****************/

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR0_START  (0x00418E00)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR0_END    (0x00418E0F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR1_START  (0x00418E10)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR1_END    (0x00418E1F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR2_START  (0x00418E20)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR2_END    (0x00418E2F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR3_START  (0x00418E30)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR3_END    (0x00418E3F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR4_START  (0x00418E40)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR4_END    (0x00418E4F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR5_START  (0x00418E50)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR5_END    (0x00418E5F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR6_START  (0x00418E60)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR6_END    (0x00418E6F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR7_START  (0x00418E70)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR7_END    (0x00418E7F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR8_START  (0x00418E80)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR8_END    (0x00418E8F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR9_START  (0x00418E90)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR9_END    (0x00418E9F)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR10_START (0x00418EA0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR10_END   (0x00418EAF)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR11_START (0x00418EB0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR11_END   (0x00418EBF)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR12_START (0x00418EC0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR12_END   (0x00418ECF)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR13_START (0x00418ED0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR13_END   (0x00418EDF)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR14_START (0x00418EE0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR14_END   (0x00418EEF)

/** SIA LUT Registers for Egress, Pipe 1, Group 2, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR15_START (0x00418EF0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP2_SLTR15_END   (0x00418EFF)

/****************/

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR0. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR0_START  (0x00418F00)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR0_END    (0x00418F0F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR1. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR1_START  (0x00418F10)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR1_END    (0x00418F1F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR2. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR2_START  (0x00418F20)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR2_END    (0x00418F2F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR3. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR3_START  (0x00418F30)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR3_END    (0x00418F3F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR4. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR4_START  (0x00418F40)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR4_END    (0x00418F4F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR5. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR5_START  (0x00418F50)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR5_END    (0x00418F5F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR6. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR6_START  (0x00418F60)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR6_END    (0x00418F6F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR7. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR7_START  (0x00418F70)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR7_END    (0x00418F7F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR8. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR8_START  (0x00418F80)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR8_END    (0x00418F8F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR9. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR9_START  (0x00418F90)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR9_END    (0x00418F9F)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR10. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR10_START (0x00418FA0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR10_END   (0x00418FAF)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR11. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR11_START (0x00418FB0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR11_END   (0x00418FBF)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR12. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR12_START (0x00418FC0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR12_END   (0x00418FCF)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR13. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR13_START (0x00418FD0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR13_END   (0x00418FDF)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR14. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR14_START (0x00418FE0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR14_END   (0x00418FEF)

/** SIA LUT Registers for Egress, Pipe 1, Group 3, and SLTR15. */
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR15_START (0x00418FF0)
#define SCE_SIA_LUT_PIPE1_EGR_GRP3_SLTR15_END   (0x00418FFF)

#define KBP_OP2_SIA_LUT_ADDR_SCE(sia_lut_start, sltr_idx, grp_num, reg_no) (sia_lut_start + (grp_num * 0x100) + (sltr_idx * 0x10) + reg_no)
#define KBP_OP2_SCE0_ING_SIA_LUT_ADDRESS(idx, grp_num, reg_no)        (SCE_SIA_LUT_PIPE0_ING_GRP0_SLTR0_START + (grp_num * 0x100) + (idx * 0x10) + reg_no)
#define KBP_OP2_SCE0_EGR_SIA_LUT_ADDRESS(idx, grp_num, reg_no)        (SCE_SIA_LUT_PIPE0_EGR_GRP0_SLTR0_START + (grp_num * 0x100) + (idx * 0x10) + reg_no)
#define KBP_OP2_SCE1_ING_SIA_LUT_ADDRESS(idx, grp_num, reg_no)        (SCE_SIA_LUT_PIPE1_ING_GRP0_SLTR0_START + (grp_num * 0x100) + (idx * 0x10) + reg_no)
#define KBP_OP2_SCE1_EGR_SIA_LUT_ADDRESS(idx, grp_num, reg_no)        (SCE_SIA_LUT_PIPE1_EGR_GRP0_SLTR0_START + (grp_num * 0x100) + (idx * 0x10) + reg_no)


/** Reverse Counter/Stats Address Translation (RCAT) Table Registers for Stats/Counters Eviction for Core 0/1. */
#define SCB_RCAT_TABLE_START                    (0x00400800)
#define SCB_RCAT_TABLE_END                      (0x004009FF)
/** Address of RCAT entry given the index */
#define KBP_OP2_RCAT_CAM_REG_ENTRY_ADDR(idx)    (SCB_RCAT_TABLE_START + (idx))

/** Mask for 46b Host Address for RCAT entry */
#define KBP_OP2_RCAT_HOST_ADDR_MASK             (0x3FFFFFFFFFFFULL)

/** Shift for 46b Host Address for RCAT entry */
#define KBP_OP2_RCAT_HOST_ADDR_SHIFT            (18)

/** Clock count between two eviction grant command generated by SCB */
#define KBP_OP2_EVICT_GRANT_RATE_COUNT          (0xFF)

#define KBP_OP2_LTR_ADDR_RES_CNTRL(ltr)         (0x00040084 + (ltr) * 0x100)


/**
 * SCP-pair enable register.
 * Each one bit will enable/disable each scp_pair per UDC, where 1'b1 for enable power on.
 * It exists in stats common block.
 * Reset value is 0x0.
 *
 */
struct op2_scp_pwr_cfg_reg {
    __EO_2(uint64_t pwr_cfg:16,    /**< Power up SCP-pairs for Core 0/1. */
           uint64_t rsvd:48);      /**< Reserved */
};

struct op2_scp_pwr_status_reg {
    uint64_t pwr_status;    /**< Return Power up SCP-pairs for Core 0/1. */
};


/**
 * SCP Ctrl0 config register, one per UDC (32 total per OP2 chip).
 * An SCP-pair enable register per UDC.
 * Each one bit will enable/disable each scp_pair, where 1'b1 for enable power on.
 * It has a 16b bitmap for USB dynamic eviction enable: 1b per USB.
 */
struct op2_udc_scp_ctrl0_reg {
    __EO_4(uint64_t scp0_en:1,              /**< Enable counter engine (SCP) 0. */
           uint64_t scp1_en:1,              /**< Enable counter engine (SCP) 1. */
           uint64_t dynamic_evic_en:1,      /**< Enable/disable dynamic (STACE) eviction for USB. */
           uint64_t rsrvd:61);              /**< Reserved. */
};


/**
 * SCP Ctrl1 config register, one per UDC (32 total per OP2 chip).
 * Returns the counter type for evicted counters, per USB pair.
 *
 */
struct op2_udc_scp_ctrl1_reg {
    __EO_9(uint64_t usbp0_cntr_type:2,      /**< USB-pair 0 counter type. */
           uint64_t usbp1_cntr_type:2,      /**< USB-pair 1 counter type. */
           uint64_t usbp2_cntr_type:2,      /**< USB-pair 2 counter type. */
           uint64_t usbp3_cntr_type:2,      /**< USB-pair 3 counter type. */
           uint64_t usbp4_cntr_type:2,      /**< USB-pair 4 counter type. */
           uint64_t usbp5_cntr_type:2,      /**< USB-pair 5 counter type. */
           uint64_t usbp6_cntr_type:2,      /**< USB-pair 6 counter type. */
           uint64_t usbp7_cntr_type:2,      /**< USB-pair 7 counter type. */
           uint64_t rsrvd:48);              /**< Reserved. */
};

/**
 * SCP LFSR1 initial seed. It MUST not equal to zero.
 * Each SCP engine has 3 LFSR's. 2 x 32b + 1 x 31b.
 */
struct op2_udc_scp_stace_lfsr1_reg {
    __EO_2(uint64_t lfsr1_seed:32,              /**< LFSR1 initial seed. */
           uint64_t rsrvd:32);              /**< Reserved. */
};

/**
 * SCP LFSR2 initial seed. It MUST not equal to zero.
 * Each SCP engine has 3 LFSR's. 2 x 32b + 1 x 31b.
 */
struct op2_udc_scp_stace_lfsr2_reg {
    __EO_2(uint64_t lfsr2_seed:32,              /**< LFSR2 initial seed. */
           uint64_t rsrvd:32);              /**< Reserved. */
};

/**
 * SCP LFSR3 initial seed. It MUST not equal to zero.
 * Each SCP engine has 3 LFSR's. 2 x 32b + 1 x 31b.
 */
struct op2_udc_scp_stace_lfsr3_reg {
    __EO_2(uint64_t lfsr3_seed:31,              /**< LFSR2 initial seed. */
           uint64_t rsrvd:33);              /**< Reserved. */
};


struct op2_kpu_segs_a_e
{
    __EO_17(uint32_t fill0a:1,        /**< If set, segment 10 filled with 0s not read from master key */
            uint32_t starta:7,        /**< Start position of segment 10 in master key */
            uint32_t len_minus_1_a:4, /**< Length of segment 10 (0 means 1 byte, 15 means 16) */
            uint32_t fill0b:1,        /**< If set, segment 11 filled with 0s not read from master key */
            uint32_t startb:7,        /**< Start position of segment 11 in master key */
            uint32_t len_minus_1_b:4, /**< Length of segment 11 (0 means 1 byte, 15 means 16) */
            uint32_t fill0c:1,        /**< If set, segment 12 filled with 0s not read from master key */
            uint32_t startc:7,        /**< Start position of segment 12 in master key */
            uint32_t len_minus_1_c:4, /**< Length of segment 12 (0 means 1 byte, 15 means 16) */
            uint32_t fill0d:1,        /**< If set, segment 13 filled with 0s not read from master key */
            uint32_t startd:7,        /**< Start position of segment 13 in master key */
            uint32_t len_minus_1_d:4, /**< Length of segment 13 (0 means 1 byte, 15 means 16) */
            uint32_t fill0e:1,        /**< If set, segment 14 filled with 0s not read from master key */
            uint32_t starte:7,        /**< Start position of segment 14 in master key */
            uint32_t len_minus_1_e:4, /**< Length of segment 14 (0 means 1 byte, 15 means 16) */
            uint32_t enable:1,        /**< Enable the above five segments */
            uint32_t unused:3);       /**< Unused, for aligning to 64b register */
};


/**
 * SCP register to control dynamic evictions.
 */
struct op2_udc_scp_stace_lfsr_mask_reg {
    __EO_3(uint64_t lfsr_mask:28,           /**< Mask value anded with actual LFSR value */
           uint64_t lfsr_mask_en:1,         /**< LFSR mask enable for debug purposes */
           uint64_t resv:35);               /**< Reserved */
};


/**
 * SCP0/1 register to count dropped commands.
 */
struct op2_udc_scp_cmd_drop_reg {
    __EO_2(uint64_t cmd_drop:48,           /**< Commands dropped N#. */
           uint64_t resv:16);               /**< Reserved. */
};

/**
 * SCP0 FIFO Occupancy count Register.
 */
struct op2_udc_scp_fifo_occp_reg {
    __EO_11(uint64_t rd_intr_fifo_occp:6,               /**< Command interface fifo occupancy. */
           uint64_t rd_psf_fifo_occp:6,                 /**< Post service fifo occupancy. */
           uint64_t rd_dp_fifo_occp:6,                  /**< Data FIFO occupancy. */
           uint64_t wr_addr_pool_fifo_occp:6,           /**< Write address free pool fifo occupancy. */
           uint64_t wr_addr_bank0_fifo_occp:6,          /**< Write address bank0 fifo occupancy. */
           uint64_t wr_addr_bank1_fifo_occp:6,          /**< Write address bank1 fifo occupancy. */
           uint64_t wr_addr_bank2_fifo_occp:6,          /**< Write address bank2 fifo occupancy. */
           uint64_t wr_addr_bank3_fifo_occp:6,          /**< Write address bank3 fifo occupancy. */
           uint64_t dyn_evic_fifo_occp:2,               /**< Dynamic eviction fifo occupancy. */
           uint64_t cntrl_evic_fifo_occp:4,             /**< Central eviction fifo occupancy. */
           uint64_t resv:16);                           /**< Reserved. */
};

/** Search and Stats Rate Control Register */
struct op2_rate_ctrl_reg {
    __EO_8(uint64_t clk_cerdit:10,
           uint64_t ctrl_cerdit:10,
           uint64_t current_clk_cerdit:10,
           uint64_t current_ctrl_cerdit:10,
           uint64_t reserved:20,
           uint64_t freeze_read_back:1,
           uint64_t read_freeze:1,
           uint64_t enable_rate_ctrl:2);
};

/** SCP status register 0 for SCP0/SCP1. */
struct scp_intr_status_udc {
    __EO_6(uint64_t scp_croe_sts:1,                 /** Counter saturation (roll-over) detected. */
           uint64_t rsrvd0:1,
           uint64_t scp_mber_sts:1,                 /** Multi-bit error detected on memory read. */
           uint64_t scp_croe_add:25,                /** Address associated with roll over error. */
           uint64_t scp_mber_add:25,                /** Address associated with multi-bit error. */
           uint64_t rsrvd1:11);
};

/** SCP intr enable register for SCP0/SCP1. */
struct scp_intr_enable_udc {
    __EO_6(uint64_t scp_croe_en:1,                  /** Communicate error to CRB on counter saturation error. */
           uint64_t scp_mber_sts_en:1,              /** Communicate error to CRB on multibit error of memory read. */
           uint64_t intrf_fifo_par_err:1,           /** Communicate error to CRB on parity error of PSF FIFO. */
           uint64_t psf_fifo_par_err:1,             /** Communicate error to CRB on parity error of PSF FIFO. */
           uint64_t dp_fifo_par_err:1,              /** Communicate error to CRB on parity error of DP FIFO. */
           uint64_t rsrvd:59);
};

/** SCP status register 2 for SCP0/SCP1. */
struct scp_intr_status2_udc {
    __EO_7(uint64_t scp_inrf_fifo_par_err:1,        /** SCP interface fifo parity error. */
           uint64_t scp_psf_fifo_par_err:1,         /** SCP post service fifo parity error. */
           uint64_t scp_dp_fifo_par_err:1,          /** SCP data path fifo parity error. */
           uint64_t scp_inrf_fifo_par_addr:5,       /** SCP interface fifo parity error addr. */
           uint64_t scp_psf_fifo_par_addr:5,        /** SCP post service fifo parity error addr. */
           uint64_t scp_dp_fifo_par_addr:4,         /** SCP data path fifo parity error addr. */
           uint64_t rsrvd:47);
};

/**
 *
 * @brief Stats LTR register types. There are 3 registers per SLTR group.
 *
 */
enum kbp_dev_op_sltr_reg_type {
    /** Output of each SCE is a 27b counter address, 16b counter value and counter type. */
    /** Registers for properties of the Stats databases for each Stats Config Engine. */
    KBP_OP2_SLTR_SCE_GRP0_REG0 = 0,
    /** Register for defining the Value and Set Index fields in incoming stats record */
    KBP_OP2_SLTR_SCE_GRP0_REG1,
    /** Register for defining the Pointer fields in incoming stats record */
    KBP_OP2_SLTR_SCE_GRP0_REG2,

    KBP_OP2_SLTR_SCE_GRP1_REG0,
    KBP_OP2_SLTR_SCE_GRP1_REG1,
    KBP_OP2_SLTR_SCE_GRP1_REG2,

    KBP_OP2_SLTR_SCE_GRP2_REG0,
    KBP_OP2_SLTR_SCE_GRP2_REG1,
    KBP_OP2_SLTR_SCE_GRP2_REG2,

    KBP_OP2_SLTR_SCE_GRP3_REG0,
    KBP_OP2_SLTR_SCE_GRP3_REG1,
    KBP_OP2_SLTR_SCE_GRP3_REG2,

    /** Register end value */
    KBP_OP2_SLTR_REG_END
};

/**
 *   Reads from an SLTR register depending on LTR register type.
 *
 * @param device Valid device handle.
 * @param sltr_num valid SLTR number
 * @param pipe_id Internal SCE Pipe ID: {0,1}. It's derived from port_id {0,1,2,3}.
 * @param ing_egr Ingress or Egress flag to mark start of SLTR address.
 * @param reg_type Valid SLTR register type
 * @param o_data Array which will hold the data read from SLTR
 * @param reg_name String name of this SLTR
 * @param reg_adrs Register address
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op2_sltr_read(struct kbp_device *device,
                                uint8_t sltr_num,
                                uint8_t pipe_id, uint8_t ing_egr,
                                enum kbp_dev_op_sltr_reg_type reg_type,
                                struct op2_sltr *o_data,
                                char *reg_name,
                                uint32_t *reg_adrs);

/**
 *   Writes to an SLTR register depending on SLTR register type.
 *
 * @param device Valid device handle.
 * @param sltr_num Valid SLTR number.
 * @param port_id Internal SCE Pipe ID: 0, 1, 2 and 3 --> maps to 0 and 1.
 * @param ing_egr Ingress or Egress flag to mark start of SLTR address.
 * @param reg_type Valid SLTR register type.
 * @param data Array which holds the data to write to SLTR.
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op2_sltr_write(struct kbp_device *device,
                                uint8_t sltr_num,
                                uint8_t pipe_id, uint8_t ing_egr,
                                enum kbp_dev_op_sltr_reg_type reg_type,
                                struct op2_sltr *data);

/**
 *   Reads to an SIA LUT register depending on SLTR index.
 */
kbp_status kbp_dm_op2_sia_lut_read(struct kbp_device *device,
                                uint8_t sltr_idx,
                                uint8_t pipe_id, uint8_t ing_egr,
                                uint8_t grp_id,
                                struct op2_sia_lut *o_data,
                                char *lut_reg_name, uint32_t *reg_adrs);
/**
 *   Writes to an SIA LUT register depending on SLTR index.
 */
kbp_status kbp_dm_op2_sia_lut_write(struct kbp_device *device,
                                uint8_t sltr_idx, uint8_t sia_idx,
                                uint8_t pipe_id, uint8_t ing_egr,
                                uint8_t grp_id,
                                struct op2_sia_lut *data);

/**
 * Performs the STATS command send
 *
 * @param device Valid device handle.
 * @param stats_records incoming stats records (512b).
 * @param num_bytes valid number of incoming stats records bytes.
 * @param pipe_id SRE/SCE Pipe ID: 0/1.
 * @param port_id OP2 port ID: 0/1/2/3.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_dm_op2_stats_cmd(struct kbp_device * device, uint8_t *stats_records,
                                uint32_t num_bytes, uint8_t pipe_id,
                                uint8_t port_id);


/**
 *   OP2 Writes to device STATS/CT address translation CAM.
 *
 * @param device Valid KBP device handle.
 * @param e Valid KBP DB entry.
 * @param tbl_id Stats/CT table ID (6b).
 * @param ct_type Stats/CT counter type (2b).
 * @param phy_usb_addr Stats/CT output physical (MSB) address bits (9b).
 * @param logical_idx Stats/CT input logical address bits (10b).
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op2_stats_write_ct_cam(struct kbp_device *device,
                              uint8_t tbl_id, int32_t ct_type, uint32_t phy_usb_addr,
                              uint32_t logical_idx);

/**
 *   Performs search for OP2. Accepts two search keys can be sent from either port
 *   to produce the expected result.
 *
 * @param device Valid device handle.
 * @param core_id0 The input core id for key0.
 * @param bank_id0 The input bank_id for key0.
 * @param cascade0 The input cascade bit for key0.
 * @param ltr0 Valid LTR number for key0
 * @param cb_addr0 The Context buffer address for the first key
 * @param key0 The first Master key bytes
 * @param key_len0 The number of valid bytes in key0
 * @param port_id1 port id for the second key
 * @param ltr1 Valid LTR number for key1
 * @param cb_addr1 The Context buffer address for the second key
 * @param core_id1 The input core id for key1.
 * @param bank_id1 The input bank_id for key1.
 * @param cascade1 The input cascade bit for key1.
 * @param key_len1 The number of valid bytes in key1
 * @param o_search_results The parsed search result returned from the device
 *
 * @return KBP_OK on successful completion of call and result contents are valid. Or an error code
 */

kbp_status kbp_dm_op2_cbwcmp(struct kbp_device *device,
                             uint32_t port_id0, int32_t ltr0,
                             uint32_t ctx0, const uint8_t *key0, uint32_t key_len0,
                             struct kbp_search_result *result0,
                             uint32_t port_id1, int32_t ltr1,
                             uint32_t ctx1, const uint8_t *key1, uint32_t key_len1,
                             struct kbp_search_result *result1);


/**
 * Generic API to scrub DMA buffer based on the DMA channel number
 *
 * @param device Valid device handle
 * @param channel_num DMA channel number to identify the DMA buffer
 * @param buffer Buffer to copy the scrubbed DWs
 * @param buffer_size Size of the buffer
 * @param num_dws_read Actual number of DWs read out into the buffer
 *
 * @return KBP_OK on success OR an error code on failure
 */
kbp_status kbp_dm_op2_scrub_dma_buffer(struct kbp_device *device, int32_t channel_num,
                                       uint64_t *buffer, uint32_t buffer_size,
                                       uint32_t *num_dws_read);

/**
 * API to perform write in Stats path
 *
 * @param device Valid device handle
 * @param address Valid device address
 * @param data Array which holds to data to write
 *
 * @return KBP_OK on success or an error code on failure.
 */
kbp_status kbp_dm_op2_stats_pio_write(struct kbp_device *device, uint32_t address, uint8_t *data);

/**
 * API to perform read in Stats path
 *
 * @param device Valid device handle
 * @param address Valid device address
 * @param data Array which holds read data
 *
 * @return KBP_OK on success or an error code on failure.
 */
kbp_status kbp_dm_op2_stats_pio_read(struct kbp_device *device, uint32_t address, uint8_t *data);

/**
 * Poll the register in Stats path for maximum "count" times until data
 * at specified bit positions specified by mask read from the register
 * is equal to 1 for power up and 0 for power down
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
kbp_status kbp_dm_op2_stats_poll_reg(struct kbp_device *device, uint32_t address, uint64_t data,
                                     uint64_t mask, uint32_t count);

/**
 * This function checks if the resource is common to both cores (shared between cores)
 *
 * @param device valid device handle
 * @param address resource address
 * @param is_common set to 1 if the address is found to be common to both cores
 *
 * @return KBP_OK on success or an error code otherwise
 */
kbp_status kbp_dm_op2_is_common_resource(struct kbp_device *device, uint32_t address, uint32_t *is_common);



/**
 * Read the Device Identification Register (DIR) and get the resources according to the device type
 *
 * @param device Valid device handle
 *
 * @return KBP_OK on success or an error code otherwise
 */

kbp_status kbp_dm_op2_query_capabilities(struct kbp_device *device);


#ifdef __cplusplus
}
#endif

#endif /* __DEVICE_OP2_H */

