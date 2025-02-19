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

#ifndef __HAL_PMU_MODULE_H__
#define __HAL_PMU_MODULE_H__

#include "hal_platform.h"

#ifdef HAL_PMU_MODULE_ENABLED

#ifdef AIR_BTA_PMIC_G2_HP
#include "hal_pmu_ab2568_platform.h"
#elif defined AIR_BTA_PMIC_G2_LP
#include "hal_pmu_ab2565_platform.h"
#endif

/*
 * HAL_KEEP_VAUD18_POWER : Keep VAUD18 power on */
#ifdef MTK_KEEP_VAUD18_POWER
#define HAL_KEEP_VAUD18_POWER
#endif

/* PMU low power setting */
#define PMU_LOW_POWER_SETTING
//#define PMU_LOW_POWER_VA18_SETTING
//#define PMU_LOW_POWER_VCORE_SETTING
#define PMU_LOW_POWER_VIO18_SETTING
//#define PMU_LOW_POWER_VRF_SETTING
//#define PMU_LOW_POWER_VAUD18_SETTING

#define PMIC_SLAVE_ADDR            0x6B
#define INVALID_INTERRUPT_VALUE    0xFF
#define PMU_PRESS_PK_TIME (3 * 100000)  // HWJ: 100ms -> 0.3s, our ui use long press power on, set this to block single click at the very beginning.

#define PMU_VCORE_CP     0xA20A0204

// G3 only
#if (defined (AIR_BTA_IC_PREMIUM_G3) || defined (AIR_BTA_IC_PREMIUM_G2))
typedef enum
{
    VSRAM_VOLTAGE_0P5,
    VSRAM_VOLTAGE_0P56,
    VSRAM_VOLTAGE_0P58,
    VSRAM_VOLTAGE_0P6,
    VSRAM_VOLTAGE_0P65,
    VSRAM_VOLTAGE_0P78,
    VSRAM_VOLTAGE_0P8,
    VSRAM_VOLTAGE_0P82,
    VSRAM_VOLTAGE_0P84,
    VSRAM_VOLTAGE_0P86,
    VSRAM_VOLTAGE_0P88,
    VSRAM_VOLTAGE_0P9,
    VSRAM_VOLTAGE_0P92,
    VSRAM_VOLTAGE_0P97,
    VSRAM_VOLTAGE_0P98,
    VSRAM_VOLTAGE_1P0,
}pmu_vsram_voltage_t;

typedef enum
{
    VRTC_VOLTAGE_0P65,
    VRTC_VOLTAGE_0P6625,
    VRTC_VOLTAGE_0P675,
    VRTC_VOLTAGE_0P6875,
    VRTC_VOLTAGE_0P7,
    VRTC_VOLTAGE_0P7125,
    VRTC_VOLTAGE_0P725,
    VRTC_VOLTAGE_0P7375,
    VRTC_VOLTAGE_0P75,
    VRTC_VOLTAGE_0P7625,
    VRTC_VOLTAGE_0P775,
    VRTC_VOLTAGE_0P7875,
    VRTC_VOLTAGE_0P8,
    VRTC_VOLTAGE_0P8125,
    VRTC_VOLTAGE_0P825,
    VRTC_VOLTAGE_0P8325,
}pmu_vrtc_voltage_t;

typedef enum
{
   PMU_STRUP_LATCH_CON0    = 0,
   PMU_STRUP_LATCH_CON1    = 1,
   PMU_STRUP_LATCH_CON2    = 2,
   PMU_STRUP_RTC_GPIO0  = 3,
   PMU_STRUP_RTC_GPIO1  = 4,
   PMU_STRUP_RTC_GPIO2  = 5,
   PMU_STRUP_RTC_GPIO3  = 6,
   PMU_STRUP_CAPTOUCH      = 7,
}pmu_strup_mux_t;

typedef enum {
    PMU_LOWPOWER_MODE,
    PMU_NORMAL_MODE,
} pmu_buckldo_stage_t;

typedef enum {
       PMIC_DVS_DEFAULT=0,
       PMIC_RISING_0P55_0P65 = 1,    /* VCORE WI/VSRAM WO wait */
       PMIC_RISING_0P65_0P8 = 2,    /* VCORE WI/VSRAM WI wait */
       PMIC_RISING_0P55_0P8 = 3,    /* VCORE WI/VSRAM WI wait */
       PMIC_FALLING_0P8_0P65 = 4,   /* VCORE WI/VSRAM WI wait */
       PMIC_FALLING_0P65_0P55 = 5,   /* VCORE WO/VSRAM WO wait */
       PMIC_FALLING_0P8_0P55 = 6,   /* VCORE WI/VSRAM WI wait */
} pmu_vsram_dvs_state_t;

typedef enum {
    PMU_VAUD18_0P7_V,
    PMU_VAUD18_0P8_V,
    PMU_VAUD18_0P9_V,
    PMU_VAUD18_1P2_V,
    PMU_VAUD18_1P3_V,
    PMU_VAUD18_1P77_V,
    PMU_VAUD18_1P8_V,
} pmu_vaud18_voltage_t;

typedef enum {
    PMU_3VVREF_1P8_V,
    PMU_3VVREF_2P78_V,
    PMU_3VVREF_1P9_V,
    PMU_3VVREF_2P0_V,
    PMU_3VVREF_2P1_V,
    PMU_3VVREF_2P2_V,
    PMU_3VVREF_2P4_V,
    PMU_3VVREF_2P5_V,
} pmu_3vvref_voltage_t;

typedef enum {
    PMU_VPA_1p2V,
    PMU_VPA_1p4V,
    PMU_VPA_1p6V,
    PMU_VPA_1p8V,
    PMU_VPA_2p2V,
} pmu_power_vpa_voltage_t;

typedef enum {
    PMU_CLASSAB,
    PMU_CLASSG2,
    PMU_CLASSG3,
    PMU_CLASSD,
} pmu_audio_mode_t;

typedef enum {
    PMU_AUDIO_PINOUT_L,
    PMU_AUDIO_PINOUT_M,
    PMU_AUDIO_PINOUT_H,
} pmu_audio_pinout_t;

