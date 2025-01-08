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
#include "bt_callback_manager.h"
#include "iAP2_spp.h"
#include "iAP2_utils.h"
#include "iAP2_log.h"
#include "iAP2_task.h"

bt_iap2_spp_cntx_t iap2_spp_cntx = {{0}};
static bool g_need_resend = false;

extern bt_status_t bt_iap2_sdp_event_callback_register(void);
extern int32_t iap2_event_callback_handler(iap2_event_t event_id, void *param);

extern iap2_node_t *iap2_rx_head;
extern iap2_node_t *iap2_tx_head;
extern bt_status_t iap2_rho_init(void);
extern bt_bd_addr_t *bt_rfcomm_get_bd_address(void *channel);

bt_status_t bt_iap2_init(void)
{
    bt_status_t result = BT_STATUS_SUCCESS;

    do {
        /* 1. Init context. */
        memset(&iap2_spp_cntx, 0, sizeof(bt_iap2_spp_cntx_t));

        /* 2. Init SDP record. */
        result = bt_iap2_sdp_event_callback_register();

        if (result != BT_STATUS_SUCCESS) {
            break;
        }

        /* 3. Register callback. */
        result = bt_callback_manager_register_callback(
            bt_callback_type_app_event,
            MODULE_MASK_SPP,
            bt_iap2_event_callback);

        if (result != BT_STATUS_SUCCESS) {
            break;
        }

        /* 4. Init RHO. */
#ifdef BT_ROLE_HANDOVER_WITH_SPP_BLE
        result = iap2_rho_init();

        if (result != BT_STATUS_SUCCESS) {
            break;
        }
#endif
    } while (0);

    iap2_report_id(IAP2_SPP_002, 1, result);

    return result;
}

bt_status_t bt_iap2_connect(
    uint32_t *handle,
    const bt_bd_addr_t *address,
    const uint8_t *uuid128)
{
    bt_status_t status = 0;
    uint8_t addr[6] = {0};

    if ((0 == iap2_memcmp((iap2_spp_cntx.bt_addr), &addr, 6) && (iap2_spp_cntx.spp_handle == BT_SPP_INVALID_HANDLE)) ||
        ((0 == iap2_memcmp(address, &(iap2_spp_cntx.bt_addr), 6)) && (0 == iap2_spp_cntx.linkInfo.state))) {
        status = bt_spp_connect(&iap2_spp_cntx.spp_handle, address, uuid128);
        if (BT_STATUS_SUCCESS == status) {
            *handle = iap2_spp_cntx.spp_handle;
            iap2_spp_cntx.linkInfo.state = IAP2_STATE_TRANSPORT_CONNECTING;
        } else {
            *handle = 0;
        }
    } else {
        status = BT_STATUS_FAIL;
        //iap2_report("[IAP2]bt_iap2_connect fail, not first conencted and not reconnect!\r\n");
        iap2_report_id(IAP2_SPP_003, 0);
    }

    //iap2_report("[IAP2]bt_iap2_connect, status: 0x%x\r\n", status);
    iap2_report_id(IAP2_SPP_004, 1, status);
    return status;
}

bt_status_t bt_iap2_disconnect(uint32_t handle)
{
    return bt_spp_disconnect(handle);
}

