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

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "iAP2_task.h"
#include "syslog.h"
#include "iAP2_utils.h"
#include "task_def.h"
#include "iAP2_spec.h"
#include "iAP2_log.h"

QueueHandle_t iap2_service_queue;
static TaskHandle_t g_iap2_task_handle;
extern void iap2_control_session_handler(uint32_t linkIndex, uint8_t *dataPtr);

#if 0
void iap2_task_mfi_data_handler(uint32_t linkIndex, uint8_t *data, uint16_t data_len)
{
    iap2_report("[IAP2] iap2_task_mfi_data_handler, linkIndex: 0x%2x, data point is 0x%4x, length 0x%2x\r\n", linkIndex, data, data_len);
    iap2_task_message_t message;
    memset((void *) &message, 0, sizeof(iap2_task_message_t));

    message.msg_type = IAP2_TASK_MESSAGE_MFI;
    message.data.mfi.linkIndex = linkIndex;
    message.data.mfi.data = (uint8_t *)iap2_memory_alloc(data_len);
    if (message.data.mfi.data) {
        iap2_memcpy(message.data.mfi.data, data, data_len);
        iap2_report("[IAP2]iap2_task_mfi_data_handler message:0x%4x, length is 0x%2x\r\n", message.data.mfi.data, data_len);
        xQueueSend(iap2_service_queue, (void *)&message, 0);
    } else {
        iap2_report("[IAP2]iap2_task_mfi_data_handler, cannot alloc memory!\r\n");
        memset((void *) &message, 0, sizeof(iap2_task_message_t));
    }
    if (data) {
        iap2_memory_free(data);
        iap2_report("[IAP2] iap2_task_mfi_data_handler, free packet\r\n");
    }
}

/**
 * @brief          This function is for service task implement.
 * @param[in]  arg      .
 * @return       void.
 */
void iap2_task(void *arg)
{
    iap2_report("[IAP2]iap2_task\r\n");
    iap2_task_message_t message;

    iap2_service_queue = xQueueCreate(IAP2_SRV_QUEUE_LENGTH, sizeof(iap2_task_message_t));
    if (NULL == iap2_service_queue) {
        iap2_report("[IAP2]create service queue failed!\r\n");
        return;
    }

    while (1) {
        if (pdPASS == xQueueReceive(iap2_service_queue, (void *)&message, portMAX_DELAY)) {
            iap2_report("[IAP2]service recieve message:type is %d\r\n", message.msg_type);
#if 0
            if (IAP2_TASK_MESSAGE_TIMER == message.msg_type) {
                iap2_timer_handler(message.data.timer.iap2_timer);
            } else
#endif
                if (IAP2_TASK_MESSAGE_MFI == message.msg_type) {
                    iap2_control_session_handler(message.data.mfi.linkIndex, message.data.mfi.data);
                    if (message.data.mfi.data) {
                        iap2_memory_free(message.data.mfi.data);
                        message.data.mfi.data = NULL;
                    }
                } else {

                }
            memset((void *) &message, 0, sizeof(iap2_task_message_t));
        }
    }
}
#endif

extern void iap2_write_challenge_data(uint32_t linkIndex, iap2_param_t *challenge);
extern void iap2_read_challenge_data(uint32_t linkIndex);
extern void iap2_read_certificate_data(uint32_t linkIndex);
extern void iap2_send_identification(uint32_t linkIndex);

void iap2_task_mfi_data_handler(uint32_t linkIndex, uint8_t *data, uint16_t data_len, iap2_task_message_type msg)
{
    //iap2_report("[IAP2] iap2_task_mfi_data_handler, linkIndex: 0x%2x, data point is 0x%4x, len is %d\r\n", linkIndex, data, data_len);
    iap2_report_id(IAP2_TASK_001, 3, linkIndex, data, data_len);
    iap2_task_message_t message;
    memset((void *) &message, 0, sizeof(iap2_task_message_t));

    message.msg_type = msg;
    message.data.mfi.linkIndex = linkIndex;
    if ((NULL != data) && (0 != data_len)) {
        message.data.mfi.data = (uint8_t *)iap2_memory_alloc(data_len);
        if (message.data.mfi.data) {
            iap2_memcpy(message.data.mfi.data, data, data_len);
            //iap2_report("[IAP2]iap2_task_mfi_data_handler message:0x%4x, length is 0x%2x\r\n", message.data.mfi.data, data_len);
            iap2_report_id(IAP2_TASK_002, 2, message.data.mfi.data, data_len);
            xQueueSend(iap2_service_queue, (void *)&message, 0);
        } else {
            //iap2_report("[IAP2]iap2_task_mfi_data_handler, cannot alloc memory!\r\n");
            iap2_report_id(IAP2_TASK_003, 0);
            memset((void *) &message, 0, sizeof(iap2_task_message_t));
        }
    } else {
        message.data.mfi.data = NULL;
        xQueueSend(iap2_service_queue, (void *)&message, 0);
    }

    if (data) {
        iap2_memory_free(data);
        //iap2_report("[IAP2] iap2_task_mfi_data_handler, free packet\r\n");
        iap2_report_id(IAP2_TASK_004, 0);
    }
}


