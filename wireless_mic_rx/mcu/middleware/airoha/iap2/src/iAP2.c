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

#ifdef MTK_IAP2_PROFILE_ENABLE

#include "bt_spp.h"
#include "iAP2_spec.h"
#include "iAP2_utils.h"
#include "iAP2_spp.h"
#include "iAP2_usb.h"
#include "iAP2_log.h"
#include "iAP2_task.h"
#ifdef SUPPORT_ROLE_HANDOVER_SERVICE
#include "bt_role_handover.h"
#endif
#include "bt_utils.h"

extern void bt_os_take_stack_mutex(void);
extern void bt_os_give_stack_mutex(void);

typedef struct {
    bool in_use;
    iap2_notify_callback callback;
} iap2_srv_callback_node_t;

static uint8_t const g_IAP2_uuid128_default[16] = {
    0x00, 0x00, 0x00, 0x00, 0xDE, 0xCA, 0xFA, 0xDE, 0xDE, 0xCA, 0xDE, 0xAF, 0xDE, 0xCA, 0xCA, 0xFE
};

static iap2_srv_callback_node_t app_cb_list[IAP2_APP_SUPPORT_CB_MAX_NUM] = {{0}};

//static uint32_t iap2_tx_mutex;
extern bt_iap2_spp_cntx_t iap2_spp_cntx;
extern uint32_t iap2_mutex;
extern iap2_node_t *iap2_rx_head;
extern iap2_node_t *iap2_tx_head;

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_iap2_get_app_bundle_id=_default_iap2_get_app_bundle_id")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak iap2_get_app_launch_param = default_iap2_get_app_launch_param
#else
#error "Unsupported Platform"
#endif

uint8_t *default_iap2_get_app_launch_param(uint16_t *len)
{
    *len = 0;
    return NULL;
}

iap2_status_t iap2_init(void)
{
    /* 1. Init mutex. */
    if (iap2_mutex == 0) {
        iap2_mutex = iap2_create_mutex();
    }

    /* 2. Init list. */
    if (iap2_rx_head == NULL) {
        iap2_rx_head = iap2_get_rx_head();
    }

    if (iap2_tx_head == NULL) {
        iap2_tx_head = iap2_get_tx_head();
    }

    if ((!iap2_rx_head) || (!iap2_tx_head)) {
        iap2_report_id(IAP2_SPP_001, 0);
    }

    /* 3. Init sync payload. */
    iap2_sync_payload_init();

    /* 4. Init transport. */
    if (BT_STATUS_SUCCESS != bt_iap2_init()) {
        return IAP2_STATUS_FAIL;
    }

#ifdef AIR_USB_MFI_ENABLE
    if (IAP2_STATUS_SUCCESS!= iap2_usb_init()) {
        return IAP2_STATUS_FAIL;
    }
#endif

    /* 5. Init task. */
    iap2_task_init();

    return IAP2_STATUS_SUCCESS;
}

iap2_status_t iap2_connect(uint32_t *handle, const bt_bd_addr_t *address)
{
    iap2_status_t status = 0;

    bt_utils_assert(address && "NULL address");
#if defined(MTK_AWS_MCE_ENABLE) && defined (SUPPORT_ROLE_HANDOVER_SERVICE)
    if (BT_ROLE_HANDOVER_STATE_ONGOING == bt_role_handover_get_state()) {
        return IAP2_STATUS_FAIL;
    }
#endif

    /** using SPP as Transport. */
    status = bt_iap2_connect(handle, address, (const uint8_t *)(&g_IAP2_uuid128_default));
    //iap2_report("[IAP2]iap2_connect, status: 0x%x\r\n", status);
    iap2_report_id(IAP2_001, 1, status);
    if (0 != status) {
        status = IAP2_STATUS_FAIL;
    }
    return status;
}

iap2_status_t iap2_disconnect(uint32_t handle)
{
    iap2_status_t status = 0;
    iap2_link_info_t *iap2LinkInfo = iap2_get_link_info(handle);

    if (NULL != iap2LinkInfo) {
        //iap2_report("[IAP2]iap2_disconnect, iap2_state: %d\r\n", iap2LinkInfo->state);
        iap2_report_id(IAP2_002, 1, iap2LinkInfo->state);
        if (iap2LinkInfo->state != IAP2_STATE_TRANSPORT_DISCONNECTED
#ifdef AIR_USB_MFI_ENABLE
            && handle != IAP2_USB_LINK_INDEX
#endif
        ) {
            status = bt_iap2_disconnect(handle);
            if (BT_STATUS_SUCCESS == status) {
                iap2LinkInfo->state = IAP2_STATE_TRANSPORT_DISCONNECTED;
            }
        }
    } else {
        return IAP2_STATUS_INVALID_HANDLE;
    }

    if (0 != status) {
        status = IAP2_STATUS_FAIL;
    }
    return status;
}

