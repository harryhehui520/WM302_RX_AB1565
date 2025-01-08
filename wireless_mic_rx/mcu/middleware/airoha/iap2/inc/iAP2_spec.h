/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#ifndef __IAP2_SPEC_H__
#define __IAP2_SPEC_H__

#include <stdbool.h>
#include "iAP2.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief IAP2_COMMAND is used in structure define to make the structure more compact.The define is different as per compiler.
 */
#if _MSC_VER >= 1500
#define IAP2_MESSAGE(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))
#elif defined(__GNUC__)
#define IAP2_MESSAGE(...) __VA_ARGS__ __attribute__((__packed__))
#define IAP2_COMMAND_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ARMCC_VERSION)
#pragma anon_unions
#define IAP2_MESSAGE(...) __VA_ARGS__ __attribute__((__packed__))
#define IAP2_COMMAND_ALIGNMENT4(...) __VA_ARGS__ __attribute__((aligned(4)))
#elif defined(__ICCARM__)
#define IAP2_MESSAGE(...) __packed __VA_ARGS__
#define IAP2_COMMAND_ALIGNMENT4(...) _Pragma("data_alignment=4") __VA_ARGS__
#else
#error "Unsupported Platform"
#endif

/** Start of iAP2 link packet */
#define IAP2_PACKET_START           0xFF5A

/** Packet control byte. */
#define IAP2_PKT_SYNC               0x80
#define IAP2_PKT_ACK                0x40
#define IAP2_PKT_EACK               0x20
#define IAP2_PKT_RST                0x10
#define IAP2_PKT_SLP                0x08

/** Session identifier default value, because iAP2 Seesion payloads cannot be present in SYN packet . */
#define IAP2_SESSION_ID_LINK        0

/* IAP2 Control Session */
#define IAP2_CTRL_MESSAGE_START                             0x4040

#define IAP2_CTRL_REQUEST_AUTHENTICATION_CERTIFICATE        0xAA00
#define IAP2_CTRL_AUTHENTICATION_CERTIFICATE                0xAA01
#define IAP2_CTRL_REQUEST_AUTHENTICATION_CHALLENGE_RESPONSE 0xAA02
#define IAP2_CTRL_AUTHENTICATION_RESPONSE                   0xAA03
#define IAP2_CTRL_AUTHENTICATION_FAILED                     0xAA04
#define IAP2_CTRL_AUTHENTICATION_SUCCEEDED                  0xAA05
#define IAP2_CTRL_AUTHENTICATION_SERIAL_NUMBER              0xAA06

#define IAP2_PARAM_AUTHENTICATION_CERTIFICATE               0
#define IAP2_PARAM_AUTHENTICATION_CHALLENGE                 0
#define IAP2_PARAM_AUTHENTICATION_RESPONSE                  0

#define IAP2_CTRL_START_IDENTIFICATION                      0x1D00
#define IAP2_CTRL_IDENTIFICATION_INFORMATION                0x1D01
#define IAP2_CTRL_IDENTIFICATION_ACCEPTED                   0x1D02
#define IAP2_CTRL_IDENTIFICATION_REJECTED                   0x1D03
#define IAP2_CTRL_CANCEL_IDENTIFICATION                     0x1D05
#define IAP2_CTRL_IDENTIFICATION_INFORMATION_UPDATE         0x1D06

#define IAP2_CTRL_START_EXTERNAL_ACCESSORY_PROTOCOL         0xEA00
#define IAP2_CTRL_STOP_EXTERNAL_ACCESSORY_PROTOCOL          0xEA01
#define IAP2_CTRL_REQUEST_APP_LAUNCH                        0xEA02
#define IAP2_CTRL_STATUS_EXTERNAL_ACCESSORY_PROTOCOL        0xEA03


/* Authentication IC */
#define IAP2_AUTH_ADDR      0x22

#define IAP2_AUTH_REG_AUTHENTICATION_CTRL_STATUS    0x10
#define IAP2_AUTH_REG_CHALLENGE_RESPONSE_LENGTH     0x11
#define IAP2_AUTH_REG_CHALLENGE_RESPONSE_DATA       0x12

#define IAP2_AUTH_REG_CHALLENGE_LENGTH              0x20
#define IAP2_AUTH_REG_CHALLENGE_DATA                0x21

