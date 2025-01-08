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


/**
 * File: app_ull_dongle_idle_activity.c
 *
 * Description: This file could receive ultra low latecy events and notify BT state change.
 *
 * Note: See doc/Airoha_IoT_SDK_Application_Developers_Guide.pdf for ULL dongle APP.
 *
 */

#include "app_ull_dongle_idle_activity.h"
#include "app_preproc_activity.h"
#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
#include "bt_ull_service.h"
#include "app_dongle_service.h"
#include "race_cmd_feature.h"
#endif
#ifdef RACE_FOTA_ACTIVE_MODE_ULL_SUPPORT
#include "race_fota.h"
#endif

#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
#include "bt_ull_le_service.h"
#include "bt_ull_le_utility.h"
#include "app_ull_dongle_le.h"
#endif

#include "apps_events_event_group.h"
#include "apps_events_usb_event.h"
#include "apps_config_event_list.h"
#include "apps_events_mic_control_event.h"
#include "apps_dongle_sync_event.h"
#include "ui_shell_manager.h"
#include "app_dongle_race.h"

#include "apps_debug.h"

#include "apps_events_interaction_event.h"
#include "hal_eint.h"
#include "hal_gpio.h"

#include "nvkey.h"
#include "nvkey_id_list.h"

#ifdef AIR_MS_GIP_ENABLE
#include "app_ms_xbox_idle_activity.h"
#endif
#include "bt_connection_manager.h"
#include "usb_main.h"
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
#include "apps_config_led_index_list.h"
#include "apps_config_led_manager.h"
#include "bt_ull_le_call_service.h"
#include "usb_hid_srv.h"
#endif
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
#include "scenario_wireless_mic_rx.h"
#endif /* AIR_WIRELESS_MIC_RX_ENABLE */

#include "battery_management.h"
#include "battery_management_core.h"
#include "apps_events_battery_event.h"

#define LOG_TAG     "[app_dongle]"

#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
#define APP_LINE_IN_MIX_RATIO_MIN_LEVEL       (0)
#define APP_LINE_IN_MIX_RATIO_BALANCED_LEVEL  (70)
#define APP_LINE_IN_MIX_RATIO_MAX_LEVEL       (100)
#define APP_LINE_IN_DEFAULT_VOLUME_VALUES     50  /**< Customer configuration*/
#define APP_LINE_OUT_DEFAULT_VOLUME_VALUES    90  /**< Customer configuration*/

typedef struct {
        bool      spk_gaming_play;                /**< Record if the speaker gaming is playing.*/
        bool      spk_chat_play;                  /**< Record if the speaker chat is playing.*/
        bool      usb_out_play;                   /**< Record if the usb out is playing.*/
#if defined(AIR_ULL_DONGLE_LINE_IN_ENABLE) || defined(AIR_ULL_DONGLE_LINE_OUT_ENABLE)
        bool      line_in;                        /**< Record if the line in.*/
        bool      line_out;                       /**< Record if the line out.*/
#endif
#ifdef AIR_DONGLE_I2S_SLV_OUT_ENABLE
        bool      i2s_out;                        /**< Record if the i2s out.*/
#endif
        bool      ull_connected;                  /**< Record if the ull was connected.*/
#if defined(AIR_ULL_DONGLE_LINE_IN_ENABLE) || defined(AIR_ULL_DONGLE_LINE_OUT_ENABLE)
        uint8_t   linein_volume_values;           /**< Record the current values of the line in streaming.*/
        uint8_t   lineout_volume_values;          /**< Record the current values of the line out streaming.*/
#endif
} app_ull_context;

static app_ull_context g_app_ull_dongle_context = {0};
#endif

uint8_t g_dongle_mode  =   APP_DONGLE_MODE_PC;

#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
#define APP_WIRELESS_MIC_TX_NUM_MAX (2)
#define APP_WIRELESS_MIC_MODE_MAX   (2)
#define APP_WIRELESS_MONO_MIC_MODE_MERGE        (5)
#define APP_WIRELESS_MONO_MIC_MODE_SPLIT_LEFT   (8)
#define APP_WIRELESS_MONO_MIC_MODE_SPLIT_RIGHT  (9)
#define APP_WIRELESS_STEREO_MIC_MODE_MERGE_LEFT   (1)
#define APP_WIRELESS_STEREO_MIC_MODE_MERGE_RIGHT  (2)
#define APP_WIRELESS_STEREO_MIC_MODE_SPLIT        (5)
#define APP_WIRELESS_STEREO_MIC_MODE_SPLIT_LEFT   (6)
#define APP_WIRELESS_STEREO_MIC_MODE_SPLIT_RIGHT  (7)

#define APP_WIRELESS_MIC_SAFETY_MODE_LEFT_GAIN      (600)   /* 600 means +6 DB */
#define APP_WIRELESS_MIC_SAFETY_MODE_RIGHT_GAIN     (0)

#define APP_WIRELESS_MIC_SAFETY_MODE_LC3PLUS_LEFT_GAIN      (0)
#define APP_WIRELESS_MIC_SAFETY_MODE_LC3PLUS_RIGHT_GAIN     (-600) /* -600 means -6 DB */

enum {
#if defined(AIR_ULL_DONGLE_LINE_OUT_ENABLE)
    APP_WIRELESS_MIC_OUTPUT_TYPE_LINE_OUT = 0,
#endif
#if defined(AIR_DONGLE_I2S_SLV_OUT_ENABLE)
    APP_WIRELESS_MIC_OUTPUT_TYPE_I2S_OUT,
#endif
    APP_WIRELESS_MIC_OUTPUT_TYPE_USB_OUT,
    APP_WIRELESS_MIC_OUTPUT_TYPE_MAX
};

typedef struct {
    bt_bd_addr_t addr;
    uint8_t mode_id;
} app_wireless_mic_rx_merge_split_mode_record_t;

typedef struct {
    bt_bd_addr_t addr;
    uint8_t audio_info_data[0];
} app_wireless_mic_rx_merge_split_audio_data_t;

#ifdef ARC_APP
#else /* !ARC_APP */
typedef struct {
#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
    uint8_t                 audio_status1;
    uint8_t                 audio_status2;
    uint8_t                 mic_gain;

    uint8_t                 audio_statusN;
#endif /* ARC_NXP_COM_ENABLE */
} arc_dp_recored_tx_setting_t;

typedef struct {
    uint8_t                 lr_2_rl;
    uint8_t                 mono_or_setero;
    uint8_t                 safety_mode;
    uint8_t                 eq_mode;
    uint8_t                 rx_gain;
    uint8_t                 laguage;
} arc_dp_recored_rx_setting_t;

typedef struct {
    rtc_time_setting_src_t src;
    uint8_t year;
    uint8_t mon;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} arc_dp_rtc_time_setting_t;

typedef struct {
    bt_addr_t               addr;
    bool                    connected;
    int8_t                  rssi;
    bool                    mic_mute;
    bool                    recording;
    uint8_t                 battery_percent;
    int32_t                 volume;

    uint8_t                 major;
    uint8_t                 minor;
    uint8_t                 revision;

#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
    uint8_t                 tx_device_status;
    uint8_t                 file_number;
    uint8_t                 recording_file_size_1;
    uint8_t                 recording_file_size_2;
    uint8_t                 recording_file_size_3;
    uint8_t                 recording_file_size_4;
#endif /* ARC_NXP_COM_ENABLE */
} arc_dp_recored_tx_data_t;

typedef struct {
    uint8_t                 reserved;

    uint8_t                 rtc_init_check;
} arc_dp_recored_rx_data_t;

/* All data and setting */
typedef struct {
    struct {
        arc_dp_recored_tx_setting_t         tx_setting[TX_DEVICE_INDEX_MAX];
        arc_dp_recored_rx_setting_t         rx_setting;
    } setting;
    arc_dp_recored_tx_data_t                tx_data[TX_DEVICE_INDEX_MAX];
    arc_dp_recored_rx_data_t                rx_data;
} arc_app_data_t;

static arc_app_data_t g_arc_app;
#endif /* ARC_APP */

static void app_wireless_mic_rx_generate_audio_connection_info(uint8_t **audio_info,
                                                               uint32_t *audio_info_size,
                                                               app_wireless_mic_rx_merge_split_mode_record_t *record_data,
                                                               uint8_t record_data_num)
{
    uint32_t total_size = 0;
    uint32_t position = 0;

    *audio_info = NULL;
    *audio_info_size = 0;
    if (record_data != NULL && record_data_num != 0) {
        uint8_t *audio_info_list[record_data_num];
        uint32_t audio_info_size_list[record_data_num];
        uint8_t i;
        for (i = 0; i < record_data_num; i++) {
            wireless_mic_rx_audio_connection_info_get(record_data[i].mode_id, &audio_info_list[i], &audio_info_size_list[i]);
            if (audio_info_list[i] != NULL && audio_info_size_list[i] != 0) {
                total_size = total_size + sizeof(app_wireless_mic_rx_merge_split_audio_data_t) + audio_info_size_list[i];
            }
        }
        *audio_info = wireless_mic_rx_audio_connection_info_malloc(total_size);
        if (audio_info) {
            for (i = 0; i < record_data_num; i++) {
                if (audio_info_list[i] != NULL && audio_info_size_list[i] != 0) {
                    app_wireless_mic_rx_merge_split_audio_data_t *audio_data = (app_wireless_mic_rx_merge_split_audio_data_t *)(*audio_info + position);
                    memcpy(&audio_data->addr, &record_data[i].addr, sizeof(bt_bd_addr_t));
                    memcpy(&audio_data->audio_info_data, audio_info_list[i], audio_info_size_list[i]);
                    position = position + sizeof(app_wireless_mic_rx_merge_split_audio_data_t) + audio_info_size_list[i];
                }
            }
            *audio_info_size = total_size;
        }
    }
}

static bt_status_t app_wireless_mic_rx_query_audio_mode(app_wireless_mic_rx_merge_split_mode_record_t **record_mode,
                                                                   uint8_t *record_count,
                                                                   const bt_bd_addr_t *change_addr,
                                                                   uint8_t target_mode)
{
    *record_mode = NULL;
    *record_count = 0;

    bt_addr_t addr_list[APP_WIRELESS_MIC_TX_NUM_MAX];
    uint8_t tx_mic_amount = APP_WIRELESS_MIC_TX_NUM_MAX;
    bt_status_t bt_status = app_ull_dongle_le_get_connected_device_list(addr_list, &tx_mic_amount);

    if (BT_STATUS_SUCCESS == bt_status && tx_mic_amount > 0)
    {
        *record_mode = (app_wireless_mic_rx_merge_split_mode_record_t *)malloc(sizeof(app_wireless_mic_rx_merge_split_mode_record_t) * tx_mic_amount);
        if (NULL != *record_mode)
        {
            *record_count = tx_mic_amount;
            for (uint8_t i = 0; i < tx_mic_amount; i++)
            {
                memcpy((*record_mode)[i].addr, addr_list[i].addr, sizeof(bt_bd_addr_t));

                bool mono = !g_arc_app.setting.rx_setting.mono_or_setero;
                if (mono)
                {
                    (*record_mode)[i].mode_id = APP_WIRELESS_STEREO_MIC_MODE_SPLIT;
                }
                else
                {
                    (*record_mode)[i].mode_id = g_arc_app.setting.rx_setting.lr_2_rl ? APP_WIRELESS_STEREO_MIC_MODE_MERGE_RIGHT : APP_WIRELESS_STEREO_MIC_MODE_MERGE_LEFT;
                }

                APPS_LOG_MSGID_I(LOG_TAG", app_wireless_mic_rx_query_audio_mode addr[%02X:%02X:%02X:%02X:%02X:%02X], mode: %d", 7,
                                 (*record_mode)[i].addr[0], (*record_mode)[i].addr[1], (*record_mode)[i].addr[2],
                                 (*record_mode)[i].addr[3], (*record_mode)[i].addr[4], (*record_mode)[i].addr[5],
                                 (*record_mode)[i].mode_id);
            }
        }
    }

    return bt_status;
}

static bt_status_t app_wireless_mic_rx_set_audio_transmit_info(bt_ull_streaming_interface_t interface,
                                                               app_wireless_mic_rx_merge_split_mode_record_t *record_data,
                                                               uint8_t record_data_num)
{
    bt_status_t ret = BT_STATUS_FAIL;
    uint8_t *info;
    uint32_t info_size;
    app_wireless_mic_rx_generate_audio_connection_info(&info, &info_size, record_data, record_data_num);
    if (info && info_size > 0) {
        bt_ull_streaming_t stream = {
            .streaming_interface = interface,
            .port = 0,
        };
        ret = bt_ull_le_srv_set_audio_connection_info(&stream, info, info_size);
        if (BT_STATUS_SUCCESS != ret) {
            /* If success, free by audio module. */
            wireless_mic_rx_audio_connection_info_free(info);
        }
    }
    //APPS_LOG_MSGID_I(LOG_TAG", set_audio_transmit_info to interface 0x%x, info = 0x%x, size = %d, ret = 0x%x", 4, interface, info, info_size, ret);
    APPS_LOG_DUMP_I(LOG_TAG", set_audio_transmit_info to interface 0x%x, size = %d, ret = 0x%x", info, info_size, interface, info_size, ret);
    return ret;
}

static void app_wireless_mic_rx_set_audio_transmit_info_to_single_interface(bt_ull_streaming_interface_t interface)
{
    app_wireless_mic_rx_merge_split_mode_record_t *record_mode = NULL;
    uint8_t record_count = 0;

    app_wireless_mic_rx_query_audio_mode(&record_mode, &record_count, NULL, 0);
    if (record_mode && record_count > 0) {
        app_wireless_mic_rx_set_audio_transmit_info(interface, record_mode, record_count);
        free(record_mode);
    }
}

static uint8_t app_wireless_mic_rx_get_active_interface(bt_ull_streaming_interface_t interfaces[APP_WIRELESS_MIC_OUTPUT_TYPE_MAX])
{
    uint8_t active_out = 0;
    memset(interfaces, BT_ULL_STREAMING_INTERFACE_UNKNOWN, sizeof(bt_ull_streaming_interface_t) * APP_WIRELESS_MIC_OUTPUT_TYPE_MAX);
#if defined(AIR_ULL_DONGLE_LINE_OUT_ENABLE)
    if (g_app_ull_dongle_context.line_out) {
        interfaces[APP_WIRELESS_MIC_OUTPUT_TYPE_LINE_OUT] = BT_ULL_STREAMING_INTERFACE_LINE_OUT;
        active_out ++;
    }
#endif
#if defined(AIR_DONGLE_I2S_SLV_OUT_ENABLE)
    if (g_app_ull_dongle_context.i2s_out) {
        interfaces[APP_WIRELESS_MIC_OUTPUT_TYPE_I2S_OUT] = BT_ULL_STREAMING_INTERFACE_I2S_OUT;
        active_out ++;
    }
#endif
    if (g_app_ull_dongle_context.usb_out_play) {
        interfaces[APP_WIRELESS_MIC_OUTPUT_TYPE_USB_OUT] = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
        active_out ++;
    }

    return active_out;
}