iap2_status_t iap2_register_callback(iap2_notify_callback callback)
{
    uint8_t i = 0;
    iap2_status_t status = 0;
    //iap2_report("[iAP2]register_cb callback %x\r\n", callback);
    iap2_report_id(IAP2_003, 1, callback);

    for (i = 0; i < IAP2_APP_SUPPORT_CB_MAX_NUM; i++) {
        if (!app_cb_list[i].in_use) {
            app_cb_list[i].callback = callback;
            app_cb_list[i].in_use = true;
            break;
        }
    }
    if (i == IAP2_APP_SUPPORT_CB_MAX_NUM) {
        //iap2_report("[iAP2]all are in use, please extend the value of IAP2_APP_SUPPORT_CB_MAX_NUM\r\n");
        iap2_report_id(IAP2_004, 0);
        status = IAP2_STATUS_FAIL;
    }
    return status;
}

iap2_status_t iap2_deregister_callback(iap2_notify_callback callback)
{
    uint8_t i = 0;
    iap2_status_t status = 0;

    //iap2_report("[iAP2]deregister_cb callback %x\r\n", callback);
    iap2_report_id(IAP2_005, 1, callback);

    for (i = 0; i < IAP2_APP_SUPPORT_CB_MAX_NUM; i++) {
        if (app_cb_list[i].in_use && app_cb_list[i].callback == callback) {
            app_cb_list[i].callback = NULL;
            app_cb_list[i].in_use = false;
            break;
        }
    }
    if (i == IAP2_APP_SUPPORT_CB_MAX_NUM) {

        //iap2_report("[iAP2]delete fail, because of not find the callback\r\n");
        iap2_report_id(IAP2_006, 0);
        status = IAP2_STATUS_FAIL;
    }

    return status;

}

iap2_status_t iap2_send_data_by_external_accessory_session(uint32_t handle, uint16_t session_id, uint8_t *data, uint16_t length)
{
    iap2_status_t status = 0;

    if (handle == IAP2_INVALID_HANDLE) {
        return IAP2_STATUS_INVALID_HANDLE;
    }
    //status = iap2_send_ea_session_data(handle, session_id, data, length);

    //iap2_take_mutex(iap2_tx_mutex);
    bt_os_take_stack_mutex();
    status = iap2_send_data_pre_check(handle, session_id, data, length);
    //iap2_report("[IAP2] iap2_send_data_by_external_accessory_session, status: 0x%x\r\n", status);
    iap2_report_id(IAP2_007, 1, status);

    if (status == BT_STATUS_SPP_TX_NOT_AVAILABLE) {
        //iap2_give_mutex(iap2_tx_mutex);
        status = IAP2_STATUS_TX_NOT_AVAILABLE;
    } else if (status != 0) {
        //iap2_give_mutex(iap2_tx_mutex);
        status = IAP2_STATUS_FAIL;
    }

    //iap2_give_mutex(iap2_tx_mutex);
    bt_os_give_stack_mutex();
    return status;
}

iap2_status_t iap2_send_data_by_control_session(uint32_t handle, uint16_t message_id, uint8_t *data, uint16_t length)
{
    iap2_status_t status = 0;

    if (handle == IAP2_INVALID_HANDLE) {
        return IAP2_STATUS_INVALID_HANDLE;
    }
    status = iap2_send_ctrl_session_data(handle, message_id, data, length);
    //iap2_report("[IAP2] iap2_send_data_by_control_session, status: 0x%x\r\n", status);
    iap2_report_id(IAP2_008, 1, status);

    if (BT_STATUS_SPP_TX_NOT_AVAILABLE == status) {
        return IAP2_STATUS_TX_NOT_AVAILABLE;
    } else if (0 != status) {
        status = IAP2_STATUS_FAIL;
    }
    return status;
}

iap2_status_t iap2_send_app_launch_request(uint32_t handle, uint8_t *app_id, bool is_alert)
{
    if (app_id == NULL || handle == 0) {
        return IAP2_STATUS_FAIL;
    }
    iap2_app_launch_method_t method = LAUNCH_WITH_USER_ALERT;
    uint32_t app_id_length = iap2_strlen((char *)app_id) + 1; /* null terminal string */
    uint16_t total_data_len = sizeof(iap2_param_header_t) + app_id_length  + sizeof(iap2_param_header_t) + sizeof((uint8_t)is_alert);
    uint8_t *data = (uint8_t *)iap2_memory_alloc(total_data_len);
    if (data == NULL) {
        iap2_report_id(IAP2_012, 0);
        return IAP2_STATUS_OUT_OF_MEMORY;
    }
    uint8_t *ptr = data;
    ((iap2_param_t *)(ptr))->param_length = bswap16(sizeof(iap2_param_header_t) + app_id_length);
    ((iap2_param_t *)(ptr))->param_id = bswap16((uint16_t)0);
    iap2_memcpy(((iap2_param_t *)ptr)->param, app_id, app_id_length - 1);
    ((iap2_param_t *)ptr)->param[app_id_length - 1] = 0; /* null terminal string */
    ptr += (app_id_length + sizeof(iap2_param_header_t));
    ((iap2_param_t *)(ptr))->param_length = bswap16(sizeof(iap2_param_header_t) + sizeof((uint8_t)is_alert));
    ((iap2_param_t *)(ptr))->param_id = bswap16((uint16_t)1);
    if (is_alert) {
        method = LAUNCH_WITH_USER_ALERT;
    } else {
        method = LAUNCH_WITHOUT_USER_ALERT;
    }

    ((iap2_param_t *)ptr)->param[0] = (uint8_t)method;
    iap2_status_t status = iap2_send_data_by_control_session(handle, IAP2_CTRL_REQUEST_APP_LAUNCH, data, total_data_len);
    iap2_report_id(IAP2_013, 2, status, is_alert);
    iap2_memory_free(data);

    return IAP2_STATUS_SUCCESS;
}

