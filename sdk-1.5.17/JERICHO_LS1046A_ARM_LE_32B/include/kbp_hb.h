/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_HB_H
#define __KBP_HB_H

 /**
  * @file kbp_hb.h
  *
  * Hit Bit implementation
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
  * * @addtogroup HB_API
  * @{
  */

 /**
  * Opaque Hit Bit database handle.
  */

struct kbp_hb_db;

 /**
  * Opaque HB handle.
  */

struct kbp_hb;

 /**
  * Creates a hit bit database
  *
  * @param device Valid device handle.
  * @param id Database ID. This is a control-plane identifier only.
  * @param capacity The number of hit bits managed by this database. Zero means dynamic capacity.
           Dynamic capacity is not supported at this time.
  * @param hb_dbp Database handle, initialized and returned on success.
  *
  * @returns KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_init(struct kbp_device *device, uint32_t id, uint32_t capacity,
                          struct kbp_hb_db **hb_dbp);

 /**
  * Destroys the hit bit database.
  *
  * @param hb_db Valid HB database handle to destroy.
  *
  * @returns KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_destroy(struct kbp_hb_db *hb_db);

 /**
  * Sets properties for the hit bit database.
  *
  * @param hb_db Valid HB database handle.
  * @param property The property to set, defined by ::kbp_db_properties.
  * @param ... Variable arguments to set properties.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_set_property(struct kbp_hb_db *hb_db, enum kbp_db_properties property, ...);

 /**
  * Gets properties for the hit bit database.
  *
  * @param hb_db Valid HB database handle
  * @param property The property to get defined by ::kbp_db_properties
  * @param ... Variable arguments to get properties into
  *
  * @return KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_get_property(struct kbp_hb_db *hb_db, enum kbp_db_properties property, ...);

 /**
  * Creates a hit bit entry.
  *
  * @param hb_db Valid HB database handle.
  * @param hb Hit bit handle returned on success. Can be used to associate with LPM/ACL database entries.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_add_entry(struct kbp_hb_db *hb_db, struct kbp_hb **hb);

 /**
  * Deletes given hit bit entry. If any LPM/ACL database entries continue to point to this
  * hit bit entry, the operation will fail.
  *
  * @param hb_db Valid HB database handle.
  * @param hb Hit bit handle to delete.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_delete_entry(struct kbp_hb_db *hb_db, struct kbp_hb *hb);

 /**
  * Deletes all hit bit entries in the database. Assumes there are
  * no live references to the hit bits present.
  *
  * @param hb_db Valid HB database handle.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

kbp_status kbp_hb_db_delete_all_entries(struct kbp_hb_db *hb_db);

 /**
   * Deletes unused hit bit entries in the database.
   *
   * @param hb_db Valid HB database handle.
   *
   * @return KBP_OK on success or an error code otherwise.
   */
kbp_status kbp_hb_db_delete_unused_entries(struct kbp_hb_db *hb_db);

 /**
  * Performs a timer tick on the hit bit database. The timer operations
  * allow software to collect the hit bit information for all the
  * entries active in the LPM/ACL database. No entries are aged or impacted,
  * the timer is used as a signal to count unreached entries for
  * aging subsequently.
  *
  * @param hb_db Valid Hit bit database handle
  *
  * @return KBP_OK on success or an error code
  */
kbp_status kbp_hb_db_timer(struct kbp_hb_db *hb_db);


/**
  * Returns the count of entries that are aged based on the age count specified.
  * The actual number of entries returned is filled in num_entries.
  *
  * @param hb_db Valid hit bit database handle
  * @param num_entries Returns the number of entries that are filled
  *
  * @return KBP_OK on success or an error code
  */

kbp_status kbp_db_get_aged_entries_count(struct kbp_hb_db *hb_db, uint32_t *num_entries);

/**
  * Returns the list of entries that are aged based on the age count specified.
  * The API fills the caller provided entry buffer with aged entries up to a
  * max of buf_size. The actual number of entries returned is filled in num_entries.
  *
  * @param hb_db Valid hit bit database handle
  * @param buf_size Size of the entry handle buffer provided
  * @param num_entries Returns the number of entries that are filled
  * @param entries Buffer to fill the aged entry handles
  *
  * @return KBP_OK on success or an error code
  */