typedef enum {
    PMIC_MICBIAS_LDO0,
    PMIC_MICBIAS_LDO1,
    PMIC_MICBIAS_LDO2,
} pmu_micbias_ldo_t;

typedef enum {
    PMIC_MICBIAS0,
    PMIC_MICBIAS1,
    PMIC_MICBIAS2,
    PMIC_MICBIAS_0_1,
    PMIC_MICBIAS_ALL,
} pmu_micbias_index_t;

typedef enum {
    PMIC_MICBIAS_LP,
    PMIC_MICBIAS_NM,
    PMIC_MICBIAS_HPM,
} pmu_micbias_mode_t;

typedef enum {
    PMIC_WDT_REG,
    PMIC_WDT_WARM,
    PMIC_WDT_COLD,
} pmu_wdtrstb_act_t;

#ifdef AIR_BTA_IC_PREMIUM_G3_TYPE_S
typedef enum {
    PMU_AUX_PN_ZCV,
    PMU_AUX_WK_ZCV,
    PMU_AUX_BATSNS,
    PMU_AUX_BAT_RECHARGER,
    PMU_AUX_VBUS,
    PMU_AUX_VBUS_UART,
    PMU_AUX_CHR_THM,
    PMU_AUX_HW_JEITA,
    PMU_AUX_PMIC_AP,
    PMU_AUX_PMIC_AUTO,
    PMU_AUX_MAX,
} pmu_adc_channel_t;
#elif defined AIR_BTA_IC_PREMIUM_G2_TYPE_68
typedef enum {
    PMU_AUX_PN_ZCV,
    PMU_AUX_WK_ZCV,
    PMU_AUX_BATSNS,
    PMU_AUX_LBAT,
    PMU_AUX_LBAT2_VBATLOW,
    PMU_AUX_BAT_RECHARGER,
    PMU_AUX_VBUS,
    PMU_AUX_CHR_THM,
    PMU_AUX_HW_JEITA,
    PMU_AUX_PMIC_AP,
    PMU_AUX_PMIC_AUTO,
    PMU_AUX_VBUS_UART,
    PMU_AUX_MAX,
} pmu_adc_channel_t;
#elif defined AIR_BTA_IC_PREMIUM_G3_TYPE_P
typedef enum {
    PMU_AUX_VICHG,
    PMU_AUX_VBAT,
    PMU_AUX_VCHG,
    PMU_AUX_LDO_BUCK,
    PMU_AUX_VBAT_CALI,
    PMU_AUX_VIN,
} pmu_adc_channel_t;
#endif

typedef enum {
    HAL_BATTERY_VOLT_03_5000_V = 35000,         /**< define voltage as  3500 mV */
    HAL_BATTERY_VOLT_03_6000_V = 36000,         /**< define voltage as  3600 mV */
    HAL_BATTERY_VOLT_03_7000_V = 37000,         /**< define voltage as  3700 mV */
    HAL_BATTERY_VOLT_03_7750_V = 37750,         /**< define voltage as  3775 mV */
    HAL_BATTERY_VOLT_03_8000_V = 38000,         /**< define voltage as  3800 mV */
    HAL_BATTERY_VOLT_03_8500_V = 38500,         /**< define voltage as  3850 mV */
    HAL_BATTERY_VOLT_03_9000_V = 39000,         /**< define voltage as  3900 mV */
    HAL_BATTERY_VOLT_04_0000_V = 40000,         /**< define voltage as  4000 mV */
    HAL_BATTERY_VOLT_04_0500_V = 40500,         /**< define voltage as  4050 mV */
    HAL_BATTERY_VOLT_04_1000_V = 41000,         /**< define voltage as  4100 mV */
    HAL_BATTERY_VOLT_04_1250_V = 41250,         /**< define voltage as  4125 mV */
    HAL_BATTERY_VOLT_04_1375_V = 41375,         /**< define voltage as  4137.5 mV */
    HAL_BATTERY_VOLT_04_1500_V = 41500,         /**< define voltage as  4150 mV */
    HAL_BATTERY_VOLT_04_1625_V = 41625,         /**< define voltage as  4162.5 mV */
    HAL_BATTERY_VOLT_04_1750_V = 41750,         /**< define voltage as  4175 mV */
    HAL_BATTERY_VOLT_04_1875_V = 41875,         /**< define voltage as  4187.5 mV */
    HAL_BATTERY_VOLT_04_2000_V = 42000,         /**< define voltage as  4200 mV */
    HAL_BATTERY_VOLT_04_2125_V = 42125,         /**< define voltage as  4212 mV */
    HAL_BATTERY_VOLT_04_2250_V = 42250,         /**< define voltage as  4225 mV */
    HAL_BATTERY_VOLT_04_2375_V = 42375,         /**< define voltage as  4237.5 mV */
    HAL_BATTERY_VOLT_04_2500_V = 42500,         /**< define voltage as  4250 mV */
    HAL_BATTERY_VOLT_04_2625_V = 42625,         /**< define voltage as  4262.5 mV */
    HAL_BATTERY_VOLT_04_2750_V = 42750,         /**< define voltage as  4275 mV */
    HAL_BATTERY_VOLT_04_2875_V = 42875,         /**< define voltage as  4287.5 mV */
    HAL_BATTERY_VOLT_04_3000_V = 43000,         /**< define voltage as  4300 mV */
    HAL_BATTERY_VOLT_04_3125_V = 43125,         /**< define voltage as  4312.5 mV */
    HAL_BATTERY_VOLT_04_3250_V = 43250,         /**< define voltage as  4325 mV */
    HAL_BATTERY_VOLT_04_3375_V = 43375,         /**< define voltage as  4337.5 mV */
    HAL_BATTERY_VOLT_04_3500_V = 43500,         /**< define voltage as  4350 mV */
    HAL_BATTERY_VOLT_04_3625_V = 43625,         /**< define voltage as  4362.5 mV */
    HAL_BATTERY_VOLT_04_3750_V = 43750,         /**< define voltage as  4375 mV */
    HAL_BATTERY_VOLT_04_3875_V = 43875,         /**< define voltage as  4387.5 mV */
    HAL_BATTERY_VOLT_04_4000_V = 44000,         /**< define voltage as  4400 mV */
    HAL_BATTERY_VOLT_04_4125_V = 44125,         /**< define voltage as  4412.5 mV */
    HAL_BATTERY_VOLT_04_4375_V = 44375,         /**< define voltage as  4437.5 mV */
    HAL_BATTERY_VOLT_04_4250_V = 44250,         /**< define voltage as  4425 mV */
    HAL_BATTERY_VOLT_04_4500_V = 44500,         /**< define voltage as  4450 mV */
    HAL_BATTERY_VOLT_04_4625_V = 44625,         /**< define voltage as  4462.5 mV */
    HAL_BATTERY_VOLT_04_4750_V = 44750,         /**< define voltage as  4475 mV */
    HAL_BATTERY_VOLT_04_4875_V = 44875,         /**< define voltage as  4487.5 mV */
    HAL_BATTERY_VOLT_04_5000_V = 45000,         /**< define voltage as  4500 mV */
    HAL_BATTERY_VOLT_04_5500_V = 45500,         /**< define voltage as  4550 mV */
    HAL_BATTERY_VOLT_04_6000_V = 46000,         /**< define voltage as  4600 mV */
    HAL_BATTERY_VOLT_06_0000_V = 60000,         /**< define voltage as  6000 mV */
    HAL_BATTERY_VOLT_06_5000_V = 65000,         /**< define voltage as  6500 mV */
    HAL_BATTERY_VOLT_07_0000_V = 70000,         /**< define voltage as  7000 mV */
    HAL_BATTERY_VOLT_07_5000_V = 75000,         /**< define voltage as  7500 mV */
    HAL_BATTERY_VOLT_08_5000_V = 85000,         /**< define voltage as  8500 mV */
    HAL_BATTERY_VOLT_09_5000_V = 95000,         /**< define voltage as  9500 mV */
    HAL_BATTERY_VOLT_10_5000_V = 105000,        /**< define voltage as 10500 mV */
    HAL_BATTERY_VOLT_MAX,
    HAL_BATTERY_VOLT_INVALID
} HAL_BATTERY_VOLTAGE_ENUM;

