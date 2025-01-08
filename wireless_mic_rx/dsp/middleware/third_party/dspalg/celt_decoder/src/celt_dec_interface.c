/* Copyright Statement:
 *
 * (C) 2019  Airoha Technology Corp. All rights reserved.
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
#ifdef MTK_CELT_DEC_ENABLE
#include "dsp_feature_interface.h"
#include "dsp_audio_process.h"
#include "celt_dec_interface.h"
#include "dsp_dump.h"
#include "bt_types.h"

/**
 *
 *  Definition
 *
 */
#if defined(AIR_GAMING_MODE_DONGLE_ENABLE)
#define AIROHA_CELT_DEC_USE_PLC         (FALSE)
#define AIROHA_CELT_DEC_PROFILING       (FALSE)
#define AIROHA_CELT_DEC_SAMPLE_RATE     ((int)16000)
#define AIROHA_CELT_DEC_CHANNEL_NO      ((int)1)
#define AIROHA_CELT_OUT_FRAME_SIZE      ((int)120)
#define AIROHA_CELT_DEC_IN_BYTES        ((int)47)
#define AIROHA_CELT_DEC_PLC_ENABLE      ((int)1)
#else
#define AIROHA_CELT_DEC_USE_PLC         (TRUE) // temp disable PLC
#define AIROHA_CELT_DEC_PROFILING       (FALSE)
#define AIROHA_CELT_DEC_SAMPLE_RATE     ((int)48000)
#define AIROHA_CELT_DEC_CHANNEL_NO      ((int)2)
#define AIROHA_CELT_OUT_FRAME_SIZE      ((int)120)
#define AIROHA_CELT_DEC_IN_BYTES        ((int)80)
#define AIROHA_CELT_DEC_PLC_ENABLE      ((int)1)
#endif

#define PlcCountMax 5
#define CELT_DEC_DEBUG_LOG              0
#define CELT_DEC_DEBUG_DUMP             0
#define GAMING_MODE_MUSIC_DONGLE_DEBUG_LANTENCY     0

#ifdef MTK_BT_CELT_USE_PIC
#include "celt_portable.h"
#endif

/**
 *
 *  Type Definition
 *
 */
typedef struct {
    int32_t SampleRate;
    int32_t ChannelNo;
    int32_t OutFrameSize;
    int32_t InDecBytes;
    int32_t PLCStatus;
} CELT_DEC_PARA,*CELT_DEC_PARA_PTR;



/**
 *
 *  Variables
 *
 */
void* opusDecInstance;
CELT_DEC_PARA gCeltDecPara = {
    .SampleRate     = AIROHA_CELT_DEC_SAMPLE_RATE,
    .ChannelNo      = AIROHA_CELT_DEC_CHANNEL_NO,
    .OutFrameSize   = AIROHA_CELT_OUT_FRAME_SIZE,
    .InDecBytes     = AIROHA_CELT_DEC_IN_BYTES,
    .PLCStatus      = AIROHA_CELT_DEC_PLC_ENABLE,
};
U8 PlcCount;

/**
 *
 * Function Prototype
 *
 */
BOOL a2dp_is_mute_packet (uint8_t* Addr);
bool stream_codec_decoder_celt_initialize (void *para);
bool stream_codec_decoder_celt_process (void *para);


VOID dsp_16bit_deinterleave(int16_t* inBuf, int16_t* outBufL, int16_t* outBufR, uint32_t inSamples)
{
    uint32_t i;

    for (i = 0 ; i < inSamples ; i++) {
        outBufL[i] = inBuf[2*i];
        outBufR[i] = inBuf[2*i+1];
    }
}

void stream_codec_decoder_celt_set_input_frame_size(uint32_t input_frame_size)
{
    gCeltDecPara.InDecBytes = input_frame_size;
}


