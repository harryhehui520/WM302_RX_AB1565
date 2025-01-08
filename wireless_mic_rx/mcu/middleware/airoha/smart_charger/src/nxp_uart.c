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

#include "FreeRTOS.h"
#include "timers.h"
#include "mux.h"
#include "smartcharger.h"
#include "hal_gpio.h"
#include "hal_uart_internal.h"
#include "hal_eint.h"
#include "hal_gpio.h"
#include "hal_log.h"
#include "chargersmartcase.h"
#include "battery_management.h"
#include "hal.h"
#include "hal_dvfs_internal.h"
#include "hal_sleep_manager_platform.h"
#include "battery_management_core.h"
#include "battery_management.h"
#include "memory_attribute.h"
#include "bt_sink_srv_ami.h"
#include "serial_port_assignment.h"
#include "serial_port.h"
#include "race_xport.h"
#include "nvkey.h"
#include "nvkey_id_list.h"
#include "hal_resource_assignment.h"
#include "hal_pmu.h"

#if defined(AIR_BLE_ULTRA_LOW_LATENCY_ENABLE)
#include "app_ull_dongle_le.h"
#include "bt_ull_le_utility.h"
#endif

#if defined(AIR_BTA_IC_PREMIUM_G3) || defined(AIR_BTA_IC_STEREO_HIGH_G3)
#if defined(AIR_BTA_PMIC_HP)
#include "hal_pmu_internal_hp.h"
#include "hal_pmu_charger_hp.h"
#elif defined(AIR_BTA_PMIC_LP)
#include "hal_pmu_internal_lp.h"
#include "hal_pmu_charger_lp.h"
#endif
#endif

#if defined(AIR_BTA_IC_PREMIUM_G2)
#if defined(AIR_BTA_PMIC_G2_HP)
#elif defined(AIR_BTA_PMIC_G2_LP)
#include "hal_pmu_charger_2565.h"
#include "hal_pmu_internal_2565.h"
#endif
#endif
#include "smchg_1wire_config.h"
#include "smchg_1wire.h"
#include "ept_gpio_var.h"


#include "race_cmd.h"
#include "timers.h"
void fr800x_return_to_usb(uint32_t user_data_len, void *user_data);


#if defined(AIR_1WIRE_ENABLE)

/* create mux debug module */
log_create_module(NXP_UART, PRINT_LEVEL_INFO);

#if defined(AIR_BTA_IC_PREMIUM_G3) || defined(AIR_BTA_IC_STEREO_HIGH_G3)
#if defined(AIR_BTA_PMIC_HP)
#define HP_1WIRE_G3
#elif defined(AIR_BTA_PMIC_LP)
#define LP_1WIRE_G3
#endif
#elif defined(AIR_BTA_IC_PREMIUM_G2)
#if defined(AIR_BTA_PMIC_G2_HP)
#define HP_1WIRE_G2
#elif defined(AIR_BTA_PMIC_G2_LP)
#define LP_1WIRE_G2
#endif
#else
#endif

#define RACE_CH 0
#define RACE_TYPE 1
#define LENGTH_L 2
#define LENGTH_H 3
#define PROTOCOL_ID_L 4
#define PROTOCOL_ID_H 5
#define CMD_ID 6
#define EARBUD_ID 7
#define DATA 8
#define BAT_LV 8
#define BAUDRATE 8
#define KEY_ID 8

#define CASE_LID_OPEN 0x2
#define CASE_LID_CLOSE_DONE 0x3
#define CASE_CHARGER_OFF 0x4
#define CASE_CHARGER_KEY 0x5
#define CASE_BATTER_LEVEL 0x6
#define CASE_LID_CLOSE 0x8
#define CASE_LOG_ENABLE 0xE
#define CASE_RACE_ENABLE 0xF

#define SMCHG_MUX_RX_DATA_SIZE 32
#ifdef ARC_1WIRE_ENABLE
#else /* !ARC_1WIRE_ENABLE */
#define SMCHG_MUX_TX_DATA_SIZE 32
#endif /* ARC_1WIRE_ENABLE */

#define SMCHG_MUX_TX_BUFF_SIZE 1024
#define SMCHG_MUX_RX_BUFF_SIZE 2048
#define SMCHG_MUX_RX_HANDLE_TIMER_MS (1)
#define SMCHG_MUX_TX_QUERY_MAX_TIME (1500)

#define SMCHG_MUX_PARSE_ERROR_FETCH_RACE_CH (0x00000001)
#define SMCHG_MUX_PARSE_ERROR_FETCH_CH_TYPE (0x00000002)
#define SMCHG_MUX_PARSE_ERROR_CH_TYPE (0x00000004)
#define SMCHG_MUX_PARSE_ERROR_FETCH_LENGTH (0x00000008)
#define SMCHG_MUX_PARSE_ERROR_FETCH_RACE_ID (0x00000010)
#define SMCHG_MUX_PARSE_ERROR_RACE_CH (0x00000020)
#define SMCHG_MUX_PARSE_ERROR_NO_RACE_HANDLE (0x00000040)
#define SMCHG_MUX_PARSE_ERROR_NO_SMCHG_HANDLE (0x00000080)
#define SMCHG_MUX_PARSE_ERROR_NO_ATCI_HANDLE (0x00000100)
#define SMCHG_MUX_PARSE_ERROR_UNKNOWN_1WIRE_STATUS (0x00000200)
#define SMCHG_MUX_PARSE_ERROR_COM_MODE_STATUS_NOT_MATCH (0x00000400)
#define SMCHG_MUX_PARSE_ERROR_NO_HCI_HANDLE (0x00000800)

#define SMCHG_RX_PKT_MAX_SIZE (5)
#define SMCHG_OUT_OF_CASE_VOL_THRESHOLD_MV (1300)

#define SMCHG_TMR_START_STATUS_OUT_OF_CASE_TMR_MASK (0x00000001) /* pSmartChargerOutTimer */
#define SMCHG_TMR_START_STATUS_RX_TMR_MASK (0x00000002)          /* gNxpUart.pNxpUartRxTimer */
#define SMCHG_TMR_START_STATUS_CHG_IN_TMR_MASK (0x00000004)      /* gNxpUart.pNxpUartChgInTmr  */
#define SMCHG_TMR_START_STATUS_CHG_OUT_TMR_MASK (0x00000008)     /* gNxpUart.pNxpUartChgOutTmr */

#ifdef ARC_1WIRE_ENABLE
const uint8_t smchg_app_table[] = {
    0,
    0,
    SMCHG_LID_OPEN,
    SMCHG_LID_CLOSE_DONE,
    SMCHG_CHG_OFF,
    SMCHG_CHG_KEY,
    0,
    0,
    SMCHG_LID_CLOSE};

static uint8_t raceEvt[] = {
    0x05, // race header
    0x5B, // race type
    0x05, // lengthL
    0x00, // lengthH
    0x00, // cmd type
    0x20, // cmd tpye
    0x00, // event
    0x00, // R or L
    0x00, // parameter
};
#else  /* !ARC_1WIRE_ENABLE */
static const uint8_t smchg_app_table[] = {
    /* 0x00 */ 0, //NXP_GET_SYSTEM_INFO
    /* 0x01 */ 0, //NXP_GET_TX1_DEVICE_PARAM
    /* 0x02 */ 0, //NXP_GET_TX2_DEVICE_PARAM
    /* 0x03 */ 0, //NXP_GET_RX_DEVICE_PARAM
    /* 0x04 */ 0, //NXP_GET_DEVICE_INFO
    /* 0x05 */ 0,
    /* 0x06 */ NXP_SET_TX1_DEVICE_PARAM,
    /* 0x07 */ NXP_SET_TX2_DEVICE_PARAM,
    /* 0x08 */ NXP_SET_RX_DEVICE_PARAM,
    /* 0x09 */ NXP_SET_SYSTEM_INFO,
};

static uint8_t raceEvt[SMCHG_MUX_TX_DATA_SIZE] = {
    0x05, // channel, race fixed to 0x05
    0x5B, // type
    0x05, // length L
    0x00, // length H
    0x00, // protocol L
    0x30, // protocol H
    0x00, // status
    0x00, // cmd
    0x00, // data0
    0x00, // data1
    0x00, // data2
    0x00, // data3
    0x00, // data4
    0x00, // data5
    0x00, // data6
    0x00, //...
};
#endif /* ARC_1WIRE_ENABLE */

typedef struct
{
    mux_buffer_t *mux_buffer;
    uint32_t offset;
    uint32_t idx;
    uint32_t counter;
    uint32_t left_data_len;
    uint32_t total_length;
} smchg_mux_buffer_t;

typedef enum
{
    SMCHG_1WIRE_STATE_INIT,
    SMCHG_1WIRE_STATE_COM_IDLE,
    SMCHG_1WIRE_STATE_COM_WAIT_TX_DONE,
    SMCHG_1WIRE_STATE_MAX
} smchg_1wire_state_t;

typedef enum
{
    SMCHG_1WIRE_MUX_CFG_NONE = 0x00000000,
    SMCHG_1WIRE_MUX_CFG_CHANGE_UART_PARAM = 0x00000001,
    SMCHG_1WIRE_MUX_CFG_CHANGE_UART_TX_INT = 0x00000002,
    SMCHG_1WIRE_MUX_CFG_UART_TX_ENABLE = 0x00000004,
    SMCHG_1WIRE_MUX_CFG_UART_RX_ENABLE = 0x00000008,
    SMCHG_1WIRE_MUX_CFG_UART_TX_RX_DISABLE = 0x00000010
} smchg_1wire_mux_cfg_cmd_t;

typedef struct
{
    mux_port_t port;
    smchg_1wire_mux_cfg_cmd_t cfg_cmd;
    mux_ctrl_para_t mux_ctrl_para;
} smchg_1wire_mux_ctrl_req_t;

typedef struct
{
    hal_uart_baudrate_t race_baudrate;
} smchg_1wire_race_mode_info_t;

typedef struct
{
    uint32_t rx_data_len;
    void *p_rx_data;
} smchg_rx_pkt_info_t;

typedef struct
{

    smchg_1wire_state_t state;
    mux_port_t mux_port;
    mux_handle_t mux_handle;
    uint16_t cur_cmd_id;
    void *cur_cmd;
    smchg_1wire_race_mode_info_t race_mode_info;
} smchg_handle_t;

typedef struct
{
    TimerHandle_t pNxpUartRxTimer;
    TimerHandle_t pNxpUartChgInTmr;
    TimerHandle_t pNxpUartChgOutTmr;

    uint8_t pre_cmd;
#ifdef ARC_1WIRE_ENABLE
    uint32_t pre_data;
#else  /* !ARC_1WIRE_ENABLE */
    uint8_t *pre_data;
#endif /* ARC_1WIRE_ENABLE */
    uint16_t pre_data_len;
    uint8_t last_cmd;
    uint8_t boot_Flag;
    uint8_t lock_sleep_flag;
    uint8_t race_mode_flag;
    uint32_t g_rx_data_len;
    void *g_rx_user_data;
    uint32_t g_rxcb_w_cnt;
    uint32_t g_rxcb_r_cnt;
    smchg_rx_pkt_info_t g_rx_data[SMCHG_RX_PKT_MAX_SIZE];
    uint32_t g_rx_handle_lock;
    uint32_t g_com_mode_chk_cnt;
    smchg_handle_t g_nxp_uart;
}nxpUartData;
static nxpUartData gNxpUart;
static volatile smchg_1wire_mode_t g_nxp_uart_mode;

