/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_PORTABLE_H
#define __KBP_PORTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @file kbp_portable.h
 *
 * Portability-related APIs. These standard implementations for Linux-based and
 * Windows-based systems are available as part of the respective packages. Customers
 * are expected to implement the functions below on any other propriety
 * Operating Systems
 *
 * @addtogroup PORTABILITY_API
 * @{
 */

#if defined(KBP_BIG_ENDIAN) && defined(KBP_LITTLE_ENDIAN)
#error cannot define both big and little endian
#endif

/**
 * Definition of little/big endian operator inside the struct
 */

/** Little Endian */
#if  defined(__i386__) || defined(__alpha__)\
      || defined(__ia64) || defined(__ia64__)\
      || defined(__amd64) || defined(__amd64__)\
      || defined(__x86_64) || defined(__x86_64__)\
      || defined(__bfin__) || (!defined(__AARCH64EB__) && (defined(__arm)\
      || defined(__arm__) || defined(aarch64_) || defined(__aarch64__))) || defined(KBP_LITTLE_ENDIAN)
#define __EO_32(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X; Y; Z; AA; BB; CC; DD; EE; FF
#define __EO_25(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X; Y
#define __EO_24(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W; X
#define __EO_23(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V; W
#define __EO_22(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U; V
#define __EO_21(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T; U
#define __EO_20(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S; T
#define __EO_19(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S
#define __EO_18(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R
#define __EO_17(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q
#define __EO_16(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P
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
#define __KBP_INPLACE_SWAP_32(x,n)
#define __KBP_SWAP_4BYTES(x,n)
#define __KBP_BYTESWAP_TWO_32B(x) (x)

#ifndef KBP_LITTLE_ENDIAN
#define KBP_LITTLE_ENDIAN
#endif

/** Big Endian */
#elif defined(__sparc) || defined(__sparc__)\
    || defined(__powerpc__) || defined(__ppc__)\
    || defined(__hpux) || defined(__hppa)\
    || defined(__s390__) || defined(__mips)\
    || defined(__mips__) || defined(__AARCH64EB__) || defined(KBP_BIG_ENDIAN)
#define __EO_32(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, BB, CC, DD, EE, FF)FF; EE; DD; CC; BB; AA; Z; Y; X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_25(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y)Y; X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_24(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X)X; W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_23(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W) W; V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_22(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V) V; U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_21(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U) U; T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_20(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T) T; S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_19(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S)S; R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_18(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R)R; Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_17(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q)Q; P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
#define __EO_16(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)P; O; N; M; L; K; J; I; H; G; F; E; D; C; B; A
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

#ifndef KBP_BIG_ENDIAN
#define KBP_BIG_ENDIAN
#endif

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
 *  Swap the bytes in MSB 32bit and in LSB 32bit
 */
#define __KBP_BYTESWAP_TWO_32B(x)\
   ((((x) & 0xFF00000000000000ull) >> 24) |   \
    (((x) & 0x00FF000000000000ull) >> 8)  |   \
    (((x) & 0x0000FF0000000000ull) << 8)  |   \
    (((x) & 0x000000FF00000000ull) << 24) |   \
    (((x) & 0x00000000FF000000ull) >> 24) |   \
    (((x) & 0x0000000000FF0000ull) >> 8)  |   \
    (((x) & 0x000000000000FF00ull) << 8)  |   \
    (((x) & 0x00000000000000FFull) << 24));


/**
 * Definition of byte swap of 32-bit value
 */
#define __KBP_BYTESWAP_32(x)\
   ((((x) & 0xFF000000ul) >> 24) |   \
    (((x) & 0x00FF0000ul) >> 8)  |   \
    (((x) & 0x0000FF00ul) << 8)  |   \
    (((x) & 0x000000FFul) << 24));

/* Swap the bytes in the n th 32-bit word of given structure x */
#define __KBP_INPLACE_SWAP_32(x,n)\
    (((uint32_t *)(&x))[n]) = __KBP_BYTESWAP_32((((uint32_t *)(&x))[n]))

/* Handles unaligned word swaps */
#define __KBP_SWAP_4BYTES(x,n)\
    {uint8_t tmp; tmp = x[n]; x[n] = x[n+3];x[n+3] = tmp; tmp = x[n+1]; x[n+1] = x[n+2];x[n+2] = tmp;}


#endif

/**
 * Portability structure for timers
 */
struct kbp_timeval {
    long tv_sec;                /**< Seconds */
    long tv_ns;                 /**< Nanoseconds */
};

typedef long kbp_time_t;

struct kbp_tm {
    int32_t sec;   /* Seconds */
    int32_t min;   /* Minutes */
    int32_t hour;  /* Hours */
    int32_t mday;  /* Day of the month */
    int32_t month; /* Month */
    int32_t year;  /* Number of years since 1900 */
    int32_t wday;  /* Day of the week */
    int32_t yday;  /* Day in the year */
    int32_t isdst; /* Day Light Saving time */
};


/**
 * Assert with message
 *
 * @param msg the message to print
 * @param file the file name
 * @param line the line number
 */
int32_t kbp_assert_detail(const char *msg, const char *file, int32_t line);

/**
 * Assert with message and this doen't abort the process when the return_error bit is set.
 * And instead it returns the error code.
  *
 * @param msg the message to print
 * @return_error return error when this bit is set
 * @error_code return this error code
 * @param file the file name
 * @param line the line number
 */
int32_t kbp_assert_detail_or_error(const char *msg, uint32_t return_error, uint32_t error_code, const char *file, int32_t line);

/**
 * Empty function for macro use
 */
int32_t kbp_identity(const int32_t b);

#define KBP_CAST_PTR_TO_U32(x) ((uint32_t)(uintptr_t)x)
#define KBP_CAST_U32_TO_PTR(x)    (void*)((uintptr_t)x)


#define kbp_assert(cond, msg) ((void)((cond) || kbp_assert_detail((msg), __FILE__, __LINE__)))
#define kbp_sassert(cond)     ((void)((cond) || kbp_assert_detail((" "), __FILE__, __LINE__)))
#define kbp_assert_(b, m)     (kbp_identity(b) ? 0 : kbp_assert_detail(m, __FILE__, __LINE__)),

#define KBP_ASSERT_OR_ERROR(cond, msg, return_error, error_code)                                           \
    do {                                                                                                   \
        if (!(cond)) {                                                                                     \
            KBP_STRY(kbp_assert_detail_or_error((msg), (return_error), (error_code), __FILE__, __LINE__)); \
        }                                                                                                  \
    } while (0)

/* make #if 0 to enable transport error details */
#if 1
#define  KBP_TX_ERROR_CHECK(dev, status)                                                                        \
         (void)dev;                                                                                             \
         (void)status;
#else
#define  KBP_TX_ERROR_CHECK(dev, status)                                                                        \
    if (dev->main_bc_device)                                                                                    \
        dev = dev->main_bc_device;                                                                              \
    if (dev->main_dev)                                                                                          \
        dev = dev->main_dev;                                                                                    \
    if (dev->fatal_transport_error || dev->check_fatal_dbg_0 || dev->check_fatal_dbg_1)   {                     \
        kbp_printf("\n ____________________________________________________________________________________\n");\
        kbp_printf("\n Transport error !!!  (check0: %d error: %d check1: %d)",                                 \
            dev->check_fatal_dbg_0, dev->fatal_transport_error, dev->check_fatal_dbg_1);                        \
        if (status)                                                                                             \
            kbp_printf("\n Status   :  Reason Code: %d  [ %s ]  ", status, kbp_get_status_string(status));      \
        kbp_printf("\n File     : %s  \n Function : %s  \n LineNo   : %u  ", __FILE__, __FUNCTION__, __LINE__); \
        kbp_printf("\n ____________________________________________________________________________________\n");\
    }
#endif

#ifdef WIN32
#define kbp_concat_identity(a)  a
#define kbp_concat_2(a,b)  kbp_concat_identity(a)kbp_concat_identity(b)
#define kbp_concat_3(a,b,c)    kbp_concat_identity(a)kbp_concat_identity(b)kbp_concat_identity(c)
#else
#define kbp_concat_2(a,b)      a##b
#define kbp_concat_3(a,b,c)    a##b##c
#endif

/**
 * Definition of stdout
 */
#define kbp_stdout   stdout

/**
 * Definition of stderr
 */
#define kbp_stderr   stderr

/**
 * Definition of fopen
 */
#define kbp_fopen    fopen

/**
 * Definition of EOF
 */
#define kbp_eof      (EOF)

/**
 * Implementation of memset.
 */

void *kbp_memset(void *str, int val, uint32_t size);

/**
 * Implementation of memcpy.
 */
void *kbp_memcpy(void *dest, const void *src, uint32_t size);

/**
 * Implementation of memcmp.
 */
int kbp_memcmp(const void *s1, const void *s2, uint32_t size);

/**
 * Implementation of memmove.
 */
void *kbp_memmove(void *dstp, const void *srcp, uint32_t numOfBytes);

/**
 * Implementation of malloc.
 */
void *kbp_sysmalloc(uint32_t size);

/**
 * Implementation of calloc.
 */
void *kbp_syscalloc(uint32_t nmemblk, uint32_t size);

/**
 * Implementation of free.
 */
void kbp_sysfree(void *ptr);

/**
 * Implementation of abort.
 */
void kbp_abort(void);

/**
 * Implementation of sprintf.
 */
int kbp_sprintf(char *buff, const char *fmt,...);

/**
 * Implementation of vsnprintf.
 */
int kbp_vsnprintf(char *buff, uint32_t buffsize, const char *fmt, va_list ap);

/**
 * Implementation of snprintf.
 */
int kbp_snprintf(char *buff, uint32_t buffsize, const char *fmt,...);

/**
 * Implementation of printf.
 */
int kbp_printf(const char *fmt,...);

/**
 * Implementation of fputs
 */
int kbp_fputs(const char *str, FILE *fp);

/**
 * Implementation of vprintf.
 */
int kbp_vprintf(const char *fmt, va_list arg);

/**
 * Implementation of fprintf.
 */
int kbp_fprintf(FILE * fp, const char *fmt, ...);

/**
 * Implementation of fscanf.
 */
int kbp_fscanf(FILE * fp,const char *fmt, ...);

/**
 * Implementation of fseek.
 */
int kbp_fseek(FILE * fp, uint32_t offset ,int whence);

/**
 * Windows implementation of error box.
 */

void kbp_enable_error_box(int32_t enable);

/**
 * Implementation of gettimeofday.
 */
int kbp_gettimeofday(struct kbp_timeval *tv);

/**
 * Implementation of gettimerval.
 */
int kbp_gettimerval(struct kbp_timeval * tv);

/**
 * Implementation of time.
 */
kbp_time_t kbp_time(kbp_time_t *currtime);

/**
 * Implementation of re-entrant version of localtime.
 */
struct kbp_tm *kbp_localtime(kbp_time_t *currtime, struct kbp_tm *timeinfo);

/**
 * Implementation of getenv.
 */
char *kbp_getenv(const char *name);

/**
 * Implementation of srandom.
 */
void kbp_srandom(uint32_t seed);

/**
 * Implementation of random.
 */
int kbp_random(void);

/**
 * Implementation of random_r.
 */
int kbp_random_r(uint32_t *seedp);


/**
 * Returns an array of files that end with the provided
 * file extension (suffix). If suffix is NULL, all files irrespective
 * of suffix are returned. Its the responsibility
 * of the caller to free up the returned array.
 *
 * @param location File or directory to start searching from.
 * @param suffix The file extension or NULL for all files.
 * @param num_found Number of elements in the returned array.
 *
 * @retval Array of file names with full paths, or NULL.
 */

char **kbp_get_files_recursive(const char *location, const char *suffix, uint32_t *num_found);

/**
 * Creates a directory structure if needed, opens the
 * specified file, and returns a file pointer. For example,
 * if /foo/bar/a.txt is passed in, and directories foo/bar
 * do not exist, it will create them.
 */

FILE *kbp_open_file(const char *fname);

/**
 * Portable Unix implementation of strsep() function.
 */

char *kbp_strsep(char **stringp, const char *delim);

/**
 * Implementation of fclose
 */

int kbp_fclose(FILE * fp);

/**
 * Implementation of usleep
 */

void kbp_usleep(uint32_t usecs);


/**
 * Implementation of mmap
 */

void *kbp_mmap(void *addr, uint32_t length, int prot, int flags,
                  int fd, uint64_t offset);

/**
 * Implementation of munmap
 */

int kbp_munmap(void *addr, uint32_t length);

/**
 * Implementation of open
 */

int kbp_open(const char *pathname, int flags, uint32_t mode);

/**
 * Implementation of vfprintf
 */
int kbp_vfprintf(FILE * fp, const char *fmt,va_list ap);


void kbp_flush_cache(uint8_t *base_address, uint32_t size_8);

/**
 *Undefined functions are
 */

#ifdef KBP_UNDEF_FUN
extern int rand_r(unsigned *);
extern unsigned int usleep(unsigned int usecs);
extern int ioctl(int, int, ...);
#endif

/**
 * @}
 */


#ifdef __cplusplus
}
#endif
#endif                          /* __KBP_PORTABLE_H */


