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

#ifndef _CELT_ENC_INTERFACE_V2_H_
#define _CELT_ENC_INTERFACE_V2_H_

#if defined(AIR_CELT_ENC_V2_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "dsp_utilities.h"
#include "dsp_buffer.h"
#include "dsp_feature_interface.h"

/* Public define -------------------------------------------------------------*/
#define CELT_ENC_USER_COUNT       4
#define CELT_ENC_MIPS_DEBUG       0

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    CELT_ENC_STATUS_ERROR = 0,
    CELT_ENC_STATUS_OK = 1
} celt_enc_status_t;

typedef enum {
    CELT_ENC_PORT_0,
    CELT_ENC_PORT_MAX,
} celt_enc_port_t;

typedef enum {
    CELT_ENC_PORT_STATUS_DEINIT = 0,
    CELT_ENC_PORT_STATUS_INIT = 1,
    CELT_ENC_PORT_STATUS_RUNNING = 2
} celt_enc_port_status_t;

typedef enum {
    CELT_ENC_CHANNEL_MODE_MONO = 0,
    CELT_ENC_CHANNEL_MODE_STEREO,
    CELT_ENC_CHANNEL_MODE_MULTI_MONO,
    CELT_ENC_CHANNEL_MODE_MULTI_STEREO,
} celt_enc_channel_mode_t;

typedef struct {
    uint16_t sample_bits;
    uint16_t channel_num;
    uint32_t sample_rate;
    uint32_t bit_rate;
    uint32_t frame_interval;
    uint32_t frame_samples;
    uint32_t in_frame_size;
    uint32_t out_frame_size;
    uint16_t process_frame_num;
    celt_enc_channel_mode_t channel_mode;
    int32_t complexity;
} celt_enc_port_config_t;

typedef struct {
    uint8_t enc_count;
    celt_enc_port_status_t status;
    uint16_t sample_bits;
    uint16_t channel_num;
    uint32_t sample_rate;
    uint32_t bit_rate;
    uint32_t frame_interval;
    uint32_t frame_samples;
    celt_enc_channel_mode_t channel_mode;
    int32_t complexity;
    uint32_t in_frame_size;
    uint32_t out_frame_size;
    uint16_t total_output_size;
    uint16_t process_frame_num;
    uint16_t work_buffer_size;
    uint16_t remain_buffer_size;
    void    *work_mem_ptr;
    void    *remain_mem_ptr;
    uint32_t finish_gpt_count;
#if CELT_ENC_MIPS_DEBUG
    uint32_t process_start_gpt_count;
    uint32_t process_finish_gpt_count;
#endif /* CELT_ENC_MIPS_DEBUG */
    void    *user[CELT_ENC_USER_COUNT];
} celt_enc_port_para_t;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern celt_enc_status_t stream_codec_encoder_celt_v2_init(celt_enc_port_t port, void *user, celt_enc_port_config_t *config);
extern celt_enc_status_t stream_codec_encoder_celt_v2_deinit(celt_enc_port_t port, void *user);
extern celt_enc_status_t stream_codec_encoder_celt_v2_get_data_info(celt_enc_port_t port, uint32_t channel, uint8_t **in_buffer_address, uint32_t *in_frame_size);
extern celt_enc_status_t stream_codec_encoder_celt_v2_get_finish_gpt_count(celt_enc_port_t port, uint32_t *gpt_count);
#if CELT_ENC_MIPS_DEBUG
extern celt_enc_status_t stream_codec_encoder_celt_v2_get_process_gpt_count(celt_enc_port_t port, uint32_t *start_count, uint32_t *finish_count);
#endif /* CELT_ENC_MIPS_DEBUG */
extern bool stream_codec_encoder_celt_v2_initialize(void *para);
extern bool stream_codec_encoder_celt_v2_process(void *para);

#endif /* AIR_CELT_ENC_V2_ENABLE */

#endif /* _CELT_ENC_INTERFACE_V2_H_ */
