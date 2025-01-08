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

#ifndef _DRV_SMART_CHARGER_H_
#define _DRV_SMART_CHARGER_H_

//#include "types.h"
#include "hal_platform.h"
#include "smartchargertypes.h"
#include "types.h"

////////////////////////////////////////////////////////////////////////////////
// Type Definitions ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef enum {
    HAL_SMART_CHARGER_STATUS_INVALID_PARAMETER = -2,  /**<  An invalid parameter was given. */
    HAL_SMART_CHARGER_STATUS_ERROR             = -1,  /**<  The function call failed. */
    HAL_SMART_CHARGER_STATUS_OK                =  0   /**<  The function call was successful. */
} hal_smart_charger_status_t;


////////////////////////////////////////////////////////////////////////////////
// Global Variables ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define SMCHG_LID_OPEN              1
#define SMCHG_LID_CLOSE_DONE        2
#define SMCHG_CHG_OFF               3
#define SMCHG_CHG_OUT               4
#define SMCHG_CHG_COMPL             11
#define SMCHG_CHG_RECHG             12
#define SMCHG_CHG_KEY               13
#define SMCHG_LID_CLOSE             14
#define SMCHG_USER_DATA             15
#define SMCHG_USER_DATA_3           16
#define SMCHG_CHG_IN                17
#ifdef ARC_1WIRE_ENABLE
#else
#define SMCHG_BATTERY_GET           20
#define SMCHG_BDADDR_GET            21
#define SMCHG_DONGLE_PARING         22
#endif /* ARC_1WIRE_ENABLE */

#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
#define NXP_GET_SYSTEM_INFO         23
#define NXP_GET_TX1_DEVICE_PARAM    24
#define NXP_GET_TX2_DEVICE_PARAM    25
#define NXP_GET_RX_DEVICE_PARAM     26
#define NXP_GET_DEVICE_INFO         27
#define NXP_SET_TX1_DEVICE_PARAM    28
#define NXP_SET_TX2_DEVICE_PARAM    29
#define NXP_SET_RX_DEVICE_PARAM     30
#define NXP_SET_SYSTEM_INFO         31
#endif /* ARC_NXP_COM_ENABLE */

#ifdef ARC_PRODUCTION_TEST
#else /* !ARC_PRODUCTION_TEST */
#define SMCHG_PT_CMD_SET_MODE       41

#define SMCHG_PT_CMD_RESET          42
#endif /* ARC_PRODUCTION_TEST */

#ifdef ARC_1WIRE_ENABLE
#else /* !ARC_1WIRE_ENABLE */
#define PKT_OFFS_CHANNEL                 0
#define PKT_OFFS_TYPE                    1
#define PKT_OFFS_LENGTH_L                2
#define PKT_OFFS_LENGTH_H                3
#define PKT_OFFS_PROTOCOL_ID_L           4
#define PKT_OFFS_PROTOCOL_ID_H           5
#define PKT_OFFS_FLAGS                   6
#define PKT_OFFS_CMD                     7
#define PKT_OFFS_DEVICE_TYPE             8
#define PKT_OFFS_DATA                    9

/* ---------------------------------- Lid Open ---------------------------------- */
#define CMD_LID_OPEN                                               (0x2)
#define CMD_LID_OPEN_DATA_LENGTH                                   (0x6)
#define CMD_LID_OPEN_DATA_CASE_BATTERY_OFFSET                      (PKT_OFFS_DATA)
#define CMD_LID_OPEN_DATA_CRC_OFFSET                               (PKT_OFFS_DATA + 1)
#define CMD_LID_OPEN_RSP_DATA_LENGTH                               (0x2)
#define CMD_LID_OPEN_RSP_DATA_EARBUD_BATTERY_OFFSET                (PKT_OFFS_DATA)
#define CMD_LID_OPEN_RSP_DATA_CRC_OFFSET                           (PKT_OFFS_DATA + 1)

/* ---------------------------------- Lid Close ---------------------------------- */
#define CMD_LID_CLOSE                                              (0x3)
#define CMD_LID_CLOSE_DATA_LENGTH                                  (0x2)
#define CMD_LID_CLOSE_DATA_CASE_BATTERY_OFFSET                     (PKT_OFFS_DATA)
#define CMD_LID_CLOSE_DATA_CRC_OFFSET                              (PKT_OFFS_DATA + 1)
#define CMD_LID_CLOSE_RSP_DATA_LENGTH                              (0x2)
#define CMD_LID_CLOSE_RSP_DATA_EARBUD_BATTERY_OFFSET               (PKT_OFFS_DATA)
#define CMD_LID_CLOSE_RSP_DATA_CRC_OFFSET                          (PKT_OFFS_DATA + 1)

/* ---------------------------------- Charger Off ---------------------------------- */
#define CMD_CHARGER_OFF                                            (0x4)
#define CMD_CHARGER_OFF_DATA_LENGTH                                (0x3)
#define CMD_CHARGER_OFF_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA)
#define CMD_CHARGER_OFF_DATA_REASON_OFFSET                         (PKT_OFFS_DATA + 1)
#define CMD_CHARGER_OFF_DATA_CRC                                   (PKT_OFFS_DATA + 2)
#define CMD_CHARGER_OFF_RSP_DATA_LENGTH                            (0x2)
#define CMD_CHARGER_OFF_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA)
#define CMD_CHARGER_OFF_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 1)

/* ---------------------------------- Battery Get ---------------------------------- */
#define CMD_BATTERY_GET                                            (0x6)
#define CMD_BATTERY_GET_DATA_LENGTH                                (0x3)
#define CMD_BATTERY_GET_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA)
#define CMD_BATTERY_GET_DATA_CASE_STATE_OFFSET                     (PKT_OFFS_DATA + 1)
#define CMD_BATTERY_GET_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 2)
#define CMD_BATTERY_GET_RSP_DATA_LENGTH                            (0x2)
#define CMD_BATTERY_GET_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA)
#define CMD_BATTERY_GET_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 1)


/* ------------------------------ Case Update Fw Size ------------------------------ */
#define CMD_FW_SIZE_GET                                            (0x13)
#define CMD_FW_SIZE_GET_DATA_LENGTH                                (0x2)
#define CMD_FW_SIZE_GET_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA)
#define CMD_FW_SIZE_GET_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 1)
#define CMD_FW_SIZE_GET_RSP_DATA_LENGTH                            (0x4)
#define CMD_FW_SIZE_GET_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA)
#define CMD_FW_SIZE_GET_RSP_DATA_LEN_L_OFFSET                      (PKT_OFFS_DATA + 1)
#define CMD_FW_SIZE_GET_RSP_DATA_LEN_H_OFFSET                      (PKT_OFFS_DATA + 2)
#define CMD_FW_SIZE_GET_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 3)