typedef enum {
    ICL_TSETP_0US   = 0,    //  0us
    ICL_TSETP_16US  = 1,    //  16us (default)
    ICL_TSETP_128uS = 2,    //  128us
    ICL_TSETP_256US = 3,    //  256us
} pmu_icl_tstep_t;

typedef enum{
        RG_ICC_20P    = 0,
        RG_ICC_40P    = 4,
        RG_ICC_60P    = 5,
        RG_ICC_80P    = 6,
        RG_ICC_100P   = 7,
}pmu_jeita_perecnt_level_t;

typedef enum
{
    TST_W_KEY_SW_MODE  = 0,
    TST_W_KEY_HW_MODE  = 1,
}pmu_protect_mode_t;

// typedef enum {
//     NORMAL=0,
//     PMU,
//     RTC,
//     CAP,
// } pmu_debug_mode_t;

typedef enum {
    PMU_DEBOUNCE_PWRKEY,
    PMU_RELEASE_PWRKEY,
    PMU_REPRESS_PWRKEY,
    PMU_RESET_DEFAULT,
} pmu_lpsd_scenario_t;

typedef enum {
    PMU_DURATION_8S,
    PMU_DURATION_10S,
    PMU_DURATION_15S,
    PMU_DURATION_20S,
} pmu_lpsd_time_t;

/*=====APMIC LP==*/

typedef enum {
    PMU_LOW_LEVEL,
    PMU_NORMAL_LEVEL,
    PMU_HIGH_LEVEL,
} pmu_slt_mode_t;

typedef enum {
    PMU_PRECC,
    PMU_FASTCC,
} pmu_safety_timer_t;

typedef enum {
    PMU_RIPPLE_OFF     = 0,
    PMU_RIPPLE_ON      = 1,
} pmu_ripple_operate_t;

typedef enum {
    PMU_RSTPAT_SRC_VBUS         = 0,
    PMU_RSTPAT_SRC_VBUS_UART    = 1,
}pmu_rstpat_src_t;

/***************************** 1wire *******************************/
typedef enum {
    PMU_1WIRE_LOW_BAT,
    PMU_1WIRE_NORM_BAT,
} pmu_1wire_bat_t;

typedef enum {
    PMU_1WIRE_INIT_TO_OUT_OF_CASE_LOW_BAT,
    PMU_1WIRE_INIT_TO_OUT_OF_CASE_NORM_BAT,
    PMU_1WIRE_INIT_TO_CHG_IN,
    PMU_1WIRE_OUT_OF_CASE_TO_CHG_IN_NORM_BAT,
    PMU_1WIRE_OUT_OF_CASE_TO_CHG_IN_LOW_BAT,
    PMU_1WIRE_COM_TO_OUT_OF_CASE,
    PMU_1WIRE_CHG_IN_TO_COM_NORM_BAT,
    PMU_1WIRE_CHG_IN_TO_COM_LOW_BAT,
    PMU_1WIRE_COM_TO_CHG_IN_NORM_BAT,
    PMU_1WIRE_COM_TO_CHG_IN_LOW_BAT,
    PMU_1WIRE_COM_TO_PWR_SAVE,
    PMU_1WIRE_ENTER_TO_LOG_NORM_BAT,
    PMU_1WIRE_ENTER_TO_LOG_LOW_BAT,
    PMU_1WIRE_MAX,
}pmu_1wire_operate_t;

void pmu_1wire_cfg(pmu_1wire_operate_t state);
uint32_t pmu_1wire_get_vbus_uart_volt(void);

//#define PMU_BOOTLOADER_ENABLE_CHARGER
#ifdef PMU_BOOTLOADER_ENABLE_CHARGER
#define PMU_BL_PRECC pmu_fastcc_chrcur_5mA
#define PMU_BL_CC pmu_fastcc_chrcur_50mA
#define PMU_BL_CV 6
#endif
#endif /* AIR_BTA_IC_PREMIUM_G3 */