bool stream_codec_decoder_celt_initialize (void *para)
{
    int32_t memSize = celt_decode_get_size(gCeltDecPara.SampleRate, gCeltDecPara.ChannelNo, gCeltDecPara.OutFrameSize, (int)stream_codec_celt_get_version());
    int32_t skip;
    void* scractchPtr = (void*)stream_codec_get_workingbuffer(para);

    if (memSize > DSP_CELT_DEC_MEMSIZE) {
        DSP_MW_LOG_I("[CELT_DEC] MemSize not enough! Required size:%d", 1, memSize);
        AUDIO_ASSERT(FALSE);
    }

    if (celt_decode_init(&opusDecInstance, scractchPtr, gCeltDecPara.SampleRate, gCeltDecPara.ChannelNo, gCeltDecPara.OutFrameSize, &skip, gCeltDecPara.InDecBytes, (int)stream_codec_celt_get_version()) != 0) {
        DSP_MW_LOG_I("[CELT_DEC] Init Fail!", 0);
        return TRUE;
    }
    PlcCount = PlcCountMax;

    DSP_MW_LOG_I("[CELT_DEC] Init Success, version = 0x%x!", 1, celt_codec_get_version());

    return FALSE;
}

#if defined(AIR_GAMING_MODE_DONGLE_ENABLE)
bool stream_codec_decoder_celt_process (void *para)
{
    U8* InBuf = stream_codec_get_1st_input_buffer(para);
    S32* OutBufL = stream_codec_get_1st_output_buffer(para);
    S32* OutBufR = stream_codec_get_2nd_output_buffer(para);
    U16 OutLength = gCeltDecPara.OutFrameSize*sizeof(U16);

    #if CELT_DEC_DEBUG_LOG
    uint32_t current_timestamp = 0;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &current_timestamp);
    DSP_MW_LOG_I("[CELT_DEC][start]: %u, %u, %d", 3, (uint32_t)InBuf, current_timestamp, hal_nvic_query_exception_number());
    #endif /* CELT_DEC_DEBUG_LOG */

    /* PLC check */
    if ((*(InBuf+0) == 0) &&
        (*(InBuf+1) == 0) &&
        (*(InBuf+2) == 0) &&
        (*(InBuf+3) == 0))
    {
        if (PlcCount < PlcCountMax)
        {
            PlcCount ++ ;
            /* there is a packet lost */
            celt_decode_prcs(opusDecInstance, NULL, gCeltDecPara.InDecBytes, (int16_t*)OutBufL, gCeltDecPara.OutFrameSize, 1);
        }
        else
        {
            memset(OutBufL, 0, OutLength);
        }
    }
    else if ((*(InBuf+0) == 0) &&
        (*(InBuf+1) == 0) &&
        (*(InBuf+2) == 0xa5) &&
        (*(InBuf+3) == 0xa5))
    {
        /* there is a requirement that the decoder do not output any data */
        stream_codec_modify_output_size(para, 0);
        // DSP_MW_LOG_I("[CELT_DEC] decoder output is 0!", 0);
        return FALSE;
    }
    else
    {
        PlcCount = 0;
        /* there is not a packet lost */
        celt_decode_prcs(opusDecInstance, InBuf, gCeltDecPara.InDecBytes, (int16_t*)OutBufL, gCeltDecPara.OutFrameSize, 0);
    }
    memcpy(OutBufR, OutBufL, OutLength);

    stream_codec_modify_resolution(para, RESOLUTION_16BIT);
    stream_codec_modify_output_samplingrate(para, FS_RATE_16K);
    stream_codec_modify_output_size(para, OutLength);
    ((DSP_ENTRY_PARA_PTR)para)->out_channel_num = 2;

    #if CELT_DEC_DEBUG_LOG
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &current_timestamp);
    DSP_MW_LOG_I("[CELT_DEC][finish]: %d, %u, %d", 3, OutLength, current_timestamp, hal_nvic_query_exception_number());
    #endif /* CELT_DEC_DEBUG_LOG */

    return FALSE;
}
#else
#if (AIROHA_CELT_DEC_PROFILING)
#define MIPS_AVERGE_TIMES (100)
uint32_t mips_cnt[MIPS_AVERGE_TIMES];
uint32_t mips_idx;
long long mips_sum;
#endif

