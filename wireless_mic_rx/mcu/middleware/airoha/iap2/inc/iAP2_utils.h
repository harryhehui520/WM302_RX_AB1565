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

#ifndef __IAP2_UTILS_H__
#define __IAP2_UTILS_H__

#include <stdint.h>
#include <stdbool.h>
#ifndef WIN32
#include <syslog.h>
#else
#include "osapi.h"
#endif
#include "iAP2_spec.h"
#include "bt_utils.h"

#ifdef __cplusplus
extern "C" {
#endif



#if defined(MTK_DEBUG_LEVEL_INFO)
#define __IAP2_DEBUG_INFO__
#define __IAP2_TRACE__
#endif


#define iap2_assert bt_utils_assert

#ifndef WIN32
#ifdef __IAP2_TRACE__
#define iap2_report(_message,...) LOG_I(IAP2, (_message), ##__VA_ARGS__)
#define iap2_hex_dump(_message,...)   LOG_HEXDUMP_I(IAP2, (_message), ##__VA_ARGS__)
#define iap2_util_report(_message,...) LOG_I(IAP2_UTIL, (_message), ##__VA_ARGS__)
#else
#define iap2_report(_message,...);
#define iap2_hex_dump(_message,...);
#define iap2_util_report(_message,...);
#endif
#else
#define iap2_report(_message,...) OS_Report((_message), ##__VA_ARGS__)
#define iap2_hex_dump(_message,...) OS_Report((_message), ##__VA_ARGS__)
#define iap2_util_report(_message,...) OS_Report((_message), ##__VA_ARGS__)
#endif /* WIN32 */


#define BSWAP_16(x) (uint16_t)(((((uint16_t)(x)) & 0x00FF) << 8) | ((((uint16_t)(x)) & 0xFF00) >> 8))

uint16_t bswap16(uint16_t x);

void *iap2_memory_alloc(uint16_t size);

void iap2_memory_free(void *point);

void *iap2_memset(void *ptr, int32_t value, uint32_t num);

void *iap2_memcpy(void *dest, const void *src, uint32_t size);

int32_t iap2_memcmp(const void *dest, const void *src, uint32_t count);

char *iap2_strfind(char *str, const char *sub);

char *iap2_strncat(char *dest, const char *src, int n);

uint32_t iap2_strlen(char *string);

char *iap2_strncpy(char *dest, const char *src, uint32_t size);

int32_t iap2_strnmp(const char *dest, const char *src, uint32_t size);

void iap2_switch_endian_bdaddr(uint8_t *bdAddr);

void iap2_set_timer_float(uint16_t TimerFloat);
void iap2_set_timer(uint32_t *timer, uint16_t timer_ticks);
void iap2_release_timer(uint32_t *timer);
bool iap2_check_timer_is_expired(uint32_t *timer);

void iap2_dump_linkInfo(iap2_link_info_t *link_info);
void iap2_dump_headerInfo(iap2_packet_header_t *header_info);
void iap2_dump_syncInfo(iap2_sync_payload_t *sync_info);
void iap2_dump_ctrlSession_header(iap2_ctrl_session_t *session);
void iap2_dump_ctrlSession_params(iap2_param_t *param);
bool iap2_check_uuid_is_valid(const uint8_t *uuid, uint16_t uuid_len);

void iap2_timer_handle_interrupt(void);

BT_PACKED(
typedef struct Node {
    uint8_t *packet;
    uint16_t packet_length;
    struct Node *next;
}) iap2_node_t;

iap2_node_t *iap2_create_list(void);
void iap2_add_node(iap2_node_t *head, uint8_t *packet, uint16_t packet_length);
uint32_t iap2_get_node_length(iap2_node_t *head);
uint32_t iap2_delete_node(iap2_node_t *head, uint8_t *packet, uint16_t packet_length);
bool iap2_check_node_is_exist(iap2_node_t *head, uint8_t *packet, uint16_t packet_length);
iap2_node_t *iap2_find_node_by_index(iap2_node_t *head, int index);

uint32_t iap2_create_mutex(void);
void iap2_take_mutex(uint32_t mutex_id);
void iap2_give_mutex(uint32_t mutex_id);
iap2_node_t *iap2_get_rx_head(void);
iap2_node_t *iap2_get_tx_head(void);
iap2_node_t *iap2_get_available_node(iap2_node_t *head);
void iap2_clear_rx_node_list(iap2_node_t *head);
void iap2_delete_and_release_node(iap2_node_t *head, uint8_t *packet, uint16_t packet_length);
void iap2_clear_tx_node_list(iap2_node_t *head);
bool iap2_check_tx_queue_is_full(void);

void iap2_report_id(const char *message, uint32_t argc, ...);

#ifdef __cplusplus
}
#endif

#endif /* __IAP2_UTILS_H__ */

