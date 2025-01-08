/* Copyright Statement:
*
* (C) 2020 Airoha Technology Corp. All rights reserved.
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

/* Includes ------------------------------------------------------------------*/
#include "dsp_feature_interface.h"
#include "dsp_audio_process.h"
#include "celt_enc_interface.h"
#include "dsp_dump.h"
#include "memory_attribute.h"
#include "preloader_pisplit.h"


/* Private define ------------------------------------------------------------*/
#define CELT_ENC_DEBUG_LOG                  0
#define CELT_ENC_DEBUG_DUMP                 0

#if defined(AIR_GAMING_MODE_DONGLE_ENABLE)
#define AIROHA_CELT_ENC_SAMPLE_RATE       ((int)48000)
#define AIROHA_CELT_ENC_CHANNEL_NO        ((int)2)
#define AIROHA_CELT_ENC_IN_FRAME_SIZE     ((int)120)
#define AIROHA_CELT_ENC_IN_BYTES          ((int)80)
#define AIROHA_CELT_ENC_COMPLEXITY        ((int)0)
#define AIROHA_CELT_ENC_PROCESS_FRAME_NUM ((int)1)
#else
#define AIROHA_CELT_ENC_SAMPLE_RATE       ((int)16000)
#define AIROHA_CELT_ENC_CHANNEL_NO        ((int)1)
#define AIROHA_CELT_ENC_IN_FRAME_SIZE     ((int)120)
#define AIROHA_CELT_ENC_IN_BYTES          ((int)47)
#define AIROHA_CELT_ENC_COMPLEXITY        ((int)0)
     #if defined(AIR_ULL_VOICE_LOW_LATENCY_ENABLE)
           #define AIROHA_CELT_ENC_PROCESS_FRAME_NUM ((int)1)
     #else
           #define AIROHA_CELT_ENC_PROCESS_FRAME_NUM ((int)2)
     #endif
#endif

#ifdef MTK_BT_CELT_USE_PIC
#include "celt_portable.h"
#endif


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    CELT_ENC_STATUS_DEINIT = 0,
    CELT_ENC_STATUS_INIT = 1,
    CELT_ENC_STATUS_RUNNING = 2
} celt_enc_status_t;


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static celt_enc_status_t celt_enc_status = CELT_ENC_STATUS_DEINIT;
static uint8_t celt_enc_count = 0;


/* Public variables ----------------------------------------------------------*/
void *opusEncInstance;
CELT_ENC_PARA gCeltEncPara = {
    .SampleRate     = AIROHA_CELT_ENC_SAMPLE_RATE,
    .ChannelNo      = AIROHA_CELT_ENC_CHANNEL_NO,
    .InFrameSize    = AIROHA_CELT_ENC_IN_FRAME_SIZE,
    .OutEncBytes    = AIROHA_CELT_ENC_IN_BYTES,
    .Complexity     = AIROHA_CELT_ENC_COMPLEXITY,
    .InputSamples   = 0,
    .RemainSamples  = 0,
    .RemainMemPtr   = NULL,
    .WorkMemPtr     = NULL
};

volatile uint32_t celt_enc_finish_gpt_count = 0;


/* Private functions ---------------------------------------------------------*/
#if defined(AIR_GAMING_MODE_DONGLE_ENABLE)
/**
 * @brief This function is used to merge two channels data into one channel data.
 *
 * @param inBufL is the first channel input data.
 * @param inBufR is the second channel input data.
 * @param outBuf is the output data channel.
 * @param inSamples is the sample sizes.
 */
ATTR_TEXT_IN_IRAM static void dsp_16bit_interleave(int16_t *inBufL, int16_t *inBufR, int16_t *outBuf, uint32_t inSamples)
{
    uint32_t i;

    for (i = 0 ; i < inSamples ; i++) {
        outBuf[inSamples*2-1-i*2]   = inBufR[inSamples-1-i];
        outBuf[inSamples*2-1-i*2-1] = inBufL[inSamples-1-i];
    }
}
#endif /* AIR_GAMING_MODE_DONGLE_ENABLE */

void stream_codec_encoder_celt_set_input_frame_size(uint32_t input_frame_size)
{
    gCeltEncPara.OutEncBytes = input_frame_size;
}

/* Public functions ----------------------------------------------------------*/
void stream_codec_encoder_celt_init(uint32_t data_size)
{
    uint32_t saved_mask;
    bool mem_flag = false;

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (celt_enc_count == 0)
    {
        celt_enc_status = CELT_ENC_STATUS_INIT;
        gCeltEncPara.RemainSamples = 0;

        /* set memory operation flag */
        mem_flag = true;
    }

    celt_enc_count += 1;
    if (celt_enc_count == 0)
    {
        AUDIO_ASSERT(0);
    }

    hal_nvic_restore_interrupt_mask(saved_mask);

    if (mem_flag)
    {
        /* get remain samples memory */
        gCeltEncPara.RemainMemPtr = preloader_pisplit_malloc_memory( PRELOADER_D_HIGH_PERFORMANCE , data_size);
        if (gCeltEncPara.RemainMemPtr == NULL)
        {
            AUDIO_ASSERT(0);
        }
    }
}

