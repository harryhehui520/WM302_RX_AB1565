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

#include "battery_management_core.h"
#include "timers.h"
#include "hal_sleep_manager_platform.h"
#ifdef AIR_BTA_PMIC_G2_LP
#include "hal_pmu_charger_2565.h"
#endif

#include "nvkey.h"
#include "nvkey_id_list.h"

#include "hal_rtc_internal.h"

#define PERCENT_UNKNOWN     0xFF

typedef enum {
    BM_STATE_NOT_INIT = 0,
    BM_STATE_START = 1,
} battery_management_state_t;

typedef struct _batt_ctrl_block_t
{
    battery_management_state_t state;

    uint8_t percent_current;
    uint8_t percent_to_user;
    uint8_t percent_in_nvkey;

    uint16_t delayCnt;
}batt_ctrl_block_t;

static batt_ctrl_block_t battCtrl = {
    .state = BM_STATE_NOT_INIT,
    .percent_current = PERCENT_UNKNOWN,
    .percent_to_user = PERCENT_UNKNOWN,
    .percent_in_nvkey = PERCENT_UNKNOWN,
    .delayCnt = 0,
};

#define BATTERY_POWER_LIST_LEN 101	// 102: index 0~100

typedef struct
{
    uint16_t voltage_discharge;   /* 1 mV */
    uint16_t voltage_charging;    /* 1 mV */
    uint16_t current_charging;    /* 1 mA */
} battery_power_info;

