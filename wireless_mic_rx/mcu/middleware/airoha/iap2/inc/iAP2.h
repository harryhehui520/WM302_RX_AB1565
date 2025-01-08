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

#ifndef __IAP2_H__
#define __IAP2_H__

/**
 * @addtogroup Bluetooth
 * @{
 * @addtogroup BluetoothIAP2 IAP2
 * @{
 * This section introduces the IAP2 APIs including terms, supported features and details on how to use the APIs to set up a IAP2 session.
 * The IAP2 defines the protocol consists of a link and one or more sessions.
 *
 * Terms and Acronyms
 * ======
 * |Terms                         |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b EA                           | External Accessory is one session type of IAP2. |
 *
 * @section iap2_api_usage How to use this module
 *
 * - The iAP2 confirmation/indication notifies the upper layer that the process has finished or an indication is received.
 *   IAP2_XXX_CNF represents the events that a procedure has finished.
 *   IAP2_XXX_IND represents the events that an indication has been received.
 * - The iAP2 confirmation/indication structures provide related information to the upper layer.
 *   The data is obtained from the events parameter.
 *
 *  - 1. Mandatory, implement #iap2_init() to set the initial configuration. It is suggeted to be invoked when the Bluetooth is powered on.
 *   - Sample code:
 *    @code
 *       int main(void)
 *       {
 *           #ifdef MTK_IAP2_PROFILE_ENABLE
 *               iap2_init();
 *           #endif
 *       }
 *    @endcode
 *  - 2. Mandatory, implement iap2_register_callback(void *callback) to register the iAP2 event handler, and implement the callback to handle the
 *           iAP2 events, such as connect, disconnect, session start indication, data received, etc.
 *   - Sample code:
 *    @code
 *       void bt_iap2_app_example(void)
 *       {
 *         iap2_init();
 *      iap2_register_callback(bt_iap2_event_notify_callback);
 *     }
 *
 *       void bt_iap2_event_notify_callback(iap2_event_t event_id, void *param)
 *       {
 *           switch (event_id)
 *           {
 *               case IAP2_CONNECT_IND:
 *               {
 *                   iap2_connect_ind_t *params = (iap2_connect_ind_t *)param;
 *                   // Check connection result and save handle if connection is successful.
 *                   break;
 *               }
 *               case IAP2_DISCONNECT_IND:
 *               {
 *                   iap2_disconnect_ind_t *params = (iap2_disconnect_ind_t *)param;
 *                   // Check disconnection result and clear the related context.
 *                   break;
 *               }
 *               case IAP2_EA_SESSION_OPEN_IND:
 *               {
 *                   iap2_ea_session_open_close_t *params = (iap2_ea_session_open_close_t *)param;
 *                   // Check EA session set up result and save the session id if session set up is successful.
 *                   break;
 *               }
 *               case IAP2_EA_SESSION_CLOSE_IND:
 *               {
 *                   iap2_ea_session_open_close_t *params = (iap2_ea_session_open_close_t *)param;
 *                   // Check EA session set down result and clear the related context..
 *                   break;
 *               }
 *               default:
 *                   break;
 *           }
 *       }
 *    @endcode
 * - 3. Mandatory, handle received data.
 *  - Step 1. The #BT_SPP_DATA_RECEIVED_IND event notifies the function #bt_app_event_callback() if the device received data from the remote.
 *   - Sample code:
 *    @code
 *      uint8_t app_receive_data_buffer[900] = {0};
 *       void bt_iap2_event_notify_callback(iap2_event_t event_id, void *param)
 *       {
 *           switch (event_id) {
 *               case IAP2_RECIEVED_DATA_IND:
 *                   iap2_data_received_ind_t* data_ind_p = (iap2_data_received_ind_t*) param;
 *                   memcpy(app_receive_data_buffer, data_ind_p->packet, data_ind_p->packet_length);
 *               default:
 *                   break;
 *           }
 *       }
 *    @endcode
 *  - Step 2. If there is no buffer for the application to save the iAP2 packet from the #IAP2_RECIEVED_DATA_IND, call the function #iap2_hold_data()
 *      to hold the packet in the Bluetooth RX buffer.
 *   - Sample code:
 *    @code
 *       bt_iap2_data_received_ind_t saved_data = {0};
 *       void bt_iap2_event_notify_callback(iap2_event_t event_id, void *param)
 *       {
 *           switch (event_id) {
 *               case IAP2_RECIEVED_DATA_IND:
 *                   iap2_data_received_ind_t* data_ind_p = (iap2_data_received_ind_t*) buff;
 *                   if (IAP2_SESSION_TYPE_CONTROL == rx_ind->session_type) {
 *                       iap2_hold_data(IAP2_SESSION_TYPE_CONTROL, data_ind_p->packet);
 *                   }
 *                   saved_data.session = IAP2_SESSION_TYPE_CONTROL;
 *                   saved_data.packet = data_ind_p->packet;
 *                   saved_data.packet = data_ind_p->packet;
 *                   saved_data.packet_length = data_ind_p->packet_length
 *               default:
 *                   break;
 *           }
 *       }
 *    @endcode
 *  - Step 3. Release the iAP2 packet after it is stored in the application by calling the function #iap2_release_data().
 *      If not released, the Bluetooth RX buffer may be exhausted and the application cannot receive data from a remote device.
 *   - Sample code:
 *    @code
 *       uint8_t app_new_data_buffer[900] = {0};
 *       bt_iap2_data_received_ind_t* data_p = &saved_data;
 *       memcpy(app_new_data_buffer, data_p->packet, data_p->packet_length);
 *       iap2_release_data(saved_data.session, saved_data.packet);
 *    @endcode
 *  - 4. Mandatory, implement #iap2_get_bt_address() and #iap2_get_bt_local_name() to set the bluetooth address and bluetooth name. This is a user-defined API, which is invoked when the Bluetooth is powered on. It should be implemented by the application.
 *   - Sample code:
 *    @code
 *       uint8_t *iap2_get_bt_address(void)
 *       {
 *           uint8_t bt_local_public_addr[6];
 *           // get the bt address and copy to bt_local_public_addr.
 *           return (uint8_t *)bt_local_public_addr;
 *       }
 *
 *       uint8_t *iap2_get_bt_local_name(void)
 *       {
 *           uint8_t device_name[31];
 *           // get the bt name and copy to device_name.
 *           return (uint8_t *)device_name;
 *       }
 *    @endcode
 *  - 5. Mandatory, implement #iap2_get_sync_payload() and #iap2_get_identification_parameters() to set the link sync payload and identification parameters. This is a user-defined API, which is invoked when the Bluetooth is powered on. It should be implemented by the application.
 *   - Sample code:
 *    @code
 *       uint8_t const *iap2_get_identification_parameters(void)
 *       {
 *           return (uint8_t const *)gIAP2_Iden_Param_pointer;
 *       }
 *
 *       iap2_sync_payload_t *iap2_get_sync_payload(void)
 *       {
 *           return (iap2_sync_payload_t *)&gIAP2_Sync_Payload;
 *       }
 *    @endcode
 *  - 6. Optional, initiate a connection to a remote device.
 *   - Sample code:
 *    @code
 *       ret = iap2_connect(&iap2_handle, address);
 *    @endcode
 *  - 7. Optional, initiate the disconnection from a remote device.
 *   - Sample code:
 *    @code
 *       ret = iap2_disconnect(iap2_handle);
 *    @endcode
 */

