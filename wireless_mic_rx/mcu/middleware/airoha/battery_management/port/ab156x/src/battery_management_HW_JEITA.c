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

/*Common*/
#include "battery_management_core.h"
#include "hal_pmu.h"
extern battery_managerment_control_info_t bm_ctrl_info;
extern battery_basic_data bm_cust;
extern TimerHandle_t xbm_jeita_timer;
extern const char *bm_ntc_state[10];    /*Data : For output log */

#if defined(AIR_BTA_PMIC_G2_LP)
#include "battery_management_sw_ntc.h"
#include "hal_pmu_cali_2565.h"
#include "hal_pmu_charger_2565.h"
uint8_t executing_status=sw_ntc_charger_normal;
extern uint8_t battery_sw_ntc_feature;

void battery_jeita_task(void *pvParameters)
{
    uint32_t interval = pmu_ntc_get_interval();
    const TickType_t xDelay = (interval * TIMEOUT_PERIOD_1S) / portTICK_PERIOD_MS;
    while(1){
        vTaskDelay(xDelay);
#ifndef BATTERY_NTC_LESS
        int temp = 0;
        pmu_ntc_state_t ntc_state = PMU_NTC_NORM;
        uint32_t radio = 0;

        pmu_ntc_update_state(&temp, &ntc_state, &radio);
        g_ntc_temp = temp;
        g_ntc_radio = radio;
        LOG_W(MPLOG,"[BM_JEITA][ntc temp :%d] [ntc_state %d :%s]" ,temp,ntc_state,bm_ntc_state[ntc_state]);/*Log output by BT*/

        if (ntc_state == PMU_NTC_NORM) {
            if (executing_status != PMU_NTC_NORM) {
                executing_status = PMU_NTC_NORM;
                LOG_MSGID_I(battery_management, "[BM_JEITA]Normal State",0);
            }
        } else if (ntc_state == PMU_NTC_WARM) {
            if (executing_status != PMU_NTC_WARM) {
                executing_status = PMU_NTC_WARM;
                LOG_MSGID_I(battery_management, "[BM_JEITA]Warm State",0);
            }
        } else if (ntc_state == PMU_NTC_COOL) {
            if (executing_status != PMU_NTC_COOL) {
                executing_status = PMU_NTC_COOL;
                LOG_MSGID_I(battery_management, "[BM_JEITA]Cool State",0);
            }
        } else if (ntc_state == PMU_NTC_HOT) {
            if (executing_status != PMU_NTC_HOT) {
                executing_status = PMU_NTC_HOT;
                LOG_MSGID_I(battery_management, "[BM_JEITA]Hot State",0);
            }
        } else if (ntc_state == PMU_NTC_COLD) {
            if (executing_status != PMU_NTC_COLD) {
                executing_status = PMU_NTC_COLD;
                LOG_MSGID_I(battery_management, "[BM_JEITA]Cold State",0);
            }
        }else if (ntc_state == PMU_NTC_PWR_OFF) {
            if (executing_status != PMU_NTC_PWR_OFF) {
                executing_status = PMU_NTC_PWR_OFF;
                LOG_MSGID_I(battery_management, "[BM_JEITA]Pwr_off State",0);
            }
        }else {
            LOG_MSGID_E(battery_management, "[BM_JEITA]Error assert", 0);
        }
        bm_ctrl_info.jeita_state = executing_status;
#else
        LOG_MSGID_E(battery_management, "[BM_JEITA]ntc not support set Normal State", 0);
#endif /* BATTERY_NTC_LESS */
    }
}
#endif

