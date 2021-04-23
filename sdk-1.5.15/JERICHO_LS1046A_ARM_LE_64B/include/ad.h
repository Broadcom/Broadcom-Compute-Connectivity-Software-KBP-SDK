/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __AD_H
#define __AD_H

/**
 * @file ad.h
 *
 * Associated data creation and management.
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
 * * @addtogroup AD_API
 * @{
 */

/**
 * Opaque AD database handle.
 */

struct kbp_ad_db;

/**
 * Opaque AD handle.
 */

struct kbp_ad;

/**
 * Creates an AD database
 *
 * @param device Valid device handle.
 * @param id Database ID. This is a control-plane identifier only.
 * @param capacity Expected maximum capacity for this database. Can be zero, which means unlimited.
 * @param width_1 Width of AD entries in bits, which must be a multiple of eight.
 * @param db Database handle, initialized and returned on success.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_init(struct kbp_device *device, uint32_t id, uint32_t capacity,
                          uint32_t width_1, struct kbp_ad_db **db);

/**
 * Destroys the AD database
 *
 * @param db Valid AD database handle to destroy.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_destroy(struct kbp_ad_db *db);

/**
 * Adds a specific hardware resource to the AD database
 *
 * @param db Valid AD database handle.
 * @param resource The resource to be added defined in ::kbp_hw_resource.
 * @param ... Variable resource arguments.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_set_resource(struct kbp_ad_db *db, enum kbp_hw_resource resource, ...);

/**
 * Retrieves the hardware resources allocated for this database
 *
 * @param db Valid AD database handle.
 * @param resource The resource to be queried, defined in ::kbp_hw_resource.
 * @param ... Resource arguments. Must be pointers into which the values will be returned.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_get_resource(struct kbp_ad_db *db, enum kbp_hw_resource resource, ...);

/**
 * Sets properties for the database.
 *
 * @param db Valid AD database handle.
 * @param property The property to set, defined by ::kbp_db_properties.
 * @param ... Variable arguments to set properties.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_set_property(struct kbp_ad_db *db, enum kbp_db_properties property, ...);

/**
 * Gets properties for the database.
 *
 * @param db valid AD database handle
 * @param property The property to get defined by ::kbp_db_properties
 * @param ... variable arguments to get properties into
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_ad_db_get_property(struct kbp_ad_db *db, enum kbp_db_properties property, ...);

/**
 * Adds the AD entry. The value array must point to valid memory of the width of the AD database.
 *
 * @param db Valid AD database handle.
 * @param value Associated data content.
 * @param ad Associated data handle returned on success. Can be used to associate with ACL, LPM and EM database entries.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_add_entry(struct kbp_ad_db *db, uint8_t * value, struct kbp_ad **ad);

/**
 * Deletes an AD entry. If any database entries continue to point to the
 * AD, the operation will fail.
 *
 * @param db Valid AD database handle.
 * @param ad Associated data handle to delete.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_delete_entry(struct kbp_ad_db *db, struct kbp_ad *ad);

/**
 * Updates an AD entry.
 *
 * @param db Valid AD database handle.
 * @param ad Associated data handle to update.
 * @param value The new AD contents.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_update_entry(struct kbp_ad_db *db, struct kbp_ad *ad, uint8_t * value);

/**
 * Looks up the AD contents for the specified handle.
 *
 * @param db Valid AD database handle.
 * @param ad Associated-data handle.
 * @param value Array into which the AD contents are copied. There must be enough valid memory to contain the AD data.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_get(struct kbp_ad_db *db, struct kbp_ad *ad, uint8_t * value);

/**
 * Pretty-prints the AD entry.
 *
 * @param db Valid AD database handle.
 * @param ad Associated-data handle.
 * @param fp File pointer.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_entry_print(struct kbp_ad_db *db, struct kbp_ad *ad, FILE * fp);

/**
 * Deletes all AD entries in the database. Assumes there are
 * no live references to the AD present
 *
 * @param db Valid AD database handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_delete_all_entries(struct kbp_ad_db *db);


/**
 * Deletes all AD entries in the database which are not being used
 * and there are no live references to those. AD entries created newly
 * and not associated with any entry will also be deleted.
 *
 * @param db Valid AD database handle.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_ad_db_delete_unused_entries(struct kbp_ad_db *db);


/**
 * @}
 */

/**
 * @addtogroup ISSU_API
 * @{
 */

/**
 * Returns the new AD DB Handle after ISSU operation
 *
 *
 * @param device the KBP device handle
 * @param stale_ptr DB handle before ISSU.
 * @param dbp New DB handle.
 *
 * @retval KBP_OK on success and result structure is populated.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */

kbp_status kbp_ad_db_refresh_handle(struct kbp_device *device, struct kbp_ad_db *stale_ptr, struct kbp_ad_db **dbp);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*__AD_H */
