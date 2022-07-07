/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#include "kbp_portable.h"
#include "default_allocator.h"


struct default_allocator_handle {
    struct default_allocator_stats stats;
    uint64_t nbytes; /* active bytes to compute peak usage */
};

struct default_allocator_header {
    uint64_t nbytes;
};

static void *default_malloc(void *cookie, uint32_t size)
{
    struct default_allocator_header *hdr = NULL;

    if (size == 0)
        kbp_assert(0, "malloc of size zero is invalid");

    hdr = kbp_sysmalloc(size + sizeof(struct default_allocator_header));
    if (hdr) {
        struct default_allocator_handle *handle = (struct default_allocator_handle *) cookie;
        uint64_t num_bytes;

        handle->stats.nallocs++;
        handle->stats.cumulative_bytes += size;
        num_bytes = (uint64_t) handle->nbytes + size;
        if (num_bytes > handle->stats.peak_bytes)
            handle->stats.peak_bytes = num_bytes;
        hdr->nbytes = size;
        handle->nbytes = num_bytes;
        return hdr + 1;
    }
    return NULL;
}

static void *default_calloc(void *cookie, uint32_t nelem, uint32_t size)
{
    uint32_t tot_size = nelem * size;
    struct default_allocator_header *hdr = NULL;

    if (tot_size == 0)
        kbp_assert(0, "calloc of size zero is invalid");

    hdr = kbp_sysmalloc(tot_size + sizeof(struct default_allocator_header));
    if (hdr) {
        struct default_allocator_handle *handle = (struct default_allocator_handle *) cookie;
        uint64_t num_bytes;

        kbp_memset(hdr, 0, tot_size + sizeof(struct default_allocator_header));
        handle->stats.nallocs++;
        handle->stats.cumulative_bytes += tot_size;
        num_bytes = handle->nbytes + tot_size;
        if (num_bytes > handle->stats.peak_bytes)
            handle->stats.peak_bytes = num_bytes;
        hdr->nbytes = tot_size;
        handle->nbytes = num_bytes;
        return hdr + 1;
    }
    return NULL;
}

static void default_free(void *cookie, void *ptr)
{
    if (ptr) {
        struct default_allocator_handle *handle = (struct default_allocator_handle *) cookie;
        struct default_allocator_header *hdr = (struct default_allocator_header *) ((uint8_t *) ptr - sizeof(struct default_allocator_header));

        kbp_sassert(handle->nbytes >= hdr->nbytes);
        handle->nbytes -= hdr->nbytes;
        handle->stats.nfrees++;
        kbp_sysfree(hdr);
    }
}

kbp_status default_allocator_create(struct kbp_allocator **alloc)
{
    struct kbp_allocator *ret;
    struct default_allocator_handle *handle;

    if (!alloc)
        return KBP_INVALID_ARGUMENT;

    ret = kbp_sysmalloc(sizeof(*ret));
    handle = kbp_syscalloc(1, sizeof(*handle));

    if (!ret || !handle) {
        if (ret)
            kbp_sysfree(ret);
        if (handle)
            kbp_sysfree(handle);

        return KBP_OUT_OF_MEMORY;
    }

    ret->cookie = handle;
    ret->xmalloc = default_malloc;
    handle->nbytes = 0;
    handle->stats.nallocs = 0;
    handle->stats.nfrees = 0;
    handle->stats.cumulative_bytes = 0;
    handle->stats.peak_bytes = 0;
    ret->xfree = default_free;
    ret->xcalloc = default_calloc;

    *alloc = ret;
    return KBP_OK;
}

kbp_status default_allocator_destroy(struct kbp_allocator * alloc)
{
    if (!alloc)
        return KBP_INVALID_ARGUMENT;

    kbp_sysfree(alloc->cookie);
    kbp_sysfree(alloc);
    return KBP_OK;
}

kbp_status default_allocator_get_stats(struct kbp_allocator *alloc, struct default_allocator_stats *stats)
{
    struct default_allocator_handle *handle;

    if (!alloc || !stats)
        return KBP_INVALID_ARGUMENT;

    handle = (struct default_allocator_handle *) alloc->cookie;
    kbp_memcpy(stats, &handle->stats, sizeof(*stats));
    return KBP_OK;
}
