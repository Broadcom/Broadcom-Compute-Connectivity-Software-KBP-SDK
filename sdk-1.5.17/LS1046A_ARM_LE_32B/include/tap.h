/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KBP_TAP_H
#define __KBP_TAP_H

/**
 * @file tap.h
 *
 * TAP database management
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
 * * @addtogroup TAP_API
 * @{
 */

struct kbp_tap_db;

struct kbp_tap_record;

struct kbp_tap_instruction;

struct kbp_tap_db_value;

struct kbp_tap_db_pointer;

struct kbp_tap_db_attribute;


/**
 *   @brief The KBP TAP entry type
 *
 */
enum kbp_tap_entry_type {
    KBP_TAP_ENTRY_TYPE_SINGLE = 0, /**< Single counter entry type */
    KBP_TAP_ENTRY_TYPE_PAIR   = 1, /**< Counter pair entry type */
    KBP_TAP_ENTRY_TYPE_INVALID     /**< Invalid entry type */
};

/**
 * @brief An enumeration to the supported KBP TAP record length
 *
 */
enum kbp_tap_record_length {
    KBP_TAP_RECORD_LENGTH_64 = 0,      /**< default length of KBP TAP record is 64 bits */
    KBP_TAP_RECORD_LENGTH_72 = 1,      /**< KBP TAP record of 72 bits */
    KBP_TAP_RECORD_LENGTH_80 = 2,      /**< KBP TAP record of 80 bits */
    KBP_TAP_RECORD_LENGTH_96 = 3,      /**< KBP TAP record of 96 bits */
};

/**
 * @brief An enumeration to the supported KBP TAP record type.
 *
 */
enum kbp_tap_record_type {
    KBP_TAP_RECORD_TYPE_NULL    = 0,   /**< KBP TAP NULL record */
    KBP_TAP_RECORD_TYPE_RSVD    = 1,   /**< KBP TAP reserved record */
    KBP_TAP_RECORD_TYPE_INGRESS = 2,   /**< KBP TAP ingress record */
    KBP_TAP_RECORD_TYPE_EGRESS  = 3,   /**< KBP TAP egress record */
};

/**
 * @brief An enumeration to the supported KBP TAP instruction type.
 *
 */
enum kbp_tap_instruction_type {
    KBP_TAP_INSTRUCTION_TYPE_INGRESS = 0, /**< KBP TAP ingress instruction */
    KBP_TAP_INSTRUCTION_TYPE_EGRESS  = 1, /**< KBP TAP egress instruction */
    KBP_TAP_INSTRUCTION_TYPE_INVALID      /**< Invalid instruction type */
};

/**
 * @brief Enumeration for the field types of record
 *
 */
enum kbp_tap_record_field_type {
    KBP_TAP_RECORD_FIELD_VALUE,
    KBP_TAP_RECORD_FIELD_POINTER,
    KBP_TAP_RECORD_FIELD_ATTRIBUTE,
    KBP_TAP_RECORD_FIELD_OPCODE,
    KBP_TAP_RECORD_FIELD_OPCODE_EXT,
    KBP_TAP_RECORD_FIELD_HOLE,
    KBP_TAP_RECORD_FIELD_INVALID
};

/**
 * @brief Enumeration for the instruction property
 *
 */
enum kbp_tap_instruction_properties {
    KBP_TAP_INST_PROP_OPCODE_EXT_VALUE, /**< To set the valid opcode extension values */
    KBP_TAP_INST_PROP_REPLICATE,        /**< To replicate instruction on other thread */
    KBP_TAP_INST_PROP_INVALID
};

/**
   * @brief Enumeration for the database property
    *
     */
enum kbp_tap_db_properties {
     KBP_TAP_DB_PROP_RATE_COMPUTE, /**< To enable Rate Computation solution on the database */
     KBP_TAP_DB_PROP_INVALID
};