bt_status_t bt_iap2_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{
    //iap2_report("[IAP2]bt_iap2_event_callback, msg: 0x%4x, status: 0x%4x\r\n", msg, status);
    iap2_report_id(IAP2_SPP_005, 2, msg, status);
    switch (msg) {
        case BT_SPP_CONNECT_IND: {
            bt_spp_connect_ind_t *conn_ind_p = (bt_spp_connect_ind_t *)buff;
            //iap2_report("[IAP2]BT_SPP_CONNECT_IND, handle: 0x%4x, channel_id: %d\r\n",
            //    conn_ind_p->handle, conn_ind_p->local_server_id);
            iap2_report_id(IAP2_SPP_006, 2, conn_ind_p->handle, conn_ind_p->local_server_id);

            if (BT_SPP_IAP2_SERVER_ID == conn_ind_p->local_server_id) {
                if (iap2_spp_cntx.spp_handle != BT_SPP_INVALID_HANDLE && iap2_spp_cntx.spp_handle != conn_ind_p->handle) {
                    bt_spp_connect_response(conn_ind_p->handle, false);
                    break;
                }
                iap2_spp_cntx.spp_handle = conn_ind_p->handle;
                iap2_spp_cntx.server_channel_id = conn_ind_p->local_server_id;
                memcpy(iap2_spp_cntx.bt_addr, conn_ind_p->address, BT_BD_ADDR_LEN);
                bt_spp_connect_response(iap2_spp_cntx.spp_handle, true);
            }
        }
        break;

        case BT_SPP_CONNECT_CNF: {/* transport connection is established. */
            bt_spp_connect_cnf_t *conn_cnf_p = (bt_spp_connect_cnf_t *)buff;
            if (iap2_spp_cntx.spp_handle == conn_cnf_p->handle) {
                if (BT_STATUS_SUCCESS != status) {
                    /* notify app connected fail*/
                    iap2_connect_ind_t iap2_connect = {0};
                    bt_bd_addr_t empty_bd_addr = {0};
                    iap2_connect.status = status;
                    iap2_connect.handle = (uint32_t)conn_cnf_p->handle;
                    iap2_connect.max_packet_length = 0;
                    iap2_connect.address = bt_rfcomm_get_bd_address((void *)conn_cnf_p->handle);
                    if (0 != memcmp(iap2_connect.address, &iap2_spp_cntx.bt_addr, sizeof(bt_bd_addr_t)) &&
                        0 != memcmp(&iap2_spp_cntx.bt_addr, &empty_bd_addr, sizeof(bt_bd_addr_t))) {
                        iap2_report_id(IAP2_SPP_013, 1, status);
                        break;
                    }
                    iap2_event_callback_handler(IAP2_CONNECT_IND, (void *)&iap2_connect);

                    iap2_clear_linkInfo(iap2_spp_cntx.spp_handle);
                    memset(&iap2_spp_cntx, 0, sizeof(bt_iap2_spp_cntx_t));
                    iap2_spp_cntx.spp_handle = BT_SPP_INVALID_HANDLE;
                } else {
                    iap2_memcpy(&iap2_spp_cntx.bt_addr, bt_rfcomm_get_bd_address((void *)iap2_spp_cntx.spp_handle), sizeof(bt_bd_addr_t));
                    iap2_link_info_t *linkinfo = iap2_get_link_info(iap2_spp_cntx.spp_handle);
                    if (linkinfo) {
                        linkinfo->state = IAP2_STATE_TRANSPORT_CONNECTED;
                        iap2_spp_cntx.max_packet_size = conn_cnf_p->max_packet_length;
                        iap2_spp_cntx.server_channel_id = conn_cnf_p->server_id;
                        iap2_get_sync_payload()->max_packet_length = bswap16(iap2_spp_cntx.max_packet_size);
                        if (0 != iap2_start_link(iap2_spp_cntx.spp_handle)) {
                            g_need_resend = true;
                        }
                    } else {
                        //iap2_report("[IAP2]BT_SPP_CONNECT_CNF, link info cannot find!\r\n");
                        iap2_report_id(IAP2_SPP_007, 0);
                    }
                }
            } else {
                iap2_report_id(IAP2_SPP_008, 0);
            }
        }
        break;

        case BT_SPP_DISCONNECT_IND: {
            bt_spp_disconnect_ind_t *disc_ind_p = (bt_spp_disconnect_ind_t *)buff;
            if (iap2_spp_cntx.spp_handle == disc_ind_p->handle) {
                /* notify app disconencted*/
                iap2_disconnect_ind_t iap2_disconnect = {0};
                iap2_disconnect.handle = (uint32_t)iap2_spp_cntx.spp_handle;
                iap2_event_callback_handler(IAP2_DISCONNECT_IND, (void *)&iap2_disconnect);

                iap2_clear_rx_node_list(iap2_get_rx_head());
                iap2_clear_tx_node_list(iap2_get_tx_head());
                iap2_rx_head = NULL;
                iap2_tx_head = NULL;
                iap2_clear_linkInfo(iap2_spp_cntx.spp_handle);
                memset(&iap2_spp_cntx, 0, sizeof(bt_iap2_spp_cntx_t));
                iap2_spp_cntx.spp_handle = BT_SPP_INVALID_HANDLE;
                //iap2_set_timer_float(20);
            } else {
                //iap2_report("[IAP2]BT_SPP_DISCONNECT_IND, Wrong spp handle!\r\n");
                iap2_report_id(IAP2_SPP_009, 0);
            }
        }
        break;

        case BT_SPP_DATA_RECEIVED_IND: {
            bt_spp_data_received_ind_t *data_ind_p = (bt_spp_data_received_ind_t *)buff;
            if (iap2_spp_cntx.spp_handle == data_ind_p->handle) {
                //iap2_report("[IAP2]bt_iap2_event_callback, recieved data point: 0x%4x\r\n", data_ind_p->packet);
                iap2_report_id(IAP2_SPP_010, 1, data_ind_p->packet);
                iap2_rx_data_handler(iap2_spp_cntx.spp_handle, data_ind_p->packet, data_ind_p->packet_length);
            }
        }
        break;

        case BT_SPP_READY_TO_SEND_IND: {
            bt_spp_ready_to_send_ind_t *ready_send_p = (bt_spp_ready_to_send_ind_t *)buff;
            if (iap2_spp_cntx.spp_handle == ready_send_p->handle) {
                if (g_need_resend) {
                    g_need_resend = false;
                    iap2_start_link(iap2_spp_cntx.spp_handle);
                } else {// notify app to send data again
                    iap2_ready_to_send_ind_t ready_send = {0};
                    ready_send.handle = iap2_spp_cntx.spp_handle;
                    iap2_event_callback_handler(IAP2_READY_TO_SEND_IND, (void *)&ready_send);
                }
            }
        }
        break;

        default:
            break;
    }

    return BT_STATUS_SUCCESS;
}