static void app_wireless_mic_rx_set_audio_transmit_info_to_all_interface(const bt_bd_addr_t *change_addr,
                                                                         uint8_t target_mode)
{
    uint8_t j;
    uint8_t active_out = 0;
    app_wireless_mic_rx_merge_split_mode_record_t *record_mode = NULL;
    uint8_t record_count = 0;

    /* set BT address into connection info */
    bt_ull_streaming_interface_t interfaces_list[APP_WIRELESS_MIC_OUTPUT_TYPE_MAX];
    active_out = app_wireless_mic_rx_get_active_interface(interfaces_list);
    if (active_out > 0 || NULL != change_addr) {
        app_wireless_mic_rx_query_audio_mode(&record_mode, &record_count, change_addr, target_mode);
        if (record_mode && record_count > 0) {
            if (active_out > 0) {
                for (j = 0; j < APP_WIRELESS_MIC_OUTPUT_TYPE_MAX; j++) {
                    if (interfaces_list[j] != BT_ULL_STREAMING_INTERFACE_UNKNOWN) {
                        app_wireless_mic_rx_set_audio_transmit_info(interfaces_list[j], record_mode, record_count);
                    }
                }
            }
            free(record_mode);
        }
    }
}

static void app_wireless_mic_rx_send_safety_mode_to_tx(uint8_t safety_mode, bt_bd_addr_t *addr)
{
    if (addr) {
        apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SAFETY_MODE,
                                                    &safety_mode, sizeof(safety_mode), addr);
    } else {
        uint8_t i;
        bt_addr_t addr_list[APP_WIRELESS_MIC_TX_NUM_MAX];
        uint8_t tx_mic_amount = APP_WIRELESS_MIC_TX_NUM_MAX;
        bt_status_t status = app_ull_dongle_le_get_connected_device_list(addr_list, &tx_mic_amount);
        for (i = 0; BT_STATUS_SUCCESS == status && i < tx_mic_amount; i++) {
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SAFETY_MODE,
                                                        &safety_mode, sizeof(safety_mode), &(addr_list[i].addr));
        }
    }
}

static void app_wireless_mic_rx_set_safety_mode(bool switch_mode, bt_ull_streaming_interface_t interface) {

    uint8_t i;
    uint8_t safety_mode = 0;
    uint32_t safety_mode_size = sizeof(safety_mode);
    int32_t left_vol_diff;
    int32_t right_vol_diff;
    bt_status_t status = BT_STATUS_SUCCESS;
    bt_ull_streaming_interface_t interfaces_list[APP_WIRELESS_MIC_OUTPUT_TYPE_MAX];

    nvkey_read_data(NVID_APP_WM_SAFETY_MODE, &safety_mode, &safety_mode_size);
    if (switch_mode) {
        safety_mode = safety_mode ? 0 : 1;
        nvkey_write_data(NVID_APP_WM_SAFETY_MODE, &safety_mode, sizeof(safety_mode));
        app_wireless_mic_rx_send_safety_mode_to_tx(safety_mode, NULL);
    }

    if (safety_mode) {
        if (bt_ull_le_srv_get_codec_type() == BT_ULL_LE_CODEC_LC3PLUS) {
            left_vol_diff = APP_WIRELESS_MIC_SAFETY_MODE_LC3PLUS_LEFT_GAIN;
            right_vol_diff = APP_WIRELESS_MIC_SAFETY_MODE_LC3PLUS_RIGHT_GAIN;
        } else {
            left_vol_diff = APP_WIRELESS_MIC_SAFETY_MODE_LEFT_GAIN;
            right_vol_diff = APP_WIRELESS_MIC_SAFETY_MODE_RIGHT_GAIN;
        }
    } else {
        left_vol_diff = 0;
        right_vol_diff = 0;
    }
    bt_ull_streaming_t streaming = {
        .port = 0,
    };
    if (BT_ULL_STREAMING_INTERFACE_UNKNOWN == interface) {
        app_wireless_mic_rx_get_active_interface(interfaces_list);
        for (i = 0; i < APP_WIRELESS_MIC_OUTPUT_TYPE_MAX; i++) {
            if (BT_ULL_STREAMING_INTERFACE_UNKNOWN != interfaces_list[i]) {
                streaming.streaming_interface = interfaces_list[i];
                status = bt_ull_le_srv_set_safety_mode_volume(&streaming, left_vol_diff, right_vol_diff);
            }
        }
    } else {
        streaming.streaming_interface = interface,
        status = bt_ull_le_srv_set_safety_mode_volume(&streaming, left_vol_diff, right_vol_diff);
    }
    APPS_LOG_MSGID_I(LOG_TAG", app_wireless_mic_rx_set_safety_mode : %d, status: 0x%x", 2, safety_mode, status);
}
#endif /* AIR_WIRELESS_MIC_RX_ENABLE */

#ifdef ARC_APP
#else /* !ARC_APP */
#include "bt_device_manager_le.h"
#include "hal_rtc_internal.h"        // CHARGER_STATE_EOC

static int32_t mapRange(int32_t value, int32_t inMin, int32_t inMax, int32_t outMin, int32_t outMax)
{
    if (value > inMax)
    {
        // TODO: why here?
        value = inMax;
    }
    else if (value < inMin)
    {
        value = inMin;
    }

    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

static void arc_dp_recored_print_display_record(tx_device_index_t index, arc_dp_recored_tx_data_t *record)
{
    APPS_LOG_MSGID_E("arc_dp_recored_print_display_record: num_id %x addr:%02x:%02x:%02x:%02x:%02x:%02x connected %d", 8,
                                                    index,
                                                    record->addr.addr[5],
                                                    record->addr.addr[4],
                                                    record->addr.addr[3],
                                                    record->addr.addr[2],
                                                    record->addr.addr[1],
                                                    record->addr.addr[0],
                                                    record->connected);
}

static bool arc_dp_recored_is_connected_device(bt_addr_t *addr)
{
    bt_addr_t addr_list[APP_WIRELESS_MIC_TX_NUM_MAX];
    uint8_t tx_mic_amount = APP_WIRELESS_MIC_TX_NUM_MAX;
    bt_status_t bt_status = app_ull_dongle_le_get_connected_device_list(addr_list, &tx_mic_amount);

    if (BT_STATUS_SUCCESS != bt_status) return FALSE;

    uint16_t i;
    for (i = 0; i < tx_mic_amount; i++)
    {
        if (0 == memcmp(&addr_list[i], addr, sizeof(bt_addr_t)))
        {
            return TRUE;
        }
    }

    return FALSE;
}

static void arc_dp_recored_get_rssi_start(void)
{
    ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_1);
    ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_2);
    ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_1, NULL, 0, NULL, 500);
}

static void arc_dp_recored_get_rssi_stop(void)
{
    ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_1);
    ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_2);
}

#define RSSI_IN_MIN               (-128)
#define RSSI_IN_MAX               (-1)
#define RSSI_OUT_MIN              (0)
#define RSSI_OUT_MAX              (100)

bool arc_dp_recored_tx_device_is_connected(tx_device_index_t index)
{
    return g_arc_app.tx_data[index].connected;
}

bool arc_dp_recored_update_display_record_rssi(bt_addr_t *addr, int8_t rssi)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].rssi = mapRange(rssi, RSSI_IN_MIN, RSSI_IN_MAX, RSSI_OUT_MIN, RSSI_OUT_MAX);

            return TRUE;
        }
    }

    return FALSE;
}

int8_t arc_dp_recored_update_display_record_get_rssi(tx_device_index_t index)
{
    return g_arc_app.tx_data[index].rssi;
}

uint8_t arc_dp_recored_update_display_record_laguage(void)
{
    return g_arc_app.setting.rx_setting.laguage;
}

static bool arc_dp_recored_update_display_record_mute_status(bt_addr_t *addr, bool                mic_mute)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].mic_mute = mic_mute;

            return TRUE;
        }
    }

    return FALSE;
}

static bool arc_dp_recored_update_display_record_record_status(bt_addr_t *addr, bool recording)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].recording = recording;

            return TRUE;
        }
    }

    return FALSE;
}

static bool arc_dp_recored_update_display_record_battery(bt_addr_t *addr, uint8_t battery_percent)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].battery_percent = battery_percent;

            return TRUE;
        }
    }

    return FALSE;
}

int8_t arc_dp_recored_update_display_record_get_battery(tx_device_index_t index)
{
    return g_arc_app.tx_data[index].battery_percent;
}

#define VOLUME_IN_MIN               (-9600)
#define VOLUME_IN_MAX               (-600)
#define VOLUME_OUT_MIN              (0)
#define VOLUME_OUT_MAX              (150)

static bool arc_dp_recored_update_display_record_volume(bt_addr_t *addr, int32_t volume)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].volume = mapRange(volume, VOLUME_IN_MIN, VOLUME_IN_MAX, VOLUME_OUT_MIN, VOLUME_OUT_MAX);

            return TRUE;
        }
    }

    return FALSE;
}

int32_t arc_dp_recored_update_display_record_get_volume(tx_device_index_t index)
{
    return g_arc_app.tx_data[index].volume;
}

static tx_device_index_t arc_dp_recored_get_index_by_address(bt_addr_t *addr)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            break;
        }
    }

    return index;
}

static void arc_dp_recored_update_display_record_connection_info(void)
{
    bt_device_manager_le_bonded_info_t *latest_bonded_info = bt_device_manager_le_get_latest_bonded_info();
    bt_device_manager_le_bonded_info_t *second_latest_bonded_info = bt_device_manager_le_get_second_latest_bonded_info();
    
    if (latest_bonded_info != NULL && second_latest_bonded_info != NULL)
    {
        if(memcmp(&latest_bonded_info->bt_addr, &second_latest_bonded_info->bt_addr, sizeof(bt_bd_addr_t)) > 0)
        {
            memcpy(&g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr, &latest_bonded_info->bt_addr, sizeof(bt_addr_t));
            memcpy(&g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr, &second_latest_bonded_info->bt_addr, sizeof(bt_addr_t));
        }
        else
        {
            memcpy(&g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr, &latest_bonded_info->bt_addr, sizeof(bt_addr_t));
            memcpy(&g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr, &second_latest_bonded_info->bt_addr, sizeof(bt_addr_t));
        }

        g_arc_app.tx_data[TX_DEVICE_INDEX_1].connected = arc_dp_recored_is_connected_device(&g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr);
        g_arc_app.tx_data[TX_DEVICE_INDEX_2].connected = arc_dp_recored_is_connected_device(&g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr);

        arc_dp_recored_print_display_record(TX_DEVICE_INDEX_1, &g_arc_app.tx_data[TX_DEVICE_INDEX_1]);
        arc_dp_recored_print_display_record(TX_DEVICE_INDEX_2, &g_arc_app.tx_data[TX_DEVICE_INDEX_2]);

        return;
    }
    else if (latest_bonded_info != NULL)
    {
        memcpy(&g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr, &latest_bonded_info->bt_addr, sizeof(bt_addr_t));
        g_arc_app.tx_data[TX_DEVICE_INDEX_1].connected = arc_dp_recored_is_connected_device(&g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr);

        arc_dp_recored_print_display_record(TX_DEVICE_INDEX_1, &g_arc_app.tx_data[TX_DEVICE_INDEX_1]);

        /* No second device found, clear as default. */
        memset(&g_arc_app.tx_data[TX_DEVICE_INDEX_2], 0, sizeof(arc_dp_recored_tx_data_t));

        return;
    }

    return;
}

static bool arc_dp_recored_update_display_record_fw_version(bt_addr_t *addr, uint8_t major, uint8_t minor, uint8_t revision)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].major = major;
            g_arc_app.tx_data[index].minor = minor;
            g_arc_app.tx_data[index].revision = revision;

            return TRUE;
        }
    }

    return FALSE;
}

bool arc_dp_recored_update_display_record_get_fw_version(tx_device_index_t index, uint8_t *major, uint8_t *minor, uint8_t *revision)
{
    *major = g_arc_app.tx_data[index].major;
    *minor = g_arc_app.tx_data[index].minor;
    *revision = g_arc_app.tx_data[index].revision;

    return TRUE;
}

bool arc_dp_recored_update_display_record_get_rx_fw_version(uint8_t *major, uint8_t *minor, uint8_t *revision)
{
    unsigned int major_tmp = 0;
    unsigned int minor_tmp = 0;
    unsigned int revision_tmp = 0;
    if (sscanf(FOTA_DEFAULT_VERSION, "v%x.%x.%x", &major_tmp, &minor_tmp, &revision_tmp))
    {
        APPS_LOG_MSGID_I(LOG_TAG" Rx fw version: v%d.%d.%d", 3, major_tmp, minor_tmp, revision_tmp);

        *major = major_tmp;
        *minor = minor_tmp;
        *revision = revision_tmp;

        return TRUE;
    }
    return FALSE;
}

static bool arc_dp_recored_update_display_record_set_tx_device_param(bt_addr_t *addr, uint8_t *data, uint8_t data_len)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.tx_data[index].tx_device_status = data[0];
            g_arc_app.setting.tx_setting[index].audio_status1 = data[1];
            g_arc_app.setting.tx_setting[index].audio_status2 = data[2];
            g_arc_app.setting.tx_setting[index].mic_gain = data[3];
            g_arc_app.tx_data[index].file_number = data[4];
            g_arc_app.tx_data[index].recording_file_size_1 = data[5];
            g_arc_app.tx_data[index].recording_file_size_2 = data[6];
            g_arc_app.tx_data[index].recording_file_size_3 = data[7];
            g_arc_app.tx_data[index].recording_file_size_4 = data[8];

            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            return TRUE;
        }
    }

    return FALSE;
}

#include "smartcharger.h"

static bool arc_dp_recored_update_display_record_set_tx_device_param_extra(bt_addr_t *addr, uint8_t *data, uint8_t data_len)
{
    uint16_t index;
    for (index = TX_DEVICE_INDEX_1; index < TX_DEVICE_INDEX_MAX; index++)
    {
        if (0 == memcmp(&g_arc_app.tx_data[index].addr, addr, sizeof(bt_addr_t)))
        {
            g_arc_app.setting.tx_setting[index].audio_statusN = data[0];

            // copy back to Rx.
            g_arc_app.setting.rx_setting.eq_mode = GET_BITS(g_arc_app.setting.tx_setting[index].audio_statusN, NXP_TX_AUDIO_STATUS_N_EQ_MODE_BIT, 0x03);

            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            return TRUE;
        }
    }

    return FALSE;
}

