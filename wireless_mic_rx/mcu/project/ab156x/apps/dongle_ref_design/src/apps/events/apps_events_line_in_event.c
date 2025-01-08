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
 * File: apps_events_line_in_event.c
 *
 * Description: This file is used to detect line in.
 *
 */
#include "apps_events_line_in_event.h"
#include "apps_events_interaction_event.h"
#include "apps_events_event_group.h"
#include "apps_race_cmd_event.h"
#include "apps_debug.h"
#include "atci.h"
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
#include "app_ull_dongle_idle_activity.h"
#endif

#include "bt_sink_srv_ami.h"

#include "hal_eint.h"
#include "hal_gpio.h"
#include "hal_audio_internal.h"

#include "ui_shell_manager.h"
#include "ui_shell_activity.h"

#include "stdlib.h"

#define  TAG  "LINE_IN_DET"

extern const unsigned char BSP_LINE_IN_EINT;
extern const unsigned char BSP_LINE_IN_DET_PIN;

#define APPS_EVENTS_LINE_IN_EVENT_DEBUG

#define LINE_IN_PLUG_IN_LEVEL HAL_GPIO_DATA_LOW

bool s_curr_line_in_status = false;

static void line_in_detect_callback(void *user_data) {
    hal_gpio_data_t current_gpio_status = 0;
    hal_eint_mask(BSP_LINE_IN_EINT);
    hal_gpio_get_input(BSP_LINE_IN_DET_PIN, &current_gpio_status);
    APPS_LOG_MSGID_I(TAG" get line in gpio sta: %d", 1, current_gpio_status);
    if (current_gpio_status == LINE_IN_PLUG_IN_LEVEL) {
        s_curr_line_in_status = true;
    } else {
        s_curr_line_in_status = false;
    }
    ui_shell_send_event(true, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_LINE_IN,
            APPS_EVENTS_INTERACTION_LINE_IN_STATUS, (void *)s_curr_line_in_status, 0, NULL, 0);
    hal_eint_unmask(BSP_LINE_IN_EINT);
}

static void app_events_line_in_init_set() {
    hal_gpio_data_t current_gpio_status = 0;
    hal_gpio_get_input(BSP_LINE_IN_DET_PIN, &current_gpio_status);
    APPS_LOG_MSGID_I(TAG" the line in pin status is: %d", 1, current_gpio_status);
    if (current_gpio_status == LINE_IN_PLUG_IN_LEVEL) {
        s_curr_line_in_status = true;
    } else {
        s_curr_line_in_status = false;
    }
    ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_LINE_IN,
            APPS_EVENTS_INTERACTION_LINE_IN_STATUS, (void *)s_curr_line_in_status, 0, NULL, 0);
}

#ifdef APPS_EVENTS_LINE_IN_EVENT_DEBUG
static atci_status_t _line_in_det_atci(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}, 0};
    uint32_t value = 0;

    switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION: {
        value= atoi(parse_cmd->string_ptr + parse_cmd->name_len + 1);
        APPS_LOG_MSGID_I(TAG" _line_in_det_atci mode = %d, value=%d", 2, parse_cmd->mode, value);
        if (value == 1) {
            s_curr_line_in_status = true;
        } else if(value == 0) {
            s_curr_line_in_status = false;
        }
        ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_LINE_IN,
                APPS_EVENTS_INTERACTION_LINE_IN_STATUS, (void *)s_curr_line_in_status, 0, NULL, 0);

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

