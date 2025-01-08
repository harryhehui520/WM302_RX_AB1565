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

#ifndef _LC3PLUS_ENC_INTERFACE_H_
#define _LC3PLUS_ENC_INTERFACE_H_

#if defined(AIR_BT_LE_LC3PLUS_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "lc3plus_codec_api.h"

/* Public define -------------------------------------------------------------*/
#define LC3PLUS_ENC_USER_COUNT       4
#define LC3PLUS_ENC_MIPS_DEBUG       0

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    LC3PLUS_ENC_STATUS_ERROR = 0,
    LC3PLUS_ENC_STATUS_OK = 1
} lc3plus_enc_status_t;

typedef enum {
    LC3PLUS_ENC_PORT_0,
    LC3PLUS_ENC_PORT_MAX,
} lc3plus_enc_port_t;

typedef enum {
    LC3PLUS_ENC_PORT_STATUS_DEINIT = 0,
    LC3PLUS_ENC_PORT_STATUS_INIT = 1,
    LC3PLUS_ENC_PORT_STATUS_RUNNING = 2
} lc3plus_enc_port_status_t;

typedef enum {
    LC3PLUS_ENC_CHANNEL_MODE_MONO = 0,
    LC3PLUS_ENC_CHANNEL_MODE_STEREO,
    LC3PLUS_ENC_CHANNEL_MODE_MULTI
} lc3plus_enc_channel_mode_t;

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
    lc3plus_enc_channel_mode_t channel_mode;
    LC3PLUS_Architecture codec_mode;
} lc3plus_enc_config_t;

typedef struct {
    uint8_t enc_count;
    lc3plus_enc_port_status_t status;
    uint16_t sample_bits;
    uint16_t channel_num;
    uint32_t sample_rate;
    uint32_t bit_rate_old;
    uint32_t bit_rate_new;
    uint32_t frame_interval;
    uint32_t frame_samples;
    lc3plus_enc_channel_mode_t channel_mode;
    LC3PLUS_Architecture codec_mode;
    uint32_t in_frame_size;
    uint16_t out_frame_size;
    uint16_t process_frame_num;
    uint16_t work_buffer_size;
    uint16_t remain_buffer_size;
    void    *work_mem_ptr;
    void    *remain_mem_ptr;
    uint32_t finish_gpt_count;
#if LC3PLUS_ENC_MIPS_DEBUG
    uint32_t process_start_gpt_count;
    uint32_t process_finish_gpt_count;
#endif /* LC3PLUS_ENC_MIPS_DEBUG */
    void    *user[LC3PLUS_ENC_USER_COUNT];
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    uint32_t tab_common_buffer_size;
    void    *tab_common_mem_ptr;
    uint32_t tab_enc_buffer_size;
    void    *tab_enc_mem_ptr;
    LC3PLUS_Param enc_t;
#endif
} lc3plus_enc_para_t;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern lc3plus_enc_status_t stream_codec_encoder_lc3plus_init(lc3plus_enc_port_t port, void *user, lc3plus_enc_config_t *config);
extern lc3plus_enc_status_t stream_codec_encoder_lc3plus_deinit(lc3plus_enc_port_t port, void *user);
extern lc3plus_enc_status_t stream_codec_encoder_lc3plus_get_data_info(lc3plus_enc_port_t port, uint32_t channel, uint8_t **in_buffer_address, uint32_t *in_frame_size);
extern lc3plus_enc_status_t stream_codec_encoder_lc3plus_set_bitrate(lc3plus_enc_port_t port, uint32_t bitrate);
extern lc3plus_enc_status_t stream_codec_encoder_lc3plus_get_finish_gpt_count(lc3plus_enc_port_t port, uint32_t *gpt_count);
#if LC3PLUS_ENC_MIPS_DEBUG
extern lc3plus_enc_status_t stream_codec_encoder_lc3plus_get_process_gpt_count(lc3plus_enc_port_t port, uint32_t *start_count, uint32_t *finish_count);
#endif /* LC3PLUS_ENC_MIPS_DEBUG */
extern bool stream_codec_encoder_lc3plus_initialize(void *para);
extern bool stream_codec_encoder_lc3plus_process(void *para);

#endif /* AIR_BT_LE_LC3PLUS_ENABLE */

#endif /* _LC3PLUS_ENC_INTERFACE_H_ */
