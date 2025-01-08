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
#include "task.h"
#include <timers.h>
#include "semphr.h"
#include "bt_platform.h"

#include <string.h>
#include <stdarg.h>
#include "iAP2_utils.h"
#include "iAP2_task.h"
#include "iAP2_log.h"
#include "bt_utils.h"

#define IAP2_TIMER_EXPIRED 0x80

static uint32_t iap2_timer_events = 0;
TimerHandle_t iap2_timer;
uint32_t iap2_mutex;

log_create_module(IAP2, PRINT_LEVEL_INFO);
log_create_module(IAP2_UTIL, PRINT_LEVEL_INFO);

extern void iap2_timer_handler(uint32_t xTimer);
extern void iap2_release_data_by_transport(uint8_t *packet);

void *iap2_memset(void *ptr, int32_t value, uint32_t num)
{
    return memset(ptr, value, num);
}

void *iap2_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}

int32_t iap2_memcmp(const void *dest, const void *src, uint32_t count)
{
    return memcmp(dest, src, count);
}

void *iap2_memory_alloc(uint16_t size)
{
#ifdef WIN32
    void *memory = (void *)malloc(size);
#else
    void *memory = (void *)pvPortMalloc(size);
#endif /* WIN32 */
    if (NULL != memory) {
        iap2_memset(memory, 0, size);
        //iap2_util_report("[IAP2] iap2_memory_alloc, ptr: 0x%x, size: %d\r\n", memory, size);
        iap2_report_id(IAP2_UTIL_008, 2, memory, size);
    } else {
        //iap2_util_report("[IAP2] iap2_memory_alloc, fail\r\n");
        //iap2_report_id(IAP2_UTIL_009, 0);
        iap2_assert(0 && "[IAP2] iap2_memory_alloc, fail");
    }
    return memory;
}

void iap2_memory_free(void *point)
{
    //iap2_util_report("[IAP2] iap2_memory_free, ptr: 0x%x\r\n", point);
    iap2_report_id(IAP2_UTIL_010, 1, point);

    if (point) {
#ifdef WIN32
        free(point);
#else
        vPortFree(point);
#endif /* WIN32 */
    }
}

char *iap2_strfind(char *str, const char *sub)
{
    return strstr(str, sub);
}

char *iap2_strncat(char *dest, const char *src, int n)
{
    return strncat(dest, src, n);
}

char *iap2_strncpy(char *dest, const char *src, uint32_t size)
{
    return strncpy(dest, src, size);
}

uint32_t iap2_strlen(char *string)
{
    return strlen(string);
}

int32_t iap2_strnmp(const char *dest, const char *src, uint32_t size)
{
    return strncmp(dest, src, size);
}


void iap2_switch_endian_bdaddr(uint8_t *bdAddr)
{
    uint8_t i, temp;

    for (i = 0; i < 3; i++) {
        temp = bdAddr[i];
        bdAddr[i] = bdAddr[5 - i];
        bdAddr[5 - i] = temp;
    }
}

uint16_t bswap16(uint16_t x)
{
    return (uint16_t)(((((uint16_t)(x)) & 0x00FF) << 8) | ((((uint16_t)(x)) & 0xFF00) >> 8));
}
#include "hal_gpt.h"

uint32_t start_time_en = 0;
uint32_t end_time_en = 0;

static void iap2_timer_expire(TimerHandle_t timer)
{
    uint32_t duration_count;

    taskDISABLE_INTERRUPTS();
    iap2_timer_events |= IAP2_TIMER_EXPIRED;
    iap2_timer = timer;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time_en);
    hal_gpt_get_duration_count(start_time_en, end_time_en, &duration_count);
    //iap2_util_report("[IAP2] iap2_timer_expire, timer: 0x%4x, duration: %d ms\r\n", timer, duration_count/1000);
    //iap2_report_id(IAP2_UTIL_011, 2, timer, duration_count / 1000);
    taskENABLE_INTERRUPTS();
    bt_trigger_interrupt(1);
}

void iap2_timer_handle_interrupt(void)
{
    uint32_t current_events;
    taskDISABLE_INTERRUPTS();
    current_events = iap2_timer_events;
    iap2_timer_events = 0;
    taskENABLE_INTERRUPTS();

    if (current_events & IAP2_TIMER_EXPIRED) {
        //iap2_take_mutex();
        iap2_timer_handler((uint32_t)iap2_timer);
        //iap2_give_mutex();
    }
    return;
}
static uint16_t g_timer_float = 80;