typedef enum {
    PMU_KEY = 0x1,
    PMU_RTCA = 0x2,
    PMU_CHRIN =0x4,
    BOOT_MODE=0x8000,
} pmu_power_on_reason_t;

typedef enum {
    PMU_OFF_MODE = 0,
    PMU_RTC_MODE = 1,
    PMU_WD_RST = 8,
    PMU_REGEN_LPSD = 10,
    PMU_SYS_RST = 13,
    PMU_CAP_LPSD = 14,
} pmu_power_off_reason_t;

typedef enum {
    IBAT_TUNE_TRIM = 0,
} pmu_charger_parameter_t;
typedef enum{
    PMU_LOCK=0,
    PMU_UNLOCK,
    PMU_TEMP
}pmu_lock_parameter_t;

typedef enum {
    PMU_NONE          = 0,                 /**< NONE Trigger */
    PMU_EDGE_RISING   = 1,                 /**< edge and rising trigger */
    PMU_EDGE_FALLING  = 2,                 /**< edge and falling trigger */
    PMU_EDGE_FALLING_AND_RISING = 3        /**< edge and falling or rising trigger */
} pmu_int_trigger_mode_t;

typedef enum {
    PMU_STATUS_INVALID_PARAMETER  = -1,     /**< pmu error invalid parameter */
    PMU_STATUS_ERROR              = 0,     /**< pmu undefined error */
    PMU_STATUS_SUCCESS            = 1       /**< pmu function ok */
}pmu_status_t;

typedef enum {
    PMU_INVALID = -1,
    PMU_ERROR   = 0,
    PMU_OK    = 1
} pmu_operate_status_t;

typedef enum {
    PMU_OFF    = 0,
    PMU_ON   = 1,
} pmu_power_operate_t;

typedef enum {
    PMU_SW_MODE,
    PMU_HW_MODE,
} pmu_control_mode_t;

// typedef enum {
//     PMU_DURATION_8S,
//     PMU_DURATION_10S,
//     PMU_DURATION_15S,
//     PMU_DURATION_20S,
// } pmu_pwrkey_time_t;

// typedef enum {
//     PMU_DEBOUNCE_PWRKEY,
//     PMU_RELEASE_PWRKEY,
//     PMU_REPRESS_PWRKEY,
//     PMU_RESET_DEFAULT,
// } pmu_pwrkey_scenario_t;

typedef enum {
    PMU_PK_PRESS    = 0,
    PMU_PK_RELEASE   = 1,
} pmu_pk_operate_t;

typedef enum {
    PMU_PWROFF,
    PMU_RTC,
    PMU_SLEEP,
    PMU_NORMAL,
    PMU_DVS,
    PMU_RTC_EXCEPTION,
} pmu_power_stage_t;

typedef enum {
    PMIC_VAUD18_1P45_V,
    PMIC_VAUD18_1P50_V,
    PMIC_VAUD18_1P55_V,
    PMIC_VAUD18_1P60_V,
    PMIC_VAUD18_1P65_V,
    PMIC_VAUD18_1P70_V,
    PMIC_VAUD18_1P71_V,
    PMIC_VAUD18_1P75_V,
    PMIC_VAUD18_1P80_V,
} pmu_power_vaud18_voltage_t;

#ifdef AIR_BTA_IC_PREMIUM_G2
typedef enum {
       PMIC_VCORE_0P5_V,
       PMIC_VCORE_0P6_V,
       PMIC_VCORE_0P7_V,
       PMIC_VCORE_0P73_V,
       PMIC_VCORE_0P75_V,
       PMIC_VCORE_0P8_V,
       PMIC_VCORE_0P9_V,
       PMIC_VCORE_FAIL_V,
} pmu_power_vcore_voltage_t;
#elif defined AIR_BTA_IC_PREMIUM_G3
typedef enum {
       PMIC_VCORE_0P525_V,
       PMIC_VCORE_0P55_V,
       PMIC_VCORE_0P65_V,
       PMIC_VCORE_0P75_V,
       PMIC_VCORE_0P80_V,
       PMIC_VCORE_0P85_V,
       PMIC_VCORE_FAIL_V,
} pmu_power_vcore_voltage_t;
#endif

typedef enum {
       PMIC_VSRAM_0P9=0,
       PMIC_VSRAM_0P85=1,
       PMIC_VSRAM_0P8=2,
} pmu_power_vsram_voltage_t;

