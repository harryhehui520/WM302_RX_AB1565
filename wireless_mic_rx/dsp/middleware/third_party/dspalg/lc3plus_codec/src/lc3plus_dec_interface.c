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
#include "dsp_feature_interface.h"
#include "dsp_audio_process.h"
#include "lc3plus_dec_interface.h"
#include "dsp_dump.h"
#include "bt_types.h"
#include "assert.h"
#include "sink_inter.h"
#include "source_inter.h"
#include "memory_attribute.h"
#include "preloader_pisplit.h"
#include "dsp_rom_table.h"
#ifdef AIR_BT_LE_LC3PLUS_USE_PIC
#include "lc3plus_codec_portable.h"
#endif
/* Private define ------------------------------------------------------------*/
#define LC3PLUS_PLC_MUTE_OUT_THD        10

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static lc3plus_dec_port_para_t lc3plus_dec_port_para[LC3PLUS_DEC_PORT_MAX];
/* Public variables ----------------------------------------------------------*/
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
#ifdef AIR_BT_CODEC_BLE_ENABLED
extern U8 g_lc3_user_cnt;
#else
U8 g_lc3_user_cnt = 0;
#endif
LC3PLUSI_Multi_FFT lc3plus_FFTx;
void* g_lc3plus_tab_common_mem_ptr;
#elif defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE)
U8 g_lc3_user_cnt = 0;
#endif
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
lc3plus_dec_status_t stream_codec_decoder_lc3plus_init(lc3plus_dec_port_t port, void *user, lc3plus_dec_port_config_t *config)
{
    uint32_t saved_mask;
    int32_t i;
    void **p_user = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *code_addr_fft = NULL;
    void *data_addr_fft = NULL;
    uint32_t pic_dram_usage = 0;
#endif
    if (port >= LC3PLUS_DEC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (lc3plus_dec_port_para[port].count == 0) {
        /* update status */
        lc3plus_dec_port_para[port].status = LC3PLUS_DEC_PORT_STATUS_INIT;

        /* config codec informations */
        lc3plus_dec_port_para[port].sample_rate = config->sample_rate;
        lc3plus_dec_port_para[port].sample_bits = config->sample_bits;
        lc3plus_dec_port_para[port].bit_rate    = config->bit_rate;
        lc3plus_dec_port_para[port].channel_mode = config->channel_mode;
        lc3plus_dec_port_para[port].frame_samples = config->frame_samples;
        lc3plus_dec_port_para[port].frame_interval = config->frame_interval;
        lc3plus_dec_port_para[port].frame_size = config->frame_size;
        lc3plus_dec_port_para[port].plc_enable = config->plc_enable;
        lc3plus_dec_port_para[port].plc_method = config->plc_method;
        lc3plus_dec_port_para[port].in_channel_num = config->in_channel_num;
        lc3plus_dec_port_para[port].out_channel_num = config->out_channel_num;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        lc3plus_dec_port_para[port].dec_t.frame_ms = config->frame_interval/100;
        lc3plus_dec_port_para[port].dec_t.sr = config->sample_rate;
#endif
        if (lc3plus_dec_port_para[port].channel_mode == LC3PLUS_DEC_CHANNEL_MODE_MONO) {
            if (lc3plus_dec_port_para[port].in_channel_num != 1) {
                AUDIO_ASSERT(0);
            }
        } else if (lc3plus_dec_port_para[port].channel_mode == LC3PLUS_DEC_CHANNEL_MODE_STEREO) {
            if ((lc3plus_dec_port_para[port].in_channel_num != 1) || (lc3plus_dec_port_para[port].out_channel_num != 2)) {
                AUDIO_ASSERT(0);
            }
        } else if (lc3plus_dec_port_para[port].channel_mode == LC3PLUS_DEC_CHANNEL_MODE_MULTI_MONO) {
            if (lc3plus_dec_port_para[port].in_channel_num != lc3plus_dec_port_para[port].out_channel_num) {
                AUDIO_ASSERT(0);
            }
        } else if (lc3plus_dec_port_para[port].channel_mode == LC3PLUS_DEC_CHANNEL_MODE_MULTI_STEREO) {
            if ((lc3plus_dec_port_para[port].in_channel_num*2) != lc3plus_dec_port_para[port].out_channel_num) {
                AUDIO_ASSERT(0);
            }
        }
    }

    /* increase status count */
    lc3plus_dec_port_para[port].count += 1;
    if (lc3plus_dec_port_para[port].count == 0) {
        AUDIO_ASSERT(0);
    }

    /* register this user into this port */
    for (i = LC3PLUS_DEC_USER_COUNT - 1; i >= 0; i--) {
        if (lc3plus_dec_port_para[port].user[i] == user) {
            p_user = &(lc3plus_dec_port_para[port].user[i]);
            break;
        } else if (lc3plus_dec_port_para[port].user[i] == NULL) {
            p_user = &(lc3plus_dec_port_para[port].user[i]);
        }
    }
    if (p_user != NULL) {
        *p_user = user;
    } else {
        AUDIO_ASSERT(0);
    }

#ifdef AIR_ULL_AUDIO_V2_DONGLE_ENABLE
    g_lc3_user_cnt += 1;
#endif

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

    return LC3PLUS_DEC_STATUS_OK;
}

lc3plus_dec_status_t stream_codec_decoder_lc3plus_deinit(lc3plus_dec_port_t port, void *user)
{
    uint32_t saved_mask;
    int32_t i;
    bool mem_flag = false;
    void *WorkMemPtr = NULL;
    void **p_user = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    uint32_t frame_interval = 0;
    void *TabCommonMemPtr = NULL;
    void *TabDecMemPtr = NULL;
#endif

    if (port >= LC3PLUS_DEC_PORT_MAX) {
        AUDIO_ASSERT(0);
    }

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

#ifdef AIR_ULL_AUDIO_V2_DONGLE_ENABLE
    g_lc3_user_cnt -= 1;
#endif

    /* decrease status count */
    if (lc3plus_dec_port_para[port].count == 0) {
        AUDIO_ASSERT(0);
    }
    lc3plus_dec_port_para[port].count -= 1;

    if (lc3plus_dec_port_para[port].count == 0) {
        /* reset codec informations */
        lc3plus_dec_port_para[port].sample_rate = 0;
        lc3plus_dec_port_para[port].sample_bits = 0;
        lc3plus_dec_port_para[port].bit_rate    = 0;
        lc3plus_dec_port_para[port].channel_mode = 0;
        lc3plus_dec_port_para[port].frame_samples = 0;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        frame_interval = lc3plus_dec_port_para[port].frame_interval;
        TabCommonMemPtr= lc3plus_dec_port_para[port].tab_common_mem_ptr;
#endif
        lc3plus_dec_port_para[port].frame_interval = 0;
        lc3plus_dec_port_para[port].frame_size = 0;
        lc3plus_dec_port_para[port].plc_enable = 0;
        lc3plus_dec_port_para[port].plc_method = 0;
        lc3plus_dec_port_para[port].in_channel_num = 0;
        lc3plus_dec_port_para[port].out_channel_num = 0;
        lc3plus_dec_port_para[port].work_buffer_size = 0;
        WorkMemPtr   = lc3plus_dec_port_para[port].work_mem_ptr;
        lc3plus_dec_port_para[port].work_mem_ptr = NULL;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
        lc3plus_dec_port_para[port].dec_t.frame_ms = 0;
        lc3plus_dec_port_para[port].dec_t.sr = 0;

        TabDecMemPtr = lc3plus_dec_port_para[port].tab_dec_mem_ptr;
        lc3plus_dec_port_para[port].tab_dec_buffer_size = 0;
        lc3plus_dec_port_para[port].tab_dec_mem_ptr = NULL;
        if (g_lc3_user_cnt == 0) {
            lc3plus_dec_port_para[port].tab_common_buffer_size = 0;
            lc3plus_dec_port_para[port].tab_common_mem_ptr = NULL;
        }
#endif
        /* set memory operation flag */
        mem_flag = true;
    }

    /* unregister this user into this port */
    for (i = LC3PLUS_DEC_USER_COUNT - 1; i >= 0; i--) {
        if (lc3plus_dec_port_para[port].user[i] == user) {
            p_user = &(lc3plus_dec_port_para[port].user[i]);
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
        if (WorkMemPtr) {
            preloader_pisplit_free_memory(WorkMemPtr);
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
            preloader_pisplit_free_memory(TabDecMemPtr);
            DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Tab_Dec Free Done!", 0);
            if (g_lc3_user_cnt == 0) {
                /* free memory if no memeory user */
                g_lc3plus_tab_common_mem_ptr = NULL;
                preloader_pisplit_free_memory(TabCommonMemPtr);
                DSP_MW_LOG_I("[LC3PLUS_DEC][LC3PLUS_ENC] LC3PLUSI_Tab_Common Free Done!", 0);
            }
#endif
        }
    }

    return LC3PLUS_DEC_STATUS_OK;
}

bool stream_codec_decoder_lc3plus_initialize(void *para)
{
    uint32_t i, j;
    lc3plus_dec_port_para_t *lc3plus_dec_port = NULL;
    DSP_STREAMING_PARA_PTR stream_ptr = DSP_STREAMING_GET_FROM_PRAR(para);
    uint32_t saved_mask;
    void *work_mem;
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *tab_common_mem;
    void *tab_dec_mem;
    LC3PLUS_Param *p_dec_t;
#endif
    LC3PLUS_ErrorCode lc3plus_ret;

    /* find out which port is belong to this stream */
    for (i = 0; i < LC3PLUS_DEC_PORT_MAX; i++) {
        for (j = 0; j < LC3PLUS_DEC_USER_COUNT; j++) {
            /* Check if this source or sink has already be regitsered into this index */
            if ((lc3plus_dec_port_para[i].user[j] == stream_ptr->source) ||
                (lc3plus_dec_port_para[i].user[j] == stream_ptr->sink)) {
                lc3plus_dec_port = &lc3plus_dec_port_para[i];
                goto FIND_DECODER_PORT;
            }
        }
    }
    if (lc3plus_dec_port == NULL) {
        AUDIO_ASSERT(0);
        return true;
    }
FIND_DECODER_PORT:
    /* status check */
    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
    if (lc3plus_dec_port->status == LC3PLUS_DEC_PORT_STATUS_INIT) {
        lc3plus_dec_port->status = LC3PLUS_DEC_PORT_STATUS_RUNNING;
    } else if (lc3plus_dec_port->status == LC3PLUS_DEC_PORT_STATUS_RUNNING) {
        hal_nvic_restore_interrupt_mask(saved_mask);
        return false;
    } else {
        DSP_MW_LOG_I("[lc3plus][dec] error status:%d", 1, lc3plus_dec_port->status);
        AUDIO_ASSERT(0);
        return true;
    }
    hal_nvic_restore_interrupt_mask(saved_mask);
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    p_dec_t = &(lc3plus_dec_port->dec_t);

   if (g_lc3_user_cnt == 1) {
#if defined(ROM_TABLE_ADDR_LC3_PLUS) && defined(ROM_TABLE_ADDR_LC3)
       LC3PLUSI_Set_ROM_Start(ROM_TABLE_ADDR_LC3_PLUS, ROM_TABLE_ADDR_LC3);
       DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Set_ROM_Start Done!", 0);
#endif
       /* get table_common memory */
       lc3plus_dec_port->tab_common_buffer_size = LC3PLUSI_Tab_Common_Get_MemSize();
       /* 8byte-align */
       lc3plus_dec_port->tab_common_buffer_size = (lc3plus_dec_port->tab_common_buffer_size + 7) / 8 * 8;
       lc3plus_dec_port->tab_common_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_dec_port->tab_common_buffer_size);
       g_lc3plus_tab_common_mem_ptr = lc3plus_dec_port->tab_common_mem_ptr;
       /* table init */
       tab_common_mem = lc3plus_dec_port->tab_common_mem_ptr;
       lc3plus_ret = LC3PLUSI_Tab_Common_Init(tab_common_mem);
       if (LC3PLUS_OK != lc3plus_ret) {
           DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Tab_Common_Init Init Fail, %d!", 1, lc3plus_ret);
           AUDIO_ASSERT(0);
       }
       DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Tab_Common_Init Done!", 0);
   } else {
       lc3plus_dec_port->tab_common_mem_ptr = g_lc3plus_tab_common_mem_ptr;
   }
   tab_common_mem = lc3plus_dec_port->tab_common_mem_ptr;

   /* get table_dec memory */
   lc3plus_dec_port->tab_dec_buffer_size = LC3PLUSI_Tab_Dec_Get_MemSize(p_dec_t);
   DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Tab_Dec_Get_MemSize(frame_ms:%d, sr:%d) ret:%d", 3, p_dec_t->frame_ms, p_dec_t->sr, lc3plus_dec_port->tab_dec_buffer_size);
   /* 8byte-align */
   lc3plus_dec_port->tab_dec_buffer_size = (lc3plus_dec_port->tab_dec_buffer_size + 7) / 8 * 8;
   lc3plus_dec_port->tab_dec_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_dec_port->tab_dec_buffer_size);

#if !(defined(ROM_TABLE_ADDR_LC3_PLUS) && defined(ROM_TABLE_ADDR_LC3))
   if (lc3plus_dec_port->tab_dec_mem_ptr == NULL) {
       AUDIO_ASSERT(0);
   }
#endif

   /* table init */
   tab_dec_mem = lc3plus_dec_port->tab_dec_mem_ptr;
   lc3plus_ret = LC3PLUSI_Tab_Dec_Init(tab_common_mem, tab_dec_mem, p_dec_t);
   if (LC3PLUS_OK != lc3plus_ret) {
       DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Tab_Dec_Init Init Fail, %d!", 1, lc3plus_ret);
       AUDIO_ASSERT(0);
   }
   DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Tab_Dec_Init Done!", 0);
#endif

#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
#if defined(ROM_TABLE_ADDR_LC3_PLUS)
    LC3PLUS_Set_ROM_Start(ROM_TABLE_ADDR_LC3_PLUS, ROM_TABLE_ADDR_LC3);
    DSP_MW_LOG_I("[LC3PLUS_DEC] LC3PLUSI_Set_ROM_Start Done!", 0);
#endif
#endif

   /* get working memory and do decoder init */
    switch (lc3plus_dec_port->channel_mode) {
        case LC3PLUS_DEC_CHANNEL_MODE_MONO:
            /* get working memory */
            lc3plus_dec_port->work_instance_count = 1;
            lc3plus_dec_port->work_buffer_size = LC3PLUS_Dec_Get_MemSize(1, lc3plus_dec_port->sample_rate, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
            /* 8byte-align */
            lc3plus_dec_port->work_buffer_size = (lc3plus_dec_port->work_buffer_size + 7) / 8 * 8;
            /* first word is used for plc count */
            lc3plus_dec_port->work_buffer_size += sizeof(uint32_t) * 2;
            lc3plus_dec_port->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_dec_port->work_buffer_size);
            if (lc3plus_dec_port->work_mem_ptr == NULL) {
                AUDIO_ASSERT(0);
            }
            /* plc count init */
            *((uint32_t *)(lc3plus_dec_port->work_mem_ptr)) = LC3PLUS_PLC_MUTE_OUT_THD;
            /* decoder init */
            work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + sizeof(uint32_t) * 2);
            lc3plus_ret = LC3PLUS_Dec_Init(work_mem, lc3plus_dec_port->sample_bits, lc3plus_dec_port->sample_rate, 1, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
            if (LC3PLUS_OK != lc3plus_ret) {
                DSP_MW_LOG_I("[LC3PLUS_DEC] Init Fail, %d!", 1, lc3plus_ret);
                AUDIO_ASSERT(0);
            }
            break;

        case LC3PLUS_DEC_CHANNEL_MODE_STEREO:
            /* get working memory */
            lc3plus_dec_port->work_instance_count = 1;
            lc3plus_dec_port->work_buffer_size = LC3PLUS_Dec_Get_MemSize(2, lc3plus_dec_port->sample_rate, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
            /* 8byte-align */
            lc3plus_dec_port->work_buffer_size = (lc3plus_dec_port->work_buffer_size + 7) / 8 * 8;
            /* first word is used for plc count */
            lc3plus_dec_port->work_buffer_size += sizeof(uint32_t) * 2;
            lc3plus_dec_port->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_dec_port->work_buffer_size);
            if (lc3plus_dec_port->work_mem_ptr == NULL) {
                AUDIO_ASSERT(0);
            }
            /* plc count init */
            *((uint32_t *)(lc3plus_dec_port->work_mem_ptr)) = LC3PLUS_PLC_MUTE_OUT_THD;
            /* decoder init */
            work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + sizeof(uint32_t) * 2);
            lc3plus_ret = LC3PLUS_Dec_Init(work_mem, lc3plus_dec_port->sample_bits, lc3plus_dec_port->sample_rate, 2, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
            if (LC3PLUS_OK != lc3plus_ret) {
                DSP_MW_LOG_I("[LC3PLUS_DEC] Init Fail, %d!", 1, lc3plus_ret);
                AUDIO_ASSERT(0);
            }
            break;

        /* multi-mono-channel mode */
        case LC3PLUS_DEC_CHANNEL_MODE_MULTI_MONO:
            /* get working memory */
            lc3plus_dec_port->work_instance_count = lc3plus_dec_port->in_channel_num;
            lc3plus_dec_port->work_buffer_size = LC3PLUS_Dec_Get_MemSize(1, lc3plus_dec_port->sample_rate, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
            /* 8byte-align */
            lc3plus_dec_port->work_buffer_size = (lc3plus_dec_port->work_buffer_size + 7) / 8 * 8;
            /* first word is used for plc count */
            lc3plus_dec_port->work_buffer_size += sizeof(uint32_t) * 2;
            lc3plus_dec_port->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_dec_port->work_buffer_size * lc3plus_dec_port->work_instance_count);
            if (lc3plus_dec_port->work_mem_ptr == NULL) {
                AUDIO_ASSERT(0);
            }
            /* decoder init one by one channel */
            for (i = 0; i < lc3plus_dec_port->work_instance_count; i++) {
                /* plc count init */
                *((uint32_t *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size)) = LC3PLUS_PLC_MUTE_OUT_THD;
                /* decoder init */
                work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size + sizeof(uint32_t) * 2);
                lc3plus_ret = LC3PLUS_Dec_Init(work_mem, lc3plus_dec_port->sample_bits, lc3plus_dec_port->sample_rate, 1, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
                if (LC3PLUS_OK != lc3plus_ret) {
                    DSP_MW_LOG_I("[LC3PLUS_DEC] Init Fail, %d!", 1, lc3plus_ret);
                    AUDIO_ASSERT(0);
                }
            }
            break;

        /* multi-stereo-channel mode */
        case LC3PLUS_DEC_CHANNEL_MODE_MULTI_STEREO:
            /* get working memory */
            lc3plus_dec_port->work_instance_count = lc3plus_dec_port->in_channel_num;
            lc3plus_dec_port->work_buffer_size = LC3PLUS_Dec_Get_MemSize(2, lc3plus_dec_port->sample_rate, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
            /* 8byte-align */
            lc3plus_dec_port->work_buffer_size = (lc3plus_dec_port->work_buffer_size + 7) / 8 * 8;
            /* first word is used for plc count */
            lc3plus_dec_port->work_buffer_size += sizeof(uint32_t) * 2;
            lc3plus_dec_port->work_mem_ptr = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, lc3plus_dec_port->work_buffer_size * lc3plus_dec_port->work_instance_count);
            if (lc3plus_dec_port->work_mem_ptr == NULL) {
                AUDIO_ASSERT(0);
            }
            /* decoder init one by one channel */
            for (i = 0; i < lc3plus_dec_port->work_instance_count; i++) {
                /* plc count init */
                *((uint32_t *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size)) = LC3PLUS_PLC_MUTE_OUT_THD;
                /* decoder init */
                work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size + sizeof(uint32_t) * 2);
                lc3plus_ret = LC3PLUS_Dec_Init(work_mem, lc3plus_dec_port->sample_bits, lc3plus_dec_port->sample_rate, 2, lc3plus_dec_port->frame_interval/100, lc3plus_dec_port->plc_method);
                if (LC3PLUS_OK != lc3plus_ret) {
                    DSP_MW_LOG_I("[LC3PLUS_DEC] Init Fail, %d!", 1, lc3plus_ret);
                    AUDIO_ASSERT(0);
                }
            }
            break;

        default:
            AUDIO_ASSERT(0);
            break;
    }

    DSP_MW_LOG_I("[lc3plus][dec] init done, version = 0x%8x", 1, LC3PLUS_Get_Version());

    return false;
}
bool stream_codec_decoder_lc3plus_process(void *para)
{
    uint32_t i, j;
    lc3plus_dec_port_para_t *lc3plus_dec_port = NULL;
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
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    void *tab_mem;
#endif
    lc3plus_dec_frame_status_t *p_frame_status;
    uint32_t *p_plc_count;
    LC3PLUS_ErrorCode lc3plus_ret;

    /* find out which port is belong to this stream */
    for (i = 0; i < LC3PLUS_DEC_PORT_MAX; i++) {
        for (j = 0; j < LC3PLUS_DEC_USER_COUNT; j++) {
            /* Check if this source or sink has already be regitsered into this index */
            if ((lc3plus_dec_port_para[i].user[j] == stream_ptr->source) ||
                (lc3plus_dec_port_para[i].user[j] == stream_ptr->sink)) {
                lc3plus_dec_port = &lc3plus_dec_port_para[i];
                goto FIND_DECODER_PORT;
            }
        }
    }
    if (lc3plus_dec_port == NULL) {
        AUDIO_ASSERT(0);
        return true;
    }
FIND_DECODER_PORT:

    in_frame_size = stream_codec_get_input_size(para);
    if(lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t) != in_frame_size){
        lc3plus_dec_port->frame_size = in_frame_size - sizeof(lc3plus_dec_frame_status_t);
        DSP_MW_LOG_I("[LC3PLUS_DEC] Modify for frame_size %d", 1, lc3plus_dec_port->frame_size);
    }
    if (in_frame_size == 0) {
        /* config output size */
        stream_codec_modify_output_size(para, in_frame_size);

        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_dec_port->finish_gpt_count);

        return false;
    }

    if ((in_frame_size % (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t))) != 0) {
        AUDIO_ASSERT(0);
        return true;
    }