#include "bt_type.h"

/**
 * @defgroup IAP2_define Define
 * @{
 */

/**
 * @brief An invalid value for the IAP2 handle.
 */
#define IAP2_INVALID_HANDLE 0x00000000

/**
 * @brief The Max Number that IAP2 support users.
 */
#define IAP2_APP_SUPPORT_CB_MAX_NUM  1

/**
 * @brief The Max length of identification buffer.
 */
#define IAP2_PARAM_IDEN_MAX_SIZE    512

/**
 * @brief The Max length of TX buffer.
 */
#define IAP2_TX_QUEUE_MAX_LENGTH (5)

/**
 * @brief IAP2 session identifier.
 */
#define IAP2_SESSION_ID_CTRL        0xCC     /**< IAP2 control session. */
#define IAP2_SESSION_ID_EXTA        0xEA     /**< IAP2 external accessory session. */

/**
 * @brief IAP2 IdentificationInformation message paramter IDs.
 */
#define IAP2_PARAM_IDEN_NAME                                0  /**< IAP2 name. */
#define IAP2_PARAM_IDEN_MODEL                               1  /**< IAP2 model identifier. */
#define IAP2_PARAM_IDEN_MANUFACTURER                        2  /**< IAP2 manufacturer. */
#define IAP2_PARAM_IDEN_SERIAL_NUMBER                       3  /**< IAP2 serial number. */
#define IAP2_PARAM_IDEN_FIRMWARE_VERSION                    4  /**< IAP2 firmware version. */
#define IAP2_PARAM_IDEN_HARDWARE_VERSION                    5  /**< IAP2 hardware version. */
#define IAP2_PARAM_IDEN_MESSAGE_SENT_BY_ACCESSORY           6  /**< IAP2 messages sent by accessory. */
#define IAP2_PARAM_IDEN_MESSAGE_RECV_FROM_DEVICE            7  /**< IAP2 messages received from device. */
#define IAP2_PARAM_IDEN_POWER_PROVIDING_CAPABILITY          8  /**< IAP2 power providing capability. */
#define IAP2_PARAM_IDEN_MAX_CURRENT_FROM_DEVICE             9  /**< IAP2 maximum current drawn from device. */
#define IAP2_PARAM_IDEN_EXTERNAL_ACCESSORY_PROTOCOL         10 /**< IAP2 supported external accessory protocol. */
#define IAP2_PARAM_IDEN_APP_MATCH_TEAM_ID                   11 /**< IAP2 App match team ID. */
#define IAP2_PARAM_IDEN_CURRENT_LANGUAGE                    12 /**< IAP2 current language. */
#define IAP2_PARAM_IDEN_SUPPORTED_LANGUAGE                  13 /**< IAP2 supported language. */
#define IAP2_PARAM_IDEN_SERIAL_TRANSPORT_COMPONENT          14 /**< IAP2 UART transport component. */
#define IAP2_PARAM_IDEN_USB_DEVICE_TRANSPORT_COMPONENT      15 /**< IAP2 USB device transport component. */
#define IAP2_PARAM_IDEN_USB_HOST_TRANSPORT_COMPONENT        16 /**< IAP2 USB host transport component. */
#define IAP2_PARAM_IDEN_BLUETOOTH_TRANSPORT_COMPONENT       17 /**< IAP2 bluetooth transport component. */
#define IAP2_PARAM_IDEN_IAP2_HID_COMPONENT                  18 /**< IAP2 HID component. */
#define IAP2_PARAM_IDEN_VEHICLE_INFORMATION_COMPONENT       20 /**< IAP2 vehicle information component. */
#define IAP2_PARAM_IDEN_VEHICLE_STATUS_COMPONENT            21 /**< IAP2 vehicle status component. */
#define IAP2_PARAM_IDEN_LOCATION_INFORMATION_COMPONENT      22 /**< IAP2 location information component. */
#define IAP2_PARAM_IDEN_USB_HOST_HID_COMPONENT              23 /**< IAP2 USB host HID component. */
#define IAP2_PARAM_IDEN_PRODUCT_PLAN_UID                    34 /**< IAP2 product plan UID. */