#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
static atci_status_t _line_in_vol_atci(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}, 0};
    char *param = NULL;

    switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION: {
        param = parse_cmd->string_ptr + parse_cmd->name_len + 1;
        param = strtok(param, ",\n\r");
        if(0 == memcmp("up", param, strlen("up")))
        {
            APPS_LOG_MSGID_I(TAG" _line_in_vol_atci: up volume.", 0);
            app_ull_dongle_change_linein_volume_level(true);
        } else if (0 == memcmp("down",param, strlen("down"))) {
            APPS_LOG_MSGID_I(TAG" _line_in_vol_atci: down volume.", 0);
            app_ull_dongle_change_linein_volume_level(false);
        }
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


static atci_status_t _line_in_vol_values_atci(atci_parse_cmd_param_t *parse_cmd)
{
    atci_response_t response = {{0}, 0};
    uint32_t value = 0;

    switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION: {
        value= atoi(parse_cmd->string_ptr + parse_cmd->name_len + 1);
        if (value <= 100) {
            APPS_LOG_MSGID_I(TAG" _line_in_vol_values_atci: volume_values=%d.", 1, value);
            app_ull_dongle_set_linein_volume_value(value);
            response.response_flag = ATCI_RESPONSE_FLAG_APPEND_OK;
        } else {
            response.response_flag = ATCI_RESPONSE_FLAG_APPEND_ERROR;
        }
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
#endif

static atci_cmd_hdlr_item_t app_events_line_in_det_atci_cmd_debug[] = {
    {
        .command_head = "AT+LINE_IN_DET",
        .command_hdlr = _line_in_det_atci,
        .hash_value1 = 0,
        .hash_value2 = 0,
    },
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
    {
       .command_head = "AT+LINE_IN_VOL",
       .command_hdlr = _line_in_vol_atci,
       .hash_value1 = 0,
       .hash_value2 = 0,
    },
    {
       .command_head = "AT+LINE_IN_VOL_VALUES",
       .command_hdlr = _line_in_vol_values_atci,
       .hash_value1 = 0,
       .hash_value2 = 0,
    },
#endif
};

static void app_events_line_in_det_atci_debug_init(void)
{
    atci_status_t ret;

    ret = atci_register_handler(app_events_line_in_det_atci_cmd_debug, sizeof(app_events_line_in_det_atci_cmd_debug) / sizeof(atci_cmd_hdlr_item_t));
    if (ret == ATCI_STATUS_OK) {
        APPS_LOG_MSGID_I(TAG" atci_register_handler register success ", 0);
    } else {
        APPS_LOG_MSGID_I(TAG" atci_register_handler  register fail", 0);
    }
}
#endif //APPS_EVENTS_LINE_IN_EVENT_DEBUG

void app_events_line_in_det_init(void) {
#ifdef ARC_LINE_IN_DET_ENABLE
    hal_eint_config_t config;
    hal_eint_status_t sta;

#ifdef APPS_EVENTS_LINE_IN_EVENT_DEBUG
    app_events_line_in_det_atci_debug_init();
#endif

    /* For falling and rising detect. */
    config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
    config.debounce_time = 300;

    hal_gpio_init(BSP_LINE_IN_DET_PIN);
    hal_eint_mask(BSP_LINE_IN_EINT);

    sta = hal_eint_init(BSP_LINE_IN_EINT, &config);
    if (sta != HAL_EINT_STATUS_OK) {
        APPS_LOG_MSGID_E(TAG" init line in eint failed: %d", 1, sta);
        hal_eint_unmask(BSP_LINE_IN_EINT);
        return;
    }

    sta = hal_eint_register_callback(BSP_LINE_IN_EINT, line_in_detect_callback, NULL);
    if (sta != HAL_EINT_STATUS_OK) {
        APPS_LOG_MSGID_E(TAG" registe line in eint callback failed: %d", 1, sta);
        hal_eint_unmask(BSP_LINE_IN_EINT);
        hal_eint_deinit(BSP_LINE_IN_EINT);
        return;
    }
    hal_eint_unmask(BSP_LINE_IN_EINT);

    app_events_line_in_init_set();

    APPS_LOG_MSGID_I(TAG" init line in success", 0);
#else /* !ARC_LINE_IN_DET_ENABLE */
#ifdef APPS_EVENTS_LINE_IN_EVENT_DEBUG
    app_events_line_in_det_atci_debug_init();
#endif

    ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_LINE_IN,
            APPS_EVENTS_INTERACTION_LINE_IN_STATUS, (void *)true, 0, NULL, 0);
#endif /* ARC_LINE_IN_DET_ENABLE */
}

#ifdef ARC_USB_SW_ENABLE
#else /* !ARC_USB_SW_ENABLE */
#include "battery_management.h"

const char BSP_CHG_CE_PIN = 16;

const char BSP_CON_DET_PIN = 15;
const unsigned char BSP_CON_DET_EINT = 15;

const char BSP_VBUS_DET_PIN = 7;
const unsigned char BSP_VBUS_DET_EINT = 7;

const char BSP_CHG_STAT_PIN = 17;
const unsigned char BSP_CHG_STAT_EINT = 17;

static bool s_curr_con_det_status = false;
static bool s_curr_vbus_det_status = false;

static bool s_curr_chg_stat = false;
bool s_prev_chg_stat = false;
bool chg_stat_changed_debouning = false;

extern void pmu_chg_disable_forced(uint8_t en);
extern bool battery_set_enable_charger(bool isEnableCharging);

static void _chg_isr_cb(battery_management_event_t event, const void *data)
{
    if (event != BATTERY_MANAGEMENT_EVENT_CHARGER_EXIST_UPDATE) {
        return;
    }

    int32_t chg_exist = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);

    APPS_LOG_MSGID_I(TAG" chg_isr_cb, chg_exist[%d]", 1, chg_exist);

    if (s_curr_con_det_status && !s_curr_vbus_det_status)
    {
        /* Disable exteranl charger in Case 4(Only connector connected) too. */
        APPS_LOG_MSGID_I(TAG" Exteranl charger disable as only connector connected (at _chg_isr_cb)", 0);

        /* Cancel pending msg. */
        chg_stat_changed_debouning = false;
        ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE);
        
        ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE);
        ui_shell_send_event(true, EVENT_PRIORITY_HIGHEST,
                            EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                            APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE,
                            NULL, 0, NULL, 130);
    }
    else
    {
        if (chg_exist)
        {
            /* Charger is atached, enable external charger */
            APPS_LOG_MSGID_I(TAG" Exteranl charger enable as charger is atached", 0);

            ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE);
            ui_shell_send_event(true, EVENT_PRIORITY_HIGHEST,
                                EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE,
                                NULL, 0, NULL, 130);
        }
        else
        {
            /* Charger is detached, disable external charger. */
            APPS_LOG_MSGID_I(TAG" Exteranl charger disable as charger is detached", 0);

            /* Cancel pending msg. */
            chg_stat_changed_debouning = false;
            ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE);

            ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE);
            ui_shell_send_event(true, EVENT_PRIORITY_HIGHEST,
                                EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE,
                                NULL, 0, NULL, 130);
        }
    }
}

