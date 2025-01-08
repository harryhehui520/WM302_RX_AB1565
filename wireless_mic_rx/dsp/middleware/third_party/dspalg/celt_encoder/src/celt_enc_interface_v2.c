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

#if defined(AIR_CELT_ENC_V2_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "assert.h"
#include "dsp_feature_interface.h"
#include "dsp_audio_process.h"
#include "dsp_dump.h"
#include "sink_inter.h"
#include "source_inter.h"
#include "memory_attribute.h"
#include "preloader_pisplit.h"
#include "celt_enc_interface_v2.h"
#ifdef AIR_BT_CELT_USE_PIC
#include "celt_portable.h"
#endif /* AIR_BT_CELT_USE_PIC */

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static celt_enc_port_para_t celt_enc_port_para[CELT_ENC_PORT_MAX];

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
ATTR_TEXT_IN_IRAM static celt_enc_port_para_t *stream_codec_encoder_celt_v2_find_out_port(DSP_STREAMING_PARA_PTR stream_ptr)
{
    uint32_t i, j;
    celt_enc_port_para_t *celt_port = NULL;

    for (i = 0; i < CELT_ENC_PORT_MAX; i++) {
        for (j = 0; j < CELT_ENC_USER_COUNT; j++) {
            /* Check if this source or sink has already be regitsered into this port */
            if ((celt_enc_port_para[i].user[j] == stream_ptr->source) ||
                (celt_enc_port_para[i].user[j] == stream_ptr->sink)) {
                celt_port = &celt_enc_port_para[i];
                goto FIND_ENCODER_PORT;
            }
        }
    }
    if (celt_port == NULL) {
        AUDIO_ASSERT(0);
    }

FIND_ENCODER_PORT:
    return celt_port;
}

ATTR_TEXT_IN_IRAM static void stream_codec_encoder_celt_v2_copy_mono_16bit_data_into_remain_buffer(uint8_t *in_buf, uint8_t *remain_mem, uint32_t in_frame_size)
{
    uint32_t j;

    for (j = 0; j < in_frame_size / sizeof(uint32_t); j++) {
        *((uint32_t *)remain_mem + j) = *((uint32_t *)in_buf + j);
    }
    if ((in_frame_size % sizeof(uint32_t)) == 0)
    {
        /* do nothing */
    }
    else if ((in_frame_size % sizeof(uint32_t)) == 2)
    {
        /* sample is 32bit or 16bit, so in here it means sample num is odd and sample is 16bit */
        *((uint16_t *)(remain_mem+in_frame_size/sizeof(uint32_t)*sizeof(uint32_t))) = *((uint16_t *)(in_buf+in_frame_size/sizeof(uint32_t)*sizeof(uint32_t))) ;
    }
    else
    {
        AUDIO_ASSERT(0);
    }
}

ATTR_TEXT_IN_IRAM static void stream_codec_encoder_celt_v2_copy_stereo_16bit_data_into_remain_buffer(uint8_t *in_buf1, uint8_t *in_buf2, uint8_t *remain_mem, uint32_t in_frame_size)
{
    uint32_t j;

    for (j = 0; j < in_frame_size / sizeof(uint16_t); j++)
    {
        *((uint16_t *)remain_mem + 2*j) = *((uint16_t *)in_buf1 + j);
        *((uint16_t *)remain_mem + 2*j + 1) = *((uint16_t *)in_buf2 + j);
    }
}