void iap2_set_timer_float(uint16_t TimerFloat)
{
    g_timer_float = TimerFloat;
}

void iap2_set_timer(uint32_t *timer, uint16_t timer_ticks)
{
    if (timer_ticks > g_timer_float) {
        timer_ticks -= g_timer_float;
    }

    if (0 == *timer) {
        *timer = (uint32_t)xTimerCreate("CUMULATIVE_TIMER",
                              timer_ticks / portTICK_PERIOD_MS,
                              pdFALSE,
                              (void *)0,
                              iap2_timer_expire);

        if (*timer) {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time_en);  // us
            xTimerStart((TimerHandle_t)*timer, 0);
            //iap2_util_report("[IAP2] iap2_set_timer, start timer: 0x%4x, delay: %d\r\n", *timer, timer_ticks);
            iap2_report_id(IAP2_UTIL_012, 2, *timer, timer_ticks);
        } else {
            //iap2_util_report("[IAP2] iap2_set_timer, create timer fail\r\n");
            iap2_report_id(IAP2_UTIL_013, 0);
        }

    } else {
        if (pdFALSE != xTimerIsTimerActive((TimerHandle_t)*timer)) {
            xTimerStop((TimerHandle_t)*timer, 0);
        }
        //xTimerStart((TimerHandle_t)xTimer_low_power, 0);
        xTimerChangePeriod((TimerHandle_t)*timer, timer_ticks / portTICK_PERIOD_MS, 0);
        xTimerReset((TimerHandle_t)*timer, 0);

        //iap2_util_report("[IAP2] iap2_set_timer, reset timer: 0x%4x, delay: %d\r\n", *timer, timer_ticks);
        iap2_report_id(IAP2_UTIL_014, 2, *timer, timer_ticks);
    }

}

void iap2_release_timer(uint32_t *timer)
{
    iap2_take_mutex(iap2_mutex);

    iap2_report_id(IAP2_UTIL_015, 1, *timer);
    if (0 != *timer) {
        if ((pdFALSE != xTimerIsTimerActive((TimerHandle_t)*timer))) {
            xTimerStop((TimerHandle_t)*timer, 0);
        }
        xTimerDelete((TimerHandle_t)*timer, 0);
        *timer = 0;
    }
    iap2_give_mutex(iap2_mutex);
}

bool iap2_check_timer_is_expired(uint32_t *timer)
{
    //iap2_report("[IAP2] iap2_check_timer_is_expired, timer: 0x%4x\r\n", *timer);

    if (*timer != 0) {
        //iap2_util_report("[IAP2] iap2_check_timer_is_expired, Yes\r\n");
        iap2_report_id(IAP2_UTIL_017, 0);
        iap2_release_timer(timer);
        return true;
    }
    return false;
}

void iap2_dump_linkInfo(iap2_link_info_t *link_info)
{
    if (link_info) {
#if 0
        iap2_report("[IAP2] iap2_dump_linkInfo, state: %d, txSEQ: %d, rxSEQ: %d, \
rxCumulative: %d, maxCumulative: %d, rxCumulativeTimeout: %d, \
rxCumulativeTimer: 0x%4x, SNWindowRange: %d, retransmission_timeout: 0x%4x, \
max_packet_length: 0x%4x\r\n",
                    link_info->state, link_info->txSEQ, link_info->rxSEQ,
                    link_info->rxCumulative, link_info->maxCumulative,
                    link_info->rxCumulativeTimeout, link_info->rxCumulativeTimer,
                    link_info->SNWindowRange, link_info->retransmission_timeout,
                    link_info->max_packet_length);
#endif
        iap2_report_id(IAP2_UTIL_001, 10,
                       link_info->state, link_info->txSEQ, link_info->rxSEQ,
                       link_info->rxCumulative, link_info->maxCumulative,
                       link_info->rxCumulativeTimeout, link_info->rxCumulativeTimer,
                       link_info->SNWindowRange, link_info->retransmission_timeout,
                       link_info->max_packet_length);
    }
}

