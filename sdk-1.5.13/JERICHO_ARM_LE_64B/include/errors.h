/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __ERRORS_H
#define __ERRORS_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @file errors.h
 *
 * Errors and fault reporting functions
 *
 */

/**
 * @addtogroup ERRORS_API
 * @{
 */

/**
 * @brief Status and error codes returned by all API functions.
 */

typedef enum kbp_status { /** \def KBP_INC_SEL(name,string)
                              Select between enumeration and error string */
#define KBP_INC_SEL(name,string) name,
#include "error_tbl.def"
#undef KBP_INC_SEL
    KBP_STATUS_LAST_UNUSED
} kbp_status;

/**
 * Function to convert a status code to a string. The returned
 * string should not be overwritten or freed by the caller.
 *
 * @param status Code to be converted.
 *
 * @retval string Verbose description of status code if valid.
 * @retval NULL if invalid status code is passed in.
 *
 * @warning The returned string should not be modified or freed.
 */

const char *kbp_get_status_string(kbp_status status);

/**
 * @brief Convenience macro to wrap function calls and capture error codes and their descriptions.
 *
 * A verbose error is printed when an error occurs.
 */

#define KBP_TRY(A)                                                      \
    do                                                                  \
    {                                                                   \
        kbp_status __tmp_status = A;                                    \
        if (__tmp_status != KBP_OK)                                     \
        {                                                               \
            kbp_printf(#A" failed: %s\n", kbp_get_status_string(__tmp_status)); \
            return __tmp_status;                                        \
        }                                                               \
    }                                                                   \
    while(0)

/**
 * @brief Convenience macro to wrap function calls and capture error codes.
 *
 * This macro is silent; it does not output any verbose messages.
 */

#define KBP_STRY(A)                                                     \
    do                                                                  \
    {                                                                   \
        kbp_status __tmp_status = A;                                    \
        if (__tmp_status != KBP_OK)                                     \
        {                                                               \
            return __tmp_status;                                        \
        }                                                               \
    } while(0)

/**
 * @brief Convenience macro to wrap function calls and capture error codes.
 *
 * This API is expected error code; if error code other than KBP_OK or Expected, return error.
                                    and it does not output any verbose messages.
 */

#define KBP_ETRY(A,E)                                                   \
    do                                                                  \
    {                                                                   \
        kbp_status __tmp_status = A;                                    \
        kbp_status __exp_status = E;                                    \
        if (__tmp_status != KBP_OK && __tmp_status != __exp_status)     \
        {                                                               \
            return __tmp_status;                                        \
        }                                                               \
    } while(0)


/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif                          /* __ERRORS_H */
