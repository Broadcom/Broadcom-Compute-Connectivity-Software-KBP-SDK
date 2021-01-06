/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __HW_LIMITS_H
#define __HW_LIMITS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @cond INTERNAL
 *
 * @file hw_limits.h
 *
 * The limits of the various HW pieces. These defines must only
 * be used in places that want to pre-define arrays in
 * data structures. The sizes here generally depict the largest
 * possible sizes across all devices. Additionally, some
 * constants of the device that have never changed across any
 * class of of our devices are pre-defined here.
 *
 * All device specific information must be derived from the device handle
 *
 */

/**
 * Macro for adjusting value to the smallest multiple of align that is greater than value
 * Align should be a power of 2
 */
#define ALIGN_UP(value, align) (((value) + ((align) - 1)) & ~((align) - 1))

/* ==================================================
 * These values are fixed across all chip lines, hence
 * can be used as constants
 */

/**
 * Number of bits in byte
 */

#define KBP_BITS_IN_BYTE (8)

/**
 * Maximum number of key processing units
 */

#define KBP_HW_MAX_KPUS (4)

/**
 * Maximum number of databases that can be searched by
 * single instruction. (compare3/op)
 */

#define KBP_HW_MAX_SEARCH_DB (8)

/**
 * Maximum number of cycles an instruction takes (compare3)
 */

#define KBP_MAX_INSTRUCTION_CYCLES (2)

/**
 * Maximum number of cascaded devices
 */
#define KBP_MAX_CASCADED_DEVICES (4)

/**
 * Maximum number of broadcast devices
 */
#define KBP_MAX_BROADCAST_DEVICES (8)


/**
 * Maximum number of soft parity error fifo depth : O3S
 */
#define KBP_MAX_PARITY_FIFO_DEPTH (16)

/**
 * Maximum number of soft parity error fifo depth : OPrime
 */
#define KBP_OP_MAX_PARITY_FIFO_DEPTH (32)

/**
 * Maximum number of parity error fifo place holder depth
 */
#define KBP_MAX_PLACE_HOLDER_PARITY_FIFO_DEPTH (256)

/**
 *Number of Index range bits to shift
 */

#define KBP_NUMBER_OF_INDEX_BITS_TO_SHIFT (512)


/* ==================================================
 * These values represent the max limits for pre-defining
 * data structure arrays etc.
 */

/**
 * Max possible range comparisons per database
 */

#define KBP_HW_MAX_RANGE_COMPARES (4)

/**
 * Max DBA entry width in bits
 */

#define KBP_HW_MAX_DBA_WIDTH_1 (640)

/**
 * Max DBA entry width in bytes
 */

#define KBP_HW_MAX_DBA_WIDTH_8 (KBP_HW_MAX_DBA_WIDTH_1 / KBP_BITS_IN_BYTE)


/**
 * Min DBA entry width in bits
 */

#define KBP_HW_MIN_DBA_WIDTH_1 (80)

/**
 * Min DBA entry width in bytes
 */

#define KBP_HW_MIN_DBA_WIDTH_8 (KBP_HW_MIN_DBA_WIDTH_1 / KBP_BITS_IN_BYTE)


/**
 * Max AB Depth
 */

#define KBP_HW_MAX_AB_DEPTH (4096)

/**
 * Max UDA entry width in bits
 */
#define KBP_HW_MAX_UDA_WIDTH_1 (256)

/**
 * Max UDA entry width in bytes
 */
#define KBP_HW_MAX_UDA_WIDTH_8 (KBP_HW_MAX_UDA_WIDTH_1 / KBP_BITS_IN_BYTE)

/**
 * Min UDA entry width in bits
 */
#define KBP_HW_MIN_UDA_WIDTH_1 (32)

/**
 * Min UDA entry width in bytes
 */
#define KBP_HW_MIN_UDA_WIDTH_8 (KBP_HW_MIN_UDA_WIDTH_1 / KBP_BITS_IN_BYTE)

/**
 * Max DBA blocks
 */

#define KBP_HW_MAX_DBA_BLOCKS (256)

/**
 * Number of Super blocks per UDM
 */

#define KBP_HW_NUM_SB_PER_UDM (4)

/**
 * Minimum priority (maximum value) supported by the device
 */
#define KBP_HW_MINIMUM_PRIORITY (0x3FFFFF)

/**
 * Length of the priority supported by the device in bits
 */
#define KBP_HW_PRIORITY_SIZE_1 (24)

/**
 * Length of the priority supported by the device in bytes
 */
#define KBP_HW_PRIORITY_SIZE_8 (KBP_HW_PRIORITY_SIZE_1 / KBP_BITS_IN_BYTE)

/**
 * Maximum number AB's ever
 */

#define KBP_HW_MAX_AB (256)

/**
 * Maximum number Super Blocks's ever
 */

#define KBP_HW_MAX_DBA_SB (64)

/**
 * Maximum number of LTR in single port mode
 */

#define KBP_HW_MAX_LTRS (128)

/**
 * Maximum number of LTR in dual port mode
 */
#define KBP_HW_MAX_LTR_DUAL_PORT (64)

/**
 * Maximum possible UDA super blocks
 */
#define KBP_HW_MAX_UDA_SB (256)

/**
 * Number of UDA super blocks in 12K
 */
#define KBP_12K_HW_MAX_UDA_SB (64)

/**
 * Max Width in bits of the LPM Key
 */
#define KBP_LPM_KEY_MAX_WIDTH_1 (160)

/**
 * Max Width in bytes of the LPM Key
 */
#define KBP_LPM_KEY_MAX_WIDTH_8 (20)


#define KBP_HW_MAX_SEARCH_KEY_WIDTH_1 (1280)

#define KBP_HW_MAX_SEARCH_KEY_WIDTH_8 (160)


/**
 * Maximum width of hit index returned as part of
 * result.
 */
#define KBP_HW_HIT_INDEX_WIDTH_1 (24)

/**
 * Maximum number of range units
 */
#define HW_MAX_RANGE_UNITS (16)

/**
 * UDM size in Mb
 */
#define KBP_HW_MAX_UDM_SIZE_MB (8)

/**
 * UDA SB size in Mb
 */
#define KBP_HW_MAX_UDA_SB_SIZE_MB (2)

/**
 * maximum BMRs can used for larger widths (greater then 320b)
 */
 #define KBP_MAX_BMR_USED_FOR_LARGER_WIDTH (3)

 /**
  * maximum meta priority value
  */
 #define KBP_MAX_META_PRIORITY_VALUE (3)

 /**
  * Number of bytes in SB
  */
 #define KBP_NUM_BYTES_IN_SB ((KBP_HW_MAX_UDA_SB_SIZE_MB * 1024 * 1024) / 8)

 /**
  * Number of AD words in SB
  */
 #define KBP_NUM_AD_WORD_IN_SB (KBP_NUM_BYTES_IN_SB / KBP_HW_MIN_UDA_WIDTH_8)

/**
 * @endcond
 */

#ifdef __cplusplus
}
#endif
#endif                          /* __HW_LIMITS_H */