typedef enum{
    PMU_POWER_STABLE=0,
    PMU_POWER_TRY_TO_ENABLE,
    PMU_POWER_TRY_TO_DISABLE,
}pmu_power_status_t;
#ifdef AIR_BTA_IC_PREMIUM_G2
typedef enum {
    PMU_BUCK_VCORE,     //0.7~13V
    PMU_BUCK_VIO18,     //1.8V
    PMU_BUCK_VRF,       //1.45V/2.2V
    PMU_BUCK_VAUD18,    //0.9V/1.8V
    PMU_LDO_VA18,       //1.8V
    PMU_LDO_VLDO33,     //3.3V
    PMU_LDO_VRF,       //1.8V
    PMU_LDO_VSRAM,
} pmu_power_domain_t;
#elif AIR_BTA_IC_PREMIUM_G3
typedef enum {
    PMU_BUCK_VCORE,
    PMU_BUCK_VIO18,
    PMU_BUCK_VRF,
    PMU_BUCK_VAUD18,
    PMU_BUCK_VPA,
    PMU_LDO_VA18,
    PMU_LDO_VLDO31,
    PMU_LDO_VLDO33,
    PMU_LDO_VSRAM,
    PMU_LDO_VRF,
    PMU_VDIG18,
    PMU_VRTC,
} pmu_power_domain_t;
#endif
typedef enum{
        RG_ICC_JC_20    = 0,
        RG_ICC_JC_40    = 4,
        RG_ICC_JC_60    = 5,
        RG_ICC_JC_80    = 6,
        RG_ICC_JC_100   = 7,
}pmu_jc_perecnt_level_t;
#ifdef AIR_BTA_IC_PREMIUM_G2
typedef enum
{
    RG_VCV_VOLTAGE_4P05V = 0,   //4.05V
    RG_VCV_VOLTAGE_4P10V = 1,   //4.10V
    RG_VCV_VOLTAGE_4P15V = 2,   //4.15V
    RG_VCV_VOLTAGE_4P20V = 3,   //4.20V
    RG_VCV_VOLTAGE_4P25V = 4,   //4.25V
    RG_VCV_VOLTAGE_4P30V = 5,   //4.30V
    RG_VCV_VOLTAGE_4P35V = 6,   //4.35V
    RG_VCV_VOLTAGE_4P40V = 7,   //4.40V
    RG_VCV_VOLTAGE_4P45V = 8,   //4.45V
    RG_VCV_VOLTAGE_4P50V = 9,   //4.50V
    RG_VCV_VOLTAGE_4P55V = 10,  //4.55V
    RG_VCV_VOLTAGE_4P60V = 11,  //4.60V
}pmu_cv_voltage_t;
#elif defined AIR_BTA_IC_PREMIUM_G3
typedef enum
{
    RG_VCV_VOLTAGE_4P05V  = 0,    //4.05V
    RG_VCV_VOLTAGE_4P075V = 1,    //4.05V
    RG_VCV_VOLTAGE_4P10V  = 2,    //4.10V
    RG_VCV_VOLTAGE_4P125V = 3,    //4.10V
    RG_VCV_VOLTAGE_4P15V  = 4,    //4.15V
    RG_VCV_VOLTAGE_4P175V = 5,    //4.15V
    RG_VCV_VOLTAGE_4P20V  = 6,    //4.20V
    RG_VCV_VOLTAGE_4P225V = 7,    //4.20V
    RG_VCV_VOLTAGE_4P25V  = 8,    //4.25V
    RG_VCV_VOLTAGE_4P725V = 9,    //4.20V
    RG_VCV_VOLTAGE_4P30V  = 10,   //4.30V
    RG_VCV_VOLTAGE_4P325V = 11,   //4.20V
    RG_VCV_VOLTAGE_4P35V  = 12,   //4.35V
    RG_VCV_VOLTAGE_4P375V = 13,   //4.20V
    RG_VCV_VOLTAGE_4P40V  = 14,   //4.40V
    RG_VCV_VOLTAGE_4P425V = 15,   //4.20V
    RG_VCV_VOLTAGE_4P45V  = 16,   //4.45V
    RG_VCV_VOLTAGE_4P475V = 17,   //4.20V
    RG_VCV_VOLTAGE_4P50V  = 19,   //4.50V
    RG_VCV_VOLTAGE_4P525V = 20,   //4.20V
    RG_VCV_VOLTAGE_4P55V  = 21,   //4.55V
    RG_VCV_VOLTAGE_4P575V = 22,   //4.20V
    RG_VCV_VOLTAGE_4P60V  = 23,   //4.60V
}pmu_cv_voltage_t;
#endif
#ifdef AIR_BTA_IC_PREMIUM_G2
typedef enum {
    ICL_ITH_10mA = 0,     //  10   mA
    ICL_ITH_90mA = 1,     //  90   mA
    ICL_ITH_200mA = 2,    //  200  mA
    ICL_ITH_300mA = 3,    //  300  mA
    ICL_ITH_400mA = 4,    //  400  mA
    ICL_ITH_500mA = 5,    //  500  mA
    ICL_ITH_600mA = 6,    //  600  mA
    ICL_ITH_700mA = 7,    //  700  mA
    ICL_ITH_800mA = 8,    //  800  mA
    ICL_ITH_900mA = 9,    //  900  mA
    ICL_ITH_1000mA = 10,  //  1000 mA
} pmu_icl_level_t;
#elif defined AIR_BTA_IC_PREMIUM_G3
typedef enum {
    ICL_ITH_10mA = 0,     //  10   mA
    ICL_ITH_75mA = 1,     //  75   mA
    ICL_ITH_200mA = 2,    //  200  mA
    ICL_ITH_300mA = 3,    //  300  mA
    ICL_ITH_443mA = 4,    //  400  mA
    ICL_ITH_500mA = 5,    //  500  mA
    ICL_ITH_600mA = 6,    //  600  mA
    ICL_ITH_700mA = 7,    //  700  mA
    ICL_ITH_800mA = 8,    //  800  mA
    ICL_ITH_900mA = 9,    //  900  mA
    ICL_ITH_1000mA = 10,  //  1000 mA
} pmu_icl_level_t;
#endif
#ifdef AIR_BTA_IC_PREMIUM_G2
typedef enum {
    RG_INT_PWRKEY,      //INT_CON0 index :0
    RG_INT_PWRKEY_R,
    RG_INT_VLDO33_LBAT_DET,
    RG_INT_VBAT_RECHG,
    RG_INT_JEITA_HOT,
    RG_INT_JEITA_WARM,
    RG_INT_JEITA_COOL,
    RG_INT_JEITA_COLD,
    RG_INT_BATOV,
    RG_INT_CHRDET,
    RG_INT_ChgStatInt,
    RG_INT_VBUS_OVP,
    RG_INT_VBUS_UVLO,
    RG_INT_ICHR_ITERM,
    RG_INT_ICHR_CHG_CUR,
    RG_INT_SAFETY_TIMEOUT,
    RG_INT_AD_LBAT_LV,     //INT_CON1 index :16
    RG_INT_THM_OVER40,
    RG_INT_THM_OVER55,
    RG_INT_THM_OVER110,
    RG_INT_THM_OVER125,
    RG_INT_THM_UNDER40,
    RG_INT_THM_UNDER55,
    RG_INT_THM_UNDER110,
    RG_INT_THM_UNDER125,
    RG_INT_BAT2_H_R,
    RG_INT_bat_h_lv,
    RG_INT_bat_l_lv,
    RG_INT_thr_h_r,
    RG_INT_thr_h_f,
    RG_INT_thr_l_r,
    RG_INT_thr_l_f,
    RG_INT_VCORE_OC,     //INT_CON2 index :32
    RG_INT_VIO18_OC,
    RG_INT_VRF_OC,
    RG_INT_VAUD18_OC,
    RG_INT_VLDO33_OC,
    RG_INT_VA18_OC,
    RG_INT_VRF11_OC,
    RG_INT_VSRAM_OC,
    RG_INT_ILimInt,        //INT_CON3 index :40
    RG_INT_ThermRegInt,
    RG_INT_AVDD50_OC,
    RG_INT_VSYS_DPM,
    PMU_INT_MAX,
} pmu_interrupt_index_t;
#elif defined AIR_BTA_IC_PREMIUM_G3
typedef enum {
    RG_INT_PWRKEY,      //INT_CON0 index :0
    RG_INT_PWRKEY_R,
    RG_INT_EN_AVDD50_OC,
    RG_INT_VBAT_RECHG,
    RG_INT_JEITA_HOT,
    RG_INT_JEITA_WARM,
    RG_INT_JEITA_COOL,
    RG_INT_JEITA_COLD,
    RG_INT_BATOV,
    RG_INT_CHRDET,
    RG_INT_ChgStatInt,
    RG_INT_VBUS_OVP,
    RG_INT_VBUS_UVLO,
    RG_INT_ICHR_ITERM,
    RG_INT_ICHR_CHG_CUR,
    RG_INT_SAFETY_TIMEOUT,
    RG_INT_AD_LBAT_LV,     //INT_CON1 index :16
    RG_INT_THM_OVER40,
    RG_INT_THM_OVER55,
    RG_INT_THM_OVER110,
    RG_INT_THM_OVER125,
    RG_INT_THM_UNDER40,
    RG_INT_THM_UNDER55,
    RG_INT_THM_UNDER110,
    RG_INT_THM_UNDER125,
    RG_INT_ILimInt,
    RG_INT_ThermRegInt,
    RG_INT_VSYS_DPM,
    RG_INT_JEITA_TO_NORMAL,
    PMU_INT_MAX,
} pmu_interrupt_index_t;
#endif

