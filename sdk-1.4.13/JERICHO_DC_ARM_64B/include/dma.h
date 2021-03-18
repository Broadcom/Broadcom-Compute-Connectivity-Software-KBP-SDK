/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __DMA_H
#define __DMA_H

 /**
  * @file dma.h
  *
  * Direct Memory Access Database creation and management.
  */

#include <stdint.h>
#include <stdio.h>

#include "errors.h"
#include "device.h"
#include "db.h"

#ifdef __cplusplus
 extern "C" {
#endif

 /**
  * * @addtogroup DMA_API
  * @{
  */

 /**
  * Opaque DMA database handle.
  */

 struct kbp_dma_db;

 /**
  * Creates an DMA database
  *
  * @param device Valid device handle.
  * @param id Database ID. This is a control-plane identifier only.
  * @param capacity Expected maximum capacity for this database.
  * @param width_1 Width of DMA entries in bits, which must be a multiple of eight.
  * @param db Database handle, initialized and returned on success.
  *
  * @returns KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_init(struct kbp_device *device, uint32_t id, uint32_t capacity,
                           uint32_t width_1, struct kbp_dma_db **db);

 /**
  * Destroys the DMA database
  *
  * @param db Valid database handle to destroy.
  *
  * @returns KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_destroy(struct kbp_dma_db *db);

 /**
  * Adds a specific hardware resource to the DMA database
  *
  * @param db Valid database handle.
  * @param resource The resource to be added defined in ::kbp_hw_resource.
  * @param ... Variable resource arguments.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_set_resource(struct kbp_dma_db *db, enum kbp_hw_resource resource, ...);

 /**
  * Retrieves the hardware resources allocated for this database
  *
  * @param db Valid database handle.
  * @param resource The resource to be queried, defined in ::kbp_hw_resource.
  * @param ... Resource arguments. Must be pointers into which the values will be returned.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_get_resource(struct kbp_dma_db *db, enum kbp_hw_resource resource, ...);

 /**
  * Sets properties for the database.
  *
  * @param db Valid database handle.
  * @param property The property to set, defined by ::kbp_db_properties.
  * @param ... Variable arguments to set properties.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_set_property(struct kbp_dma_db *db, enum kbp_db_properties property, ...);

 /**
  * Gets properties for the database.
  *
  * @param db valid database handle
  * @param property The property to get defined by ::kbp_db_properties
  * @param ... variable arguments to get properties into
  *
  * @return KBP_OK on success or an error code
  */

 kbp_status kbp_dma_db_get_property(struct kbp_dma_db *db, enum kbp_db_properties property, ...);

 /**
  * Adds the DMA entry. The value array must point to valid memory of the width of the DMA database.
  *
  * @param db Valid database handle.
  * @param value DMA data content.
  * @param offset Location in the DMA database where entry is to written
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_add_entry(struct kbp_dma_db *db, uint8_t * value, uint32_t offset);

 /**
  * Deletes the DMA entry
  *
  * @param db Valid database handle.
  * @param offset Location in the DMA database of entry to be deleted.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_delete_entry(struct kbp_dma_db *db, uint32_t offset);

 /**
  * Reads a DMA entry
  *
  * @param db Valid database handle.
  * @param offset Location in the DMA database of entry to be read.
  * @param value The value of DMA entry read.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_dma_db_read_entry(struct kbp_dma_db *db, uint32_t offset, uint8_t * value);

 /**
  * @}
  */

 /**
  * @addtogroup ISSU_API
  * @{
  */

 /**
  * Returns the new DMA DB Handle after ISSU operation
  *
  *
  * @param device the KBP device handle
  * @param stale_ptr DB handle before ISSU.
  * @param dbp New DB handle.
  *
  * @retval KBP_OK on success and result structure is populated.
  * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
  */

 kbp_status kbp_dma_db_refresh_handle(struct kbp_device *device, struct kbp_dma_db *stale_ptr, struct kbp_dma_db **dbp);

 /**
  * @}
  */

#ifdef __cplusplus
 }
#endif
#endif /*__DMA_H */

