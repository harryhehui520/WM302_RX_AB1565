/* Copyright Statement:
 *
 * (C) 2018  Airoha Technology Corp. All rights reserved.
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

/**
 * File: apps_events_mic_control_event.h
 *
 * Description: This file defines the enum of event ids of EVENT_GROUP_UI_SHELL_WIRELESS_MIC group events.
 *
 */

#ifndef __APPS_EVENTS_MIC_CONTROL_EVENT_H__
#define __APPS_EVENTS_MIC_CONTROL_EVENT_H__

/** @brief
 * This enum defines the event ids of EVENT_GROUP_UI_SHELL_WIRELESS_MIC group events.
 */
typedef enum {
    APPS_EVENTS_MIC_CONTROL_MUTE,
    APPS_EVENTS_MIC_CONTROL_LOCAL_RECORDER,
    APPS_EVENTS_MIC_CONTROL_SAFETY_MODE,

#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
    APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM,
    APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM_EXTRA,
    APPS_EVENTS_MIC_CONTROL_SET_SYSTEM_INFO,
    APPS_EVENTS_MIC_CONTROL_GET_RTC_TIME,
#endif /* ARC_NXP_COM_ENABLE */
} app_mic_rx_control_event_t;

typedef enum {
    APPS_EVENTS_TX_MIC_STATUS,
    APPS_EVENTS_TX_RECORDER_STATUS,
    APPS_EVENTS_TX_BATTERY_STATUS,
    APPS_EVENTS_TX_VOLUME_STATUS,

    APPS_EVENTS_TX_FW_VERSION,

#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
    APPS_EVENTS_TX_SET_TX_DEVICE_PARAM,
    APPS_EVENTS_TX_SET_TX_DEVICE_PARAM_EXTRA,
    APPS_EVENTS_TX_GET_RTC_TIME_RSP,
#endif /* ARC_NXP_COM_ENABLE */

} app_mic_tx_status_event_t;

#endif /* __APPS_EVENTS_MIC_CONTROL_EVENT_H__ */