#ifdef AIR_BTA_PMIC_G2_LP
typedef enum {
    RG_INT_PWRKEY_FALL,                    //PMU_CON3,     index :0
    RG_INT_PWRKEY_RISE,                    //PMU_CON3,     index :2
    RG_INT_CHG_IN,                         //CHARGER_CON1, index :0
    RG_INT_CHG_OUT,                        //CHARGER_CON1, index :2
    RG_INT_CHG_COMPL,                      //CHARGER_CON1, index :4
    RG_INT_CHG_RECHG,                      //CHARGER_CON1, index :6
    RG_INT_ADC_SW_TRIG,                    //ADC_CON3,     index :1
    RG_INT_ADC_HW_TRIG,                    //ADC_CON3,     index :3
    PMU_INT_MAX_LP,
} pmu_interrupt_index_lp_t;
#elif defined AIR_BTA_PMIC_LP
typedef enum {
    RG_ADC_SW_TRIG_FLAG,
    RG_ADC_HW_TRIG_FLAG,
    RG_CHG_IN_INT_FLAG,
    RG_CHG_OUT_INT_FLAG,
    RG_CHG_PRE_COMPLETE_INT_FLAG,
    RG_CHG_COMPLETE_INT_FLAG,
    RG_CHG_RECHG_INT_FLAG,
    RG_REGEN_IRQ_RISE_FLAG,
    RG_REGEN_IRQ_FALL_FLAG,
    PMU_INT_MAX_LP,
} pmu_interrupt_index_lp_t;
#endif
enum
{
    PMU_NOT_INIT,
    PMU_INIT,
};

typedef void (*pmu_callback_t)(void);

typedef struct
{
    void (*pmu_callback)(void);
    void *user_data;
    bool init_status;
	bool isMask;
} pmu_function_t;

typedef struct
{
    pmu_callback_t callback1; //press callback
    void *user_data1;
    pmu_callback_t callback2; //release callback
    void *user_data2;
} pmu_pwrkey_config_t;

typedef enum {
    option_setting=0,
    option2_init=1,
    option2_recharger = 2,
    option2_exit = 3,
    option3_init = 4,
    option3_checking = 5,
    option3_recharger = 6,
    option3_exit = 7,
    option4_init = 8,
    option4_exit = 9,
} pmu_eoc_operating_t;

typedef enum {
    pmu_eoc_option1=1,
    pmu_eoc_option2=2,
    pmu_eoc_option3=3,
    pmu_eoc_option4=4,
} pmu_eoc_option_t;