#define SMCHG_1WIRE_UART_RX_ENABLE_CMD (SMCHG_1WIRE_MUX_CFG_CHANGE_UART_PARAM | SMCHG_1WIRE_MUX_CFG_CHANGE_UART_TX_INT | SMCHG_1WIRE_MUX_CFG_UART_RX_ENABLE)
#define SMCHG_1WIRE_UART_TX_ENABLE_CMD (SMCHG_1WIRE_MUX_CFG_CHANGE_UART_PARAM | SMCHG_1WIRE_MUX_CFG_CHANGE_UART_TX_INT | SMCHG_1WIRE_MUX_CFG_UART_TX_ENABLE)
#define SMCHG_1WIRE_UART_TRX_DISABLE_CMD (SMCHG_1WIRE_MUX_CFG_CHANGE_UART_TX_INT | SMCHG_1WIRE_MUX_CFG_UART_TX_RX_DISABLE)
static const uint32_t nxp_uart_ctrl_cmd[] = {
    SMCHG_1WIRE_MUX_CFG_NONE,         /* SMCHG_1WIRE_NORM */
    SMCHG_1WIRE_UART_TRX_DISABLE_CMD, /* SMCHG_1WIRE_OUT */
    SMCHG_1WIRE_UART_TX_ENABLE_CMD,   /* SMCHG_1WIRE_LOG */
    SMCHG_1WIRE_UART_TRX_DISABLE_CMD, /* SMCHG_1WIRE_CHG */
    SMCHG_1WIRE_UART_RX_ENABLE_CMD,   /* SMCHG_1WIRE_COM */
    SMCHG_1WIRE_UART_RX_ENABLE_CMD,   /* SMCHG_1WIRE_RACE */
    SMCHG_1WIRE_UART_RX_ENABLE_CMD,   /* SMCHG_1WIRE_ATCI */
    SMCHG_1WIRE_MUX_CFG_NONE};

static void nxp_uart_rx_handle(uint32_t user_data_len, void *user_data);
static smchg_status_t nxp_uart_tx_post_handle(uint32_t user_data_len, void *user_data);
static smchg_status_t nxp_uart_give_lock(uint32_t *p_lock);
static smchg_status_t nxp_uart_take_lock(uint32_t *p_lock);
static smchg_status_t nxp_uart_mux_control(smchg_handle_t *p_sm_handle, void *p_cfg);

/* sleep lock control */
void nxp_uart_lock_sleep(void)
{
    SMCHG_LOG_MSGID_D("nxp_uart, lock_sleep, flag[%d]", 1, gNxpUart.lock_sleep_flag);

    if (!gNxpUart.lock_sleep_flag)
    {
        hal_sleep_manager_lock_sleep(SLEEP_LOCK_CHARGER_CASE);
        gNxpUart.lock_sleep_flag = 1;
    }
}

void nxp_uart_unlock_sleep(void)
{
    SMCHG_LOG_MSGID_D("nxp_uart, unlock_sleep, flag[%d]", 1, gNxpUart.lock_sleep_flag);

    if (gNxpUart.lock_sleep_flag)
    {
        hal_sleep_manager_unlock_sleep(SLEEP_LOCK_CHARGER_CASE);
        gNxpUart.lock_sleep_flag = 0;
    }
}

smchg_1wire_mode_t nxp_uart_get_mode_status(void)
{
    return g_nxp_uart_mode;
}

smchg_status_t nxp_uart_set_mode_status(smchg_1wire_mode_t mode)
{
    if (mode >= SMCHG_1WIRE_MAX)
    {
        return SMCHG_STATUS_INVALID_PARAMETER;
    }

    g_nxp_uart_mode = mode;

    return SMCHG_STATUS_OK;
}

//static void nxp_uart_app_cmd(uint8_t cmd)
//{
//    SMCHG_LOG_MSGID_D("nxp_uart, app_cmd[%d]", 1, cmd);
//}

static serial_port_dev_t nxp_uart_port_convert_mux_to_port_service(mux_port_t port)
{
    serial_port_dev_t ser_port = SERIAL_PORT_DEV_UNDEFINED;

    switch (port)
    {
    case MUX_UART_2:
        ser_port = SERIAL_PORT_DEV_UART_2;
        break;

    default:
        SMCHG_LOG_MSGID_E("nxp_uart, port not support [%d]", 1, port);
        break;
    }
    return ser_port;
}

static smchg_status_t nxp_uart_reset_smchg_state(smchg_handle_t *p_smchg)
{
    p_smchg->state = SMCHG_1WIRE_STATE_COM_IDLE;
    p_smchg->cur_cmd_id = 0;
    p_smchg->cur_cmd = NULL;

    return SMCHG_STATUS_OK;
}

static smchg_status_t nxp_uart_take_lock(uint32_t *p_lock)
{
    uint32_t irq_status;

    if (p_lock == NULL)
    {
        return SMCHG_STATUS_INVALID_PARAMETER;
    }

    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    if (*p_lock)
    {
        hal_nvic_restore_interrupt_mask(irq_status);
        return SMCHG_STATUS_ERROR;
    }
    *p_lock = 1;
    ;
    hal_nvic_restore_interrupt_mask(irq_status);
    return SMCHG_STATUS_OK;
}

static smchg_status_t nxp_uart_give_lock(uint32_t *p_lock)
{
    uint32_t irq_status;

    if (p_lock == NULL)
    {
        return SMCHG_STATUS_INVALID_PARAMETER;
    }
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    *p_lock = 0;
    hal_nvic_restore_interrupt_mask(irq_status);
    return SMCHG_STATUS_OK;
}

int32_t nxp_uart_chg_exist(void)
{
    return battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);
}

void nxp_uart_com_mode_tx_done(void)
{
    uint32_t time_s = 0, time_e = 0, time_dur = 0;
    mux_status_t mux_status = MUX_STATUS_ERROR_BUSY;
    hal_gpt_status_t gpt_status = HAL_GPT_STATUS_ERROR;

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &time_s);

    do
    {

        mux_status = mux_control(gNxpUart.g_nxp_uart.mux_port, MUX_CMD_GET_TX_PORT_IDLE, NULL);
        // SMCHG_LOG_MSGID_W("1wire, com_mode_to_race_mode, mux_status[%d]", 1, mux_status);

        gpt_status = hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &time_e);
        if (gpt_status != HAL_GPT_STATUS_OK)
        {
            break;
        }

        gpt_status = hal_gpt_get_duration_count(time_s, time_e, &time_dur);
        if (gpt_status != HAL_GPT_STATUS_OK)
        {
            // SMCHG_LOG_MSGID_E("1wire, com_mode_tx_done, get gpt dur error, status[%d]", 1, gpt_status);
            break;
        }
    } while (mux_status != MUX_STATUS_OK);

    SMCHG_LOG_MSGID_D("nxp_uart, com_mode_tx_done, time[%dus], gpt status[%d]", 2, time_dur, gpt_status);
}

static smchg_status_t nxp_uart_mux_control(smchg_handle_t *p_sm_handle, void *p_cfg)
{
    smchg_1wire_mux_ctrl_req_t *p_ctrl_req = NULL;
    smchg_1wire_mux_cfg_cmd_t smchg_mux_cmd = SMCHG_1WIRE_MUX_CFG_NONE;
    mux_ctrl_para_t *mux_cfg = NULL;
    mux_ctrl_cmd_t mux_cmd = 0;
    uint32_t cmd_idx = 0x1;
    bool is_ctrl = TRUE;
    smchg_status_t status = SMCHG_STATUS_OK;
    mux_status_t mux_status = MUX_STATUS_OK;

    if (p_sm_handle == NULL || p_cfg == NULL)
    {
        status = SMCHG_STATUS_INVALID_PARAMETER;
        goto end;
    }
    p_ctrl_req = (smchg_1wire_mux_ctrl_req_t *)p_cfg;
    mux_cfg = &(p_ctrl_req->mux_ctrl_para);
    smchg_mux_cmd = p_ctrl_req->cfg_cmd;

    SMCHG_LOG_MSGID_I("nxp_uart, mux ctrl, mux_cmd [0x%x]", 1, smchg_mux_cmd);

    while (smchg_mux_cmd && (mux_status == MUX_STATUS_OK))
    {
        SMCHG_LOG_MSGID_D("nxp_uart, mux ctrl, mux_cmd [0x%x],cmd_idx[%d]", 2, smchg_mux_cmd, cmd_idx);
        switch (smchg_mux_cmd & cmd_idx)
        {
        case SMCHG_1WIRE_MUX_CFG_CHANGE_UART_PARAM:
            mux_cmd = MUX_CMD_CHANGE_UART_PARAM;
            break;
        case SMCHG_1WIRE_MUX_CFG_CHANGE_UART_TX_INT:
            mux_cmd = MUX_CMD_CHANGE_UART_TX_INT;
            break;
#if 0   /* HWJ: TODO: Set pin functions by smchg_1wire_gpio_cfg, assert if smchg_1wire_get_mode_status is wrong, reimplement later for power consumption. */
        case SMCHG_1WIRE_MUX_CFG_UART_TX_ENABLE:
            mux_cmd = MUX_CMD_UART_TX_ENABLE;
            break;
        case SMCHG_1WIRE_MUX_CFG_UART_RX_ENABLE:
            mux_cmd = MUX_CMD_UART_RX_ENABLE;
            break;
        case SMCHG_1WIRE_MUX_CFG_UART_TX_RX_DISABLE:
            mux_cmd = MUX_CMD_UART_TX_RX_DISABLE;
            break;
#endif
        default:
            is_ctrl = FALSE;
            break;
        }

        if (is_ctrl)
        {
            mux_status = mux_control(gNxpUart.g_nxp_uart.mux_port, mux_cmd, mux_cfg);
            if (mux_status != MUX_STATUS_OK)
            {
                status = SMCHG_STATUS_ERROR_MUX_CTRL_FAIL;
            }
            smchg_mux_cmd = smchg_mux_cmd & (~cmd_idx);
        }
        else
        {
            /* HWJ: Clear flags too if invalid. */
            smchg_mux_cmd = smchg_mux_cmd & (~cmd_idx);
        }
        cmd_idx = (cmd_idx << 1);
        is_ctrl = TRUE;
    }
end:
    SMCHG_LOG_MSGID_I("nxp_uart, mux ctrl, mux_status[%d], status[%d]", 2, mux_status, status);
    return status;
}

/*     1wire mode     */
static void nxp_uart_race_mode(hal_uart_baudrate_t baudrate)
{
    smchg_1wire_mux_ctrl_req_t smchg_mux_ctrl;
    smchg_status_t status = SMCHG_STATUS_OK;
    serial_port_dev_t ser_port = SERIAL_PORT_DEV_UNDEFINED;
    SMCHG_LOG_MSGID_D("nxp_uart, race_mode, baudrate[%d]", 1, smchg_1wire_baudrate_report(baudrate));

    if (status == SMCHG_STATUS_OK)
    {
        nxp_uart_set_mode_status(SMCHG_1WIRE_RACE);
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.baudrate = baudrate;
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.int_enable = TRUE;
        smchg_mux_ctrl.cfg_cmd = nxp_uart_ctrl_cmd[SMCHG_1WIRE_RACE];

        status = nxp_uart_mux_control(&gNxpUart.g_nxp_uart, (void *)&smchg_mux_ctrl);
        if (status == SMCHG_STATUS_OK)
        {
            gNxpUart.g_com_mode_chk_cnt = 0;
            ser_port = nxp_uart_port_convert_mux_to_port_service(gNxpUart.g_nxp_uart.mux_port);
            if (ser_port != SERIAL_PORT_DEV_UNDEFINED)
            {
#if defined(MTK_RACE_CMD_ENABLE)
                race_normal_init(ser_port, baudrate);
#endif
            }
        }
    }
    SMCHG_LOG_MSGID_I("nxp_uart, race_mode, baudrate[%d], status[%d]", 2, baudrate, status);
}