/**
 *  @brief Define for iAP2 app event.
 */
#define IAP2_CONNECT_IND            0x00 /**< IAP2 Connected indication Event. */
#define IAP2_DISCONNECT_IND         0x01 /**< IAP2 Disconnected indication Event. */
#define IAP2_RECIEVED_DATA_IND      0x02 /**< IAP2 Data Recieved indication Event. */
#define IAP2_READY_TO_SEND_IND      0x03 /**< IAP2 Dtat Send is available indication Event. */
#define IAP2_EA_SESSION_OPEN_IND    0x04 /**< IAP2 EA Session has been eatablished. */
#define IAP2_EA_SESSION_CLOSE_IND   0x05 /**< IAP2 EA Session has been stoped. */
typedef uint8_t iap2_event_t;          /**< The type of A2DP app event. */

/**
 *  @brief Define for iAP2 status type.
 */
#define IAP2_STATUS_SUCCESS               0x00   /**< Operation success. */
#define IAP2_STATUS_FAIL                 -0x01   /**< Operation fail. */
#define IAP2_STATUS_INVALID_HANDLE       -0x02   /**< Handle is error. */
#define IAP2_STATUS_INVALID_UUID         -0x03   /**< Invalid UUID. */
#define IAP2_STATUS_OUT_OF_MEMORY        -0x04   /**< No Memory for operation. */
#define IAP2_STATUS_TX_NOT_AVAILABLE     -0x05   /**<  The TX buffer in the local device or the RX buffer in the remote device has no space available. */
#define IAP2_STATUS_TX_QUEUE_FULL        -0x06   /**<  Remote device didn't respond enough ACK. */
typedef int32_t iap2_status_t;                 /**< The type of iAP2 status role. */

