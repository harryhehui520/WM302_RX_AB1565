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

#if defined(AIR_CELT_DEC_V2_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "dsp_feature_interface.h"
#include "dsp_audio_process.h"
#include "celt_dec_interface_v2.h"
#include "dsp_dump.h"
#include "bt_types.h"
#include "assert.h"
#include "sink_inter.h"
#include "source_inter.h"
#include "memory_attribute.h"
#include "preloader_pisplit.h"
#ifdef AIR_BT_CELT_USE_PIC
#include "celt_portable.h"
#endif /* AIR_BT_CELT_USE_PIC */

/* Private define ------------------------------------------------------------*/
#define CELT_PLC_MUTE_OUT_THD        5

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static celt_dec_port_para_t celt_dec_port_para[CELT_DEC_PORT_MAX];

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
ATTR_TEXT_IN_IRAM static celt_dec_port_para_t *stream_codec_decoder_celt_v2_find_out_port(DSP_STREAMING_PARA_PTR stream_ptr)
{
    uint32_t i, j;
    celt_dec_port_para_t *celt_dec_port = NULL;

    for (i = 0; i < CELT_DEC_PORT_MAX; i++) {
        for (j = 0; j < CELT_DEC_USER_COUNT; j++) {
            /* Check if this source or sink has already be regitsered into this index */
            if ((celt_dec_port_para[i].user[j] == stream_ptr->source) ||
                (celt_dec_port_para[i].user[j] == stream_ptr->sink)) {
                celt_dec_port = &celt_dec_port_para[i];
                goto FIND_DECODER_PORT;
            }
        }
    }
    if (celt_dec_port == NULL) {
        AUDIO_ASSERT(0);
        return celt_dec_port;
    }

FIND_DECODER_PORT:
    return celt_dec_port;
}