bool arc_dp_recored_update_display_record_get_tx_device_param(tx_device_index_t index, uint8_t *out_data, uint8_t out_data_len)
{
    if (out_data_len < 9)
    {
        assert(0);
    }

    if (index >= TX_DEVICE_INDEX_MAX)
    {
        return FALSE;
    }

    const bool is_rf_connected = g_arc_app.tx_data[index].connected;
    if (is_rf_connected)
    {
        SET_BIT(g_arc_app.tx_data[index].tx_device_status, NXP_TX_DEVICE_STATUS_RF_CONNECTED_BIT);
    }
    else
    {
        CLR_BIT(g_arc_app.tx_data[index].tx_device_status, NXP_TX_DEVICE_STATUS_RF_CONNECTED_BIT);
    }

    out_data[0] = g_arc_app.tx_data[index].tx_device_status;
    out_data[1] = g_arc_app.setting.tx_setting[index].audio_status1;
    out_data[2] = g_arc_app.setting.tx_setting[index].audio_status2;
    out_data[3] = g_arc_app.setting.tx_setting[index].mic_gain;
    out_data[4] = g_arc_app.tx_data[index].file_number;
    out_data[5] = g_arc_app.tx_data[index].recording_file_size_1;
    out_data[6] = g_arc_app.tx_data[index].recording_file_size_2;
    out_data[7] = g_arc_app.tx_data[index].recording_file_size_3;
    out_data[8] = g_arc_app.tx_data[index].recording_file_size_4;

    return TRUE;
}

bool arc_dp_recored_update_display_record_get_rx_device_param(uint8_t *out_data, uint8_t out_data_len)
{
    if (out_data_len < 4)
    {
        assert(0);
    }

    uint8_t mono_or_setero_or_safety_mode = 0;
    if (g_arc_app.setting.rx_setting.safety_mode)
    {
        mono_or_setero_or_safety_mode = 2;
    }
    else if (g_arc_app.setting.rx_setting.mono_or_setero)
    {
        mono_or_setero_or_safety_mode = 1;
    }

    out_data[0] = g_arc_app.setting.rx_setting.lr_2_rl;
    out_data[1] = mono_or_setero_or_safety_mode;
    out_data[2] = g_arc_app.setting.rx_setting.eq_mode;
    out_data[3] = g_arc_app.setting.rx_setting.rx_gain;

    return TRUE;
}

void arc_dp_recored_set_rtc_time(rtc_time_setting_src_t src, uint8_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
{
    hal_rtc_time_t  time;
    memset(&time, 0, sizeof(time));
    time.rtc_year = year;
    time.rtc_mon = mon;
    time.rtc_day = day;
    time.rtc_hour = hour;
    time.rtc_min = min;
    time.rtc_sec = sec;
    hal_rtc_set_time(&time);

    {
        arc_dp_rtc_time_setting_t rtc_time_setting = {0};
        rtc_time_setting.src = src;
        rtc_time_setting.year = year;
        rtc_time_setting.mon = mon;
        rtc_time_setting.day = day;
        rtc_time_setting.hour = hour;
        rtc_time_setting.min = min;
        rtc_time_setting.sec = sec;
        nvkey_write_data(NVID_CUS_RTC_TIME_SETTING, (const uint8_t *) &(rtc_time_setting), sizeof(arc_dp_rtc_time_setting_t));
    }

    g_arc_app.rx_data.rtc_init_check = true;
}
#endif /* ARC_APP */

#include "app_smcharger.h"

static bool app_ull_dongle_idle_internal_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    /* UI shell internal event must process by this activity, so default is true. */
    bool ret = true;
    switch (event_id) {
        case EVENT_ID_SHELL_SYSTEM_ON_CREATE: {
            APPS_LOG_MSGID_I(LOG_TAG", create", 0);
            USB_HOST_TYPE usb_host_type = Get_USB_Host_Type();
            APPS_LOG_MSGID_I(LOG_TAG", create usb_host_type=%d", 1, usb_host_type);
#ifdef AIR_MS_GIP_ENABLE
            if (usb_host_type == USB_HOST_TYPE_XBOX) {
            } else {
                // Need to power up security_chip in non-xbox mode, then let it auto enter sleep mode in order to power_saving.
                // (active mode) 10mA, (sleep mode) 0.055mA
                extern void ms_gip_i2c_init(void);
                ms_gip_i2c_init();
            }
#endif

#ifdef ARC_APP
#else /* !ARC_APP */
            {
                uint32_t size = 0;
                nvkey_status_t status = NVKEY_STATUS_ERROR;

                size =  sizeof(arc_dp_recored_rx_setting_t) + sizeof(arc_dp_recored_tx_setting_t) * 2;
                status = nvkey_read_data(NVID_CUS_APP_SETTING, (uint8_t *)&(g_arc_app.setting), &size);
                if (NVKEY_STATUS_OK == status)
                {
                    /* Nothing to do, these setting should be uesed only after bt connected.
                           uint8_t    lr_2_rl;
                           uint8_t    mono_or_setero_or_safety_mode;
                           uint8_t    rx_gain;
                     */
                }
                else
                {
                    APPS_LOG_MSGID_I(LOG_TAG"Read NVID_CUS_APP_SETTING faild=%d", 1, status);
                    /* TODO: err handle. */
                }
            }

            // func: set rx gain.
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_SET_RX_GAIN, (void *)(uint32_t)(g_arc_app.setting.rx_setting.rx_gain), 0, NULL, 0);

            arc_dp_recored_update_display_record_connection_info();

            {
                uint32_t size = 0;
                nvkey_status_t status = NVKEY_STATUS_ERROR;
                arc_dp_rtc_time_setting_t rtc_time_setting = {0};

                size =  sizeof(rtc_time_setting);
                status = nvkey_read_data(NVID_CUS_RTC_TIME_SETTING, (uint8_t *)&(rtc_time_setting), &size);
                if (NVKEY_STATUS_OK == status)
                {
                    hal_rtc_time_t rtc_time;
                    hal_rtc_get_time(&rtc_time);

                    uint32_t rtc_time_sec = rtc_internal_time_to_tick(rtc_time.rtc_year, rtc_time.rtc_mon, rtc_time.rtc_day,
                                                                      rtc_time.rtc_hour, rtc_time.rtc_min, rtc_time.rtc_sec);
                    uint32_t rtc_time_setting_sec = rtc_internal_time_to_tick(rtc_time_setting.year, rtc_time_setting.mon, rtc_time_setting.day,
                                                                              rtc_time_setting.hour, rtc_time_setting.min, rtc_time_setting.sec);
                    if (rtc_time_sec > rtc_time_setting_sec)
                    {
                        g_arc_app.rx_data.rtc_init_check = true;
                    }
                    else
                    {
                        APPS_LOG_MSGID_I(LOG_TAG"Rtc time is lost, battery disconnected or over discharged.", 0);
                        g_arc_app.rx_data.rtc_init_check = false;
                    }
                }
                else
                {
                    APPS_LOG_MSGID_I(LOG_TAG"Read NVID_CUS_RTC_TIME_SETTING faild=%d", 1, status);
                    g_arc_app.rx_data.rtc_init_check = false;
                }

                /* RTC time may be incorrent, but we can still see how long the time has passed from it. */
                ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_PRINT_RTC_TIME, NULL, 0, NULL, 500);
            }
#endif /* ARC_APP */
            break;
        }
        case EVENT_ID_SHELL_SYSTEM_ON_DESTROY: {
            APPS_LOG_MSGID_I(LOG_TAG", destroy", 0);
            break;
        }
        case EVENT_ID_SHELL_SYSTEM_ON_RESUME: {
            APPS_LOG_MSGID_I(LOG_TAG", resume", 0);
            break;
        }
        case EVENT_ID_SHELL_SYSTEM_ON_PAUSE: {
            APPS_LOG_MSGID_I(LOG_TAG", pause", 0);
            break;
        }
        case EVENT_ID_SHELL_SYSTEM_ON_REFRESH: {
            APPS_LOG_MSGID_I(LOG_TAG", refresh", 0);
            break;
        }
        case EVENT_ID_SHELL_SYSTEM_ON_RESULT: {
            APPS_LOG_MSGID_I(LOG_TAG", result", 0);
            break;
        }
        default:
            break;
    }
    return ret;
}

static bool app_ull_dongle_idle_key_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    bool ret = false;
    apps_config_key_action_t action;
    if (extra_data) {
        action = *(uint16_t *)extra_data;
    } else {
        return ret;
    }

    switch (action) {
        case KEY_DONGLE_CONTROL_RECORD:
            apps_dongle_sync_event_send_extra(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_LOCAL_RECORDER, NULL, 0);
            ret = true;
            break;
        case KEY_DONGLE_CONTROL_MUTE_MIC:
            apps_dongle_sync_event_send_extra(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_MUTE, NULL, 0);
            ret = true;
            break;
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)

#ifdef AIR_ULL_DONGLE_LINE_OUT_ENABLE
#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
        case KEY_VOICE_UP:
        case KEY_VOICE_DN: {
            app_ull_dongle_change_volume_level_for_interface(action == KEY_VOICE_UP, BT_ULL_STREAMING_INTERFACE_LINE_OUT);
            ret = true;
            break;
        }
#endif
#endif
#endif
        default:
            break;
    }

    return ret;
}

#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
/**
* @brief      This function receive some USB event.
* @param[in]  self, the context pointer of the activity.
* @param[in]  event_id, the current event ID to be handled.
* @param[in]  extra_data, extra data pointer of the current event, NULL means there is no extra data.
* @param[in]  data_len, the length of the extra data. 0 means extra_data is NULL.
* @return     If return true, the current event cannot be handle by the next activity.
*/
static bool app_ull_dongle_idle_ull_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    bool ret = false;
    APPS_LOG_MSGID_I(LOG_TAG", received ull event id: %x", 1, event_id);
    switch (event_id) {
#if defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
        case BT_ULL_EVENT_LE_CONNECTED :
        case BT_ULL_EVENT_LE_DISCONNECTED : {
            app_ull_dongle_le_srv_event_callback(event_id, extra_data, data_len);
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
            app_wireless_mic_rx_set_audio_transmit_info_to_all_interface(NULL, 0);
            if (BT_ULL_EVENT_LE_CONNECTED == event_id) {
                if (extra_data && data_len) {
                    bt_ull_le_connected_info_t *conn_info = (bt_ull_le_connected_info_t *)extra_data;
                    bt_addr_t *le_address = app_ull_dongle_le_get_bt_addr_by_conn_handle(conn_info->conn_handle);
                    if (le_address) {
                        uint8_t safety_mode = 0;
                        uint32_t safety_mode_size = sizeof(safety_mode);
                        nvkey_read_data(NVID_APP_WM_SAFETY_MODE, &safety_mode, &safety_mode_size);
                        app_wireless_mic_rx_send_safety_mode_to_tx(safety_mode, &(le_address->addr));
                    }
                }
            }
#endif
#ifdef ARC_APP
#else /* !ARC_APP */
            arc_dp_recored_update_display_record_connection_info();

            if (app_ull_dongle_le_is_connected())
            {
                arc_dp_recored_get_rssi_start();
            }
            else
            {
                arc_dp_recored_get_rssi_stop();
            }

            /* Update setting to tx on CONNECTED, must do after arc_dp_recored_update_display_record_connection_info(). */
            if (BT_ULL_EVENT_LE_CONNECTED == event_id)
            {
                if (extra_data && data_len)
                {
                    bt_ull_le_connected_info_t *conn_info = (bt_ull_le_connected_info_t *)extra_data;
                    bt_addr_t *le_address = app_ull_dongle_le_get_bt_addr_by_conn_handle(conn_info->conn_handle);
                    if (le_address)
                    {
                        tx_device_index_t index = arc_dp_recored_get_index_by_address(le_address);

                        if (TX_DEVICE_INDEX_MAX != index)
                        {
//                            HWJ: use tx setting instead.
//                            {
//                                uint8_t tmp_data[3];
//                                tmp_data[0] = g_arc_app.setting.tx_setting[index].audio_status1;
//                                tmp_data[1] = g_arc_app.setting.tx_setting[index].audio_status2;
//                                tmp_data[2] = g_arc_app.setting.tx_setting[index].mic_gain;
//
//                                /* Pass it to Tx. */
//                                apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM,
//                                                                             tmp_data, 3,
//                                                                             &(g_arc_app.tx_data[index].addr.addr));
//                            }

                            if(!g_arc_app.rx_data.rtc_init_check)
                            {
                                APPS_LOG_MSGID_I(LOG_TAG"Rtc time trying to recover.", 0);
                                /* Local time is lost, try to recover from remote. */
                                apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_GET_RTC_TIME,
                                                                             NULL, 0,
                                                                             &(g_arc_app.tx_data[index].addr.addr));
                            }
                            else
                            {
                                uint8_t tmp_data[8];
                                tmp_data[0] = g_arc_app.setting.rx_setting.laguage;
                                hal_rtc_time_t time;
                                hal_rtc_get_time(&time);
                                tmp_data[1] = time.rtc_year;
                                tmp_data[2] = time.rtc_mon;
                                tmp_data[3] = time.rtc_day;
                                tmp_data[4] = time.rtc_hour;
                                tmp_data[5] = time.rtc_min;
                                tmp_data[6] = time.rtc_sec;
                                tmp_data[7] = g_arc_app.rx_data.reserved;

                                /* Pass it to Tx. */
                                apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_SYSTEM_INFO,
                                                                             tmp_data, 8,
                                                                             &(g_arc_app.tx_data[index].addr.addr));
                            }
                        }
                        else
                        {
                            /* TODO: why here? */
                        }
                    }
                }
            }
#endif /* ARC_APP */
        }
        break;    
