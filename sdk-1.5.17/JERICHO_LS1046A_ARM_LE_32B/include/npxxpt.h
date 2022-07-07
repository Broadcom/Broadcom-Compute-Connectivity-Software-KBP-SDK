/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2022 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#ifndef __NPXXPT_H
#define __NPXXPT_H

#include <stdint.h>

#include "device.h"
#include "errors.h"
#include "db.h"
#include "xpt_op.h"
#include "xpt_12k.h"




#ifdef HAVE_EZCHIP_HW
#include "EZtype.h"
#include "EZrc.h"
#ifdef NPX_NPS
  #include "EZapiTCAM.h"
  #define EZapi_ExtCommandParams EZapiTCAM_ExtTCAMCommandParams
  /* -- Backward Compatibility  */
  /*
   #define EZapiPrm_ExtKBPCommandParams EZapi_ExtCommandParams
   #define EZapiPrm_ExtTCAMCommandParams EZapi_ExtCommandParams
   */
#else
  #include "EZapiPrm.h"
  #define EZapi_ExtCommandParams EZapiPrm_ExtTCAMCommandParams
#endif
#endif




#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_EZCHIP_HW
/*
 * On real h/w system, pick up from driver header files
 */
typedef uint32_t EZstatus;
typedef uint32_t EZui32;
typedef  uint8_t EZuc8;
typedef  int32_t EZbool;

#ifdef NPX_NPS

#define  EZapiTCAM_ConfigCmd_ExtTCAMCommand                 (1002)
#define  EZapiTCAM_EXT_TCAM_HOST_CONTEXTS_BUFFER            (1024)

typedef uint32_t EZapiCP_Version;

typedef struct EZapiTCAM_ExtKBPCommandParams_t {
    EZapiCP_Version eVersion;
    EZui32 uiSide;
    EZui32 uiOpcode;
    EZui32 uiContext;
    EZui32 uiRequestDataSize;
    EZuc8 *pucRequestData;
    EZui32 uiResponseDataSize;
    EZuc8 *pucResponseData;
    EZui32 uiResponseErrorMask;
    EZui32 uiResponseOpcode;
    EZui32 uiResponseContext;
    EZbool bDebug;
} EZapiTCAM_ExtKBPCommandParams;

#define EZapiTCAM_ExtTCAMCommandParams EZapiTCAM_ExtKBPCommandParams
#define EZapi_ExtCommandParams EZapiTCAM_ExtKBPCommandParams
  /* -- Backward Compatibility  -- */
  /*
   #define EZapiPrm_ExtKBPCommandParams EZapi_ExtCommandParams
   #define EZapiPrm_ExtTCAMCommandParams EZapi_ExtCommandParams
   */
#else

typedef uint32_t EZapiDriver_Version;
typedef struct EZapiPrm_ExtKBPCommandParams_t {
    EZapiDriver_Version eVersion;
    EZui32 uiOpcode;
    EZui32 uiContext;
    EZui32 uiRequestDataSize;
    EZuc8 *pucRequestData;
    EZui32 uiResponseDataSize;
    EZuc8 *pucResponseData;
    EZui32 uiResponseErrorMask;
    EZui32 uiResponseOpcode;
    EZui32 uiResponseContext;
    EZbool bDebug;
} EZapiPrm_ExtKBPCommandParams;

#define EZapiPrm_ExtTCAMCommandParams EZapiPrm_ExtKBPCommandParams
#define EZapi_ExtCommandParams EZapiPrm_ExtKBPCommandParams
#endif

#endif /* HAVE_EZCHIP_HW*/







/* Ez Driver version */
#define KBP_NPX_XPT_DRV_VER    (0)

#ifdef NPX_NPS

/* Range for CB Address in Non -Debug mode */
#define KBP_NPX_XPT_NON_DEBUG_CB_ADDR_RANGE_START               (0)
#define KBP_NPX_XPT_NON_DEBUG_CB_ADDR_RANGE_END                 (1023)

#else
/* Range for CB Address in Non -Debug mode, dual port */
#define KBP_NPX_XPT_NON_DEBUG_CB_ADDR_RANGE_START_DUAL_PORT     (16368)
#define KBP_NPX_XPT_NON_DEBUG_CB_ADDR_RANGE_END_DUAL_PORT       (16383)

/* Range for CB Address in Non -Debug mode, single port */
#define KBP_NPX_XPT_NON_DEBUG_CB_ADDR_RANGE_START_SINGLE_PORT   (32752)
#define KBP_NPX_XPT_NON_DEBUG_CB_ADDR_RANGE_END_SINGLE_PORT     (32767)
#endif

/* Special Reason Codes for npx_xpt only
   in case of multiple errors value of the reason code returned will be ORed value of the
   corresponding reason codes */
#define KBP_NPX_XPT_FATAL_ERR                   (0x1FFF)
#define KBP_NPX_XPT_PKT_ERR                     (0x1001)
#define KBP_NPX_XPT_DEV_INTERFACE_ERR           (0x1002)
#define KBP_NPX_XPT_DEV_RESPONSE_TIMEOUT_ERR    (0x1004)
#define KBP_NPX_XPT_ILA_MAC_ERR                 (0x1008)
#define KBP_NPX_XPT_CTX_ID_MISMATCH_ERR         (0x1010)
#define KBP_NPX_XPT_RSLT_FIFO_OVERFLOW_ERR      (0x1020)

