/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
 * File: apps_events_i2s_in_event.c
 *
 * Description: This file is used to detect i2s in.
 *
 */
#include "apps_events_i2s_in_event.h"
#include "apps_events_interaction_event.h"
#include "apps_events_event_group.h"
#include "apps_race_cmd_event.h"
#include "apps_debug.h"
#include "atci.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define  TAG  "I2S_IN_DET"

typedef enum {
    APP_I2S_IN_DET_IN     = 0,
    APP_I2S_IN_DET_OUT,
} app_i2s_in_state_t;

static app_i2s_in_det_t s_i2s_in_det;

static atci_status_t _i2s_in_det_atci(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}, 0};
    char *ptr = NULL;

    switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION: {
        ptr = parse_cmd->string_ptr + parse_cmd->name_len + 1;
        char cmd[20] = {0};
        uint8_t copy_len = strlen(ptr) - 2;
        memcpy(cmd, ptr, (copy_len > 19 ? 19 : copy_len));
        memset(&s_i2s_in_det, 0 , sizeof(app_i2s_in_det_t));

        sscanf(cmd, "%hhu,%hx,%hu,%lu,%lu,%lu", &s_i2s_in_det.i2s_state,
                                                &s_i2s_in_det.i2s_device,
                                                &s_i2s_in_det.i2s_interface,
                                                &s_i2s_in_det.i2s_sample_rate,
                                                &s_i2s_in_det.i2s_famart,
                                                &s_i2s_in_det.i2s_word_len);

        APPS_LOG_MSGID_I(TAG" i2s_state=%d, device=0x%x, interface=0x%x, sample_rate=%d, format=%d, word_len=%d", 6,
                         s_i2s_in_det.i2s_state, s_i2s_in_det.i2s_device, s_i2s_in_det.i2s_interface,
                         s_i2s_in_det.i2s_sample_rate, s_i2s_in_det.i2s_famart, s_i2s_in_det.i2s_word_len);

        ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_I2S_IN,
                APPS_EVENTS_I2S_IN_STATUS_CHANGE, (void *)&s_i2s_in_det, 0, NULL, 0);

        response.response_flag = ATCI_RESPONSE_FLAG_APPEND_OK;
        break;
    }
    default:
        response.response_flag = ATCI_RESPONSE_FLAG_APPEND_ERROR;
        break;
    }
    response.response_len = strlen((char *)response.response_buf);
    atci_send_response(&response);
    return ATCI_STATUS_OK;
}

static atci_cmd_hdlr_item_t app_events_i2s_in_det_atci_cmd_debug[] = {
    {
        .command_head = "AT+I2S_IN_DET",
        .command_hdlr = _i2s_in_det_atci,
        .hash_value1 = 0,
        .hash_value2 = 0,
    },
};

void app_events_i2s_in_init(void) {
    atci_register_handler(app_events_i2s_in_det_atci_cmd_debug, sizeof(app_events_i2s_in_det_atci_cmd_debug) / sizeof(atci_cmd_hdlr_item_t));
    APPS_LOG_MSGID_I(TAG" init success", 0);
}