#if defined(AIR_BT_LE_LC3PLUS_USE_PIC) && !defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
    tab_mem = lc3plus_dec_port->tab_common_mem_ptr;
#endif

    /* do decoder processs */
    switch (lc3plus_dec_port->channel_mode) {
        case LC3PLUS_DEC_CHANNEL_MODE_MONO:
            total_out_data_size = 0;
            frame_num = in_frame_size / (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t));
            for (currnet_frame = 0; currnet_frame < frame_num; currnet_frame++) {
                out_samples = lc3plus_dec_port->frame_samples;
                if (lc3plus_dec_port->sample_bits == 16)
                {
                    out_data_size = out_samples * sizeof(uint16_t);
                }
                else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
                {
                    out_data_size = out_samples * sizeof(uint32_t);
                }
                else
                {
                    AUDIO_ASSERT(0);
                    return true;
                }
                /* get frame status and input and output buffer of this frame */
                p_frame_status = (lc3plus_dec_frame_status_t *)((uint32_t)stream_codec_get_1st_input_buffer(para) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)));
                in_buf1  = (uint8_t *)((uint32_t)stream_codec_get_1st_input_buffer(para) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)) + sizeof(lc3plus_dec_frame_status_t));
                out_buf1 = (uint8_t *)((uint32_t)stream_codec_get_1st_output_buffer(para) + total_out_data_size);
                /* get working memory and plc count of this channel */
                p_plc_count = (uint32_t *)((uint32_t)(lc3plus_dec_port->work_mem_ptr));
                work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + sizeof(uint32_t) * 2);
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                LOG_AUDIO_DUMP(in_buf1, lc3plus_dec_port->frame_size, AUDIO_CODEC_IN);
#endif
#endif
                /* frame status check */
                if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_NORMAL) {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                    lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0);