void iap2_dump_headerInfo(iap2_packet_header_t *header_info)
{
    if (header_info) {
#if 0
        iap2_report("[IAP2] iap2_dump_headerInfo, packet_start: 0x%x, packet_length: 0x%x, ctrl_byte: 0x%x, \
seq_number: %d, ack_number: %d, session_identifier: %d, header_checksum: %d\r\n",
                    header_info->packet_start, header_info->packet_length, header_info->control_byte,
                    header_info->seq_number, header_info->ack_number,
                    header_info->session_identifier, header_info->header_checksum);
#endif
        iap2_report_id(IAP2_UTIL_002, 7,
                       header_info->packet_start, header_info->packet_length, header_info->control_byte,
                       header_info->seq_number, header_info->ack_number,
                       header_info->session_identifier, header_info->header_checksum);
    }
}

void iap2_dump_syncInfo(iap2_sync_payload_t *sync_info)
{
    if (sync_info) {
#if 0
        iap2_report("[IAP2] iap2_dump_syncInfo, link_version: %d, max_num_out_packets: %d, \
max_packet_length: 0x%x, retransmission_timeout: 0x%x, \
cumulative_ack_timeout: 0x%x, max_retrans: %d, max_cumulative_ack: %d, \
session_0.id: %d, session_0.type, session_0.version, \
session_1.id: %d, session_1.type, session_1.version\r\n",
                    sync_info->link_version, sync_info->max_num_out_packets,
                    sync_info->max_packet_length, sync_info->retransmission_timeout,
                    sync_info->cumulative_ack_timeout, sync_info->max_num_retransmissions,
                    sync_info->max_num_cumulative_acks, sync_info->session[0].identifier,
                    sync_info->session[0].type, sync_info->session[0].version,
                    sync_info->session[1].identifier, sync_info->session[1].type,
                    sync_info->session[1].version);
#endif
        iap2_report_id(IAP2_UTIL_003, 13,
                       sync_info->link_version, sync_info->max_num_out_packets,
                       sync_info->max_packet_length, sync_info->retransmission_timeout,
                       sync_info->cumulative_ack_timeout, sync_info->max_num_retransmissions,
                       sync_info->max_num_cumulative_acks, sync_info->session[0].identifier,
                       sync_info->session[0].type, sync_info->session[0].version,
                       sync_info->session[1].identifier, sync_info->session[1].type,
                       sync_info->session[1].version);
    }
}

void iap2_dump_ctrlSession_header(iap2_ctrl_session_t *session)
{
    if (session) {
        //iap2_report("[IAP2] iap2_dump_ctrlSession_header, start: 0x%x, length: 0x%x, msg_id: 0x%x\r\n",
        //  session->message_start, session->message_length, session->message_id);
        iap2_report_id(IAP2_UTIL_004, 3, session->message_start, session->message_length, session->message_id);
    }

}

void iap2_dump_ctrlSession_params(iap2_param_t *param)
{
    if (param) {
        //iap2_report("[IAP2] iap2_dump_ctrlSession_params, length: 0x%x, param_id: 0x%x, param: %s\r\n",
        //    param->param_length, param->param_id, param->param[0]);
        iap2_report_id(IAP2_UTIL_005, 3, param->param_length, param->param_id, param->param[0]);
    }

}

bool iap2_check_uuid_is_valid(const uint8_t *uuid, uint16_t uuid_len)
{
    bool ret = false;
    uint8_t i = 0;
    uint8_t const g_IAP2_uuid128[16] = {
        0x00, 0x00, 0x00, 0x00, 0xDE, 0xCA, 0xFA, 0xDE, 0xDE, 0xCA, 0xDE, 0xAF, 0xDE, 0xCA, 0xCA, 0xFE
    };

    if (uuid_len == sizeof(g_IAP2_uuid128)) {
        for (i = 0; i < sizeof(g_IAP2_uuid128); i++) {
            if (uuid[i] != g_IAP2_uuid128[i]) {
                break;
            }
        }
        if (i == sizeof(g_IAP2_uuid128)) {
            //iap2_report("[IAP2] iap2_check_uuid_is_valid, valid\r\n");
            iap2_report_id(IAP2_UTIL_006, 0);
            return true;
        }
    }
    return ret;
}


//********************************************************Node Function****************************************************************************//
iap2_node_t *iap2_rx_head = NULL;
iap2_node_t *iap2_tx_head = NULL;
static iap2_node_t g_iap2_rx_head;
static iap2_node_t g_iap2_tx_head;
extern uint16_t g_offset;

//MUTEX LOCK
uint32_t iap2_create_mutex(void)
{
    return (uint32_t)xSemaphoreCreateRecursiveMutex();
}