#define IAP2_AUTH_REG_CERTIFICATE_LENGTH            0x30
#define IAP2_AUTH_REG_CERTIFICATE_DATA              0x31

/**
 * @brief IAP2 event.
 */
#define IAP2_EVT_DISCONNECTED                       0x00
#define IAP2_EVT_CONNECTED                          0x01
#define IAP2_EVT_EA_SESSION_START                   0x02
#define IAP2_EVT_EA_SESSION_STOP                    0x03
#define IAP2_EVT_DATA_RECIEVED                      0x04
typedef uint8_t iap2_evt_t;

/**
 *  @brief This structure defines the iAP2 control session message structure.
 */
typedef struct {
    uint16_t message_start;    /**< Start of control session packet. */
    uint16_t message_length;   /**< Message length of control session packet. */
    uint16_t message_id;       /**< Message ID of control session packet. */
} iap2_ctrl_session_t;


/**
 *  @brief This structure defines the iAP2 control session message parameter structure.
 */
typedef struct {
    uint16_t param_length;   /**< Parameter length. */
    uint16_t param_id;       /**< Parameter ID. */
    uint8_t param[1];        /**< Parameter data. */
} iap2_param_t;


/**
 *  @brief This structure defines the iAP2 ea session structure.
 */
typedef struct {
    uint16_t session_id;   /**< Session ID. */
} iap2_ea_session_t;


/** IAP2 packet structure, fixed-size 9-byte. */
IAP2_MESSAGE(
typedef struct {
    uint16_t packet_start;
    uint16_t packet_length;
    uint8_t control_byte;
    uint8_t seq_number;            /** packet sequence number. */
    uint8_t ack_number;            /** packet acknowledgement number. */
    uint8_t session_identifier;
    uint8_t header_checksum;
}) iap2_packet_header_t;

/* IAP2 State Control */

#define IAP2_STATE_TRANSPORT_DISCONNECTED               0x00
#define IAP2_STATE_TRANSPORT_CONNECTING                 0x01
#define IAP2_STATE_TRANSPORT_CONNECTED                  0x02
#define IAP2_STATE_DETECT_SUPPORT                       0x03
#define IAP2_STATE_LINK_UNSUPPORT                       0x04
#define IAP2_STATE_SEND_LINK_CONFIG                     0x05
#define IAP2_STATE_WAIT_LINK_CONFIG                     0x06
#define IAP2_STATE_WAIT_AUTHENTICATION_REQUEST          0x07
#define IAP2_STATE_READ_CERTIFICATE_LENGTH              0x08
#define IAP2_STATE_READ_CERTIFICATE_DATA                0x09
#define IAP2_STATE_WAIT_CHALLENGE_REQUEST               0x0A
#define IAP2_STATE_READ_CHALLENGE_LENGTH                0x0B
#define IAP2_STATE_READ_CHALLENGE_DATA                  0x0C
#define IAP2_STATE_WAIT_AUTHENTICATION_VERDICT          0x0D
#define IAP2_STATE_WAIT_START_IDENTIFICATION            0x0E
#define IAP2_STATE_SEND_IDENTIFICATION                  0x0F
#define IAP2_STATE_WAIT_IDENTIFICATION_VERDICT          0x10
#define IAP2_STATE_LINK_ESTABLISHED                     0x11
typedef uint8_t iap2_state_t;

typedef union {
    struct {
        uint8_t detectCount; /**detect counter, for multi attemps. */
    } detect;
    struct {
        uint16_t length;
    } certificate;
    struct {
        uint16_t length;
    } challenge;
    struct {
        uint8_t syncCount; /**sync counter, for multi attemps. */
    } sync;
} iap2_state_var_t;

typedef struct {
    iap2_state_t state;
    iap2_state_var_t stateVar;
    uint8_t txSEQ; /** SEQ number for next tx packet. */
    uint8_t rxSEQ; /** SEQ number of last acknowledged rx packet. */
    uint8_t rxCumulative;/** the num of recieved ACK. */
    uint8_t maxCumulative;/** the max num of recieved ack before snet an ACK. */
    uint8_t lastAckPSN;
    uint8_t SNWindowRange;
    uint16_t rxCumulativeTimeout;
    uint32_t rxCumulativeTimer;
    uint8_t protocolIdentifier;
    uint8_t protocolSessionIdentifier;
    uint16_t max_packet_length;         /**< Maximum recieved packet length. */
    uint16_t retransmission_timeout;    /**< Retransmission timeout . */
    uint16_t reserve;                   /**< Reserved for future. */
} iap2_link_info_t;