/**
 * Creates TAP database
 *
 * @param device Valid device handle.
 * @param id Database ID. This is a control-plane identifier only.
 * @param capacity The number of entries managed by this database.
 * @param type Entry type, Single or Pair
 * @param set_size Database entry set size
 * @param tap_dbp Database handle, initialized and returned on success.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_init(struct kbp_device *device, uint32_t id,
                           uint32_t capacity, enum kbp_tap_entry_type type,
                           int32_t set_size, struct kbp_tap_db **tap_dbp);

/**
 * Destroys TAP database. Memory and hardware resources reserved by
 * this database are recovered. All entries associated with this
 * database are invalidated
 *
 * @param tap_db TAP database handle
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_destroy(struct kbp_tap_db *tap_db);

/**
 * Associates a property to the TAP database
 *
 * @param tap_db TAP database handle
 * @param property Specific property for this database
 *
 * @returns KBP_OK on success or an error code otherwise.
 */

kbp_status kbp_tap_db_set_property(struct kbp_tap_db *tap_db, enum kbp_tap_db_properties property, ...);

/**
 * Creates a tap record
 *
 * @param device Valid device handle
 * @param type Record type Ingress OR Egress
 * @param record handle, initialized and returned on success
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_record_init(struct kbp_device *device, enum kbp_tap_record_type type,
                               struct kbp_tap_record **record);

/**
 * Adds a field to the TAP record. Repeated calls to add field
 * help to construct the record.
 *
 * @param record Valid record handle
 * @param name Name of the field
 * @param width_1 Width of the field in bits
 * @param type Type of the field
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_record_add_field(struct kbp_tap_record *record, char *name, uint32_t width_1,
                                    enum kbp_tap_record_field_type type);

/**
 * Creates a new TAP instruction
 *
 * @param device Valid device handle.
 * @param id Nonzero instruction ID. This is a control-plane identifier only
 * @param inst_type Instruction type
 * @param instr Instruction. initialized and returned on success.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_instruction_init(struct kbp_device *device, uint32_t id,
                                    enum kbp_tap_instruction_type inst_type,
                                    struct kbp_tap_instruction **instr);

/**
 * Destroys the TAP instruction,
 *
 * @param instruction Valid instruction handle.
 *
 * @retval KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_instruction_destroy(struct kbp_tap_instruction *instruction);


/**
 * Adds a TAP database to the TAP instruction
 *
 * @param inst Valid instruction handle
 * @param db Valid TAP database handle
 * @param pointer_min Minimum pointer value
 * @param pointer_max Maximum pointer value
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_instruction_add_db(struct kbp_tap_instruction *inst, struct kbp_tap_db *db,
                                      uint32_t pointer_min, uint32_t pointer_max);

/**
 * Associates record to the TAP instruction
 *
 * @param inst TAP instruction handle
 * @param record TAP record
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_instruction_set_record(struct kbp_tap_instruction *inst, struct kbp_tap_record *record);

/**
 * Installs the KBP TAP instruction to the device. The SLTR
 * is active from this point for data-plane operations
 *
 * @param instruction Valid TAP instruction handle
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_instruction_install(struct kbp_tap_instruction *instruction);

/**
 * Creates a new TAP db value (byte_count)
 *
 * @param db Valid TAP database handle.
 * @param value handle, initialized and returned on success.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_value_init(struct kbp_tap_db *db, struct kbp_tap_db_value **value);

/**
 * Sets name and width of value field of the TAP db
 *
 * @param value Valid TAP db value handle
 * @param name Field name
 * @param width_1 Field width in bits
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_value_set_field(struct kbp_tap_db_value *value, char *name,  uint32_t width_1);

/**
 * Creates a new TAP db pointer
 *
 * @param db Valid TAP database handle.
 * @param pointer handle, initialized and returned on success.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_pointer_init(struct kbp_tap_db *db, struct kbp_tap_db_pointer **pointer);

/**
 * Adds a field to the TAP db pointer
 *
 * @param pointer Valid TAP db pointer handle
 * @param name Field name
 * @param width_1 Field width in bits
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_pointer_add_field(struct kbp_tap_db_pointer *pointer, char *name,  uint32_t width_1);

/**
 * Associates a pointer to the TAP database
 *
 * @param db Valid TAP database handle
 * @param pointer Valid TAP db pointer handle
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_set_pointer(struct kbp_tap_db *db, struct kbp_tap_db_pointer *pointer);

/**
 * Creates a new TAP attribute
 *
 * @param db Valid TAP database handle.
 * @param attr pointer handle, Initialized and returned on success.
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_attribute_init(struct kbp_tap_db *db, struct kbp_tap_db_attribute **attr);

/**
 * Adds a field to the TAP attribute
 *
 * @param attr Valid TAP attribute handle
 * @param name Field name
 * @param width_1 Field width in bits
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_attribute_add_field(struct kbp_tap_db_attribute *attr, char *name,  uint32_t width_1);

/**
 * Associates an attribute to the TAP database
 *
 * @param db Valid TAP database handle
 * @param attr Valid TAP attribute handle
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_set_attribute(struct kbp_tap_db *db, struct kbp_tap_db_attribute *attr);

/**
 * Associates a property to the TAP instruction
 *
 * @param instruction Valid TAP instruction handle
 * @param property Specific property for this instruction
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_instruction_set_property(struct kbp_tap_instruction *instruction,
                                            enum kbp_tap_instruction_properties property, ...);

/**
 * API to map attribute values to entries in the counter entry set
 *
 * @param db Valid TAP database handle
 * @param attr_value The attribute value to map
 * @param entry_in_set The attribute value is mapped to this entry in the counter entry set
 *
 * @returns KBP_OK on success or an error code otherwise.
 */