#endif
        case BT_ULL_EVENT_USB_PLAYING_IND: {
            bt_ull_streaming_t *p_type = (bt_ull_streaming_t *)extra_data;
            if (p_type && sizeof(bt_ull_streaming_t) == data_len) {
#ifdef RACE_FOTA_ACTIVE_MODE_ULL_SUPPORT
                //if (!(race_fota_is_running(TRUE) && race_fota_is_active_mode())) {
                    APPS_LOG_MSGID_I("app_ull_dongle_idle_ull_event_proc:BT_ULL_ACTION_START_STREAMING", 0);
                    bt_ull_action(BT_ULL_ACTION_START_STREAMING, p_type, sizeof(bt_ull_streaming_t));
                //}
#else
                bt_ull_action(BT_ULL_ACTION_START_STREAMING, p_type, sizeof(bt_ull_streaming_t));
#endif
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULLA_DONGLE_MUSIC_PLAYING, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case BT_ULL_EVENT_USB_STOP_IND: {
            bt_ull_streaming_t *p_type = (bt_ull_streaming_t *)extra_data;
            if (p_type && sizeof(bt_ull_streaming_t) == data_len) {
                bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, p_type, sizeof(bt_ull_streaming_t));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULLA_DONGLE_MUSIC_STOP, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case BT_ULL_EVENT_USB_SAMPLE_RATE_IND: {
            bt_ull_sample_rate_t *p_sample = (bt_ull_sample_rate_t *)extra_data;
            if (p_sample && sizeof(bt_ull_sample_rate_t) == data_len) {
                bt_ull_action(BT_ULL_ACTION_SET_STREAMING_SAMPLE_RATE, p_sample, sizeof(bt_ull_sample_rate_t));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULLA_DONGLE_MUSIC_SAMPLE_RATE, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case BT_ULL_EVENT_USB_VOLUME_IND: {
            bt_ull_volume_t *p_vol = (bt_ull_volume_t *)extra_data;
            if (p_vol && sizeof(bt_ull_volume_t) == data_len) {
                bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, p_vol, sizeof(bt_ull_volume_t));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULLA_DONGLE_MUSIC_VOLUME, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case BT_ULL_EVENT_USB_MUTE_IND: {
            bt_ull_streaming_t *p_type = (bt_ull_streaming_t *)extra_data;
            if (p_type && sizeof(bt_ull_streaming_t) == data_len) {
                bt_ull_action(BT_ULL_ACTION_SET_STREAMING_MUTE, p_type, sizeof(bt_ull_streaming_t));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULLA_DONGLE_MUSIC_MUTE, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case BT_ULL_EVENT_USB_UNMUTE_IND: {
            bt_ull_streaming_t *p_type = (bt_ull_streaming_t *)extra_data;
            if (p_type && sizeof(bt_ull_streaming_t) == data_len) {
                bt_ull_action(BT_ULL_ACTION_SET_STREAMING_UNMUTE, p_type, sizeof(bt_ull_streaming_t));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULLA_DONGLE_MUSIC_UNMUTE, but data not correct", 0);
            }
            ret = true;
            break;
        }
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
        case BT_ULL_EVENT_LE_STREAMING_START_IND: {
            bt_ull_le_streaming_start_ind_t *start_stream = (bt_ull_le_streaming_start_ind_t *)extra_data;
            if (start_stream) {
                APPS_LOG_MSGID_E(LOG_TAG", received BT_ULL_EVENT_LE_STREAMING_START_IND mode:%d,", 1, start_stream->stream.streaming_interface);
                if (BT_ULL_STREAMING_INTERFACE_MICROPHONE == start_stream->stream.streaming_interface
#ifdef AIR_ULL_DONGLE_LINE_OUT_ENABLE
                    || BT_ULL_STREAMING_INTERFACE_LINE_OUT == start_stream->stream.streaming_interface
#endif
#ifdef AIR_DONGLE_I2S_SLV_OUT_ENABLE
                    || BT_ULL_STREAMING_INTERFACE_I2S_OUT == start_stream->stream.streaming_interface
#endif
                    ) {
                    app_wireless_mic_rx_set_safety_mode(false, start_stream->stream.streaming_interface);
                    app_wireless_mic_rx_set_audio_transmit_info_to_single_interface(start_stream->stream.streaming_interface);
                }
            }
            break;
        }
#endif
#ifdef ARC_APP
#else /* !ARC_APP */
        case BT_ULL_EVENT_LE_GET_RSSI_1:
        {
            bt_addr_t *addr = &g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr;

            uint16_t handle = app_ull_dongle_le_get_conn_handle_by_addr(addr);
            if (BT_HANDLE_INVALID != handle) {
                bt_hci_cmd_read_rssi_t read_rssi = {
                    .handle = handle,
                };
                if (BT_STATUS_SUCCESS == bt_gap_le_read_rssi(&read_rssi)) {
                    //APPS_LOG_MSGID_I(LOG_TAG", bt_gap_le_read_rssi, success", 0);
                } else {
                    APPS_LOG_MSGID_I(LOG_TAG", bt_gap_le_read_rssi, fail", 0);
                }
            }

            /* Cannot read rssi concurrently. */
            if (g_arc_app.tx_data[TX_DEVICE_INDEX_2].connected)
            {
                ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_2, NULL, 0, NULL, 500);
            }
            else
            {
                ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_1, NULL, 0, NULL, 500);
            }
        }
        ret = true;
        break;

        case BT_ULL_EVENT_LE_GET_RSSI_2:
        {
            bt_addr_t *addr = &g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr;

            uint16_t handle = app_ull_dongle_le_get_conn_handle_by_addr(addr);
            if (BT_HANDLE_INVALID != handle) {
                bt_hci_cmd_read_rssi_t read_rssi = {
                    .handle = handle,
                };
                if (BT_STATUS_SUCCESS == bt_gap_le_read_rssi(&read_rssi)) {
                    //APPS_LOG_MSGID_I(LOG_TAG", bt_gap_le_read_rssi, success", 0);
                } else {
                    APPS_LOG_MSGID_I(LOG_TAG", bt_gap_le_read_rssi, fail", 0);
                }
            }

            /* Cannot read rssi concurrently. */
            if (g_arc_app.tx_data[TX_DEVICE_INDEX_1].connected)
            {
                ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_1, NULL, 0, NULL, 500);
            }
            else
            {
                ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_LE_GET_RSSI_2, NULL, 0, NULL, 500);
            }
        }
        ret = true;
        break;

        case BT_ULL_EVENT_SETTING_UPDATE:
        {
            nvkey_write_data(NVID_CUS_APP_SETTING, (const uint8_t *) &(g_arc_app.setting), sizeof(arc_dp_recored_rx_setting_t) + sizeof(arc_dp_recored_tx_setting_t) * 2);
        }
        ret = true;
        break;

        case BT_ULL_EVENT_PRINT_RTC_TIME:
        {
            hal_rtc_time_t rtc_time;
            hal_rtc_get_time(&rtc_time);

            uint32_t date = 0;
            uint32_t time = 0;

            date = (rtc_time.rtc_year / 1000) << 28;
            date |= ((rtc_time.rtc_year / 100) % 10) << 24;
            date |= ((rtc_time.rtc_year / 10) % 10) << 20;
            date |= ((rtc_time.rtc_year) % 10) << 16;

            date |= ((rtc_time.rtc_mon / 10)) << 12;
            date |= ((rtc_time.rtc_mon) % 10) << 8;

            date |= ((rtc_time.rtc_day / 10)) << 4;
            date |= ((rtc_time.rtc_day) % 10);

            time |= ((rtc_time.rtc_hour / 10) % 10) << 20;
            time |= ((rtc_time.rtc_hour) % 10) << 16;

            time |= ((rtc_time.rtc_min / 10)) << 12;
            time |= ((rtc_time.rtc_min) % 10) << 8;

            time |= ((rtc_time.rtc_sec / 10)) << 4;
            time |= ((rtc_time.rtc_sec) % 10);

            APPS_LOG_MSGID_I(LOG_TAG"NOW: %08x-%06x", 2, date, time);

            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_PRINT_RTC_TIME, NULL, 0, NULL, 30 * 1000);
        }
        ret = true;
        break;

        case BT_ULL_EVENT_USER_PAIRING_END_TIMEOUT:
        {
            if (app_ull_dongle_le_sirk_is_null())
            {
                /* HWJ: Sirk is null but we still have tx to connect, so must be in bonded device list. */
                app_ull_dongle_le_scan_device(APP_ULL_DONGLE_LE_SCAN_BONDED_DEVICE);
            }
            else
            {
                /* HWJ: Continue to connect the next device if we have sirk only, such as just burning and writing sirk by charging case. */
                app_ull_dongle_le_scan_device(APP_ULL_DONGLE_LE_SCAN_COORDINATED_SET_BY_SIRK);
            }
        }
        ret = true;
        break;

#endif /* ARC_APP */
        default:
            break;
    }

    return ret;
}

static void app_ull_dongle_idle_set_sample_info(uint8_t interface_id, bool update_sample_rate, bool update_size_channel)
{
    const apps_usb_interface_enable_app_task_recorder_t *interface_status = app_preproc_activity_get_usb_interface_info(interface_id);
    APPS_LOG_MSGID_I(LOG_TAG", app_ull_dongle_idle_set_sample_info[%d]", 1, interface_id);
    if (interface_status == NULL) {
        return;
    }
    bt_ull_streaming_t stream = {
        .streaming_interface = BT_ULL_STREAMING_INTERFACE_UNKNOWN,
    };
#if defined(AIR_USB_AUDIO_ENABLE) && !defined(APPS_USB_AUDIO_SUPPORT)
    if (interface_id == APPS_USB_EVENTS_INTERFACE_SPEAKER_CHAT) {
        stream.port = 1;
        stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
    }
#ifdef AIR_USB_AUDIO_2_SPK_ENABLE
    else if (interface_id == APPS_USB_EVENTS_INTERFACE_SPEAKER_GAMING) {
        stream.port = 0;
        stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
    }
#endif
#endif

#ifdef AIR_USB_AUDIO_1_MIC_ENABLE
    if (interface_id == APPS_USB_EVENTS_INTERFACE_MIC) {
        stream.port = 0;
        stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
    }
#endif
    if (stream.streaming_interface == BT_ULL_STREAMING_INTERFACE_UNKNOWN) {
        return;
    }

    if (update_size_channel) {
/******************************** sample_size ****************************************************/
        bt_ull_streaming_sample_size_t sample_size;
        sample_size.streaming = stream;
        sample_size.sample_size = interface_status->sample_size;
        APPS_LOG_MSGID_I(LOG_TAG", APPS_EVENTS_USB_AUDIO_SAMPLE_SIZE[%d], sample_size:0x%x", 2, interface_id, sample_size.sample_size);
        if (sample_size.sample_size != 0) {
            bt_ull_action(BT_ULL_ACTION_SET_STREAMING_SAMPLE_SIZE, &sample_size, sizeof(sample_size));
        }
/******************************** sample_size ****************************************************/
/******************************** Channel ****************************************************/
        bt_ull_streaming_sample_channel_t sample_channel;
        sample_channel.streaming = stream;
        sample_channel.sample_channel = interface_status->channel;
        APPS_LOG_MSGID_I(LOG_TAG", APPS_EVENTS_USB_AUDIO_CHANNEL[%d], sample_channel:0x%x", 2, interface_id, sample_channel.sample_channel);
        if (sample_channel.sample_channel != 0) {
            bt_ull_action(BT_ULL_ACTION_SET_STREAMING_SAMPLE_CHANNEL, &sample_channel, sizeof(sample_channel));
        }
/******************************** Channel ****************************************************/
    }

/******************************** sample_rate ****************************************************/
    if (update_sample_rate && interface_status->sample_rate != 0) {
        bt_ull_sample_rate_t sp_rate;
        sp_rate.streaming = stream;
        sp_rate.sample_rate = interface_status->sample_rate;
        APPS_LOG_MSGID_I(LOG_TAG", APPS_EVENTS_USB_AUDIO_SAMPLE_RATE[%d], sample_rate:0x%x", 2, interface_id, sp_rate.sample_rate);
        bt_ull_action(BT_ULL_ACTION_SET_STREAMING_SAMPLE_RATE, &sp_rate, sizeof(sp_rate));
    }
/******************************** sample_size ****************************************************/
}

static bool app_ull_dongle_idle_usb_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    bool ret = false;
    uint32_t usb_data = (uint32_t)extra_data;
    APPS_LOG_MSGID_I(LOG_TAG", received usb event id: 0x%x, extra_data:0x%x", 2, event_id, extra_data);

    switch (event_id) {
        case APPS_EVENTS_USB_AUDIO_PLAY:
        case APPS_EVENTS_USB_AUDIO_STOP:
        case APPS_EVENTS_USB_AUDIO_UNPLUG: {
            app_events_usb_port_t *p_port = (app_events_usb_port_t *) & (usb_data);
            bt_ull_streaming_t stream;
            if (!p_port) {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_PLAY, but data not correct", 0);
                break;
            }
            uint8_t interface_id = apps_event_usb_get_interface_id_from_port_info(p_port);
            const apps_usb_interface_enable_app_task_recorder_t *interface_status = app_preproc_activity_get_usb_interface_info(interface_id);
            if (interface_status && interface_status->enabled) {
                if (APP_USB_AUDIO_SPK_PORT == p_port->port_type) {
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_port->port_num) {
                        stream.port = 0;    /* gaming */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_gaming_play     = true;
#endif
                    } else {
                        stream.port = 1;    /* chat */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_chat_play       = true;
#endif
                    }
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                    app_ull_dongle_change_mix_ratio();
#endif
                } else {
                    g_app_ull_dongle_context.usb_out_play = true;
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    stream.port = 0;        /* mic */
                }

#ifdef RACE_FOTA_ACTIVE_MODE_ULL_SUPPORT
                if (!(race_fota_is_running(TRUE) && race_fota_is_active_mode()))
#endif
                {
                    APPS_LOG_MSGID_I("app_ull_dongle_idle_usb_event_proc:BT_ULL_ACTION_START_STREAMING[%d]", 1, interface_id);
                    app_ull_dongle_idle_set_sample_info(interface_id, false, true);
                    bt_ull_action(BT_ULL_ACTION_START_STREAMING, &stream, sizeof(stream));
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
                    app_wireless_mic_rx_set_safety_mode(false, BT_ULL_STREAMING_INTERFACE_MICROPHONE);
                    app_wireless_mic_rx_set_audio_transmit_info_to_single_interface(BT_ULL_STREAMING_INTERFACE_MICROPHONE);
#endif
                }
                APPS_LOG_MSGID_I(LOG_TAG", received APPS_EVENTS_USB_AUDIO_PLAY[%d]: stream_interface=0x%02x, stream_port=%d",
                        3, interface_id, stream.streaming_interface, stream.port);
                app_ull_dongle_idle_set_sample_info(interface_id, true, false);
            } else if (interface_status) {
                bt_ull_streaming_t stream;
                if (APP_USB_AUDIO_SPK_PORT == p_port->port_type) {
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_port->port_num) {
                        stream.port = 0;    /* gaming */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_gaming_play     = false;
#endif
                    } else {
                        stream.port = 1;    /* chat */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_chat_play       = false;
#endif
                    }
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                    app_ull_dongle_change_mix_ratio();
#endif
                } else {
                    g_app_ull_dongle_context.usb_out_play = false;
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    stream.port = 0;        /* mic */
                }
                APPS_LOG_MSGID_I(LOG_TAG", received APPS_EVENTS_USB_AUDIO_STOP[%d]: stream_interface=0x%02x, stream_port=%d",
                                        3, interface_id, stream.streaming_interface, stream.port);
                bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
            }
            break;
        }
