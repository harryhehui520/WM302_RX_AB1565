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

/*****************************************************************************
 *
 * Description:
 * ------------
 * The header file for users.
 *
 ****************************************************************************/



#ifndef __iAP2_TASK_H__
#define __iAP2_TASK_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "iAP2_spp.h"
#include "bt_spp.h"
#ifdef AIR_USB_MFI_ENABLE
#include "iAP2_usb.h"
#endif

typedef uint8_t iap2_task_message_type;
#define IAP2_TASK_MESSAGE_NONE                  0
#define IAP2_TASK_MESSAGE_WRITE_CHALLENGE       1
#define IAP2_TASK_MESSAGE_READ_CHALLENGE        2
#define IAP2_TASK_MESSAGE_READ_CERTIFICATE      3
#define IAP2_TASK_MESSAGE_SEND_IDENTIFICATION   4
#define IAP2_TASK_MESSAGE_TIMER                 5
#ifdef AIR_USB_MFI_ENABLE
#define IAP2_TASK_MESSAGE_USB_RX                6
#endif

typedef struct {
    iap2_task_message_type msg_type;
    union {
        struct {
            uint32_t iap2_timer;
        } timer;

        struct {
            uint32_t linkIndex;
            uint8_t *data;
        } mfi;
#ifdef AIR_USB_MFI_ENABLE
        struct {
            uint32_t linkIndex;
            iap2_usb_packet_t *packet;
            uint16_t length;
        } usb;
#endif
    } data;
} iap2_task_message_t;

void iap2_task_init(void);
#if 0
//void iap2_task_timer_handler(TimerHandle_t xTimer);
#endif
#if 0
void iap2_task_mfi_data_handler(uint32_t linkIndex, uint8_t *data, uint16_t data_len);
#endif
void iap2_task_mfi_data_handler(uint32_t linkIndex, uint8_t *data, uint16_t data_len, iap2_task_message_type msg);

#endif/*__iAP2_TASK_H__*/

