/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef INCLUDED_kbp_UTILITY_H
#define INCLUDED_kbp_UTILITY_H

#include <stdint.h>
#include "kbp_externcstart.h"

/**
 * Min function
 */
#define KBP_MIN(X, Y) (kbp_assert_((X)==(X), "Side effect in macro parm") kbp_assert_((Y)==(Y), "Side effect in macro parm") (X) <= (Y) ? (X) : (Y))

/**
 * Max function
 */
#define KBP_MAX(X, Y) (kbp_assert_((X)==(X), "Side effect in macro parm") kbp_assert_((Y)==(Y), "Side effect in macro parm") (X) >= (Y) ? (X) : (Y))

#define kbp_NUM_BYTES_PER_80_BITS 10
#define kbp_BITS_IN_REG           80
/*------------------FUNCTION FOR COMMON---------------------*/

void convert_dm_to_xy(uint8_t * data_d, uint8_t * data_m, uint8_t * data_x, uint8_t * data_y, uint32_t datalenInBytes);


void convert_xy_to_dm(uint8_t *data_x, uint8_t *data_y, uint8_t* data_d, uint8_t *data_m, uint32_t dataLenInBytes);



/**
 * Performs LPT encoding
 *
 * @param x valid pointer to x data
 * @param y valid pointer to y data
 * @param length length of the data array
 *
 * @return none
 */
void kbp_lpt_encode(uint8_t *x, uint8_t *y, uint32_t length);


extern
uint32_t ReadBitsInRegs(uint8_t * RegOf80Bits, uint8_t end, uint8_t start);
extern
void WriteBitsInRegs(uint8_t * RegOf80Bits, uint8_t end, uint8_t start, uint32_t value);
extern
void WriteBitsInRegsAndWrapAround(uint8_t * RegOf80Bits, uint8_t len, uint8_t start, uint32_t value, uint8_t wrapBoundary);
extern
void PrintReginNibbles(uint8_t * RegOf80Bits);

/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
extern
uint32_t ReadBitsInArrray(uint8_t * Arr, uint32_t ArrSize, uint32_t EndPos, uint32_t StartPos);

extern
void WriteBitsInArray(uint8_t * Arr, uint32_t ArrSize, uint32_t EndPos, uint32_t StartPos, uint32_t Value);
/*----------------------------------------------------------------*/
extern 
uint32_t Kbp_Stats_ReadBitsInArrray(uint8_t * Arr, uint32_t ArrSize, uint32_t EndPos, uint32_t StartPos);

extern
uint32_t reverseBitsnk(uint32_t n, uint32_t k);

extern
void kbp_FillOnes(uint8_t * data, uint32_t datalen, uint32_t startBit, uint32_t endBit);

extern
void kbp_FillZeroes(uint8_t * data, uint32_t datalen, uint32_t startBit, uint32_t endBit);

extern
void kbp_CopyData(uint8_t * o_data, uint8_t * data, uint32_t datalen, uint32_t startBit, uint32_t endBit);

void WriteBitsInByte(uint8_t * targetByte_p, uint8_t sourceByte, uint8_t startBit, uint8_t endBit);

void WriteFirstNBytes(uint8_t * arr, uint32_t numBytes, uint32_t Value);

uint64_t LongReadBitsInArray(uint8_t * Arr, uint32_t ArrSize, uint32_t EndPos, uint32_t StartPos);

void LongWriteBitsInArray(uint8_t * Arr, uint32_t ArrSize, uint32_t EndPos, uint32_t StartPos, uint64_t Value);

void FlipBitsInArray(uint8_t * data_p, uint32_t totalNumBytes, uint32_t endPos, uint32_t startPos);

void kbp_swap_bytes(uint8_t *dest_data, const uint8_t *src_data, uint8_t flag, int32_t length);

//uint32_t Kbp_Stats_ReadBitsInArrray(uint8_t * Arr, uint32_t ArrSize, uint32_t EndPos, uint32_t StartPos);

#include "kbp_externcend.h"
#endif                          /* INCLUDED_kbp_UTILITY_H */
 /**/