#if 0
        case APPS_EVENTS_USB_AUDIO_PLAY: {
            app_events_usb_port_t *p_port = (app_events_usb_port_t *) & (usb_data);
            if (p_port) {
                bt_ull_streaming_t stream;
                if (APP_USB_AUDIO_SPK_PORT == p_port->port_type) {
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_port->port_num) {
                        stream.port = 0;    /* gaming */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_gaming_play     = true;
#endif
                    } else {
                        stream.port = 1;    /* chat */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_chat_play       = true;
#endif
                    }
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                    app_ull_dongle_change_mix_ratio();
#endif
                } else {
                    g_app_ull_dongle_context.usb_out_play = true;
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    stream.port = 0;        /* mic */
                }
#ifdef RACE_FOTA_ACTIVE_MODE_ULL_SUPPORT
                //if (!(race_fota_is_running(TRUE) && race_fota_is_active_mode())) {
                    APPS_LOG_MSGID_I("app_ull_dongle_idle_usb_event_proc:BT_ULL_ACTION_START_STREAMING", 0);
                    bt_ull_action(BT_ULL_ACTION_START_STREAMING, &stream, sizeof(stream));
                //}
#else
                bt_ull_action(BT_ULL_ACTION_START_STREAMING, &stream, sizeof(stream));
#endif
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
                app_wireless_mic_rx_set_safety_mode(false, BT_ULL_STREAMING_INTERFACE_MICROPHONE);
                app_wireless_mic_rx_set_audio_transmit_info_to_single_interface(BT_ULL_STREAMING_INTERFACE_MICROPHONE);
#endif
                APPS_LOG_MSGID_I(LOG_TAG", received APPS_EVENTS_USB_AUDIO_PLAY: stream_interface=0x%02x, stream_port=%d",
                        2, stream.streaming_interface, stream.port);
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_PLAY, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case APPS_EVENTS_USB_AUDIO_STOP:
        case APPS_EVENTS_USB_AUDIO_UNPLUG: {
            app_events_usb_port_t *p_port = (app_events_usb_port_t *) & (usb_data);
            if (p_port) {
                bt_ull_streaming_t stream;
                if (APP_USB_AUDIO_SPK_PORT == p_port->port_type) {
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_port->port_num) {
                        stream.port = 0;    /* gaming */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_gaming_play     = false;
#endif
                    } else {
                        stream.port = 1;    /* chat */
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                        g_app_ull_dongle_context.spk_chat_play       = false;
#endif
                    }
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                    app_ull_dongle_change_mix_ratio();
#endif
                } else {
                    g_app_ull_dongle_context.usb_out_play = false;
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    stream.port = 0;        /* mic */
                }
                APPS_LOG_MSGID_I(LOG_TAG", received APPS_EVENTS_USB_AUDIO_STOP: stream_interface=0x%02x, stream_port=%d",
                                        2, stream.streaming_interface, stream.port);
                bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_STOP, but data not correct", 0);
            }
            ret = true;
            break;
        }
#endif
        case APPS_EVENTS_USB_AUDIO_VOLUME: {
            app_events_usb_volume_t *p_vol = (app_events_usb_volume_t *)extra_data;
            if (p_vol) {
                APPS_LOG_MSGID_I(LOG_TAG", db is l=%d, r=%d", 2, p_vol->left_db, p_vol->right_db);
                bt_ull_volume_t vol;
                if (APP_USB_AUDIO_SPK_PORT == p_vol->port_type) {
                    vol.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_vol->port_num) {
                        vol.streaming.port = 0;    /* gaming */
                    } else {
                        vol.streaming.port = 1;    /* chat */
                    }
                } else {
                    vol.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    vol.streaming.port = 0;        /* mic */
                }
                vol.action = BT_ULL_VOLUME_ACTION_SET_ABSOLUTE_VOLUME;
                /* L/R channel volue is same */
                if (p_vol->left_volume == p_vol->right_volume) {
                    vol.channel = BT_ULL_AUDIO_CHANNEL_DUAL;
                    vol.volume = p_vol->left_volume;
                    //vol.gain = p_vol->left_db;
                    bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &vol, sizeof(vol));
                } else {
                    if (0xFF != p_vol->left_volume) {
                        vol.channel = BT_ULL_AUDIO_CHANNEL_LEFT;
                        vol.volume = p_vol->left_volume;
                        //vol.gain = p_vol->left_db;
                        bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &vol, sizeof(vol));
                    }
                    if (0xFF != p_vol->right_volume) {
                        vol.channel = BT_ULL_AUDIO_CHANNEL_RIGHT;
                        vol.volume = p_vol->right_volume;
                        //vol.gain = p_vol->right_db;
                        bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &vol, sizeof(vol));
                    }
                }
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_VOLUME, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case APPS_EVENTS_USB_AUDIO_MUTE: {
            app_events_usb_mute_t *p_mute = (app_events_usb_mute_t *) & (usb_data);
            if (p_mute) {
                bt_ull_streaming_t stream;
                if (APP_USB_AUDIO_SPK_PORT == p_mute->port_type) {
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_mute->port_num) {
                        stream.port = 0;    /* gaming */
                    } else {
                        stream.port = 1;    /* chat */
                    }
                } else {
                    stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    stream.port = 0;        /* mic */
                }
                if (p_mute->is_mute) {
                    bt_ull_action(BT_ULL_ACTION_SET_STREAMING_MUTE, &stream, sizeof(stream));
                } else {
                    bt_ull_action(BT_ULL_ACTION_SET_STREAMING_UNMUTE, &stream, sizeof(stream));
                }
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_MUTE, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case APPS_EVENTS_USB_AUDIO_SAMPLE_RATE: {
            app_events_usb_sample_rate_t *p_rate = (app_events_usb_sample_rate_t *) & (usb_data);
            if (p_rate) {
                uint8_t interface_id = apps_event_usb_get_interface_id_from_port_info(&p_rate->port);
                app_ull_dongle_idle_set_sample_info(interface_id, true, true);
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_SAMPLE_RATE, but data not correct", 0);
            }
            ret = true;
            break;
        }
#if 0
        case APPS_EVENTS_USB_AUDIO_SAMPLE_SIZE: {
            app_events_usb_sample_size_t *p_sample_size = (app_events_usb_sample_size_t *)&(usb_data);
            if (NULL != p_sample_size) {
                bt_ull_streaming_sample_size_t sample_size;
                if (APP_USB_AUDIO_SPK_PORT == p_sample_size->port_type) {
                    sample_size.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_sample_size->port_num) {
                        sample_size.streaming.port = 0;    /* gaming */
                    } else {
                        sample_size.streaming.port = 1;    /* chat */
                    }
                } else {
                    sample_size.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    sample_size.streaming.port = 0;        /* mic */
                }
                sample_size.sample_size = p_sample_size->size;
                APPS_LOG_MSGID_I(LOG_TAG", APPS_EVENTS_USB_AUDIO_SAMPLE_SIZE, sample_rate:0x%x", 1, sample_size.sample_size);
                if (sample_size.sample_size != 0) {
                    bt_ull_action(BT_ULL_ACTION_SET_STREAMING_SAMPLE_SIZE, &sample_size, sizeof(sample_size));
                }
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_SAMPLE_SIZE, but data not correct", 0);
            }
            ret = true;
            break;
        }
        case APPS_EVENTS_USB_AUDIO_CHANNEL: {
            app_events_usb_channel_t *p_channel = (app_events_usb_channel_t *)&(usb_data);
            if (NULL != p_channel) {
                bt_ull_streaming_sample_channel_t sample_channel;
                if (APP_USB_AUDIO_SPK_PORT == p_channel->port_type) {
                    sample_channel.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
                    if (1 == p_channel->port_num) {
                        sample_channel.streaming.port = 0;    /* gaming */
                    } else {
                        sample_channel.streaming.port = 1;    /* chat */
                    }
                } else {
                    sample_channel.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
                    sample_channel.streaming.port = 0;        /* mic */
                }
                sample_channel.sample_channel = p_channel->channel;
                APPS_LOG_MSGID_I(LOG_TAG", APPS_EVENTS_USB_AUDIO_CHANNEL, sample_rate:0x%x", 1, sample_channel.sample_channel);
                if (sample_channel.sample_channel != 0)
                    bt_ull_action(BT_ULL_ACTION_SET_STREAMING_SAMPLE_CHANNEL, &sample_channel, sizeof(sample_channel));
            } else {
                APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_CHANNEL, but data not correct", 0);
            }
            ret = true;
            break;
        }
#endif
        case APPS_EVENTS_USB_AUDIO_RESET: {
#if defined(AIR_USB_AUDIO_ENABLE)
            bt_ull_streaming_t stream;
            /* stop gaming */
            stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
            stream.port = 0;    /* gaming */
            bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
            /* stop chat */
            stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
            stream.port = 1;    /* chat */
            bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
            /* stop mic */
            stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_MICROPHONE;
            stream.port = 0;    /* mic */
            bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
            ret = true;
#endif
            break;
        }
        case APPS_EVENTS_USB_AUDIO_SUSPEND: {
            APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_SUSPEND, but no handler", 0);
            break;
        }
        case APPS_EVENTS_USB_AUDIO_RESUME: {
            APPS_LOG_MSGID_E(LOG_TAG", received APPS_EVENTS_USB_AUDIO_RESUME, but no handler", 0);
            break;
        }
        default:
            break;
    }

    return ret;
}

static bool app_ull_dongle_send_data_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    bool ret = false;
    app_ull_user_data_t *ull_app_data = NULL;
    switch (event_id) {
        case ULL_EVT_DONGLE_MODE: {
            bt_bd_addr_t addr_list = {0};
            if (bt_cm_get_connected_devices(BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_CUSTOMIZED_ULL), &addr_list, 1)) {
                bt_ull_user_data_t tx_data;
                memcpy(&(tx_data.remote_address), addr_list, sizeof(bt_bd_addr_t));
                ull_app_data = (app_ull_user_data_t *)pvPortMalloc(sizeof(app_ull_user_data_t));
                if (ull_app_data) {
                    ull_app_data->user_evt = ULL_EVT_DONGLE_MODE;
                    ull_app_data->data_len = 1;
                    ull_app_data->data[0] = g_dongle_mode;
                    tx_data.user_data = (uint8_t *)ull_app_data;
                    tx_data.user_data_length = sizeof(app_ull_user_data_t);
                    bt_ull_action(BT_ULL_ACTION_TX_USER_DATA, &tx_data, sizeof(tx_data));
                    vPortFree(ull_app_data);
                }
            }
#if defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
            else {
                bt_ull_user_data_t tx_data;
                bt_addr_t address_list[BT_ULL_LE_MAX_LINK_NUM];
                uint8_t count = BT_ULL_LE_MAX_LINK_NUM;
                uint8_t i;
                if (BT_STATUS_SUCCESS != app_ull_dongle_le_get_connected_device_list(address_list, &count)) {
                    count = 0;
                }
                ull_app_data = (app_ull_user_data_t *)pvPortMalloc(sizeof(app_ull_user_data_t));
                if(ull_app_data) {
                    ull_app_data->user_evt = ULL_EVT_DONGLE_MODE;
                    ull_app_data->data_len = 1;
                    ull_app_data->data[0] = g_dongle_mode;
                    tx_data.user_data = (uint8_t *)ull_app_data;
                    tx_data.user_data_length = sizeof(app_ull_user_data_t);
                    for (i = 0; i < count; i++) {
                        memcpy(tx_data.remote_address, address_list[i].addr, sizeof(bt_bd_addr_t));
                        bt_ull_action(BT_ULL_ACTION_TX_USER_DATA, &tx_data, sizeof(tx_data));
                    }

                    APPS_LOG_MSGID_I("Send user data by ULL Dongle LE", 0);
                    vPortFree(ull_app_data);
                }
            }
#endif
            ret = true;
            break;
        }
        default:
            break;
    }
    return ret;
}
#endif

#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
#ifdef AIR_ULL_DONGLE_LINE_OUT_ENABLE
void app_ull_dongle_set_lineout_volume_value(uint8_t value)
{
    bt_status_t bt_status = BT_STATUS_FAIL;
    bt_ull_volume_t vol = {0};
    vol.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_OUT;
    vol.streaming.port                = 0;
    vol.action                        = BT_ULL_VOLUME_ACTION_SET_ABSOLUTE_VOLUME;
    vol.channel                       = BT_ULL_AUDIO_CHANNEL_DUAL;
    vol.volume                        = value;
    bt_status = bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &vol, sizeof(vol));
    if (bt_status == BT_STATUS_SUCCESS) {
        g_app_ull_dongle_context.lineout_volume_values = value;
    }
    APPS_LOG_MSGID_I(LOG_TAG" app_ull_set_line_out_volume_value :value=%d, status=0x%x", 2, value, bt_status);
}
#endif

#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
void app_ull_dongle_set_linein_volume_value(uint8_t value)
{
    bt_status_t bt_status = BT_STATUS_FAIL;
    bt_ull_volume_t vol = {0};
    vol.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_IN;
    vol.streaming.port                = 0;
    vol.action                        = BT_ULL_VOLUME_ACTION_SET_ABSOLUTE_VOLUME;
    vol.channel                       = BT_ULL_AUDIO_CHANNEL_DUAL;
    vol.volume                        = value;
    bt_status = bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &vol, sizeof(vol));
    if (bt_status == BT_STATUS_SUCCESS) {
        g_app_ull_dongle_context.linein_volume_values = value;
    }
    APPS_LOG_MSGID_I(LOG_TAG" app_ull_set_line_in_volume_value :value=%d, status=0x%x", 2, value, bt_status);
}

void app_ull_dongle_change_linein_volume_level(bool up)
{
    bt_status_t bt_status = BT_STATUS_FAIL;
    bt_ull_volume_t volume_param = {0};
    volume_param.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_IN;
    volume_param.streaming.port = 0;
    volume_param.channel = BT_ULL_VOLUME_CHANNEL_DUEL;
    volume_param.volume = 10; /* The delta value. */
    if (up) {
        volume_param.action = BT_ULL_VOLUME_ACTION_SET_UP;
    } else {
        volume_param.action = BT_ULL_VOLUME_ACTION_SET_DOWN;
    }
    bt_status = bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &volume_param, sizeof(volume_param));
    APPS_LOG_MSGID_I(LOG_TAG" app_ull_change_line_in_volume :is_up=%d, status=0x%x", 2, up, bt_status);
}