int32_t iap2_event_callback_handler(iap2_event_t event_id, void *param)
{
    uint8_t i = 0;
    int32_t ret = 0;

    for (i = 0; i < IAP2_APP_SUPPORT_CB_MAX_NUM; i++) {
        if (app_cb_list[i].in_use && app_cb_list[i].callback != NULL) {
            app_cb_list[i].callback(event_id, param);
            ret = 0;
        }
    }
    return ret;
}

void iap2_event_callback(uint32_t linkIndex, iap2_evt_t event, void *param)
{
    //iap2_report("[IAP2] iap2_event_callback, event: %d\r\n", event);
    iap2_report_id(IAP2_009, 1, event);
    switch (event) {
        case IAP2_EVT_CONNECTED: {
            /* notify app conencted*/
            iap2_connect_ind_t iap2_connect = {0};
            iap2_connect.status = IAP2_STATUS_SUCCESS;
            iap2_connect.handle = (uint32_t)iap2_spp_cntx.spp_handle;
            iap2_connect.max_packet_length = iap2_spp_cntx.max_packet_size;
            iap2_connect.address = (bt_bd_addr_t *)&iap2_spp_cntx.bt_addr;

            iap2_event_callback_handler(IAP2_CONNECT_IND, (void *)&iap2_connect);
        }
        break;

        case IAP2_EVT_DISCONNECTED: {
            /* notify app disconencted*/
            iap2_disconnect_ind_t iap2_disconnect = {0};
            iap2_disconnect.handle = (uint32_t)iap2_spp_cntx.spp_handle;
            iap2_event_callback_handler(IAP2_DISCONNECT_IND, (void *)&iap2_disconnect);

        }
        break;

        case IAP2_EVT_EA_SESSION_START: {
            iap2_ea_session_op_t *ea_start = (iap2_ea_session_op_t *)param;
            iap2_ea_session_open_close_t ea_open = {0};
            ea_open.protocol_id = ea_start->protocol_id;
            ea_open.session_id = ea_start->session_id;
            iap2_event_callback_handler(IAP2_EA_SESSION_OPEN_IND, (void *)&ea_open);
        }
        break;

        case IAP2_EVT_EA_SESSION_STOP: {
            iap2_ea_session_op_t *ea_stop = (iap2_ea_session_op_t *)param;
            iap2_ea_session_open_close_t ea_close = {0};
            ea_close.protocol_id = ea_stop->protocol_id;
            ea_close.session_id = ea_stop->session_id;
            iap2_event_callback_handler(IAP2_EA_SESSION_CLOSE_IND, (void *)&ea_close);
        }
        break;

        case IAP2_EVT_DATA_RECIEVED: {
            iap2_data_received_t *data_recieve = (iap2_data_received_t *)param;
            iap2_data_received_ind_t iap2_data_rx = {0};
            iap2_data_rx.handle = iap2_spp_cntx.spp_handle;
            iap2_data_rx.packet = data_recieve->data;
            iap2_data_rx.packet_length = data_recieve->length;
            if (IAP2_SESSION_TYPE_CONTROL == data_recieve->session_t) {//ctrl session data
                iap2_data_rx.session_type = IAP2_SESSION_TYPE_CONTROL;
                iap2_data_rx.message_id = data_recieve->message_id;
            } else if (IAP2_SESSION_TYPE_EXTERNAL_ACCESSORY == data_recieve->session_t) {//ea session data
                iap2_data_rx.session_type = IAP2_SESSION_TYPE_EXTERNAL_ACCESSORY;
                iap2_data_rx.session_id = data_recieve->session_id;
            }
            iap2_event_callback_handler(IAP2_RECIEVED_DATA_IND, (void *)&iap2_data_rx);
            break;
        }

        default:
            break;
    }
}

void iap2_release_data(iap2_session_type_t session_type, uint8_t *data)
{
    if (IAP2_SESSION_TYPE_CONTROL == session_type) {
        iap2_release_ctrl_session_data(data);
    } else if (IAP2_SESSION_TYPE_EXTERNAL_ACCESSORY == session_type) {
        iap2_release_ea_session_data(data);
    } else {
        //iap2_report("[IAP2] iap2_release_data, session type %d is not support!\r\n", session_type);
        iap2_report_id(IAP2_011, 1, session_type);
    }

}


#endif  /* MTK_IAP2_PROFILE_ENABLE */