/** @brief This structure defines #IAP2_READY_TO_SEND_IND. */
typedef struct {
    uint16_t protocol_id;                /* it  is only for EA Session*/
    uint16_t session_id;                 /* it  is only for EA Session*/
} iap2_ea_session_op_t;

/** @brief This structure defines #IAP2_RECIEVED_DATA_IND. */
typedef struct {
    uint8_t *data;   /**< The packet is received from a remote device.*/
    uint16_t length;  /**< The length of the received packet.*/
    iap2_session_type_t session_t;
    union {
        uint16_t session_id;                 /* it is only for EA Session*/
        uint16_t message_id;                 /* it is only for Control Session*/
    };
} iap2_data_received_t;

/** @brief This defines the structure of identification result message parameter. */
typedef struct {
    uint16_t param_length;   /**< Parameter length. */
    uint16_t param_id;       /**< Parameter ID. */
} iap2_identification_result_t;

/**
 *  @brief APP launch method.
 */
#define LAUNCH_WITH_USER_ALERT              0x00
#define LAUNCH_WITHOUT_USER_ALERT           0x01
typedef uint8_t iap2_app_launch_method_t;

/**
 *  @brief This structure defines the iAP2 APP launch message structure.
 */
typedef struct {
    uint8_t *app_bundle_id;   /**< The app bundle id.*/
    uint16_t app_bundle_id_len; /**< The length of app bundle id.*/
    iap2_app_launch_method_t method;  /**< The app launch method.*/
} iap2_app_launch_t;

/**
 *  @brief iAP2 status external accessory protocol status type.
 */
#define SESSION_STATUS_OK                   0x00   /**< Accept external accessory session start.*/
#define SESSION_CLOSE                       0x01   /**< Reject external accessory session start when reach the max supported session number.*/
typedef uint8_t iap2_ea_session_status_t;

/**
 * @brief      This function begins to start iAP2 procedure.
 * @param[in]  None.
 * @return     None.
 */
int32_t iap2_start_link(uint32_t linkIndex);

/**
 * @brief      This function handle sync payload init.
 * @param[in]  None.
 * @return     None.
 */
void iap2_sync_payload_init(void);

/**
 * @brief      This function is used to clear the saved link info.
 * @param[in]  linkIndex         is the linkindex of the current transport, like SPP connection handle.
 * @return     None.
 */
void iap2_clear_linkInfo(uint32_t linkIndex);

/**
 * @brief     This is a user-defined API that returns the iAP2 transport link information.
 * @return    A pointer to the iAP2 transport link information. The pointer cannot be NULL. It's recommended to use a global variable to store the iAP2 transport link information.
 */
iap2_link_info_t *iap2_get_link_info(uint32_t linkIndex);

/**
 * @brief   This function is a static callback for the application to listen to the iAP2 event. Provide a user-defined callback.
 * @param[in] linkIndex
 * @param[in] event
 * @param[in] param     is the payload of the callback message.
 * @return            None.
 */
void iap2_event_callback(uint32_t linkIndex, iap2_evt_t event, void *param);

/**
 * @brief      This function handle the events from the transport.
 * @param[in]  linkIndex         is the linkindex of the current transport, like SPP connection handle.
 * @param[in] dataPtr           is a pointer to a structure that specifies the parameters for the event.
 * @param[in] data_len         is the length of the data.
 * @return     None.
 */
void iap2_rx_data_handler(uint32_t linkIndex, uint8_t *dataPtr, uint16_t data_len);


/**
 * @brief                    This function sends data by EA Session to a remote device.
 * @param[in] linkIndex        is the connection handle of the current connection.
 * @param[in] protocolSessionIdentifier   is the External Accessory protocol session identifier.
 * @param[in] data           is a pointer to the packet to send to a remote device.
 * @param[in] data_size        is the length of a packet to send.
 * @return                   #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                           #IAP2_STATUS_FAIL, the operation has failed.
 *                           #IAP2_STATUS_TX_NOT_AVAILABLE, if the TX buffer in the local device or the RX buffer in the remote
 *                           device has no space available. The application should wait for the #IAP2_READY_TO_SEND_IND event before
 *                           the next send operation.
 */
