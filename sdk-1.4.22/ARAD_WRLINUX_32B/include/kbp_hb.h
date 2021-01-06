/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
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
  * Creates an Hit Bit database
  *
  * @param device Valid device handle.
  * @param id Database ID. This is a control-plane identifier only.
  * @param capacity The number of hit bits managed by this database. Zero means dynamic capacity.
           Dynamic capacity is not supported at this time
  * @param hb_dbp Database handle, initialized and returned on success.
  *
  * @returns KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_hb_db_init(struct kbp_device *device, uint32_t id, uint32_t capacity,
                           struct kbp_hb_db **hb_dbp);

 /**
  * Destroys the Hit Bit database
  *
  * @param hb_db Valid database handle to destroy.
  *
  * @returns KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_hb_db_destroy(struct kbp_hb_db *hb_db);

 /**
  * Sets properties for the database.
  *
  * @param hb_db Valid database handle.
  * @param property The property to set, defined by ::kbp_db_properties.
  * @param ... Variable arguments to set properties.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_hb_db_set_property(struct kbp_hb_db *hb_db, enum kbp_db_properties property, ...);

 /**
  * Gets properties for the database.
  *
  * @param hb_db valid database handle
  * @param property The property to get defined by ::kbp_db_properties
  * @param ... variable arguments to get properties into
  *
  * @return KBP_OK on success or an error code
  */

 kbp_status kbp_hb_db_get_property(struct kbp_hb_db *hb_db, enum kbp_db_properties property, ...);

 /**
  * Creates the hit bit entry.
  *
  * @param hb_db Valid database handle.
  * @param hb Hit Bit handle returned on success. Can be used to associate LPM database entries.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_hb_db_add_entry(struct kbp_hb_db *hb_db, struct kbp_hb **hb);

 /**
  * Deletes the Hit Bit entry. If any database entries continue to point to the
  * Hit Bit, the operation will fail.
  *
  * @param hb_db Valid database handle.
  * @param hb Hit Bit handle to delete.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_hb_db_delete_entry(struct kbp_hb_db *hb_db, struct kbp_hb *hb);

 /**
  * Deletes all Hit Bit entries in the database. Assumes there are
  * no live references to the Hit Bits present
  *
  * @param hb_db Valid database handle.
  *
  * @return KBP_OK on success or an error code otherwise.
  */

 kbp_status kbp_hb_db_delete_all_entries(struct kbp_hb_db *hb_db);

 /**
   * Deletes the unused Hit Bit entries in the database.
   *
   * @param hb_db Valid database handle.
   *
   * @return KBP_OK on success or an error code otherwise.
   */
 kbp_status kbp_hb_db_delete_unused_entries(struct kbp_hb_db *hb_db);

 /**
  * Performs a timer tick on the Hit Bit database. The timer operations
  * allows software to collect the Hit Bit information for all the
  * entries active in the database. No entries are aged or impacted,
  * the timer is used as a signal to count unreached entries for
  * aging subsequently.
  *
  * @param hb_db valid Hit bit database handle
  *
  * @return KBP_OK on success or an error code
  */
 kbp_status kbp_hb_db_timer(struct kbp_hb_db *hb_db);


/**
  * Returns the list of entries that are aged based on the age count specified.
  * The API fills the provided pre-allocated entry buffer with aged entries upto a
  * max of buf_size. The actual number of entries returned is filled in num_entries.
  *
  * @param hb_db valid Hit bit database handle
  * @param buf_size size of the entry handle buffer provided
  * @param num_entries returns the number of entries that are filled
  * @param entries Buffer to fill the aged entry handles
  *
  * @return KBP_OK on success or an error code
  */

kbp_status kbp_db_get_aged_entries (struct kbp_hb_db *hb_db, uint32_t buf_size, uint32_t *num_entries,
                                    struct kbp_entry **entries);


/**
 * Returns the new DB Handle after ISSU operation
 *
 *
 * @param device the KBP device handle
 * @param stale_ptr DB handle before ISSU.
 * @param dbp New DB handle.
 *
 * @retval KBP_OK on success and result structure is populated.
 * @retval KBP_INVALID_ARGUMENT for invalid or null parameters.
 */
kbp_status kbp_hb_db_refresh_handle(struct kbp_device *device, struct kbp_hb_db *stale_ptr, struct kbp_hb_db **dbp);



/**
 * @brief Opaque entry iterator handle.
 */

struct kbp_aged_entry_iter;

/**
 * Creates an iterator to iterate over all aged entries in the database.
 * Currently entries cannot be deleted when iterating over them
 *
 * @param db Valid hit bit database handle.
 * @param iter Iterator initialized and returned on success.
 *
 * @retval KBP_OK on success.
 * @retval KBP_OUT_OF_MEMORY if out of memory.
 */

kbp_status kbp_hb_db_aged_entry_iter_init(struct kbp_hb_db *hb_db, struct kbp_aged_entry_iter **iter);

/**
 * Gets the next aged entry in the database, or NULL if the last entry.
 *
 * @param db Valid hit bit database handle.
 * @param iter Valid initialized iterator.
 * @param entry A non-NULL valid entry handle returned on success, or NULL after the last entry.
 *
 * @return KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_hb_db_aged_entry_iter_next(struct kbp_hb_db *hb_db, struct kbp_aged_entry_iter *iter, struct kbp_entry **entry);

/**
 * Reclaims the iterator resources.
 *
 * @param db Valid hit bit database handle.
 * @param iter Valid initialized iterator.
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_db_aged_entry_iter_destroy(struct kbp_hb_db *hb_db, struct kbp_aged_entry_iter *iter);


/**
 * Gets the idle count for the hit bit
 *
 * @param db Valid hit bit database handle.
 * @param hb hit bit entry for which we need the idle count
 * @param idle_count the idle count for the entry is returned here
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_entry_get_idle_count(struct kbp_hb_db *hb_db, struct kbp_hb *hb, uint32_t *idle_count);

/**
 * Sets the idle count for the hit bit
 *
 * @param db Valid hit bit database handle.
 * @param hb hit bit entry for which we need to set the idle count
 * @param idle_count the idle count which should be set
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_entry_set_idle_count(struct kbp_hb_db *hb_db, struct kbp_hb *hb, uint32_t idle_count);


/**
 * Gets the bit value for the hit bit
 *
 * @param db Valid hit bit database handle.
 * @param hb hit bit entry for which we need the bit value
 * @param bit value the bit value for the entry is returned here
 * @param clear_on_read if clear_on_read is 1, then the hit bit will be cleared in hardware
 *
 * @return KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_hb_entry_get_bit_value(struct kbp_hb_db *hb_db, struct kbp_hb *hb_handle, uint32_t *bit_value, uint8_t clear_on_read);



/**
 * @}
 */


#ifdef __cplusplus
 }
#endif
#endif /*__KBP_HB_H */