static void _detect_pin_level_handler(bool from_isr, const char det_pin)
{
    hal_gpio_data_t current_gpio_status = 0;
    hal_gpio_get_input(det_pin, &current_gpio_status);
    APPS_LOG_MSGID_I(TAG" get det gpio %d status %d", 2, det_pin, current_gpio_status);

    if (BSP_CON_DET_PIN == det_pin)
    {
        s_curr_con_det_status = (HAL_GPIO_DATA_HIGH == current_gpio_status) ? TRUE : FALSE;
    }
    else if (BSP_VBUS_DET_PIN == det_pin)
    {
        s_curr_vbus_det_status = (HAL_GPIO_DATA_HIGH == current_gpio_status) ? TRUE : FALSE;
    }

    if (!s_curr_con_det_status && !s_curr_vbus_det_status)
    {
        /* Case 1: Nothing connected, revert to default. */

        /* Disable charging. */
        pmu_chg_disable_forced(FALSE);
        battery_set_enable_charger(FALSE);

        APPS_LOG_MSGID_I(TAG" D+/D- to type-c as defalut", 0);
    }
    else if (!s_curr_con_det_status && s_curr_vbus_det_status)
    {
        /* Case 2: Only Type-C connected. */

        /* Enable charging. */
        pmu_chg_disable_forced(FALSE);
        battery_set_enable_charger(TRUE);

        APPS_LOG_MSGID_I(TAG" D+/D- to type-c as only type-c connected", 0);
    }
    else if (s_curr_con_det_status && s_curr_vbus_det_status)
    {
        /* Case 3: Both Type-C and connector are connected. */

        /* Enable charging. */
        pmu_chg_disable_forced(FALSE);
        battery_set_enable_charger(TRUE);

        APPS_LOG_MSGID_I(TAG" D+/D- to connector as both type-c and connected are connected", 0);
    }
    else if (s_curr_con_det_status && !s_curr_vbus_det_status)
    {
        /* Case 4: Only connector connected. */

        /* Disable charger preventing electric leakage from phone. */
        pmu_chg_disable_forced(TRUE);
        battery_set_enable_charger(FALSE);

        APPS_LOG_MSGID_I(TAG" D+/D- to connector as only connector connected", 0);
    }

    if (s_curr_con_det_status && !s_curr_vbus_det_status)
    {
        /* Disable exteranl charger in Case 4(Only connector connected) too. */
        APPS_LOG_MSGID_I(TAG" Exteranl charger disable as only connector connected", 0);

        /* Cancel pending msg. */
        chg_stat_changed_debouning = false;
        ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE);
        
        ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE);
        ui_shell_send_event(true, EVENT_PRIORITY_HIGHEST,
                            EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                            APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE,
                            NULL, 0, NULL, 130);
    }
    else
    {
        if (BSP_CHG_STAT_PIN == det_pin)
        {
            s_curr_chg_stat = (HAL_GPIO_DATA_HIGH == current_gpio_status) ? TRUE : FALSE;
        }

        int32_t chg_exist = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);

        if (!chg_exist)
        {
            /* Charger is detached, do nothing. */
            APPS_LOG_MSGID_I(TAG" Exteranl charger msg ignored as charger is detached", 0);
        }
        else
        {
            if (!chg_stat_changed_debouning)
            {
                if (s_curr_chg_stat)
                {
                    /* STAT High: Charging completed/Charging is disabled or in sleep mode. */
                    APPS_LOG_MSGID_I(TAG" Exteranl charger STAT High", 0);
        
                    /* Disable external charger. */
                    /* do not cannel APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE as we want to enable external charger always. */
                    ui_shell_send_event(from_isr, EVENT_PRIORITY_HIGHEST,
                                        EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                        APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE,
                                        NULL, 0, NULL, 60*1000);  // 1min: leave some charger time preventing any error status.
                }
                else
                {
                    /* STAT Low: Charging battery (or recharge). */
                    APPS_LOG_MSGID_I(TAG" Exteranl charger STAT Low", 0);
        
                    /* Enable external charger. */
                    ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE);
                    ui_shell_send_event(from_isr, EVENT_PRIORITY_HIGHEST,
                                        EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                        APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE,
                                        NULL, 0, NULL, 130);
                }
            }
            else
            {
                /* 0.65Hz Blinking: Charge is suspended due to input over-voltage, TS fault, or battery over-voltage. */
                APPS_LOG_MSGID_I(TAG" Exteranl charger msg ignored as 0.65Hz Blinking", 0);
        
                /*
                    Do nothing.
                    case 1: from charger to dis-charger, APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE is already sent by STAT high.
                    cass 2: from dis-charger to charger, do nothing until 0.65Hz blinking stop, then new status would set by APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE.
                */
            }
        
            s_prev_chg_stat = s_curr_chg_stat;
        
            chg_stat_changed_debouning = true;
            ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE);
            ui_shell_send_event(from_isr, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE, NULL, 0, NULL, 1600);   // 1600: 0.65Hz Blinking for SGM41523 = 1.538s... < 1.6s
        }
    }
}