/* ---------------------------- Case Update Fw Data Get ---------------------------- */
#define CMD_FW_DATA_GET                                            (0x14)
#define CMD_FW_DATA_GET_DATA_LENGTH                                (0x6)
#define CMD_FW_DATA_GET_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA)
#define CMD_FW_DATA_GET_DATA_OFFSET_L_OFFSET                       (PKT_OFFS_DATA + 1)
#define CMD_FW_DATA_GET_DATA_OFFSET_H_OFFSET                       (PKT_OFFS_DATA + 2)
#define CMD_FW_DATA_GET_DATA_LEN_L_OFFSET                          (PKT_OFFS_DATA + 3)
#define CMD_FW_DATA_GET_DATA_LEN_H_OFFSET                          (PKT_OFFS_DATA + 4)
#define CMD_FW_DATA_GET_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 5)
//#define CMD_FW_DATA_GET_RSP_DATA_LENGTH                          Not fixed
#define CMD_FW_DATA_GET_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA)
#define CMD_FW_DATA_GET_RSP_DATA_OFFSET                            (PKT_OFFS_DATA + 1)
//#define CMD_FW_DATA_GET_RSP_DATA_CRC_OFFSET                      Not fixed

/* ------------------------------- Case Update Fw Crc ------------------------------- */
#define CMD_FW_CRC_GET                                             (0x15)
#define CMD_FW_CRC_GET_DATA_LENGTH                                 (0x2)
#define CMD_FW_CRC_GET_DATA_CASE_BATTERY_OFFSET                    (PKT_OFFS_DATA)
#define CMD_FW_CRC_GET_DATA_CRC_OFFSET                             (PKT_OFFS_DATA + 1)
#define CMD_FW_CRC_GET_RSP_DATA_LENGTH                             (0x4)
#define CMD_FW_CRC_GET_RSP_DATA_EARBUD_BATTERY_OFFSET              (PKT_OFFS_DATA)
#define CMD_FW_CRC_GET_RSP_DATA_CRC_L_OFFSET                       (PKT_OFFS_DATA + 1)
#define CMD_FW_CRC_GET_RSP_DATA_CRC_H_OFFSET                       (PKT_OFFS_DATA + 2)
#define CMD_FW_CRC_GET_RSP_DATA_CRC_OFFSET                         (PKT_OFFS_DATA + 3)

/* ----------------------------- Case Update Fw Version ----------------------------- */
#define CMD_FW_VER                                                 (0x16)
#define CMD_FW_VER_DATA_LENGTH                                     (0x5)
#define CMD_FW_VER_DATA_CASE_BATTERY_OFFSET                        (PKT_OFFS_DATA)
#define CMD_FW_VER_DATA_BOOTLOADER_VERSION_OFFSET                  (PKT_OFFS_DATA + 1)
#define CMD_FW_VER_DATA_APPLICATION_VERSION_OFFSET                 (PKT_OFFS_DATA + 2)
#define CMD_FW_VER_DATA_HW_VERSION_OFFSET                          (PKT_OFFS_DATA + 3)
#define CMD_FW_VER_DATA_CRC_OFFSET                                 (PKT_OFFS_DATA + 4)
#define CMD_FW_VER_RSP_DATA_LENGTH                                 (0x5)
#define CMD_FW_VER_RSP_DATA_EARBUD_BATTERY_OFFSET                  (PKT_OFFS_DATA)
#define CMD_FW_VER_RSP_DATA_BOOTLOADER_VERSION_OFFSET              (PKT_OFFS_DATA + 1)
#define CMD_FW_VER_RSP_DATA_APPLICATION_VERSION_OFFSET             (PKT_OFFS_DATA + 2)
#define CMD_FW_VER_RSP_DATA_HW_VERSION_OFFSET                      (PKT_OFFS_DATA + 3)
#define CMD_FW_VER_RSP_DATA_CRC_OFFSET                             (PKT_OFFS_DATA + 4)


/* ------------------------------- Bd_Addr Get ------------------------------- */
#define CMD_BD_ADDR_GET                                            (0x17)
#define CMD_BD_ADDR_GET_DATA_LENGTH                                (2)
#define CMD_BD_ADDR_GET_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA + 0)
#define CMD_BD_ADDR_GET_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 1)
#define CMD_BD_ADDR_GET_RSP_DATA_LENGTH                            (8)
#define CMD_BD_ADDR_GET_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA + 0)
#define CMD_BD_ADDR_GET_RSP_DATA_ADDR_0_OFFSET                     (PKT_OFFS_DATA + 1)
#define CMD_BD_ADDR_GET_RSP_DATA_ADDR_1_OFFSET                     (PKT_OFFS_DATA + 2)
#define CMD_BD_ADDR_GET_RSP_DATA_ADDR_2_OFFSET                     (PKT_OFFS_DATA + 3)
#define CMD_BD_ADDR_GET_RSP_DATA_ADDR_3_OFFSET                     (PKT_OFFS_DATA + 4)
#define CMD_BD_ADDR_GET_RSP_DATA_ADDR_4_OFFSET                     (PKT_OFFS_DATA + 5)
#define CMD_BD_ADDR_GET_RSP_DATA_ADDR_5_OFFSET                     (PKT_OFFS_DATA + 6)
#define CMD_BD_ADDR_GET_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 7)

