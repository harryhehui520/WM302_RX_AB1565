
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

/**
 * File: app_bt_conn_manager.c
 *
 * Description: This file provides BT Connection Manager.
 *
 */

#include "app_bt_conn_manager.h"

#include "app_bt_state_service.h"
#include "apps_debug.h"
#include "apps_events_bt_event.h"
#include "apps_events_event_group.h"
#include "bt_aws_mce_srv.h"
#include "bt_connection_manager.h"
#include "bt_connection_manager_internal.h"
#include "bt_customer_config.h"
#include "bt_device_manager.h"
#include "bt_device_manager_le.h"
#include "bt_device_manager_link_record.h"
#include "bt_hsp.h"
#include "bt_sink_srv_le.h"
#include "bt_iot_device_white_list.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "multi_ble_adv_manager.h"
#include "nvkey.h"
#include "nvkey_id_list.h"
#include "ui_shell_manager.h"

#ifdef MTK_AWS_MCE_ENABLE
#include "apps_aws_sync_event.h"
#endif
#ifdef AIR_MULTI_POINT_ENABLE
#include "app_bt_emp_service.h"
#endif
#ifdef AIR_BT_FAST_PAIR_ENABLE
#include "app_fast_pair.h"
#endif
#if defined(AIR_LE_AUDIO_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
#include "app_lea_service.h"
#include "app_lea_service_adv_mgr.h"
#include "app_lea_service_conn_mgr.h"
#include "app_lea_service_event.h"
#include "app_lea_service_sync_info.h"
#endif
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
#include "app_ull_idle_activity.h"
#include "bt_ull_service.h"
#endif
#ifdef AIR_APP_A2DP_LBB_VENDOR_CODEC_LIMIT
#include "bt_sink_srv_a2dp.h"
#endif
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
#include "bt_ull_le_service.h"
#endif


/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_CONN]"

#ifndef PACKED
#define PACKED  __attribute__((packed))
#endif

#define APP_BT_CONN_MAX_CONN_NUM                        2

#define APP_BT_CONN_AWS_SYNC_EDR_EVENT                  0
#define APP_BT_CONN_AWS_SYNC_CONN_NUM                   1

#define APP_BT_CONN_COD_SUPPORT_LEA_FLAG                (0x4000)

typedef struct {
    uint8_t                                             type;
    bool                                                edr_connected;
    uint8_t                                             edr_addr[BT_BD_ADDR_LEN];
    uint8_t                                             edr_num;
    uint8_t                                             lea_num;
    uint8_t                                             ull2_num;
} PACKED app_bt_conn_aws_data_t;

typedef enum {
    APP_BT_CONN_EVENT_EDR_CONNECTED,
    APP_BT_CONN_EVENT_EDR_DISCONNECTED,
    APP_BT_CONN_EVENT_LEA_CONNECTED,
    APP_BT_CONN_EVENT_LEA_DISCONNECTED,
    APP_BT_CONN_EVENT_ULL2_CONNECTED,
    APP_BT_CONN_EVENT_ULL2_DISCONNECTED,
} app_bt_conn_mgr_event_t;

typedef struct {
    uint8_t                                             edr_num;
    uint8_t                                             lea_num;
    uint8_t                                             ull2_num;
#ifdef MTK_AWS_MCE_ENABLE
    uint8_t                                             peer_edr_num;
    uint8_t                                             peer_lea_num;
    uint8_t                                             peer_ull2_num;
#endif
} app_bt_conn_mgr_context_t;

static app_bt_conn_mgr_context_t                        app_bt_conn_ctx = {0};

#ifdef APP_CONN_MGR_RECONNECT_CONTROL

#define APP_CONN_RECONNECT_TIMER                        (10 * 1000)
#define APP_CONN_PARTNER_ACTIVE_RECONN_LEA_TIMER        (1 * 1000)

#define APP_CONN_IS_EMPTY_ADDR(X, EMPTY)                (memcmp((X), (EMPTY), BT_BD_ADDR_LEN) == 0)

#define APP_CONN_RECONNECT_EDR_PROFILE_FLAG_DEFAULT     0
#define APP_CONN_RECONNECT_EDR_PROFILE_FLAG_HFP_ONLY    1

typedef struct {
    uint8_t                                             link_type;
    uint8_t                                             addr_type;
    uint8_t                                             addr[BT_BD_ADDR_LEN];
    uint32_t                                            edr_profile_flag;
} PACKED app_bt_conn_reconnect_item_t;

typedef struct {
    uint8_t                                             edr_num;
    uint8_t                                             le_num;
    app_bt_conn_reconnect_item_t                        item[APP_BT_CONN_MAX_CONN_NUM];
} PACKED app_bt_conn_reconnect_info_t;

static app_bt_conn_reconnect_info_t                     app_bt_conn_reconnect_info = {0};
static bool                                             app_bt_conn_saved_flag = FALSE;
static bool                                             app_bt_conn_default_connect_classic_flag = FALSE;
static bool                                             app_bt_conn_reconnect_flag = FALSE;
static uint8_t                                          app_bt_conn_classic_off_device_num = 0;     // Only for reboot BT Classic

static void app_bt_conn_mgr_reconnect_complete(bool complete);

#endif



/**================================================================================*/
/**                                 Internal Function                              */
/**================================================================================*/
#if !defined(AIR_BT_TAKEOVER_ENABLE) || defined(MTK_BT_SPEAKER_DISABLE_BROADCAST_EDR)
static void app_bt_conn_mgr_cancel_connect(void)
{
    bt_bd_addr_t bd_addr[2];
    uint32_t connecting_number = 2;

    connecting_number = bt_cm_get_connecting_devices(~BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS),
                                                     bd_addr, connecting_number);
    bt_cm_connect_t connect_param = {{0}, ~(BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS))};
    for (int i = 0; i < connecting_number; i++) {
        memcpy(connect_param.address, bd_addr[i], sizeof(bt_bd_addr_t));
        bt_status_t bt_status = bt_cm_disconnect(&connect_param);
        uint8_t *addr = (uint8_t *)bd_addr[i];
        APPS_LOG_MSGID_I(LOG_TAG" cancel_connect, addr=%02X:%02X:%02X:%02X:%02X:%02X bt_status=0x%08X",
                         7, addr[5], addr[4], addr[3], addr[2], addr[1], addr[0], bt_status);
    }
}

static void app_bt_conn_mgr_enable_page_scan(bool enable)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    if (role == BT_AWS_MCE_ROLE_AGENT || role == BT_AWS_MCE_ROLE_NONE) {
        bt_cm_write_scan_mode(BT_CM_COMMON_TYPE_UNKNOW,
                              (enable ? BT_CM_COMMON_TYPE_ENABLE : BT_CM_COMMON_TYPE_DISABLE));
        APPS_LOG_MSGID_I(LOG_TAG" page_scan, enable=%d", 1, enable);

        if (!enable) {
            app_bt_conn_mgr_cancel_connect();
        }
    } else {
        APPS_LOG_MSGID_I(LOG_TAG" page_scan, Partner not need to enable=%d", 1, enable);
    }
}