static const battery_power_info battery_power_list[BATTERY_POWER_LIST_LEN] =
{
    /*00*/    {0,           0,           0xFFFF},
    /*01*/    {2999,        3603,        0xFFFF},
    /*02*/    {3226,        3648,        0xFFFF},
    /*03*/    {3329,        3657,        0xFFFF},
    /*04*/    {3400,        3669,        0xFFFF},
    /*05*/    {3445,        3675,        0xFFFF},
    /*06*/    {3472,        3690,        0xFFFF},
    /*07*/    {3486,        3698,        0xFFFF},
    /*08*/    {3499,        3716,        0xFFFF},
    /*09*/    {3511,        3726,        0xFFFF},
    /*10*/    {3523,        3737,        0xFFFF},
    /*11*/    {3536,        3760,        0xFFFF},
    /*12*/    {3553,        3772,        0xFFFF},
    /*13*/    {3570,        3796,        0xFFFF},
    /*14*/    {3586,        3808,        0xFFFF},
    /*15*/    {3604,        3827,        0xFFFF},
    /*16*/    {3624,        3835,        0xFFFF},
    /*17*/    {3642,        3848,        0xFFFF},
    /*18*/    {3657,        3853,        0xFFFF},
    /*19*/    {3672,        3858,        0xFFFF},
    /*20*/    {3684,        3864,        0xFFFF},
    /*21*/    {3696,        3867,        0xFFFF},
    /*22*/    {3705,        3871,        0xFFFF},
    /*23*/    {3715,        3873,        0xFFFF},
    /*24*/    {3721,        3876,        0xFFFF},
    /*25*/    {3726,        3877,        0xFFFF},
    /*26*/    {3730,        3879,        0xFFFF},
    /*27*/    {3734,        3882,        0xFFFF},
    /*28*/    {3737,        3883,        0xFFFF},
    /*29*/    {3739,        3886,        0xFFFF},
    /*30*/    {3741,        3888,        0xFFFF},
    /*31*/    {3743,        3889,        0xFFFF},
    /*32*/    {3745,        3893,        0xFFFF},
    /*33*/    {3747,        3894,        0xFFFF},
    /*34*/    {3748,        3898,        0xFFFF},
    /*35*/    {3750,        3899,        0xFFFF},
    /*36*/    {3751,        3903,        0xFFFF},
    /*37*/    {3752,        3905,        0xFFFF},
    /*38*/    {3753,        3906,        0xFFFF},
    /*39*/    {3754,        3910,        0xFFFF},
    /*40*/    {3755,        3912,        0xFFFF},
    /*41*/    {3756,        3916,        0xFFFF},
    /*42*/    {3757,        3918,        0xFFFF},
    /*43*/    {3758,        3921,        0xFFFF},
    /*44*/    {3759,        3925,        0xFFFF},
    /*45*/    {3760,        3927,        0xFFFF},
    /*46*/    {3762,        3932,        0xFFFF},
    /*47*/    {3764,        3934,        0xFFFF},
    /*48*/    {3766,        3937,        0xFFFF},
    /*49*/    {3769,        3942,        0xFFFF},
    /*50*/    {3772,        3944,        0xFFFF},
    /*51*/    {3775,        3950,        0xFFFF},
    /*52*/    {3779,        3953,        0xFFFF},
    /*53*/    {3783,        3956,        0xFFFF},
    /*54*/    {3787,        3963,        0xFFFF},
    /*55*/    {3791,        3966,        0xFFFF},
    /*56*/    {3796,        3969,        0xFFFF},
    /*57*/    {3801,        3977,        0xFFFF},
    /*58*/    {3806,        3980,        0xFFFF},
    /*59*/    {3812,        3988,        0xFFFF},
    /*60*/    {3818,        3992,        0xFFFF},
    /*61*/    {3824,        3996,        0xFFFF},
    /*62*/    {3830,        4005,        0xFFFF},
    /*63*/    {3838,        4009,        0xFFFF},
    /*64*/    {3844,        4013,        0xFFFF},
    /*65*/    {3851,        4023,        0xFFFF},
    /*66*/    {3857,        4028,        0xFFFF},
    /*67*/    {3864,        4037,        0xFFFF},
    /*68*/    {3872,        4042,        0xFFFF},
    /*69*/    {3879,        4047,        0xFFFF},
    /*70*/    {3886,        4058,        0xFFFF},       /* Delta T */
    /*71*/    {3892,        4063,        0xFFFF},       /* 0:00:30 */
    /*72*/    {3899,        4069,        0xFFFF},       /* 0:00:30 */
    /*73*/    {3907,        4080,        0xFFFF},       /* 0:01:00 */
    /*74*/    {3914,        4086,        0xFFFF},       /* 0:00:30 */
    /*75*/    {3921,        4092,        0xFFFF},       /* 0:00:30 */
    /*76*/    {3929,        4104,        0xFFFF},       /* 0:01:00 */
    /*77*/    {3937,        4110,        0xFFFF},       /* 0:00:30 */
    /*78*/    {3944,        4116,        0xFFFF},       /* 0:00:30 */
    /*79*/    {3951,        4128,        0xFFFF},       /* 0:01:00 */
    /*80*/    {3958,        4135,        0xFFFF},       /* 0:00:30 */
    /*81*/    {3965,        4141,        0xFFFF},       /* 0:00:30 */
    /*82*/    {3972,        4156,        0xFFFF},       /* 0:01:00 */
    /*83*/    {3979,        4163,        0xFFFF},       /* 0:00:30 */
    /*84*/    {3988,        4172,        0xFFFF},       /* 0:00:30 */
    /*85*/    {3999,        4190,        0xFFFF},       /* 0:01:00 */
    /*86*/    {4010,        4199,        0xFFFF},       /* 0:00:30 */
    /*87*/    {4021,        0xFFFF,      322},          /* 0:00:30 */
    /*88*/    {4032,        0xFFFF,      272},          /* 0:01:00 */
    /*89*/    {4042,        0xFFFF,      236},          /* 0:01:00 */
    /*90*/    {4049,        0xFFFF,      207},          /* 0:01:00 */
    /*91*/    {4057,        0xFFFF,      184},          /* 0:01:00 */
    /*92*/    {4066,        0xFFFF,      154},          /* 0:01:30 */
    /*93*/    {4076,        0xFFFF,      131},          /* 0:01:30 */
    /*94*/    {4085,        0xFFFF,      107},          /* 0:02:00 */
    /*95*/    {4095,        0xFFFF,      85},           /* 0:02:30 */
    /*96*/    {4106,        0xFFFF,      66},           /* 0:03:00 */
    /*97*/    {4117,        0xFFFF,      48},           /* 0:04:00 */
    /*98*/    {4127,        0xFFFF,      32},           /* 0:06:00 */
    /*99*/    {4140,        0xFFFF,      18},           /* 0:09:30 */
    /*max*/   {0xFFFF,      0xFFFF,      0}
};