ATTR_TEXT_IN_IRAM_LEVEL_2 bool stream_codec_decoder_celt_process (void *para)
{
    U8* InBuf = stream_codec_get_1st_input_buffer(para);
    S32* OutBufL = stream_codec_get_1st_output_buffer(para);
    S32* OutBufR = stream_codec_get_2nd_output_buffer(para);
    U16 InLength = stream_codec_get_input_size(para);
    U16 OutLength = gCeltDecPara.OutFrameSize*sizeof(U16);

    uint32_t start_time, end_time;


    if (!InLength) {
        stream_codec_modify_output_size(para, 0);
        return FALSE;
    }

    if (a2dp_is_mute_packet(InBuf)) {

        #if (AIROHA_CELT_DEC_USE_PLC)

        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);

        memset(OutBufL, 0, OutLength);
        memset(OutBufR, 0, OutLength);

#ifdef AIR_AUDIO_DUMP_ENABLE
        LOG_AUDIO_DUMP((U8*)OutBufL,
                        OutLength,
                        VOICE_RX_PLC_IN);
#endif

        /* PLC */
        if (PlcCount < PlcCountMax)
        {
            PlcCount ++ ;
            celt_decode_prcs(opusDecInstance, NULL, gCeltDecPara.InDecBytes, (int16_t*)OutBufL, gCeltDecPara.OutFrameSize, 1);
            #if GAMING_MODE_MUSIC_DONGLE_DEBUG_LANTENCY
            extern VOID MCE_GetBtClk(BTCLK* pCurrCLK, BTPHASE* pCurrPhase,BT_CLOCK_OFFSET_SCENARIO type);
            uint8_t data[4+4+80];
            uint32_t bt_clk;
            uint16_t bt_phase;
            MCE_GetBtClk((BTCLK*)&bt_clk, (BTPHASE*)&bt_phase,BT_CLK_Offset);
            *((uint32_t *)data+0) = 0xdeadbeef;
            *((uint32_t *)data+1) = bt_clk;
            memcpy(data+4+4, (uint8_t *)(InBuf), 80);
            LOG_AUDIO_DUMP(data, 4+4+80, 13);
            #endif /* GAMING_MODE_MUSIC_DONGLE_DEBUG_LANTENCY */

            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
            DSP_MW_LOG_I("celt PLC time:%d\r\n", 1, (uint32_t)(end_time-start_time));
            dsp_16bit_deinterleave((int16_t*)OutBufL, (int16_t*)OutBufL, (int16_t*)OutBufR, gCeltDecPara.ChannelNo*gCeltDecPara.OutFrameSize);
        }
#ifdef AIR_AUDIO_DUMP_ENABLE
        LOG_AUDIO_DUMP((U8*)OutBufL,
                        OutLength,
                        VOICE_RX_PLC_OUT);
#endif

        if (stream_codec_get_output_resolution(para) == RESOLUTION_32BIT)
        {
            dsp_converter_16bit_to_32bit(OutBufL, (S16*)OutBufL, OutLength/sizeof(S16));
            dsp_converter_16bit_to_32bit(OutBufR, (S16*)OutBufR, OutLength/sizeof(S16));
            OutLength *= 2 ;
        }

        #else
        if (stream_codec_get_output_resolution(para) == RESOLUTION_32BIT)
        {
            dsp_converter_16bit_to_32bit(OutBufL, (S16*)OutBufL, OutLength/sizeof(S16));
            dsp_converter_16bit_to_32bit(OutBufR, (S16*)OutBufR, OutLength/sizeof(S16));
            OutLength = OutLength*2;
        }

        memset(OutBufL, 0, OutLength);
        memset(OutBufR, 0, OutLength);

        stream_codec_modify_output_size(para, OutLength);
        #endif

    } else {

#ifdef AIR_AUDIO_DUMP_ENABLE
        LOG_AUDIO_DUMP((U8*)InBuf,
                        gCeltDecPara.InDecBytes,
                        AUDIO_CODEC_IN);
#endif

        #if (AIROHA_CELT_DEC_PROFILING)
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &start_time);
        #endif
        PlcCount = 0;
        celt_decode_prcs(opusDecInstance, InBuf, gCeltDecPara.InDecBytes, (int16_t*)OutBufL, gCeltDecPara.OutFrameSize, 0);

        #if GAMING_MODE_MUSIC_DONGLE_DEBUG_LANTENCY
        extern VOID MCE_GetBtClk(BTCLK* pCurrCLK, BTPHASE* pCurrPhase,BT_CLOCK_OFFSET_SCENARIO type);
        uint8_t data[4+4+80];
        uint32_t bt_clk;
        uint16_t bt_phase;
        MCE_GetBtClk((BTCLK*)&bt_clk, (BTPHASE*)&bt_phase,BT_CLK_Offset);
        *((uint32_t *)data+0) = 0x0;
        *((uint32_t *)data+1) = bt_clk;
        memcpy(data+4+4, (uint8_t *)(InBuf), 80);
        LOG_AUDIO_DUMP(data, 4+4+80, 13);
        #endif /* GAMING_MODE_MUSIC_DONGLE_DEBUG_LANTENCY */

        #if (AIROHA_CELT_DEC_PROFILING)
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &end_time);
        #endif

        dsp_16bit_deinterleave((int16_t*)OutBufL, (int16_t*)OutBufL, (int16_t*)OutBufR, gCeltDecPara.ChannelNo*gCeltDecPara.OutFrameSize);