/* Maximum of 512b of response is supported by transport */
#define KBP_NPX_XPT_MAX_RESPONSE_DATA           (64)

struct kbp_npxxpt_resp_details {
    uint32_t m_responseOpcode;
    uint32_t m_responseContextId;
    uint32_t m_responseErrorMask; /* Contains Error mask value returned by
                                     Interface; Only LSB 6b are valid,
                                     value of 0 indicates no error */
    /* In case of packet error contains
       packet error code in both debug mode
       and non-debug mode.  In Debug mode; if no error
       detected contains data that is read from device; */
    uint8_t m_responseData[KBP_NPX_XPT_MAX_RESPONSE_DATA];
};

/**
 * @brief Properties for Npx transport layer
 *
 * Properties that can be set with kbp_npxxpt_set_property()
 *
 */

enum kbp_npxxpt_properties {
    KBP_NPX_PROP_DEBUG_FLAG,             /**< Enable/Disable the debug flag, if enables logs the response */
    KBP_NPX_PROP_EZ_FUNC,                /**< Register customer KBP function to pass the messages */
    KBP_NPX_PROP_CHANNEL_ID,             /**< Transport channel ID */
    KBP_NPX_PROP_LOG,                    /**< Log transport messages to file */
    KBP_NPX_PROP_LOG_TEST_BENCH_FMT,     /**< Log in the test bench format */
    KBP_NPX_PROP_ERROR_LOG,              /**< Log for capturing error messages - replacing stdout */
    KBP_NPX_PROP_EZ_SILICON_P1,          /**< split compare command to cbwrite and compare if mkey > 320b */
    KBP_NPX_PROP_HANG_ON_ERROR,          /**< if set will be in hang state; error returned by ezchip command API */
    KBP_NPX_PROP_RESEND_INST_ON_ERROR,   /**< if set will resend same inst again and be in hang state */
    KBP_NPX_PROP_SEND_RAED_RESP_ON_ERROR,/**< if set; on read the operations fails and params.uiResponseErrorMask > 0
                                              will send the response what we got from the device */
#ifdef NPX_NPS
    KBP_NPX_PROP_PAYLOAD_SIZE,           /**< compare response size, NPX = 0, NPS = 1 */
    KBP_NPX_PROP_SIDE,
#endif
    KBP_NPX_PROP_SMT1_INCR_CHANNEL_ID,   /**< if set, will increment the transport channel ID by uiOpcode[9],
                                              i.e. increment for SMT1 transactions */
    KBP_NPX_PROP_SET_RESET_ERROR_LOG_FILE,/**< Default: stdout, to set pass valid file handle,
                                                                to reset pass NULL */
    KBP_NPX_PROP_INVALID                 /**< Invalid. This should be the last entry */
};

/*
 * Install callback that transports messages through the
 * transport layer. Typically one will directly
 * install the function EZapiPrm_ExtKBPCommand
 */

#ifdef NPX_NPS
  typedef uint32_t (*kbp_npx_kbp_handle)(uint32_t channel, uint32_t value, void *msg);
#else
  typedef uint32_t (*kbp_npx_kbp_handle)(uint32_t channel, void *msg);
#endif

/**
 * Properties to tailor the transport layer. Supported properties
 * are defined in ::kbp_npxxpt_properties
 *
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_DEBUG_FLAG, <value>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_EZ_FUNC, <fn_ptr>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_CHANNEL_ID, id);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_LOG, fp);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_LOG_TEST_BENCH_FMT, fp);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_EZ_SILICON_P1, <value>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_HANG_ON_ERROR, <value>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_RESEND_INST_ON_ERROR, <num_times>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_FIX_PARITY_ERRORS, <value>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_SIDE, <value>);
 * kbp_npxxpt_set_property(xpt, KBP_NPX_PROP_PAYLOAD_SIZE, <value>);
 *
 * @param xpt pointer to the transport layer initialized by the function on success
 * @param property defined in ::kbp_npxxpt_properties
 * @param ... variable arguments related to the property
 *
 * @returns KBP_OK on success or an error code
 */

kbp_status kbp_npxxpt_set_property(void *xpt, enum kbp_npxxpt_properties property, ...);

/**
 * Initialize the Driver and return transport layer handle
 *
 * @param alloc valid allocator handle
 * @param type the device type to initialize the model for ::kbp_device_type
 * @param xpt pointer to the transport layer initialized by the function on success
 * @param debug_flag to select the mode
 *
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_npxxpt_init(struct kbp_allocator *alloc, enum kbp_device_type type, void **xpt);

/**
 * Destroy the resources allocated for the Driver
 *
 * @param type the device type of the driver
 * @param xpt valid initialized transport layer handle returned by kbp_npxxpt_init()
 * @return KBP_OK on success or an error code
 */

kbp_status kbp_npxxpt_destroy(enum kbp_device_type type, void *xpt);

/**
 * Return response information details
 *
 * @param xpt valid initialized transport layer handle returned by kbp_npxxpt_init()
 *
 * @retval valid response detail or NULL
 */

struct kbp_npxxpt_resp_details *kbp_npxxpt_getresponse_details(kbp_xpt *self);


#ifdef __cplusplus
}
#endif
#endif /*__NPXXPT_H */