/* ------------------------------- Old_Key Get ------------------------------- */
#define CMD_OLD_KEY_GET                                            (0x18)
#define CMD_OLD_KEY_GET_DATA_LENGTH                                (8)
#define CMD_OLD_KEY_GET_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA + 0)
#define CMD_OLD_KEY_GET_DATA_ADDR_0_OFFSET                         (PKT_OFFS_DATA + 1)
#define CMD_OLD_KEY_GET_DATA_ADDR_1_OFFSET                         (PKT_OFFS_DATA + 2)
#define CMD_OLD_KEY_GET_DATA_ADDR_2_OFFSET                         (PKT_OFFS_DATA + 3)
#define CMD_OLD_KEY_GET_DATA_ADDR_3_OFFSET                         (PKT_OFFS_DATA + 4)
#define CMD_OLD_KEY_GET_DATA_ADDR_4_OFFSET                         (PKT_OFFS_DATA + 5)
#define CMD_OLD_KEY_GET_DATA_ADDR_5_OFFSET                         (PKT_OFFS_DATA + 6)
#define CMD_OLD_KEY_GET_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 7)
#define CMD_OLD_KEY_GET_RSP_DATA_LENGTH                            (18)
#define CMD_OLD_KEY_GET_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA + 0)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_0_OFFSET                      (PKT_OFFS_DATA + 1)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_1_OFFSET                      (PKT_OFFS_DATA + 2)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_2_OFFSET                      (PKT_OFFS_DATA + 3)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_3_OFFSET                      (PKT_OFFS_DATA + 4)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_4_OFFSET                      (PKT_OFFS_DATA + 5)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_5_OFFSET                      (PKT_OFFS_DATA + 6)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_6_OFFSET                      (PKT_OFFS_DATA + 7)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_7_OFFSET                      (PKT_OFFS_DATA + 8)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_8_OFFSET                      (PKT_OFFS_DATA + 9)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_9_OFFSET                      (PKT_OFFS_DATA + 10)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_10_OFFSET                     (PKT_OFFS_DATA + 11)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_11_OFFSET                     (PKT_OFFS_DATA + 12)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_12_OFFSET                     (PKT_OFFS_DATA + 13)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_13_OFFSET                     (PKT_OFFS_DATA + 14)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_14_OFFSET                     (PKT_OFFS_DATA + 15)
#define CMD_OLD_KEY_GET_RSP_DATA_KEY_15_OFFSET                     (PKT_OFFS_DATA + 16)
#define CMD_OLD_KEY_GET_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 17)

/* --------------------------- New_Key Get(Rx Only) --------------------------- */
#define CMD_NEW_KEY_GET                                            (0x19)
#define CMD_NEW_KEY_GET_DATA_LENGTH                                (2)
#define CMD_NEW_KEY_GET_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA + 0)
#define CMD_NEW_KEY_GET_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 1)
#define CMD_NEW_KEY_GET_RSP_DATA_LENGTH                            (18)
#define CMD_NEW_KEY_GET_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA + 0)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_0_OFFSET                      (PKT_OFFS_DATA + 1)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_1_OFFSET                      (PKT_OFFS_DATA + 2)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_2_OFFSET                      (PKT_OFFS_DATA + 3)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_3_OFFSET                      (PKT_OFFS_DATA + 4)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_4_OFFSET                      (PKT_OFFS_DATA + 5)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_5_OFFSET                      (PKT_OFFS_DATA + 6)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_6_OFFSET                      (PKT_OFFS_DATA + 7)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_7_OFFSET                      (PKT_OFFS_DATA + 8)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_8_OFFSET                      (PKT_OFFS_DATA + 9)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_9_OFFSET                      (PKT_OFFS_DATA + 10)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_10_OFFSET                     (PKT_OFFS_DATA + 11)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_11_OFFSET                     (PKT_OFFS_DATA + 12)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_12_OFFSET                     (PKT_OFFS_DATA + 13)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_13_OFFSET                     (PKT_OFFS_DATA + 14)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_14_OFFSET                     (PKT_OFFS_DATA + 15)
#define CMD_NEW_KEY_GET_RSP_DATA_KEY_15_OFFSET                     (PKT_OFFS_DATA + 16)
#define CMD_NEW_KEY_GET_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 17)

/* ------------------------------- Pair Device ------------------------------- */
#define CMD_PAIR_DEVICE                                            (0x1A)
#define CMD_PAIR_DEVICE_DATA_LENGTH                                (24)
#define CMD_PAIR_DEVICE_DATA_CASE_BATTERY_OFFSET                   (PKT_OFFS_DATA + 0)
#define CMD_PAIR_DEVICE_DATA_ADDR_0_OFFSET                         (PKT_OFFS_DATA + 1)
#define CMD_PAIR_DEVICE_DATA_ADDR_1_OFFSET                         (PKT_OFFS_DATA + 2)
#define CMD_PAIR_DEVICE_DATA_ADDR_2_OFFSET                         (PKT_OFFS_DATA + 3)
#define CMD_PAIR_DEVICE_DATA_ADDR_3_OFFSET                         (PKT_OFFS_DATA + 4)
#define CMD_PAIR_DEVICE_DATA_ADDR_4_OFFSET                         (PKT_OFFS_DATA + 5)
#define CMD_PAIR_DEVICE_DATA_ADDR_5_OFFSET                         (PKT_OFFS_DATA + 6)
#define CMD_PAIR_DEVICE_DATA_KEY_0_OFFSET                          (PKT_OFFS_DATA + 7)
#define CMD_PAIR_DEVICE_DATA_KEY_1_OFFSET                          (PKT_OFFS_DATA + 8)
#define CMD_PAIR_DEVICE_DATA_KEY_2_OFFSET                          (PKT_OFFS_DATA + 9)
#define CMD_PAIR_DEVICE_DATA_KEY_3_OFFSET                          (PKT_OFFS_DATA + 10)
#define CMD_PAIR_DEVICE_DATA_KEY_4_OFFSET                          (PKT_OFFS_DATA + 11)
#define CMD_PAIR_DEVICE_DATA_KEY_5_OFFSET                          (PKT_OFFS_DATA + 12)
#define CMD_PAIR_DEVICE_DATA_KEY_6_OFFSET                          (PKT_OFFS_DATA + 13)
#define CMD_PAIR_DEVICE_DATA_KEY_7_OFFSET                          (PKT_OFFS_DATA + 14)
#define CMD_PAIR_DEVICE_DATA_KEY_8_OFFSET                          (PKT_OFFS_DATA + 15)
#define CMD_PAIR_DEVICE_DATA_KEY_9_OFFSET                          (PKT_OFFS_DATA + 16)
#define CMD_PAIR_DEVICE_DATA_KEY_10_OFFSET                         (PKT_OFFS_DATA + 17)
#define CMD_PAIR_DEVICE_DATA_KEY_11_OFFSET                         (PKT_OFFS_DATA + 18)
#define CMD_PAIR_DEVICE_DATA_KEY_12_OFFSET                         (PKT_OFFS_DATA + 19)
#define CMD_PAIR_DEVICE_DATA_KEY_13_OFFSET                         (PKT_OFFS_DATA + 20)
#define CMD_PAIR_DEVICE_DATA_KEY_14_OFFSET                         (PKT_OFFS_DATA + 21)
#define CMD_PAIR_DEVICE_DATA_KEY_15_OFFSET                         (PKT_OFFS_DATA + 22)
#define CMD_PAIR_DEVICE_DATA_CRC_OFFSET                            (PKT_OFFS_DATA + 23)
#define CMD_PAIR_DEVICE_RSP_DATA_LENGTH                            (0x2)
#define CMD_PAIR_DEVICE_RSP_DATA_EARBUD_BATTERY_OFFSET             (PKT_OFFS_DATA)
#define CMD_PAIR_DEVICE_RSP_DATA_CRC_OFFSET                        (PKT_OFFS_DATA + 1)