#ifdef AIR_AUDIO_DUMP_ENABLE
        LOG_AUDIO_DUMP((U8*)OutBufL,
                        OutLength,
                        VOICE_RX_PLC_IN);

        LOG_AUDIO_DUMP((U8*)OutBufL,
                        OutLength,
                        VOICE_RX_PLC_OUT);
#endif

        #if (AIROHA_CELT_DEC_PROFILING)
        mips_cnt[mips_idx] = (end_time-start_time);

        if (MIPS_AVERGE_TIMES-1 == mips_idx) {
            mips_sum = 0;
            for (uint32_t idx = 0 ; idx < MIPS_AVERGE_TIMES ; idx++) {
                mips_sum += mips_cnt[idx];
            }
            mips_sum /= MIPS_AVERGE_TIMES;

            DSP_MW_LOG_I("celt dec time:%d\r\n", 1, (uint32_t)(mips_sum));
        }

        mips_idx = (mips_idx + 1) % MIPS_AVERGE_TIMES;
        #endif

#ifdef AIR_AUDIO_DUMP_ENABLE
        LOG_AUDIO_DUMP((U8*)OutBufL,
                        OutLength,
                        AUDIO_SOURCE_IN_L);

        LOG_AUDIO_DUMP((U8*)OutBufR,
                        OutLength,
                        AUDIO_SOURCE_IN_R);
#endif

        if (stream_codec_get_output_resolution(para) == RESOLUTION_32BIT)
        {
            dsp_converter_16bit_to_32bit(OutBufL, (S16*)OutBufL, OutLength/sizeof(S16));
            dsp_converter_16bit_to_32bit(OutBufR, (S16*)OutBufR, OutLength/sizeof(S16));
            OutLength *= 2 ;
        }
    }

    stream_codec_modify_resolution(para, stream_codec_get_output_resolution(para));
    stream_codec_modify_output_size(para, OutLength);

    return FALSE;
}
#endif

#endif