void app_ull_dongle_change_mix_ratio(void)
{
    bt_status_t bt_status         = BT_STATUS_FAIL;
    uint8_t spk_gaming_ratio      = 0;
    uint8_t spk_chat_ratio        = 0;
    uint8_t line_in_ratio         = 0;
    bt_ull_mix_ratio_t mix_ratio  = {0};
    mix_ratio.num_streaming       = BT_ULL_MAX_STREAMING_NUM;

    if (!g_app_ull_dongle_context.line_in) {
        spk_gaming_ratio = APP_LINE_IN_MIX_RATIO_MAX_LEVEL;
        spk_chat_ratio   = APP_LINE_IN_MIX_RATIO_MAX_LEVEL;
        line_in_ratio    = APP_LINE_IN_MIX_RATIO_MIN_LEVEL;
    } else {
        if (g_app_ull_dongle_context.spk_gaming_play || g_app_ull_dongle_context.spk_chat_play) {
            spk_gaming_ratio = APP_LINE_IN_MIX_RATIO_BALANCED_LEVEL;
            spk_chat_ratio   = APP_LINE_IN_MIX_RATIO_BALANCED_LEVEL;
            line_in_ratio    = APP_LINE_IN_MIX_RATIO_BALANCED_LEVEL;
        } else if (!g_app_ull_dongle_context.spk_gaming_play && !g_app_ull_dongle_context.spk_chat_play) {
            spk_gaming_ratio = APP_LINE_IN_MIX_RATIO_MIN_LEVEL;
            spk_chat_ratio   = APP_LINE_IN_MIX_RATIO_MIN_LEVEL;
            line_in_ratio    = APP_LINE_IN_MIX_RATIO_MAX_LEVEL;
        }
    }

    mix_ratio.streamings[0].streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_SPEAKER;
    if (g_app_ull_dongle_context.spk_gaming_play) {
        mix_ratio.streamings[0].streaming.port = 0; /* gaming streaming port */
        mix_ratio.streamings[0].ratio = spk_gaming_ratio;
    } else {
        mix_ratio.streamings[0].streaming.port = 1; /* chat streaming port */
        mix_ratio.streamings[0].ratio = spk_chat_ratio;
    }

    mix_ratio.streamings[1].streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_IN;
    mix_ratio.streamings[1].streaming.port = 0; /* line in streaming port */
    mix_ratio.streamings[1].ratio = line_in_ratio;

    bt_status = bt_ull_action(BT_ULL_ACTION_SET_STREAMING_MIX_RATIO, &mix_ratio, sizeof(mix_ratio));
    APPS_LOG_MSGID_I(LOG_TAG" app_ull_dongle_change_mix_ratio: spk_gaming_ratio=%d, spk_chat_ratio=%d, line_in_ratio=%d, status=0x%x",
            4, spk_gaming_ratio, spk_chat_ratio, line_in_ratio, bt_status);
}

static bool app_ull_dongle_get_line_in_streaming_is_playing(void)
{
    bool ret = false;
    bt_ull_streaming_info_t info = {0};
    bt_ull_streaming_t streaming = {
        .streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_IN,
        .port = 0,
    };

    if ((BT_STATUS_SUCCESS == bt_ull_get_streaming_info(streaming,&info)) && info.is_playing) {
        ret = true;
    }
    APPS_LOG_MSGID_I(LOG_TAG" line_in_streaming_is_playing=%d", 1, ret);
    return ret;
}
#endif

#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
void app_ull_dongle_change_volume_level_for_interface(bool up, bt_ull_streaming_interface_t interface)
{
#ifdef AIR_WIRELESS_MIC_RX_ENABLE
    bt_status_t bt_status = BT_STATUS_FAIL;
    bt_ull_volume_t volume_param = {0};
    volume_param.streaming.streaming_interface = interface;
    volume_param.streaming.port = 0;
    volume_param.channel = BT_ULL_VOLUME_CHANNEL_DUEL;
    volume_param.action = BT_ULL_VOLUME_ACTION_SET_ABSOLUTE_VOLUME;
    uint8_t current_volume = bt_ull_le_srv_get_streaming_volume(&volume_param.streaming);
    if (up) {
        volume_param.volume = current_volume + 10;
        if (volume_param.volume > 100) {
            volume_param.volume = 100;
        }
    } else {
        volume_param.volume = current_volume > 10 ? current_volume - 10 : 0;
    }
    bt_status = bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &volume_param, sizeof(volume_param));
    APPS_LOG_MSGID_I(LOG_TAG" app_ull_change_[%x]_volume :is_up=%d, volume = %d, status=0x%x", 4, interface, up, volume_param.volume, bt_status);
#endif
}
#endif

extern bool chg_stat_changed_debouning;
extern bool s_prev_chg_stat;
extern const char BSP_CHG_CE_PIN;

#if defined(AIR_ULL_DONGLE_LINE_IN_ENABLE) || defined(AIR_ULL_DONGLE_LINE_OUT_ENABLE)
static bool app_ull_dongle_idle_line_in_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    bool ret = false;
    bt_status_t bt_status = BT_STATUS_FAIL;

    switch (event_id) {
        case APPS_EVENTS_INTERACTION_LINE_IN_STATUS: {
            bool line_in_status = (bool)extra_data;
            bt_ull_streaming_t stream = {0};

            stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_IN;
            stream.port = 0;
            if (line_in_status) {
#ifdef RACE_FOTA_ACTIVE_MODE_ULL_SUPPORT
                //if (race_fota_is_running(TRUE) && race_fota_is_active_mode()) {
                //    break;
                //}
#endif
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                g_app_ull_dongle_context.line_in = true;
                if (!app_ull_dongle_get_line_in_streaming_is_playing()) {
                    bt_status = bt_ull_action(BT_ULL_ACTION_START_STREAMING, &stream, sizeof(stream));
                    if (bt_status == BT_STATUS_SUCCESS) {
                        app_ull_dongle_set_linein_volume_value(APP_LINE_IN_DEFAULT_VOLUME_VALUES);
                        app_ull_dongle_change_mix_ratio();
                    }
                }
#endif
#ifdef AIR_ULL_DONGLE_LINE_OUT_ENABLE
                /* line out. */
                g_app_ull_dongle_context.line_out = true;
                stream.streaming_interface        = BT_ULL_STREAMING_INTERFACE_LINE_OUT;
                bt_ull_action(BT_ULL_ACTION_START_STREAMING, &stream, sizeof(stream));
                //app_ull_dongle_set_lineout_volume_value(APP_LINE_OUT_DEFAULT_VOLUME_VALUES);
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
                app_wireless_mic_rx_set_safety_mode(false, BT_ULL_STREAMING_INTERFACE_LINE_OUT);
                app_wireless_mic_rx_set_audio_transmit_info_to_single_interface(BT_ULL_STREAMING_INTERFACE_LINE_OUT);
#endif /* AIR_WIRELESS_MIC_RX_ENABLE */
#endif
            } else {
#ifdef AIR_ULL_DONGLE_LINE_IN_ENABLE
                g_app_ull_dongle_context.line_in  = false;
                if (app_ull_dongle_get_line_in_streaming_is_playing()) {
                    bt_status = bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
                    app_ull_dongle_change_mix_ratio();
                }
#endif
#ifdef AIR_ULL_DONGLE_LINE_OUT_ENABLE
                /* line out. */
                g_app_ull_dongle_context.line_out = false;
                stream.streaming_interface        = BT_ULL_STREAMING_INTERFACE_LINE_OUT;
                bt_status = bt_ull_action(BT_ULL_ACTION_STOP_STREAMING, &stream, sizeof(stream));
#endif
            }
            APPS_LOG_MSGID_I(LOG_TAG",[LINE_IN_DET] received APPS_EVENTS_INTERACTION_LINE_IN_STATUS: line_in_status=%d, bt_status=%d",
                             2, line_in_status, bt_status);
            break;
        }

#ifdef ARC_USB_SW_ENABLE
#else /* !ARC_USB_SW_ENABLE */
        case APPS_EVENTS_INTERACTION_EXT_CHG_STAT_CHANGED_DEBOUNE:
            chg_stat_changed_debouning = false;
            if (s_prev_chg_stat)
            {
                /* STAT High: Charging completed/Charging is disabled or in sleep mode. */
                APPS_LOG_MSGID_I(LOG_TAG" Exteranl charger STAT High after debouning end", 0);
        
                /* Disable external charger. */
                /* do not cannel APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE as we want to enable external charger always. */
                ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST,
                                    EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                    APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE,
                                    NULL, 0, NULL, 60*1000);  // 1min: leave some charger time preventing any error status.
            }
            else
            {
                /* STAT Low: Charging battery (or recharge). */
                APPS_LOG_MSGID_I(LOG_TAG" Exteranl charger STAT Low after debouning end", 0);
        
                /* Enable external charger. */
                ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_INTERACTION, APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE);
                ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST,
                                    EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                    APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE,
                                    NULL, 0, NULL, 130);
            }
            break;
        case APPS_EVENTS_INTERACTION_EXT_CHG_ENABLE:
            {
                APPS_LOG_MSGID_I(LOG_TAG" Exteranl charger enable", 0);
                hal_gpio_set_output(BSP_CHG_CE_PIN, HAL_GPIO_DATA_LOW);
            }
            break;
        case APPS_EVENTS_INTERACTION_EXT_CHG_DISABLE:
            {
                APPS_LOG_MSGID_I(LOG_TAG" Exteranl charger disable", 0);
                hal_gpio_set_output(BSP_CHG_CE_PIN, HAL_GPIO_DATA_HIGH);
            }
            break;
#endif /* ARC_USB_SW_ENABLE */

        default:
            break;
    }

    return ret;
}
#endif
#endif //AIR_BT_ULTRA_LOW_LATENCY_ENABLE or AIR_BLE_ULTRA_LOW_LATENCY_ENABLE

#ifdef MTK_RACE_CMD_ENABLE
static bool app_ull_dongle_idle_proc_tx_status_events(struct _ui_shell_activity *self,
                                                         uint32_t event_id,
                                                         void *extra_data,
                                                         size_t data_len)
{
    bool ret             = false;
#if (defined AIR_BLE_ULTRA_LOW_LATENCY_ENABLE) && (defined AIR_WIRELESS_MIC_ENABLE)
    apps_dongle_event_sync_info_t *pkg = (apps_dongle_event_sync_info_t *)extra_data;
    if (pkg == NULL) {
        APPS_LOG_MSGID_W(LOG_TAG" tx_status_events: pkg is NULL!", 0);
        return ret;
    }
    /* EVENT_GROUP_UI_SHELL_WIRELESS_MIC is 50 and it must be same on dongle and headset!!! */
    if (pkg->event_group == EVENT_GROUP_UI_SHELL_WIRELESS_MIC) {
        app_ull_dongle_race_remote_control_type_t control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_INVALID;
        APPS_LOG_MSGID_I(LOG_TAG" tx_status_event, type=%d data_len=%d.", 2, pkg->event_id, pkg->extra_data_len);
        switch (pkg->event_id) {
            /* The Teams application handshake with dongle done. */
            case APPS_EVENTS_TX_MIC_STATUS: {
                bool mute_status = false;
                if (pkg->extra_data_len != 0) {
                    memcpy(&mute_status, pkg->data, sizeof(bool));
                    control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_MUTE_MIC;
                    APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: mute_status=%d", 1, mute_status);
#ifdef ARC_APP
#else /* !ARC_APP */
                    bt_addr_t addr = {0};
                    uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                    arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                    arc_dp_recored_update_display_record_mute_status(&addr, mute_status);
#endif /* ARC_APP */
                }
                break;
            }
            /* It will not be received now. */
            case APPS_EVENTS_TX_RECORDER_STATUS: {
                bool record_status = false;
                if (pkg->extra_data_len != 0) {
                    memcpy(&record_status, pkg->data, sizeof(bool));
                    control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_RECORD;
                    APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: record_status=%d", 1, record_status);
#ifdef ARC_APP
#else /* !ARC_APP */
                    bt_addr_t addr = {0};
                    uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                    arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                    arc_dp_recored_update_display_record_record_status(&addr, record_status);
#endif /* ARC_APP */
                }
                break;
            }
            case APPS_EVENTS_TX_BATTERY_STATUS: {
                uint8_t battery_percent = 0;
                if (pkg->extra_data_len != 0) {
                    memcpy(&battery_percent, pkg->data, sizeof(uint8_t));
                    control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_BATTERY;
                    APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: battery_percent=%d", 1, battery_percent);
#ifdef ARC_APP
#else /* !ARC_APP */
                    bt_addr_t addr = {0};
                    uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                    arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                    arc_dp_recored_update_display_record_battery(&addr, battery_percent);
#endif /* ARC_APP */
                }
                break;
            }
            case APPS_EVENTS_TX_VOLUME_STATUS: {
                int32_t volume_data = 0;
                if (pkg->extra_data_len != 0) {
                    memcpy(&volume_data, pkg->data, sizeof(int32_t));
                    control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_TX_VOLUME;
                    APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: volume=%d", 1, volume_data);
#ifdef ARC_APP
#else /* !ARC_APP */
                    bt_addr_t addr = {0};
                    uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                    arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                    arc_dp_recored_update_display_record_volume(&addr, volume_data);
#endif /* ARC_APP */
                }
                break;
            }
#ifdef ARC_APP
#else /* !ARC_APP */
            case APPS_EVENTS_TX_FW_VERSION:
            {
                if (6 == pkg->extra_data_len)
                {
                    // control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_BATTERY;  HWJ: TODO: To check what is it?

                    unsigned int major = 0;
                    unsigned int minor = 0;
                    unsigned int revision = 0;
                    if (sscanf((char *)(pkg->data), "v%x.%x.%x", &major, &minor, &revision))
                    {
                        APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: v%d.%d.%d", 3, major, minor, revision);

                        bt_addr_t addr = {0};
                        uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                        arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                        arc_dp_recored_update_display_record_fw_version(&addr, major, minor, revision);
                    }
                }
            }
            break;
#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
            case APPS_EVENTS_TX_SET_TX_DEVICE_PARAM:
            {
                uint8_t temp_data[9] = {0};    /* 9: TEMP_DATA_LEN */
                if (pkg->extra_data_len != 0)
                {
                    memcpy(temp_data, pkg->data, 9);    /* 9: TEMP_DATA_LEN */
                    // control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_BATTERY;  HWJ: TODO: To check what is it?

                    APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: %x %x %x %x %x %x %x %x %x", 9,
                        temp_data[0], temp_data[1], temp_data[2], temp_data[3], temp_data[4],
                        temp_data[5], temp_data[6], temp_data[7], temp_data[8]);

                    bt_addr_t addr = {0};
                    uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                    arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                    arc_dp_recored_update_display_record_set_tx_device_param(&addr, temp_data, 9);    /* 9: TEMP_DATA_LEN */
                }
            }
            break;

            case APPS_EVENTS_TX_SET_TX_DEVICE_PARAM_EXTRA:
            {
                uint8_t temp_data[3] = {0};    /* 3: TEMP_DATA_LEN */
                if (pkg->extra_data_len != 0)
                {
                    memcpy(temp_data, pkg->data, 3);    /* 3: TEMP_DATA_LEN */
                    // control_type = APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_BATTERY;  HWJ: TODO: To check what is it?

                    APPS_LOG_MSGID_I(LOG_TAG" tx_status_events: %x %x %x", 3,
                        temp_data[0], temp_data[1], temp_data[2]);

                    bt_addr_t addr = {0};
                    uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
                    arc_apps_dongle_race_cmd_get_addr_from_channel_id(&addr, channel_id);
                    arc_dp_recored_update_display_record_set_tx_device_param_extra(&addr, temp_data, 3);    /* 3: TEMP_DATA_LEN */
                }
            }
            break;

            case APPS_EVENTS_TX_GET_RTC_TIME_RSP:
            {
                uint8_t temp_data[7] = {0};    /* 7: TEMP_DATA_LEN */
                if (pkg->extra_data_len != 0)
                {
                    memcpy(temp_data, pkg->data, 7);    /* 7: TEMP_DATA_LEN */
                    if (temp_data[0])
                    {
                        APPS_LOG_MSGID_I(LOG_TAG"Rtc time recover ok.", 0);
                        arc_dp_recored_set_rtc_time(RTC_TIME_SETTING_FROM_AIR,
                                                    temp_data[1], temp_data[2], temp_data[3], temp_data[4], temp_data[5], temp_data[6]);
                    }
                    else
                    {
                        APPS_LOG_MSGID_I(LOG_TAG"Rtc time recover fail.", 0);
                    }
                }
            }
            break;
#endif /* ARC_NXP_COM_ENABLE */
#endif /* ARC_APP */
            default:
                break;
        }


//        if (control_type != APP_ULL_DONGLE_RACE_REMOTE_CONTROL_TYPE_INVALID) {
//            uint8_t channel_id = *(((uint8_t *)extra_data) + data_len);
//            apps_dongle_race_cmd_on_remote_control_state_change(control_type, pkg->data[0], channel_id);
//        }

    }