typedef enum {
    pmu_fastcc_chrcur_0p5mA=0,
    pmu_fastcc_chrcur_1mA,
    pmu_fastcc_chrcur_1p5mA,
    pmu_fastcc_chrcur_2mA,
    pmu_fastcc_chrcur_2p5mA,
    pmu_fastcc_chrcur_3mA,
    pmu_fastcc_chrcur_3p5mA,
    pmu_fastcc_chrcur_4mA,
    pmu_fastcc_chrcur_4p5mA,
    pmu_fastcc_chrcur_5mA,
    pmu_fastcc_chrcur_10mA,
    pmu_fastcc_chrcur_15mA,
    pmu_fastcc_chrcur_20mA,
    pmu_fastcc_chrcur_25mA,
    pmu_fastcc_chrcur_30mA,
    pmu_fastcc_chrcur_35mA,
    pmu_fastcc_chrcur_40mA,
    pmu_fastcc_chrcur_45mA,
    pmu_fastcc_chrcur_50mA,
    pmu_fastcc_chrcur_55mA,
    pmu_fastcc_chrcur_60mA,
    pmu_fastcc_chrcur_65mA,
    pmu_fastcc_chrcur_70mA,
    pmu_fastcc_chrcur_75mA,
    pmu_fastcc_chrcur_80mA,
    pmu_fastcc_chrcur_90mA,
    pmu_fastcc_chrcur_100mA,
    pmu_fastcc_chrcur_110mA,
    pmu_fastcc_chrcur_120mA,
    pmu_fastcc_chrcur_130mA,
    pmu_fastcc_chrcur_140mA,
    pmu_fastcc_chrcur_150mA,
    pmu_fastcc_chrcur_160mA,
    pmu_fastcc_chrcur_170mA,
    pmu_fastcc_chrcur_180mA,
    pmu_fastcc_chrcur_190mA,
    pmu_fastcc_chrcur_200mA,
    pmu_fastcc_chrcur_210mA,
    pmu_fastcc_chrcur_220mA,
    pmu_fastcc_chrcur_230mA,
    pmu_fastcc_chrcur_240mA,
    pmu_fastcc_chrcur_250mA,
    pmu_fastcc_chrcur_260mA,
    pmu_fastcc_chrcur_270mA,
    pmu_fastcc_chrcur_280mA,
    pmu_fastcc_chrcur_290mA,
    pmu_fastcc_chrcur_300mA,
    pmu_fastcc_chrcur_310mA,
    pmu_fastcc_chrcur_320mA,
    pmu_fastcc_chrcur_330mA,
    pmu_fastcc_chrcur_340mA,
    pmu_fastcc_chrcur_350mA,
    pmu_fastcc_chrcur_360mA,
    pmu_fastcc_chrcur_370mA,
    pmu_fastcc_chrcur_380mA,
    pmu_fastcc_chrcur_390mA,
    pmu_fastcc_chrcur_400mA,
    pmu_fastcc_chrcur_410mA,
    pmu_fastcc_chrcur_420mA,
    pmu_fastcc_chrcur_430mA,
    pmu_fastcc_chrcur_440mA,
    pmu_fastcc_chrcur_450mA,
    pmu_fastcc_chrcur_460mA,
    pmu_fastcc_chrcur_470mA,
    pmu_fastcc_chrcur_480mA,
    pmu_fastcc_chrcur_490mA,
    pmu_fastcc_chrcur_500mA,
} pmu_fastcc_chrcur_t;

typedef enum {
    pmu_iterm_chrcur_0p5mA=0,
    pmu_iterm_chrcur_1mA,
    pmu_iterm_chrcur_1p5mA,
    pmu_iterm_chrcur_2mA,
    pmu_iterm_chrcur_2p5mA,
    pmu_iterm_chrcur_3mA,
    pmu_iterm_chrcur_3p5mA,
    pmu_iterm_chrcur_4mA,
    pmu_iterm_chrcur_4p5mA,
    pmu_iterm_chrcur_5mA,
    pmu_iterm_chrcur_5p5mA,
    pmu_iterm_chrcur_6mA,
    pmu_iterm_chrcur_6p5mA,
    pmu_iterm_chrcur_7mA,
    pmu_iterm_chrcur_7p5mA,
    pmu_iterm_chrcur_8mA,
    pmu_iterm_chrcur_9mA,
    pmu_iterm_chrcur_10mA,
    pmu_iterm_chrcur_11mA,
    pmu_iterm_chrcur_12mA,
    pmu_iterm_chrcur_13mA,
    pmu_iterm_chrcur_14mA,
    pmu_iterm_chrcur_15mA,
    pmu_iterm_chrcur_16mA,
    pmu_iterm_chrcur_17mA,
    pmu_iterm_chrcur_18mA,
    pmu_iterm_chrcur_19mA,
    pmu_iterm_chrcur_20mA,
    pmu_iterm_chrcur_21mA,
    pmu_iterm_chrcur_22mA,
    pmu_iterm_chrcur_23mA,
    pmu_iterm_chrcur_24mA,
    pmu_iterm_chrcur_25mA,
    pmu_iterm_chrcur_26mA,
    pmu_iterm_chrcur_27mA,
    pmu_iterm_chrcur_28mA,
    pmu_iterm_chrcur_29mA,
    pmu_iterm_chrcur_30mA,
    pmu_iterm_chrcur_31mA,
    pmu_iterm_chrcur_32mA,
    pmu_iterm_chrcur_34mA,
    pmu_iterm_chrcur_36mA,
    pmu_iterm_chrcur_38mA,
    pmu_iterm_chrcur_40mA,
    pmu_iterm_chrcur_42mA,
    pmu_iterm_chrcur_44mA,
    pmu_iterm_chrcur_46mA,
    pmu_iterm_chrcur_48mA,
    pmu_iterm_chrcur_50mA,
    pmu_iterm_chrcur_60mA,
    pmu_iterm_chrcur_62mA,
    pmu_iterm_chrcur_64mA,
} pmu_iterm_chrcur_t;

enum {
    SDP_CHARGER = 1,
    CDP_CHARGER,
    DCP_CHARGER,
    SS_TABLET_CHARGER,
    IPAD2_IPAD4_CHARGER,
    IPHONE_5V_1A_CHARGER,
    NON_STD_CHARGER,
    DP_DM_FLOATING,
    UNABLE_TO_IDENTIFY_CHARGER,
    INVALID_CHARGER = 0xFF,
};

/* Because of restrictions on HW
 * Charging current through matching combination on the battery pack
 * But due to the digital design of HW, list all charging current
*/

/* Dynamic Debug Print Flags */
typedef union {
    struct {
        uint8_t vcore    :1;
        uint8_t other    :1;
        uint8_t reserved :6;
    } b;
    uint8_t val;
} pmu_dynamic_debug_t;

extern pmu_dynamic_debug_t pmu_dynamic_debug;