static void app_bt_conn_mgr_disallow_edr(void)
{
    app_bt_conn_mgr_enable_page_scan(FALSE);
    bool exit_discoverable = app_bt_state_service_set_bt_visible(FALSE, FALSE, 0);
#ifdef AIR_BT_FAST_PAIR_ENABLE
    app_fast_pair_enable_advertising(FALSE);
#endif
    APPS_LOG_MSGID_I(LOG_TAG" disallow_edr, exit discoverable/fast_pair_adv=%d",
                     1, exit_discoverable);
}
#endif

#if !defined(AIR_BT_TAKEOVER_ENABLE) || defined(APP_CONN_MGR_RECONNECT_CONTROL)
static void app_bt_conn_mgr_connect_edr(const uint8_t *addr, uint32_t edr_profile_flag)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    uint32_t default_edr_profile = (bt_customer_config_app_get_cm_config()->power_on_reconnect_profile
                                    & (~(BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS))));

    bt_cm_connect_t connect_param = {{0}, 0};
    memcpy(connect_param.address, addr, sizeof(bt_bd_addr_t));
    connect_param.profile = default_edr_profile;
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
    if (edr_profile_flag == APP_CONN_RECONNECT_EDR_PROFILE_FLAG_HFP_ONLY) {
        connect_param.profile = (BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_HFP));
    }
#endif
    bt_status_t bt_status = bt_cm_connect(&connect_param);
    APPS_LOG_MSGID_I(LOG_TAG" connect_edr, [%02X] addr=%02X:%02X:%02X:%02X:%02X:XX profile_flag=%d bt_status=0x%08X",
                     8, role, addr[5], addr[4], addr[3], addr[2], addr[1], edr_profile_flag, bt_status);
}
#endif

static uint8_t app_bt_conn_mgr_get_conn_num(void)
{
    return (app_bt_conn_ctx.edr_num + app_bt_conn_ctx.lea_num + app_bt_conn_ctx.ull2_num);
}

static bool app_bt_conn_mgr_is_support_emp(void)
{
    bool support_emp = FALSE;
#ifdef AIR_MULTI_POINT_ENABLE
    support_emp = app_bt_emp_is_enable();
#endif
    return support_emp;
}

static void app_bt_conn_mgr_default_connect_classic(void)
{
    uint32_t pair_num = bt_device_manager_get_paired_number();
    if (pair_num == 0) {
        return;
    }

#ifdef APP_CONN_MGR_RECONNECT_ONLY_ONE
    bt_cm_power_on_reconnect(1);
#else
    // Try to reconnect EDR via BT CM API (old Pure EDR reconnect)
    bool support_emp = app_bt_conn_mgr_is_support_emp();
    bt_cm_power_on_reconnect((support_emp ? 2 : 1));
#endif
    APPS_LOG_MSGID_I(LOG_TAG" default_connect_classic", 0);
}

#ifdef MTK_AWS_MCE_ENABLE
static bool app_bt_conn_mgr_sync_aws_data(uint8_t type, bool edr_connected, const uint8_t *addr)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    bt_aws_mce_srv_link_type_t aws_link_type = bt_aws_mce_srv_get_link_type();
    bt_status_t bt_status = BT_STATUS_FAIL;
    app_bt_conn_aws_data_t aws_data = {0};
    aws_data.type = type;

#ifdef AIR_SPEAKER_ENABLE
    bt_aws_mce_srv_mode_t aws_mode = bt_aws_mce_srv_get_mode();
    if (aws_mode != BT_AWS_MCE_SRV_MODE_DOUBLE) {
        APPS_LOG_MSGID_E(LOG_TAG" sync_aws_data, [%02X] invalid mode", 2, role, aws_mode);
        return FALSE;
    }
#endif

    if (aws_link_type == BT_AWS_MCE_SRV_LINK_NONE) {
        APPS_LOG_MSGID_E(LOG_TAG" sync_aws_data, [%02X] error type=%d edr_connected=%d",
                         3, role, type, edr_connected);
        return FALSE;
    }

    if (role == BT_AWS_MCE_ROLE_AGENT && type == APP_BT_CONN_AWS_SYNC_EDR_EVENT) {
        aws_data.edr_connected = edr_connected;
        memcpy(aws_data.edr_addr, addr, BT_BD_ADDR_LEN);
        bt_status = apps_aws_sync_event_send_extra(EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                                                   APP_CONN_MGR_EVENT_SYNC_APP_CONN_EVENT,
                                                   &aws_data, sizeof(aws_data));
        APPS_LOG_MSGID_I(LOG_TAG" sync_aws_data, [%02X] edr_connected=%d bt_status=0x%08X",
                         3, role, edr_connected, bt_status);
    } else if (type == APP_BT_CONN_AWS_SYNC_CONN_NUM) {
        aws_data.edr_num = app_bt_conn_ctx.edr_num;
        aws_data.lea_num = app_bt_conn_ctx.lea_num;
        aws_data.ull2_num = app_bt_conn_ctx.ull2_num;
        bt_status = apps_aws_sync_event_send_extra(EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                                                   APP_CONN_MGR_EVENT_SYNC_APP_CONN_EVENT,
                                                   &aws_data, sizeof(aws_data));
        APPS_LOG_MSGID_I(LOG_TAG" sync_aws_data, [%02X] edr_num=%d lea_num=%d ull2_num=%d bt_status=0x%08X",
                         5, role, aws_data.edr_num, aws_data.lea_num, aws_data.ull2_num, bt_status);
    } else {
        APPS_LOG_MSGID_I(LOG_TAG" sync_aws_data, error role=%02X or type=%d", 2, role, type);
    }

    return (bt_status == BT_STATUS_SUCCESS);
}

#endif

static void app_bt_conn_mgr_clear_context(void)
{
    //APPS_LOG_MSGID_I(LOG_TAG" clear_context", 0);
    memset(&app_bt_conn_ctx, 0, sizeof(app_bt_conn_ctx));
}

static void app_bt_conn_mgr_check_conn(bool edr_changed, bool lea_changed, bool ull2_changed)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    uint8_t edr_num = app_bt_conn_ctx.edr_num;
    uint8_t lea_num = app_bt_conn_ctx.lea_num;
    uint8_t ull2_num = app_bt_conn_ctx.ull2_num;
    uint8_t conn_num = edr_num + lea_num + ull2_num;
    APPS_LOG_MSGID_I(LOG_TAG" check_conn, [%02X] conn_num=%d edr_changed=%d lea_changed=%d ull2_changed=%d",
                     5, role, conn_num, edr_changed, lea_changed, ull2_changed);

#if defined(AIR_MULTI_POINT_ENABLE) && (defined(AIR_LE_AUDIO_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)) && defined(AIR_APP_A2DP_LBB_VENDOR_CODEC_LIMIT)
    // For Vendor Codec (Vendor Code ON)
    if (bt_sink_srv_a2dp_get_vendor_codec_config()) {
        if (edr_num == 1 && (lea_num == 1 || ull2_num == 1)) {
            APPS_LOG_MSGID_I(LOG_TAG" check_conn, [LEA][vendor_codec] LEA_EDR, disconnect LEA", 0);
            app_lea_service_disconnect(FALSE, APP_LE_AUDIO_DISCONNECT_MODE_ALL, NULL,
                                       BT_HCI_STATUS_REMOTE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES);
        } else if (edr_changed && edr_num > 0) {
            APPS_LOG_MSGID_I(LOG_TAG" check_conn, [LEA][vendor_codec] EDR Connected, stop ADV and disconnect LEA", 0);
            app_lea_service_stop_advertising(FALSE);
            app_lea_service_disconnect(FALSE, APP_LE_AUDIO_DISCONNECT_MODE_ALL, NULL,
                                       BT_HCI_STATUS_REMOTE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES);
        } else if (edr_changed && edr_num == 0) {
            APPS_LOG_MSGID_I(LOG_TAG" check_conn, [LEA][vendor_codec] EDR Disconnected, start LEA ADV", 0);
            app_lea_service_start_advertising(APP_LEA_ADV_MODE_TARGET_ALL, FALSE, 0);
        }
    }
