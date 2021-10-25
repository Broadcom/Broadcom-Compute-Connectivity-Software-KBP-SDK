/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2021 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __KEY_H
#define __KEY_H

/**
 * @file key.h
 *
 * This module helps define the key layout for databases and instructions.
 * This forms the basis for extraction of subkeys from master keys specified
 * as part of instructions. This allows the control-plane API
 * to program the key-processing units (KPUS) in hardware.
 */

#include <stdint.h>

#include "errors.h"
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup KEY_API
 * @{
 */

/**
 * Opaque key handle
 */

struct kbp_key;

/**
 * The type of the key field. This helps
 * the control plane identify the type of a
 * field. This information is mainly used for
 * programming the KPUs and effective range
 * handling in hardware.
 */

enum kbp_key_field_type {
    KBP_KEY_FIELD_TERNARY,/**< Arbitrary data/mask field with don't cares. */
    KBP_KEY_FIELD_PREFIX, /**< An IPv4 or IPv6 address prefix. */
    KBP_KEY_FIELD_EM,     /**< Exact-match field that does not have don't cares (for example, Table ID). */
    KBP_KEY_FIELD_RANGE,  /**< 16-bit range field that can be compared as >= or <= (for example, ports). */
    KBP_KEY_FIELD_TABLE_ID, /**< Equivalent to exact match, identifies the table identifier
                               tuple when the database is a collection of multiple tables. */
    KBP_KEY_FIELD_HOLE,   /**< Arbitrary number of bytes in the key, which are zero-filled.
                             It is assumed the entry in DBA will not compare this portion of the key.
                             This can be used to express BMR functionality */
    /* This should be the last entry */
    KBP_KEY_FIELD_DUMMY_FILL, /**< Ignores the field in the key specified for instructions only */
    KBP_KEY_FIELD_INVALID
};

/**
 * Creates a new key, which will be used to define the layout of entries.
 *
 * @param device Valid KBP device handle.
 * @param key The initialized key, returned on success.
 *
 * @retval KBP_OUT_OF_MEMORY when the key cannot be allocated.
 * @retval KBP_INVALID_ARGUMENT if the arguments are NULL or invalid.
 * @retval KBP_OK on success.
 */

kbp_status kbp_key_init(struct kbp_device *device, struct kbp_key **key);

/**
 * Adds a field to the key. Repeated calls to add field
 * help to construct the key. The field names provided are
 * not interpreted in any way. However,  to program the KPU correctly, the field names
 * in the databases must match the field names in the instruction
 * key. The field width must be a multiple of eight bits.
 *
 * @param key Valid key handle.
 * @param name Field name.
 * @param width_1 Width of the field in bits. Must be multiple of eight bits.
 * @param type The type of the field defined by ::kbp_key_field_type.
 *
 * @retval KBP_OUT_OF_MEMORY when the key field cannot be allocated.
 * @retval KBP_INVALID_ARGUMENT if the arguments are NULL or invalid.
 * @retval KBP_OK on success.
 */

kbp_status kbp_key_add_field(struct kbp_key *key, char *name, uint32_t width_1, enum kbp_key_field_type type);

/**
 * This API allows user to add overlay key field on the master key.
 * Repeated calls to this API allow to specify multiple overlay key fields.
 * The field names provided are not interpreted in any way. However, to program the KPU
 * correctly, the field names in the databases must match the field names in the instruction key.
 *
 * @param master_key Valid master key handle.
 * @param name Field name.
 * @param width_1 Width of the field in bits. Must be multiple of eight bits.
 * @param type The type of the field defined by ::kbp_key_field_type.
 * @param offset_1 Offset of the field in master key in bits. Must be multiple of eight bits.
 *
 * @retval KBP_OUT_OF_MEMORY when the key field cannot be allocated.
 * @retval KBP_INVALID_ARGUMENT if the arguments are NULL or invalid.
 * @retval KBP_OK on success.
 */
kbp_status kbp_key_overlay_field(struct kbp_key *master_key, char *name, uint32_t width_1, enum kbp_key_field_type type, uint32_t offset_1);




/**
 * This API allows user to specify fields as critical.
 * This is an optional API.
 * Fields that are exected to have least amount of dontcares in the entries can be marked as critical fields.
 * This information helps the SDK to optimize the entry storage 
 * This API can be called multiple times for the same key with different fields. The sdk uses the fields in the same order that they are set.
 * for example if this api is used to set "field5" as critical followed by "field3" as critical, then the SDK uses field5 followed by field3
 * 
 * @param key Valid key handle.
 * @param name Field name.
 * 
 * @retval KBP_INVALID_ARGUMENT if the arguments are NULL or invalid.
 * @retval KBP_OK on success.
 */
kbp_status kbp_key_set_critical_field(struct kbp_key *key, char *name);



/**
 * Verifies that the database_key can be derived from the specified master key.
 *
 * @param master_key Valid key handle to the master key.
 * @param db_key Valid key handle to the database key that specifies the layout records.
 * @param error_field Pointer to the name of the field (if any) that causes an error. The memory
 *                    returned must not be freed. Can be NULL if user is not interested in the error field.
 *
 * @retval KBP_OK if the database key can be derived from the master key.
 * @retval KBP_KEY_FIELD_MISSING if a field specified in the database key is missing from the master key.
 * @retval KBP_KEY_GRAN_ERROR if the database key can be derived from the master key only from byte boundaries.
 * @retval KBP_INVALID_ARGUMENT if the arguments are NULL or invalid.
 */

kbp_status kbp_key_verify(struct kbp_key *master_key, struct kbp_key *db_key, char **error_field);

/**
 * Pretty-print the key information.
 *
 * @param key Valid key handle.
 * @param fp Pointer to the file where the contents are to be dumped.
 *
 * @retval KBP_INVALID_ARGUMENT if the arguments are NULL or invalid.
 * @retval KBP_OK on success.
 */

kbp_status kbp_key_print(struct kbp_key *key, FILE * fp);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*__KEY_H */
