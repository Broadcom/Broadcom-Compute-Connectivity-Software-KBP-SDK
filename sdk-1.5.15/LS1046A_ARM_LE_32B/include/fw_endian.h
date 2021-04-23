/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_ENDIAN_H
#define __KBP_ENDIAN_H


//simple instructions
#define NOP         0x0
#define PIOWR       0x1
#define PIORDX      0x2
#define PIORDY      0x3
#define fPIORDX     0x4  /* fast version of PIORDX. It's executed directly like compare as opposed to through EMC pipe */
#define LSNBW       0x5

#if defined(OP2_FW) || defined(FW_USE_MODEL)
#define BLKREAD     0x6
#define BLKWRITE    0x7
#endif

// Complex instructions
// DBA
#define BLKCP       0x8
#define BLKMV       0x9
#define BLKCLR      0xA
#define BLKEV       0xB

#define BLKCI_MAXPAYLOAD    0x2

// LSN
#define LSNNW       0xC
#define LSNSBC      0xD
#define LSNCLR      0xE

#define LSN_MAX_PAYLOAD     0x2
#define LSNNW_MAX_PAYLOAD   0x5
#define LSNNW_MIN_PAYLOAD   0x2

//Generic complex instructions
#define BRICKWR             0x20
#define WRBRICK             0x30
#define ATTN_REG0           0x70
#define WATCHDOG_RECOVERY   0x7C
#define WATCHDOG            0X7D
#define AOMTIMEOUT          0x7E
#define LOOPBACK            0x7F

/** Opcode for IOCWA complex instruction */
#define KBP_OP_INSTR_IOCWA              (0xF)
/** HWA LSNNW Opcode */
#define KBP_OPCODE_LSNNW                (0xc)