#endif

#ifdef APP_CONN_MGR_RECONNECT_CONTROL
    if (app_bt_conn_reconnect_flag) {
        APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] check_conn, reconnect ongoing", 0);
        if (app_bt_conn_reconnect_info.edr_num == edr_num
            && app_bt_conn_reconnect_info.le_num == lea_num) {
            app_bt_conn_mgr_reconnect_complete(TRUE);
        }
        return;
    }
#endif
}

static void app_bt_conn_mgr_handle_event(app_bt_conn_mgr_event_t event, const uint8_t *addr)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();

    bool edr_changed = FALSE;
    bool lea_changed = FALSE;
    bool ull2_changed = FALSE;
    uint8_t old_edr_num = app_bt_conn_ctx.edr_num;
    uint8_t old_lea_num = app_bt_conn_ctx.lea_num;
    uint8_t old_ull2_num = app_bt_conn_ctx.ull2_num;

    if (event == APP_BT_CONN_EVENT_EDR_CONNECTED) {
        app_bt_conn_ctx.edr_num++;
        edr_changed = TRUE;
    } else if (event == APP_BT_CONN_EVENT_EDR_DISCONNECTED) {
        if (app_bt_conn_ctx.edr_num > 0) {
            app_bt_conn_ctx.edr_num--;
            edr_changed = TRUE;
        }
    } else if (event == APP_BT_CONN_EVENT_LEA_CONNECTED) {
        app_bt_conn_ctx.lea_num++;
        lea_changed = TRUE;
    } else if (event == APP_BT_CONN_EVENT_LEA_DISCONNECTED) {
        if (app_bt_conn_ctx.lea_num > 0) {
            app_bt_conn_ctx.lea_num--;
            lea_changed = TRUE;
        }
    }  else if (event == APP_BT_CONN_EVENT_ULL2_CONNECTED) {
        app_bt_conn_ctx.ull2_num++;
        ull2_changed = TRUE;
    } else if (event == APP_BT_CONN_EVENT_ULL2_DISCONNECTED) {
        if (app_bt_conn_ctx.ull2_num > 0) {
            app_bt_conn_ctx.ull2_num--;
            ull2_changed = TRUE;
        }
    }

    APPS_LOG_MSGID_W(LOG_TAG" handle_event, [%02X] edr_num=%d->%d lea_num=%d->%d ull2_num=%d->%d",
                     7, role, old_edr_num, app_bt_conn_ctx.edr_num, old_lea_num, app_bt_conn_ctx.lea_num,
                     old_ull2_num, app_bt_conn_ctx.ull2_num);

#ifdef MTK_AWS_MCE_ENABLE
    if (event == APP_BT_CONN_EVENT_LEA_CONNECTED || event == APP_BT_CONN_EVENT_LEA_DISCONNECTED
        || event == APP_BT_CONN_EVENT_ULL2_CONNECTED || event == APP_BT_CONN_EVENT_ULL2_DISCONNECTED) {
#ifdef AIR_LE_AUDIO_BOTH_SYNC_INFO
        app_lea_sync_info_send();
#endif
        app_bt_conn_mgr_sync_aws_data(APP_BT_CONN_AWS_SYNC_CONN_NUM, FALSE, NULL);
    }
#endif

    app_bt_conn_mgr_check_conn(edr_changed, lea_changed, ull2_changed);
}



/**================================================================================*/
/**                                 Reconnect Control                              */
/**================================================================================*/
#ifdef APP_CONN_MGR_RECONNECT_CONTROL

static uint8_t app_bt_conn_mgr_get_bt_cm_num(uint8_t support_max_edr_num)
{
    uint8_t bt_cm_num = 0;
#ifdef MTK_AWS_MCE_ENABLE
    bt_cm_num += 1;
#endif

    const bt_cm_config_t *bt_cm_config = bt_customer_config_get_cm_config();
    if (support_max_edr_num > 0 && bt_cm_config->connection_takeover) {
        bt_cm_num += 1;
    }
    if (support_max_edr_num > 0) {
        bt_cm_num += support_max_edr_num;
    }

    APPS_LOG_MSGID_I(LOG_TAG" get_bt_cm_num, support_max_edr_num=%d->%d",
                     2, support_max_edr_num, bt_cm_num);
    return bt_cm_num;
}

static void app_bt_conn_mgr_reconnect_lea(uint8_t le_num)
{
    if (le_num == 0 || le_num > APP_BT_CONN_MAX_CONN_NUM) {
        APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] reconnect_lea, error lea_num=%d", 1, le_num);
        return;
    }

#if defined(AIR_LE_AUDIO_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
    uint8_t add_le_num = 0;
    for (int i = 0; i < APP_BT_CONN_MAX_CONN_NUM; i++) {
        if (app_bt_conn_reconnect_info.item[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_LE) {
            if (add_le_num == 0) {
                app_lea_adv_mgr_update_target_addr(APP_LEA_TARGET_SET_UNIQUE_ADDR,
                                                   app_bt_conn_reconnect_info.item[i].addr_type,
                                                   app_bt_conn_reconnect_info.item[i].addr);
            } else {
                app_lea_adv_mgr_update_target_addr(APP_LEA_TARGET_ADD_ADDR,
                                                   app_bt_conn_reconnect_info.item[i].addr_type,
                                                   app_bt_conn_reconnect_info.item[i].addr);
            }
            add_le_num++;
            if (add_le_num == le_num) {
                break;
            }
        }
    }

    if (add_le_num > 0) {
        app_lea_service_start_advertising(APP_LEA_ADV_MODE_TARGET, FALSE, APP_CONN_RECONNECT_TIMER);
    }
#endif
}

static void app_bt_conn_mgr_check_reconnect_lea(uint8_t lea_num)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    if (lea_num == 0) {
        APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] check_reconnect_lea, [%02X] NO LE Addr", 1, role);
        return;
    }

#if defined(AIR_LE_AUDIO_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
    if (role == BT_AWS_MCE_ROLE_AGENT || role == BT_AWS_MCE_ROLE_NONE) {
        app_bt_conn_mgr_reconnect_lea(lea_num);
    } else if (role == BT_AWS_MCE_ROLE_PARTNER) {
        ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_CONN_MGR, APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA);
        ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                            APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA, (void *)(uint32_t)lea_num,
                            0, NULL, APP_CONN_PARTNER_ACTIVE_RECONN_LEA_TIMER);
    }
#endif
}