/**
 *  @brief Define for IAP2 Session type..
 */

#define IAP2_SESSION_TYPE_CONTROL                (0)       /**< Control session. */
#define IAP2_SESSION_TYPE_FILE_TRANSFER          (1)       /**< Open state. */
#define IAP2_SESSION_TYPE_EXTERNAL_ACCESSORY     (2)       /**< Streaming state. */
typedef uint8_t iap2_session_type_t;                    /**< The type of iAP2 session. */


/**
 * @}
 */

/**
 * @defgroup IAP2_struct Struct
 * @{
 */

/**
 *  @brief This structure defines the header of iAP2 control session message structure.
 */
typedef struct {
    uint16_t message_length;  /**< Message length of control session packet. */
    uint16_t message_id;      /**< Message ID of control session packet. */
} iap2_control_msg_header_t;


/**
 *  @brief This structure defines the header of iAP2 control session message parameter structure.
 */
typedef struct {
    uint16_t param_length;  /**< Parameter length. */
    uint16_t param_id;      /**< Parameter ID. */
} iap2_param_header_t;



/**
 *  @brief This structure defines the #IAP2_CONNECT_IND.
 */
typedef struct {
    iap2_status_t status;         /**< Connect status. */
    uint32_t handle;              /**< The connection handle of the current connection. */
    uint16_t max_packet_length;   /**< The maximum length of a TX/RX packet after a iAP2 connection is established. */
    bt_bd_addr_t *address;        /**< The Bluetooth address of a remote device. */
} iap2_connect_ind_t;

/**
 *  @brief This structure defines the #IAP2_DISCONNECT_IND.
 */
typedef struct {
    uint32_t handle;      /**< The connection handle of the current connection. */
} iap2_disconnect_ind_t;

/**
 *  @brief This structure defines the #IAP2_READY_TO_SEND_IND.
 */
typedef struct {
    uint32_t handle;     /**< The connection handle of the current connection. */
} iap2_ready_to_send_ind_t;


/**
 *  @brief This structure defines the #IAP2_EA_SESSION_OPEN_IND and #IAP2_EA_SESSION_CLOSE_IND.
 */
typedef struct {
    uint16_t protocol_id; /**< The external accessory protocol id. */
    uint16_t session_id;  /**< The external accessory protocol session id. */
} iap2_ea_session_open_close_t;

/**
 *  @brief This structure defines the #IAP2_RECIEVED_DATA_IND.
 */
typedef struct {
    uint32_t handle;                  /**< The connection handle of the current connection. */
    uint8_t *packet;                  /**< The point of packet that is received from a remote device. */
    uint16_t packet_length;           /**< The length of the received packet. */
    iap2_session_type_t session_type; /**< The received packet is control session packet or ea session packet. */
    union {
        uint16_t session_id;          /**< only for EA Seesion, it is the external accessory protocol session id. */
        uint16_t message_id;          /**< only for Control Seesion, it is the message id of control session packet. */
    };
} iap2_data_received_ind_t;


/**
 *  @brief This structure defines the link synchronization payload details.
 */
