/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DEFAULT_ALLOCATOR_H
#define __DEFAULT_ALLOCATOR_H

#include <stdint.h>

#include "allocator.h"
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file default_allocator.h
 *
 * Internal implementation of allocator abstractions with bookkeeping.
 * Additional memory is consumed per allocation for bookkeeping.
 * Relies on standard malloc/free.
 *
 * @addtogroup DEFAULT_ALLOCATOR_API
 * @{
 */

/**
 * Creates a new default allocator that
 * uses operations from stdlib.h and keeps
 * statistics.
 *
 * @param alloc Allocator, initialized and returned on success.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status default_allocator_create(struct kbp_allocator **alloc);

/**
 * Destroys the default allocator. If incorrect
 * number of free calls are made, the memory may
 * leak.
 *
 * @param alloc Valid allocator handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status default_allocator_destroy(struct kbp_allocator *alloc);

/**
 * Allocator statistics, bytes allocated, and
 * number of allocation calls made.
 */

struct default_allocator_stats {
    uint64_t peak_bytes;        /**< Maximum active bytes ever allocated. */
    uint64_t cumulative_bytes;  /**< Total number of bytes allocated. */
    uint64_t nallocs;           /**< Number of malloc/calloc calls. */
    uint64_t nfrees;            /**< Number of free calls. */
};

/**
 * Returns statistics associated with the allocator. These statistics are
 * held internally.
 *
 * @param alloc Valid allocator handle.
 * @param stats Valid pointer to memory to be populated with statistics.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status default_allocator_get_stats(struct kbp_allocator *alloc, struct default_allocator_stats *stats);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif                          /* __DEFAULT_ALLOCATOR_H */