ATTR_TEXT_IN_IRAM static void stream_codec_decoder_celt_v2_memset_all_zero(uint8_t *out_buf, uint32_t out_data_size)
{
    uint32_t j;

    for (j = 0; j < out_data_size/sizeof(uint32_t); j++) {
        *((uint32_t *)out_buf + j) = 0;
    }
    if (out_data_size%sizeof(uint32_t) == 0)
    {
        /* do nothing */
    }
    else if (out_data_size%sizeof(uint32_t) == 2)
    {
        *((uint16_t *)(out_buf + out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = 0;
    }
    else
    {
        AUDIO_ASSERT(0);
    }
}

/* Public functions ----------------------------------------------------------*/
celt_dec_status_t stream_codec_decoder_celt_v2_init(celt_dec_port_t port, void *user, celt_dec_port_config_t *config)
{
    uint32_t saved_mask;
    int32_t i;
    void **p_user = NULL;

    if (port >= CELT_DEC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (celt_dec_port_para[port].count == 0) {
        /* update status */
        celt_dec_port_para[port].status = CELT_DEC_PORT_STATUS_INIT;

        /* config codec informations */
        celt_dec_port_para[port].sample_rate = config->sample_rate;
        celt_dec_port_para[port].sample_bits = config->sample_bits;
        celt_dec_port_para[port].bit_rate    = config->bit_rate;
        celt_dec_port_para[port].channel_mode = config->channel_mode;
        celt_dec_port_para[port].frame_samples = config->frame_samples;
        celt_dec_port_para[port].frame_interval = config->frame_interval;
        celt_dec_port_para[port].frame_size = config->frame_size;
        celt_dec_port_para[port].plc_enable = config->plc_enable;
        celt_dec_port_para[port].in_channel_num = config->in_channel_num;
        celt_dec_port_para[port].out_channel_num = config->out_channel_num;
        if (celt_dec_port_para[port].channel_mode == CELT_DEC_CHANNEL_MODE_MONO) {
            if (celt_dec_port_para[port].in_channel_num != 1) {
                AUDIO_ASSERT(0);
            }
        } else if (celt_dec_port_para[port].channel_mode == CELT_DEC_CHANNEL_MODE_STEREO) {
            if ((celt_dec_port_para[port].in_channel_num != 1) || (celt_dec_port_para[port].out_channel_num != 2)) {
                AUDIO_ASSERT(0);
            }
        } else if (celt_dec_port_para[port].channel_mode == CELT_DEC_CHANNEL_MODE_MULTI_MONO) {
            if (celt_dec_port_para[port].in_channel_num != celt_dec_port_para[port].out_channel_num) {
                AUDIO_ASSERT(0);
            }
        } else if (celt_dec_port_para[port].channel_mode == CELT_DEC_CHANNEL_MODE_MULTI_STEREO) {
            if ((celt_dec_port_para[port].in_channel_num*2) != celt_dec_port_para[port].out_channel_num) {
                AUDIO_ASSERT(0);
            }
        }
    }

    /* increase status count */
    celt_dec_port_para[port].count += 1;
    if (celt_dec_port_para[port].count == 0) {
        AUDIO_ASSERT(0);
    }

    /* register this user into this port */
    for (i = CELT_DEC_USER_COUNT - 1; i >= 0; i--) {
        if (celt_dec_port_para[port].user[i] == user) {
            p_user = &(celt_dec_port_para[port].user[i]);
            break;
        } else if (celt_dec_port_para[port].user[i] == NULL) {
            p_user = &(celt_dec_port_para[port].user[i]);
        }
    }
    if (p_user != NULL) {
        *p_user = user;
    } else {
        AUDIO_ASSERT(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);

    return CELT_DEC_STATUS_OK;
}

celt_dec_status_t stream_codec_decoder_celt_v2_deinit(celt_dec_port_t port, void *user)
{
    uint32_t saved_mask;
    int32_t i;
    bool mem_flag = false;
    void *WorkMemPtr = NULL;
    void **p_user = NULL;

    if (port >= CELT_DEC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    /* decrease status count */
    if (celt_dec_port_para[port].count == 0) {
        AUDIO_ASSERT(0);
    }
    celt_dec_port_para[port].count -= 1;

    if (celt_dec_port_para[port].count == 0) {
        /* reset codec informations */
        celt_dec_port_para[port].sample_rate = 0;
        celt_dec_port_para[port].sample_bits = 0;
        celt_dec_port_para[port].bit_rate    = 0;
        celt_dec_port_para[port].channel_mode = 0;
        celt_dec_port_para[port].frame_samples = 0;
        celt_dec_port_para[port].frame_interval = 0;
        celt_dec_port_para[port].frame_size = 0;
        celt_dec_port_para[port].plc_enable = 0;
        celt_dec_port_para[port].in_channel_num = 0;
        celt_dec_port_para[port].out_channel_num = 0;
        celt_dec_port_para[port].work_buffer_size = 0;
        WorkMemPtr   = celt_dec_port_para[port].work_mem_ptr;
        celt_dec_port_para[port].work_mem_ptr = NULL;

        /* set memory operation flag */
        mem_flag = true;
    }

    /* unregister this user into this port */
    for (i = CELT_DEC_USER_COUNT - 1; i >= 0; i--) {
        if (celt_dec_port_para[port].user[i] == user) {
            p_user = &(celt_dec_port_para[port].user[i]);
            break;
        }
    }
    if (p_user != NULL) {
        *p_user = NULL;
    } else {
        AUDIO_ASSERT(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);

    if (mem_flag) {
        /* free working memory */
        if (WorkMemPtr) {
            preloader_pisplit_free_memory(WorkMemPtr);
        }
    }

    return CELT_DEC_STATUS_OK;
}

bool stream_codec_decoder_celt_v2_initialize(void *para)
{
    uint32_t i;
    celt_dec_port_para_t *celt_dec_port;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    uint32_t saved_mask;
    void *work_mem;
    void **instance;
    int32_t celt_ret;
    int32_t skip;

    /* find out which port is belong to this stream */
    celt_dec_port = stream_codec_decoder_celt_v2_find_out_port(stream_ptr);

    /* status check */
    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
    if (celt_dec_port->status == CELT_DEC_PORT_STATUS_INIT) {
        celt_dec_port->status = CELT_DEC_PORT_STATUS_RUNNING;
    } else if (celt_dec_port->status == CELT_DEC_PORT_STATUS_RUNNING) {
        hal_nvic_restore_interrupt_mask(saved_mask);
        return false;
    } else {
        DSP_MW_LOG_I("[celt][dec] error status:%d", 1, celt_dec_port->status);
        AUDIO_ASSERT(0);
        return true;
    }
    hal_nvic_restore_interrupt_mask(saved_mask);

   /* get working memory and do decoder init */
    switch (celt_dec_port->channel_mode) {
        /* mono-channel mode */
        case CELT_DEC_CHANNEL_MODE_MONO:
        case CELT_DEC_CHANNEL_MODE_MULTI_MONO:
            /* get working memory */
            celt_dec_port->work_instance_count = celt_dec_port->in_channel_num;
            celt_dec_port->work_buffer_size = celt_decode_get_size(celt_dec_port->sample_rate, 1, celt_dec_port->frame_samples, (int)stream_codec_celt_get_version());
            /* 8byte-align */
            celt_dec_port->work_buffer_size = (celt_dec_port->work_buffer_size + 7) / 8 * 8;
            /* first word is used for plc count, second word is used for instance */
            celt_dec_port->work_buffer_size += (sizeof(uint32_t) + sizeof(void *));
            celt_dec_port->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, celt_dec_port->work_buffer_size * celt_dec_port->work_instance_count);
            if (celt_dec_port->work_mem_ptr == NULL) {
                AUDIO_ASSERT(0);
            }
            /* decoder init one by one channel */
            for (i = 0; i < celt_dec_port->work_instance_count; i++) {
                /* plc count init */
                *((uint32_t *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size)) = CELT_PLC_MUTE_OUT_THD;
                /* decoder init */
                instance = (void **)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t));
                work_mem = (void *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t) + sizeof(void *));
                celt_ret = celt_decode_init(instance, work_mem, celt_dec_port->sample_rate, 1, celt_dec_port->frame_samples, &skip, celt_dec_port->frame_size, (int)stream_codec_celt_get_version());
                if (0 != celt_ret) {
                    DSP_MW_LOG_I("[CELT_DEC] Init Fail, %d!", 1, celt_ret);
                    AUDIO_ASSERT(0);
                }
            }
            break;

        /* stereo-channel mode */
        case CELT_DEC_CHANNEL_MODE_STEREO:
        case CELT_DEC_CHANNEL_MODE_MULTI_STEREO:
            /* get working memory */
            celt_dec_port->work_instance_count = celt_dec_port->in_channel_num;
            celt_dec_port->work_buffer_size = celt_decode_get_size(celt_dec_port->sample_rate, 2, celt_dec_port->frame_samples, (int)stream_codec_celt_get_version());
            /* 8byte-align */
            celt_dec_port->work_buffer_size = (celt_dec_port->work_buffer_size + 7) / 8 * 8;
            /* first word is used for plc count, second word is used for instance */
            celt_dec_port->work_buffer_size += (sizeof(uint32_t) + sizeof(void *));
            celt_dec_port->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, celt_dec_port->work_buffer_size * celt_dec_port->work_instance_count);
            if (celt_dec_port->work_mem_ptr == NULL) {
                AUDIO_ASSERT(0);
            }
            /* decoder init one by one channel */
            for (i = 0; i < celt_dec_port->work_instance_count; i++) {
                /* plc count init */
                *((uint32_t *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size)) = CELT_PLC_MUTE_OUT_THD;
                /* decoder init */
                instance = (void **)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t));
                work_mem = (void *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t) + sizeof(void *));
                celt_ret = celt_decode_init(instance, work_mem, celt_dec_port->sample_rate, 2, celt_dec_port->frame_samples, &skip, celt_dec_port->frame_size, (int)stream_codec_celt_get_version());
                if (0 != celt_ret) {
                    DSP_MW_LOG_I("[CELT_DEC] Init Fail, %d!", 1, celt_ret);
                    AUDIO_ASSERT(0);
                }
            }
            break;

        default:
            AUDIO_ASSERT(0);
            break;
    }

    DSP_MW_LOG_I("[celt][dec] init done, working mem = %d, 0x%x, version = 0x%8x", 3, celt_dec_port->work_buffer_size, celt_dec_port->work_mem_ptr, celt_codec_get_version());

    return false;
}