void nxp_uart_leave_race_mode(void)
{
    SMCHG_LOG_MSGID_I("nxp_uart, leave_race_mode", 0);
#if defined(MTK_RACE_CMD_ENABLE)
    race_normal_deinit();
#endif
}

static void nxp_uart_chg_mode(void)
{
    smchg_1wire_mux_ctrl_req_t smchg_mux_ctrl;
    smchg_status_t status = SMCHG_STATUS_OK;

    SMCHG_LOG_MSGID_D("nxp_uart, chg_mode", 0);
    memset(&smchg_mux_ctrl, 0x0, sizeof(smchg_mux_ctrl));
    if (nxp_uart_get_mode_status() == SMCHG_1WIRE_CHG)
    {
        status = SMCHG_STATUS_REENTER_CHG_MODE;
        goto end;
    }
    nxp_uart_set_mode_status(SMCHG_1WIRE_CHG);

    {
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.int_enable = FALSE;
        smchg_mux_ctrl.cfg_cmd = nxp_uart_ctrl_cmd[SMCHG_1WIRE_CHG];
        status = nxp_uart_mux_control(&gNxpUart.g_nxp_uart, (void *)&smchg_mux_ctrl);
        gNxpUart.g_com_mode_chk_cnt = 0;
        nxp_uart_unlock_sleep();
    }
end:
    SMCHG_LOG_MSGID_I("nxp_uart, chg_mode, status[%d]", 1, status);
}

static void nxp_uart_com_mode(void)
{
    smchg_1wire_mux_ctrl_req_t smchg_mux_ctrl;
    smchg_status_t status = SMCHG_STATUS_OK;

    SMCHG_LOG_MSGID_D("nxp_uart, com_mode, baudrate[%d]", 1, smchg_1wire_baudrate_report(smchg_cfg.com_mode_baud_rate));
    nxp_uart_set_mode_status(SMCHG_1WIRE_COM);

    if (status == SMCHG_STATUS_OK)
    {
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.baudrate = smchg_cfg.com_mode_baud_rate;
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.int_enable = TRUE;
        smchg_mux_ctrl.cfg_cmd = nxp_uart_ctrl_cmd[SMCHG_1WIRE_COM];
        status = nxp_uart_mux_control(&gNxpUart.g_nxp_uart, (void *)&smchg_mux_ctrl);
        nxp_uart_lock_sleep();
    }

    SMCHG_LOG_MSGID_I("nxp_uart, com_mode, status [%d]", 1, status);
}

static void nxp_uart_out_of_case(bool isInit)
{
    smchg_1wire_mux_ctrl_req_t smchg_mux_ctrl;
    smchg_status_t status = SMCHG_STATUS_OK;

    SMCHG_LOG_MSGID_D("nxp_uart, out_of_case", 0);
    memset(&smchg_mux_ctrl, 0x0, sizeof(smchg_mux_ctrl));

    {
        nxp_uart_set_mode_status(SMCHG_1WIRE_OUT);
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.int_enable = FALSE;
        smchg_mux_ctrl.cfg_cmd = nxp_uart_ctrl_cmd[SMCHG_1WIRE_OUT];
        status = nxp_uart_mux_control(&gNxpUart.g_nxp_uart, (void *)&smchg_mux_ctrl);
        nxp_uart_unlock_sleep();
    }
    SMCHG_LOG_MSGID_I("nxp_uart, out_of_case, status[%d]", 1, status);
}

static void nxp_uart_pwr_save_mode(void)
{
    smchg_1wire_mux_ctrl_req_t smchg_mux_ctrl;
    smchg_status_t status = SMCHG_STATUS_OK;
    SMCHG_LOG_MSGID_D("nxp_uart, pwr_save_mode", 0);

    memset(&smchg_mux_ctrl, 0x0, sizeof(smchg_mux_ctrl));

    {
        nxp_uart_set_mode_status(SMCHG_1WIRE_OUT);
        smchg_mux_ctrl.mux_ctrl_para.mux_set_config_uart_param.int_enable = FALSE;
        smchg_mux_ctrl.cfg_cmd = nxp_uart_ctrl_cmd[SMCHG_1WIRE_OUT];
        status = nxp_uart_mux_control(&gNxpUart.g_nxp_uart, (void *)&smchg_mux_ctrl);
        nxp_uart_unlock_sleep();
    }
    SMCHG_LOG_MSGID_I("nxp_uart, pwr_save_mode, status[%d]", 1, status);
}

smchg_status_t nxp_uart_enter_pwr_save_mode(void)
{
    nxp_uart_pwr_save_mode();

    return SMCHG_STATUS_OK;
}

#ifdef ARC_1WIRE_ENABLE
static void nxp_uart_send_to_app(uint8_t cmd, uint32_t data, uint16_t data_len)
#else  /* !ARC_1WIRE_ENABLE */
static void nxp_uart_send_to_app(uint8_t cmd, uint8_t *data, uint16_t data_len)
#endif /* ARC_1WIRE_ENABLE */
{
    if (gNxpUart.last_cmd == cmd)
    {
        if (cmd == SMCHG_LID_OPEN ||
            cmd == SMCHG_LID_CLOSE_DONE ||
            cmd == SMCHG_LID_CLOSE)
        {
            SMCHG_LOG_MSGID_D("nxp_uart, repeat app_cmd[%d]", 1, cmd);
            return;
        }
    }

    gNxpUart.last_cmd = cmd;

    if (cmd)
    {
        smartcharger_callback_t callback_handler = ChargerSmartCase_GetSmartCaseHandle();
        if (callback_handler)
        {
            // nxp_uart_app_cmd(cmd);
            callback_handler(cmd, TRUE, data, data_len);
            SMCHG_LOG_MSGID_D("nxp_uart, send_to_app, cmd[%d], data[%d], data_len[%d]", 3, cmd, data, data_len);
        }
        else
        {
            gNxpUart.pre_cmd = cmd;
            gNxpUart.pre_data = data;
            gNxpUart.pre_data_len = data_len;
        }
    }
}

void nxp_uart_pre_handle(void)
{
    if (gNxpUart.pre_cmd)
    {
        nxp_uart_send_to_app(gNxpUart.pre_cmd, gNxpUart.pre_data, gNxpUart.pre_data_len);
        gNxpUart.pre_cmd = 0;
        gNxpUart.pre_data = 0;
        gNxpUart.pre_data_len = 0;
    }
}

static void nxp_uart_rx_handle_timer_cb(TimerHandle_t pxExpiredTimer)
{
    uint32_t irq_status = 0;
    int32_t rx_cb_count_diff = 0;

    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    // dequeue
    gNxpUart.g_rx_data_len = gNxpUart.g_rx_data[gNxpUart.g_rxcb_r_cnt].rx_data_len;
    gNxpUart.g_rx_user_data = gNxpUart.g_rx_data[gNxpUart.g_rxcb_r_cnt].p_rx_data;
    if (gNxpUart.g_rxcb_r_cnt == (SMCHG_RX_PKT_MAX_SIZE - 1))
    {
        gNxpUart.g_rxcb_r_cnt = 0;
    }
    else
    {
        gNxpUart.g_rxcb_r_cnt++;
    }
    hal_nvic_restore_interrupt_mask(irq_status);
    // rx handle
    nxp_uart_rx_handle(gNxpUart.g_rx_data_len, gNxpUart.g_rx_user_data);

    // check if there is any unhandled rx pkt or not
    hal_nvic_save_and_set_interrupt_mask(&irq_status);

    rx_cb_count_diff = gNxpUart.g_rxcb_w_cnt - gNxpUart.g_rxcb_r_cnt;
    if (rx_cb_count_diff == 0)
    {
        gNxpUart.g_rx_data_len = 0;
        gNxpUart.g_rx_user_data = NULL;
        nxp_uart_give_lock(&gNxpUart.g_rx_handle_lock);
    }
    hal_nvic_restore_interrupt_mask(irq_status);
    if (rx_cb_count_diff)
    {
        SMCHG_LOG_MSGID_I("nxp_uart, rx_handle, gNxpUart.g_rxcb_w_cnt = %d, gNxpUart.g_rxcb_r_cnt = %d", 2, gNxpUart.g_rxcb_w_cnt, gNxpUart.g_rxcb_r_cnt);
        if (xTimerStart(gNxpUart.pNxpUartRxTimer, 0) != pdPASS)
        {
            SMCHG_LOG_MSGID_I("nxp_uart, rx timer start from isr fail", 0);
            assert(0);
        }
        else
        {
            SMCHG_LOG_MSGID_I("nxp_uart, rx timer start again", 0);
        }
    }
}

#if defined(AIR_BTA_IC_STEREO_HIGH_G3)
static void smchg_1wire_pmu_hdl_cb(TimerHandle_t pxExpiredTimer)
{
    if (pxExpiredTimer == gNxpUart.pNxpUartChgInTmr)
    {
        // SMCHG_LOG_MSGID_I("1wire, Tmr chg-in", 0);
        smchg_1wire_intr_to_chg_mode();
        if (gNxpUart.race_mode_flag)
        {
            nxp_uart_leave_race_mode();
            gNxpUart.race_mode_flag = 0;
        }
        nxp_uart_chg_mode();
        nxp_uart_send_to_app(SMCHG_CHG_IN, 0, 0);
    }
    else if (pxExpiredTimer == gNxpUart.pNxpUartChgOutTmr)
    {
        // SMCHG_LOG_MSGID_I("1wire, Tmr chg-out", 0);
        if (nxp_uart_get_mode_status() == SMCHG_1WIRE_CHG)
        { // any mode to com mode, without enter out of case directly
            smchg_1wire_intr_to_com_mode();
            nxp_uart_com_mode();
        }
    }
    else
    {
        SMCHG_LOG_MSGID_I("1wire, Tmr unknown", 0);
    }
}

static void smchg_1wire_chg_in_hdlr(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    SMCHG_LOG_MSGID_I("1wire, chg-in notification", 0);
    if (xTimerStartFromISR(gNxpUart.pNxpUartChgInTmr, &xHigherPriorityTaskWoken) != pdPASS)
    {
        SMCHG_LOG_MSGID_E("1wire, gNxpUart.pNxpUartChgInTmr start from isr fail", 0);
        assert(0);
    }
    if (xHigherPriorityTaskWoken != pdFALSE)
    {
        portYIELD_FROM_ISR(pdTRUE);
    }
}

static void smchg_1wire_chg_out_hdlr(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    SMCHG_LOG_MSGID_I("1wire, chg-out notification", 0);
    if (xTimerStartFromISR(gNxpUart.pNxpUartChgOutTmr, &xHigherPriorityTaskWoken) != pdPASS)
    {
        SMCHG_LOG_MSGID_E("1wire, gNxpUart.pNxpUartChgOutTmr start from isr fail", 0);
        assert(0);
    }
    if (xHigherPriorityTaskWoken != pdFALSE)
    {
        portYIELD_FROM_ISR(pdTRUE);
    }
}