static void app_bt_conn_mgr_reconnect_complete(bool complete)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    bool visible = app_bt_service_is_visible();

    // Clear flag, stop timer
    app_bt_conn_reconnect_flag = FALSE;
    ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_CONN_MGR, APP_CONN_MGR_EVENT_RECONNECT_TIME_OUT);
    memset(&app_bt_conn_reconnect_info, 0, sizeof(app_bt_conn_reconnect_info_t));
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] reconnect_complete, [%02X] complete=%d visible=%d",
                     3, role, complete, visible);

#if defined(AIR_LE_AUDIO_ENABLE) || defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
    ui_shell_remove_event(EVENT_GROUP_UI_SHELL_LE_AUDIO, EVENT_ID_LE_AUDIO_ADV_TIMER);
    if (visible) {
        app_lea_service_start_advertising(APP_LEA_ADV_MODE_GENERAL, FALSE, APP_LE_AUDIO_ADV_TIME);
    } else {
        app_lea_service_start_advertising(APP_LEA_ADV_MODE_TARGET_ALL, FALSE, 0);
    }
#endif
}

void app_bt_conn_manager_save(void)
{
    if (app_bt_conn_saved_flag) {
        APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] save, already saved", 0);
        return;
    }

    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    const bt_device_manager_link_record_t *link_info = bt_device_manager_link_record_get_connected_link();
    uint8_t connected_num = link_info->connected_num;
    memset(&app_bt_conn_reconnect_info, 0, sizeof(app_bt_conn_reconnect_info_t));
    uint8_t edr_num = 0;
    uint8_t le_num = 0;

    for (int i = 0; i < connected_num; i++) {
#ifdef APP_CONN_MGR_RECONNECT_ONLY_ONE
        if (i >= 1) {
            APPS_LOG_MSGID_W(LOG_TAG"[Reconnect] save, [%02X] only Reconnect ONE num=%d", 2, role, connected_num);
            break;
        }
#else
        if (i >= APP_BT_CONN_MAX_CONN_NUM) {
            APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] save, [%02X] link_connected_num=%d", 2, role, connected_num);
            break;
        }
#endif

        if (link_info->connected_device[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_EDR) {
            edr_num++;
            app_bt_conn_reconnect_info.item[i].edr_profile_flag = 0;

#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
            if (app_bt_conn_ctx.ull2_num > 0 && !app_ull_idle_activity_allow_a2dp_connect()) {
                app_bt_conn_reconnect_info.item[i].edr_profile_flag = APP_CONN_RECONNECT_EDR_PROFILE_FLAG_HFP_ONLY;
                APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] save, [%02X] ULL2 - EDR HFP only", 1, role);
            }
#endif
        } else if (link_info->connected_device[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_LE) {
            le_num++;
            app_bt_conn_reconnect_info.item[i].edr_profile_flag = 0;
        }

        app_bt_conn_reconnect_info.item[i].link_type = link_info->connected_device[i].link_type;
        app_bt_conn_reconnect_info.item[i].addr_type = link_info->connected_device[i].remote_bd_type;
        memcpy(app_bt_conn_reconnect_info.item[i].addr, link_info->connected_device[i].remote_addr, BT_BD_ADDR_LEN);
    }

    uint8_t *addr1 = app_bt_conn_reconnect_info.item[0].addr;
    uint8_t *addr2 = app_bt_conn_reconnect_info.item[1].addr;
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] save, [%02X] connected_num=%d edr_num=%d lea_num=%d",
                     4, role, connected_num, edr_num, le_num);
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] save, link1=%d-%d-%02X:%02X:%02X:%02X:%02X:%02X",
                     8, app_bt_conn_reconnect_info.item[0].link_type,
                     app_bt_conn_reconnect_info.item[0].addr_type,
                     addr1[5], addr1[4], addr1[3], addr1[2], addr1[1], addr1[0]);
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] save, link2=%d-%d-%02X:%02X:%02X:%02X:%02X:%02X",
                     8, app_bt_conn_reconnect_info.item[1].link_type,
                     app_bt_conn_reconnect_info.item[1].addr_type,
                     addr2[5], addr2[4], addr2[3], addr2[2], addr2[1], addr2[0]);

#ifdef APP_CONN_MGR_RECONNECT_ONLY_ONE
    configASSERT(edr_num + le_num <= 1);
#else
    configASSERT(edr_num + le_num <= APP_BT_CONN_MAX_CONN_NUM);
#endif
    app_bt_conn_reconnect_info.edr_num = edr_num;
    app_bt_conn_reconnect_info.le_num = le_num;

    nvkey_status_t status = nvkey_write_data(NVID_APP_BT_RECONNECT_INFO,
                                             (const uint8_t *)&app_bt_conn_reconnect_info,
                                             sizeof(app_bt_conn_reconnect_info_t));
    if (status != NVKEY_STATUS_OK) {
        APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] save, error nvkey_status=%d", 1, status);
    }

    app_bt_conn_saved_flag = TRUE;
}

void app_bt_conn_manager_restore(void)
{
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    uint32_t size = sizeof(app_bt_conn_reconnect_info_t);
    memset(&app_bt_conn_reconnect_info, 0, size);
    nvkey_status_t status = nvkey_read_data(NVID_APP_BT_RECONNECT_INFO,
                                            (uint8_t *)&app_bt_conn_reconnect_info, &size);
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] restore, read status=%d size=%d", 2, status, size);
    if (status == NVKEY_STATUS_ITEM_NOT_FOUND) {
        size = sizeof(app_bt_conn_reconnect_info_t);
        status = nvkey_write_data(NVID_APP_BT_RECONNECT_INFO, (const uint8_t *)&app_bt_conn_reconnect_info, size);
        APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] restore, write status=%d", 1, status);
        app_bt_conn_reconnect_flag = FALSE;
    } else if (status != NVKEY_STATUS_OK) {
        APPS_LOG_MSGID_E(LOG_TAG"[Reconnect] restore, error status=%d", 1, status);
        return;
    }

    bool support_emp = app_bt_conn_mgr_is_support_emp();
    uint8_t edr_num = app_bt_conn_reconnect_info.edr_num;
    uint8_t le_num = app_bt_conn_reconnect_info.le_num;
    uint8_t *addr1 = app_bt_conn_reconnect_info.item[0].addr;
    uint8_t *addr2 = app_bt_conn_reconnect_info.item[1].addr;
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] restore, [%02X] edr_num=%d le_num=%d support_emp=%d",
                     4, role, edr_num, le_num, support_emp);
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] restore, link1=%d-%d-%02X:%02X:%02X:%02X:%02X:%02X",
                     8, app_bt_conn_reconnect_info.item[0].link_type,
                     app_bt_conn_reconnect_info.item[0].addr_type,
                     addr1[5], addr1[4], addr1[3], addr1[2], addr1[1], addr1[0]);
    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] restore, link2=%d-%d-%02X:%02X:%02X:%02X:%02X:%02X",
                     8, app_bt_conn_reconnect_info.item[1].link_type,
                     app_bt_conn_reconnect_info.item[1].addr_type,
                     addr2[5], addr2[4], addr2[3], addr2[2], addr2[1], addr2[0]);

    // Set BT CM max num
    uint8_t bt_cm_num = app_bt_conn_mgr_get_bt_cm_num((support_emp ? 2 : 1));
    bt_bd_addr_t keep_addr_list[1] = {{0}};
    bt_cm_set_max_connection_number(bt_cm_num, keep_addr_list, 0, FALSE);

    ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_CONN_MGR, APP_CONN_MGR_EVENT_RECONNECT_TIME_OUT);
    ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_CONN_MGR, APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA);

    if (le_num == 0 && edr_num == 0) {
        app_bt_conn_mgr_reconnect_complete(TRUE);

        app_bt_conn_mgr_default_connect_classic();
        app_bt_conn_default_connect_classic_flag = TRUE;
    } else if (le_num == 1) {
        app_bt_conn_reconnect_flag = TRUE;
        ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                            APP_CONN_MGR_EVENT_RECONNECT_TIME_OUT, NULL, 0, NULL, APP_CONN_RECONNECT_TIMER);

        if (edr_num == 1) {
            // EDR - Reconnect one
            for (int i = 0; i < APP_BT_CONN_MAX_CONN_NUM; i++) {
                if (app_bt_conn_reconnect_info.item[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_EDR) {
                    app_bt_conn_mgr_connect_edr(app_bt_conn_reconnect_info.item[i].addr,
                                                app_bt_conn_reconnect_info.item[i].edr_profile_flag);
                    break;
                }
            }
        }
        // LEA - check reconnect_lea
        app_bt_conn_mgr_check_reconnect_lea(1);
    } else if (le_num == 2) {
        app_bt_conn_reconnect_flag = TRUE;
        ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                            APP_CONN_MGR_EVENT_RECONNECT_TIME_OUT, NULL, 0, NULL, APP_CONN_RECONNECT_TIMER);

        // LEA - check reconnect_lea
        app_bt_conn_mgr_check_reconnect_lea(2);
    } else if (edr_num == 1 || edr_num == 2) {
        app_bt_conn_reconnect_flag = TRUE;
        ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                            APP_CONN_MGR_EVENT_RECONNECT_TIME_OUT, NULL, 0, NULL, APP_CONN_RECONNECT_TIMER);

        // EDR - Reconnect one/two
        for (int i = 0; i < edr_num; i++) {
            if (app_bt_conn_reconnect_info.item[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_EDR) {
                app_bt_conn_mgr_connect_edr(app_bt_conn_reconnect_info.item[i].addr,
                                            app_bt_conn_reconnect_info.item[i].edr_profile_flag);
            }
        }
    } else {
        configASSERT(0);
    }
}