void iap2_take_mutex(uint32_t mutex_id)
{
    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        return;
    }
    if (mutex_id == 0) {
        bt_utils_assert(0 && "Spp Air is not initialized.");
    }

    xSemaphoreTakeRecursive((SemaphoreHandle_t)mutex_id, portMAX_DELAY);
}

void iap2_give_mutex(uint32_t mutex_id)
{
    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        return;
    }
    xSemaphoreGiveRecursive((SemaphoreHandle_t)mutex_id);
}

iap2_node_t *iap2_get_rx_head(void)
{
    return &g_iap2_rx_head;
}

iap2_node_t *iap2_get_tx_head(void)
{
    return &g_iap2_tx_head;
}

/**
 * @brief          This function is for create a list.
 * @param[in]  void.
 * @return       the head of the list.
 */
iap2_node_t *iap2_create_list(void)
{
    iap2_node_t *head;
    head = (iap2_node_t *)pvPortMalloc(sizeof(iap2_node_t));

    if (NULL != head) {
        head->packet = NULL;
        head->packet_length = 0;
        head->next = NULL;
    }
    return head;
}

/**
 * @brief          This function is for add a node into list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       void.
 */
void iap2_add_node(iap2_node_t *head, uint8_t *packet, uint16_t packet_length)
{
    //insert start
    iap2_take_mutex(iap2_mutex);

    iap2_node_t *p = (iap2_node_t *)pvPortMalloc(sizeof(iap2_node_t));
    if (NULL != p) {
        p->packet = packet;
        p->packet_length = packet_length;
        p->next = head->next;
        head->next = p;
    } else {
        //iap2_util_report("[IAP2]iap2_add_node, fail!\r\n");
        iap2_report_id(IAP2_UTIL_018, 0);
    }
    iap2_give_mutex(iap2_mutex);

}

/**
 * @brief          This function is for get the list length.
 * @param[in]  head      is the head of the list.
 * @return       the length of the list.
 */
uint32_t iap2_get_node_length(iap2_node_t *head)//get list length
{
    iap2_take_mutex(iap2_mutex);
    uint32_t n = 0;
    iap2_node_t *p;

    if (NULL == head) {
        return 0;
    }

    p = head->next;
    while (p) {
        n++;
        p = p->next;
    }
    iap2_give_mutex(iap2_mutex);
    return n;
}

/**
 * @brief          This function is for delete a node into list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       delete success or not.
 */
uint32_t iap2_delete_node(iap2_node_t *head, uint8_t *packet, uint16_t packet_length)
{
    iap2_take_mutex(iap2_mutex);

    iap2_node_t *p;
    iap2_node_t *q;
    for (p = head; ((NULL != p) && (NULL != p->next)); p = p->next) {
        if (p->next->packet == packet) {
            q = p->next;
            p->next = q->next;
            //iap2_util_report("[IAP2]iap2_delete_node, node: 0x%4x, packet: 0x%4x, pak_len: %d\r\n", q, q->packet, q->packet_length);
            iap2_util_report(IAP2_UTIL_019, 3, q, q->packet, q->packet_length);
            vPortFree(q);
            iap2_give_mutex(iap2_mutex);
            return 1;
        }
    }
    iap2_give_mutex(iap2_mutex);
    return 0;
}

/**
 * @brief          This function is for find a node into list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       the exit node or not.
 */
bool iap2_check_node_is_exist(iap2_node_t *head, uint8_t *packet, uint16_t packet_length)
{
    iap2_take_mutex(iap2_mutex);

    if (NULL == head) {
        return false;
    }

    iap2_node_t *p = head->next;
    while (NULL != p) {
        if (p->packet == packet) {
            iap2_give_mutex(iap2_mutex);
            return true;
        } else {
            p = p->next;
        }
    }
    iap2_give_mutex(iap2_mutex);
    return false;
}

/**
 * @brief          This function is for add a node by the index of the list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       the node.
 */
iap2_node_t *iap2_find_node_by_index(iap2_node_t *head, int index)
{
    iap2_take_mutex(iap2_mutex);

    int i;
    iap2_node_t *p;
    if (NULL == head) {
        return NULL;
    }

    p = head->next;
    for (i = 0; i < (index - 1); i++) {
        if (NULL == p) {
            break;
        }
        p = p->next;
    }

    if (NULL == p) {
        iap2_give_mutex(iap2_mutex);
        //iap2_util_report("[IAP2]iap2_find_node_by_index, node not find!\r\n");
        iap2_report_id(IAP2_UTIL_020, 0);
        return NULL;
    }

    //iap2_util_report("[IAP2]iap2_find_node_by_index, find node: 0x%4x, packet: 0x%4x, pak_len: 0x%4x\r\n",  p, p->packet, p->packet_length);
    iap2_report_id(IAP2_UTIL_021, 3, p, p->packet, p->packet_length);
    iap2_give_mutex(iap2_mutex);
    return p;
}