#else
                    lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0, &lc3plus_FFTx);
#endif
                    if (LC3PLUS_OK != lc3plus_ret) {
                        DSP_MW_LOG_I("[LC3PLUS_DEC] Process Fail! %d", 1, lc3plus_ret);
                        /* do PLC for avoid this error */
                        *p_frame_status = LC3PLUS_DEC_FRAME_STATUS_PLC;
                        // AUDIO_ASSERT(0);
                    } else {
                        *p_plc_count = 0;
                    }
                }
                if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_PLC) {
                    if ((lc3plus_dec_port->plc_enable == 0) || (*p_plc_count >= LC3PLUS_PLC_MUTE_OUT_THD)) {
                        // memset(out_buf1, 0, out_data_size);
                        uint32_t SampleCnt = out_data_size/sizeof(uint32_t);
                        for (i = 0; i < SampleCnt; i++) {
                            *((uint32_t *)out_buf1 + i) = 0;
                        }
                        if (out_data_size%sizeof(uint32_t) == 0)
                        {
                            /* do nothing */
                        }
                        else if (out_data_size%sizeof(uint32_t) == 2)
                        {
                            *((uint16_t *)(out_buf1 + out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = 0;
                        }
                        else
                        {
                            AUDIO_ASSERT(0);
                        }
                    } else {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0);
#else
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0, &lc3plus_FFTx);
#endif
                        if (LC3PLUS_DECODE_ERROR != lc3plus_ret) {
                            DSP_MW_LOG_I("[LC3PLUS_DEC] PLC Process Fail! %d", 1, lc3plus_ret);
                            // memset(out_buf1, 0, out_data_size);
                            uint32_t SampleCnt = out_data_size/sizeof(uint32_t);
                            for (i = 0; i < SampleCnt; i++) {
                                *((uint32_t *)out_buf1 + i) = 0;
                            }
                            if (out_data_size%sizeof(uint32_t) == 0)
                            {
                                /* do nothing */
                            }
                            else if (out_data_size%sizeof(uint32_t) == 2)
                            {
                                *((uint16_t *)(out_buf1 + out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = 0;
                            }
                            else
                            {
                                AUDIO_ASSERT(0);
                            }
                        }
                        *p_plc_count = (*p_plc_count) + 1;
                    }
                } else if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_BYPASS_DECODER) {
                    /* there is a requirement that the decoder do not output any data */
                    out_data_size = 0;
                    // DSP_MW_LOG_I("[LC3PLUS_DEC] decoder output is 0!", 0);
                }
                if (out_data_size != 0) {
                    /* copy mono data into other channels */
                    for (i = 0; i < lc3plus_dec_port->out_channel_num - 1; i++) {
                        out_buf2 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i + 2) + total_out_data_size);
                        // memcpy(out_buf2, out_buf1, out_data_size);
                        uint32_t SampleCnt = out_data_size/sizeof(uint32_t);
                        for (j = 0; j < SampleCnt; j++) {
                            *((uint32_t *)out_buf2 + j) = *((uint32_t *)out_buf1 + j);
                        }
                        if (out_data_size%sizeof(uint32_t) == 0)
                        {
                            /* do nothing */
                        }
                        else if (out_data_size%sizeof(uint32_t) == 2)
                        {
                            *((uint16_t *)(out_buf2 + out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = *((uint16_t *)(out_buf1 + out_data_size/sizeof(uint32_t)*sizeof(uint32_t)));
                        }
                        else
                        {
                            AUDIO_ASSERT(0);
                        }
                    }
                }
                /* update total output size */
                total_out_data_size += out_data_size;
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                LOG_AUDIO_DUMP(out_buf1, out_data_size, AUDIO_SOURCE_IN_L);
#endif
#endif
            }
            break;

        case LC3PLUS_DEC_CHANNEL_MODE_STEREO:
            total_out_data_size = 0;
            frame_num = in_frame_size / (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t));
            for (currnet_frame = 0; currnet_frame < frame_num; currnet_frame++) {
                out_samples = lc3plus_dec_port->frame_samples;
                if (lc3plus_dec_port->sample_bits == 16)
                {
                    out_data_size = out_samples * sizeof(uint16_t);
                }
                else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
                {
                    out_data_size = out_samples * sizeof(uint32_t);
                }
                else
                {
                    AUDIO_ASSERT(0);
                    return true;
                }
                /* get frame status and input and output buffer of this frame */
                p_frame_status = (lc3plus_dec_frame_status_t *)((uint32_t)stream_codec_get_1st_input_buffer(para) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)));
                in_buf1  = (uint8_t *)((uint32_t)stream_codec_get_1st_input_buffer(para) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)) + sizeof(lc3plus_dec_frame_status_t));
                out_buf1 = (uint8_t *)((uint32_t)stream_codec_get_1st_output_buffer(para) + total_out_data_size);
                out_buf2 = (uint8_t *)((uint32_t)stream_codec_get_2nd_output_buffer(para) + total_out_data_size);
                /* get working memory and plc count of this channel */
                p_plc_count = (uint32_t *)((uint32_t)(lc3plus_dec_port->work_mem_ptr));
                work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + sizeof(uint32_t) * 2);
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                LOG_AUDIO_DUMP(in_buf1, lc3plus_dec_port->frame_size, AUDIO_CODEC_IN);
#endif
#endif
                /* frame status check */
                if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_NORMAL) {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                    lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0);