void app_bt_conn_manager_update_connecting_num(void)
{
    uint32_t connecting_num = bt_cm_get_connecting_devices(~BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS), NULL, 0);
    const bt_device_manager_link_record_t *link_info = bt_device_manager_link_record_get_connected_link();
    uint8_t connected_num = link_info->connected_num;

    app_bt_conn_classic_off_device_num = connecting_num;
    for (int i = 0; i < connected_num; i++) {
        if (link_info->connected_device[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_EDR) {
            app_bt_conn_classic_off_device_num++;
        }
    }

    APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] CLASSIC_BT_OFF, connected_num=%d connecting_num=%d classic=%d",
                     3, connected_num, connecting_num, app_bt_conn_classic_off_device_num);
#ifdef APP_CONN_MGR_RECONNECT_ONLY_ONE
    if (app_bt_conn_classic_off_device_num > 1) {
        app_bt_conn_classic_off_device_num = 1;
    }
#else
    if (app_bt_conn_classic_off_device_num > APP_BT_CONN_MAX_CONN_NUM) {
        app_bt_conn_classic_off_device_num = APP_BT_CONN_MAX_CONN_NUM;
    }
#endif
}

bool app_bt_conn_mgr_is_reconnecting(void)
{
    return app_bt_conn_reconnect_flag;
}

void app_bt_conn_mgr_lea_restart_reconnect_adv(void)
{
    APPS_LOG_MSGID_W(LOG_TAG" lea_restart_reconnect_adv, flag=%d lea_num=%d",
                     2, app_bt_conn_reconnect_flag, app_bt_conn_reconnect_info.le_num);
    if (app_bt_conn_reconnect_flag && app_bt_conn_reconnect_info.le_num > 0) {
        ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_CONN_MGR, APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA);
        ui_shell_send_event(FALSE, EVENT_PRIORITY_HIGH, EVENT_GROUP_UI_SHELL_APP_CONN_MGR,
                            APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA, (void *)(uint32_t)app_bt_conn_reconnect_info.le_num,
                            0, NULL, 0);
    }
}

#endif



/**================================================================================*/
/**                             UI_Shell Event Function                            */
/**================================================================================*/
static bool app_bt_conn_mgr_activity_proc_ui_shell_group(uint32_t event_id, void *extra_data, size_t data_len)
{
    switch (event_id) {
        case EVENT_ID_SHELL_SYSTEM_ON_CREATE: {
            APPS_LOG_MSGID_I(LOG_TAG" CREATE", 0);
        }
        break;
    }
    return TRUE;
}

static bool app_bt_conn_mgr_activity_bt_cm_event_group(uint32_t event_id, void *extra_data, size_t data_len)
{
    switch (event_id) {
        case BT_CM_EVENT_REMOTE_INFO_UPDATE: {
            bt_cm_remote_info_update_ind_t *remote_update = (bt_cm_remote_info_update_ind_t *)extra_data;
            if (remote_update != NULL) {
                bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();

                uint8_t *addr = (uint8_t *)remote_update->address;
                bt_bd_addr_t *local_addr = bt_device_manager_get_local_address();
                bool phone_related = (memcmp(remote_update->address, local_addr, sizeof(bt_bd_addr_t)) != 0);
                APPS_LOG_MSGID_I(LOG_TAG" BT_CM event, [%02X] phone_conn=%d addr=%08X%04X acl=%d->%d srv=0x%04X->0x%04X",
                                 8, role, phone_related, *((uint32_t *)(addr + 2)), *((uint16_t *)addr),
                                 remote_update->pre_acl_state, remote_update->acl_state,
                                 remote_update->pre_connected_service, remote_update->connected_service);

#ifdef MTK_AWS_MCE_ENABLE
                bool aws_conntected = (!(BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS) & remote_update->pre_connected_service)
                                       && (BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS) & remote_update->connected_service));
                bool aws_disconntected = ((BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS) & remote_update->pre_connected_service)
                                          && !(BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS) & remote_update->connected_service));
