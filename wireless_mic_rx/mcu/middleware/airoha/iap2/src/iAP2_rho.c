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
#include "iAP2_log.h"
#include "iAP2_spp.h"
#include "iAP2_spec.h"
#include "iAP2_utils.h"
#ifdef BT_ROLE_HANDOVER_WITH_SPP_BLE
#include "bt_role_handover.h"
#include "bt_spp.h"

BT_PACKED(
typedef struct {
    //uint8_t  bt_addr[BT_BD_ADDR_LEN]; // provided by RHO Service
    uint16_t server_channel_id;
    uint16_t max_packet_size;
    //uint32_t spp_handle; // update in new Agent

    //iap2_state_t state; // judge from data length
    //iap2_state_var_t stateVar; // only used in connecting
    uint8_t txSEQ;
    uint8_t rxSEQ;
    uint8_t rxCumulative;
    uint8_t maxCumulative;
    uint8_t lastAckPSN;
    uint8_t SNWindowRange;
    uint16_t rxCumulativeTimeout;
    //TimerHandle_t rxCumulativeTimer; // local timer
    //uint8_t protocolIdentifier; // only used in EA session start and stop
    //uint8_t protocolSessionIdentifier; // only used in EA session start and stop
    uint16_t max_packet_length;
    uint16_t retransmission_timeout;

    //uint8_t upper_data[1];
}) iap2_rho_context_t;

bt_status_t iap2_rho_allow_execution(const bt_bd_addr_t *address);
uint8_t iap2_rho_get_data_length(const bt_bd_addr_t *address);
bt_status_t iap2_rho_get_data(const bt_bd_addr_t *address, void *data);
bt_status_t iap2_rho_update(bt_role_handover_update_info_t *info);
void iap2_rho_status_callback(const bt_bd_addr_t *address, bt_aws_mce_role_t role, bt_role_handover_event_t event, bt_status_t status);

bt_status_t iap2_rho_allow_execution_ext(const bt_bd_addr_t *address);
uint8_t iap2_rho_get_data_length_ext(const bt_bd_addr_t *address);
bt_status_t iap2_rho_get_data_ext(const bt_bd_addr_t *address, void *data);
bt_status_t iap2_rho_update_ext(iap2_connect_ind_t *ind, bt_aws_mce_role_t role, void *data);

bt_status_t default_iap2_rho_allow_execution_ext(const bt_bd_addr_t *address)
{
    return BT_STATUS_SUCCESS;
}

uint8_t default_iap2_rho_get_data_length_ext(const bt_bd_addr_t *address)
{
    return 0;
}

bt_status_t default_iap2_rho_get_data_ext(const bt_bd_addr_t *address, void *data)
{
    return BT_STATUS_SUCCESS;
}

bt_status_t default_iap2_rho_update_ext(iap2_connect_ind_t *ind, bt_aws_mce_role_t role, void *data)
{
    return BT_STATUS_SUCCESS;
}

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename_iap2_rho_allow_execution_ext=_default_iap2_rho_allow_execution_ext")
#pragma comment(linker, "/alternatename_iap2_rho_get_data_length_ext=_default_iap2_rho_get_data_length_ext")
#pragma comment(linker, "/alternatename_iap2_rho_get_data_ext=_default_iap2_rho_get_data_ext")
#pragma comment(linker, "/alternatename_iap2_rho_update_ext=_default_iap2_rho_update_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak iap2_rho_allow_execution_ext = default_iap2_rho_allow_execution_ext
#pragma weak iap2_rho_get_data_length_ext = default_iap2_rho_get_data_length_ext
#pragma weak iap2_rho_get_data_ext = default_iap2_rho_get_data_ext
#pragma weak iap2_rho_update_ext = default_iap2_rho_update_ext
#else
#error "Unsupported Platform"
#endif

extern bt_iap2_spp_cntx_t iap2_spp_cntx;

bt_status_t iap2_rho_init(void)
{
    bt_role_handover_callbacks_t callbacks = {
        .allowed_cb = iap2_rho_allow_execution,
        .get_len_cb = iap2_rho_get_data_length,
        .get_data_cb = iap2_rho_get_data,
        .update_cb = iap2_rho_update,
        .status_cb = iap2_rho_status_callback
    };

    bt_role_handover_register_callbacks(BT_ROLE_HANDOVER_MODULE_IAP2, &callbacks);
    return BT_STATUS_SUCCESS;
}

bt_status_t iap2_rho_allow_execution(const bt_bd_addr_t *address)
{
    bt_status_t allow_execution = BT_STATUS_SUCCESS;
    bt_status_t allow_execution_ext = iap2_rho_allow_execution_ext(address);

    if ((iap2_spp_cntx.linkInfo.state != IAP2_STATE_LINK_ESTABLISHED) &&
        (iap2_spp_cntx.linkInfo.state != IAP2_STATE_TRANSPORT_DISCONNECTED)) {
        allow_execution = BT_STATUS_PENDING;
    }

    iap2_report_id(IAP2_RHO_001, 2, allow_execution, allow_execution_ext);

    if ((allow_execution == BT_STATUS_SUCCESS) && (allow_execution_ext == BT_STATUS_SUCCESS)) {
        return BT_STATUS_SUCCESS;
    } else if ((allow_execution == BT_STATUS_PENDING) || (allow_execution_ext == BT_STATUS_PENDING)) {
        return BT_STATUS_PENDING;
    } else {
        return BT_STATUS_FAIL;
    }
}