#endif
    return ret;
}
#endif

#include "apps_events_i2s_in_event.h"

static bool app_ull_dongle_idle_handle_i2s_in_event(ui_shell_activity_t *self,
                                        uint32_t event_id,
                                        void *extra_data,
                                        size_t data_len)
{
    bool ret = false;

#ifdef AIR_DONGLE_I2S_SLV_OUT_ENABLE
    if (APPS_EVENTS_I2S_IN_STATUS_CHANGE == event_id && NULL != extra_data) {
#ifdef RACE_FOTA_ACTIVE_MODE_ULL_SUPPORT
        //if (race_fota_is_running(TRUE) && race_fota_is_active_mode()) {
        //    return ret;
        //}
#endif
#if defined(AIR_WIRELESS_MIC_RX_ENABLE)
        app_i2s_in_det_t *i2s_param = (app_i2s_in_det_t *)extra_data;
        bt_ull_streaming_t stream = {0};
        stream.streaming_interface = BT_ULL_STREAMING_INTERFACE_I2S_OUT;
        bt_ull_action_t action;
        g_app_ull_dongle_context.i2s_out = i2s_param->i2s_state;
        if (i2s_param->i2s_state) { 
            action = BT_ULL_ACTION_START_STREAMING;
        } else {
            action = BT_ULL_ACTION_STOP_STREAMING;
        }
        bt_ull_action(action, &stream, sizeof(stream));
        if (BT_ULL_ACTION_START_STREAMING == action) {
            app_wireless_mic_rx_set_safety_mode(false, BT_ULL_STREAMING_INTERFACE_I2S_OUT);
            app_wireless_mic_rx_set_audio_transmit_info_to_single_interface(BT_ULL_STREAMING_INTERFACE_I2S_OUT);
        }
#endif
    }
#endif

    return ret;
}

#ifdef ARC_APP
#else /* !ARC_APP */
#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */

static void arc_dp_recored_lr_2_rl_changed(void)
{
    // See app_wireless_mic_rx_query_audio_mode().
    app_wireless_mic_rx_set_audio_transmit_info_to_all_interface(NULL, 0);
}

static void arc_dp_recored_mono_or_setero_or_safety_mode_changed(void)
{
    if (g_arc_app.setting.rx_setting.safety_mode)
    {
        // Only allow safety mode in setero mode.
        // See app_wireless_mic_rx_query_audio_mode().
        app_wireless_mic_rx_set_audio_transmit_info_to_all_interface(NULL, 0);

        uint8_t safety_mode = 0;
        uint32_t safety_mode_size = sizeof(safety_mode);
        nvkey_read_data(NVID_APP_WM_SAFETY_MODE, &safety_mode, &safety_mode_size);
        if (safety_mode == 0) {
            app_wireless_mic_rx_set_safety_mode(true, BT_ULL_STREAMING_INTERFACE_UNKNOWN);
        }
    }
    else
    {
        uint8_t safety_mode = 0;
        uint32_t safety_mode_size = sizeof(safety_mode);
        nvkey_read_data(NVID_APP_WM_SAFETY_MODE, &safety_mode, &safety_mode_size);
        if (safety_mode == 1) {
            app_wireless_mic_rx_set_safety_mode(true, BT_ULL_STREAMING_INTERFACE_UNKNOWN);
        }

        // Set mono mode or setero mode
        // See app_wireless_mic_rx_query_audio_mode().
        app_wireless_mic_rx_set_audio_transmit_info_to_all_interface(NULL, 0);
    }
}

#include "app_home_screen_idle_activity.h"

#include "apps_config_key_remapper.h"
#include "smchg_1wire.h"

bool nxp_flags_power_on = FALSE;
bool is_in_pt_mode = FALSE;

static bool arc_nxp_com_event_proc(ui_shell_activity_t *self, uint32_t event_id, void *extra_data, size_t data_len)
{
    /* Nxp com event must process by this activity, so default is true. */
    bool ret = true;
    switch (event_id)
    {
        case NXP_EVENT_SET_TX1_DEVICE_PARAM:
        {
            /* Save in local. */
            uint8_t *tmp_data = (uint8_t *)extra_data;
            g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_1].audio_status1 = tmp_data[0];
            g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_1].audio_status2 = tmp_data[1];
            g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_1].mic_gain = tmp_data[2];

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            /* Pass it to Tx. */
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM,
                                                         extra_data, data_len,
                                                         &(g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr.addr));
        }
        break;

        case NXP_EVENT_SET_TX2_DEVICE_PARAM:
        {
            /* Save in local. */
            uint8_t *tmp_data = (uint8_t *)extra_data;
            g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_2].audio_status1 = tmp_data[0];
            g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_2].audio_status2 = tmp_data[1];
            g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_2].mic_gain = tmp_data[2];

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            /* Pass it to Tx. */
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM,
                                                         extra_data, data_len,
                                                         &(g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr.addr));
        }
        break;

        case NXP_EVENT_SET_LR_2_RL_ONOFF:
        {
            g_arc_app.setting.rx_setting.lr_2_rl = (uint32_t)extra_data;

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            arc_dp_recored_lr_2_rl_changed();
        }
        break;

        case NXP_EVENT_SET_SETERO_OR_SAFETY_MODE:
        {
            uint8_t mono_or_setero_or_safety_mode = (uint32_t)extra_data;

            if (2 == mono_or_setero_or_safety_mode)                       // 2: safety mode
            {
                g_arc_app.setting.rx_setting.safety_mode = 1;
                /* Only allow safety mode in setero mode. */
                g_arc_app.setting.rx_setting.mono_or_setero = 1;
            }
            else if (1 == mono_or_setero_or_safety_mode)                  // 1: setero mode
            {
                g_arc_app.setting.rx_setting.safety_mode = 0;
                g_arc_app.setting.rx_setting.mono_or_setero = 1;
            }
            else                                                          // 0: mono mode
            {
                g_arc_app.setting.rx_setting.safety_mode = 0;
                g_arc_app.setting.rx_setting.mono_or_setero = 0;
            }

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            arc_dp_recored_mono_or_setero_or_safety_mode_changed();
        }
        break;

        case NXP_EVENT_SET_EQ_MODE:
        {
            g_arc_app.setting.rx_setting.eq_mode = (uint32_t)extra_data;

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            // copy it to tx.
            CLR_BITS(g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_1].audio_statusN, NXP_TX_AUDIO_STATUS_N_EQ_MODE_BIT, 0x03);
            SET_BITS(g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_1].audio_statusN, NXP_TX_AUDIO_STATUS_N_EQ_MODE_BIT, g_arc_app.setting.rx_setting.eq_mode & 0x03);
            CLR_BITS(g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_2].audio_statusN, NXP_TX_AUDIO_STATUS_N_EQ_MODE_BIT, 0x03);
            SET_BITS(g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_2].audio_statusN, NXP_TX_AUDIO_STATUS_N_EQ_MODE_BIT, g_arc_app.setting.rx_setting.eq_mode & 0x03);

            uint8_t tmp_data[3];
            /* Pass it to Tx. */
            tmp_data[0] = g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_1].audio_statusN;
            tmp_data[1] = 0;
            tmp_data[2] = 0;
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM_EXTRA,
                                                         tmp_data, 3,
                                                         &(g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr.addr));
            /* Pass it to Tx. */
            tmp_data[0] = g_arc_app.setting.tx_setting[TX_DEVICE_INDEX_2].audio_statusN;
            tmp_data[1] = 0;
            tmp_data[2] = 0;
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_TX_DEVICE_PARAM_EXTRA,
                                                         tmp_data, 3,
                                                         &(g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr.addr));
        }
        break;

        case NXP_EVENT_SET_RX_GAIN:
        {
            g_arc_app.setting.rx_setting.rx_gain = (uint32_t)extra_data;

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            // HWJ: refer to app_ull_dongle_change_volume_level_for_interface.
            {
                bt_status_t bt_status = BT_STATUS_FAIL;
                bt_ull_volume_t volume_param = {0};
                volume_param.streaming.streaming_interface = BT_ULL_STREAMING_INTERFACE_LINE_OUT;
                volume_param.streaming.port = 0;
                volume_param.channel = BT_ULL_AUDIO_CHANNEL_DUAL;
                volume_param.action = BT_ULL_VOLUME_ACTION_SET_ABSOLUTE_VOLUME;
                //uint8_t current_volume = bt_ull_le_srv_get_streaming_volume(&volume_param.streaming);
                uint8_t current_volume = 70;
                if (g_arc_app.setting.rx_setting.rx_gain > 15)
                {
                    volume_param.volume = 15;
                }
                else if (g_arc_app.setting.rx_setting.rx_gain < -15)
                {
                    volume_param.volume = -15;
                }
                volume_param.volume = current_volume + 2 * g_arc_app.setting.rx_setting.rx_gain;
                bt_status = bt_ull_action(BT_ULL_ACTION_SET_STREAMING_VOLUME, &volume_param, sizeof(volume_param));
                APPS_LOG_MSGID_I(LOG_TAG" app_ull_change_volume: volume = %d, status=0x%x", 2, volume_param.volume, bt_status);
            }
        }
        break;

        case NXP_EVENT_SET_SYSTEM_INFO:
        {
            /* Save in local. */
            uint8_t *tmp_data = (uint8_t *)extra_data;
            g_arc_app.setting.rx_setting.laguage = tmp_data[0];
            g_arc_app.rx_data.reserved = tmp_data[7];

            /* Update nvid at changed. */
            ui_shell_remove_event(EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE);
            ui_shell_send_event(false, EVENT_PRIORITY_HIGH, EVENT_GROUP_BT_ULTRA_LOW_LATENCY, BT_ULL_EVENT_SETTING_UPDATE, NULL, 0, NULL, 2000);

            arc_dp_recored_set_rtc_time(RTC_TIME_SETTING_FROM_UART,
                                        tmp_data[1], tmp_data[2], tmp_data[3], tmp_data[4], tmp_data[5], tmp_data[6]);

            /* Pass it to Tx. */
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_SYSTEM_INFO,
                                                         extra_data, data_len,
                                                         &(g_arc_app.tx_data[TX_DEVICE_INDEX_1].addr.addr));
            apps_dongle_sync_event_send_extra_by_address(EVENT_GROUP_UI_SHELL_WIRELESS_MIC, APPS_EVENTS_MIC_CONTROL_SET_SYSTEM_INFO,
                                                         extra_data, data_len,
                                                         &(g_arc_app.tx_data[TX_DEVICE_INDEX_2].addr.addr));
        }
        break;

        case NXP_EVENT_BATTERY_LEVEL_INIT_CHECK:
        {
            battery_basic_data battery_basic_data = battery_management_get_basic_data();
            int32_t battery_voltage = battery_management_get_battery_property(BATTERY_PROPERTY_VOLTAGE);
            APPS_LOG_MSGID_I(LOG_TAG" init battery level: %d shutdown_bat %d", 2, battery_voltage, battery_basic_data.s1_voltage);
            if (battery_voltage <= battery_basic_data.s1_voltage)
            {
                ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_NXP_LDO_ENABLE, (void *)(uint32_t)0, 0, NULL, 0);
            }
            else
            {
                ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_NXP_LDO_ENABLE, (void *)(uint32_t)1, 0, NULL, 0);
            }
        }
        break;

        case SMCHARGER_EVENT_POWERING_ON_TIMEOUT:
        {
            if (bt_device_manager_is_relay_enable())
            {
                APPS_LOG_MSGID_E(LOG_TAG" powering on timeout but relay_enable.", 0);
            }
            else if (apps_config_key_get_mmi_state() == APP_BT_OFF)
            {
                APPS_LOG_MSGID_E(LOG_TAG" power off as missing power on event.", 0);
                /* Do KEY_ULL_AIR_PAIRING */
                uint16_t *p_key_action = (uint16_t *)pvPortMalloc(sizeof(uint16_t));
                if (p_key_action) {
                    *p_key_action = KEY_POWER_OFF;
                    /* The extra_data of the event is key action. */
                    ui_shell_send_event(false,
                                        EVENT_PRIORITY_MIDDLE, EVENT_GROUP_UI_SHELL_KEY,
                                        INVALID_KEY_EVENT_ID,
                                        p_key_action, sizeof(uint16_t), NULL, 0);
                }
            }
        }
        break;

        case NXP_EVENT_NXP_LDO_ENABLE:
        {
            uint32_t ldo_enable = (uint32_t)extra_data;
            static uint32_t ldo_enable_local = -1;

            if (ldo_enable)
            {
                if (ldo_enable_local != 1)
                {
                    ldo_enable_local = 1;

                    nxp_flags_power_on = TRUE;

                    APPS_LOG_MSGID_I(LOG_TAG" open LDO to NXP", 0);
                    hal_rtc_gpio_set_output(HAL_RTC_GPIO_0, HAL_RTC_GPIO_DATA_HIGH);

                    hal_pinmux_set_function(HAL_GPIO_18, HAL_GPIO_18_UART2_TXD);
                    hal_pinmux_set_function(HAL_GPIO_19, HAL_GPIO_19_UART2_RXD);

                    ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_INTERRUPT_SIGNAL, (void *)(uint32_t)1, 0, NULL, 100);
                }
            }
            else
            {
                if (ldo_enable_local != 0)
                {
                    ldo_enable_local = 0;

                    nxp_flags_power_on = FALSE;

                    APPS_LOG_MSGID_I(LOG_TAG" interrupt release.", 0);
                    hal_gpio_set_output(HAL_GPIO_13, HAL_GPIO_DATA_LOW);

                    ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_INTERRUPT_SIGNAL, (void *)(uint32_t)0, 0, NULL, 100);
                }
            }
        }
        break;

        case NXP_EVENT_INTERRUPT_SIGNAL:
        {
            uint32_t interrupt_hold = (uint32_t)extra_data;
            if (interrupt_hold)
            {
                APPS_LOG_MSGID_I(LOG_TAG" interrupt hold.", 0);
                hal_gpio_set_output(HAL_GPIO_13, HAL_GPIO_DATA_HIGH);

                hal_gpio_set_output(HAL_GPIO_14, HAL_GPIO_DATA_LOW);
            }
            else
            {
                hal_pinmux_set_function(HAL_GPIO_18, HAL_GPIO_18_GPIO18);
                hal_gpio_set_direction(HAL_GPIO_18, HAL_GPIO_DIRECTION_INPUT);
                hal_pinmux_set_function(HAL_GPIO_19, HAL_GPIO_19_GPIO19);
                hal_gpio_set_direction(HAL_GPIO_19, HAL_GPIO_DIRECTION_INPUT);

                APPS_LOG_MSGID_I(LOG_TAG" close LDO to NXP", 0);
                hal_rtc_gpio_set_output(HAL_RTC_GPIO_0, HAL_RTC_GPIO_DATA_LOW);
            }
        }
        break;