#endif

                if (role == BT_AWS_MCE_ROLE_AGENT || role == BT_AWS_MCE_ROLE_NONE) {
                    if (remote_update->pre_acl_state == BT_CM_ACL_LINK_CONNECTING
                        && remote_update->acl_state == BT_CM_ACL_LINK_DISCONNECTED) {
                        APPS_LOG_MSGID_I(LOG_TAG" BT_CM event, ignore EDR(ACL) Connect fail", 0);
                        break;
                    }

                    if (remote_update->pre_acl_state < BT_CM_ACL_LINK_CONNECTED
                        && remote_update->acl_state >= BT_CM_ACL_LINK_CONNECTED
                        && phone_related) {
                        bool support_lea = bt_iot_device_white_list_check_iot_case((bt_bd_addr_t *)addr,
                                                                                   BT_IOT_IDENTIFY_LEA_SUPPORT_DEVICE);
                        uint32_t cod = bt_device_manager_remote_find_cod(addr);
                        APPS_LOG_MSGID_I(LOG_TAG" BT_CM event, phone EDR(ACL) Connected cod=0x%08X support_lea=%d",
                                         2, cod, support_lea);
#ifdef AIR_LE_AUDIO_DUALMODE_ENABLE
                        if (((cod & APP_BT_CONN_COD_SUPPORT_LEA_FLAG) > 0) || support_lea) {
                            if (app_lea_feature_mode == APP_LEA_FEATURE_MODE_DUAL_MODE) {
                                bool add_ret = app_lea_conn_mgr_add_bond_info(BT_ADDR_PUBLIC, addr, APP_LEA_CONN_TYPE_LE_AUDIO);
                                // Note: Need to start ADV with TARGET_ALL mode for "not exit discovery mode"
                                if (add_ret) {
                                    app_lea_service_start_advertising(APP_LEA_ADV_MODE_TARGET_ALL, FALSE, 0);
                                }
                            }
                        } else {
                            app_lea_conn_mgr_remove_bond_info(BT_ADDR_PUBLIC, addr);
                        }
#endif
                        app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_EDR_CONNECTED, addr);
#ifdef MTK_AWS_MCE_ENABLE
                        app_bt_conn_mgr_sync_aws_data(APP_BT_CONN_AWS_SYNC_EDR_EVENT, TRUE, addr);
#endif
                    } else if (remote_update->pre_acl_state != BT_CM_ACL_LINK_DISCONNECTED
                               && remote_update->acl_state == BT_CM_ACL_LINK_DISCONNECTED
                               && phone_related) {
                        APPS_LOG_MSGID_I(LOG_TAG" BT_CM event, phone EDR(ACL) Disconnected", 0);
                        app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_EDR_DISCONNECTED, addr);
#ifdef MTK_AWS_MCE_ENABLE
                        app_bt_conn_mgr_sync_aws_data(APP_BT_CONN_AWS_SYNC_EDR_EVENT, FALSE, addr);
#endif
                    }
                }

#ifdef MTK_AWS_MCE_ENABLE
                if (aws_conntected) {
                    APPS_LOG_MSGID_I(LOG_TAG" BT_CM event, [%02X] AWS Connected -> sync_conn_num", 1, role);
                    app_bt_conn_mgr_sync_aws_data(APP_BT_CONN_AWS_SYNC_CONN_NUM, FALSE, NULL);
#ifdef APP_CONN_MGR_RECONNECT_CONTROL
                    ui_shell_remove_event(EVENT_GROUP_UI_SHELL_APP_CONN_MGR, APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA);
#endif
                } else if (aws_disconntected) {
                    APPS_LOG_MSGID_I(LOG_TAG" BT_CM event, [%02X] AWS Disconnected -> clear peer / partner edr_num", 1, role);
                    if (role == BT_AWS_MCE_ROLE_PARTNER) {
                        app_bt_conn_ctx.edr_num = 0;
                    }
                    app_bt_conn_ctx.peer_edr_num = 0;
                    app_bt_conn_ctx.peer_lea_num = 0;
                    app_bt_conn_ctx.peer_ull2_num = 0;
                }
#endif
            }
            break;
        }
        default:
            break;
    }
    return FALSE;
}

static bool app_bt_conn_mgr_activity_bt_dm_event_group(uint32_t event_id, void *extra_data, size_t data_len)
{
    bt_device_manager_power_event_t event = 0;
    bt_device_manager_power_status_t status = 0;
    bt_event_get_bt_dm_event_and_status(event_id, &event, &status);
    switch (event) {
        case BT_DEVICE_MANAGER_POWER_EVT_ACTIVE_COMPLETE: {
            if (BT_DEVICE_MANAGER_POWER_STATUS_SUCCESS == status) {
                APPS_LOG_MSGID_I(LOG_TAG" BT DM event, POWER ON", 0);
                app_bt_conn_mgr_clear_context();
#ifdef APP_CONN_MGR_RECONNECT_CONTROL
                app_bt_conn_classic_off_device_num = 0;
                app_bt_conn_manager_restore();
#endif
            }
            break;
        }

        case BT_DEVICE_MANAGER_POWER_EVT_STANDBY_COMPLETE: {
            if (BT_DEVICE_MANAGER_POWER_RESET_TYPE_NORMAL == status) {
                APPS_LOG_MSGID_I(LOG_TAG" BT DM event, POWER OFF", 0);
                app_bt_conn_mgr_clear_context();
#ifdef APP_CONN_MGR_RECONNECT_CONTROL
                app_bt_conn_classic_off_device_num = 0;
                app_bt_conn_default_connect_classic_flag = FALSE;
#endif
            }
            break;
        }

#ifdef APP_CONN_MGR_RECONNECT_CONTROL
        case BT_DEVICE_MANAGER_POWER_EVT_CLASSIC_STANDBY_COMPLETE: {
            if (BT_DEVICE_MANAGER_POWER_RESET_TYPE_NORMAL == status) {
                app_bt_conn_default_connect_classic_flag = FALSE;
            }
            break;
        }

        case BT_DEVICE_MANAGER_POWER_EVT_CLASSIC_ACTIVE_COMPLETE: {
            if (BT_DEVICE_MANAGER_POWER_STATUS_SUCCESS == status) {
                bt_device_manager_power_state_t power_state = bt_device_manager_power_get_power_state(BT_DEVICE_TYPE_CLASSIC);
                uint32_t pair_num = bt_device_manager_get_paired_number();
                APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] BT DM event, CLASSIC POWER ON power_state=%d classic_off_num=%d pair_num=%d edr=%d le=%d",
                                 5, power_state, app_bt_conn_classic_off_device_num, pair_num,
                                 app_bt_conn_reconnect_info.edr_num, app_bt_conn_reconnect_info.le_num);
                if (app_bt_conn_classic_off_device_num > 0) {
                    if (power_state == BT_DEVICE_MANAGER_POWER_STATE_ACTIVE) {
                        bt_cm_power_on_reconnect(app_bt_conn_classic_off_device_num);
                        app_bt_conn_classic_off_device_num = 0;
                    }
                } else if (app_bt_conn_reconnect_info.edr_num == 0 && app_bt_conn_reconnect_info.le_num == 0) {
                    if (app_bt_conn_default_connect_classic_flag) {
                        app_bt_conn_default_connect_classic_flag = FALSE;
                        APPS_LOG_MSGID_W(LOG_TAG"[Reconnect] BT DM event, CLASSIC POWER ON already reconnect", 0);
                        break;
                    }

                    if (power_state == BT_DEVICE_MANAGER_POWER_STATE_ACTIVE) {
                        APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] BT DM event, CLASSIC POWER ON still reconnect", 0);
                        app_bt_conn_mgr_default_connect_classic();
                    }
                }
                app_bt_conn_saved_flag = FALSE;
            }
            break;
        }
#endif
    }
    return FALSE;
}