/* ---------------------------------- Reset ---------------------------------- */
#define CMD_RESET                                                  (0x1B)
#define CMD_RESET_DATA_LENGTH                                      (0x2)
#define CMD_RESET_DATA_CASE_BATTERY_OFFSET                         (PKT_OFFS_DATA)
#define CMD_RESET_DATA_CRC_OFFSET                                  (PKT_OFFS_DATA + 1)
#define CMD_RESET_RSP_DATA_LENGTH                                  (0x2)
#define CMD_RESET_RSP_DATA_EARBUD_BATTERY_OFFSET                   (PKT_OFFS_DATA)
#define CMD_RESET_RSP_DATA_CRC_OFFSET                              (PKT_OFFS_DATA + 1)

#define NXP_FR800x_TRANS_COMMAND                                               (0x0A)
#define NXP_FR800x_TRANS_COMMAND_DATA_LENGTH                                   (0x08)
#define NXP_FR800x_TRANS_COMMAND_DATA_OFFEST 

#endif /* ARC_1WIRE_ENABLE */

#ifdef ARC_NXP_COM_ENABLE
#else /* !ARC_NXP_COM_ENABLE */
#define GET_BITS(p, n, mask) (((p) >> (n)) & (mask))
#define SET_BITS(p, n, mask) ((p) |= ((mask) << (n)))
#define CLR_BITS(p, n, mask) ((p) &= (~((mask) << (n))))

#define GET_BIT(p, n) (((p) & (1 << (n))) ? TRUE : FALSE)
#define SET_BIT(p, n) ((p) |= (1 << (n)))
#define CLR_BIT(p, n) ((p) &= (~(1 << (n))))


#define NXP_PKT_OFFS_CHANNEL                 0
#define NXP_PKT_OFFS_TYPE                    1
#define NXP_PKT_OFFS_LENGTH_L                2
#define NXP_PKT_OFFS_LENGTH_H                3
#define NXP_PKT_OFFS_PROTOCOL_ID_L           4
#define NXP_PKT_OFFS_PROTOCOL_ID_H           5
#define NXP_PKT_OFFS_STATUS                  6
#define NXP_PKT_OFFS_CMD                     7
#define NXP_PKT_OFFS_DATA                    8


#define NXP_PKT_OFFS_PKT_MAX_LEN            21      // MCU issue: Must set to fixed len.

#define NXP_TX_DEVICE_STATUS_HAS_CHARGER_BIT              7
#define NXP_TX_DEVICE_STATUS_IS_CHARGING_OVER_BIT         6
#define NXP_TX_DEVICE_STATUS_IS_POWER_ON_BIT              5
#define NXP_TX_DEVICE_STATUS_DSP_RESET_BIT                4
#define NXP_TX_DEVICE_STATUS_IS_IN_PT_MODE_BIT            3
#define NXP_TX_DEVICE_STATUS_IS_IN_PAIRING_BIT            2
#define NXP_TX_DEVICE_STATUS_EXTERNAL_MIC_INSERTED_BIT    1
#define NXP_TX_DEVICE_STATUS_RF_CONNECTED_BIT             0

#define NXP_TX_AUDIO_STATUS_1_FORMAT_EMMC_BIT             7
#define NXP_TX_AUDIO_STATUS_1_HQ_RECORD_MODE_BIT          5
#define NXP_TX_AUDIO_STATUS_1_STEREO_RECORD_BIT           4
#define NXP_TX_AUDIO_STATUS_1_AGC_BIT                     3
#define NXP_TX_AUDIO_STATUS_1_AUTO_RECORD_BIT             2
#define NXP_TX_AUDIO_STATUS_1_RECORD_BIT                  1
#define NXP_TX_AUDIO_STATUS_1_MUTE_BIT                    0

#define NXP_TX_AUDIO_STATUS_2_NR_MODE_BIT                 2
#define NXP_TX_AUDIO_STATUS_2_LOW_CUT_MODE_BIT            0

#define NXP_TX_AUDIO_STATUS_N_EQ_MODE_BIT                 6    // HWJ: temporary used.


#define NXP_RX_DEVICE_STATUS_HAS_CHARGER_BIT              7
#define NXP_RX_DEVICE_STATUS_IS_CHARGING_OVER_BIT         6
#define NXP_RX_DEVICE_STATUS_IS_POWER_ON_BIT              5
#define NXP_RX_DEVICE_STATUS_IS_IN_PT_MODE_BIT            4
#define NXP_RX_DEVICE_STATUS_IS_IN_PAIRING_BIT            3
#define NXP_RX_DEVICE_STATUS_HEADSET_ATTACHED_BIT         2
#define NXP_RX_DEVICE_STATUS_LINE_OUT_ATTACHED_BIT        1
#define NXP_RX_DEVICE_STATUS_USB_ATTACHED_BIT             0

#define NXP_RX_AUDIO_STATUS_IN_CASE_STATUS                7
#define NXP_RX_AUDIO_STATUS_CLOSE_LID_STATUS              6
#define NXP_RX_AUDIO_STATUS_IS_APP_CONNECTED              5
#define NXP_RX_AUDIO_STATUS_EQ_MODE                       3
#define NXP_RX_AUDIO_STATUS_SETERO_OR_SAFETY_MODE_BIT     1
#define NXP_RX_AUDIO_STATUS_LR_2_RL_MODE_BIT              0

/* ------------------------------------ GetSystemInfo ------------------------------------ */
#define NXP_GET_SYSTEM_INFO_COMMAND                                            (0x00)
#define NXP_GET_SYSTEM_INFO_COMMAND_DATA_LENGTH                                (0x01)
#define NXP_GET_SYSTEM_INFO_COMMAND_CRC_OFFSET                                 (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_DATA_LENGTH                            (0x08)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_LAGUAGE_OFFSET                         (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_YEAR_OFFSET                       (NXP_PKT_OFFS_DATA + 1)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_MONTH_OFFSET                      (NXP_PKT_OFFS_DATA + 2)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_DAY_OFFSET                        (NXP_PKT_OFFS_DATA + 3)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_HOUR_OFFSET                       (NXP_PKT_OFFS_DATA + 4)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_MINUTE_OFFSET                     (NXP_PKT_OFFS_DATA + 5)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_TIME_SECOND_OFFSET                     (NXP_PKT_OFFS_DATA + 6)
#define NXP_GET_SYSTEM_INFO_COMMAND_RSP_CRC_OFFSET                             (NXP_PKT_OFFS_DATA + 7)

