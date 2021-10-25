/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DEVICE_KAPS_H
#define __DEVICE_KAPS_H

#include <stdint.h>
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond INTERNAL
 *
 * @file device_kaps.h
 *
 * Defines depths, widths and the number of for all software-visible resources in KAPS
 */


#define KAPS_AD_WIDTH_1 (20)

#define KAPS_SEARCH_INTERFACE_WIDTH_1 (160)

#define KAPS_SEARCH_INTERFACE_WIDTH_8 (20)

#define KAPS_DBA_WIDTH_8 (20)

#define KAPS_DBA_WIDTH_1 (160)

#define KAPS_REGISTER_WIDTH_1 (32)

#define KAPS_REGISTER_WIDTH_8 (4)

#define KAPS_HB_ROW_WIDTH_8 (2)

#define KAPS_HB_ROW_WIDTH_1 (16)





/*Device Ids*/

#define KAPS_DEFAULT_DEVICE_ID (0x0001)

#define KAPS_QUMRAN_DEVICE_ID (0x0002) /*QAX*/

#define KAPS_JERICHO_PLUS_DEVICE_ID (0x0003)

#define KAPS_QUX_DEVICE_ID  (0x0004)

#define KAPS_JERICHO_2_DEVICE_ID      (0x0005)



/*JR+ sub type*/
#define KAPS_JERICHO_PLUS_SUB_TYPE_FM0 (0)

#define KAPS_JERICHO_PLUS_SUB_TYPE_FM4 (1)

#define KAPS_JERICHO_PLUS_SUB_TYPE_JER_MODE_FM0 (2)

#define KAPS_JERICHO_PLUS_SUB_TYPE_JER_MODE_FM4 (3)


/*JR2 sub types*/
#define KAPS_JERICHO_2_SUB_TYPE_TWO_LEVEL (0)

#define KAPS_JERICHO_2_SUB_TYPE_THREE_LEVEL (1)

#define KAPS_JERICHO_2_SUB_TYPE_Q2A_THREE_LEVEL (2)

#define KAPS_JERICHO_2_SUB_TYPE_J2P_THREE_LEVEL (3)




/*Revision register*/

#define KAPS_REVISION_REGISTER_ADDR (0x0)

#define KAPS_JERICHO_REVISION_REG_VALUE (0x00010000)

#define KAPS_QUMRAN_AX_REVISION_REG_VALUE (0x00020000)

#define KAPS_JERICHO_PLUS_FM0_REVISION_REG_VALUE (0x00030000)

#define KAPS_JERICHO_PLUS_FM4_REVISION_REG_VALUE (0x00030001)

#define KAPS_JERICHO_PLUS_JER_MODE_FM0_REVISION_REG_VALUE (0x00030002)

#define KAPS_JERICHO_PLUS_JER_MODE_FM4_REVISION_REG_VALUE (0x00030003)


#define KAPS_QUX_REVISION_REG_VALUE (0x00040000)

#define KAPS_JERICHO_2_REVISION_REG_VALUE (0x00050000)








/**
 * @brief KAPS DBA entry
 */

struct kaps_dba_entry
{
    uint8_t key[KAPS_SEARCH_INTERFACE_WIDTH_8]; /**< 160b data or mask */
    __EO_3(uint32_t resv:4,       /**< Unused */
           uint32_t is_valid:2,   /**< Valid bit per 80b part of data/mask */
           uint32_t pad:2);       /**< SW pad */
};

/**
 * @brief KAPS AD info representation
 */
struct kaps_ad_entry
{

    __EO_5(uint32_t ad:20,   /**< Associated data */
           uint32_t resv:12, /**< unused */
           uint32_t resv1,/**< unused */
           uint32_t resv2,/**< unused */
           uint32_t resv3);/**< unused */
};





/**
 * @endcond
 */

#ifdef __cplusplus
}
#endif

#endif /* __DEVICE_KAPS_H */
