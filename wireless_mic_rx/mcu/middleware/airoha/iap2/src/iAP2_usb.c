/* Copyright Statement:
 *
 * (C) 2023  Airoha Technology Corp. All rights reserved.
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

#include "iAP2_usb.h"
#include "iAP2_task.h"

#include <FreeRTOS.h>
#include <queue.h>

static iap2_usb_context_t g_iap2_usb_context;
extern QueueHandle_t iap2_service_queue;

static void iap2_usb_rx_callback(uint8_t len, uint8_t *data);

iap2_status_t iap2_usb_init(void)
{
    memset(&g_iap2_usb_context, 0, sizeof(iap2_usb_context_t));
    USB_MFI_Register_Rx_Callback(iap2_usb_rx_callback);

    return IAP2_STATUS_SUCCESS;
}

void iap2_usb_config_done(void)
{
    iap2_link_info_t *linkInfo = iap2_get_link_info(IAP2_USB_LINK_INDEX);

    if (linkInfo != NULL) {
        linkInfo->state = IAP2_STATE_TRANSPORT_CONNECTED;
        iap2_get_sync_payload()->max_packet_length = bswap16(IAP2_USB_MAX_PACKET_SIZE);
        iap2_start_link(IAP2_USB_LINK_INDEX);
    }
}

iap2_status_t iap2_usb_send_data(uint32_t linkIndex, uint8_t *packet, uint16_t packet_size)
{
    if (linkIndex != IAP2_USB_LINK_INDEX) {
        return IAP2_STATUS_FAIL;
    }

    if (USB_MFI_TX_SendData(packet_size, packet) != USB_MFI_STATUS_OK) {
        return IAP2_STATUS_FAIL;
    }

    return IAP2_STATUS_SUCCESS;
}

iap2_link_info_t *iap2_usb_get_link_info(uint32_t linkIndex)
{
    return (linkIndex != IAP2_USB_LINK_INDEX) ? NULL : &g_iap2_usb_context.linkInfo;
}

uint32_t iap2_usb_get_link_index(void)
{
    return IAP2_USB_LINK_INDEX;
}

void iap2_usb_hold_data(uint8_t *data)
{
    iap2_usb_packet_t *packet = IAP2_USB_DATA_TO_PACKET(data);

    if (packet != NULL) {
        packet->reference_count++;
    }
}

void iap2_usb_release_data(uint8_t *data)
{
    iap2_usb_packet_t *packet = IAP2_USB_DATA_TO_PACKET(data);

    if (packet != NULL) {
        if (--packet->reference_count == 0) {
            iap2_memory_free(packet);
        }
    }
}
static void iap2_usb_rx_callback(uint8_t len, uint8_t *data)
{
    iap2_task_message_t message = {0};
    iap2_usb_packet_t *packet = iap2_memory_alloc(sizeof(iap2_usb_packet_t) + len);

    if (packet == NULL) {
        return;
    }

    packet->reference_count = 1;
    memcpy(packet->data, data, len);

    message.msg_type = IAP2_TASK_MESSAGE_USB_RX;
    message.data.usb.linkIndex = IAP2_USB_LINK_INDEX;
    message.data.usb.packet = packet;
    message.data.usb.length = len;

    xQueueSendFromISR(iap2_service_queue, &message, 0);
}