int32_t iap2_send_ea_session_data(uint32_t linkIndex, uint16_t protocolSessionIdentifier, uint8_t *data, uint16_t data_size);

/**
 * @brief                    This function sends data by EA Session to a remote device and check whether packet can be send now.
 * @param[in] linkIndex        is the connection handle of the current connection.
 * @param[in] protocolSessionIdentifier   is the External Accessory protocol session identifier.
 * @param[in] data           is a pointer to the packet to send to a remote device.
 * @param[in] data_size        is the length of a packet to send.
 * @return                   #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                           #IAP2_STATUS_FAIL, the operation has failed.
 *                           #IAP2_STATUS_TX_NOT_AVAILABLE, if the TX buffer in the local device or the RX buffer in the remote
 *                           device has no space available. The application should wait for the #IAP2_READY_TO_SEND_IND event before
 *                           the next send operation.
 *                           #IAP2_STATUS_TX_QUEUE_FULL, not received the ACK packet from the remote device.
 */
int32_t iap2_send_data_pre_check(uint32_t linkIndex, uint16_t protocolSessionIdentifier, uint8_t *data, uint16_t data_size);

/**
 * @brief                    This function sends data by Control Session to a remote device.
 * @param[in] linkIndex          is the connection handle of the current connection.
 * @param[in] message_id  is a message id of the control session packet to send to a remote device.
 * @param[in] data           is a pointer to the packet to send to a remote device.
 * @param[in] data_size          is the length of a packet to send.
 * @return                   #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                           #IAP2_STATUS_FAIL, the operation has failed.
 *                           #IAP2_STATUS_TX_NOT_AVAILABLE, if the TX buffer in the local device or the RX buffer in the remote
 *                           device has no space available. The application should wait for the #IAP2_READY_TO_SEND_IND event before
 *                           the next send operation.
 */
int32_t iap2_send_ctrl_session_data(uint32_t linkIndex, uint16_t message_id, uint8_t *data, uint16_t data_size);


/**
 * @brief           This function holds the iAP2 control seesion packet until it is fully consumed.
 * @param[in]    data  is the initialization parameter. The value is provided once it is called by the iAP2.
 * @return          None.
 */
void iap2_hold_ctrl_session_data(uint8_t *data);

/**
 * @brief           This function holds the iAP2 ea session packet until it is fully consumed.
 * @param[in]    data  is the initialization parameter. The value is provided once it is called by the iAP2.
 * @return          None.
 */
void iap2_hold_ea_session_data(uint8_t *data);

/**
* @brief           This function releases the AP2 control seesion packet  after it is consumed.
* @param[in]    data  is the initialization parameter. The value is provided once it is called by the iAP2.
* @return         None.
*/
void iap2_release_ctrl_session_data(uint8_t *data);

/**
* @brief           This function releases the AP2 ea session packet  after it is consumed.
* @param[in]    data  is the initialization parameter. The value is provided once it is called by the iAP2.
* @return         None.
*/
void iap2_release_ea_session_data(uint8_t *data);

/**
* @brief                    This function sends data by Control Session to a remote device.
* @param[in] linkIndex          is the connection handle of the current connection.
* @param[in] sessionIdentifier  is the External Accessory protocol session identifier.
* @param[in] status           is the status of External Accessory protocol session.
* @return                   #IAP2_STATUS_SUCCESS, the operation completed successfully.
*                           #IAP2_STATUS_FAIL, the operation has failed.
*                           #IAP2_STATUS_TX_NOT_AVAILABLE, if the TX buffer in the local device or the RX buffer in the remote
*                           device has no space available. The application should wait for the #IAP2_READY_TO_SEND_IND event before
*                           the next send operation.
*/
int32_t iap2_extA_protocol_status_change(uint32_t linkIndex, uint16_t sessionIdentifier, iap2_ea_session_status_t status);

#ifdef __cplusplus
}
#endif

#endif /* __IAP2_SPEC_H__ */