static bool app_bt_conn_mgr_activity_bt_sink_event_group(uint32_t event_id, void *extra_data, size_t data_len)
{
    switch (event_id) {
#ifdef AIR_LE_AUDIO_ENABLE
        case LE_SINK_SRV_EVENT_REMOTE_INFO_UPDATE: {
            bt_le_sink_srv_event_remote_info_update_t *ind = (bt_le_sink_srv_event_remote_info_update_t *)extra_data;
            if (ind == NULL) {
                break;
            }

            //bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
            uint8_t type = (uint8_t)ind->address.type;
            uint8_t *addr = (uint8_t *)ind->address.addr;
            if (ind->pre_state != ind->state) {
                APPS_LOG_MSGID_I(LOG_TAG" BT_SINK event, LEA_Link=%d->%d addr=%02X:%02X:%02X:%02X:%02X:XX addr_type=%d",
                                 8, ind->pre_state, ind->state,
                                 addr[5], addr[4], addr[3], addr[2], addr[1], type);
            }
            if (ind->pre_state == BT_BLE_LINK_DISCONNECTED
                && ind->state == BT_BLE_LINK_CONNECTED) {
                // BT_GAP_LE_CONNECT_IND -> Bonded -> bt_le_sink_srv_event_remote_info_update_t
                app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_LEA_CONNECTED, addr);
            } else if (ind->pre_state == BT_BLE_LINK_CONNECTED
                       && ind->state == BT_BLE_LINK_DISCONNECTED) {
                // bt_le_sink_srv_event_remote_info_update_t -> BT_GAP_LE_DISCONNECT_IND
                app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_LEA_DISCONNECTED, addr);
            }
            break;
        }
#endif
        default:
            break;
    }
    return FALSE;
}

static bool app_bt_conn_mgr_activity_ble_ull_event_group(uint32_t event_id, void *extra_data, size_t data_len)
{
    switch (event_id) {
#ifdef AIR_BLE_ULTRA_LOW_LATENCY_ENABLE
        case BT_ULL_EVENT_LE_CONNECTED: {
            bt_ull_le_connected_info_t *con_info = (bt_ull_le_connected_info_t*)extra_data;
            if (con_info->status != BT_STATUS_SUCCESS) {
                break;
            }
            APPS_LOG_MSGID_I(LOG_TAG" BLE_ULL event, connected", 0);
            app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_ULL2_CONNECTED, NULL);
            break;
        }
        case BT_ULL_EVENT_LE_DISCONNECTED: {
            APPS_LOG_MSGID_I(LOG_TAG" BLE_ULL event, disconnected", 0);
            app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_ULL2_DISCONNECTED, NULL);
            break;
        }
#endif
        default:
            break;
    }
    return FALSE;
}

#ifdef MTK_AWS_MCE_ENABLE
static bool app_bt_conn_mgr_activity_proc_aws_data(void *extra_data, size_t data_len)
{
    bool ret = FALSE;

    bt_aws_mce_report_info_t *aws_data_ind = (bt_aws_mce_report_info_t *)extra_data;
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();

    if (aws_data_ind->module_id == BT_AWS_MCE_REPORT_MODULE_APP_ACTION) {
        uint32_t event_group;
        uint32_t event_id;
        void *p_extra_data = NULL;
        uint32_t extra_data_len = 0;

        apps_aws_sync_event_decode_extra(aws_data_ind, &event_group, &event_id, &p_extra_data, &extra_data_len);
        if (event_group == EVENT_GROUP_UI_SHELL_APP_CONN_MGR
            && event_id == APP_CONN_MGR_EVENT_SYNC_APP_CONN_EVENT) {
            app_bt_conn_aws_data_t aws_data = {0};
            memcpy(&aws_data, (uint8_t *)p_extra_data, sizeof(app_bt_conn_aws_data_t));

            APPS_LOG_MSGID_I(LOG_TAG" AWS_DATA, [%02X] edr_num=%d lea_num=%d ull2_num=%d",
                             4, role, app_bt_conn_ctx.edr_num, app_bt_conn_ctx.lea_num, app_bt_conn_ctx.ull2_num);
            if (role == BT_AWS_MCE_ROLE_PARTNER && aws_data.type == APP_BT_CONN_AWS_SYNC_EDR_EVENT) {
                APPS_LOG_MSGID_I(LOG_TAG" AWS_DATA, [%02X] Agent edr_connected=%d", 2, role, aws_data.edr_connected);
                if (aws_data.edr_connected) {
                    app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_EDR_CONNECTED, aws_data.edr_addr);
                } else {
                    app_bt_conn_mgr_handle_event(APP_BT_CONN_EVENT_EDR_DISCONNECTED, aws_data.edr_addr);
                }
            } else if (aws_data.type == APP_BT_CONN_AWS_SYNC_CONN_NUM) {
                APPS_LOG_MSGID_I(LOG_TAG" AWS_DATA, [%02X] Peer edr_num=%d lea_num=%d ull2_num=%d",
                                 4, role, aws_data.edr_num, aws_data.lea_num, aws_data.ull2_num);
                app_bt_conn_ctx.peer_edr_num = aws_data.edr_num;
                app_bt_conn_ctx.peer_lea_num = aws_data.lea_num;
                app_bt_conn_ctx.peer_ull2_num = aws_data.ull2_num;
                if (role == BT_AWS_MCE_ROLE_PARTNER) {
                    bool is_changed = (app_bt_conn_ctx.edr_num != app_bt_conn_ctx.peer_edr_num);
                    app_bt_conn_ctx.edr_num = app_bt_conn_ctx.peer_edr_num;
                    APPS_LOG_MSGID_I(LOG_TAG" AWS_DATA, [20] Partner is_changed=%d edr_num=%d",
                                     2, is_changed, app_bt_conn_ctx.edr_num);
                    if (is_changed) {
                        app_bt_conn_mgr_check_conn(TRUE, FALSE, FALSE);
                    }
                }
            }
            ret = TRUE;
        }
    }
    return ret;
}
#endif



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
uint8_t app_bt_conn_manager_get_conn_info(uint8_t *edr_num, uint8_t *lea_num, uint8_t *ull2_num)
{
    if (edr_num != NULL) {
        *edr_num = app_bt_conn_ctx.edr_num;
    }
    if (lea_num != NULL) {
        *lea_num = app_bt_conn_ctx.lea_num;
    }
    if (ull2_num != NULL) {
        *ull2_num = app_bt_conn_ctx.ull2_num;
    }
    return app_bt_conn_mgr_get_conn_num();
}

bool app_bt_conn_manager_allow_le_adv(void)
{
    bool ret = FALSE;
    bool support_emp = app_bt_conn_mgr_is_support_emp();
    uint8_t conn_num = app_bt_conn_mgr_get_conn_num();

#ifdef AIR_BT_TAKEOVER_ENABLE
    // Always allow LE ADV for LEA or ULL2
    ret = TRUE;
#else
    if (support_emp) {
        if (conn_num < APP_BT_CONN_MAX_CONN_NUM) {
            ret = TRUE;
        }
    } else if (conn_num == 0) {
        ret = TRUE;
    }
#endif

#if defined(AIR_MULTI_POINT_ENABLE) && defined(AIR_APP_A2DP_LBB_VENDOR_CODEC_LIMIT)
    if (bt_sink_srv_a2dp_get_vendor_codec_config() && app_bt_conn_ctx.edr_num > 0) {
        APPS_LOG_MSGID_E(LOG_TAG"[vendor_codec] allow_le_audio, EMP OFF & EDR", 0);
        ret = FALSE;
    }
#endif

    APPS_LOG_MSGID_I(LOG_TAG" allow_le_audio, ret=%d conn_num=%d support_emp=%d",
                     3, ret, conn_num, support_emp);
    return ret;
}