void battery_management_charger_task(void *pvParameters)
{
    const TickType_t xDelay = CHARGER_REGULAR_TIME * TIMEOUT_PERIOD_1S;
    while (1)
    {
        vTaskDelay( xDelay );

        /*Log output by BT*/
        LOG_MSGID_I(battery_management, "[BM_TASK]Bat temp = %d(Celsius), capacity = %d, chg exist = %d, bat volt = %d(mV), bat state = %d", 5,
                    (int)battery_management_get_battery_property(BATTERY_PROPERTY_TEMPERATURE),
                    (int)battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY),
                    (int)battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST),
                    (int)battery_management_get_battery_property(BATTERY_PROPERTY_VOLTAGE),
                    (int)battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_STATE));
    }
}

/*==========[Battery Management:Gague]==========*/

#define ABS(a)          (((a) < 0) ? -(a) : (a))

bool battery_management_gauge_save_percent_to_nvkey(uint8_t percent, bool force)
{
    bool update = FALSE;

    /* Save immediately. */
    if(force)
    {
        update = TRUE;
    }
    /* Reduce wirting times for the SPI-flash erase/program cycles limitation. */
    else if((percent % 5) == 0 || ABS(battCtrl.percent_in_nvkey - percent) >= 5)
    {
        update = TRUE;
    }

    nvkey_status_t status = NVKEY_STATUS_ERROR;
    if (update)
    {
        if (force)
        {
            LOG_MSGID_I(battery_management, "batsns_nvkey save percent:%d->%d (By forced)", 2, battCtrl.percent_in_nvkey, percent);
        }
        else
        {
            LOG_MSGID_I(battery_management, "batsns_nvkey save percent:%d->%d", 2, battCtrl.percent_in_nvkey, percent);
        }

        battCtrl.percent_in_nvkey = percent;

        status = nvkey_write_data(NVID_CUS_APP_BATTERY_PERCENT, (const uint8_t *)&battCtrl.percent_in_nvkey, sizeof(battCtrl.percent_in_nvkey));
        if (NVKEY_STATUS_OK != status)
        {
            LOG_MSGID_I(battery_management, "batsns_nvkey save failed %d", 1, status);
        }
    }

    return NVKEY_STATUS_OK == status ? TRUE : FALSE;
}

uint8_t battery_management_gauge_read_percent_from_nvkey(void)
{
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    uint32_t read_size = sizeof(battCtrl.percent_in_nvkey);
    status = nvkey_read_data(NVID_CUS_APP_BATTERY_PERCENT, (uint8_t *)&battCtrl.percent_in_nvkey, &read_size);
    if (NVKEY_STATUS_OK != status)
    {
        LOG_MSGID_I(battery_management, "batsns_nvkey read failed %d", 1, status);
    }

    return NVKEY_STATUS_OK == status ? battCtrl.percent_in_nvkey : PERCENT_UNKNOWN;
}

static uint16_t battery_management_gauge_get_full_bat_in_charging(void)
{
    uint8_t percent = 0;
    for(percent = 0; percent <= BATTERY_POWER_LIST_LEN - 1; percent++)
    {
        if(battery_power_list[percent + 1].voltage_charging == 0xFFFF)
        {
            break;
        }
    }

    return battery_power_list[percent].voltage_charging;
}

/* When charging, the voltage of battery would be pulled high a bit, trim it here. */
static uint8_t battery_management_gauge_batsns_to_percent(void)
{
#ifdef AIR_BTA_PMIC_G2_LP
    uint8_t percent = 0;
    uint32_t batsns = pmu_bat_get_pure_volt();
    int32_t is_charger_exist = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);

    if (!is_charger_exist)
    {
        for (percent = 0; percent <= BATTERY_POWER_LIST_LEN - 1; percent++)
        {
            if (batsns >= battery_power_list[percent].voltage_discharge && batsns < battery_power_list[percent + 1].voltage_discharge)
            {
                break;
            }
        }
    }
    else
    {
        if (batsns < battery_management_gauge_get_full_bat_in_charging())
        {
            for(percent = 0; percent <= BATTERY_POWER_LIST_LEN - 1; percent++)
            {
                if(batsns >= battery_power_list[percent].voltage_charging && batsns < battery_power_list[percent + 1].voltage_charging)
                {
                    break;
                }
            }
        }
        else
        {
            percent = 100;    /* Just set a target. */
        }
    }

    LOG_MSGID_I(battery_management, "batsns_to_percent Vbat:%d, Charging:%d -> Target Percent:%d", 3, batsns, is_charger_exist, percent);

    return percent;
#endif
}