#ifndef __KBP_PORTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @file fw_endian.h
 *
 * Macros to ensure bitfields are appropriately positioned in
 * structures irrespective of endianess of host system
 *
 * @addtogroup PORTABILITY_API
 * @{
 */

#if defined(KBP_BIG_ENDIAN) && defined(KBP_LITTLE_ENDIAN)
#error cannot define both big and little endian
#endif

#if !defined(KBP_BIG_ENDIAN) && !defined(KBP_LITTLE_ENDIAN)
#error Must define either KBP_BIG_ENDIAN or KBP_LITTLE_ENDIAN
#endif

/**
 * Definition of little/big endian operator inside the struct
 */

/** Little Endian */
#if defined(KBP_LITTLE_ENDIAN) || defined(__i386__) || defined(__alpha__)\
      || defined(__ia64) || defined(__ia64__)\
      || defined(__amd64) || defined(__amd64__)\
      || defined(__x86_64) || defined(__x86_64__)\
      || defined(__bfin__) || (!defined(__AARCH64EB__) && (defined(__arm)\
      || defined(__arm__) || defined(aarch64_) || defined(__aarch64__)))
#define __EO_33(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X; Y; Z; AA; BB; CC; DD; EE; FF; GG
#define __EO_32(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X; Y; Z; AA; BB; CC; DD; EE; FF
#define __EO_25(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X; Y
#define __EO_24(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X
#define __EO_23(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W
#define __EO_22(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V
#define __EO_19(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S
#define __EO_18(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R
#define __EO_17(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q
#define __EO_16(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P
#define __EO_15(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O
#define __EO_14(A, B, C, D, E, F, G, H, I, J, K, L, M, N)A; B; C; D; E; F; G; H; I; J; K; L; M; N
#define __EO_13(A, B, C, D, E, F, G, H, I, J, K, L, M)A; B; C; D; E; F; G; H; I; J; K; L; M
#define __EO_12(A, B, C, D, E, F, G, H, I, J, K, L)A; B; C; D; E; F; G; H; I; J; K; L
#define __EO_11(A, B, C, D, E, F, G, H, I, J, K)A; B; C; D; E; F; G; H; I; J; K
#define __EO_10(A, B, C, D, E, F, G, H, I, J)A; B; C; D; E; F; G; H; I; J
#define __EO_9(A, B, C, D, E, F, G, H, I)A; B; C; D; E; F; G; H; I
#define __EO_8(A, B, C, D, E, F, G, H)A; B; C; D; E; F; G; H
#define __EO_7(A, B, C, D, E, F, G)A; B; C; D; E; F; G
#define __EO_6(A, B, C, D, E, F)A; B; C; D; E; F
#define __EO_5(A, B, C, D, E)A; B; C; D; E
#define __EO_4(A, B, C, D)A; B; C; D
#define __EO_3(A, B, C)A; B; C
#define __EO_2(A, B)A; B

#define __KBP_BYTESWAP_32(x) (x)
#define __KBP_BYTESWAP_64(x) (x)

#define FORCE_BYTESWAP_64(x)\
      ((((x) & 0xFF00000000000000ull) >> 56) |   \
      (((x) & 0x00FF000000000000ull) >> 40) |   \
      (((x) & 0x0000FF0000000000ull) >> 24) |   \
      (((x) & 0x000000FF00000000ull) >> 8)  |   \
      (((x) & 0x00000000FF000000ull) << 8)  |   \
      (((x) & 0x0000000000FF0000ull) << 24) |   \
      (((x) & 0x000000000000FF00ull) << 40) |   \
      (((x) & 0x00000000000000FFull) << 56))

/** Big Endian */
#elif defined(KBP_BIG_ENDIAN) || defined(__sparc) || defined(__sparc__)\
    || defined(__powerpc__) || defined(__ppc__)\
    || defined(__hpux) || defined(__hppa)\
    || defined(__s390__) || defined(__mips)\
    || defined(__mips__) || defined(__AARCH64EB__)
#define __EO_33(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF, GG)GG; FF; EE; DD; CC; BB; AA; Z; Y; X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_32(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF)FF; EE; DD; CC; BB; AA; Z; Y; X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_25(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y)Y; X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_24(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X)X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_23(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W) W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_22(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V) V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_19(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S)S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_18(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R)R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_17(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q)Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_16(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_15(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O)O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_14(A, B, C, D, E, F, G, H, I, J, K, L, M, N)N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_13(A, B, C, D, E, F, G, H, I, J, K, L, M)M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_12(A, B, C, D, E, F, G, H, I, J, K, L)L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_11(A, B, C, D, E, F, G, H, I, J, K)K; J; I; H; G; F; E; D; C; B; A
#define __EO_10(A, B, C, D, E, F, G, H, I, J)J; I; H; G; F; E; D; C; B; A
#define __EO_9(A, B, C, D, E, F, G, H, I)I; H; G; F; E; D; C; B; A
#define __EO_8(A, B, C, D, E, F, G, H)H; G; F; E; D; C; B; A
#define __EO_7(A, B, C, D, E, F, G)G; F; E; D; C; B; A
#define __EO_6(A, B, C, D, E, F)F; E; D; C; B; A
#define __EO_5(A, B, C, D, E)E; D; C; B; A
#define __EO_4(A, B, C, D)D; C; B; A
#define __EO_3(A, B, C)C; B; A
#define __EO_2(A, B)B; A

/**
 * Definition of byte swap of 64-bit value
 */
#define __KBP_BYTESWAP_64(x)\
   ((((x) & 0xFF00000000000000ull) >> 56) |   \
    (((x) & 0x00FF000000000000ull) >> 40) |   \
    (((x) & 0x0000FF0000000000ull) >> 24) |   \
    (((x) & 0x000000FF00000000ull) >> 8)  |   \
    (((x) & 0x00000000FF000000ull) << 8)  |   \
    (((x) & 0x0000000000FF0000ull) << 24) |   \
    (((x) & 0x000000000000FF00ull) << 40) |   \
    (((x) & 0x00000000000000FFull) << 56));

/**
 * Definition of byte swap of 32-bit value
 */
#define __KBP_BYTESWAP_32(x)\
   ((((x) & 0xFF000000ul) >> 24) |   \
    (((x) & 0x00FF0000ul) >> 8)  |   \
    (((x) & 0x0000FF00ul) << 8)  |   \
    (((x) & 0x000000FFul) << 24));


#define FORCE_BYTESWAP_64(x) (x)

#endif


/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif
#endif