#else
                    lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0, &lc3plus_FFTx);
#endif
                    if (LC3PLUS_OK != lc3plus_ret) {
                        DSP_MW_LOG_I("[LC3PLUS_DEC] Process Fail! %d", 1, lc3plus_ret);
                        /* do PLC for avoid this error */
                        *p_frame_status = LC3PLUS_DEC_FRAME_STATUS_PLC;
                        // AUDIO_ASSERT(0);
                    } else {
                        *p_plc_count = 0;
                    }
                }
                if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_PLC) {
                    if ((lc3plus_dec_port->plc_enable == 0) || (*p_plc_count >= LC3PLUS_PLC_MUTE_OUT_THD)) {
                        // memset(out_buf1, 0, out_data_size*2);
                        uint32_t SampleCnt = (out_data_size*2)/sizeof(uint32_t);
                        for (i = 0; i < SampleCnt; i++) {
                            *((uint32_t *)out_buf1 + i) = 0;
                        }
                        if ((out_data_size*2)%sizeof(uint32_t) != 0)
                        {
                            AUDIO_ASSERT(0);
                        }
                    } else {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0);
#else
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0, &lc3plus_FFTx);
#endif
                        if (LC3PLUS_DECODE_ERROR != lc3plus_ret) {
                            DSP_MW_LOG_I("[LC3PLUS_DEC] PLC Process Fail! %d", 1, lc3plus_ret);
                            // memset(out_buf1, 0, out_data_size*2);
                            for (i = 0; i < (out_data_size*2)/sizeof(uint32_t); i++) {
                                *((uint32_t *)out_buf1 + i) = 0;
                            }
                            if ((out_data_size*2)%sizeof(uint32_t) != 0)
                            {
                                AUDIO_ASSERT(0);
                            }
                        }
                        *p_plc_count = (*p_plc_count) + 1;
                    }
                } else if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_BYPASS_DECODER) {
                    /* there is a requirement that the decoder do not output any data */
                    out_data_size = 0;
                    // DSP_MW_LOG_I("[LC3PLUS_DEC] decoder output is 0!", 0);
                }
                /* split L/R data into stream buffer ch1 and stream buffer ch2  */
                for (i = 0; i < out_samples; i++)
                {
                    if (lc3plus_dec_port->sample_bits == 16)
                    {
                        *((uint16_t *)out_buf2 + i) = *((uint16_t *)out_buf1 + 2*i + 1);
                        *((uint16_t *)out_buf1 + i) = *((uint16_t *)out_buf1 + 2*i);
                    }
                    else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
                    {
                        *((uint32_t *)out_buf2 + i) = *((uint32_t *)out_buf1 + 2*i + 1);
                        *((uint32_t *)out_buf1 + i) = *((uint32_t *)out_buf1 + 2*i);
                    }
                }
                /* update total output size */
                total_out_data_size += out_data_size;
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                LOG_AUDIO_DUMP(out_buf1, out_data_size, AUDIO_SOURCE_IN_L);
                LOG_AUDIO_DUMP(out_buf2, out_data_size, AUDIO_SOURCE_IN_R);
