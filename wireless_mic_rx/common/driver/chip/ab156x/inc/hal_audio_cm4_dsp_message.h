/* Copyright Statement:
 *
 * (C) 2022  Airoha Technology Corp. All rights reserved.
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

#ifndef __HAL_AUDIO_CM4_DSP_MESSAGE_H__
#define __HAL_AUDIO_CM4_DSP_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------
// CM4 to DSP message base address
//--------------------------------------------
#define MSG_MCU2DSP_COMMON_BASE          0x0000
#define MSG_MCU2DSP_BT_AUDIO_UL_BASE     0x0100  //ToDo
#define MSG_MCU2DSP_BT_AUDIO_DL_BASE     0x0200
#define MSG_MCU2DSP_BT_VOICE_UL_BASE     0x0300
#define MSG_MCU2DSP_BT_VOICE_DL_BASE     0x0400
#define MSG_MCU2DSP_PLAYBACK_BASE        0x0500
#define MSG_MCU2DSP_RECORD_BASE          0x0600  //ToDo
#define MSG_MCU2DSP_PROMPT_BASE          0x0700
#define MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_BASE 0x0780
#define MSG_MCU2DSP_LINEIN_PLAYBACK_BASE 0x0800
#define MSG_MCU2DSP_BLE_AUDIO_UL_BASE    0x0900
#define MSG_MCU2DSP_BLE_AUDIO_DL_BASE    0x0A00
#define MSG_MCU2DSP_AUDIO_BASE           0x0B00
#define MSG_MCU2DSP_AUDIO_TRANSMITTER_BASE 0x0C00
#define MSG_MCU2DSP_ADAPT_ANC_BASE       0x0D00
#define MSG_MCU2DSP_ANC_BASE             0x0D30

typedef enum {
    // MSG_MCU2DSP_COMMON_BASE           0x0000
    MSG_MCU2DSP_COMMON_SET_MEMORY = MSG_MCU2DSP_COMMON_BASE,
    MSG_MCU2DSP_COMMON_SET_SYSRAM,
    MSG_MCU2DSP_COMMON_STREAM_DEINIT,
    MSG_DSP2MCU_COMMON_UPDATE_AUDIO_NVDM_STATUS,

    MSG_MCU2DSP_COMMON_SET_INPUT_DEVICE = MSG_MCU2DSP_COMMON_BASE + 0x10,
    MSG_MCU2DSP_COMMON_MUTE_INPUT_DEVICE,
    MSG_MCU2DSP_COMMON_SET_INPUT_DEVICE_VOLUME,
    MSG_MCU2DSP_COMMON_SET_INPUT_DEVICE_CHANNEL,

    MSG_MCU2DSP_COMMON_SET_OUTPUT_DEVICE = MSG_MCU2DSP_COMMON_BASE + 0x20,
    MSG_MCU2DSP_COMMON_MUTE_OUTPUT_DEVICE,
    MSG_MCU2DSP_COMMON_SET_OUTPUT_DEVICE_VOLUME,
    MSG_MCU2DSP_COMMON_SET_OUTPUT_DEVICE_CHANNEL,
    MSG_MCU2DSP_COMMON_SET_OUTPUT_VOLUME_PARAMETERS,
    MSG_MCU2DSP_COMMON_SW_GAIN_EN,
    MSG_MCU2DSP_COMMON_SET_DRIVER_PARAM,
    MSG_MCU2DSP_COMMON_POWER_OFF_DAC_IMMEDIATELY,

    MSG_MCU2DSP_COMMON_SPEECH_SET_MODE = MSG_MCU2DSP_COMMON_BASE + 0x30,
    MSG_MCU2DSP_COMMON_SPEECH_SET_ENHANCEMENT_PARAMTER,
    MSG_MCU2DSP_COMMON_SPEECH_ENHANCEMENT_START,
    MSG_MCU2DSP_COMMON_SPEECH_ENHANCEMENT_STOP,

    MSG_MCU2DSP_COMMON_SIDETONE_START = MSG_MCU2DSP_COMMON_BASE + 0x40,
    MSG_MCU2DSP_COMMON_SIDETONE_STOP,
    MSG_MCU2DSP_COMMON_SIDETONE_SET_VOLUME,

    MSG_MCU2DSP_COMMON_DC_COMPENSATION_START = MSG_MCU2DSP_COMMON_BASE + 0x48,
    MSG_MCU2DSP_COMMON_DC_COMPENSATION_STOP,
    MSG_MCU2DSP_COMMON_CHANGE_DSP_SETTING,
    MSG_MCU2DSP_COMMON_CHANGE_DSP_CHANEL,
    MSG_MCU2DSP_COMMON_DUMMY_DSP_SHUTDOWN,
    MSG_MCU2DSP_COMMON_ALC_SWITCH,
    MSG_MCU2DSP_COMMON_AUDIO_LOOPBACK_TEST,

    MSG_MCU2DSP_COMMON_REQ_GET_REALTIME_REF_GAIN = MSG_MCU2DSP_COMMON_BASE + 0x50,
    MSG_MCU2DSP_COMMON_AEC_NR_SET_PARAM,
    MSG_MCU2DSP_COMMON_PEQ_SET_PARAM,
    MSG_MCU2DSP_COMMON_DEQ_SET_PARAM,
    MSG_MCU2DSP_COMMON_SET_ALGORITHM_PARAM,
    MSG_MCU2DSP_COMMON_AUDIO_ANC_ADAPTIVE_GET,
    MSG_MCU2DSP_COMMON_AUDIO_ANC_ADAPTIVE_SET,
    MSG_MCU2DSP_COMMON_ADEQ_SET_PARAM,
    MSG_MCU2DSP_COMMON_REQ_GET_REALTIME_LIB_VERSION,

    MSG_DSP2MCU_COMMON_REQ_GET_AUDIO_FEATURE_PARAMETER = MSG_MCU2DSP_COMMON_BASE + 0x60,
    MSG_DSP2MCU_COMMON_REQ_SET_AUDIO_FEATURE_PARAMETER,

    MSG_MCU2DSP_COMMON_AUDIO_DUMP_MASK= MSG_MCU2DSP_COMMON_BASE + 0x70,
    MSG_MCU2DSP_COMMON_AIRDUMP_EN,
    MSG_MCU2DSP_COMMON_AEC_NR_EN,
    #ifdef ENABLE_HWSRC_CLKSKEW
    MSG_MCU2DSP_COMMON_CLKSKEW_MODE_SEL,
    #endif
    #ifdef MTK_SLT_AUDIO_HW
    MSG_MCU2DSP_COMMON_AUDIO_SLT,
    MSG_DSP2MCU_COMMON_AUDIO_SLT_RESULT,
    #endif
    MSG_DSP2MCU_COMMON_AUDIO_ANC_SWITCH,
    MSG_DSP2MCU_COMMON_AUDIO_ANC_ADAPTIVE,

    // MSG_MCU2DSP_AUDIO_SYNC_REQUEST
    MSG_MCU2DSP_AUDIO_SYNC_REQUEST = MSG_MCU2DSP_COMMON_BASE + 0x80,
    MSG_DSP2MCU_AUDIO_SYNC_DONE,

    // MSG_DSP2MCU_AUDIO_VOLUME_MONITOR
    MSG_DSP2MCU_AUDIO_VOLUME_MONITOR_START = MSG_MCU2DSP_COMMON_BASE + 0x90,
    MSG_DSP2MCU_AUDIO_VOLUME_MONITOR_STOP,

    // MSG_MCU2DSP_BT_AUDIO_UL_BASE    0x0100

    // MSG_MCU2DSP_BT_AUDIO_DL_BASE    0x0200
    MSG_MCU2DSP_BT_AUDIO_DL_OPEN = MSG_MCU2DSP_BT_AUDIO_DL_BASE,
    MSG_MCU2DSP_BT_AUDIO_DL_CLOSE,
    MSG_MCU2DSP_BT_AUDIO_DL_START,
    MSG_MCU2DSP_BT_AUDIO_DL_STOP,
    MSG_MCU2DSP_BT_AUDIO_DL_CONFIG,
    MSG_MCU2DSP_BT_AUDIO_DL_SET_VOLUME,
    MSG_DSP2MCU_BT_AUDIO_DL_ERROR,
    MSG_DSP2MCU_BT_AUDIO_DL_TIME_REPORT,
    MSG_MCU2DSP_BT_AUDIO_DL_SUSPEND,
    MSG_MCU2DSP_BT_AUDIO_DL_RESUME,
    MSG_DSP2MCU_BT_AUDIO_DL_LTCS_DATA_REPORT,
    MSG_DSP2MCU_BT_AUDIO_DL_REINIT_REQUEST,
    MSG_DSP2MCU_BT_AUDIO_DL_ALC_REQUEST,
    MSG_DSP2MCU_BT_AUDIO_DL_LTCS_TIMEOUT_REQUEST,
    MSG_MCU2DSP_BT_AUDIO_DL_RST_LOSTNUM_REPORT,
    MSG_MCU2DSP_BT_AUDIO_PLC_CONTROL,
    MSG_MCU2DSP_BT_AUDIO_DL_PLAY_EN_FROM_BTCON,
    MSG_MCU2DSP_HWGAIN_SET_FADE_TIME_GAIN,
    MSG_MCU2DSP_BT_AUDIO_CLK_SKEW_DEBUG_CONTROL,

    // MSG_MCU2DSP_BT_VOICE_UL_BASE    0x0300
    MSG_MCU2DSP_BT_VOICE_UL_OPEN = MSG_MCU2DSP_BT_VOICE_UL_BASE,
    MSG_MCU2DSP_BT_VOICE_UL_CLOSE,
    MSG_MCU2DSP_BT_VOICE_UL_START,
    MSG_MCU2DSP_BT_VOICE_UL_STOP,
    MSG_MCU2DSP_BT_VOICE_UL_CONFIG,
    MSG_MCU2DSP_BT_VOICE_UL_SET_VOLUME,
    MSG_DSP2MCU_BT_VOICE_UL_ERROR,
    MSG_MCU2DSP_BT_VOICE_UL_PLAY_EN,
    MSG_MCU2DSP_BT_VOICE_UL_SUSPEND,
    MSG_MCU2DSP_BT_VOICE_UL_RESUME,
    MSG_DSP2MCU_AVC_PARA_SEND,
    MSG_DSP2MCU_LEQ_PARA_SEND,

    // MSG_MCU2DSP_BT_VOICE_DL_BASE    0x0400
    MSG_MCU2DSP_BT_VOICE_DL_OPEN = MSG_MCU2DSP_BT_VOICE_DL_BASE,
    MSG_MCU2DSP_BT_VOICE_DL_CLOSE,
    MSG_MCU2DSP_BT_VOICE_DL_START,
    MSG_MCU2DSP_BT_VOICE_DL_STOP,
    MSG_MCU2DSP_BT_VOICE_DL_CONFIG,
    MSG_MCU2DSP_BT_VOICE_DL_SET_VOLUME,
    MSG_DSP2MCU_BT_VOICE_DL_ERROR,
    MSG_MCU2DSP_BT_VOICE_DL_SUSPEND,
    MSG_MCU2DSP_BT_VOICE_DL_RESUME,
    MSG_MCU2DSP_BT_VOICE_DL_AVC_PARA_SEND,
    MSG_MCU2DSP_BT_VOICE_DL_LEQ_PARA_SEND,

    // MSG_MCU2DSP_PLAYBACK_BASE       0x0500
    MSG_MCU2DSP_PLAYBACK_OPEN = MSG_MCU2DSP_PLAYBACK_BASE,
    MSG_MCU2DSP_PLAYBACK_CLOSE,
    MSG_MCU2DSP_PLAYBACK_START,
    MSG_MCU2DSP_PLAYBACK_STOP,
    MSG_MCU2DSP_PLAYBACK_CONFIG,
    MSG_MCU2DSP_PLAYBACK_SET_VOLUME,
    MSG_DSP2MCU_PLAYBACK_ERROR,
    MSG_DSP2MCU_PLAYBACK_DATA_REQUEST,
    MSG_MCU2DSP_PLAYBACK_SUSPEND,
    MSG_MCU2DSP_PLAYBACK_RESUME,

    // MSG_MCU2DSP_RECORD_BASE         0x0600
    MSG_MCU2DSP_RECORD_OPEN = MSG_MCU2DSP_RECORD_BASE,
    MSG_MCU2DSP_RECORD_CLOSE,
    MSG_MCU2DSP_RECORD_START,
    MSG_MCU2DSP_RECORD_STOP,
    MSG_MCU2DSP_RECORD_CONFIG,
    MSG_MCU2DSP_RECORD_SET_VOLUME,
    MSG_DSP2MCU_RECORD_DATA_NOTIFY,
    MSG_DSP2MCU_RECORD_ERROR,
    MSG_MCU2DSP_RECORD_SUSPEND,
    MSG_MCU2DSP_RECORD_RESUME,
    MSG_DSP2MCU_RECORD_WWE_VERSION,
    MSG_DSP2MCU_RECORD_WWD_NOTIFY,
    MSG_DSP2MCU_RECORD_DATA_ABORT_NOTIFY,
    MSG_MCU2DSP_RECORD_LC_SET_PARAM = MSG_MCU2DSP_RECORD_BASE + 0x20,
    MSG_DSP2MCU_RECORD_LC_WZ_REPORT,

    // MSG_MCU2DSP_PROMPT_BASE         0x0700
    MSG_MCU2DSP_PROMPT_OPEN = MSG_MCU2DSP_PROMPT_BASE,
    MSG_MCU2DSP_PROMPT_CLOSE,
    MSG_MCU2DSP_PROMPT_START,
    MSG_MCU2DSP_PROMPT_STOP,
    MSG_MCU2DSP_PROMPT_CONFIG,
    MSG_MCU2DSP_PROMPT_SET_VOLUME,
    MSG_DSP2MCU_PROMPT_ERROR,
    MSG_DSP2MCU_PROMPT_DATA_REQUEST,
    MSG_MCU2DSP_PROMPT_AWS_SYNC_TRIGGER,
    MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_OPEN = MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_BASE,
    MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_CLOSE,
    MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_START,
    MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_STOP,
    MSG_MCU2DSP_PROMPT_DUMMY_SOURCE_CHANGE_FEATURE,

    // MSG_MCU2DSP_LINEIN_PLAYBACK_BASE         0x0800
    MSG_MCU2DSP_LINEIN_PLAYBACK_OPEN = MSG_MCU2DSP_LINEIN_PLAYBACK_BASE,
    MSG_MCU2DSP_LINEIN_PLAYBACK_CLOSE,
    MSG_MCU2DSP_LINEIN_PLAYBACK_START,
    MSG_MCU2DSP_LINEIN_PLAYBACK_STOP,
    MSG_MCU2DSP_LINEIN_PLAYBACK_SUSPEND,
    MSG_MCU2DSP_LINEIN_PLAYBACK_RESUME,
    MSG_MCU2DSP_TRULY_LINEIN_PLAYBACK_OPEN,
    MSG_MCU2DSP_TRULY_LINEIN_PLAYBACK_CLOSE,

    // MSG_MCU2DSP_BLE_AUDIO_UL_BASE    0x0900
    MSG_MCU2DSP_BLE_AUDIO_UL_OPEN = MSG_MCU2DSP_BLE_AUDIO_UL_BASE,
    MSG_MCU2DSP_BLE_AUDIO_UL_CLOSE,
    MSG_MCU2DSP_BLE_AUDIO_UL_START,
    MSG_MCU2DSP_BLE_AUDIO_UL_STOP,
    MSG_MCU2DSP_BLE_AUDIO_UL_CONFIG,
    MSG_MCU2DSP_BLE_AUDIO_UL_SET_VOLUME,
    MSG_DSP2MCU_BLE_AUDIO_UL_ERROR,
    MSG_MCU2DSP_BLE_AUDIO_UL_PLAY_EN,
    MSG_MCU2DSP_BLE_AUDIO_UL_SUSPEND,
    MSG_MCU2DSP_BLE_AUDIO_UL_RESUME,
    MSG_MCU2DSP_BLE_AUDIO_UL_BUFFER_INFO,
    MSG_MCU2DSP_BLE_AUDIO_UL_PLAYBACK_DATA_INFO,

    // MSG_MCU2DSP_BLE_AUDIO_DL_BASE    0x0A00
    MSG_MCU2DSP_BLE_AUDIO_DL_OPEN = MSG_MCU2DSP_BLE_AUDIO_DL_BASE,
    MSG_MCU2DSP_BLE_AUDIO_DL_CLOSE,
    MSG_MCU2DSP_BLE_AUDIO_DL_START,
    MSG_MCU2DSP_BLE_AUDIO_DL_STOP,
    MSG_MCU2DSP_BLE_AUDIO_DL_CONFIG,
    MSG_MCU2DSP_BLE_AUDIO_DL_SET_VOLUME,
    MSG_DSP2MCU_BLE_AUDIO_DL_ERROR,
    MSG_MCU2DSP_BLE_AUDIO_DL_SUSPEND,
    MSG_MCU2DSP_BLE_AUDIO_DL_RESUME,
    MSG_MCU2DSP_BLE_AUDIO_DL_BUFFER_INFO,
    MSG_MCU2DSP_BLE_AUDIO_INIT_PLAY_INFO,

    // MSG_MCU2DSP_AUDIO_BASE    0x0B00
    MSG_MCU2DSP_AUDIO_AMP_RESERVED  = MSG_MCU2DSP_AUDIO_BASE,
    MSG_DSP2MCU_AUDIO_AMP,
    MSG_DSP2MCU_BT_AUDIO_DL_SILENCE_DETECTION_FEEDBACK,
    MSG_MCU2DSP_AUDIO_AMP_FORCE_CLOSE,
    MSG_MCU2DSP_GSENSOR_DETECT_START,
    MSG_MCU2DSP_GSENSOR_DETECT_STOP,
    MSG_MCU2DSP_GSENSOR_DETECT_READ_RG,
    MSG_MCU2DSP_GSENSOR_DETECT_WRITE_RG,
    MSG_DSP2MCU_DCHS_COSYS_SYNC,
    MSG_DSP2MCU_AUDIO_UL_MUTE_SPEAK_DETECT,

    // MSG_MCU2DSP_AUDIO_TRANSMITTER_BASE    0x0C00
    MSG_MCU2DSP_AUDIO_TRANSMITTER_OPEN = MSG_MCU2DSP_AUDIO_TRANSMITTER_BASE,
    MSG_MCU2DSP_AUDIO_TRANSMITTER_CLOSE,
    MSG_MCU2DSP_AUDIO_TRANSMITTER_START,
    MSG_MCU2DSP_AUDIO_TRANSMITTER_STOP,
    MSG_MCU2DSP_AUDIO_TRANSMITTER_CONFIG,
    MSG_MCU2DSP_AUDIO_TRANSMITTER_SUSPEND,
    MSG_MCU2DSP_AUDIO_TRANSMITTER_RESUME,
    MSG_MCU2DSP_GAME_HEADSET_UL_IRQ_EN,
    MSG_DSP2MCU_AUDIO_TRANSMITTER_DATA_NOTIFY,
    MSG_DSP2MCU_AUDIO_TRANSMITTER_DATA_DIRECT,

    // MSG_MCU2DSP_ADAPT_ANC_BASE    0x0D00
    MSG_MCU2DSP_ADAPT_ANC_OPEN = MSG_MCU2DSP_ADAPT_ANC_BASE,
    MSG_MCU2DSP_ADAPT_ANC_CLOSE,
    MSG_MCU2DSP_ADAPT_ANC_START,
    MSG_MCU2DSP_ADAPT_ANC_STOP,

    // MSG_MCU2DSP_ANC_BASE    0x0D30
    MSG_MCU2DSP_COMMON_ANC_START      =                      MSG_MCU2DSP_ANC_BASE,        //MSG_MCU2DSP_ANC_START
    MSG_MCU2DSP_COMMON_ANC_STOP       =                     (MSG_MCU2DSP_ANC_BASE + 0x1), //MSG_MCU2DSP_ANC_STOP
    MSG_MCU2DSP_COMMON_ANC_SET_VOLUME =                     (MSG_MCU2DSP_ANC_BASE + 0x2), //MSG_MCU2DSP_ANC_SET_VOLUME
    MSG_MCU2DSP_COMMON_ANC_SET_PARAM  =                     (MSG_MCU2DSP_ANC_BASE + 0x3), //MSG_MCU2DSP_ANC_SET_PARAM
    MSG_DSP2MCU_COMMON_ANC_START_DONE =                     (MSG_MCU2DSP_ANC_BASE + 0x4), //MSG_DSP2MCU_ANC_START_DONE
    MSG_DSP2MCU_COMMON_ANC_RAMP_DONE  =                     (MSG_MCU2DSP_ANC_BASE + 0x5),
    MSG_DSP2MCU_ANC_RELAY_CMD         =                     (MSG_MCU2DSP_ANC_BASE + 0x6),
} mcu2dsp_audio_msg_t;

#define AUDIO_CCNI_MESSAGE_ACK(ccni_msg)    (ccni_msg | 0x8000)

#ifdef __cplusplus
}
#endif

#endif /*__HAL_AUDIO_CM4_DSP_MESSAGE_H__ */