/* Public functions ----------------------------------------------------------*/
celt_enc_status_t stream_codec_encoder_celt_v2_init(celt_enc_port_t port, void *user, celt_enc_port_config_t *config)
{
    uint32_t saved_mask;
    int32_t i;
    void **p_user = NULL;

    if (port >= CELT_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (celt_enc_port_para[port].enc_count == 0) {
        /* update status */
        celt_enc_port_para[port].status = CELT_ENC_PORT_STATUS_INIT;

        /* config celt codec */
        celt_enc_port_para[port].sample_bits = config->sample_bits;
        celt_enc_port_para[port].channel_num = config->channel_num;
        if ((config->sample_rate != 48000) && (config->sample_rate != 16000))
        {
            DSP_MW_LOG_I("[celt][enc] error sample rate:%d", 1, config->sample_rate);
            AUDIO_ASSERT(FALSE);
        }
        celt_enc_port_para[port].sample_rate = config->sample_rate;
        celt_enc_port_para[port].bit_rate = config->bit_rate;
        celt_enc_port_para[port].frame_interval = config->frame_interval;
        celt_enc_port_para[port].frame_samples = config->frame_samples;
        celt_enc_port_para[port].channel_mode = config->channel_mode;
        celt_enc_port_para[port].complexity = config->complexity;
        celt_enc_port_para[port].process_frame_num = config->process_frame_num;
        celt_enc_port_para[port].in_frame_size = config->in_frame_size;
        celt_enc_port_para[port].out_frame_size = config->out_frame_size;
        celt_enc_port_para[port].total_output_size = 0;

        /* get remain samples memory */
        celt_enc_port_para[port].remain_buffer_size = config->in_frame_size*config->process_frame_num;
    }

    /* increase status count */
    celt_enc_port_para[port].enc_count += 1;
    if (celt_enc_port_para[port].enc_count == 0) {
        AUDIO_ASSERT(0);
    }

    /* register this user into this port */
    for (i = CELT_ENC_USER_COUNT - 1; i >= 0; i--) {
        if (celt_enc_port_para[port].user[i] == user) {
            p_user = &(celt_enc_port_para[port].user[i]);
            break;
        } else if (celt_enc_port_para[port].user[i] == NULL) {
            p_user = &(celt_enc_port_para[port].user[i]);
        }
    }
    if (p_user != NULL) {
        *p_user = user;
    } else {
        AUDIO_ASSERT(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);

    return CELT_ENC_STATUS_OK;
}

celt_enc_status_t stream_codec_encoder_celt_v2_deinit(celt_enc_port_t port, void *user)
{
    uint32_t saved_mask;
    int32_t i;
    bool mem_flag = false;
    void *WorkMemPtr = NULL;
    void *RemainMemPtr = NULL;
    void **p_user = NULL;

    if (port >= CELT_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    /* decrease status count */
    if (celt_enc_port_para[port].enc_count == 0) {
        AUDIO_ASSERT(0);
    }
    celt_enc_port_para[port].enc_count -= 1;

    if (celt_enc_port_para[port].enc_count == 0) {
        /* update status */
        celt_enc_port_para[port].status = CELT_ENC_PORT_STATUS_DEINIT;

        /* reset celt codec */
        celt_enc_port_para[port].sample_bits = 0;
        celt_enc_port_para[port].channel_num = 0;
        celt_enc_port_para[port].sample_rate = 0;
        celt_enc_port_para[port].bit_rate = 0;
        celt_enc_port_para[port].frame_interval = 0;
        celt_enc_port_para[port].frame_samples = 0;
        celt_enc_port_para[port].channel_mode = 0;
        celt_enc_port_para[port].complexity = 0;
        celt_enc_port_para[port].in_frame_size = 0;
        celt_enc_port_para[port].out_frame_size = 0;
        celt_enc_port_para[port].total_output_size = 0;
        celt_enc_port_para[port].work_buffer_size = 0;
        celt_enc_port_para[port].remain_buffer_size = 0;
        WorkMemPtr = celt_enc_port_para[port].work_mem_ptr;
        celt_enc_port_para[port].work_mem_ptr = NULL;
        RemainMemPtr = celt_enc_port_para[port].remain_mem_ptr;
        celt_enc_port_para[port].remain_mem_ptr = NULL;

        /* set memory operation flag */
        mem_flag = true;
    }

    /* unregister this user into this port */
    for (i = CELT_ENC_USER_COUNT - 1; i >= 0; i--) {
        if (celt_enc_port_para[port].user[i] == user) {
            p_user = &(celt_enc_port_para[port].user[i]);
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
        preloader_pisplit_free_memory(WorkMemPtr);

        /* free remain samples memory */
        preloader_pisplit_free_memory(RemainMemPtr);
    }

    return CELT_ENC_STATUS_OK;
}

celt_enc_status_t stream_codec_encoder_celt_v2_get_data_info(celt_enc_port_t port, uint32_t channel, uint8_t **in_buffer_address, uint32_t *in_frame_size)
{
    celt_enc_port_para_t *celt_para = NULL;

    if (port >= CELT_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    celt_para = &celt_enc_port_para[port];

    if ((channel > celt_para->channel_num) || (channel == 0)) {
        AUDIO_ASSERT(0);
    }

    *in_buffer_address = (uint8_t *)((uint32_t)celt_para->remain_mem_ptr + (channel - 1) * celt_para->remain_buffer_size);
    *in_frame_size = celt_para->in_frame_size;

    return CELT_ENC_STATUS_OK;
}

celt_enc_status_t stream_codec_encoder_celt_v2_get_finish_gpt_count(celt_enc_port_t port, uint32_t *gpt_count)
{
    if (port >= CELT_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    *gpt_count = celt_enc_port_para[port].finish_gpt_count;

    return CELT_ENC_STATUS_OK;
}

#if CELT_ENC_MIPS_DEBUG
celt_enc_status_t stream_codec_encoder_celt_v2_get_process_gpt_count(celt_enc_port_t port, uint32_t *start_count, uint32_t *finish_count)
{
    if (port >= CELT_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    *start_count = celt_enc_port_para[port].process_start_gpt_count;
    *finish_count = celt_enc_port_para[port].process_finish_gpt_count;

    return CELT_ENC_STATUS_OK;
}
#endif /* CELT_ENC_MIPS_DEBUG */

bool stream_codec_encoder_celt_v2_initialize(void *para)
{
    uint32_t i;
    uint32_t saved_mask;
    celt_enc_port_para_t *celt_para;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    int32_t ret;
    uint8_t *working_mem;
    void **instance;

    /* find out which port is belong to this stream */
    celt_para = stream_codec_encoder_celt_v2_find_out_port(stream_ptr);

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
    /* status check */
    if (celt_para->status == CELT_ENC_PORT_STATUS_INIT) {
        celt_para->status = CELT_ENC_PORT_STATUS_RUNNING;
    } else if (celt_para->status == CELT_ENC_PORT_STATUS_RUNNING) {
        hal_nvic_restore_interrupt_mask(saved_mask);
        return false;
    } else {
        DSP_MW_LOG_I("[celt][enc] error status:%d", 1, celt_para->status);
        AUDIO_ASSERT(FALSE);
        return true;
    }
    hal_nvic_restore_interrupt_mask(saved_mask);

    /* get sample memory */
    celt_para->remain_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, celt_para->remain_buffer_size * celt_para->channel_num);
    if (celt_para->remain_mem_ptr == NULL) {
        AUDIO_ASSERT(0);
    }

    if ((celt_para->channel_mode == CELT_ENC_CHANNEL_MODE_MONO) || (celt_para->channel_mode == CELT_ENC_CHANNEL_MODE_MULTI_MONO))
    {
        /* get codec working memory for mono channel */
        celt_para->work_buffer_size = celt_encode_get_size(celt_para->sample_rate, 1, celt_para->frame_samples, (int)stream_codec_celt_get_version());
        /* keep space for instance */
        celt_para->work_buffer_size += sizeof(void *);
        /* 4B aligned */
        celt_para->work_buffer_size = (celt_para->work_buffer_size + 3) / 4 * 4;
        celt_para->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, celt_para->work_buffer_size * celt_para->channel_num);
        if (celt_para->work_mem_ptr == NULL) {
            AUDIO_ASSERT(0);
        }
        /* do encoder init one by one channel */
        for (i = 0; i < celt_para->channel_num; i++) {
            instance = (void **)((uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size);
            working_mem = (uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size + sizeof(void *);
            ret = celt_encode_init(instance, working_mem, celt_para->sample_rate, 1, celt_para->frame_samples, celt_para->complexity, celt_para->out_frame_size, (int)stream_codec_celt_get_version());
            if (ret != 0) {
                DSP_MW_LOG_E("[celt][enc] init fail %d", 1, ret);
                AUDIO_ASSERT(0);
                return true;
            }
        }
    }
    else
    {
        /* get codec working memory for stereo channel */
        celt_para->work_buffer_size = celt_encode_get_size(celt_para->sample_rate, 2, celt_para->frame_samples, (int)stream_codec_celt_get_version());
        /* keep space for instance */
        celt_para->work_buffer_size += sizeof(void *);
        /* 4B aligned */
        celt_para->work_buffer_size = (celt_para->work_buffer_size + 3) / 4 * 4;
        celt_para->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, celt_para->work_buffer_size * (celt_para->channel_num/2));
        if (celt_para->work_mem_ptr == NULL) {
            AUDIO_ASSERT(0);
        }
        /* do encoder init one by one stereo-channel */
        for (i = 0; i < (celt_para->channel_num/2); i++) {
            instance = (void **)((uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size);
            working_mem = (uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size + sizeof(void *);
            ret = celt_encode_init(instance, working_mem, celt_para->sample_rate, 2, celt_para->frame_samples, celt_para->complexity, celt_para->out_frame_size, (int)stream_codec_celt_get_version());
            if (ret != 0) {
                DSP_MW_LOG_E("[celt][enc] init fail %d", 1, ret);
                AUDIO_ASSERT(0);
                return true;
            }
        }
    }

    DSP_MW_LOG_I("[celt][enc] init done, working mem = %d, 0x%x, version = 0x%8x", 3, celt_para->work_buffer_size, celt_para->work_mem_ptr, celt_codec_get_version());

    return false;
}

ATTR_TEXT_IN_IRAM bool stream_codec_encoder_celt_v2_process(void *para)
{
    uint32_t i, j;
    celt_enc_port_para_t *celt_para;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    uint8_t *in_buf;
    uint8_t *in_buf2;
    uint8_t *out_buf;
    uint16_t in_frame_size;
    uint8_t *remain_mem;
    uint8_t *working_mem;
    void **instance;
    uint32_t out_size;
    int32_t ret;

    /* find out which port is belong to this stream */
    celt_para = stream_codec_encoder_celt_v2_find_out_port(stream_ptr);

    in_frame_size = stream_codec_get_input_size(para);
    celt_para->in_frame_size = (U32)in_frame_size;
    if (in_frame_size == 0) {
        /* config output size */
        stream_codec_modify_output_size(para, in_frame_size);
        celt_para->total_output_size = in_frame_size;

        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_para->finish_gpt_count);

        return false;
    }

    switch (celt_para->channel_mode)
    {
        case CELT_ENC_CHANNEL_MODE_MONO:
        case CELT_ENC_CHANNEL_MODE_MULTI_MONO:
            /* do encoder one by one channel */
            for (i = 0; i < celt_para->channel_num; i++) {
                in_buf  = (uint8_t *)stream_codec_get_input_buffer(para, i + 1);
                out_buf = (uint8_t *)stream_codec_get_output_buffer(para, i + 1);
                remain_mem = (uint8_t *)((uint32_t)celt_para->remain_mem_ptr + i * celt_para->remain_buffer_size);
                instance = (void **)((uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size);
                working_mem = (uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size + sizeof(void *);

                /* copy data from stream buffer to remain buffer */
                if (in_frame_size > celt_para->remain_buffer_size) {
                    AUDIO_ASSERT(0);
                }
                if (stream_codec_get_input_resolution(para) == RESOLUTION_16BIT)
                {
                    stream_codec_encoder_celt_v2_copy_mono_16bit_data_into_remain_buffer(in_buf, remain_mem, in_frame_size);
                }
                else
                {
                    AUDIO_ASSERT(0);
                }

                /* do encoding */
                out_size = celt_para->out_frame_size;
                for (j = 0; j < celt_para->process_frame_num; j++)
                {
                    /* do encode and output to the stream buffer */
                    #if CELT_ENC_MIPS_DEBUG
                    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_para->process_start_gpt_count);
                    #endif /* CELT_ENC_MIPS_DEBUG */
                    ret = celt_encode_prcs(*instance, (const int16_t *)(remain_mem+(in_frame_size/celt_para->process_frame_num*j)), celt_para->frame_samples, (unsigned char *)(out_buf+j*out_size), out_size);
                    #if CELT_ENC_MIPS_DEBUG
                    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_para->process_finish_gpt_count);
                    #endif /* CELT_ENC_MIPS_DEBUG */
                    if ((uint32_t)ret != out_size) {
                        DSP_MW_LOG_E("[celt][enc] process fail %d, %d, %d, %d, %d, %d", 6, ret, out_size, in_frame_size, celt_para->frame_samples, celt_para->process_frame_num, j);
                        // AUDIO_ASSERT(0);
                        // return false;
                    }
                }
            }
            break;

        case CELT_ENC_CHANNEL_MODE_STEREO:
        case CELT_ENC_CHANNEL_MODE_MULTI_STEREO:
            /* stereo case */
            for (i = 0; i < (celt_para->channel_num/2); i++) {
                in_buf  = (uint8_t *)stream_codec_get_input_buffer(para, 2*i + 1);
                in_buf2 = (uint8_t *)stream_codec_get_input_buffer(para, 2*i + 2);
                out_buf = (uint8_t *)stream_codec_get_output_buffer(para, i + 1);
                remain_mem = (uint8_t *)((uint32_t)celt_para->remain_mem_ptr + i * celt_para->remain_buffer_size);
                instance = (void **)((uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size);
                working_mem = (uint8_t *)celt_para->work_mem_ptr + i * celt_para->work_buffer_size + sizeof(void *);

                /* copy data from stream buffer to remain buffer */
                if (in_frame_size*2 != celt_para->remain_buffer_size) {
                    AUDIO_ASSERT(0);
                }
                if (stream_codec_get_input_resolution(para) == RESOLUTION_16BIT)
                {
                    stream_codec_encoder_celt_v2_copy_stereo_16bit_data_into_remain_buffer(in_buf, in_buf2, remain_mem, in_frame_size);
                }
                else
                {
                    AUDIO_ASSERT(0);
                }

                /* do encoding */
                out_size = celt_para->out_frame_size;
                for (j = 0; j < celt_para->process_frame_num ; j++)
                {
                    /* do stereo encode and output to the stream buffer */
                    #if CELT_ENC_MIPS_DEBUG
                    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_para->process_start_gpt_count);
                    #endif /* CELT_ENC_MIPS_DEBUG */
                    ret = celt_encode_prcs(*instance, (const int16_t *)(remain_mem+(2*in_frame_size/celt_para->process_frame_num*j)), celt_para->frame_samples, (unsigned char *)(out_buf+j*out_size), out_size);
                    #if CELT_ENC_MIPS_DEBUG
                    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_para->process_finish_gpt_count);
                    #endif /* CELT_ENC_MIPS_DEBUG */
                    if ((uint32_t)ret != out_size) {
                        DSP_MW_LOG_E("[celt][enc] process fail %d, %d, %d, %d, %d, %d", 6, ret, out_size, in_frame_size, celt_para->frame_samples, celt_para->process_frame_num, j);
                        // AUDIO_ASSERT(0);
                        // return true;
                    }
                }
            }
            break;

        default:
            DSP_MW_LOG_E("[celt][enc] unkown channel mode %d", 1, celt_para->channel_mode);
            AUDIO_ASSERT(0);
            break;
    }

    /* config output size */
    celt_para->total_output_size = celt_para->out_frame_size*celt_para->process_frame_num;
    stream_codec_modify_output_size(para, celt_para->total_output_size);

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_para->finish_gpt_count);

    return false;
}

#endif /* AIR_CELT_ENC_V2_ENABLE */