/*Linear gauge use smooth VBAT*/
static void battery_management_gauge_batsns_smooth(uint8_t percent_target)
{
    if(battCtrl.delayCnt < 0xffff)
    {
        battCtrl.delayCnt++;
    }

    if (battCtrl.state == BM_STATE_NOT_INIT)
    {
        uint8_t percent = battery_management_gauge_read_percent_from_nvkey();
        int reason = hal_rtc_get_power_on_reason();
        /* Case 1. Firmware burned just now, need initialization. */
        /* Case 2. Battery is changed. */
        if (PERCENT_UNKNOWN == percent || RTC_POWERED_BY_1ST == reason)
        {
            battCtrl.percent_current = percent_target;

            battery_management_gauge_save_percent_to_nvkey(battCtrl.percent_current, TRUE);
        }
        else
        {
            /* Restore percent from nvid */
            battCtrl.percent_current = percent;
        }

        LOG_MSGID_I(battery_management, "batsns_smooth init, Current Percent:%d(Target Percent:%d)", 2, battCtrl.percent_current, percent_target);

        battCtrl.delayCnt = 0;
        battCtrl.state = BM_STATE_START;
    }
    else if (battCtrl.state == BM_STATE_START)
    {
        int32_t is_charger_exist = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);

        if (!is_charger_exist)
        {
            uint8_t delayCnt = 0;

            // In noraml case, it will take 3~4min for 1% power consumption with -70mA discharging current. Smaller discharging
            // current is ok, for example, 1% for -30mA discharging current will take about 7~8min. But bigger one will be
            // a problem, this will cause the battery level presenting to the user is not real and sudden shutdown finally.
            if (percent_target < 5)
            {
                delayCnt = 1;   // 1: 10s
            }
            else if (percent_target < 20)
            {
                delayCnt = 6;   // 6: 1min
            }
            else
            {
                delayCnt = 18;   // 18: 3min
            }

            if (battCtrl.delayCnt > delayCnt)
            {
                battCtrl.delayCnt = 0;

                /* Only allow decrease on discharging. */
                if(percent_target > battCtrl.percent_current)
                {
                    LOG_MSGID_I(battery_management, "batsns_smooth on discharging error[Percent:%d->%d]", 2, battCtrl.percent_current, percent_target);
                }
                else
                {
                    if (battCtrl.percent_current > 0)
                    {
                        battCtrl.percent_current -= 1;
                    }
                    
                    LOG_MSGID_I(battery_management, "batsns_smooth on discharging, Current Percent:%d(Target Percent:%d)", 2, battCtrl.percent_current, percent_target);
                    
                    battery_management_gauge_save_percent_to_nvkey(battCtrl.percent_current, FALSE);
                }
            }
        }
        else
        {
            if (battCtrl.delayCnt > 4)   // 4: 40s, and 40s * 100 / 60s = 67min match the spec of whole time full-charged.
            {
                battCtrl.delayCnt = 0;

                /* Only allow increase on charging. */
                if(percent_target < battCtrl.percent_current)
                {
                    LOG_MSGID_I(battery_management, "batsns_smooth on charging error[Percent:%d->%d]", 2, battCtrl.percent_current, percent_target);
                }
                else
                {
                    if (battCtrl.percent_current < 100)
                    {
                        battCtrl.percent_current += 1;
                    }
                    
                    LOG_MSGID_I(battery_management, "batsns_smooth on charging, Current Percent:%d(Target Percent:%d)", 2, battCtrl.percent_current, percent_target);
                    
                    battery_management_gauge_save_percent_to_nvkey(battCtrl.percent_current, FALSE);
                }
            }
        }
    }
    else
    {
        LOG_MSGID_I(battery_management, "batsns_smooth step error", 0);
    }
}

void battery_management_gauge_linear_task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, GAUGE_LINEAR_REGULAR_TIME * TIMEOUT_PERIOD_1S);

        battery_management_gauge_batsns_smooth(battery_management_gauge_batsns_to_percent());
    }
}

uint32_t battery_management_gauge_get_vbat(void)
{
    return battery_power_list[battCtrl.percent_current].voltage_discharge;
}

uint32_t battery_management_gauge_get_percent(void)
{
    uint32_t percent = battCtrl.percent_current;

    if(MTK_BATTERY_ULTRA_LOW_BAT >= percent)
    {
        percent = MTK_BATTERY_ULTRA_LOW_BAT;
    }

    return percent;
}

void battery_management_gauge_init(void)
{
    battery_management_gauge_batsns_smooth(battery_management_gauge_batsns_to_percent());
}

