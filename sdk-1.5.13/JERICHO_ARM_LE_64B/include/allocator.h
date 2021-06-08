/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @file allocator.h
 *
 * Allocator definition for KBP SDK and fast free-pool-based memory management of structures.
 *
 * @addtogroup ALLOCATOR_API
 * @{
 */

/**
 * @brief Allocator functions provided by user, used by the whole SDK for allocation.
 */

struct kbp_allocator {
    void *cookie;                                    /**< Opaque handle passed into all allocation callback
                                                        functions. Set by user and not used in any way by
                                                        the SDK code. */
    void *(*xmalloc) (void *cookie, uint32_t size);  /**< Malloc callback, the memory may not be zero-filled.
                                                        Returns NULL on error. */
    void *(*xcalloc) (void *cookie, uint32_t nelements, uint32_t size);  /**< calloc callback. Memory should
                                                                            be zero-filled. Returns NULL on error */
    void (*xfree) (void *cookie, void *ptr);         /**< Free callback. */
};

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif                          /* __ALLOCATOR_H */