static void _detect_pin_callback(void *user_data)
{
    uint32_t pin_info = (uint32_t)user_data;
    const char det_pin = (pin_info >> 8) & 0xFF;
    const unsigned char eint = pin_info & 0xFF;

    hal_eint_mask(eint);
    _detect_pin_level_handler(TRUE, det_pin);
    hal_eint_unmask(eint);
}

static void _det_pin_init(const char det_pin, const unsigned char eint)
{
    hal_eint_config_t config;
    hal_eint_status_t sta;

    /* For falling and rising detect. */
    config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
    config.debounce_time = 300;

    hal_gpio_init(det_pin);
    hal_eint_mask(eint);

    sta = hal_eint_init(eint, &config);
    if (sta != HAL_EINT_STATUS_OK)
    {
        APPS_LOG_MSGID_E(TAG" init %d eint failed: %d", 2, det_pin, sta);
        hal_eint_unmask(eint);
        return;
    }

    uint32_t pin_info = det_pin << 8 | eint;
    sta = hal_eint_register_callback(eint, _detect_pin_callback, (void *)pin_info);
    if (sta != HAL_EINT_STATUS_OK)
    {
        APPS_LOG_MSGID_E(TAG" registe %d eint callback failed: %d", 2, det_pin, sta);
        hal_eint_unmask(eint);
        hal_eint_deinit(eint);
        return;
    }
    hal_eint_unmask(eint);

    /* Check status after initialization. */
    _detect_pin_level_handler(FALSE, det_pin);

    APPS_LOG_MSGID_I(TAG" init det pin %d success", 1, det_pin);
}

uint8_t arc_events_usb_is_attached(void)
{
    return (s_curr_con_det_status || s_curr_vbus_det_status);
}

void arc_events_usb_det_init(void)
{
    _det_pin_init(BSP_CON_DET_PIN, BSP_CON_DET_EINT);

    _det_pin_init(BSP_VBUS_DET_PIN, BSP_VBUS_DET_EINT);
}

void arc_events_external_charger_det_init(void)
{
    _det_pin_init(BSP_CHG_STAT_PIN, BSP_CHG_STAT_EINT);

    if (battery_management_register_callback(_chg_isr_cb) != BATTERY_MANAGEMENT_STATUS_OK) {
        APPS_LOG_MSGID_I(TAG" init chg_isr_cb fail", 0);
        assert(0);
    }
}
#endif /* ARC_USB_SW_ENABLE */