#else

static void nxp_uart_chg_isr_cb(battery_management_event_t event, const void *data)
{
    int32_t chg_exist = nxp_uart_chg_exist();

    if (event != BATTERY_MANAGEMENT_EVENT_CHARGER_EXIST_UPDATE)
    {
        return;
    }
    SMCHG_LOG_MSGID_I("nxp_uart, chg_isr_cb, chg_exist[%d]", 1, chg_exist);

    if (chg_exist)
    {
        if (nxp_uart_get_mode_status() == SMCHG_1WIRE_CHG)
        {
            nxp_uart_com_mode();
            // if (xTimerStart(pSmartChargerOutTimer, 0) == pdFAIL) {
            //     SMCHG_LOG_MSGID_E("1wire, rx_handle, start com_mode_timer fail", 0);
            // }
        }
        //nxp_uart_send_to_app(SMCHG_CHG_IN, 0, 0);
    }
    else
    {
        if (gNxpUart.race_mode_flag)
        {
            nxp_uart_leave_race_mode();
            gNxpUart.race_mode_flag = 0;
        }
        /* HWJ: No charger mode but need this to disable UART. */
        nxp_uart_chg_mode();
    }
}

#endif

static void nxp_uart_chg_state_change_cb_register(void)
{
#if defined(AIR_BTA_IC_STEREO_HIGH_G3)
    pmu_register_callback_lp(CHG_IN_INT_FLAG, (pmu_callback_t)smchg_1wire_chg_in_hdlr, NULL, PMU_CB_1WIRE);
    pmu_register_callback_lp(CHG_OUT_INT_FLAG, (pmu_callback_t)smchg_1wire_chg_out_hdlr, NULL, PMU_CB_1WIRE);
    gNxpUart.pNxpUartChgInTmr = xTimerCreate("SmchgChgIn", pdMS_TO_TICKS(1), pdFALSE, NULL, smchg_1wire_pmu_hdl_cb);
    if (!gNxpUart.pNxpUartChgInTmr)
    {
        SMCHG_LOG_MSGID_D("1wire, gNxpUart.pNxpUartChgInTmr", 0);
        assert(0);
    }
    gNxpUart.pNxpUartChgOutTmr = xTimerCreate("SmchgChgOut", pdMS_TO_TICKS(1), pdFALSE, NULL, smchg_1wire_pmu_hdl_cb);
    if (!gNxpUart.pNxpUartChgOutTmr)
    {
        SMCHG_LOG_MSGID_D("1wire, gNxpUart.pNxpUartChgOutTmr", 0);
        assert(0);
    }
#else
    if (battery_management_register_callback(nxp_uart_chg_isr_cb) != BATTERY_MANAGEMENT_STATUS_OK)
    {
        SMCHG_LOG_MSGID_D("nxp_uart, init chg_isr_cb fail", 0);
        assert(0);
    }
#endif
}

static smchg_status_t nxp_uart_rx_timer_start(uint32_t data_len, void *user_data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    smchg_status_t status = SMCHG_STATUS_OK;
    uint32_t irq_status;

    // enqueue
    hal_nvic_save_and_set_interrupt_mask(&irq_status);
    gNxpUart.g_rx_data[gNxpUart.g_rxcb_w_cnt].rx_data_len = data_len;
    gNxpUart.g_rx_data[gNxpUart.g_rxcb_w_cnt].p_rx_data = user_data;
    if (gNxpUart.g_rxcb_w_cnt == (SMCHG_RX_PKT_MAX_SIZE - 1))
    {
        gNxpUart.g_rxcb_w_cnt = 0;
    }
    else
    {
        gNxpUart.g_rxcb_w_cnt++;
    }
    hal_nvic_restore_interrupt_mask(irq_status);

    // get rx handle lock
    status = nxp_uart_take_lock(&gNxpUart.g_rx_handle_lock);
    if (status == SMCHG_STATUS_OK)
    {

        if (xTimerStartFromISR(gNxpUart.pNxpUartRxTimer, &xHigherPriorityTaskWoken) != pdPASS)
        {
            SMCHG_LOG_MSGID_D("nxp_uart, rx timer start from isr fail", 0);
            status = SMCHG_STATUS_ERROR_TMR_OP_FAIL;
            assert(0);
        }
    }
    else if (status == SMCHG_STATUS_ERROR)
    {
        SMCHG_LOG_MSGID_D("nxp_uart, rx timer restart", 0);
        status = SMCHG_STATUS_ERROR_RX_HDL_TMR_RESTART;
    }
    if (status == SMCHG_STATUS_OK && xHigherPriorityTaskWoken != pdFALSE)
    {
        // Actual macro used here is port specific.
        portYIELD_FROM_ISR(pdTRUE);
    }

    SMCHG_LOG_MSGID_I("nxp_uart, rx timer start, status[%d]", 1, status);

    return status;
}

static smchg_status_t nxp_uart_tx_post_handle(uint32_t user_data_len, void *user_data)
{
    // mux_status_t mux_status     = MUX_STATUS_OK;
    smchg_status_t smchg_status = SMCHG_STATUS_OK;

    if (gNxpUart.g_nxp_uart.state == SMCHG_1WIRE_STATE_COM_WAIT_TX_DONE)
    {
        SMCHG_LOG_MSGID_I("nxp_uart, tx post handle, handle cmd id [%d]", 1, gNxpUart.g_nxp_uart.cur_cmd_id);

        switch (gNxpUart.g_nxp_uart.cur_cmd_id)
        {
        case CASE_RACE_ENABLE:
            if (gNxpUart.g_nxp_uart.cur_cmd != NULL)
            {
                smchg_1wire_race_mode_info_t *race_mode_cfg = (smchg_1wire_race_mode_info_t *)gNxpUart.g_nxp_uart.cur_cmd;
                if (race_mode_cfg->race_baudrate > HAL_UART_BAUDRATE_4800 && race_mode_cfg->race_baudrate < HAL_UART_BAUDRATE_3200000)
                {
                    nxp_uart_race_mode(race_mode_cfg->race_baudrate);
                    gNxpUart.race_mode_flag = 1;
                }
                else
                {
                    smchg_status = SMCHG_STATUS_TX_POST_INVALID_BAUDRATE;
                }
            }
            else
            {
                smchg_status = SMCHG_STATUS_TX_POST_INVALID_CMD_PTR;
            }
            break;
        default:
            break;
        }
        gNxpUart.g_nxp_uart.state = SMCHG_1WIRE_STATE_COM_IDLE;
        gNxpUart.g_nxp_uart.cur_cmd_id = 0;
        gNxpUart.g_nxp_uart.cur_cmd = NULL;
    }

    SMCHG_LOG_MSGID_I("nxp_uart, tx post handle, status [%d], state [%d], cmd_id [%d]", 3, smchg_status, gNxpUart.g_nxp_uart.state, gNxpUart.g_nxp_uart.cur_cmd_id);
    return smchg_status;
}

static uint8_t calculate_checksum(const uint8_t *buffer, uint32_t size)
{
    uint8_t checksum = 0;

    uint32_t i;
    for (i = 0; i < size; i++) {
        checksum += *(buffer + i);
    }
    return checksum;
}

#include "app_smcharger.h"
#include "hal_rtc.h"
#include "app_ull_dongle_idle_activity.h"

extern bool nxp_flags_power_on;
extern bool is_in_pairing;
extern bool is_in_pt_mode;