typedef struct {
    uint8_t link_version;               /**< Link version. */
    uint8_t max_num_out_packets;        /**< Maximum number of outstanding packets. */
    uint16_t max_packet_length;         /**< Maximum recieved packet length. */
    uint16_t retransmission_timeout;    /**< Retransmission timeout . */
    uint16_t cumulative_ack_timeout;    /**< Cumulative acknowledgement timeout. */
    uint8_t max_num_retransmissions;    /**< Maximum number of retransmission. */
    uint8_t max_num_cumulative_acks;    /**< Maximum cumulative acknowledgement. */
    struct {
        uint8_t identifier;             /**< Session ID. */
        uint8_t type;                   /**< Session type. */
        uint8_t version;                /**< Session version. */
    } session[2];                       /**< IAP2 sessions */
} iap2_sync_payload_t;

/**
 *  @brief iAP2 event handler type.
 */
typedef void(* iap2_notify_callback)(iap2_event_t event_id, void *param);


/**
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Function for initializing the iAP2 module. It is better to invoke this function when bootup and it shuold be called one time in a project.
 * @param[in] None.
 * @return    #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *            #IAP2_STATUS_FAIL, the operation has failed.
 */
iap2_status_t iap2_init(void);

/**
 * @brief     This function registers a callback to the IAP2 module.
 * @param[in] callback      is a pointer to the callback function to register. This callback function is invoked by the IAP2 module.
 * @return                  #IAP2_STATUS_SUCCESS, if the operation is successful.
 *                          #IAP2_STATUS_FAIL, if the callback type is incorrect or already registered or if the maximum number of callbacks,
 *                          as defined by #IAP2_APP_SUPPORT_CB_MAX_NUM has been reached.
 */
iap2_status_t iap2_register_callback(iap2_notify_callback callback);

/**
 * @brief     This function unregister the callback from the IAP2 module.
 * @param[in] type          is the callback type to unregister.
 * @param[in] callback      is a pointer to the callback function to unregister.
 * @return                  #IAP2_STATUS_SUCCESS, if the operation is successful.
 *                          #IAP2_STATUS_FAIL, if the callback type is incorrect or unregistered, or the callback function is unregistered.
 */
iap2_status_t iap2_deregister_callback(iap2_notify_callback callback);

/**
 * @brief                       This function is for the iap2 client to connect to a remote server, the #IAP2_CONNECT_IND event is reported to
 *                              indicate the result of the connection. Note that this API can only be used by an iap2 client.
 * @param[out] handle           is the connection handle of the current connection.
 * @param[in] address           is the Bluetooth address of a remote device.
 * @return                      #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                              #IAP2_STATUS_FAIL, the operation has failed.
 *                              #IAP2_STATUS_INVALID_UUID, the UUID error.
 */
iap2_status_t iap2_connect(uint32_t *handle, const bt_bd_addr_t *address);

/**
 * @brief               This function disconnects an existing connection, the #IAP2_DISCONNECT_IND event is reported
 *                      to indicate the result of the disconnection.
 * @param[in] handle    is the iAP2 handle of the current connection.
 * @return              #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                      #IAP2_STATUS_FAIL, the operation has failed.
 *                      #IAP2_STATUS_INVALID_HANDLE, the handle error.
 */
iap2_status_t iap2_disconnect(uint32_t handle);

/**
 * @brief                    This function sends data by EA Session to a remote device.
 * @param[in] handle        is the connection handle of the current connection.
 * @param[in] session_id   is the External Accessory protocol session identifier.
 * @param[in] data           is a pointer to the packet to send to a remote device.
 * @param[in] length        is the length of a packet to send.
 * @return                   #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                           #IAP2_STATUS_FAIL, the operation has failed.
 *                           #IAP2_STATUS_TX_NOT_AVAILABLE, if the TX buffer in the local device or the RX buffer in the remote
 *                           device has no space available. The application should wait for the #IAP2_READY_TO_SEND_IND event before
 *                           the next send operation.
 */
iap2_status_t iap2_send_data_by_external_accessory_session(uint32_t handle, uint16_t session_id, uint8_t *data, uint16_t length);