uint32_t iap2_check_node_buffer(iap2_node_t *head, uint8_t *data, uint16_t data_size)
{
    uint32_t r_size = 0;
    uint32_t count = 0;

    if (!head) {//head is NULL
        return r_size;
    }
    count = iap2_get_node_length(head);
    //iap2_util_report("[IAP2]iap2_check_node_buffer, count: %d\r\n", count);
    iap2_report_id(IAP2_UTIL_022, 1, count);

    if (count != 0) {
        uint8_t *pak;
        uint16_t pak_len;

        iap2_node_t *node = iap2_find_node_by_index(head, count);
        if (node) {
            if (data_size > node->packet_length) {
                memcpy(data, node->packet, node->packet_length);
                r_size = node->packet_length;
            } else {
                bt_utils_assert(0 && "enlarge the read buffer");
            }

            pak = node->packet;
            pak_len = node->packet_length;

            //iap2_util_report("[IAP2]iap2_check_node_buffer, pak: 0x%4x, pak_len: %d\r\n", pak, pak_len);
            iap2_report_id(IAP2_UTIL_023, 2, pak, pak_len);
            iap2_delete_node(head, node->packet, node->packet_length); //deleteElem must before bt_iap2_release_data, or the sequence of the packets will be wrong
            if (pak || (pak_len != 0)) {
                iap2_release_data_by_transport(pak);
            }
        }
    }
    return r_size;
}

void iap2_clear_rx_node_list(iap2_node_t *head)
{
    uint32_t count = iap2_get_node_length(head);

    g_offset = 0;
    while (count > 0) {
        uint8_t *pak = NULL;
        uint16_t pak_len = 0;

        iap2_node_t *node = iap2_find_node_by_index(head, count);

        if (node) {
            pak = node->packet;
            pak_len = node->packet_length;
            iap2_delete_node(head, node->packet, node->packet_length);
        }
        if (pak || (pak_len != 0)) {
            iap2_release_data_by_transport(pak);
        }
        count --;
    }
}

void iap2_delete_and_release_node(iap2_node_t *head, uint8_t *packet, uint16_t packet_length)
{
    if (iap2_check_node_is_exist(head, packet, packet_length)) {
        uint8_t *pak;
        uint16_t pak_len;

        pak = packet;
        pak_len = packet_length;
        iap2_delete_node(head, packet, packet_length);

        if (pak || (pak_len != 0)) {
            iap2_release_data_by_transport(pak);
        }
    }
}

iap2_node_t *iap2_get_available_node(iap2_node_t *head)
{
    uint32_t count = iap2_get_node_length(head);

    if (count) {//list is not null
        iap2_node_t *node = iap2_find_node_by_index(head, count);
        return node;
    }
    return NULL;
}

void iap2_clear_tx_node_list(iap2_node_t *head)
{
    uint32_t count = iap2_get_node_length(head);

    while (count > 0) {
        uint8_t *pak = NULL;

        iap2_node_t *node = iap2_find_node_by_index(head, count);
        if (node) {
            pak = node->packet;
            iap2_delete_node(head, node->packet, node->packet_length);
        }
        if (pak) {
            iap2_memory_free(pak);
        }
        count --;
    }
}

bool iap2_check_tx_queue_is_full(void)
{
    uint32_t tx_node_num = iap2_get_node_length(iap2_get_tx_head());
    //iap2_report("[IAP2] TX queue number of nodes is %d\r\n", tx_node_num);
    iap2_report_id(IAP2_UTIL_007, 1, tx_node_num);

    if (iap2_get_tx_queue_max_length() <= tx_node_num) {
        return true;
    }
    return false;
}

void iap2_report_id(const char *message, uint32_t argc, ...)
{
    va_list ap;
    log_control_block_t *block = &log_control_block_IAP2;

    va_start(ap, argc);
    log_print_msgid(block, PRINT_LEVEL_INFO, message, argc, ap);
    va_end(ap);
}


#endif