static void nxp_uart_rx_handle(uint32_t user_data_len, void *user_data)
{
    static uint8_t raceCmd[SMCHG_MUX_RX_DATA_SIZE] = {0}; /* Keep persistent for gNxpUart.pre_data used in nxp_uart_send_to_app. */
    mux_buffer_t buffer;
    buffer.buf_size = SMCHG_MUX_RX_DATA_SIZE;
    buffer.p_buf = raceCmd;
    uint32_t data_size = 0;
    uint32_t rcv_size = 0;
    mux_status_t mux_status = MUX_STATUS_ERROR;
    smchg_status_t status = SMCHG_STATUS_OK;
    uint8_t earbud_ch = 0x02; // audio_channel_t earbud_ch = ami_get_audio_channel();
    uint16_t protocol_id = 0;

    mux_status = mux_rx(gNxpUart.g_nxp_uart.mux_handle, &buffer, &data_size);

    /* Memroy check has been done in rx_protocol_callback. */
    protocol_id = (raceCmd[NXP_PKT_OFFS_PROTOCOL_ID_H] << 8) | raceCmd[NXP_PKT_OFFS_PROTOCOL_ID_L];
    rcv_size = ((raceCmd[NXP_PKT_OFFS_LENGTH_H] << 8) | raceCmd[NXP_PKT_OFFS_LENGTH_L]) + 4;

    if (rcv_size == data_size)
    {
        /* For compatible with AIROHA tools */
        if (0x2000 == protocol_id)
        {
            earbud_ch = raceCmd[EARBUD_ID]; /* HWJ: I want return true always when using tool. */

            SMCHG_LOG_MSGID_I("nxp_uart, rx_handle, race_ch[0x%X], race_type[0x%X], cmd_id[0x%X], earbud_id[%d], data[%d], earbud_ch[%d], data_size[%d], rcv_size[%d], statue[%d], mux_status[%d]", 10,
                              raceCmd[RACE_CH], raceCmd[RACE_TYPE], raceCmd[CMD_ID], raceCmd[EARBUD_ID], raceCmd[DATA], earbud_ch, data_size, rcv_size, status, mux_status);

            if ((raceCmd[RACE_CH] == 0x5) && (raceCmd[RACE_TYPE] == 0x5A) && (raceCmd[CMD_ID]))
            {
                // uint32_t data = 0;
                // uint16_t data_len = 0;

                // if (raceCmd[CMD_ID] == CASE_LID_OPEN || raceCmd[CMD_ID] == CASE_CHARGER_OFF)
                // {
                //     data = raceCmd[BAT_LV];
                //     data_len = 1;
                // }
                // else if (raceCmd[CMD_ID] == CASE_CHARGER_KEY)
                // {
                //     data = raceCmd[KEY_ID];
                //     data_len = 1;
                // }

                // if (raceCmd[CMD_ID] <= CASE_LID_CLOSE) {
                //     nxp_uart_send_to_app(smchg_app_table[raceCmd[CMD_ID]], data, data_len);
                // }

                if (raceCmd[EARBUD_ID] == earbud_ch)
                {
                    uint32_t tx_size = 0;

                    raceEvt[RACE_CH] = 0x05;
                    raceEvt[RACE_TYPE] = 0x5B;
                    raceEvt[LENGTH_L] = 0x05;
                    raceEvt[LENGTH_H] = 0x00;
                    raceEvt[PROTOCOL_ID_L] = 0x00;
                    raceEvt[PROTOCOL_ID_H] = 0x20;
                    raceEvt[CMD_ID] = raceCmd[CMD_ID];
                    raceEvt[EARBUD_ID] = earbud_ch;
                    raceEvt[BAT_LV] = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);
                    gNxpUart.g_nxp_uart.state = SMCHG_1WIRE_STATE_COM_WAIT_TX_DONE;
                    gNxpUart.g_nxp_uart.cur_cmd_id = raceCmd[CMD_ID];
                    if (raceCmd[CMD_ID] == CASE_RACE_ENABLE && gNxpUart.race_mode_flag == 0)
                    {
                        gNxpUart.g_nxp_uart.race_mode_info.race_baudrate = raceCmd[BAUDRATE];
                        gNxpUart.g_nxp_uart.cur_cmd = (void *)&(gNxpUart.g_nxp_uart.race_mode_info);
                    }
                    buffer.buf_size = 9;
                    buffer.p_buf = raceEvt;

                    {
                        mux_status = mux_tx(gNxpUart.g_nxp_uart.mux_handle, &buffer, 1, &tx_size);
                        if (mux_status != MUX_STATUS_OK)
                        {
                            SMCHG_LOG_MSGID_E("nxp_uart, rx_handle, mux tx error, status[%d]", 1, mux_status);
                            nxp_uart_reset_smchg_state(&gNxpUart.g_nxp_uart);
                        }
                    }
                    SMCHG_LOG_MSGID_I("nxp_uart, rx_handle, response, data[%d], size[%d]", 3, raceEvt[DATA], tx_size, status);
                }
            }

            return;
        }

        SMCHG_LOG_MSGID_I("nxp_uart, rx_handle, channle[0x%X], type[0x%X], length[0x%x], cmd[0x%X]", 4,
                          raceCmd[NXP_PKT_OFFS_CHANNEL], raceCmd[NXP_PKT_OFFS_TYPE], ((raceCmd[NXP_PKT_OFFS_LENGTH_H] << 8) | raceCmd[NXP_PKT_OFFS_LENGTH_L]),
                          raceCmd[NXP_PKT_OFFS_CMD]);

        uint8_t *data = raceCmd + NXP_PKT_OFFS_DATA;
        uint16_t data_len = ((raceCmd[NXP_PKT_OFFS_LENGTH_H] << 8) | raceCmd[NXP_PKT_OFFS_LENGTH_L]) - 6; /* 6: Protocol Id(2bytes) + Flags(1byte) + Cmd(1byte) + DeviceType(1byte) + CRC(1byte) */

        raceEvt[NXP_PKT_OFFS_PROTOCOL_ID_L] = 0x00;
        raceEvt[NXP_PKT_OFFS_PROTOCOL_ID_H] = 0x30;
        raceEvt[NXP_PKT_OFFS_CMD] = raceCmd[NXP_PKT_OFFS_CMD];

        switch (raceCmd[NXP_PKT_OFFS_CMD])
        {
        case NXP_GET_SYSTEM_INFO_COMMAND:
        {
            /* No app handle need! */
            //nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_GET_SYSTEM_INFO_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_LAGUAGE_OFFSET] = arc_dp_recored_update_display_record_laguage();
            {
                hal_rtc_time_t time;
                hal_rtc_get_time(&time);
                raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_YEAR_OFFSET] = time.rtc_year;         /* Years - [0,127] */
                raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_MONTH_OFFSET] = time.rtc_mon;         /* Months - [1,12]  */
                raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_DAY_OFFSET] = time.rtc_day;           /* Day of the month - [1,31]  */
                raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_HOUR_OFFSET] = time.rtc_hour;         /* Hours after midnight - [0,23]  */
                raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_MINUTE_OFFSET] = time.rtc_min;        /* Minutes after the hour - [0,59]  */
                raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_SECOND_OFFSET] = time.rtc_sec;        /* Seconds after minutes - [0,59]  */
            }
            raceEvt[NXP_GET_SYSTEM_INFO_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_GET_SYSTEM_INFO_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_GET_TX1_DEVICE_PARAM_COMMAND:
        {
            /* No app handle need! */
            //nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            static uint8_t device_status_local = 0xFF;
            static uint8_t audio_status_1_local = 0xFF;
            static uint8_t audio_status_2_local = 0xFF;

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            const bool is_rf_connected = arc_dp_recored_tx_device_is_connected(TX_DEVICE_INDEX_1);
            if (is_rf_connected)
            {
                uint8_t temp_data[9] = {0};    /* 9: TEMP_DATA_LEN */
                arc_dp_recored_update_display_record_get_tx_device_param(TX_DEVICE_INDEX_1, temp_data, 9);    /* 9: TEMP_DATA_LEN */
                {
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET] = temp_data[0];
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET] = temp_data[1];
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET] = temp_data[2];

                    if (device_status_local != temp_data[0])
                    {
                        device_status_local = temp_data[0];
                        SMCHG_LOG_MSGID_I("nxp_uart, debug, TX1 device_status 0x%X", 1, device_status_local);
                    }

                    if (audio_status_1_local != temp_data[1])
                    {
                        audio_status_1_local = temp_data[1];
                        SMCHG_LOG_MSGID_I("nxp_uart, debug, TX1 audio_status_1 0x%X", 1, audio_status_1_local);
                    }

                    if (audio_status_2_local != temp_data[2])
                    {
                        audio_status_2_local = temp_data[2];
                        SMCHG_LOG_MSGID_I("nxp_uart, debug, TX1 audio_status_2 0x%X", 1, audio_status_2_local);
                    }

                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_GAIN_OFFSET] = temp_data[3];
                    {
                        bool mute_state = GET_BIT(raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET], NXP_TX_AUDIO_STATUS_1_MUTE_BIT);

                        if (mute_state)
                        {
                            raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET] = 0;
                        }
                        else
                        {
                            raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET] = arc_dp_recored_update_display_record_get_volume(TX_DEVICE_INDEX_1);
                        }
                    }
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_RSSI_OFFSET] = arc_dp_recored_update_display_record_get_rssi(TX_DEVICE_INDEX_1);
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET] = arc_dp_recored_update_display_record_get_battery(TX_DEVICE_INDEX_1);
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_FILE_NUMBER_OFFSET] = temp_data[4];
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_1_OFFSET] = temp_data[5];
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_2_OFFSET] = temp_data[6];
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_3_OFFSET] = temp_data[7];
                    raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_4_OFFSET] = temp_data[8];
                }
            }
            else
            {
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET] = 0;
                
                if (device_status_local != 0)
                {
                    device_status_local = 0;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, TX1 device_status 0x%X", 1, device_status_local);
                }
                
                if (audio_status_1_local != 0)
                {
                    audio_status_1_local = 0;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, TX1 audio_status_1 0x%X", 1, audio_status_1_local);
                }
                
                if (audio_status_2_local != 0)
                {
                    audio_status_2_local = 0;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, TX1 audio_status_2 0x%X", 1, audio_status_2_local);
                }
                
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_GAIN_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_RSSI_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_FILE_NUMBER_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_1_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_2_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_3_OFFSET] = 0;
                raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_4_OFFSET] = 0;
            }
            raceEvt[NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_GET_TX2_DEVICE_PARAM_COMMAND:
        {
            /* No app handle need! */
            //nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            static uint8_t device_status_local = 0xFF;
            static uint8_t audio_status_1_local = 0xFF;
            static uint8_t audio_status_2_local = 0xFF;

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            const bool is_rf_connected = arc_dp_recored_tx_device_is_connected(TX_DEVICE_INDEX_2);
            if (is_rf_connected)
            {
                uint8_t temp_data[9] = {0};    /* 9: TEMP_DATA_LEN */
                arc_dp_recored_update_display_record_get_tx_device_param(TX_DEVICE_INDEX_2, temp_data, 9);    /* 9: TEMP_DATA_LEN */
                {
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET] = temp_data[0];
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET] = temp_data[1];
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET] = temp_data[2];

                    if (device_status_local != temp_data[0])
                    {
                        device_status_local = temp_data[0];
                        SMCHG_LOG_MSGID_I("nxp_uart, debug, TX2 device_status 0x%X", 1, device_status_local);
                    }

                    if (audio_status_1_local != temp_data[1])
                    {
                        audio_status_1_local = temp_data[1];
                        SMCHG_LOG_MSGID_I("nxp_uart, debug, TX2 audio_status_1 0x%X", 1, audio_status_1_local);
                    }

                    if (audio_status_2_local != temp_data[2])
                    {
                        audio_status_2_local = temp_data[2];
                        SMCHG_LOG_MSGID_I("nxp_uart, debug, TX2 audio_status_2 0x%X", 1, audio_status_2_local);
                    }

                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_GAIN_OFFSET] = temp_data[3];
                    {
                        bool mute_state = GET_BIT(raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET], NXP_TX_AUDIO_STATUS_1_MUTE_BIT);

                        if (mute_state)
                        {
                            raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET] = 0;
                        }
                        else
                        {
                            raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET] = arc_dp_recored_update_display_record_get_volume(TX_DEVICE_INDEX_2);
                        }
                    }
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_RSSI_OFFSET] = arc_dp_recored_update_display_record_get_rssi(TX_DEVICE_INDEX_2);
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET] = arc_dp_recored_update_display_record_get_battery(TX_DEVICE_INDEX_2);
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_FILE_NUMBER_OFFSET] = temp_data[4];
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_1_OFFSET] = temp_data[5];
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_2_OFFSET] = temp_data[6];
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_3_OFFSET] = temp_data[7];
                    raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_4_OFFSET] = temp_data[8];
                }
            }
            else
            {
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET] = 0;
                
                if (device_status_local != 0)
                {
                    device_status_local = 0;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, TX2 device_status 0x%X", 1, device_status_local);
                }
                
                if (audio_status_1_local != 0)
                {
                    audio_status_1_local = 0;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, TX2 audio_status_1 0x%X", 1, audio_status_1_local);
                }
                
                if (audio_status_2_local != 0)
                {
                    audio_status_2_local = 0;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, TX2 audio_status_2 0x%X", 1, audio_status_2_local);
                }
                
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_GAIN_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_RSSI_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_FILE_NUMBER_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_1_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_2_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_3_OFFSET] = 0;
                raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_4_OFFSET] = 0;
            }
            raceEvt[NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_GET_RX_DEVICE_PARAM_COMMAND:
        {
            /* No app handle need! */
            //nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            static uint8_t device_status_local = 0xFF;
            static uint8_t audio_status_local = 0xFF;

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            uint8_t device_status = 0;
            int32_t charger_exist = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);
            int32_t charger_status = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_STATE);
            const bool is_charger_exist = (charger_exist > 0) ? TRUE : FALSE;
            const bool is_charging_over = (CHARGER_STATE_EOC == charger_status) ? TRUE : FALSE;
            const bool is_usb_attached = arc_events_usb_is_attached();
            device_status = (is_charger_exist << NXP_RX_DEVICE_STATUS_HAS_CHARGER_BIT) |
                            (is_charging_over << NXP_RX_DEVICE_STATUS_IS_CHARGING_OVER_BIT) |
                            (nxp_flags_power_on << NXP_RX_DEVICE_STATUS_IS_POWER_ON_BIT) |
                            (is_in_pt_mode << NXP_RX_DEVICE_STATUS_IS_IN_PT_MODE_BIT) |
                            (is_in_pairing << NXP_RX_DEVICE_STATUS_IS_IN_PAIRING_BIT) |
                            (is_usb_attached << NXP_RX_DEVICE_STATUS_USB_ATTACHED_BIT);
            uint8_t temp_data[4] = {0};    /* 4: TEMP_DATA_LEN */
            arc_dp_recored_update_display_record_get_rx_device_param(temp_data, 4);    /* 4: TEMP_DATA_LEN */
            uint8_t audio_status = (temp_data[0] & 0x01) << NXP_RX_AUDIO_STATUS_LR_2_RL_MODE_BIT |          // 0x01: NXP_RX_AUDIO_STATUS_LR_2_RL_MODE_BIT mask
                                   (temp_data[1] & 0x03) << NXP_RX_AUDIO_STATUS_SETERO_OR_SAFETY_MODE_BIT | // 0x03: NXP_RX_AUDIO_STATUS_SETERO_OR_SAFETY_MODE_BIT mask
                                   (temp_data[2] & 0x03) << NXP_RX_AUDIO_STATUS_EQ_MODE |                   // 0x03: NXP_RX_AUDIO_STATUS_EQ_MODE mask
                                   (0) << NXP_RX_AUDIO_STATUS_IS_APP_CONNECTED |
                                   (APP_SMCHARGER_LID_CLOSE == app_smlid_is_close()) << NXP_RX_AUDIO_STATUS_CLOSE_LID_STATUS |
                                   (APP_SMCHARGER_IN == app_smcharger_is_charging()) << NXP_RX_AUDIO_STATUS_IN_CASE_STATUS;

            {
                raceEvt[NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET] = device_status;
                raceEvt[NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_OFFSET] = audio_status;

                if (device_status_local != device_status)
                {
                    device_status_local = device_status;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, RX device_status 0x%X", 1, device_status_local);
                }

                if (audio_status_local != audio_status)
                {
                    audio_status_local = audio_status;
                    SMCHG_LOG_MSGID_I("nxp_uart, debug, RX audio_status 0x%X", 1, audio_status_local);
                }

                raceEvt[NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_RX_GAIN_OFFSET] = temp_data[3];
            }
            raceEvt[NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET] = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);;
            raceEvt[NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_GET_DEVICE_INFO_COMMAND:
        {
            /* No app handle need! */
            //nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_GET_DEVICE_INFO_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            uint8_t major = 0, minor = 0, revision = 0;
            arc_dp_recored_update_display_record_get_fw_version(TX_DEVICE_INDEX_1, &major, &minor, &revision);
            {
                raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_TX1_FW_VER_L_OFFSET] = major;
                raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_TX1_FW_VER_H_OFFSET] = (minor << 4) | revision;
            }
            major = 0, minor = 0, revision = 0;
            arc_dp_recored_update_display_record_get_fw_version(TX_DEVICE_INDEX_2, &major, &minor, &revision);
            {
                raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_TX2_FW_VER_L_OFFSET] = major;
                raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_TX2_FW_VER_H_OFFSET] = (minor << 4) | revision;
            }
            major = 0, minor = 0, revision = 0;
            arc_dp_recored_update_display_record_get_rx_fw_version(&major, &minor, &revision);
            {
                raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_RX_FW_VER_L_OFFSET] = major;
                raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_RX_FW_VER_H_OFFSET] = (minor << 4) | revision;
            }
            raceEvt[NXP_GET_DEVICE_INFO_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_GET_DEVICE_INFO_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_SET_TX1_DEVICE_PARAM_COMMAND:
        {
            nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            /* Response the same data as receiving to ensure it is correct. */
            raceEvt[NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET] = raceCmd[NXP_SET_TX1_DEVICE_PARAM_COMMAND_AUDIO_STATUS_1_OFFSET];
            raceEvt[NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET] = raceCmd[NXP_SET_TX1_DEVICE_PARAM_COMMAND_AUDIO_STATUS_2_OFFSET];
            raceEvt[NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_TX_GAIN_OFFSET] = raceCmd[NXP_SET_TX1_DEVICE_PARAM_COMMAND_TX_GAIN_OFFSET];
            raceEvt[NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_SET_TX2_DEVICE_PARAM_COMMAND:
        {
            nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            /* Response the same data as receiving to ensure it is correct. */
            raceEvt[NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET] = raceCmd[NXP_SET_TX2_DEVICE_PARAM_COMMAND_AUDIO_STATUS_1_OFFSET];
            raceEvt[NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET] = raceCmd[NXP_SET_TX2_DEVICE_PARAM_COMMAND_AUDIO_STATUS_2_OFFSET];
            raceEvt[NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_TX_GAIN_OFFSET] = raceCmd[NXP_SET_TX2_DEVICE_PARAM_COMMAND_TX_GAIN_OFFSET];
            raceEvt[NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_SET_RX_DEVICE_PARAM_COMMAND:
        {
            nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            /* Response the same data as receiving to ensure it is correct. */
            raceEvt[NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_OFFSET] = raceCmd[NXP_SET_RX_DEVICE_PARAM_COMMAND_AUDIO_STATUS_OFFSET];
            raceEvt[NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_RX_GAIN_OFFSET] = raceCmd[NXP_SET_RX_DEVICE_PARAM_COMMAND_RX_GAIN_OFFSET];
            raceEvt[NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_SET_SYSTEM_INFO_COMMAND:
        {
            nxp_uart_send_to_app(smchg_app_table[raceCmd[NXP_PKT_OFFS_CMD]], data, data_len);

            /* Response data. */
            raceEvt[NXP_PKT_OFFS_LENGTH_L] = NXP_PKT_OFFS_DATA + NXP_SET_SYSTEM_INFO_COMMAND_RSP_DATA_LENGTH - 4; /* 4: channel + type + length(2byte) */
            raceEvt[NXP_PKT_OFFS_LENGTH_H] = 0x00;
            /* Response the same data as receiving to ensure it is correct. */
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_LAGUAGE_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_LAGUAGE_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_YEAR_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_TIME_YEAR_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_MONTH_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_TIME_MONTH_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_DAY_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_TIME_DAY_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_HOUR_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_TIME_HOUR_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_MINUTE_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_TIME_MINUTE_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_SECOND_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_TIME_SECOND_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_RESERVED_OFFSET] = raceCmd[NXP_SET_SYSTEM_INFO_COMMAND_RESERVED_OFFSET];
            raceEvt[NXP_SET_SYSTEM_INFO_COMMAND_RSP_CRC_OFFSET] = calculate_checksum(raceEvt+4, NXP_PKT_OFFS_DATA + NXP_SET_SYSTEM_INFO_COMMAND_RSP_DATA_LENGTH - 4 - 1);
            buffer.buf_size = NXP_PKT_OFFS_PKT_MAX_LEN;
            buffer.p_buf = raceEvt;
        }
        break;

        case NXP_FR800x_TRANS_COMMAND:
        {
            SMCHG_LOG_MSGID_I("nxp_uart, NXP_FR800x_TRANS_COMMAND", 0);
            fr800x_return_to_usb(raceCmd[NXP_PKT_OFFS_DATA], raceCmd+NXP_PKT_OFFS_DATA+1);
            //to usb data, no need return uart data
            return;
        }
        break;

        default:
            SMCHG_LOG_MSGID_I("nxp_uart, rx_handle, invalid cmd", 0);
            break;
        }

        // if (raceCmd[PKT_OFFS_DEVICE_TYPE] == earbud_ch) {
        {
            uint32_t tx_size = 0;

            // MUX TX start
            gNxpUart.g_nxp_uart.state = SMCHG_1WIRE_STATE_COM_WAIT_TX_DONE;
            gNxpUart.g_nxp_uart.cur_cmd_id = raceCmd[NXP_PKT_OFFS_CMD];
            {
                mux_status = mux_tx(gNxpUart.g_nxp_uart.mux_handle, &buffer, 1, &tx_size);
                if (mux_status != MUX_STATUS_OK)
                {
                    SMCHG_LOG_MSGID_E("nxp_uart, rx_handle, mux tx error, status[%d]", 1, mux_status);
                    nxp_uart_reset_smchg_state(&gNxpUart.g_nxp_uart);
                }
            }
            SMCHG_LOG_MSGID_I("nxp_uart, rx_handle, response, tx_size[%d], status[%d]", 2, tx_size, status);
        }
    }
}

static void nxp_uart_cb(mux_handle_t handle, mux_event_t event, uint32_t data_len, void *user_data)
{
    SMCHG_LOG_MSGID_I("nxp_uart, uart_cb, rx(tx)_done, event[%d], 1:rx, 6:tx, 8:brk_signal", 1, event);
    if (event == MUX_EVENT_READY_TO_READ)
    {
        gNxpUart.g_com_mode_chk_cnt = 0;
        nxp_uart_rx_timer_start(data_len, user_data);
    }
    else if (event == MUX_EVENT_TRANSMISSION_DONE)
    {
        gNxpUart.g_com_mode_chk_cnt = 0;
        nxp_uart_tx_post_handle(data_len, user_data);
    }
    else if (event == MUX_EVENT_BREAK_SIGNAL)
    {
    }
}

static smchg_mux_buffer_t smchg_mux_buffer;
static void nxp_uart_mux_buffer_fetch_init(mux_buffer_t buffers[], uint32_t buffers_counter)
{
    uint32_t i;

    smchg_mux_buffer.mux_buffer = buffers;
    smchg_mux_buffer.offset = 0;
    smchg_mux_buffer.idx = 0;
    smchg_mux_buffer.counter = buffers_counter;
    smchg_mux_buffer.left_data_len = 0;
    for (i = 0; i < buffers_counter; i++)
    {
        smchg_mux_buffer.left_data_len += buffers[i].buf_size;
    }
    smchg_mux_buffer.total_length = smchg_mux_buffer.left_data_len;
}

static bool nxp_uart_mux_header_fetch(uint8_t *out_buf, uint32_t out_len)
{
    uint32_t i;

    if (smchg_mux_buffer.idx >= smchg_mux_buffer.counter)
    {
        SMCHG_LOG_MSGID_E("nxp_uart, mux_header_featch counter fail, idx[%d], counter[%d]", 2,
                          smchg_mux_buffer.idx, smchg_mux_buffer.counter);
        return false;
    }

    if (smchg_mux_buffer.left_data_len < out_len)
    {
        SMCHG_LOG_MSGID_E("nxp_uart, mux_header_featch length fail, left_data_len[%d], out_len[%d]", 2,
                          smchg_mux_buffer.left_data_len, out_len);
        return false;
    }

    for (i = 0; i < out_len; i++, smchg_mux_buffer.left_data_len--, smchg_mux_buffer.offset++)
    {
        if (smchg_mux_buffer.offset >= smchg_mux_buffer.mux_buffer[smchg_mux_buffer.idx].buf_size)
        {
            smchg_mux_buffer.idx++;
            smchg_mux_buffer.offset = 0;
            if (smchg_mux_buffer.idx >= smchg_mux_buffer.counter)
            {
                SMCHG_LOG_MSGID_E("nxp_uart, mux_header_featch counter fail, idx[%d], counter[%d]", 2,
                                  smchg_mux_buffer.idx, smchg_mux_buffer.counter);
                assert(0);
            }
        }
        *(out_buf + i) = *(smchg_mux_buffer.mux_buffer[smchg_mux_buffer.idx].p_buf + smchg_mux_buffer.offset);
    }
    return true;
}

static void nxp_uart_mux_tx_protocol_cb(mux_handle_t handle, const mux_buffer_t payload[], uint32_t buffers_counter, mux_buffer_t *head, mux_buffer_t *tail, void *user_data)
{
    const char *user_name = NULL;
    uint32_t i = 0, race_id = 0, total_size = 0;

    mux_status_t status = mux_query_user_name(handle, &user_name);
    smchg_1wire_mode_t smchg_1wire_status = nxp_uart_get_mode_status();
    if ((status == MUX_STATUS_OK) && (user_name != NULL))
    {
        if (smchg_1wire_status == SMCHG_1WIRE_NORM)
        {
            if (strcmp(user_name, "ATCI") == 0)
            {
                /* [Special] Need to fill the head buffer */
                race_id = 0x0F92;
            }
            else
            {
                /* SYSLOG/RACE/other */
                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
        }
        else if (smchg_1wire_status == SMCHG_1WIRE_LOG)
        {
            if (strcmp(user_name, "SYSLOG") == 0)
            {
                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
            else
            {
                /* Ignore tx except syslog */
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
        }
        else if (smchg_1wire_status == SMCHG_1WIRE_COM)
        {
            if (strcmp(user_name, "SM_CHG") == 0)
            {
                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
            else if (strcmp(user_name, "NXP_COM") == 0)
            {
                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
            else
            {
                /* Ignore tx except CHG CMD */
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
        }
        else if (smchg_1wire_status == SMCHG_1WIRE_RACE)
        {
            if (strcmp(user_name, "RACE_CMD") == 0 || strcmp(user_name, "HCI_CMD") == 0)
            {
                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
            else if (strcmp(user_name, "ATCI") == 0)
            {
                race_id = 0x0F92;
            }
            else
            {
                /* Ignore tx except race CMD */
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
                head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
                tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

                head->p_buf = NULL;
                tail->p_buf = NULL;
                head->buf_size = 0;
                tail->buf_size = 0;
                return;
            }
        }
        else if ((smchg_1wire_status == SMCHG_1WIRE_CHG) || (smchg_1wire_status == SMCHG_1WIRE_OUT))
        {
            /* Ignore all tx */
            head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
            head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
            head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
            head->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

            tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 0] = 0x65;
            tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 1] = 0x72;
            tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 2] = 0x69;
            tail->p_buf[TX_PROTOCOL_CB_HEAD_BUFFER_MAX_LEN + 3] = 0x57;

            head->p_buf = NULL;
            tail->p_buf = NULL;
            head->buf_size = 0;
            tail->buf_size = 0;
            return;
        }
        else
        {
            /* mode error */
            head->p_buf = NULL;
            tail->p_buf = NULL;
            head->buf_size = 0;
            tail->buf_size = 0;
            return;
        }
    }
    else
    {
        head->p_buf = NULL;
        tail->p_buf = NULL;
        head->buf_size = 0;
        tail->buf_size = 0;
        return;
    }

    total_size = 0;
    for (i = 0; i < buffers_counter; i++)
    {
        total_size += payload[i].buf_size;
    }

    /* Insert the race header here */
    head->p_buf[0] = 0x05;
    head->p_buf[1] = RACE_TYPE_NOTIFICATION;
    head->p_buf[2] = (uint8_t)((total_size + 2) & 0xFF);
    head->p_buf[3] = (uint8_t)(((total_size + 2) >> 8) & 0xFF);
    head->p_buf[4] = (uint8_t)(race_id & 0xFF);
    head->p_buf[5] = (uint8_t)((race_id >> 8) & 0xFF);
    head->buf_size = 6;

    tail->p_buf = NULL;
    tail->buf_size = 0;
}

uint8_t package_uart_recv[250];
uint8_t package_uart_recv_len = 0;
RACE_ERRCODE freq_timer_start(uint32_t delay_msec);

static void nxp_uart_mux_rx_protocol_cb(mux_handle_t *handle, mux_buffer_t buffers[], uint32_t buffers_counter,
                                    uint32_t *consume_len, uint32_t *package_len, void *user_data)
{
    uint8_t race_ch = 0, race_type = 0;
    uint16_t race_length = 0, race_id = 0;
    uint32_t collected_length = 0, error_code = 0;
    mux_handle_t p_handle;

    race_length = 0;
    collected_length = 0;
    *package_len = 0;
    *consume_len = 0;

    smchg_1wire_mode_t smchg_1wire_status = nxp_uart_get_mode_status();

    nxp_uart_mux_buffer_fetch_init(buffers, buffers_counter);

    if(smchg_1wire_status == SMCHG_1WIRE_FREQ_OTA)
    {
        *handle = 0x0;
        *package_len = 0;
        *consume_len = smchg_mux_buffer.total_length;

        for (uint8_t i = 0; i < buffers_counter; i++)
        {
            memcpy(package_uart_recv+package_uart_recv_len, buffers[i].p_buf, buffers[i].buf_size);
            package_uart_recv_len += buffers[i].buf_size;
        }
        if(package_uart_recv_len > 4)
        {
            uint8_t recv_len = package_uart_recv[2];
            recv_len += 4;
            SMCHG_LOG_MSGID_D("nxp_uart, recv, %d--%d", 2, package_uart_recv_len, recv_len);
            if(package_uart_recv_len >= recv_len)
            {
                fr800x_return_to_usb(package_uart_recv[NXP_PKT_OFFS_DATA], package_uart_recv+NXP_PKT_OFFS_DATA+1);
                package_uart_recv_len = 0;
            }
        }
        return;
    }


    /* 1wire sm check */
    if ((smchg_1wire_status != SMCHG_1WIRE_NORM) && (smchg_1wire_status != SMCHG_1WIRE_COM) && (smchg_1wire_status != SMCHG_1WIRE_RACE) && (smchg_1wire_status != SMCHG_1WIRE_ATCI))
    {
        /* error */
        *handle = 0x0;
        *package_len = 0;
        *consume_len = smchg_mux_buffer.total_length;
        error_code |= SMCHG_MUX_PARSE_ERROR_UNKNOWN_1WIRE_STATUS;
        goto end;
    }

    if (nxp_uart_mux_header_fetch(&race_ch, 1) == false)
    {
        *package_len = 0;
        *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
        error_code |= SMCHG_MUX_PARSE_ERROR_FETCH_RACE_CH;
        // SMCHG_LOG_MSGID_E("1wire, mux_rx_protocol_cb, race_ch fetch fail", 0);
        goto end;
    }

    if (race_ch == 0x05 || race_ch == 0x15)
    {
        if (nxp_uart_mux_header_fetch(&race_type, 1) == false)
        {
            *package_len = 0;
            *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
            error_code |= SMCHG_MUX_PARSE_ERROR_FETCH_CH_TYPE;
            SMCHG_LOG_MSGID_D("nxp_uart, mux_rx_protocol_cb, race_type fetch fail", 0);
            goto end;
        }

        if ((race_type != RACE_TYPE_COMMAND) && (race_type != RACE_TYPE_COMMAND_WITHOUT_RSP))
        {
            *package_len = 0;
            *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
            error_code |= SMCHG_MUX_PARSE_ERROR_CH_TYPE;
            SMCHG_LOG_MSGID_D("nxp_uart, mux_rx_protocol_cb, race_type[0x%X]", 1, race_type);
            goto end;
        }

        if (nxp_uart_mux_header_fetch((uint8_t *)&race_length, 2) == false)
        {
            *package_len = 0;
            *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
            error_code |= SMCHG_MUX_PARSE_ERROR_FETCH_LENGTH;
            SMCHG_LOG_MSGID_D("nxp_uart, mux_rx_protocol_cb, race_length fetch fail", 0);
            goto end;
        }

        if (nxp_uart_mux_header_fetch((uint8_t *)&race_id, 2) == false)
        {
            *package_len = 0;
            *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
            error_code |= SMCHG_MUX_PARSE_ERROR_FETCH_RACE_ID;
            SMCHG_LOG_MSGID_D("nxp_uart, mux_rx_protocol_cb, race_id fetch fail", 0);
            goto end;
        }

        *handle = 0;
        collected_length = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
        if (race_id == 0x0F92)
        {
            if (mux_query_user_handle(gNxpUart.g_nxp_uart.mux_port, "ATCI", &p_handle) == MUX_STATUS_OK)
            {
                /* ATCI race command */
                *handle = p_handle;
                /* RACE cmd format: 05 5D length(2 byte) 0f92 at+test=? */
                *package_len = race_length - 2;
                *consume_len = 6;
            }
            else
            {
                *package_len = 0;
                *consume_len = collected_length;
                error_code |= SMCHG_MUX_PARSE_ERROR_NO_ATCI_HANDLE;
            }
        }
        else if (race_id == 0x2000 || race_id == 0x3000 || race_id == 0x4000)
        {
            if (smchg_1wire_status != SMCHG_1WIRE_COM)
            {
                *package_len = 0;
                *consume_len = collected_length;
                error_code |= SMCHG_MUX_PARSE_ERROR_COM_MODE_STATUS_NOT_MATCH;
                // return;
            }
            else if (mux_query_user_handle(gNxpUart.g_nxp_uart.mux_port, "NXP_COM", &p_handle) == MUX_STATUS_OK)
            {
                /* 1wire cmd */
                if (smchg_mux_buffer.left_data_len >= (race_length - 2))
                {
                    *package_len = collected_length + race_length - 2;
                    *consume_len = 0;
                    *handle = p_handle;
                }
                else
                {
                    *package_len = collected_length + smchg_mux_buffer.left_data_len;
                    *consume_len = 0;
                    *handle = p_handle;
                    SMCHG_LOG_MSGID_E("nxp_uart, mux_rx_protocol_cb fail, data len not enough", 0);
                }
                gNxpUart.g_com_mode_chk_cnt = 0;
            }
            else
            {
                *package_len = 0;
                *consume_len = collected_length;
                error_code |= SMCHG_MUX_PARSE_ERROR_NO_SMCHG_HANDLE;
            }
        }
        else
        {
            if ((mux_query_user_handle(gNxpUart.g_nxp_uart.mux_port, "RACE_CMD", &p_handle) == MUX_STATUS_OK) &&
                (smchg_1wire_status == SMCHG_1WIRE_RACE))
            {
                // race cmd
                if (smchg_mux_buffer.left_data_len >= (race_length - 2))
                {
                    *package_len = collected_length + race_length - 2;
                    *consume_len = 0;
                    *handle = p_handle;
                }
                else
                {
                    *package_len = 0;
                    *consume_len = collected_length + smchg_mux_buffer.left_data_len;
                    *handle = p_handle;
                    SMCHG_LOG_MSGID_E("nxp_uart, RACE mode mux_rx_protocol_cb fail, data len not enough", 0);
                }
                gNxpUart.g_com_mode_chk_cnt = 0;
            }
            else
            {
                *package_len = 0;
                if ((race_length + 4) >= smchg_mux_buffer.total_length)
                {
                    *consume_len = smchg_mux_buffer.total_length;
                }
                else
                {
                    *consume_len = race_length + 4;
                }
                error_code |= SMCHG_MUX_PARSE_ERROR_NO_RACE_HANDLE;
                SMCHG_LOG_MSGID_D("nxp_uart, mux_rx_protocol_cb fail, no_race_handle", 0);
                goto end;
            }
        }
    }
    else if ((smchg_1wire_status == SMCHG_1WIRE_RACE) && (race_ch == 0x01 || race_ch == 0x02 || race_ch == 0x04))
    {
        uint16_t reserved_data = 0;
        uint16_t total_length = 0;
        uint32_t rsv_len = 0, cmd_len = 0;
        gNxpUart.g_com_mode_chk_cnt = 0;
        if (race_ch == 0x01)
        {
            rsv_len = 2;
            cmd_len = 1;
        }
        else if (race_ch == 0x02)
        {
            rsv_len = 2;
            cmd_len = 2;
        }
        else if (race_ch == 0x04)
        {
            rsv_len = 1;
            cmd_len = 1;
        }

        *handle = 0;
        if (mux_query_user_handle(gNxpUart.g_nxp_uart.mux_port, "HCI_CMD", &p_handle) == MUX_STATUS_OK)
        {
            if (nxp_uart_mux_header_fetch((uint8_t *)&reserved_data, rsv_len) == false)
            {
                *package_len = 0;
                *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
                return;
            }
            if (nxp_uart_mux_header_fetch((uint8_t *)&total_length, cmd_len) == false)
            {
                *package_len = 0;
                *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
                return;
            }
            *handle = p_handle;
            if (total_length >= smchg_mux_buffer.left_data_len)
            {
                *package_len = smchg_mux_buffer.left_data_len + rsv_len + cmd_len + 1;
            }
            else
            {
                *package_len = total_length + rsv_len + cmd_len + 1;
            }
            *consume_len = 0;
        }
        else
        {
            SMCHG_LOG_MSGID_E("nxp_uart, mux_rx_protocol_cb , no HCI_CMD handle", 0);
            *package_len = 0;
            *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
            error_code |= SMCHG_MUX_PARSE_ERROR_NO_HCI_HANDLE;
        }
    }
    else
    {
        *package_len = 0;
        *consume_len = smchg_mux_buffer.total_length - smchg_mux_buffer.left_data_len;
        error_code |= SMCHG_MUX_PARSE_ERROR_RACE_CH;
        SMCHG_LOG_MSGID_D("nxp_uart, mux_rx_protocol_cb fail, race_ch[0x%X]", 1, race_ch);
        goto end;
    }
end:
    if (error_code)
    {
        SMCHG_LOG_MSGID_I("nxp_uart, mux_rx_protocol_cb fail, 1wire mode [%d], err_code[0x%X], race_ch[0x%X]", 3, smchg_1wire_status, error_code, race_ch);
    }
}

static smchg_status_t nxp_uart_uart_init(smchg_handle_t *p_sm_handle)
{
    mux_port_setting_t setting;
    mux_protocol_t protocol_callback_1wire = {nxp_uart_mux_tx_protocol_cb, nxp_uart_mux_rx_protocol_cb, NULL};
    mux_status_t mux_init_status;
    smchg_status_t status = SMCHG_STATUS_OK;

    if (p_sm_handle == NULL)
    {
        return SMCHG_STATUS_INVALID_PARAMETER;
    }
    memset(&setting, 0, sizeof(setting));
    setting.dev_setting.uart.uart_config.baudrate = smchg_cfg.com_mode_baud_rate;
    setting.dev_setting.uart.uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    setting.dev_setting.uart.uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    setting.dev_setting.uart.uart_config.parity = HAL_UART_PARITY_NONE;
    setting.dev_setting.uart.flowcontrol_type = MUX_UART_NONE_FLOWCONTROL;
    setting.portLinkRegAddr = 0;

    setting.tx_buffer_size = SMCHG_MUX_TX_BUFF_SIZE;
    setting.rx_buffer_size = SMCHG_MUX_RX_BUFF_SIZE;
    mux_init_status = mux_init(p_sm_handle->mux_port, &setting, &protocol_callback_1wire);
    if (mux_init_status != MUX_STATUS_OK)
    {
        SMCHG_LOG_MSGID_W("nxp_uart, mux_init fail[%d]", 1, mux_init_status);
    }
    mux_init_status = mux_open(p_sm_handle->mux_port, "NXP_COM", &(p_sm_handle->mux_handle), nxp_uart_cb, NULL);

    if (mux_init_status != MUX_STATUS_OK)
    {
        SMCHG_LOG_MSGID_E("nxp_uart, mux_open fail[%d]", 1, mux_init_status);
        assert(0);
    }

    SMCHG_LOG_MSGID_D("nxp_uart, uart_init, baudrate[%d]", 1,
                      smchg_1wire_baudrate_report(setting.dev_setting.uart.uart_config.baudrate));
    return status;
}

static smchg_status_t nxp_uart_com_mode_init(smchg_handle_t *p_sm_handle)
{
    smchg_status_t status = SMCHG_STATUS_OK;

    status = nxp_uart_uart_init(&gNxpUart.g_nxp_uart);
    if (status == SMCHG_STATUS_OK)
    {
        gNxpUart.pNxpUartRxTimer = xTimerCreate("NXP RX", pdMS_TO_TICKS(SMCHG_MUX_RX_HANDLE_TIMER_MS), pdFALSE, NULL, nxp_uart_rx_handle_timer_cb);
        if (!gNxpUart.pNxpUartRxTimer)
        {
            SMCHG_LOG_MSGID_D("nxp_uart, init rx_handle_timer_cb fail", 0);
            assert(0);
        }
    }
    return status;
}

static const uint8_t raceEvtOn1wireDfu[] = {
    0x05, // race header
    0x5D, // race type
    0x05, // lengthL
    0x00, // lengthH
    0x00, // cmd type
    0x20, // cmd tpye
    0x00, // event
    0x00, // R or L
    0x00, // parameter
};

static const uint8_t sys_start_str[] = {'A','B','1','6','5','6',',','s','t','a','r','t'};

void nxp_uart_tx_send_notification(const uint8_t *payload, uint16_t size_payload)
{
    mux_status_t mux_status = MUX_STATUS_ERROR;
    uint32_t tx_size = 0;

    mux_buffer_t buf = {(uint8_t *)payload, size_payload};
    mux_status = mux_tx(gNxpUart.g_nxp_uart.mux_handle, &buf, 1, &tx_size);
    if (mux_status != MUX_STATUS_OK)
    {
        SMCHG_LOG_MSGID_E("nxp_uart, notification mux tx fail [%d]", 1, mux_status);
    }

    {
        nxp_uart_com_mode_tx_done();
    }
}

void nxp_uart_test_timer_cb(TimerHandle_t pxExpiredTimer)
{
    mux_buffer_t buffer;
    buffer.buf_size = 12;
    buffer.p_buf = sys_start_str;
    gNxpUart.g_nxp_uart.state = SMCHG_1WIRE_STATE_COM_WAIT_TX_DONE;
    gNxpUart.g_nxp_uart.cur_cmd_id = buffer.p_buf[NXP_PKT_OFFS_CMD];
    mux_status_t mux_status = MUX_STATUS_ERROR;
    uint32_t tx_size = 0;

    SMCHG_LOG_MSGID_D("nxp_uart, start send", 0);

    mux_status = mux_tx(gNxpUart.g_nxp_uart.mux_handle, &buffer, 1, &tx_size);
    if (mux_status != MUX_STATUS_OK)
    {
        SMCHG_LOG_MSGID_E("nxp_uart, rx_handle, mux tx error, status[%d]", 1, mux_status);
        nxp_uart_reset_smchg_state(&gNxpUart.g_nxp_uart);
    }
}
TimerHandle_t hxd_test_timer;


void nxp_uart_init(void)
{
    uint8_t pwr_off_reason = 0;
    int32_t chg_exist = 0;

    SMCHG_LOG_MSGID_D("nxp_uart, init enter", 0);
    memset(&gNxpUart.g_nxp_uart, 0x0, sizeof(gNxpUart.g_nxp_uart));
    gNxpUart.g_nxp_uart.state = SMCHG_1WIRE_STATE_INIT;
    gNxpUart.g_nxp_uart.cur_cmd_id = 0;
    gNxpUart.g_nxp_uart.cur_cmd = NULL;
    gNxpUart.g_nxp_uart.mux_port = MUX_UART_2;

    gNxpUart.last_cmd = SMCHG_CHG_OUT;

    if (nxp_uart_com_mode_init(&gNxpUart.g_nxp_uart) == SMCHG_STATUS_OK)
    {
        /* 1wire DFU */
        pwr_off_reason = pmu_get_power_off_reason();
        if ((gNxpUart.boot_Flag == 0) && (pwr_off_reason == 0x8))
        {
            SMCHG_LOG_MSGID_D("nxp_uart, boot_evt send", 0);

            nxp_uart_tx_send_notification(raceEvtOn1wireDfu, sizeof(raceEvtOn1wireDfu));

            gNxpUart.boot_Flag = 1;
        }
        //nxp_uart_chg_state_change_cb_register();

        chg_exist = 1;    //nxp_uart_chg_exist();
        if (chg_exist)
        {
            nxp_uart_com_mode();

            hxd_test_timer = xTimerCreate("NXP test", pdMS_TO_TICKS(2000), pdFALSE, NULL, nxp_uart_test_timer_cb);
            xTimerStart(hxd_test_timer, 0);
        }
        else
        {
            nxp_uart_chg_mode();
            nxp_uart_out_of_case(TRUE);
        }
    }
    SMCHG_LOG_MSGID_I("nxp_uart, chg_exist[%d], gNxpUart.boot_flag[%d], pwr_off[%d]", 3, chg_exist, gNxpUart.boot_Flag, pwr_off_reason);
}


uint8_t retrun_channel_id;
uint8_t retrun_app_id;
uint8_t package_usb_recv[250];
uint8_t package_usb_recv_len = 0;
uint8_t return_usb_package[10] = {0x00, 0x05, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0xEB, 0x00};
bool return_save_info = false;
void *race_cmd_nxp_uart_CmdHandler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    SMCHG_LOG_MSGID_I("race_cmd_nxp_uart_CmdHandler, uint16_t[%d], channel_id[%x], app_id[%x]", 3, length, channel_id, pCmdMsg->hdr.id);

    if(nxp_uart_get_mode_status() != SMCHG_1WIRE_FREQ_OTA)
    {
        SMCHG_LOG_MSGID_I("nxp_uart_set_mode_status SMCHG_1WIRE_FREQ_OTA", 0);
        nxp_uart_set_mode_status(SMCHG_1WIRE_FREQ_OTA);
    }
    package_uart_recv_len = 0;
    retrun_channel_id = channel_id;
    retrun_app_id = pCmdMsg->hdr.id;

    {
        mux_buffer_t buffer;
        buffer.buf_size = length-2;
        buffer.p_buf = pCmdMsg->payload;
        gNxpUart.g_nxp_uart.state = SMCHG_1WIRE_STATE_COM_WAIT_TX_DONE;
        gNxpUart.g_nxp_uart.cur_cmd_id = buffer.p_buf[NXP_PKT_OFFS_CMD];
        mux_status_t mux_status = MUX_STATUS_ERROR;
        uint32_t tx_size = 0;

        SMCHG_LOG_MSGID_D("nxp_uart, start send", 0);

        mux_status = mux_tx(gNxpUart.g_nxp_uart.mux_handle, &buffer, 1, &tx_size);
        if (mux_status != MUX_STATUS_OK)
        {
            SMCHG_LOG_MSGID_E("nxp_uart, rx_handle, mux tx error, status[%d]", 1, mux_status);
            nxp_uart_reset_smchg_state(&gNxpUart.g_nxp_uart);
        }
    }

    return NULL;
}

#define RACE_ID_UART_TRANS_0   0x2F20
void fr800x_return_to_usb(uint32_t user_data_len, void *user_data)
{
    SMCHG_LOG_MSGID_D("fr800x_return_to_usb %d", 1, user_data_len);

    if(return_save_info == false)
    {
        race_send_data_to_port(retrun_channel_id, user_data, user_data_len);
    }
    else
    {
        race_send_data_to_port(retrun_channel_id, return_usb_package, 10);
    }
    return_save_info = false;
}

#endif