kbp_status kbp_tap_db_map_attr_value_to_entry(struct kbp_tap_db *db, int32_t attr_value,
                                              int32_t entry_in_set);

/**
 * Application should call this API to initiate TAP entry reads from the device.
 * This is a non-blocking call and function returns immediately after launching
 * a counter read command to the device.
 *
 * @param db Valid TAP database handle
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_db_read_initiate(struct kbp_tap_db *db);

/**
 * Application should call this API to scrub the TAP entry DMA buffer, to
 * refresh Entry Master copy in the host memory. This API must be invoked
 * in a loop until is_complete becomes 1 which means all entries are read back
 * into the host memory.
 *
 * @param db Valid TAP database handle
 * @param is_complete Set to 1 if counter read is complete
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_db_is_read_complete(struct kbp_tap_db *db, int32_t *is_complete);

/**
 * Returns 64b TAP entry value given the entry number and counter offset
 *
 * @param db Valid TAP database handle
 * @param entry_num Entry to read (row number)
 * @param counter_offset Counter offset of the entry to read
 * @param value 64b entry value
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_db_entry_get_value(struct kbp_tap_db *db, uint32_t entry_num,
                                      uint32_t counter_offset, uint64_t *value);

/**
 * Returns 64b-64b TAP entry pair value given the entry number and counter offset
 *
 * @param db Valid TAP database handle
 * @param entry_num Entry to read (row number)
 * @param counter_offset Counter offset of the entry to read
 * @param packet_count 64b packet count value
 * @param byte_count 64b byte count value
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_db_entry_pair_get_value(struct kbp_tap_db *db, uint32_t entry_num,
                                           uint32_t counter_offset, uint64_t *packet_count,
                                           uint64_t *byte_count);

/**
 * @}
 */

/**
 * @addtogroup ISSU_API
 * @{
 */

/**
 * Returns the new TAP DB handle after ISSU operation. This API can be called
 * after device lock also.
 *
 * @param device Valid device handle
 * @param stale_ptr DB handle before ISSU
 * @param dpp New DB handle
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_db_refresh_handle(struct kbp_device *device, struct kbp_tap_db *stale_ptr,
                                     struct kbp_tap_db **dpp);

/**
 * Returns the new TAP instruction handle after ISSU operation. This API can be called
 * after device lock also.
 *
 * @param device Valid device handle
 * @param stale_ptr Instruction handle before ISSU
 * @param inst New instruction handle
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_instruction_refresh_handle(struct kbp_device *device,
                                              struct kbp_tap_instruction *stale_ptr,
                                              struct kbp_tap_instruction **inst);


/**
 * Prints stats port related registers data
 *
 * @param device Valid device handle
 * @param port_id stats port number
 * @param fp Valid file pointer to dump the contents to
 *
 * @returns KBP_OK on success or an error code otherwise
 */
kbp_status kbp_tap_dump_port_regs(struct kbp_device *device, int32_t port_id, FILE *fp);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*__KBP_TAP_H */