void stream_codec_encoder_celt_deinit(void)
{
    uint32_t saved_mask;
    bool mem_flag = false;
    void *WorkMemPtr;
    void *RemainMemPtr;

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    if (celt_enc_count == 0)
    {
        AUDIO_ASSERT(0);
    }

    celt_enc_count -= 1;
    if (celt_enc_count == 0)
    {
        celt_enc_status = CELT_ENC_STATUS_DEINIT;
        gCeltEncPara.RemainSamples = 0;

        /* backup working memory pointer */
        WorkMemPtr = gCeltEncPara.WorkMemPtr;
        gCeltEncPara.WorkMemPtr = NULL;

        /* backup remain samples memory pointer */
        RemainMemPtr = gCeltEncPara.RemainMemPtr;
        gCeltEncPara.RemainMemPtr = NULL;

        /* set memory operation flag */
        mem_flag = true;
    }

    hal_nvic_restore_interrupt_mask(saved_mask);

    if (mem_flag)
    {
        /* free working memory */
        preloader_pisplit_free_memory(WorkMemPtr);

        /* free remain samples memory */
        preloader_pisplit_free_memory(RemainMemPtr);
    }
}

/**
 * @brief This function is used to initialize the celt encoder run-time environment.
 *
 * @param para is the input parameters.
 * @return true means there is a error.
 * @return false means there is no error.
 */
bool stream_codec_encoder_celt_initialize(void *para)
{
#if defined(AIR_GAMING_MODE_DONGLE_ENABLE)
    UNUSED(para);
    void *scractchPtr = NULL;
    uint32_t saved_mask;
    int32_t memSize;

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);

    /* status check */
    if (celt_enc_status == CELT_ENC_STATUS_INIT)
    {
        celt_enc_status = CELT_ENC_STATUS_RUNNING;
    }
    else if (celt_enc_status == CELT_ENC_STATUS_RUNNING)
    {
        hal_nvic_restore_interrupt_mask(saved_mask);
        return FALSE;
    }
    else
    {
        DSP_MW_LOG_I("[CELT_ENC] error status:%d", 1, celt_enc_status);
        AUDIO_ASSERT(FALSE);
        return TRUE;
    }

    hal_nvic_restore_interrupt_mask(saved_mask);

    /* Because celt API maybe is PIC, so we need to get working memory here for safety */
    memSize = celt_encode_get_size(gCeltEncPara.SampleRate, gCeltEncPara.ChannelNo, gCeltEncPara.InFrameSize, (int)stream_codec_celt_get_version());
    gCeltEncPara.WorkMemPtr = preloader_pisplit_malloc_memory( PRELOADER_D_HIGH_PERFORMANCE , memSize);
    if (gCeltEncPara.WorkMemPtr == NULL)
    {
        AUDIO_ASSERT(0);
    }

    scractchPtr = gCeltEncPara.WorkMemPtr;

#else
    int32_t memSize = celt_encode_get_size(gCeltEncPara.SampleRate, gCeltEncPara.ChannelNo, gCeltEncPara.InFrameSize, (int)stream_codec_celt_get_version());
    void *scractchPtr = (void *)stream_codec_get_workingbuffer(para);

    if (memSize > DSP_CELT_ENC_MEMSIZE)
    {
        DSP_MW_LOG_I("[CELT_ENC] MemSize not enough! Required size:%d", 1, memSize);
        AUDIO_ASSERT(FALSE);
        return TRUE;
    }
#endif /*defined(AIR_GAMING_MODE_DONGLE_ENABLE)*/

    if (celt_encode_init(&opusEncInstance, scractchPtr, gCeltEncPara.SampleRate, gCeltEncPara.ChannelNo, gCeltEncPara.InFrameSize, gCeltEncPara.Complexity, gCeltEncPara.OutEncBytes, (int)stream_codec_celt_get_version()) != 0)
    {
        DSP_MW_LOG_I("[CELT_ENC] Init Fail!", 0);
        return TRUE;
    }

    DSP_MW_LOG_I("[CELT_ENC] Init Success, version = 0x%x!", 1, celt_codec_get_version());

    return FALSE;
}

/**
 * @brief This function is used to do the celt encode process.
 *
 * @param para is the input parameters.
 * @return true means there is a error.
 * @return false means there is no error.
 */