kbp_status kbp_db_get_aged_entries(struct kbp_hb_db *hb_db, uint32_t buf_size, uint32_t *num_entries, struct kbp_entry **entries);


/**
 * Returns the new hit bit database handle after ISSU operation.
 *
 *
 * @param device Valid KBP device handle
 * @param stale_ptr Hit bit database handle before ISSU
 * @param dbp New hit bit database handle after ISSU
 *
 * @retval KBP_OK On success and hit bit database handle is populated.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */
kbp_status kbp_hb_db_refresh_handle(struct kbp_device *device, struct kbp_hb_db *stale_ptr, struct kbp_hb_db **dbp);



/**
 * @brief Opaque aged entry iterator handle.
 */

struct kbp_aged_entry_iter;

/**
 * Creates an iterator to iterate over all aged entries in the database.
 * Currently entries cannot be deleted when iterating over them.
 *
 * @param hb_db Valid hit bit database handle.
 * @param iter Iterator initialized and returned on success.
 *
 * @retval KBP_OK On success.
 * @retval KBP_OUT_OF_MEMORY If out of memory.
 */

kbp_status kbp_hb_db_aged_entry_iter_init(struct kbp_hb_db *hb_db, struct kbp_aged_entry_iter **iter);

/**
 * Gets the next aged entry in the database, or NULL if no more aged entries present.
 *
 * @param hb_db Valid hit bit database handle.
 * @param iter Valid initialized iterator.
 * @param entry A non-NULL valid entry handle returned on success, or NULL after the last entry.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_hb_db_aged_entry_iter_next(struct kbp_hb_db *hb_db, struct kbp_aged_entry_iter *iter, struct kbp_entry **entry);

/**
 * Reclaims the iterator resources.
 *
 * @param hb_db Valid hit bit database handle.
 * @param iter Valid initialized iterator.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_db_aged_entry_iter_destroy(struct kbp_hb_db *hb_db, struct kbp_aged_entry_iter *iter);


/**
 * Gets the idle count for the hit bit
 *
 * @param hb_db Valid hit bit database handle.
 * @param hb Hit bit entry for which we need the idle count.
 * @param idle_count The idle count for the entry is returned here.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_entry_get_idle_count(struct kbp_hb_db *hb_db, struct kbp_hb *hb, uint32_t *idle_count);

/**
 * Sets the idle count for the hit bit
 *
 * @param hb_db Valid hit bit database handle.
 * @param hb Hit bit entry for which we need to set the idle count.
 * @param idle_count The idle count to be set for the hit bit entry.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_entry_set_idle_count(struct kbp_hb_db *hb_db, struct kbp_hb *hb, uint32_t idle_count);


/**
 * Gets the bit value for the hit bit.
 *
 * @param hb_db Valid hit bit database handle.
 * @param hb_handle Hit bit entry for which we need the bit value.
 * @param bit_value Value of the hit bit for the entry is returned here.
 * @param clear_on_read If 1, the hit bit will be cleared in hardware.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_entry_get_bit_value(struct kbp_hb_db *hb_db, struct kbp_hb *hb_handle, uint32_t *bit_value, uint8_t clear_on_read);

/**
 * Application should call this API to initiate Hitbit bank reads from the device.
 * This is a non-blocking call and function returns immediately after launching
 * a Hitbit bank read command to the device.
 *
 * @param hb_db Valid hitbit database handle
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_hb_db_read_initiate(struct kbp_hb_db *hb_db);

/**
 * Application should call this API to know if the Hitbit bank read operation initiated
 * using kbp_counter_read_initiate API invocation is complete or not.
 * This API must be invoked in a loop until is_complete becomes 1 which means all
 * Hitbit banks are read back
 *
 * @param hb_db Valid HB database handle
 * @param is_complete Set to 1 if counter read is complete
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_hb_db_is_read_complete(struct kbp_hb_db *hb_db, int32_t *is_complete);

/**
 * @}
 */


#ifdef __cplusplus
 }
#endif
#endif /*__KBP_HB_H */