#endif
#endif
            }
            break;

        case LC3PLUS_DEC_CHANNEL_MODE_MULTI_MONO:
            frame_num = in_frame_size / (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t));
            /* process each channel one by one */
            for (i = 0; i < lc3plus_dec_port->work_instance_count; i++) {
                total_out_data_size = 0;
                /* get working memory and plc count of this channel */
                p_plc_count = (uint32_t *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size);
                work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size + sizeof(uint32_t) * 2);
                for (currnet_frame = 0; currnet_frame < frame_num; currnet_frame++) {
                    out_samples = lc3plus_dec_port->frame_samples;
                    if (lc3plus_dec_port->sample_bits == 16)
                    {
                        out_data_size = out_samples * sizeof(uint16_t);
                    }
                    else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
                    {
                        out_data_size = out_samples * sizeof(uint32_t);
                    }
                    else
                    {
                        AUDIO_ASSERT(0);
                        return true;
                    }
                    /* get frame status and input and output buffer of this frame */
                    p_frame_status = (lc3plus_dec_frame_status_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)));
                    in_buf1  = (uint8_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)) + sizeof(lc3plus_dec_frame_status_t));
                    out_buf1 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i + 1) + total_out_data_size);
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                    if (i == 0) {
                        LOG_AUDIO_DUMP(in_buf1, lc3plus_dec_port->frame_size, AUDIO_CODEC_IN);
                    }