#ifdef ARC_PRODUCTION_TEST
#else /* !ARC_PRODUCTION_TEST */
        case NXP_EVENT_PT_CMD_SET_MODE:
        {
            APPS_LOG_MSGID_I(LOG_TAG" NXP_EVENT_PT_CMD_SET_MODE", 0);

            uint8_t *tmp_data = (uint8_t *)extra_data;

            if (tmp_data[0])    // != 0
            {
                smchg_pt_force_com_mode(TRUE);

                is_in_pt_mode = TRUE;

                ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_PT_MODE_TIMEOUT, NULL, 0, NULL, 5*60*1000);    // Auto exit for 5min
            }
            else
            {
                smchg_pt_force_com_mode(FALSE);

                is_in_pt_mode = FALSE;

                ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_PT_MODE_TIMEOUT);
            }

            ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_INTERRUPT_SIGNAL, (void *)(uint32_t)1, 0, NULL, 0);
        }
        break;

        case NXP_EVENT_PT_MODE_TIMEOUT:
        {
            APPS_LOG_MSGID_I(LOG_TAG" NXP_EVENT_PT_MODE_TIMEOUT", 0);

            smchg_pt_force_com_mode(FALSE);

            is_in_pt_mode = FALSE;

            ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_INTERRUPT_SIGNAL, (void *)(uint32_t)1, 0, NULL, 0);
        }
        break;
#endif /* ARC_PRODUCTION_TEST */

        case NXP_EVENT_FORCE_POWER_DOWN:
        {
            APPS_LOG_MSGID_I(LOG_TAG" Force Power Down", 0);
            app_home_screen_set_ready_to_off();
            app_home_screen_check_power_off_and_reboot();
        }
        break;

        default:
        {
            APPS_LOG_MSGID_I(LOG_TAG" unexpected nxp event", 0);
        }
        break;
    }

    {
        home_screen_local_context_type_t *home_screen_local_context = app_home_screen_idle_activity_get_context();
        if (home_screen_local_context->state == APP_HOME_SCREEN_STATE_POWERING_OFF || home_screen_local_context->state == APP_HOME_SCREEN_STATE_REBOOT)
        {
            ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_FORCE_POWER_DOWN, NULL, 0, NULL, 5000);
        }
    }

    return ret;
}

#endif /* ARC_NXP_COM_ENABLE */
#endif /* ARC_APP */

#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
static bt_ull_le_srv_call_event_t s_last_event = USB_HID_SRV_EVENT_CALL_END;
#endif
bool app_ull_dongle_idle_activity_proc(
    ui_shell_activity_t *self,
    uint32_t event_group,
    uint32_t event_id,
    void *extra_data,
    size_t data_len)
{
    bool ret = false;
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
    static bool s_muted = false;
#endif

    switch (event_group) {
        case EVENT_GROUP_UI_SHELL_SYSTEM:
            ret = app_ull_dongle_idle_internal_event_proc(self, event_id, extra_data, data_len);

            if (EVENT_ID_SHELL_SYSTEM_ON_CREATE == event_id)
            {
                ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, SMCHARGER_EVENT_POWERING_ON_TIMEOUT, NULL, 0, NULL, 30000);
            }
            break;
        case EVENT_GROUP_UI_SHELL_KEY:
            ret = app_ull_dongle_idle_key_event_proc(self, event_id, extra_data, data_len);
            break;
#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
        case EVENT_GROUP_BT_ULTRA_LOW_LATENCY:
            ret = app_ull_dongle_idle_ull_event_proc(self, event_id, extra_data, data_len);
            break;
        case EVENT_GROUP_ULL_SEND_CUSTOM_DATA:
            ret = app_ull_dongle_send_data_event_proc(self, event_id, extra_data, data_len);
            break;
        case EVENT_GROUP_UI_SHELL_USB_AUDIO:
            ret = app_ull_dongle_idle_usb_event_proc(self, event_id, extra_data, data_len);
            return false;
            //break;
#if defined(AIR_ULL_DONGLE_LINE_IN_ENABLE) || defined(AIR_ULL_DONGLE_LINE_OUT_ENABLE)
        case EVENT_GROUP_UI_SHELL_LINE_IN: {
            ret = app_ull_dongle_idle_line_in_event_proc(self, event_id, extra_data, data_len);
            return false;
            break;
        }
#endif
#endif //AIR_BT_ULTRA_LOW_LATENCY_ENABLE
#ifdef MTK_RACE_CMD_ENABLE
        case EVENT_GROUP_UI_SHELL_DONGLE_DATA: {
            ret = app_ull_dongle_idle_proc_tx_status_events(self, event_id, extra_data, data_len);
            break;
        }
#endif
        case EVENT_GROUP_UI_SHELL_I2S_IN:
            ret = app_ull_dongle_idle_handle_i2s_in_event(self, event_id, extra_data, data_len);
            break;
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
        case EVENT_GROUP_UI_SHELL_USB_HID_CALL: {
            APPS_LOG_MSGID_I("EVENT_GROUP_UI_SHELL_USB_HID_CALL event=%d", 1, event_id);
            bt_ull_le_call_srv_send_event((bt_ull_le_srv_call_event_t)event_id, NULL, 0);
            if (event_id < USB_HID_SRV_EVENT_CALL_MIC_MUTE) {
                s_last_event = (bt_ull_le_srv_call_event_t)event_id;
                if (s_last_event == BT_ULL_LE_SRV_CALL_EVENT_END) {
                    s_muted = false;
                }
            } else if (event_id == BT_ULL_LE_SRV_CALL_EVENT_REMOTE_MIC_MUTE) {
                s_muted = true;
            } else if (event_id == BT_ULL_LE_SRV_CALL_EVENT_REMOTE_MIC_UNMUTE) {
                s_muted = false;
            }
            ui_shell_send_event(false, EVENT_PRIORITY_HIGHEST, EVENT_GROUP_UI_SHELL_APP_INTERACTION,
                                    APPS_EVENTS_INTERACTION_UPDATE_LED_BG_PATTERN, NULL, 0,
                                    NULL, 0);
            break;
        }
        case EVENT_GROUP_UI_SHELL_APP_INTERACTION: {
            if (event_id == APPS_EVENTS_INTERACTION_UPDATE_LED_BG_PATTERN) {
                APPS_LOG_MSGID_I("APPS_EVENTS_INTERACTION_UPDATE_LED_BG_PATTERN last sta=%d, mute=%d", 2, s_last_event, s_muted);
                if (s_last_event == BT_ULL_LE_SRV_CALL_EVENT_INCOMING) {
                    apps_config_set_background_led_pattern(LED_INDEX_INCOMING_CALL, true, APPS_CONFIG_LED_AWS_SYNC_PRIO_MIDDLE);
                }
                else if (s_last_event >= BT_ULL_LE_SRV_CALL_EVENT_ACTIVE && s_last_event <= BT_ULL_LE_SRV_CALL_EVENT_UNHOLD)
                {
                    /* USE the air pairing to indicate the call actite but muted case. */
                    apps_config_set_background_led_pattern(s_muted ? LED_INDEX_AIR_PAIRING: LED_INDEX_CALL_ACTIVE, true, APPS_CONFIG_LED_AWS_SYNC_PRIO_MIDDLE);
                }
                ret = true;
            }
            break;
        }
#endif

#ifdef ARC_APP
#else /* !ARC_APP */
#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
        case EVENT_GROUP_UI_SHELL_BATTERY:
        {
            if (APPS_EVENTS_BATTERY_PERCENT_CHANGE == event_id)
            {
                battery_basic_data battery_basic_data = battery_management_get_basic_data();
                int32_t battery_voltage = battery_management_get_battery_property(BATTERY_PROPERTY_VOLTAGE);
                APPS_LOG_MSGID_I(LOG_TAG" battery level: %d", 1, battery_voltage);
                if (battery_voltage <= battery_basic_data.s1_voltage)
                {
                    ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_NXP_LDO_ENABLE, (void *)(uint32_t)0, 0, NULL, 0);
                }
                else
                {
                    ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_NXP_COM, NXP_EVENT_NXP_LDO_ENABLE, (void *)(uint32_t)1, 0, NULL, 0);
                }
            }
        }
        break;
        /* APP nxp communicate events. */
        case EVENT_GROUP_UI_SHELL_APP_NXP_COM:
        {
            APPS_LOG_MSGID_I(LOG_TAG" NXP group, event_id=%d", 1, event_id);
            ret = arc_nxp_com_event_proc(self, event_id, extra_data, data_len);
        }
#endif /* ARC_NXP_COM_ENABLE */
#endif /* ARC_APP */
        default:
            break;
    }

    return ret;
}

#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
bool app_ull_dongle_has_call_sta() {
    return (s_last_event != BT_ULL_LE_SRV_CALL_EVENT_END);
}
#else
bool app_ull_dongle_has_call_sta() {
    return false;
}
#endif

#ifdef AIR_MS_GIP_ENABLE
//dongle switch
const unsigned char DONGLE_SWITCH_EINT = HAL_GPIO_10;
const unsigned char DONGLE_SWITCH_DET_PIN = HAL_GPIO_10;

static void dongle_switch_detect_callback(void *user_data)
{
    hal_gpio_data_t current_gpio_status = 0;
    hal_eint_mask(DONGLE_SWITCH_EINT);

    hal_gpio_get_input(DONGLE_SWITCH_DET_PIN, &current_gpio_status);
    g_dongle_mode = (current_gpio_status == HAL_GPIO_DATA_HIGH ? APP_DONGLE_MODE_PC : APP_DONGLE_MODE_XBOX_PS);
    APPS_LOG_MSGID_I("dongle_switch, dongle_mode=%d", 1, g_dongle_mode);

#if defined(AIR_BT_ULTRA_LOW_LATENCY_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
    ui_shell_send_event(TRUE, EVENT_PRIORITY_HIGHEST,
                        EVENT_GROUP_UI_SHELL_APP_SERVICE,
                        APP_DONGLE_SERVICE_MODE_SWITCH_EVENT,
                        NULL, 0, NULL, 0);
#endif /* AIR_BT_ULTRA_LOW_LATENCY_ENABLE */
    hal_eint_unmask(DONGLE_SWITCH_EINT);
}

static void dongle_switch_init_set(void)
{
    hal_gpio_data_t current_gpio_status = 0;
    hal_gpio_get_input(DONGLE_SWITCH_DET_PIN, &current_gpio_status);
    g_dongle_mode = (current_gpio_status == HAL_GPIO_DATA_HIGH ? APP_DONGLE_MODE_PC : APP_DONGLE_MODE_XBOX_PS);
    APPS_LOG_MSGID_I("dongle_switch init, g_dongle_mode=%d", 1, g_dongle_mode);

    if (g_dongle_mode == APP_DONGLE_MODE_XBOX_PS) {
        Set_USB_Host_Type(USB_HOST_TYPE_XBOX);
    }
}

void dongle_switch_det_init(void)
{
    hal_eint_config_t config;
    hal_eint_status_t sta;
    APPS_LOG_MSGID_I("dongle_switch_det_init", 0);
    /* For falling and rising detect. */
    config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;
    config.debounce_time = 300;

    hal_gpio_init(DONGLE_SWITCH_DET_PIN);
    hal_eint_mask(DONGLE_SWITCH_EINT);

    sta = hal_eint_init(DONGLE_SWITCH_EINT, &config);
    if (sta != HAL_EINT_STATUS_OK) {
        APPS_LOG_MSGID_E("init dongle_switch eint failed: %d", 1, sta);
        hal_eint_unmask(DONGLE_SWITCH_EINT);
        return;
    }

    sta = hal_eint_register_callback(DONGLE_SWITCH_EINT, dongle_switch_detect_callback, NULL);
    if (sta != HAL_EINT_STATUS_OK) {
        APPS_LOG_MSGID_E("registe dongle_switch eint callback failed: %d", 1, sta);
        hal_eint_unmask(DONGLE_SWITCH_EINT);
        hal_eint_deinit(DONGLE_SWITCH_EINT);
        return;
    }
    hal_eint_unmask(DONGLE_SWITCH_EINT);

    dongle_switch_init_set();
}

#endif /* AIR_MS_GIP_ENABLE */
