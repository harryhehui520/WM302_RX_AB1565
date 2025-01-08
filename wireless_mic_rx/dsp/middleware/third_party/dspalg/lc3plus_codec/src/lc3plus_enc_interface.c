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

#if defined(AIR_BT_LE_LC3PLUS_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "assert.h"
#include "dsp_feature_interface.h"
#include "dsp_audio_process.h"
#include "dsp_dump.h"
#include "sink_inter.h"
#include "source_inter.h"
#include "memory_attribute.h"
#include "preloader_pisplit.h"
#include "lc3plus_enc_interface.h"
#include "dsp_rom_table.h"
#ifdef AIR_BT_LE_LC3PLUS_USE_PIC
#include "lc3plus_codec_portable.h"
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static lc3plus_enc_para_t lc3plus_enc_para[LC3PLUS_ENC_PORT_MAX];

/* Public variables ----------------------------------------------------------*/
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
extern U8 g_lc3_user_cnt;
extern LC3PLUSI_Multi_FFT lc3plus_FFTx;
extern void* g_lc3plus_tab_common_mem_ptr;
#elif defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE)
extern U8 g_lc3_user_cnt;
#endif
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
lc3plus_enc_status_t stream_codec_encoder_lc3plus_init(lc3plus_enc_port_t port, void *user, lc3plus_enc_config_t *config)
{
    uint32_t saved_mask;
    int32_t i;
    void **p_user = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *code_addr_fft = NULL;
    void *data_addr_fft = NULL;
    uint32_t pic_dram_usage = 0;
#endif


    if (port >= LC3PLUS_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

#ifdef AIR_ULL_AUDIO_V2_DONGLE_ENABLE
    g_lc3_user_cnt += 1;
#endif

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (lc3plus_enc_para[port].enc_count == 0) {
        /* update status */
        lc3plus_enc_para[port].status = LC3PLUS_ENC_PORT_STATUS_INIT;

        /* config lc3 codec */
        lc3plus_enc_para[port].sample_bits = config->sample_bits;
        lc3plus_enc_para[port].channel_num = config->channel_num;
        if ((config->sample_rate != 96000) && (config->sample_rate != 48000) && (config->sample_rate != 32000) && (config->sample_rate != 16000))
        {
            DSP_MW_LOG_I("[lc3plus][enc] error sample rate:%d", 1, config->sample_rate);
            AUDIO_ASSERT(FALSE);
        }
        lc3plus_enc_para[port].sample_rate = config->sample_rate;
        lc3plus_enc_para[port].bit_rate_old = config->bit_rate;
        lc3plus_enc_para[port].bit_rate_new = config->bit_rate;
        lc3plus_enc_para[port].frame_interval = config->frame_interval;
        lc3plus_enc_para[port].frame_samples = config->frame_samples;
        lc3plus_enc_para[port].channel_mode = config->channel_mode;
        lc3plus_enc_para[port].codec_mode = config->codec_mode;
        lc3plus_enc_para[port].process_frame_num = config->process_frame_num;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        lc3plus_enc_para[port].enc_t.frame_ms = config->frame_interval/100;
        lc3plus_enc_para[port].enc_t.sr = config->sample_rate;
#endif
        /* get remain samples memory */
        lc3plus_enc_para[port].remain_buffer_size = config->in_frame_size*config->process_frame_num;
    }

    /* increase status count */
    lc3plus_enc_para[port].enc_count += 1;
    if (lc3plus_enc_para[port].enc_count == 0) {
        AUDIO_ASSERT(0);
    }

    /* register this user into this port */
    for (i = LC3PLUS_ENC_USER_COUNT - 1; i >= 0; i--) {
        if (lc3plus_enc_para[port].user[i] == user) {
            p_user = &(lc3plus_enc_para[port].user[i]);
            break;
        } else if (lc3plus_enc_para[port].user[i] == NULL) {
            p_user = &(lc3plus_enc_para[port].user[i]);
        }
    }
    if (p_user != NULL) {
        *p_user = user;
    } else {
        AUDIO_ASSERT(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    if (g_lc3_user_cnt == 1) {
        if (config->frame_interval == 2500) {
            lc3plusi_fft2_5ms_library_load(code_addr_fft, data_addr_fft, &pic_dram_usage);
            lc3plus_FFTx.fix_fft_Init = fix_fft_Init_2p5_MS;
            lc3plus_FFTx.FFT4N = FFT4N_2p5_MS;
            lc3plus_FFTx.FFT8N = FFT8N_2p5_MS;
            lc3plus_FFTx.fix_fft15 = fix_fft15_2p5_MS;
            lc3plus_FFTx.fix_fft20 = fix_fft20_2p5_MS;
            lc3plus_FFTx.fix_fft40 = fix_fft40_2p5_MS;
        } else if(config->frame_interval == 5000) {
            lc3plusi_fft5_0ms_library_load(code_addr_fft, data_addr_fft, &pic_dram_usage);
            lc3plus_FFTx.fix_fft_Init = fix_fft_Init_5_MS;
            lc3plus_FFTx.FFT8N        = FFT8N_5_MS;
            lc3plus_FFTx.fix_fft10    = fix_fft10_5_MS;
            lc3plus_FFTx.fix_fft15    = fix_fft15_5_MS;
            lc3plus_FFTx.fix_fft30    = fix_fft30_5_MS;
            lc3plus_FFTx.fix_fft40    = fix_fft40_5_MS;
        } else if(config->frame_interval == 10000) {
            lc3plusi_fft10_0ms_library_load(code_addr_fft, data_addr_fft, &pic_dram_usage);
            lc3plus_FFTx.fix_fft_Init = fix_fft_Init_10_MS;
            lc3plus_FFTx.FFT8N        = FFT8N_10_MS;
            lc3plus_FFTx.fix_fft10    = fix_fft10_10_MS;
            lc3plus_FFTx.FFT16N       = FFT16N_10_MS;
            lc3plus_FFTx.fix_fft20    = fix_fft20_10_MS;
            lc3plus_FFTx.fix_fft30    = fix_fft30_10_MS;
            lc3plus_FFTx.fix_fft40    = fix_fft40_10_MS;
        }
    }
#endif


    return LC3PLUS_ENC_STATUS_OK;
}

lc3plus_enc_status_t stream_codec_encoder_lc3plus_deinit(lc3plus_enc_port_t port, void *user)
{
    uint32_t saved_mask;
    int32_t i;
    bool mem_flag = false;
    void *WorkMemPtr = NULL;
    void *RemainMemPtr = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *TabCommonMemPtr = NULL;
    void *TabEncMemPtr = NULL;
    uint32_t frame_interval = 0;
#endif
    void **p_user = NULL;

    if (port >= LC3PLUS_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

#ifdef AIR_ULL_AUDIO_V2_DONGLE_ENABLE
    g_lc3_user_cnt -= 1;
#endif

    /* decrease status count */
    if (lc3plus_enc_para[port].enc_count == 0) {
        AUDIO_ASSERT(0);
    }
    lc3plus_enc_para[port].enc_count -= 1;

    if (lc3plus_enc_para[port].enc_count == 0) {
        /* update status */
        lc3plus_enc_para[port].status = LC3PLUS_ENC_PORT_STATUS_DEINIT;

        /* reset lc3 codec */
        lc3plus_enc_para[port].sample_bits = 0;
        lc3plus_enc_para[port].channel_num = 0;
        lc3plus_enc_para[port].sample_rate = 0;
        lc3plus_enc_para[port].bit_rate_old = 0;
        lc3plus_enc_para[port].bit_rate_new = 0;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        frame_interval = lc3plus_enc_para[port].frame_interval;
#endif
        lc3plus_enc_para[port].frame_interval = 0;
        lc3plus_enc_para[port].frame_samples = 0;
        lc3plus_enc_para[port].channel_mode = 0;
        lc3plus_enc_para[port].codec_mode = 0;
        lc3plus_enc_para[port].in_frame_size = 0;
        lc3plus_enc_para[port].out_frame_size = 0;
        lc3plus_enc_para[port].work_buffer_size = 0;
        lc3plus_enc_para[port].remain_buffer_size = 0;
        WorkMemPtr = lc3plus_enc_para[port].work_mem_ptr;
        lc3plus_enc_para[port].work_mem_ptr = NULL;
        RemainMemPtr = lc3plus_enc_para[port].remain_mem_ptr;
        lc3plus_enc_para[port].remain_mem_ptr = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        TabEncMemPtr = lc3plus_enc_para[port].tab_enc_mem_ptr;
        lc3plus_enc_para[port].tab_enc_mem_ptr = NULL;
        lc3plus_enc_para[port].enc_t.frame_ms = 0;
        lc3plus_enc_para[port].enc_t.sr = 0;
        if (g_lc3_user_cnt == 0) {
            TabCommonMemPtr = lc3plus_enc_para[port].tab_common_mem_ptr;
            lc3plus_enc_para[port].tab_common_buffer_size = 0;
            lc3plus_enc_para[port].tab_common_mem_ptr = NULL;
        }
#endif

        /* set memory operation flag */
        mem_flag = true;
    }

    /* unregister this user into this port */
    for (i = LC3PLUS_ENC_USER_COUNT - 1; i >= 0; i--) {
        if (lc3plus_enc_para[port].user[i] == user) {
            p_user = &(lc3plus_enc_para[port].user[i]);
            break;
        }
    }
    if (p_user != NULL) {
        *p_user = NULL;
    } else {
        AUDIO_ASSERT(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    if (g_lc3_user_cnt == 0) {
        if (frame_interval == 2500) {
            lc3plusi_fft2_5ms_library_unload();
            lc3plus_FFTx.fix_fft_Init = NULL;
            lc3plus_FFTx.FFT4N = NULL;
            lc3plus_FFTx.FFT8N = NULL;
            lc3plus_FFTx.fix_fft15 = NULL;
            lc3plus_FFTx.fix_fft20 = NULL;
            lc3plus_FFTx.fix_fft40 = NULL;
        } else if(frame_interval == 5000) {
            lc3plusi_fft5_0ms_library_unload();
            lc3plus_FFTx.fix_fft_Init = NULL;
            lc3plus_FFTx.FFT8N        = NULL;
            lc3plus_FFTx.fix_fft10    = NULL;
            lc3plus_FFTx.fix_fft15    = NULL;
            lc3plus_FFTx.fix_fft30    = NULL;
            lc3plus_FFTx.fix_fft40    = NULL;
        } else if(frame_interval == 10000) {
            lc3plusi_fft10_0ms_library_unload();
            lc3plus_FFTx.fix_fft_Init = NULL;
            lc3plus_FFTx.FFT8N        = NULL;
            lc3plus_FFTx.fix_fft10    = NULL;
            lc3plus_FFTx.FFT16N       = NULL;
            lc3plus_FFTx.fix_fft20    = NULL;
            lc3plus_FFTx.fix_fft30    = NULL;
            lc3plus_FFTx.fix_fft40    = NULL;
        }
    }
#endif
    if (mem_flag) {
        /* free working memory */
        preloader_pisplit_free_memory(WorkMemPtr);

        /* free remain samples memory */
        preloader_pisplit_free_memory(RemainMemPtr);

#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        preloader_pisplit_free_memory(TabEncMemPtr);
        DSP_MW_LOG_I("[LC3PLUS_ENC] LC3PLUSI_Tab_Enc Free Done!!", 0);
        if (g_lc3_user_cnt == 0) {
            /* free memory if no memeory user */
            g_lc3plus_tab_common_mem_ptr = NULL;
            preloader_pisplit_free_memory(TabCommonMemPtr);
            DSP_MW_LOG_I("[LC3PLUS_ENC][LC3PLUS_DEC] LC3PLUSI_Tab_Common Free Done!!", 0);
        }
#endif
    }

    return LC3PLUS_ENC_STATUS_OK;
}

lc3plus_enc_status_t stream_codec_encoder_lc3plus_get_data_info(lc3plus_enc_port_t port, uint32_t channel, uint8_t **in_buffer_address, uint32_t *in_frame_size)
{
    lc3plus_enc_para_t *lc3plus_para = NULL;

    if (port >= LC3PLUS_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    lc3plus_para = &lc3plus_enc_para[port];

    if ((channel > lc3plus_para->channel_num) || (channel == 0)) {
        AUDIO_ASSERT(0);
    }

    *in_buffer_address = (uint8_t *)((uint32_t)lc3plus_para->remain_mem_ptr + (channel - 1) * lc3plus_para->remain_buffer_size);
    *in_frame_size    = lc3plus_para->in_frame_size;

    return LC3PLUS_ENC_STATUS_OK;
}

lc3plus_enc_status_t stream_codec_encoder_lc3plus_set_bitrate(lc3plus_enc_port_t port, uint32_t bitrate)
{
    uint32_t saved_mask;
    lc3plus_enc_para_t *lc3plus_para = NULL;

    if (port >= LC3PLUS_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    lc3plus_para = &lc3plus_enc_para[port];

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
    lc3plus_para->bit_rate_new = bitrate;
    hal_nvic_restore_interrupt_mask(saved_mask);

    return LC3PLUS_ENC_STATUS_OK;
}

lc3plus_enc_status_t stream_codec_encoder_lc3plus_get_finish_gpt_count(lc3plus_enc_port_t port, uint32_t *gpt_count)
{
    if (port >= LC3PLUS_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    *gpt_count = lc3plus_enc_para[port].finish_gpt_count;

    return LC3PLUS_ENC_STATUS_OK;
}

#if LC3PLUS_ENC_MIPS_DEBUG
lc3plus_enc_status_t stream_codec_encoder_lc3plus_get_process_gpt_count(lc3plus_enc_port_t port, uint32_t *start_count, uint32_t *finish_count)
{
    if (port >= LC3PLUS_ENC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    *start_count = lc3plus_enc_para[port].process_start_gpt_count;
    *finish_count = lc3plus_enc_para[port].process_finish_gpt_count;

    return LC3PLUS_ENC_STATUS_OK;
}
#endif /* LC3PLUS_ENC_MIPS_DEBUG */

bool stream_codec_encoder_lc3plus_initialize(void *para)
{
    uint32_t i, j;
    uint32_t saved_mask;
    lc3plus_enc_para_t *lc3plus_para = NULL;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    LC3PLUS_ErrorCode ret;
    uint8_t *working_mem = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *tab_common_mem;
    void *tab_enc_mem;
    LC3PLUS_Param *p_enc_t;
#endif
    /* find out which port is belong to this stream */
    for (i = 0; i < LC3PLUS_ENC_PORT_MAX; i++) {
        for (j = 0; j < LC3PLUS_ENC_USER_COUNT; j++) {
            /* Check if this source or sink has already be regitsered into this port */
            if ((lc3plus_enc_para[i].user[j] == stream_ptr->source) ||
                (lc3plus_enc_para[i].user[j] == stream_ptr->sink)) {
                lc3plus_para = &lc3plus_enc_para[i];
                goto FIND_ENCODER_PORT;
            }
        }
    }
    if (lc3plus_para == NULL) {
        AUDIO_ASSERT(0);
    }

FIND_ENCODER_PORT:

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
    /* status check */
    if (lc3plus_para->status == LC3PLUS_ENC_PORT_STATUS_INIT) {
        lc3plus_para->status = LC3PLUS_ENC_PORT_STATUS_RUNNING;
    } else if (lc3plus_para->status == LC3PLUS_ENC_PORT_STATUS_RUNNING) {
        hal_nvic_restore_interrupt_mask(saved_mask);
        return false;
    } else {
        DSP_MW_LOG_I("[lc3plus][enc] error status:%d", 1, lc3plus_para->status);
        AUDIO_ASSERT(FALSE);
        return true;
    }
    hal_nvic_restore_interrupt_mask(saved_mask);

    /* get sample memory */
    lc3plus_para->remain_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_para->remain_buffer_size * lc3plus_para->channel_num);
    if (lc3plus_para->remain_mem_ptr == NULL) {
        AUDIO_ASSERT(0);
    }
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    p_enc_t = &(lc3plus_para->enc_t);
    /* get table_common memory */
    if (g_lc3_user_cnt == 1) {
#if defined(ROM_TABLE_ADDR_LC3_PLUS) && defined(ROM_TABLE_ADDR_LC3)
       LC3PLUSI_Set_ROM_Start(ROM_TABLE_ADDR_LC3_PLUS, ROM_TABLE_ADDR_LC3);
       DSP_MW_LOG_I("[LC3PLUS_ENC] LC3PLUSI_Set_ROM_Start Done!", 0);
#endif
        lc3plus_para->tab_common_buffer_size = LC3PLUSI_Tab_Common_Get_MemSize();
        /* 8byte-align */
        lc3plus_para->tab_common_buffer_size = (lc3plus_para->tab_common_buffer_size + 7) / 8 * 8;
        lc3plus_para->tab_common_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_para->tab_common_buffer_size);
        if (lc3plus_para->tab_common_mem_ptr == NULL) {
            AUDIO_ASSERT(0);
        }
        g_lc3plus_tab_common_mem_ptr = lc3plus_para->tab_common_mem_ptr;
        /* table_common init */
        tab_common_mem = lc3plus_para->tab_common_mem_ptr;
        ret = LC3PLUSI_Tab_Common_Init(tab_common_mem);
        if (LC3PLUS_OK != ret) {
            DSP_MW_LOG_I("[LC3PLUS_ENC] Table Common Init Fail, %d!", 1, ret);
            AUDIO_ASSERT(0);
        }
        DSP_MW_LOG_I("[LC3PLUS_ENC] LC3PLUSI_Tab_Common_Init Done!", 0);
    } else {
        lc3plus_para->tab_common_mem_ptr = g_lc3plus_tab_common_mem_ptr;
    }

    tab_common_mem = lc3plus_para->tab_common_mem_ptr;

    lc3plus_para->tab_enc_buffer_size = LC3PLUSI_Tab_Enc_Get_MemSize(p_enc_t);
    DSP_MW_LOG_I("[LC3PLUS_ENC] LC3PLUSI_Tab_Enc_Get_MemSize(frame_ms:%d, sr:%d) ret:%d", 3, p_enc_t->frame_ms, p_enc_t->sr, lc3plus_para->tab_enc_buffer_size);
    /* 8byte-align */
    lc3plus_para->tab_enc_buffer_size = (lc3plus_para->tab_enc_buffer_size + 7) / 8 * 8;
    lc3plus_para->tab_enc_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_para->tab_enc_buffer_size);

#if !(defined(ROM_TABLE_ADDR_LC3_PLUS) && defined(ROM_TABLE_ADDR_LC3))
    if (lc3plus_para->tab_enc_mem_ptr == NULL) {
        AUDIO_ASSERT(0);
    }
#endif

    /* table_enc init */
    tab_enc_mem = lc3plus_para->tab_enc_mem_ptr;
    ret = LC3PLUSI_Tab_Enc_Init(tab_common_mem, tab_enc_mem, p_enc_t);
    if (LC3PLUS_OK != ret) {
        DSP_MW_LOG_I("[LC3PLUS_ENC] Table Enc Init Fail, %d!", 1, ret);
        AUDIO_ASSERT(0);
    }
    DSP_MW_LOG_I("[LC3PLUS_ENC] LC3PLUSI_Tab_Enc_Init Done!", 0);
#endif

#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
#if defined(ROM_TABLE_ADDR_LC3_PLUS)
    LC3PLUS_Set_ROM_Start(ROM_TABLE_ADDR_LC3_PLUS, ROM_TABLE_ADDR_LC3);
    DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Set_ROM_Start Done!", 0);
#endif
#endif

    if (lc3plus_para->channel_mode != LC3PLUS_ENC_CHANNEL_MODE_STEREO)
    {
        /* get codec working memory */
        lc3plus_para->work_buffer_size = LC3PLUS_Enc_Get_MemSize(1, lc3plus_para->sample_rate, lc3plus_para->frame_interval / 100);
        lc3plus_para->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_para->work_buffer_size * lc3plus_para->channel_num);
        if (lc3plus_para->work_mem_ptr == NULL) {
            AUDIO_ASSERT(0);
        }
        /* do encoder init one by one channel */
        for (i = 0; i < lc3plus_para->channel_num; i++) {
            working_mem = (uint8_t *)lc3plus_para->work_mem_ptr + i * lc3plus_para->work_buffer_size;
            ret = LC3PLUS_Enc_Init(working_mem, lc3plus_para->sample_bits, lc3plus_para->sample_rate, 1, lc3plus_para->bit_rate_new, lc3plus_para->frame_interval / 100, lc3plus_para->codec_mode);
            if (ret != LC3PLUS_OK) {
                DSP_MW_LOG_E("[lc3plus][enc] init fail %d", 1, ret);
                AUDIO_ASSERT(0);
                return true;
            }
        }
    }
    else
    {
        /* get codec working memory for stereo channel */
        lc3plus_para->work_buffer_size = LC3PLUS_Enc_Get_MemSize(2, lc3plus_para->sample_rate, lc3plus_para->frame_interval / 100);
        lc3plus_para->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_para->work_buffer_size);
        if (lc3plus_para->work_mem_ptr == NULL) {
            AUDIO_ASSERT(0);
        }
        working_mem = (uint8_t *)lc3plus_para->work_mem_ptr;
        ret = LC3PLUS_Enc_Init(working_mem, lc3plus_para->sample_bits, lc3plus_para->sample_rate, 2, lc3plus_para->bit_rate_new, lc3plus_para->frame_interval / 100, lc3plus_para->codec_mode);
        if (ret != LC3PLUS_OK) {
            DSP_MW_LOG_E("[lc3plus][enc] init fail %d", 1, ret);
            AUDIO_ASSERT(0);
            return true;
        }
    }

    DSP_MW_LOG_I("[lc3plus][enc] init done, working mem = %d, 0x%x, version = 0x%8x", 3, lc3plus_para->work_buffer_size, lc3plus_para->work_mem_ptr, LC3PLUS_Get_Version());

    return false;
}

ATTR_TEXT_IN_IRAM bool stream_codec_encoder_lc3plus_process(void *para)
{
    uint32_t i, j;
    lc3plus_enc_para_t *lc3plus_para = NULL;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    uint8_t *in_buf;
    uint8_t *in_buf2;
    uint8_t *out_buf;
    uint16_t in_frame_size;
    uint8_t *remain_mem;
    uint8_t *working_mem;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *tab_mem;
#endif
    uint32_t out_size;
    LC3PLUS_ErrorCode ret;

    /* find out which port is belong to this stream */
    for (i = 0; i < LC3PLUS_ENC_PORT_MAX; i++) {
        for (j = 0; j < LC3PLUS_ENC_USER_COUNT; j++) {
            /* Check if this source or sink has already be regitsered into this port */
            if ((lc3plus_enc_para[i].user[j] == stream_ptr->source) ||
                (lc3plus_enc_para[i].user[j] == stream_ptr->sink)) {
                lc3plus_para = &lc3plus_enc_para[i];
                goto FIND_ENCODER_PORT;
            }
        }
    }
    if (lc3plus_para == NULL) {
        AUDIO_ASSERT(0);
    }
FIND_ENCODER_PORT:

    in_frame_size = stream_codec_get_input_size(para);
    lc3plus_para->in_frame_size = (U32)in_frame_size;
    if (in_frame_size == 0) {
        /* config output size */
        stream_codec_modify_output_size(para, in_frame_size);
        lc3plus_para->out_frame_size = in_frame_size;

        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_para->finish_gpt_count);

        return false;
    }
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    tab_mem = lc3plus_para->tab_common_mem_ptr;
#endif
    if (lc3plus_para->channel_mode != LC3PLUS_ENC_CHANNEL_MODE_STEREO)
    {
        /* mono or multi-channel mode case */
        /* do encoder one by one channel */
        for (i = 0; i < lc3plus_para->channel_num; i++) {
            in_buf = (uint8_t *)stream_codec_get_input_buffer(para, i + 1);
            out_buf = (uint8_t *)stream_codec_get_output_buffer(para, i + 1);
            remain_mem = (uint8_t *)((uint32_t)lc3plus_para->remain_mem_ptr + i * lc3plus_para->remain_buffer_size);
            working_mem = (uint8_t *)lc3plus_para->work_mem_ptr + i * lc3plus_para->work_buffer_size;

            /* copy data from stream buffer to remain buffer */
            if (in_frame_size != lc3plus_para->remain_buffer_size) {
                AUDIO_ASSERT(0);
            }
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

            if (lc3plus_para->bit_rate_old != lc3plus_para->bit_rate_new)
            {
                LC3PLUS_Enc_Set_BitRate(working_mem, lc3plus_para->bit_rate_new);
            }
            out_size = 0;
            for (j = 0; j < lc3plus_para->process_frame_num ; j++)
            {
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                if(i == 0)
                {
                    LOG_AUDIO_DUMP((uint8_t *)remain_mem + (in_frame_size / lc3plus_para->process_frame_num * j), in_frame_size / lc3plus_para->process_frame_num, AUDIO_WOOFER_PLC_OUT);
                }
#endif
#endif
                /* do encode and output to the stream buffer */
                #if LC3PLUS_ENC_MIPS_DEBUG
                hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_para->process_start_gpt_count);
                #endif /* LC3PLUS_ENC_MIPS_DEBUG */
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                ret = LC3PLUS_Enc_Prcs((void *)working_mem, (uint8_t *)out_buf + (j*out_size), (uint8_t *)remain_mem + (in_frame_size / lc3plus_para->process_frame_num * j), &out_size);
#else
                ret = LC3PLUS_Enc_Prcs((void *)working_mem, tab_mem,(uint8_t *)out_buf + (j*out_size), (uint8_t *)remain_mem + (in_frame_size / lc3plus_para->process_frame_num * j), &out_size, &lc3plus_FFTx);
#endif
                #if LC3PLUS_ENC_MIPS_DEBUG
                hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_para->process_finish_gpt_count);
                #endif /* LC3PLUS_ENC_MIPS_DEBUG */

#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                if(i == 0)
                {
                    LOG_AUDIO_DUMP(out_buf + (j*out_size), out_size, AUDIO_WOOFER_UPSAMPLE_16K);
                }
#endif
#endif
                if (ret != LC3PLUS_OK) {
                    DSP_MW_LOG_E("[lc3plus][enc] process fail %d", 1, ret);
                    AUDIO_ASSERT(0);
                    return true;
                }
            }
        }
        if (lc3plus_para->bit_rate_old != lc3plus_para->bit_rate_new)
        {
            lc3plus_para->bit_rate_old = lc3plus_para->bit_rate_new;
        }
    }
    else
    {
        /* stereo case */
        in_buf = (uint8_t *)stream_codec_get_input_buffer(para, 1);
        in_buf2 = (uint8_t *)stream_codec_get_input_buffer(para, 2);
        out_buf = (uint8_t *)stream_codec_get_output_buffer(para, 1);
        remain_mem = (uint8_t *)lc3plus_para->remain_mem_ptr;
        working_mem = (uint8_t *)lc3plus_para->work_mem_ptr;

        /* copy data from stream buffer to remain buffer */
        if (in_frame_size != lc3plus_para->remain_buffer_size) {
            AUDIO_ASSERT(0);
        }
        if (stream_codec_get_input_resolution(para) == RESOLUTION_16BIT)
        {
            for (j = 0; j < in_frame_size / sizeof(uint16_t); j++)
            {
                *((uint16_t *)remain_mem + 2*j) = *((uint16_t *)in_buf + j);
                *((uint16_t *)remain_mem + 2*j + 1) = *((uint16_t *)in_buf2 + j);
            }
        }
        else
        {
            for (j = 0; j < in_frame_size / sizeof(uint32_t); j++)
            {
                *((uint32_t *)remain_mem + 2*j) = *((uint32_t *)in_buf + j);
                *((uint32_t *)remain_mem + 2*j + 1) = *((uint32_t *)in_buf2 + j);
            }
        }

        if (lc3plus_para->bit_rate_old != lc3plus_para->bit_rate_new)
        {
            LC3PLUS_Enc_Set_BitRate(working_mem, lc3plus_para->bit_rate_new);
        }

        out_size = 0;
        for (j = 0; j < lc3plus_para->process_frame_num ; j++)
        {

#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
            LOG_AUDIO_DUMP(remain_mem + (in_frame_size * 2 / lc3plus_para->process_frame_num * j), in_frame_size * 2 / lc3plus_para->process_frame_num, AUDIO_WOOFER_PLC_OUT);
#endif
#endif
            /* do stereo encode and output to the stream buffer */
            #if LC3PLUS_ENC_MIPS_DEBUG
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_para->process_start_gpt_count);
            #endif /* LC3PLUS_ENC_MIPS_DEBUG */
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
            ret = LC3PLUS_Enc_Prcs((void *)working_mem, (uint8_t *)out_buf + (j*out_size), (uint8_t *)remain_mem + (in_frame_size * 2 / lc3plus_para->process_frame_num * j), &out_size);
#else
            ret = LC3PLUS_Enc_Prcs((void *)working_mem, tab_mem,(uint8_t *)out_buf + (j*out_size), (uint8_t *)remain_mem + (in_frame_size * 2 / lc3plus_para->process_frame_num * j), &out_size, &lc3plus_FFTx);
#endif
            #if LC3PLUS_ENC_MIPS_DEBUG
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_para->process_finish_gpt_count);

#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
            LOG_AUDIO_DUMP(out_buf + (j*out_size), out_size, AUDIO_WOOFER_UPSAMPLE_16K);
#endif
#endif

            #endif /* LC3PLUS_ENC_MIPS_DEBUG */
            if (ret != LC3PLUS_OK) {
                DSP_MW_LOG_E("[lc3plus][enc] process fail %d", 1, ret);
                AUDIO_ASSERT(0);
                return true;
            }
        }

        if (lc3plus_para->bit_rate_old != lc3plus_para->bit_rate_new)
        {
            lc3plus_para->bit_rate_old = lc3plus_para->bit_rate_new;
        }
    }

    /* config output size */
    lc3plus_para->out_frame_size = out_size*lc3plus_para->process_frame_num;
    stream_codec_modify_output_size(para, out_size*lc3plus_para->process_frame_num);


    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_para->finish_gpt_count);

    return false;
}

#endif /* AIR_BT_LE_LC3PLUS_ENABLE */