ATTR_TEXT_IN_IRAM bool stream_codec_decoder_celt_v2_process(void *para)
{
    uint32_t i, j;
    celt_dec_port_para_t *celt_dec_port;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    uint8_t *in_buf1;
    uint8_t *out_buf1;
    uint8_t *out_buf2;
    uint32_t in_frame_size;
    uint32_t out_data_size;
    uint32_t out_samples;
    uint32_t total_out_data_size;
    uint32_t frame_num;
    uint32_t currnet_frame;
    void *work_mem;
    void **instance;
    celt_dec_frame_status_t *p_frame_status;
    uint32_t *p_plc_count;
    int32_t celt_ret;

    /* find out which port is belong to this stream */
    celt_dec_port = stream_codec_decoder_celt_v2_find_out_port(stream_ptr);

    in_frame_size = stream_codec_get_input_size(para);
    if (in_frame_size == 0) {
        /* config output size */
        stream_codec_modify_output_size(para, in_frame_size);

        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_dec_port->finish_gpt_count);

        return false;
    }

    if ((in_frame_size % (celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t))) != 0) {
        AUDIO_ASSERT(0);
        return true;
    }

    /* do decoder processs */
    switch (celt_dec_port->channel_mode) {
        case CELT_DEC_CHANNEL_MODE_MONO:
        case CELT_DEC_CHANNEL_MODE_MULTI_MONO:
            frame_num = in_frame_size / (celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t));
            /* process each channel one by one */
            for (i = 0; i < celt_dec_port->work_instance_count; i++) {
                total_out_data_size = 0;
                /* get instance and working memory and plc count of this channel */
                p_plc_count = (uint32_t *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size);
                instance = (void **)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t));
                work_mem = (void *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t) + sizeof(void *));
                for (currnet_frame = 0; currnet_frame < frame_num; currnet_frame++) {
                    out_samples = celt_dec_port->frame_samples;
                    if (celt_dec_port->sample_bits == 16)
                    {
                        out_data_size = out_samples * sizeof(uint16_t);
                    }
                    else
                    {
                        AUDIO_ASSERT(0);
                        return true;
                    }
                    /* get frame status and input and output buffer of this frame */
                    p_frame_status = (celt_dec_frame_status_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * ((celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t) + 3) / 4 * 4));
                    in_buf1  = (uint8_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * ((celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t) + 3) / 4 * 4) + sizeof(celt_dec_frame_status_t));
                    out_buf1 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i + 1) + total_out_data_size);
                    /* frame status check */
                    if (*p_frame_status == CELT_DEC_FRAME_STATUS_NORMAL) {
                        celt_ret = celt_decode_prcs(*instance, in_buf1, celt_dec_port->frame_size, (int16_t*)out_buf1, celt_dec_port->frame_samples, 0);
                        if ((int32_t)out_samples != celt_ret) {
                            DSP_MW_LOG_I("[CELT_DEC] Process Fail! %d", 1, celt_ret);
                            /* do PLC for avoid this error */
                            *p_frame_status = CELT_DEC_FRAME_STATUS_PLC;
                            // AUDIO_ASSERT(0);
                        } else {
                            *p_plc_count = 0;
                        }
                    }
                    if (*p_frame_status == CELT_DEC_FRAME_STATUS_PLC) {
                        if ((celt_dec_port->plc_enable == 0) || (*p_plc_count >= CELT_PLC_MUTE_OUT_THD)) {
                            stream_codec_decoder_celt_v2_memset_all_zero(out_buf1, out_data_size);
                        } else {
                            celt_ret = celt_decode_prcs(*instance, in_buf1, celt_dec_port->frame_size, (int16_t*)out_buf1, celt_dec_port->frame_samples, 1);
                            if ((int32_t)out_samples != celt_ret) {
                                DSP_MW_LOG_I("[CELT_DEC] PLC Process Fail! %d", 1, celt_ret);
                                stream_codec_decoder_celt_v2_memset_all_zero(out_buf1, out_data_size);
                            }
                            *p_plc_count = (*p_plc_count) + 1;
                        }
                    } else if (*p_frame_status == CELT_DEC_FRAME_STATUS_BYPASS_DECODER) {
                        /* there is a requirement that the decoder do not output any data */
                        out_data_size = 0;
                        // DSP_MW_LOG_I("[CELT_DEC] decoder output is 0!", 0);
                    }
                    /* update total output size */
                    total_out_data_size += out_data_size;
                }
            }
            if ((celt_dec_port->channel_mode == CELT_DEC_CHANNEL_MODE_MONO) && (celt_dec_port->out_channel_num > 1))
            {
                /* copy mono data into other channels */
                out_buf1 = (uint8_t *)(uint32_t)stream_codec_get_output_buffer(para, 1);
                for (i = 0; i < celt_dec_port->out_channel_num - 1; i++) {
                    out_buf2 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i + 2));
                    for (j = 0; j < total_out_data_size/sizeof(uint32_t); j++) {
                        *((uint32_t *)out_buf2 + j) = *((uint32_t *)out_buf1 + j);
                    }
                    if (total_out_data_size%sizeof(uint32_t) == 0)
                    {
                        /* do nothing */
                    }
                    else if (total_out_data_size%sizeof(uint32_t) == 2)
                    {
                        *((uint16_t *)(out_buf2 + total_out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = *((uint16_t *)(out_buf1 + total_out_data_size/sizeof(uint32_t)*sizeof(uint32_t)));
                    }
                    else
                    {
                        AUDIO_ASSERT(0);
                    }
                }
            }
            break;

        case CELT_DEC_CHANNEL_MODE_STEREO:
        case CELT_DEC_CHANNEL_MODE_MULTI_STEREO:
            frame_num = in_frame_size / (celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t));
            /* process each channel one by one */
            for (i = 0; i < celt_dec_port->work_instance_count; i++) {
                total_out_data_size = 0;
                /* get instance and working memory and plc count of this channel */
                p_plc_count = (uint32_t *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size);
                instance = (void **)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t));
                work_mem = (void *)((uint32_t)(celt_dec_port->work_mem_ptr) + i * celt_dec_port->work_buffer_size + sizeof(uint32_t) * 2);
                for (currnet_frame = 0; currnet_frame < frame_num; currnet_frame++) {
                    out_samples = celt_dec_port->frame_samples;
                    if (celt_dec_port->sample_bits == 16)
                    {
                        out_data_size = out_samples * sizeof(uint16_t);
                    }
                    else
                    {
                        AUDIO_ASSERT(0);
                        return true;
                    }
                    /* get frame status and input and output buffer of this frame */
                    p_frame_status = (celt_dec_frame_status_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * (celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t)));
                    in_buf1  = (uint8_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * (celt_dec_port->frame_size + sizeof(celt_dec_frame_status_t)) + sizeof(celt_dec_frame_status_t));
                    out_buf1 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i*2 + 1) + total_out_data_size);
                    out_buf2 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i*2 + 2) + total_out_data_size);
                    /* frame status check */
                    if (*p_frame_status == CELT_DEC_FRAME_STATUS_NORMAL) {
                        celt_ret = celt_decode_prcs(*instance, in_buf1, celt_dec_port->frame_size, (int16_t*)out_buf1, celt_dec_port->frame_samples, 0);
                        if ((int32_t)out_samples != celt_ret) {
                            DSP_MW_LOG_I("[CELT_DEC] Process Fail! %d", 1, celt_ret);
                            /* do PLC for avoid this error */
                            *p_frame_status = CELT_DEC_FRAME_STATUS_PLC;
                            // AUDIO_ASSERT(0);
                        } else {
                            *p_plc_count = 0;
                        }
                    }
                    if (*p_frame_status == CELT_DEC_FRAME_STATUS_PLC) {
                        if ((celt_dec_port->plc_enable == 0) || (*p_plc_count >= CELT_PLC_MUTE_OUT_THD)) {
                            stream_codec_decoder_celt_v2_memset_all_zero(out_buf1, out_data_size*2);
                        } else {
                            celt_ret = celt_decode_prcs(*instance, in_buf1, celt_dec_port->frame_size, (int16_t*)out_buf1, celt_dec_port->frame_samples, 1);
                            if ((int32_t)out_samples != celt_ret) {
                                DSP_MW_LOG_I("[CELT_DEC] PLC Process Fail! %d", 1, celt_ret);
                                stream_codec_decoder_celt_v2_memset_all_zero(out_buf1, out_data_size*2);
                            }
                            *p_plc_count = (*p_plc_count) + 1;
                        }
                    } else if (*p_frame_status == CELT_DEC_FRAME_STATUS_BYPASS_DECODER) {
                        /* there is a requirement that the decoder do not output any data */
                        out_data_size = 0;
                        // DSP_MW_LOG_I("[CELT_DEC] decoder output is 0!", 0);
                    }
                    /* split L/R data into stream buffer ch1 and stream buffer ch2  */
                    for (j = 0; j < out_samples; j++)
                    {
                        if (celt_dec_port->sample_bits == 16)
                        {
                            *((uint16_t *)out_buf2 + j) = *((uint16_t *)out_buf1 + 2*j + 1);
                            *((uint16_t *)out_buf1 + j) = *((uint16_t *)out_buf1 + 2*j);
                        }
                    }
                    /* update total output size */
                    total_out_data_size += out_data_size;
                }
            }
            break;

        default:
            AUDIO_ASSERT(0);
            break;
    }

    stream_codec_modify_output_samplingrate(para, celt_dec_port->sample_rate / 1000);
    stream_codec_modify_output_size(para, total_out_data_size);
    if (celt_dec_port->sample_bits == 16)
    {
        stream_codec_modify_resolution(para, RESOLUTION_16BIT);
    }
    else if ((celt_dec_port->sample_bits == 24) || (celt_dec_port->sample_bits == 32))
    {
        AUDIO_ASSERT(0);
    }

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_dec_port->finish_gpt_count);

    return false;
}

#endif /* AIR_CELT_DEC_V2_ENABLE */