uint8_t iap2_rho_get_data_length(const bt_bd_addr_t *address)
{
    uint8_t data_length = 0;
    if (address == NULL) {
        return 0;
    }
    if ((iap2_spp_cntx.linkInfo.state == IAP2_STATE_LINK_ESTABLISHED) &&
        (0 == memcmp(iap2_spp_cntx.bt_addr, address, sizeof(bt_bd_addr_t)))) {
        data_length = sizeof(iap2_rho_context_t) + iap2_rho_get_data_length_ext(address);
    }

    iap2_report_id(IAP2_RHO_002, 1, data_length);
    return data_length;
}

bt_status_t iap2_rho_get_data(const bt_bd_addr_t *address, void *data)
{
    bt_status_t status = BT_STATUS_SUCCESS;
    if (address == NULL) {
        return BT_STATUS_FAIL;
    }
    iap2_rho_context_t *rho_context = (iap2_rho_context_t *)data;

    if ((rho_context != NULL) && (iap2_spp_cntx.linkInfo.state == IAP2_STATE_LINK_ESTABLISHED)
        && (0 == memcmp(iap2_spp_cntx.bt_addr, address, sizeof(bt_bd_addr_t)))) {
        rho_context->max_packet_size = iap2_spp_cntx.max_packet_size;
        rho_context->server_channel_id = iap2_spp_cntx.server_channel_id;

        rho_context->txSEQ = iap2_spp_cntx.linkInfo.txSEQ;
        rho_context->rxSEQ = iap2_spp_cntx.linkInfo.rxSEQ;
        rho_context->rxCumulative = iap2_spp_cntx.linkInfo.rxCumulative;
        rho_context->maxCumulative = iap2_spp_cntx.linkInfo.maxCumulative;
        rho_context->lastAckPSN = iap2_spp_cntx.linkInfo.lastAckPSN;
        rho_context->SNWindowRange = iap2_spp_cntx.linkInfo.SNWindowRange;
        rho_context->rxCumulativeTimeout = iap2_spp_cntx.linkInfo.rxCumulativeTimeout;
        rho_context->max_packet_length = iap2_spp_cntx.linkInfo.max_packet_length;
        rho_context->retransmission_timeout = iap2_spp_cntx.linkInfo.retransmission_timeout;

        status = iap2_rho_get_data_ext(address, data + sizeof(iap2_rho_context_t));
    } else {
        status = BT_STATUS_FAIL;
    }

    iap2_report_id(IAP2_RHO_003, 1, status);
    return status;
}

bt_status_t iap2_rho_update(bt_role_handover_update_info_t *info)
{
    bt_status_t status = BT_STATUS_SUCCESS;

    if (info->role == BT_AWS_MCE_ROLE_AGENT) {
        iap2_memset(&iap2_spp_cntx, 0, sizeof(iap2_spp_cntx));
        status = iap2_rho_update_ext((void *)info->addr, info->role, NULL);
        iap2_report_id(IAP2_RHO_005, 0);
    } else if (info->role == BT_AWS_MCE_ROLE_PARTNER) {
        iap2_rho_context_t *rho_context = (iap2_rho_context_t *)info->data;
        iap2_report_id(IAP2_RHO_006, 0);

        if (rho_context != NULL) {
            iap2_spp_cntx.server_channel_id = rho_context->server_channel_id;
            iap2_spp_cntx.max_packet_size = rho_context->max_packet_size;
            iap2_spp_cntx.spp_handle = bt_spp_get_handle_by_local_server_id(info->addr, iap2_spp_cntx.server_channel_id);
            iap2_memcpy(&iap2_spp_cntx.bt_addr, info->addr, sizeof(bt_bd_addr_t));

            iap2_spp_cntx.linkInfo.state = IAP2_STATE_LINK_ESTABLISHED;
            iap2_spp_cntx.linkInfo.txSEQ = rho_context->txSEQ;
            iap2_spp_cntx.linkInfo.rxSEQ = rho_context->rxSEQ;
            iap2_spp_cntx.linkInfo.rxCumulative = rho_context->rxCumulative;
            iap2_spp_cntx.linkInfo.maxCumulative = rho_context->maxCumulative;
            iap2_spp_cntx.linkInfo.lastAckPSN = rho_context->lastAckPSN;
            iap2_spp_cntx.linkInfo.SNWindowRange = rho_context->SNWindowRange;
            iap2_spp_cntx.linkInfo.rxCumulativeTimeout = rho_context->rxCumulativeTimeout;
            iap2_spp_cntx.linkInfo.rxCumulativeTimer = 0;
            iap2_spp_cntx.linkInfo.protocolIdentifier = 0;
            iap2_spp_cntx.linkInfo.protocolSessionIdentifier = 0;
            iap2_spp_cntx.linkInfo.max_packet_length = rho_context->max_packet_length;
            iap2_spp_cntx.linkInfo.retransmission_timeout = rho_context->retransmission_timeout;
            //iap2_memcpy(&iap2_spp_cntx.linkInfo.stateVar, 0, sizeof(iap2_state_var_t));

            // update upper layer
            iap2_connect_ind_t ind = {
                .status = IAP2_STATUS_SUCCESS,
                .handle = iap2_spp_cntx.spp_handle,
                .max_packet_length = iap2_spp_cntx.max_packet_size,
                .address = (void *)info->addr
            };

            status = iap2_rho_update_ext(&ind, info->role, (void *)info->data + sizeof(iap2_rho_context_t));
        } else {
            status = BT_STATUS_FAIL;
            iap2_report_id(IAP2_RHO_007, 0);
        }
    } else {
        status = BT_STATUS_FAIL;
        iap2_report_id(IAP2_RHO_008, 1, info->role);
    }

    return status;
}

void iap2_rho_status_callback(const bt_bd_addr_t *address, bt_aws_mce_role_t role, bt_role_handover_event_t event, bt_status_t status)
{
    iap2_report_id(IAP2_RHO_009, 3, role, event, status);
}
#endif
#endif