#endif
#endif
                    /* frame status check */
                    if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_NORMAL) {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0);
#else
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0, &lc3plus_FFTx);
#endif
                        if (LC3PLUS_OK != lc3plus_ret) {
                            DSP_MW_LOG_I("[LC3PLUS_DEC] Process Fail! %d", 1, lc3plus_ret);
                            /* do PLC for avoid this error */
                            *p_frame_status = LC3PLUS_DEC_FRAME_STATUS_PLC;
                            // AUDIO_ASSERT(0);
                        } else {
                            *p_plc_count = 0;
                        }
                    }
                    if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_PLC) {
                        if ((lc3plus_dec_port->plc_enable == 0) || (*p_plc_count >= LC3PLUS_PLC_MUTE_OUT_THD)) {
                            // memset(out_buf1, 0, out_data_size);
                            uint32_t SampleCnt = out_data_size/sizeof(uint32_t);
                            for (j = 0; j < SampleCnt; j++) {
                                *((uint32_t *)out_buf1 + j) = 0;
                            }
                            if (out_data_size%sizeof(uint32_t) == 0)
                            {
                                /* do nothing */
                            }
                            else if (out_data_size%sizeof(uint32_t) == 2)
                            {
                                *((uint16_t *)(out_buf1 + out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = 0;
                            }
                            else
                            {
                                AUDIO_ASSERT(0);
                            }
                        } else {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                            lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0);
#else
                            lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0, &lc3plus_FFTx);
#endif
                            if (LC3PLUS_DECODE_ERROR != lc3plus_ret) {
                                DSP_MW_LOG_I("[LC3PLUS_DEC] PLC Process Fail! %d", 1, lc3plus_ret);
                                // memset(out_buf1, 0, out_data_size);
                                for (j = 0; j < out_data_size/sizeof(uint32_t); j++) {
                                    *((uint32_t *)out_buf1 + j) = 0;
                                }
                                if (out_data_size%sizeof(uint32_t) == 0)
                                {
                                    /* do nothing */
                                }
                                else if (out_data_size%sizeof(uint32_t) == 2)
                                {
                                    *((uint16_t *)(out_buf1 + out_data_size/sizeof(uint32_t)*sizeof(uint32_t))) = 0;
                                }
                                else
                                {
                                    AUDIO_ASSERT(0);
                                }
                            }
                            *p_plc_count = (*p_plc_count) + 1;
                        }
                    } else if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_BYPASS_DECODER) {
                        /* there is a requirement that the decoder do not output any data */
                        out_data_size = 0;
                        // DSP_MW_LOG_I("[LC3PLUS_DEC] decoder output is 0!", 0);
                    }
                    /* update total output size */
                    total_out_data_size += out_data_size;
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                    if (i == 0) {
                        LOG_AUDIO_DUMP(out_buf1, out_data_size, AUDIO_SOURCE_IN_L);
                    }