/**
 * @brief          This function is for service task implement.
 * @param[in]  arg      .
 * @return       void.
 */
void iap2_task(void *arg)
{
    iap2_task_message_t message;

    if (iap2_service_queue != NULL) {
        vQueueDelete(iap2_service_queue);
    }

    iap2_service_queue = xQueueCreate(IAP2_SRV_QUEUE_LENGTH, sizeof(iap2_task_message_t));
    if (NULL == iap2_service_queue) {
        //iap2_report("[IAP2]create service queue failed!\r\n");
        iap2_report_id(IAP2_TASK_005, 0);
        return;
    }

    while (1) {
        if (pdPASS == xQueueReceive(iap2_service_queue, (void *)&message, portMAX_DELAY)) {
            //iap2_report("[IAP2]service recieve message:type is %d\r\n", message.msg_type);
            iap2_report_id(IAP2_TASK_006, 1, message.msg_type);
#if 0
            if (IAP2_TASK_MESSAGE_TIMER == message.msg_type) {
                iap2_timer_handler(message.data.timer.iap2_timer);
            } else
#endif
            switch (message.msg_type) {
                case IAP2_TASK_MESSAGE_WRITE_CHALLENGE: {
                    iap2_write_challenge_data(message.data.mfi.linkIndex, (iap2_param_t *)(message.data.mfi.data + sizeof(iap2_packet_header_t) + sizeof(iap2_ctrl_session_t)));
                    if (message.data.mfi.data) {
                        iap2_memory_free(message.data.mfi.data);
                        message.data.mfi.data = NULL;
                    }
                }
                break;

                case IAP2_TASK_MESSAGE_READ_CHALLENGE: {
                    iap2_read_challenge_data(message.data.mfi.linkIndex);
                    if (message.data.mfi.data) {
                        iap2_memory_free(message.data.mfi.data);
                        message.data.mfi.data = NULL;
                    }
                }
                break;

                case IAP2_TASK_MESSAGE_READ_CERTIFICATE: {
                    iap2_read_certificate_data(message.data.mfi.linkIndex);
                    if (message.data.mfi.data) {
                        iap2_memory_free(message.data.mfi.data);
                        message.data.mfi.data = NULL;
                    }
                }
                break;

                case IAP2_TASK_MESSAGE_SEND_IDENTIFICATION: {
                    iap2_send_identification(message.data.mfi.linkIndex);
                    if (message.data.mfi.data) {
                        iap2_memory_free(message.data.mfi.data);
                        message.data.mfi.data = NULL;
                    }
                }
                break;
#ifdef AIR_USB_MFI_ENABLE
                case IAP2_TASK_MESSAGE_USB_RX: {
                    iap2_rx_data_handler(message.data.usb.linkIndex, message.data.usb.packet->data, message.data.usb.length);
                    iap2_usb_release_data(message.data.usb.packet->data);
                }
                break;
#endif
                default:
                    break;
            }

            memset((void *) &message, 0, sizeof(iap2_task_message_t));
        }
    }
}

/**
 * @brief      This function is for service task init implement.
 * @param[in]  void.
 * @return     void.
 */

void iap2_task_init(void)
{
    if (g_iap2_task_handle != 0) {
        vTaskDelete(g_iap2_task_handle);
    }

    if (pdPASS != xTaskCreate(iap2_task, IAP2_SRV_TASK_NAME, IAP2_SRV_TASK_STACKSIZE / sizeof(StackType_t), NULL, IAP2_SRV_TASK_PRIORITY, &g_iap2_task_handle)) {
        //iap2_report("[IAP2]iap2_task_init, fail!\r\n");
        iap2_report_id(IAP2_TASK_007, 0);
    }
}

#endif