iap2_link_info_t *bt_iap2_get_link_info(uint32_t handle)
{
    if (handle == iap2_spp_cntx.spp_handle) {
        return &(iap2_spp_cntx.linkInfo);
    }
    return NULL;
}

uint32_t bt_iap2_get_link_handle(void)
{
    return iap2_spp_cntx.spp_handle;
}

uint16_t bt_iap2_get_link_mtu(void)
{
    return iap2_spp_cntx.max_packet_size;
}

int32_t bt_iap2_send_data(uint32_t handle, uint8_t *packet, uint16_t packet_size)
{
    uint16_t send_length = 0;
    bool need_resend = false;
    int32_t result = 0;

    if (iap2_spp_cntx.max_packet_size < packet_size) {
        //if (650 < packet_size) {
        //send_length = 650;
        send_length = iap2_spp_cntx.max_packet_size;
        need_resend = true;
        result = bt_spp_send(handle, packet, send_length);
        if ((0 == result) && (need_resend)) {
            need_resend = false;
            result = bt_spp_send(handle, (uint8_t *)(packet + send_length), (packet_size - send_length));
        }
    } else {
        result = bt_spp_send(handle, packet, packet_size);
    }

    return result;
}

void bt_iap2_hold_data(uint8_t *packet)
{
    //iap2_report("[IAP2]bt_iap2_hold_data, hold data point: 0x%4x\r\n", packet);
    iap2_report_id(IAP2_SPP_011, 1, packet);
    bt_spp_hold_data(packet);
}

void bt_iap2_release_data(uint8_t *packet)
{
    //iap2_report("[IAP2]bt_iap2_release_data, hold data point: 0x%4x\r\n", packet);
    iap2_report_id(IAP2_SPP_012, 1, packet);
    bt_spp_release_data(packet);

}


#endif