#endif
#endif
                }
            }
            break;

        case LC3PLUS_DEC_CHANNEL_MODE_MULTI_STEREO:
            frame_num = in_frame_size / (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t));
            /* process each channel one by one */
            for (i = 0; i < lc3plus_dec_port->work_instance_count; i++) {
                total_out_data_size = 0;
                /* get working memory and plc count of this channel */
                p_plc_count = (uint32_t *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size);
                work_mem = (void *)((uint32_t)(lc3plus_dec_port->work_mem_ptr) + i * lc3plus_dec_port->work_buffer_size + sizeof(uint32_t) * 2);
                for (currnet_frame = 0; currnet_frame < frame_num; currnet_frame++) {
                    out_samples = lc3plus_dec_port->frame_samples;
                    if (lc3plus_dec_port->sample_bits == 16)
                    {
                        out_data_size = out_samples * sizeof(uint16_t);
                    }
                    else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
                    {
                        out_data_size = out_samples * sizeof(uint32_t);
                    }
                    else
                    {
                        AUDIO_ASSERT(0);
                        return true;
                    }
                    /* get frame status and input and output buffer of this frame */
                    p_frame_status = (lc3plus_dec_frame_status_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)));
                    in_buf1  = (uint8_t *)((uint32_t)stream_codec_get_input_buffer(para, i + 1) + currnet_frame * (lc3plus_dec_port->frame_size + sizeof(lc3plus_dec_frame_status_t)) + sizeof(lc3plus_dec_frame_status_t));
                    out_buf1 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i*2 + 1) + total_out_data_size);
                    out_buf2 = (uint8_t *)((uint32_t)stream_codec_get_output_buffer(para, i*2 + 2) + total_out_data_size);
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                    if (i == 0) {
                        LOG_AUDIO_DUMP(in_buf1, lc3plus_dec_port->frame_size, AUDIO_CODEC_IN);
                    }