/* ---------------------------------- GetTx1DeviceParam ---------------------------------- */
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND                                       (0x01)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_DATA_LENGTH                           (0x01)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_CRC_OFFSET                            (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH                       (0x0D)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET              (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET             (NXP_PKT_OFFS_DATA + 1)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET             (NXP_PKT_OFFS_DATA + 2)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_GAIN_OFFSET                   (NXP_PKT_OFFS_DATA + 3)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET                  (NXP_PKT_OFFS_DATA + 4)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_RSSI_OFFSET                       (NXP_PKT_OFFS_DATA + 5)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET              (NXP_PKT_OFFS_DATA + 6)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_FILE_NUMBER_OFFSET                (NXP_PKT_OFFS_DATA + 7)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_1_OFFSET            (NXP_PKT_OFFS_DATA + 8)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_2_OFFSET            (NXP_PKT_OFFS_DATA + 9)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_3_OFFSET            (NXP_PKT_OFFS_DATA + 10)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_4_OFFSET            (NXP_PKT_OFFS_DATA + 11)
#define NXP_GET_TX1_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET                        (NXP_PKT_OFFS_DATA + 12)

/* ---------------------------------- GetTx2DeviceParam ---------------------------------- */
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND                                       (0x02)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_DATA_LENGTH                           (0x01)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_CRC_OFFSET                            (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH                       (0x0D)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET              (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET             (NXP_PKT_OFFS_DATA + 1)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET             (NXP_PKT_OFFS_DATA + 2)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_GAIN_OFFSET                   (NXP_PKT_OFFS_DATA + 3)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_MIC_LEVEL_OFFSET                  (NXP_PKT_OFFS_DATA + 4)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_RSSI_OFFSET                       (NXP_PKT_OFFS_DATA + 5)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET              (NXP_PKT_OFFS_DATA + 6)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_FILE_NUMBER_OFFSET                (NXP_PKT_OFFS_DATA + 7)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_1_OFFSET            (NXP_PKT_OFFS_DATA + 8)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_2_OFFSET            (NXP_PKT_OFFS_DATA + 9)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_3_OFFSET            (NXP_PKT_OFFS_DATA + 10)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_REC_FILE_SIZE_4_OFFSET            (NXP_PKT_OFFS_DATA + 11)
#define NXP_GET_TX2_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET                        (NXP_PKT_OFFS_DATA + 12)

/* ---------------------------------- GetRxDeviceParam ---------------------------------- */
#define NXP_GET_RX_DEVICE_PARAM_COMMAND                                        (0x03)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_DATA_LENGTH                            (0x01)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_CRC_OFFSET                             (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH                        (0x05)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_DEVICE_STATUS_OFFSET               (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_OFFSET                (NXP_PKT_OFFS_DATA + 1)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_RX_GAIN_OFFSET                     (NXP_PKT_OFFS_DATA + 2)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_BATTERY_LEVEL_OFFSET               (NXP_PKT_OFFS_DATA + 3)
#define NXP_GET_RX_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET                         (NXP_PKT_OFFS_DATA + 4)

/* ------------------------------------ GetDeviceInfo ------------------------------------ */
#define NXP_GET_DEVICE_INFO_COMMAND                                            (0x04)
#define NXP_GET_DEVICE_INFO_COMMAND_DATA_LENGTH                                (0x01)
#define NXP_GET_DEVICE_INFO_COMMAND_CRC_OFFSET                                 (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_DATA_LENGTH                            (0x07)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_TX1_FW_VER_L_OFFSET                    (NXP_PKT_OFFS_DATA + 0)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_TX1_FW_VER_H_OFFSET                    (NXP_PKT_OFFS_DATA + 1)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_TX2_FW_VER_L_OFFSET                    (NXP_PKT_OFFS_DATA + 2)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_TX2_FW_VER_H_OFFSET                    (NXP_PKT_OFFS_DATA + 3)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_RX_FW_VER_L_OFFSET                     (NXP_PKT_OFFS_DATA + 4)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_RX_FW_VER_H_OFFSET                     (NXP_PKT_OFFS_DATA + 5)
#define NXP_GET_DEVICE_INFO_COMMAND_RSP_CRC_OFFSET                             (NXP_PKT_OFFS_DATA + 6)

/* ---------------------------------- SetTx1DeviceParam ---------------------------------- */
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND                                       (0x06)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_DATA_LENGTH                           (0x4)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_AUDIO_STATUS_1_OFFSET                 (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_AUDIO_STATUS_2_OFFSET                 (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_TX_GAIN_OFFSET                        (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_CRC_OFFSET                            (NXP_PKT_OFFS_DATA + 3)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH                       (0x4)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET             (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET             (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_TX_GAIN_OFFSET                    (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_TX1_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET                        (NXP_PKT_OFFS_DATA + 3)

/* ---------------------------------- SetTx2DeviceParam ---------------------------------- */
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND                                       (0x07)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_DATA_LENGTH                           (0x4)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_AUDIO_STATUS_1_OFFSET                 (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_AUDIO_STATUS_2_OFFSET                 (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_TX_GAIN_OFFSET                        (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_CRC_OFFSET                            (NXP_PKT_OFFS_DATA + 3)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH                       (0x4)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_1_OFFSET             (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_2_OFFSET             (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_TX_GAIN_OFFSET                    (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_TX2_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET                        (NXP_PKT_OFFS_DATA + 3)

/* ----------------------------------- SetRxDeviceParam ----------------------------------- */
#define NXP_SET_RX_DEVICE_PARAM_COMMAND                                        (0x08)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_DATA_LENGTH                            (0x3)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_AUDIO_STATUS_OFFSET                    (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_RX_GAIN_OFFSET                         (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_CRC_OFFSET                             (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_DATA_LENGTH                        (0x3)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_AUDIO_STATUS_OFFSET                (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_RX_GAIN_OFFSET                     (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_RX_DEVICE_PARAM_COMMAND_RSP_CRC_OFFSET                         (NXP_PKT_OFFS_DATA + 2)

/* ------------------------------------ SetSystemInfo ------------------------------------ */
#define NXP_SET_SYSTEM_INFO_COMMAND                                            (0x09)
#define NXP_SET_SYSTEM_INFO_COMMAND_DATA_LENGTH                                (0x09)
#define NXP_SET_SYSTEM_INFO_COMMAND_LAGUAGE_OFFSET                             (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_SYSTEM_INFO_COMMAND_TIME_YEAR_OFFSET                           (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_SYSTEM_INFO_COMMAND_TIME_MONTH_OFFSET                          (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_SYSTEM_INFO_COMMAND_TIME_DAY_OFFSET                            (NXP_PKT_OFFS_DATA + 3)
#define NXP_SET_SYSTEM_INFO_COMMAND_TIME_HOUR_OFFSET                           (NXP_PKT_OFFS_DATA + 4)
#define NXP_SET_SYSTEM_INFO_COMMAND_TIME_MINUTE_OFFSET                         (NXP_PKT_OFFS_DATA + 5)
#define NXP_SET_SYSTEM_INFO_COMMAND_TIME_SECOND_OFFSET                         (NXP_PKT_OFFS_DATA + 6)
#define NXP_SET_SYSTEM_INFO_COMMAND_RESERVED_OFFSET                            (NXP_PKT_OFFS_DATA + 7)
#define NXP_SET_SYSTEM_INFO_COMMAND_CRC_OFFSET                                 (NXP_PKT_OFFS_DATA + 8)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_DATA_LENGTH                            (0x09)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_LAGUAGE_OFFSET                         (NXP_PKT_OFFS_DATA + 0)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_YEAR_OFFSET                       (NXP_PKT_OFFS_DATA + 1)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_MONTH_OFFSET                      (NXP_PKT_OFFS_DATA + 2)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_DAY_OFFSET                        (NXP_PKT_OFFS_DATA + 3)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_HOUR_OFFSET                       (NXP_PKT_OFFS_DATA + 4)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_MINUTE_OFFSET                     (NXP_PKT_OFFS_DATA + 5)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_TIME_SECOND_OFFSET                     (NXP_PKT_OFFS_DATA + 6)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_RESERVED_OFFSET                        (NXP_PKT_OFFS_DATA + 7)
#define NXP_SET_SYSTEM_INFO_COMMAND_RSP_CRC_OFFSET                             (NXP_PKT_OFFS_DATA + 8)

/* ---------------------------------------------------------- */

#endif /* ARC_NXP_COM_ENABLE */

#ifdef ARC_PRODUCTION_TEST
#else /* !ARC_PRODUCTION_TEST */
#define PT_PKT_OFFS_CHANNEL                 0
#define PT_PKT_OFFS_TYPE                    1
#define PT_PKT_OFFS_LENGTH_L                2
#define PT_PKT_OFFS_LENGTH_H                3
#define PT_PKT_OFFS_PROTOCOL_ID_L           4
#define PT_PKT_OFFS_PROTOCOL_ID_H           5
#define PT_PKT_OFFS_CMD                     6
#define PT_PKT_OFFS_DATA                    7

/* ------------------------------------- SetMode ------------------------------------- */
#define PT_CMD_SET_MODE                                                        (0xB0)
#define PT_CMD_SET_MODE_DATA_LENGTH                                            (0x2)
#define PT_CMD_SET_MODE_DATA_ENABLE_OFFSET                                     (PT_PKT_OFFS_DATA)
#define PT_CMD_SET_MODE_DATA_CRC_OFFSET                                        (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_SET_MODE_RSP_DATA_LENGTH                                        (0x2)
#define PT_CMD_SET_MODE_RSP_DATA_ENABLE_OFFSET                                 (PT_PKT_OFFS_DATA)
#define PT_CMD_SET_MODE_RSP_DATA_CRC_OFFSET                                    (PT_PKT_OFFS_DATA + 1)

/* ----------------------------------- GetLocalAddr ----------------------------------- */
#define PT_CMD_GET_LOCAL_ADDR                                                  (0xB1)
#define PT_CMD_GET_LOCAL_ADDR_DATA_LENGTH                                      (0x1)
#define PT_CMD_GET_LOCAL_ADDR_DATA_CRC_OFFSET                                  (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_LENGTH                                  (0x7)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_ADDR_0_OFFSET                           (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_ADDR_1_OFFSET                           (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_ADDR_2_OFFSET                           (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_ADDR_3_OFFSET                           (PT_PKT_OFFS_DATA + 3)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_ADDR_4_OFFSET                           (PT_PKT_OFFS_DATA + 4)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_ADDR_5_OFFSET                           (PT_PKT_OFFS_DATA + 5)
#define PT_CMD_GET_LOCAL_ADDR_RSP_DATA_CRC_OFFSET                              (PT_PKT_OFFS_DATA + 6)

/* ----------------------------------- GetKeyStatus ----------------------------------- */
#define PT_CMD_GET_KEY_STATUS                                                  (0xB2)
#define PT_CMD_GET_KEY_STATUS_DATA_LENGTH                                      (0x1)
#define PT_CMD_GET_KEY_STATUS_DATA_CRC_OFFSET                                  (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_LENGTH                                  (0x6)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_KEY_ID_OFFSET                           (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_KEY_EVENT_OFFSET                        (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_MMI_STATE_OFFSET                        (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_ACTION_ID_H_OFFSET                      (PT_PKT_OFFS_DATA + 3)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_ACTION_ID_L_OFFSET                      (PT_PKT_OFFS_DATA + 4)
#define PT_CMD_GET_KEY_STATUS_RSP_DATA_CRC_OFFSET                              (PT_PKT_OFFS_DATA + 5)

/* -------------------------------- GetSoftwareVersion -------------------------------- */
#define PT_CMD_GET_SW_VER                                                      (0xB4)
#define PT_CMD_GET_SW_VER_DATA_LENGTH                                          (0x1)
#define PT_CMD_GET_SW_VER_DATA_CRC_OFFSET                                      (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_SW_VER_RSP_DATA_LENGTH                                      (0x4)
#define PT_CMD_GET_SW_VER_RSP_DATA_MAJOR_OFFSET                                (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_SW_VER_RSP_DATA_MINOR_OFFSET                                (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_SW_VER_RSP_DATA_REVISION_OFFSET                             (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_GET_SW_VER_RSP_DATA_CRC_OFFSET                                  (PT_PKT_OFFS_DATA + 3)

/* ----------------------------------- LowCutSwitch ----------------------------------- */
#define PT_CMD_LOW_CUT_SWITCH                                                  (0xC5)
#define PT_CMD_LOW_CUT_SWITCH_DATA_LENGTH                                      (0x1)
#define PT_CMD_LOW_CUT_SWITCH_DATA_CRC_OFFSET                                  (PT_PKT_OFFS_DATA)
#define PT_CMD_LOW_CUT_SWITCH_RSP_DATA_LENGTH                                  (0x2)
#define PT_CMD_LOW_CUT_SWITCH_RSP_DATA_STATUS_OFFSET                           (PT_PKT_OFFS_DATA)
#define PT_CMD_LOW_CUT_SWITCH_RSP_DATA_CRC_OFFSET                              (PT_PKT_OFFS_DATA + 1)

/* ------------------------------- NoiseReductionSwitch ------------------------------- */
#define PT_CMD_NOISE_REDUCTION_SWITCH                                          (0xC6)
#define PT_CMD_NOISE_REDUCTION_SWITCH_DATA_LENGTH                              (0x1)
#define PT_CMD_NOISE_REDUCTION_SWITCH_DATA_CRC_OFFSET                          (PT_PKT_OFFS_DATA)
#define PT_CMD_NOISE_REDUCTION_SWITCH_RSP_DATA_LENGTH                          (0x2)
#define PT_CMD_NOISE_REDUCTION_SWITCH_RSP_DATA_STATUS_OFFSET                   (PT_PKT_OFFS_DATA)
#define PT_CMD_NOISE_REDUCTION_SWITCH_RSP_DATA_CRC_OFFSET                      (PT_PKT_OFFS_DATA + 1)

/* ------------------------------- StereoModeSwitch ------------------------------- */
#define PT_CMD_STEREO_MODE_SWITCH                                              (0xC7)
#define PT_CMD_STEREO_MODE_SWITCH_DATA_LENGTH                                  (0x1)
#define PT_CMD_STEREO_MODE_SWITCH_DATA_CRC_OFFSET                              (PT_PKT_OFFS_DATA)
#define PT_CMD_STEREO_MODE_SWITCH_RSP_DATA_LENGTH                              (0x2)
#define PT_CMD_STEREO_MODE_SWITCH_RSP_DATA_STATUS_OFFSET                       (PT_PKT_OFFS_DATA)
#define PT_CMD_STEREO_MODE_SWITCH_RSP_DATA_CRC_OFFSET                          (PT_PKT_OFFS_DATA + 1)

/* ---------------------------- HighResRecorderSwitch ---------------------------- */
#define PT_CMD_HIGH_RES_RECORDER_SWITCH                                        (0xC8)

/* ------------------------------- SafetyModeSwitch ------------------------------- */
#define PT_CMD_SAFETY_MODE_SWITCH                                              (0xC9)
#define PT_CMD_SAFETY_MODE_SWITCH_DATA_LENGTH                                  (0x1)
#define PT_CMD_SAFETY_MODE_SWITCH_DATA_CRC_OFFSET                              (PT_PKT_OFFS_DATA)
#define PT_CMD_SAFETY_MODE_SWITCH_RSP_DATA_LENGTH                              (0x2)
#define PT_CMD_SAFETY_MODE_SWITCH_RSP_DATA_STATUS_OFFSET                       (PT_PKT_OFFS_DATA)
#define PT_CMD_SAFETY_MODE_SWITCH_RSP_DATA_CRC_OFFSET                          (PT_PKT_OFFS_DATA + 1)

/* ---------------------------------- EqModeSet ---------------------------------- */
#define PT_CMD_EQ_MODE_SET                                                     (0xD0)
#define PT_CMD_EQ_MODE_SET_DATA_LENGTH                                         (0x2)
#define PT_CMD_EQ_MODE_SET_DATA_EQ_OFFSET                                      (PT_PKT_OFFS_DATA)
#define PT_CMD_EQ_MODE_SET_DATA_CRC_OFFSET                                     (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_EQ_MODE_SET_RSP_DATA_LENGTH                                     (0x2)
#define PT_CMD_EQ_MODE_SET_RSP_DATA_STATUS_OFFSET                              (PT_PKT_OFFS_DATA)
#define PT_CMD_EQ_MODE_SET_RSP_DATA_CRC_OFFSET                                 (PT_PKT_OFFS_DATA + 1)

/* --------------------------------- ResetParingInfo --------------------------------- */
#define PT_CMD_RESET_PARING_INFO                                               (0xB5)
#define PT_CMD_RESET_PARING_INFO_DATA_LENGTH                                   (0x1)
#define PT_CMD_RESET_PARING_INFO_DATA_CRC_OFFSET                               (PT_PKT_OFFS_DATA)
#define PT_CMD_RESET_PARING_INFO_RSP_DATA_LENGTH                               (0x1)
#define PT_CMD_RESET_PARING_INFO_RSP_DATA_CRC_OFFSET                           (PT_PKT_OFFS_DATA)

/* ------------------------------------ GetBattery ------------------------------------ */
#define PT_CMD_GET_BATTERY                                                     (0xB7)
#define PT_CMD_GET_BATTERY_DATA_LENGTH                                         (0x1)
#define PT_CMD_GET_BATTERY_DATA_CRC_OFFSET                                     (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_BATTERY_RSP_DATA_LENGTH                                     (0x4)
#define PT_CMD_GET_BATTERY_RSP_DATA_IN_PERCENT_OFFSET                          (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_BATTERY_RSP_DATA_IN_VOLTAGE_H_OFFSET                        (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_BATTERY_RSP_DATA_IN_VOLTAGE_L_OFFSET                        (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_GET_BATTERY_RSP_DATA_CRC_OFFSET                                 (PT_PKT_OFFS_DATA + 3)

/* -------------------------------------- GetNtc -------------------------------------- */
#define PT_CMD_GET_NTC                                                         (0xB8)
#define PT_CMD_GET_NTC_DATA_LENGTH                                             (0x2)
#define PT_CMD_GET_NTC_DATA_SRC_OFFSET                                         (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_NTC_DATA_CRC_OFFSET                                         (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_NTC_RSP_DATA_LENGTH                                         (0x4)
#define PT_CMD_GET_NTC_RSP_DATA_IN_DEGREE_OFFSET                               (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_NTC_RSP_DATA_IN_VOLTAGE_H_OFFSET                            (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_NTC_RSP_DATA_IN_VOLTAGE_L_OFFSET                            (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_GET_NTC_RSP_DATA_CRC_OFFSET                                     (PT_PKT_OFFS_DATA + 3)

/* ----------------------------------- SetSerialNumber ----------------------------------- */
#define PT_CMD_SET_SN                                                          (0xBC)
#define PT_CMD_SET_SN_DATA_LENGTH                                              (0x13)
#define PT_CMD_SET_SN_DATA_SN_0_OFFSET                                         (PT_PKT_OFFS_DATA + 0)
#define PT_CMD_SET_SN_DATA_SN_1_OFFSET                                         (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_SET_SN_DATA_SN_2_OFFSET                                         (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_SET_SN_DATA_SN_3_OFFSET                                         (PT_PKT_OFFS_DATA + 3)
#define PT_CMD_SET_SN_DATA_SN_4_OFFSET                                         (PT_PKT_OFFS_DATA + 4)
#define PT_CMD_SET_SN_DATA_SN_5_OFFSET                                         (PT_PKT_OFFS_DATA + 5)
#define PT_CMD_SET_SN_DATA_SN_6_OFFSET                                         (PT_PKT_OFFS_DATA + 6)
#define PT_CMD_SET_SN_DATA_SN_7_OFFSET                                         (PT_PKT_OFFS_DATA + 7)
#define PT_CMD_SET_SN_DATA_SN_8_OFFSET                                         (PT_PKT_OFFS_DATA + 8)
#define PT_CMD_SET_SN_DATA_SN_9_OFFSET                                         (PT_PKT_OFFS_DATA + 9)
#define PT_CMD_SET_SN_DATA_SN_10_OFFSET                                        (PT_PKT_OFFS_DATA + 10)
#define PT_CMD_SET_SN_DATA_SN_11_OFFSET                                        (PT_PKT_OFFS_DATA + 11)
#define PT_CMD_SET_SN_DATA_SN_12_OFFSET                                        (PT_PKT_OFFS_DATA + 12)
#define PT_CMD_SET_SN_DATA_SN_13_OFFSET                                        (PT_PKT_OFFS_DATA + 13)
#define PT_CMD_SET_SN_DATA_SN_14_OFFSET                                        (PT_PKT_OFFS_DATA + 14)
#define PT_CMD_SET_SN_DATA_SN_15_OFFSET                                        (PT_PKT_OFFS_DATA + 15)
#define PT_CMD_SET_SN_DATA_SN_16_OFFSET                                        (PT_PKT_OFFS_DATA + 16)
#define PT_CMD_SET_SN_DATA_SN_17_OFFSET                                        (PT_PKT_OFFS_DATA + 17)
#define PT_CMD_SET_SN_DATA_CRC_OFFSET                                          (PT_PKT_OFFS_DATA + 18)
#define PT_CMD_SET_SN_RSP_DATA_LENGTH                                          (0x2)
#define PT_CMD_SET_SN_RSP_DATA_STATUS_OFFSET                                   (PT_PKT_OFFS_DATA)
#define PT_CMD_SET_SN_RSP_DATA_CRC_OFFSET                                      (PT_PKT_OFFS_DATA + 1)

/* ---------------------------------- GetSerialNumber ---------------------------------- */
#define PT_CMD_GET_SN                                                          (0xBD)
#define PT_CMD_GET_SN_DATA_LENGTH                                              (0x1)
#define PT_CMD_GET_SN_DATA_CRC_OFFSET                                          (PT_PKT_OFFS_DATA)
#define PT_CMD_GET_SN_RSP_DATA_LENGTH                                          (0x13)
#define PT_CMD_GET_SN_RSP_DATA_SN_0_OFFSET                                     (PT_PKT_OFFS_DATA + 0)
#define PT_CMD_GET_SN_RSP_DATA_SN_1_OFFSET                                     (PT_PKT_OFFS_DATA + 1)
#define PT_CMD_GET_SN_RSP_DATA_SN_2_OFFSET                                     (PT_PKT_OFFS_DATA + 2)
#define PT_CMD_GET_SN_RSP_DATA_SN_3_OFFSET                                     (PT_PKT_OFFS_DATA + 3)
#define PT_CMD_GET_SN_RSP_DATA_SN_4_OFFSET                                     (PT_PKT_OFFS_DATA + 4)
#define PT_CMD_GET_SN_RSP_DATA_SN_5_OFFSET                                     (PT_PKT_OFFS_DATA + 5)
#define PT_CMD_GET_SN_RSP_DATA_SN_6_OFFSET                                     (PT_PKT_OFFS_DATA + 6)
#define PT_CMD_GET_SN_RSP_DATA_SN_7_OFFSET                                     (PT_PKT_OFFS_DATA + 7)
#define PT_CMD_GET_SN_RSP_DATA_SN_8_OFFSET                                     (PT_PKT_OFFS_DATA + 8)
#define PT_CMD_GET_SN_RSP_DATA_SN_9_OFFSET                                     (PT_PKT_OFFS_DATA + 9)
#define PT_CMD_GET_SN_RSP_DATA_SN_10_OFFSET                                    (PT_PKT_OFFS_DATA + 10)
#define PT_CMD_GET_SN_RSP_DATA_SN_11_OFFSET                                    (PT_PKT_OFFS_DATA + 11)
#define PT_CMD_GET_SN_RSP_DATA_SN_12_OFFSET                                    (PT_PKT_OFFS_DATA + 12)
#define PT_CMD_GET_SN_RSP_DATA_SN_13_OFFSET                                    (PT_PKT_OFFS_DATA + 13)
#define PT_CMD_GET_SN_RSP_DATA_SN_14_OFFSET                                    (PT_PKT_OFFS_DATA + 14)
#define PT_CMD_GET_SN_RSP_DATA_SN_15_OFFSET                                    (PT_PKT_OFFS_DATA + 15)
#define PT_CMD_GET_SN_RSP_DATA_SN_16_OFFSET                                    (PT_PKT_OFFS_DATA + 16)
#define PT_CMD_GET_SN_RSP_DATA_SN_17_OFFSET                                    (PT_PKT_OFFS_DATA + 17)
#define PT_CMD_GET_SN_RSP_DATA_CRC_OFFSET                                      (PT_PKT_OFFS_DATA + 18)

/* ------------------------------------- ResetCmd ------------------------------------- */
#define PT_CMD_RESET                                                           (0xC1)
#define PT_CMD_RESET_DATA_LENGTH                                               (0x1)
#define PT_CMD_RESET_DATA_CRC_OFFSET                                           (PT_PKT_OFFS_DATA)
#define PT_CMD_RESET_RSP_DATA_LENGTH                                           (0x2)
#define PT_CMD_RESET_RSP_DATA_STATUS_OFFSET                                    (PT_PKT_OFFS_DATA)
#define PT_CMD_RESET_RSP_DATA_CRC_OFFSET                                       (PT_PKT_OFFS_DATA + 1)

/* ------------------------------------ PowerOffCmd ------------------------------------ */
#define PT_CMD_POWER_OFF                                                       (0xCB)
#define PT_CMD_POWER_OFF_DATA_LENGTH                                           (0x1)
#define PT_CMD_POWER_OFF_DATA_CRC_OFFSET                                       (PT_PKT_OFFS_DATA)
#define PT_CMD_POWER_OFF_RSP_DATA_LENGTH                                       (0x1)
#define PT_CMD_POWER_OFF_RSP_DATA_CRC_OFFSET                                   (PT_PKT_OFFS_DATA)

#endif /* ARC_PRODUCTION_TEST */


////////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* _DRV_SMART_CHARGER_H_ */