/*==========[Basic function]==========*/
void pmu_init(void);
void pmu_config(void);
void pmu_select_vsram_vosel(pmu_power_stage_t mode , pmu_vsram_voltage_t val);
void pmu_latch_power_key_for_bootloader(void);
uint8_t pmu_get_pmic_version(void);
pmu_power_vcore_voltage_t pmu_lock_vcore(pmu_power_stage_t mode,pmu_power_vcore_voltage_t vol,pmu_lock_parameter_t lock);
pmu_operate_status_t pmu_set_register_value(uint32_t address, uint32_t mask, uint32_t shift, uint32_t value);
uint32_t pmu_get_register_value(uint32_t address, uint32_t mask, uint32_t shift);
pmu_operate_status_t pmu_force_set_register_value(uint32_t address, uint32_t value);
bool pmu_get_chr_detect_value(void);
void pmu_set_cap_wo_vbus(pmu_power_operate_t oper);
void pmu_enable_sw_lp_mode(pmu_power_domain_t domain, pmu_control_mode_t mode);
void pmu_switch_control_mode(pmu_power_domain_t domain, pmu_control_mode_t mode);
void pmu_lock_va18(int oper);
void pmu_charger_check_faston(void);
void pmu_enable_ocp(pmu_power_operate_t oper);
void pmu_enable_lpsd(pmu_lpsd_time_t tmr, pmu_power_operate_t oper);
void pmu_enable_micbias(pmu_micbias_ldo_t ldo, pmu_micbias_index_t index, pmu_micbias_mode_t mode,pmu_power_operate_t operate);
pmu_operate_status_t pmu_set_micbias_vout(pmu_micbias_index_t index,pmu_3vvref_voltage_t vol);
pmu_operate_status_t pmu_pwrkey_enable(pmu_power_operate_t oper);
#ifndef AIR_BTA_IC_PREMIUM_G3_TYPE_D
#ifdef AIR_BTA_IC_PREMIUM_G3
uint32_t pmu_auxadc_get_channel_value(pmu_adc_channel_t Channel);
#endif
#endif
void pmu_select_wdt_mode(pmu_wdtrstb_act_t sel);
void pmu_dump_otp(void);
void pmu_dump_nvkey(void);
void pmu_dump_rg(void);
/*-------------------------------------------[D-die PMU]----------------------------------------------------*/
#ifdef AIR_BTA_IC_PREMIUM_G3
pmu_operate_status_t pmu_set_register_value_ddie(uint32_t address, uint32_t mask, uint32_t shift, uint32_t value);
uint32_t pmu_get_register_value_ddie(uint32_t address, uint32_t mask, uint32_t shift);
uint8_t pmu_enable_usb_power(pmu_power_operate_t oper);
#endif
/*==========[BUCK/LDO]==========*/
void pmu_enable_power(pmu_power_domain_t pmu_pdm, pmu_power_operate_t operate);
uint8_t pmu_get_power_status(pmu_power_domain_t pmu_pdm);
void pmu_set_vsram_voltage(pmu_vsram_voltage_t val);
pmu_power_vcore_voltage_t pmu_get_vcore_voltage(void);
pmu_operate_status_t pmu_select_vsram_voltage(pmu_power_stage_t mode, pmu_power_vsram_voltage_t vol);
pmu_operate_status_t pmu_select_vcore_voltage(pmu_power_stage_t mode, pmu_power_vcore_voltage_t vol);
void pmu_set_audio_enhance(pmu_power_operate_t oper);
pmu_operate_status_t pmu_set_vaud18_vout(pmu_vaud18_voltage_t lv, pmu_vaud18_voltage_t mv, pmu_vaud18_voltage_t hv);
void pmu_set_vpa_voltage(pmu_power_vpa_voltage_t oper);
void pmu_get_lock_status(int sta);
bool pmu_get_pwrkey_state(void);
void pmu_enable_captouch(pmu_power_operate_t oper);
void pmu_power_off_sequence(pmu_power_stage_t stage);
uint8_t pmu_get_power_on_reason(void);
uint8_t pmu_get_power_off_reason(void);
void pmu_set_rstpat(pmu_power_operate_t oper, pmu_rstpat_src_t src);
pmu_operate_status_t pmu_pwrkey_normal_key_init(pmu_pwrkey_config_t *config);
void pmu_set_vaud18_voltage(pmu_power_vaud18_voltage_t oper);
/*==========[Charger]==========*/
void pmu_charger_init(uint16_t precc_cur,uint16_t cv_termination);
uint8_t pmu_enable_charger(uint8_t isEnableCharging);
bool pmu_set_icl_curent_level(uint8_t currentLevel);
#ifdef AIR_BTA_IC_PREMIUM_G2
uint8_t pmu_get_bc12_charger_type(void);
#endif
void pmu_set_charger_current_limit(uint8_t port);
void pmu_select_eco_option_operating(pmu_eoc_option_t opt,pmu_eoc_operating_t oper);
uint32_t pmu_get_charger_state(void);
void pmu_select_eoc_option_operating(pmu_eoc_option_t opt, pmu_eoc_operating_t oper);
void pmu_set_icl_by_type(uint8_t port);
bool pmu_set_extend_charger_time(uint8_t timeMins);
void pmu_enable_recharger(bool isEnableCharging);
bool pmu_set_rechg_voltage(uint8_t isEnableRecharge);
void pmu_set_pre_charger_current(pmu_fastcc_chrcur_t cur);
void pmu_set_audio_mode(pmu_audio_mode_t mode,pmu_power_operate_t operate);
void pmu_set_charger_current(pmu_fastcc_chrcur_t cur);
void pmu_set_iterm_current_irq(pmu_iterm_chrcur_t cur);
void pmu_set_iterm_current(pmu_iterm_chrcur_t cur);
bool pmu_select_cv_voltage(uint8_t voltage);
bool pmu_select_cc_safety_timer(uint8_t timeMHrs);
uint32_t pmu_disable_vsys_discharge(uint8_t value);
uint8_t pmu_get_usb_input_status(void);
bool pmu_select_precc_voltage(uint8_t voltage);
/*==========[HW-JEITA/NTC]==========*/
void pmu_hw_jeita_init(void);
uint8_t pmu_get_hw_jeita_status(void);
pmu_operate_status_t pmu_set_jeita_voltage(uint32_t auxadcVolt, uint8_t JeitaThreshold);
void pmu_jeita_state_setting(uint8_t state,pmu_jc_perecnt_level_t ICC_JC,pmu_cv_voltage_t vol);
void pmu_set_jeita_state_setting(uint8_t state,pmu_jeita_perecnt_level_t ICC_JC,pmu_cv_voltage_t vol);
void pmu_thermal_parameter_init(void);
int32_t pmu_auxadc_get_pmic_temperature(void);
bool pmu_set_hw_jeita_enable(uint8_t value);
#endif /* HAL_PMU_MODULE_ENABLED */
#endif
