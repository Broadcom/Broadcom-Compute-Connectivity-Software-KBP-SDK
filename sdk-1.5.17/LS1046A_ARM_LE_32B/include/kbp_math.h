/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

/*@@NlmCmMath Module
   Summary
   Integral math routines. NO FLOATING POINT!

   Description
   Description goes here
*/

#ifndef INCLUDED_NLMCMMATH_H
#define INCLUDED_NLMCMMATH_H

#include <stdint.h>
#include <kbp_externcstart.h>

uint32_t kbp_crc32(uint32_t crc, const uint8_t * bits, uint32_t num_bytes);
void kbp_compute_crc10_table(void);
uint32_t kbp_fast_crc10(uint8_t * data_p, uint32_t numBytes);
void kbp_crc24(uint64_t data, int32_t reset_crc, uint32_t *crcreg);
uint32_t kbp_find_next_prime(uint32_t lower_bound);

#include <kbp_externcend.h>

#endif