bool app_bt_conn_manager_check_exist_link(bool check_edr, uint8_t *addr)
{
    bool ret = FALSE;
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    const bt_device_manager_link_record_t *link_info = bt_device_manager_link_record_get_connected_link();
    uint8_t connected_num = link_info->connected_num;

    for (int i = 0; i < connected_num; i++) {
        const uint8_t *conn_addr = link_info->connected_device[i].remote_addr;
        if (check_edr && link_info->connected_device[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_EDR
            && memcmp(conn_addr, addr, BT_BD_ADDR_LEN) == 0) {
            ret = TRUE;
            break;
        } else if (!check_edr && link_info->connected_device[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_LE
                   && memcmp(conn_addr, addr, BT_BD_ADDR_LEN) == 0) {
            ret = TRUE;
            break;
        }
    }

    APPS_LOG_MSGID_I(LOG_TAG" check_exist_link, [%02X] check_edr=%d addr=%08X%04X connected_num=%d ret=%d",
                     6, role, check_edr, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), connected_num, ret);
    return ret;
}

void app_bt_conn_mgr_reconnect_edr(void)
{
    app_bt_conn_mgr_default_connect_classic();
}

bt_status_t app_bt_conn_mgr_disconnect_edr(uint8_t *addr)
{
    bt_cm_connect_t disc_param = {{0}, 0};
    if (addr == NULL) {
        bt_bd_addr_t disc_addr = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        memcpy(disc_param.address, &disc_addr, sizeof(bt_bd_addr_t));
    } else {
        memcpy(disc_param.address, addr, sizeof(bt_bd_addr_t));
    }
    disc_param.profile = BT_CM_PROFILE_SERVICE_MASK_ALL;
    bt_status_t bt_status = bt_cm_disconnect(&disc_param);
    return bt_status;
}

void app_bt_conn_mgr_enable_edr(bool enable)
{
#ifdef AIR_SPEAKER_ENABLE
    if (enable) {
        app_bt_conn_mgr_enable_page_scan(TRUE);
    } else {
        app_bt_conn_mgr_disallow_edr();
    }
#endif
}

void app_bt_conn_mgr_enable_edr_profile(bool enable)
{
    // Disconnect EDR profile except SPP_AIR/A2DP/AVRCP/AWS, disable HFP SDP
    bt_aws_mce_role_t role = bt_connection_manager_device_local_info_get_aws_role();
    const bt_device_manager_link_record_t *link_record = bt_device_manager_link_record_get_connected_link();
    uint8_t conn_num = link_record->connected_num;
    bt_device_manager_link_record_item_t *link_list = (bt_device_manager_link_record_item_t *)&link_record->connected_device[0];
    uint32_t edr_profile = bt_customer_config_app_get_cm_config()->power_on_reconnect_profile;
    uint32_t other_profiles = edr_profile & ~((BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_A2DP_SINK)
                                               | BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AVRCP)
                                               | BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AIR)
                                               | BT_CM_PROFILE_SERVICE_MASK(BT_CM_PROFILE_SERVICE_AWS)));

    bt_hfp_enable_service_record(enable);
    bt_hsp_enable_service_record(enable);
    if (role == BT_AWS_MCE_ROLE_AGENT && conn_num > 0) {
        for (int i = 0; i < conn_num; i++) {
            if (link_list[i].link_type == BT_DEVICE_MANAGER_LINK_TYPE_EDR) {
                uint8_t *addr = (uint8_t *)link_list[i].remote_addr;
                bt_cm_profile_service_state_t a2dp = bt_cm_get_profile_service_state(addr, BT_CM_PROFILE_SERVICE_A2DP_SINK);
                bt_cm_profile_service_state_t hfp = bt_cm_get_profile_service_state(addr, BT_CM_PROFILE_SERVICE_HFP);
                APPS_LOG_MSGID_I(LOG_TAG" enable_edr_profile, [%02X] addr=%08X%04X enable=%d a2dp=%d hfp=%d",
                                 6, role, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), enable, a2dp, hfp);

                if (enable && a2dp && !hfp) {
                    bt_cm_connect_t conn_param = {{0}, other_profiles};
                    memcpy(conn_param.address, addr, sizeof(bt_bd_addr_t));
                    bt_status_t bt_status = bt_cm_connect(&conn_param);
                    APPS_LOG_MSGID_I(LOG_TAG" enable_edr_profile, connect addr=%08X%04X other_profiles=0x%08X bt_status=0x%08X",
                                     4, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), other_profiles, bt_status);
                } else if (!enable && hfp) {
                    bt_cm_connect_t disc_param = {{0}, other_profiles};
                    memcpy(disc_param.address, addr, sizeof(bt_bd_addr_t));
                    bt_status_t bt_status = bt_cm_disconnect(&disc_param);
                    APPS_LOG_MSGID_I(LOG_TAG" enable_edr_profile, disconnect addr=%08X%04X other_profiles=0x%08X bt_status=0x%08X",
                                     4, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), other_profiles, bt_status);
                }
            }
        }
    }
}

bool app_bt_conn_manager_activity_proc(struct _ui_shell_activity *self,
                                       uint32_t event_group,
                                       uint32_t event_id,
                                       void *extra_data,
                                       size_t data_len)
{
    bool ret = FALSE;
    switch (event_group) {
        case EVENT_GROUP_UI_SHELL_SYSTEM:
            ret = app_bt_conn_mgr_activity_proc_ui_shell_group(event_id, extra_data, data_len);
            break;
        case EVENT_GROUP_UI_SHELL_BT_CONN_MANAGER:
            ret = app_bt_conn_mgr_activity_bt_cm_event_group(event_id, extra_data, data_len);
            break;
        case EVENT_GROUP_UI_SHELL_BT_DEVICE_MANAGER:
            ret = app_bt_conn_mgr_activity_bt_dm_event_group(event_id, extra_data, data_len);
            break;
        case EVENT_GROUP_UI_SHELL_BT_SINK:
            ret = app_bt_conn_mgr_activity_bt_sink_event_group(event_id, extra_data, data_len);
            break;
        case EVENT_GROUP_BT_ULTRA_LOW_LATENCY: {
            ret = app_bt_conn_mgr_activity_ble_ull_event_group(event_id, extra_data, data_len);
            break;
        }
#ifdef MTK_AWS_MCE_ENABLE
        case EVENT_GROUP_UI_SHELL_AWS_DATA:
            ret = app_bt_conn_mgr_activity_proc_aws_data(extra_data, data_len);
            break;
#endif
        case EVENT_GROUP_UI_SHELL_APP_CONN_MGR: {
#ifdef APP_CONN_MGR_RECONNECT_CONTROL
            if (event_id == APP_CONN_MGR_EVENT_RECONNECT_TIME_OUT) {
                APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] RECONNECT_TIME_OUT event", 0);
                app_bt_conn_mgr_reconnect_complete(FALSE);
            } else if (event_id == APP_CONN_MGR_EVENT_PARTNER_RECONNECT_LEA) {
                APPS_LOG_MSGID_I(LOG_TAG"[Reconnect] PARTNER_RECONNECT_LEA event", 0);
                app_bt_conn_mgr_reconnect_lea((uint8_t)(uint32_t)extra_data);
            }
#endif
            break;
        }
    }
    return ret;
}