#endif
#endif
                    /* frame status check */
                    if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_NORMAL) {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0);
#else
                        lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 0, 0, &lc3plus_FFTx);
#endif
                        if (LC3PLUS_OK != lc3plus_ret) {
                            DSP_MW_LOG_I("[LC3PLUS_DEC] Process Fail! %d", 1, lc3plus_ret);
                            /* do PLC for avoid this error */
                            *p_frame_status = LC3PLUS_DEC_FRAME_STATUS_PLC;
                            // AUDIO_ASSERT(0);
                        } else {
                            *p_plc_count = 0;
                        }
                    }
                    if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_PLC) {
                        if ((lc3plus_dec_port->plc_enable == 0) || (*p_plc_count >= LC3PLUS_PLC_MUTE_OUT_THD)) {
                            // memset(out_buf1, 0, out_data_size*2);
                            for (j = 0; j < (out_data_size*2)/sizeof(uint32_t); j++) {
                                *((uint32_t *)out_buf1 + j) = 0;
                            }
                            if ((out_data_size*2)%sizeof(uint32_t) != 0)
                            {
                                AUDIO_ASSERT(0);
                            }
                        } else {
#if !defined(AIR_BT_LE_LC3PLUS_USE_PIC) || defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE)
                            lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0);
#else
                            lc3plus_ret = LC3PLUS_Dec_Prcs(work_mem, tab_mem, (uint8_t *)in_buf1, (uint8_t *)out_buf1, lc3plus_dec_port->frame_size, 1, 0, &lc3plus_FFTx);
#endif
                            if (LC3PLUS_DECODE_ERROR != lc3plus_ret) {
                                DSP_MW_LOG_I("[LC3PLUS_DEC] PLC Process Fail! %d", 1, lc3plus_ret);
                                // memset(out_buf1, 0, out_data_size*2);
                                for (j = 0; j < (out_data_size*2)/sizeof(uint32_t); j++) {
                                    *((uint32_t *)out_buf1 + j) = 0;
                                }
                                if ((out_data_size*2)%sizeof(uint32_t) != 0)
                                {
                                    AUDIO_ASSERT(0);
                                }
                            }
                            *p_plc_count = (*p_plc_count) + 1;
                        }
                    } else if (*p_frame_status == LC3PLUS_DEC_FRAME_STATUS_BYPASS_DECODER) {
                        /* there is a requirement that the decoder do not output any data */
                        out_data_size = 0;
                        // DSP_MW_LOG_I("[LC3PLUS_DEC] decoder output is 0!", 0);
                    }
                    /* split L/R data into stream buffer ch1 and stream buffer ch2  */
                    for (j = 0; j < out_samples; j++)
                    {
                        if (lc3plus_dec_port->sample_bits == 16)
                        {
                            *((uint16_t *)out_buf2 + j) = *((uint16_t *)out_buf1 + 2*j + 1);
                            *((uint16_t *)out_buf1 + j) = *((uint16_t *)out_buf1 + 2*j);
                        }
                        else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
                        {
                            *((uint32_t *)out_buf2 + j) = *((uint32_t *)out_buf1 + 2*j + 1);
                            *((uint32_t *)out_buf1 + j) = *((uint32_t *)out_buf1 + 2*j);
                        }
                    }
                    /* update total output size */
                    total_out_data_size += out_data_size;
#ifdef AIR_AUDIO_DUMP_ENABLE
#if !defined(AIR_ULL_AUDIO_V2_DONGLE_ENABLE) && !defined(AIR_BLE_AUDIO_DONGLE_ENABLE)
                    if (i == 0) {
                        LOG_AUDIO_DUMP(out_buf1, out_data_size, AUDIO_SOURCE_IN_L);
                        LOG_AUDIO_DUMP(out_buf2, out_data_size, AUDIO_SOURCE_IN_R);
                    }
#endif
#endif
                }
            }
            break;

        default:
            AUDIO_ASSERT(0);
            break;
    }

    stream_codec_modify_output_samplingrate(para, lc3plus_dec_port->sample_rate / 1000);
    stream_codec_modify_output_size(para, total_out_data_size);
    if (lc3plus_dec_port->sample_bits == 16)
    {
        stream_codec_modify_resolution(para, RESOLUTION_16BIT);
    }
    else if ((lc3plus_dec_port->sample_bits == 24) || (lc3plus_dec_port->sample_bits == 32))
    {
        stream_codec_modify_resolution(para, RESOLUTION_32BIT);
    }

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&lc3plus_dec_port->finish_gpt_count);

    return false;
}
#endif /* AIR_BT_LE_LC3PLUS_ENABLE */