ATTR_TEXT_IN_IRAM bool stream_codec_encoder_celt_process(void *para)
{
#if defined(AIR_GAMING_MODE_DONGLE_ENABLE)
    U16* OutBufL     = stream_codec_get_1st_output_buffer(para);
    U16* OutBufR     = stream_codec_get_2nd_output_buffer(para);
    U16  OutLength   = stream_codec_get_input_size(para);
    U16* IntBuf      = (U16 *)(gCeltEncPara.RemainMemPtr);
    U16  OutEncBytes = 0;
    uint32_t i;

    #if CELT_ENC_DEBUG_LOG
    uint32_t current_timestamp = 0;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &current_timestamp);
    DSP_MW_LOG_I("[CELT_ENC][start]: %u, %u, %d", 3, (uint32_t)IntBuf, current_timestamp, hal_nvic_query_exception_number());
    #endif /* CELT_ENC_DEBUG_LOG */

    /* copy data into the tail of the internal buffer */
    dsp_16bit_interleave((int16_t *)OutBufL, (int16_t *)OutBufR, (int16_t *)(IntBuf+gCeltEncPara.RemainSamples*2), OutLength/sizeof(int16_t));
    gCeltEncPara.RemainSamples += OutLength/sizeof(int16_t);
    gCeltEncPara.InputSamples = OutLength/sizeof(int16_t);

    /* when the data in the interbal buffer is enough, do encode */
    while(gCeltEncPara.RemainSamples >= (uint32_t)gCeltEncPara.InFrameSize)
    {
        /* do encoder */
        celt_encode_prcs(opusEncInstance, (const int16_t *)IntBuf, gCeltEncPara.InFrameSize, (unsigned char *)OutBufL, gCeltEncPara.OutEncBytes);

        /* update remain samples */
        gCeltEncPara.RemainSamples -= gCeltEncPara.InFrameSize;

        /* move remain data to the header and offset out buffer pointer */
        for (i = 0; i < gCeltEncPara.RemainSamples; i++)
        {
            *((U32 *)IntBuf + i) = *((U32 *)IntBuf + gCeltEncPara.InFrameSize + i);
        }
        OutBufL = (U16 *)((U8 *)OutBufL + gCeltEncPara.OutEncBytes);

        /* update out length */
        OutEncBytes += gCeltEncPara.OutEncBytes;
    }

    /* set the output size */
    stream_codec_modify_output_size(para, OutEncBytes);

    #if CELT_ENC_DEBUG_LOG
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &current_timestamp);
    DSP_MW_LOG_I("[CELT_ENC][finish]: %d, %d, %d, %u, %d", 5, OutLength, OutEncBytes, gCeltEncPara.RemainSamples, current_timestamp, hal_nvic_query_exception_number());
    #endif /* CELT_ENC_DEBUG_LOG */

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, (uint32_t *)&celt_enc_finish_gpt_count);

#else

    S16* InBufL = stream_codec_get_1st_input_buffer(para);
    S16* OutBuf = stream_codec_get_1st_output_buffer(para);
    U8 TempBuf[AIROHA_CELT_ENC_IN_BYTES*AIROHA_CELT_ENC_PROCESS_FRAME_NUM];
    U8 i,EncodeTimes,BytesPerSample;
    BytesPerSample = (stream_function_get_output_resolution(para) == RESOLUTION_32BIT) ? 4 : 2;
    EncodeTimes = AIROHA_CELT_ENC_PROCESS_FRAME_NUM;

    //printf("[CELT] %d %d %d %d %d", gCeltEncPara.SampleRate, gCeltEncPara.InFrameSize, gCeltEncPara.ChannelNo, gCeltEncPara.OutEncBytes, gCeltEncPara.Complexity);
    //memset(InBufL, 0, gCeltEncPara.InFrameSize*EncodeTimes*BytesPerSample);

    #ifdef AIR_AUDIO_DUMP_ENABLE
    LOG_AUDIO_DUMP((U8*)InBufL, gCeltEncPara.InFrameSize*EncodeTimes*BytesPerSample, AUDIO_SOUNDBAR_INPUT);
    #endif

    for(i = 0; i< EncodeTimes; i++) {
        celt_encode_prcs(opusEncInstance,
                         InBufL + i*gCeltEncPara.InFrameSize,
                         gCeltEncPara.InFrameSize,
                         &TempBuf[i*gCeltEncPara.OutEncBytes],
                         gCeltEncPara.OutEncBytes);
    }
    memcpy(OutBuf, (U8*)(&TempBuf[0]), gCeltEncPara.OutEncBytes*EncodeTimes);
    stream_codec_modify_output_size(para, gCeltEncPara.OutEncBytes);

    #ifdef AIR_AUDIO_DUMP_ENABLE
    LOG_AUDIO_DUMP((U8*)OutBuf, gCeltEncPara.OutEncBytes*EncodeTimes, AUDIO_SOUNDBAR_TX);
    #endif

#endif /*defined(AIR_GAMING_MODE_DONGLE_ENABLE)*/

    return FALSE;
}

