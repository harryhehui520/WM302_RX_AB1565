/* Copyright Statement:
 *
 * (C) 2019  Airoha Technology Corp. All rights reserved.
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
#ifndef _SMARTCHARGER_TYPES_H_
#define _SMARTCHARGER_TYPES_H_

#include "types.h"
#include "smchg_1wire_config.h"


#ifndef UNUSED
#define UNUSED(n)
#endif

#ifndef PACKED
#define PACKED __attribute__((packed))
#endif

typedef enum {
    SMART_CHARGER_EVENT_BATTERY_UPDATE             = 0x00000001,
    SMART_CHARGER_EVENT_CHARGER_STATE_UPDATE       = 0x00000002,
    SMART_CHARGER_EVENT_MESSAGE_UPDATE             = 0x00000004,
    SMART_CHARGER_EVENT_CHARGER_EXIST_UPDATE       = 0x00000008,
} smartcharger_management_event_t;

enum {
    CASE_TYPE_NONE,
    CASE_TYPE_SMART_1WIRE,
};

typedef enum {
    SMCHG_TYPE_NONE_PRESERVED_1,
    SMCHG_TYPE_NONE_PRESERVED_2,
    SMCHG_TYPE_1WIRE_2PINS,
    SMCHG_TYPE_1WIRE_MAX,
} smchg_type_t;

typedef enum {
    SMCHG_UART0_2GPIO,
    SMCHG_UART1_2GPIO,
    SMCHG_UART0_1GPIO,
    SMCHG_UART1_1GPIO,
} smchg_uart_gpio_t;



typedef uint8_t CHARGER_INT;
#define CHARGER_PLUG_INT            ((CHARGER_INT)1)
#define CHARGER_UNPLUG_INT          ((CHARGER_INT)2)
#define CHARGER_COMPLETE_INT        ((CHARGER_INT)4)
#define CHARGER_RECHARGE            ((CHARGER_INT)8)


#ifdef ARC_1WIRE_ENABLE
typedef void(* smartcharger_callback_t)(uint8_t event, uint8_t from_isr, uint32_t data, uint16_t data_len);
#else /* !ARC_1WIRE_ENABLE */
typedef void(* smartcharger_callback_t)(uint8_t event, uint8_t from_isr, uint8_t *data, uint16_t data_len);
#endif /* ARC_1WIRE_ENABLE */

typedef struct HandlerData *Handler;
typedef struct HandlerData {
    uint32_t (*handler)(Handler, uint16_t, void *, uint32_t);
} HandlerData;


#endif