/**
 * @brief                    This function sends data by Control Session to a remote device.
 * @param[in] handle          is the connection handle of the current connection.
 * @param[in] message_id  is a message id of the control session packet to send to a remote device.
 * @param[in] data           is a pointer to the packet to send to a remote device.
 * @param[in] length          is the length of a packet to send.
 * @return                   #IAP2_STATUS_SUCCESS, the operation completed successfully.
 *                           #IAP2_STATUS_FAIL, the operation has failed.
 *                           #IAP2_STATUS_TX_NOT_AVAILABLE, if the TX buffer in the local device or the RX buffer in the remote
 *                           device has no space available. The application should wait for the #IAP2_READY_TO_SEND_IND event before
 *                           the next send operation.
 */
iap2_status_t iap2_send_data_by_control_session(uint32_t handle, uint16_t message_id, uint8_t *data, uint16_t length);

/**
 * @brief     This is a user-defined API that returns the Bluetooth address.
 * @param[in] None.
 * @return    A pointer to the Bluetooth address. The pointer cannot be NULL. It's recommended to use a global variable to store the Bluetooth address.
 */
uint8_t *iap2_get_bt_address(void);

/**
 * @brief     This is a user-defined API that returns the Bluetooth name.
 * @param[in] None.
 * @return    A pointer to the Bluetooth name. The pointer cannot be NULL. It's recommended to use a global variable to store the Bluetooth name.
 */
uint8_t *iap2_get_bt_local_name(void);

/**
 * @brief     This is a user-defined API that returns the Serail Number.
 * @param[in] None.
 * @return    A pointer to the Serail Number. The pointer cannot be NULL. It's recommended to use a global variable to store the Serail Number.
 */
uint8_t *iap2_get_serial_number(void);

/**
 * @brief     This is a user-defined API that returns the Model Name.
 * @param[in] None.
 * @return    A pointer to the Model Name. The pointer cannot be NULL. It's recommended to use a global variable to store the Model Name.
 */
uint8_t *iap2_get_model_name(void);

/**
 * @brief     This is a user-defined API that returns the Firmware Version.
 * @param[in] None.
 * @return    A pointer to the Firmware Version. The pointer cannot be NULL. It's recommended to use a global variable to store the Firmware Version.
 */
uint8_t *iap2_get_fw_version(void);

/**
 * @brief     This is a user-defined API that returns the Hardware Version.
 * @param[in] None.
 * @return    A pointer to the Hardware Version. The pointer cannot be NULL. It's recommended to use a global variable to store the Hardware Version.
 */
uint8_t *iap2_get_hw_version(void);

/**
 * @brief     This is a user-defined API that returns the MAX length of TX Queue.
 * @param[in] None.
 * @return    A pointer to the MAX length of TX Queue.
 */
uint8_t iap2_get_tx_queue_max_length(void);


/**
 * @brief     This is a user-defined API that returns the iAP2 sync payload.
 * @param[in] None.
 * @return    A pointer to the iAP2 sync payload. The pointer cannot be NULL. It's recommended to use a global variable to store the iAP2 sync payload.
 */
iap2_sync_payload_t *iap2_get_sync_payload(void);

/**
 * @brief     This is a user-defined API that returns the iAP2 identification parameters.
 * @param[in] None.
 * @return    A pointer to the iAP2 identification parameters.. The pointer cannot be NULL. It's recommended to use a global variable to store the iAP2 identification parameters.
 */
uint8_t const *iap2_get_identification_parameters(void);

/**
* @brief           This function releases the AP2 control seesion or ea session packet  after it is consumed.
* @param[in]    session_type  is the iAP2 data packet type, control session or ea session.
* @param[in]    data  is the initialization parameter. The value is provided once it is called by the iAP2.
* @return         None.
*/
void iap2_release_data(iap2_session_type_t session_type, uint8_t *data);

/**
* @brief           This function for getting IAP2 team ID for APP match.
* @param[in]   None
* @return         A pointer to IAP2 team ID.
*/
uint8_t *iap2_get_team_id(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 * @}
 */
#endif /*__IAP2_H__*/



