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

#ifdef AIR_BT_CODEC_BLE_ENABLED

#include "types.h"
#include "stream_audio.h"
#include "source_inter.h"
#include "sink_inter.h"
#include "transform.h"
#include "stream_n9ble.h"
#include "dsp_audio_msg.h"
#include "audio_config.h"
#include "dsp_audio_process.h"
#include "dsp_memory.h"
#include "dsp_share_memory.h"
#include "dsp_temp.h"
#include "dsp_dump.h"
#ifdef AIR_BT_CLK_SKEW_ENABLE
#include "clk_skew.h"
#endif
#include "source_inter.h"
#include "audio_nvdm_common.h"
#ifdef AIR_AUDIO_TRANSMITTER_ENABLE
#include "stream_audio_transmitter.h"
#endif /* AIR_AUDIO_TRANSMITTER_ENABLE */
#ifdef AIR_BT_LE_LC3PLUS_ENABLE
#include "lc3plus_dec_interface.h"
#include "lc3plus_enc_interface.h"
#endif
#if defined(AIR_CELT_DEC_V2_ENABLE)
#include "celt_dec_interface_v2.h"
#endif /* AIR_CELT_DEC_V2_ENABLE */

#if defined(AIR_CELT_ENC_V2_ENABLE)
#include "celt_enc_interface_v2.h"
#endif /* AIR_CELT_ENC_V2_ENABLE */
#ifdef MTK_PEQ_ENABLE
#include "peq_interface.h"
#endif
#include "bt_interface.h"


Stream_n9ble_Config_t N9BLE_setting;
static bool g_ble_pkt_lost[4][2];
static uint32_t g_pkt_lost_count = 0;

uint16_t g_ble_abr_length=0;
uint16_t g_ble_ul_abr_length=0;

#ifdef AIR_BLE_FEATURE_MODE_ENABLE
static bool g_ble_dl_ul_process_active;
#endif
extern bool ULL_NrOffloadFlag;
#ifdef AIR_ECNR_PREV_PART_ENABLE
extern uint8_t voice_ecnr_ec_get_postec_gain(void);
#endif

static U16 N9Ble_calculate_avm_frame_num(U16 avm_buffer_length, U16 frame_length){
    return (avm_buffer_length/ALIGN_4(frame_length + BLE_AVM_FRAME_HEADER_SIZE));
}

static U32 N9Ble_check_avm_frame_valid(LE_AUDIO_HEADER *buf_header, U32 check_abr)
{
    U32 frame_valid = (buf_header->TimeStamp != BLE_AVM_INVALID_TIMESTAMP) && (buf_header->_reserved_byte_0Dh & 0x01);
    if(frame_valid && check_abr) {
        frame_valid = (buf_header->Pdu_LEN_Without_MIC) && (g_ble_abr_length == buf_header->Pdu_LEN_Without_MIC);
    }
    return frame_valid;
}

ATTR_TEXT_IN_IRAM static VOID N9BleRx_update_from_share_information(SOURCE source)
{
    memcpy(&(source->streamBuffer.ShareBufferInfo), source->param.n9ble.share_info_base_addr, sizeof(n9_dsp_share_info_t));

    #ifdef AIR_BTA_IC_PREMIUM_G3
    source->streamBuffer.ShareBufferInfo.start_addr |= 0x60000000;
    #else
    source->streamBuffer.ShareBufferInfo.start_addr = hal_memview_cm4_to_dsp0(source->streamBuffer.ShareBufferInfo.start_addr);
    #endif

    /* Refer to the hal_audio_dsp_controller.c for the limitaion of legnth */
    source->streamBuffer.ShareBufferInfo.length = ALIGN_4(source->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE) * source->param.n9ble.process_number * N9Ble_calculate_avm_frame_num(source->param.n9ble.share_info_base_addr->length, source->param.n9ble.frame_length);
}

ATTR_TEXT_IN_IRAM static VOID N9BleTx_update_from_share_information(SINK sink)
{
    memcpy(&(sink->streamBuffer.ShareBufferInfo), sink->param.n9ble.share_info_base_addr, sizeof(n9_dsp_share_info_t));

    #ifdef AIR_BTA_IC_PREMIUM_G3
    sink->streamBuffer.ShareBufferInfo.start_addr |= 0x60000000;
    #else
    sink->streamBuffer.ShareBufferInfo.start_addr = hal_memview_cm4_to_dsp0(sink->streamBuffer.ShareBufferInfo.start_addr);
    #endif

    /* Refer to the hal_audio_dsp_controller.c for the limitaion of legnth */
    sink->streamBuffer.ShareBufferInfo.length = ALIGN_4(sink->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE) * N9Ble_calculate_avm_frame_num(sink->param.n9ble.share_info_base_addr->length, sink->param.n9ble.frame_length);
}

ATTR_TEXT_IN_IRAM_LEVEL_2 VOID N9Ble_update_readoffset_share_information(SOURCE source, U32 ReadOffset)
{
    source->param.n9ble.share_info_base_addr->read_offset = ReadOffset;
    source->param.n9ble.share_info_base_addr->bBufferIsFull = FALSE;
}

ATTR_TEXT_IN_IRAM_LEVEL_2 VOID N9Ble_update_writeoffset_share_information(SINK sink, U32 WriteOffset)
{
    sink->param.n9ble.share_info_base_addr->write_offset = WriteOffset;
    if (WriteOffset == sink->param.n9ble.share_info_base_addr->read_offset) {
        sink->param.n9ble.share_info_base_addr->bBufferIsFull = TRUE;
    }
}

ATTR_TEXT_IN_IRAM_LEVEL_2 static VOID N9Ble_update_timestamp_share_information(U32 *timestamp_ptr, U32 timestamp)
{
    *timestamp_ptr = timestamp;
}

static VOID N9Ble_Reset_Sourceoffset_share_information(SOURCE source)
{
    source->param.n9ble.share_info_base_addr->write_offset = 0;
    source->param.n9ble.share_info_base_addr->read_offset = 0;
    source->param.n9ble.share_info_base_addr->length = ALIGN_4(source->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE) * source->param.n9ble.process_number * N9Ble_calculate_avm_frame_num(source->param.n9ble.share_info_base_addr->length, source->param.n9ble.frame_length);
    source->param.n9ble.share_info_base_addr->bBufferIsFull = FALSE;
}

static VOID N9Ble_Reset_Sinkoffset_share_information(SINK sink)
{
    sink->param.n9ble.share_info_base_addr->write_offset = 0;
    sink->param.n9ble.share_info_base_addr->read_offset = 0;
    sink->param.n9ble.share_info_base_addr->length = ALIGN_4(sink->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE) * N9Ble_calculate_avm_frame_num(sink->param.n9ble.share_info_base_addr->length, sink->param.n9ble.frame_length);
    sink->param.n9ble.share_info_base_addr->bBufferIsFull = FALSE;
}

static VOID N9Ble_SinkUpdateLocalWriteOffset(SINK sink, U8 num)
{
    sink->streamBuffer.ShareBufferInfo.write_offset += ALIGN_4(sink->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE) * num;
    sink->streamBuffer.ShareBufferInfo.write_offset %= sink->streamBuffer.ShareBufferInfo.length;
}

VOID N9Ble_SourceUpdateLocalReadOffset(SOURCE source, U8 num)
{
    source->streamBuffer.ShareBufferInfo.read_offset += ALIGN_4(source->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE) * num;
    source->streamBuffer.ShareBufferInfo.read_offset %= source->streamBuffer.ShareBufferInfo.length;
}

static VOID N9Ble_Rx_Buffer_Init(SOURCE source)
{
    N9BleRx_update_from_share_information(source);
    N9Ble_Reset_Sourceoffset_share_information(source);
}

static VOID N9Ble_Tx_Buffer_Init(SINK sink)
{
    N9BleTx_update_from_share_information(sink);
    N9Ble_Reset_Sinkoffset_share_information(sink);
}

static VOID N9Ble_Default_setting_init(SOURCE source, SINK sink)
{

    if (source != NULL) {
        //source->param.n9ble.share_info_base_addr->length        = ((28+156)*6);
        N9BLE_setting.N9Ble_source.Buffer_Frame_Num        = N9Ble_calculate_avm_frame_num(source->param.n9ble.share_info_base_addr->length, source->param.n9ble.frame_length);
        N9BLE_setting.N9Ble_source.Process_Frame_Num       = source->param.n9ble.process_number;
        N9BLE_setting.N9Ble_source.Frame_Size              = ALIGN_4(BLE_AVM_FRAME_HEADER_SIZE + source->param.n9ble.frame_length);
        DSP_MW_LOG_I("[BLE] source avm length %d source Frame_Size: %d  Buffer_Frame_Num: %d", 3, source->param.n9ble.share_info_base_addr->length, N9BLE_setting.N9Ble_source.Frame_Size, N9BLE_setting.N9Ble_source.Buffer_Frame_Num);
    }

    if (sink != NULL) {
        //sink->param.n9ble.share_info_base_addr->length        = ((28+156)*6);
        N9BLE_setting.N9Ble_sink.Buffer_Frame_Num        = N9Ble_calculate_avm_frame_num(sink->param.n9ble.share_info_base_addr->length, sink->param.n9ble.frame_length);
        N9BLE_setting.N9Ble_sink.Process_Frame_Num         = sink->param.n9ble.process_number;
        N9BLE_setting.N9Ble_sink.Frame_Size                = ALIGN_4(BLE_AVM_FRAME_HEADER_SIZE + sink->param.n9ble.frame_length);
        //N9BLE_setting.N9Ble_sink.N9_Ro_abnormal_cnt        = 0;
        DSP_MW_LOG_I("[BLE] sink avm length %d sink Frame_Size: %d  Buffer_Frame_Num: %d", 3, sink->param.n9ble.share_info_base_addr->length, N9BLE_setting.N9Ble_sink.Frame_Size, N9BLE_setting.N9Ble_sink.Buffer_Frame_Num);
    }
}

#if ((defined(AIR_UL_FIX_SAMPLING_RATE_48K)|| defined(AIR_BLE_FIXED_RATIO_SRC_ENABLE)) && defined(AIR_FIXED_RATIO_SRC))
#include "src_fixed_ratio_interface.h"

static uint32_t internal_fs_converter(stream_samplerate_t fs)
{
    switch (fs) {
        case FS_RATE_44_1K:
            return 44100;

        case FS_RATE_8K:
        case FS_RATE_16K:
        case FS_RATE_24K:
        case FS_RATE_32K:
        case FS_RATE_48K:
        case FS_RATE_96K:
            return fs * 1000;

        default:
            DSP_MW_LOG_E("[BLE] sample rate is not supported!", 0);
            AUDIO_ASSERT(FALSE);
            return fs;
    }
}
#endif
#if (defined(AIR_BLE_FIXED_RATIO_SRC_ENABLE) && defined(AIR_FIXED_RATIO_SRC))
static src_fixed_ratio_port_t *g_n9ble_dl_swb_fixed_ratio_port[3];
static src_fixed_ratio_port_t *g_n9ble_ul_swb_fixed_ratio_port[3];

static const N9ble_Swsrc_Config_t N9Ble_Swsrc_maping_table[] = {
    /*fs_in, fs_out, fs_tmp1, fs_tmp2, swb_cnt*/
    { 8, 8, 0, 0, 0},
    { 8, 16, 0, 0, 1},
    { 8, 24, 0, 0, 1},
    { 8, 32, 16, 0, 2},
    { 8, 48, 16, 0, 2},
    { 8, 96, 16, 32, 3},
    {16, 16, 0, 0, 0},
    {16, 24, 48, 0, 2},
    {16, 32, 0, 0, 1},
    {16, 48, 0, 0, 1},
    {16, 96, 32, 0, 2},
    {24, 24, 0, 0, 0},
    {24, 32, 48, 96, 3},
    {24, 48, 0, 0, 1},
    {24, 96, 48, 0, 2},
    {32, 32, 0, 0, 0},
    {32, 48, 96, 0, 2},
    {32, 96, 0, 0, 1},
    {48, 48, 0, 0, 0},
    {48, 96, 0, 0, 1},
    {96, 96, 0, 0, 0},
};

void N9Ble_DL_SWB_Sample_Rate_Init(void)
{
    uint32_t channel_number;
    DSP_STREAMING_PARA_PTR dl_stream;
    src_fixed_ratio_config_t *smp_config;
    SOURCE source = Source_blks[SOURCE_TYPE_N9BLE];

    dl_stream = DSP_Streaming_Get(source, source->transform->sink);
    channel_number = stream_function_get_channel_number(&(dl_stream->callback.EntryPara));
    stream_samplerate_t fs_in = dl_stream->callback.EntryPara.in_sampling_rate;
    //stream_samplerate_t fs_out = dl_stream->sink->param.audio.src_rate / 1000; //dl_stream->callback.EntryPara.codec_out_sampling_rate;
    stream_samplerate_t fs_out = 48;
    if(source->param.n9ble.context_type == BLE_CONTEXT_CONVERSATIONAL){
#ifdef AIR_BT_BLE_SWB_ENABLE
        fs_out = 32;
#else
        fs_out = 16;
#endif
    }
    stream_samplerate_t fs_temp = 0, fs_temp2 = 0;
    uint8_t swb_cnt = 0;
    /*fs_in = FS_RATE_32K;
    fs_temp = FS_RATE_16K;//fs_out;
    fs_temp2 = FS_RATE_48K;//fs_out;
    fs_out = FS_RATE_16K;
    swb_cnt = 1;*/

    uint32_t i;
    for (i = 0; i < ARRAY_SIZE(N9Ble_Swsrc_maping_table); i++) {
        if (fs_in <= fs_out) {
            if ((fs_in == N9Ble_Swsrc_maping_table[i].fs_in) && (fs_out == N9Ble_Swsrc_maping_table[i].fs_out)) {
                fs_temp = N9Ble_Swsrc_maping_table[i].fs_tmp1;
                fs_temp2 = N9Ble_Swsrc_maping_table[i].fs_tmp2;
                swb_cnt = N9Ble_Swsrc_maping_table[i].swb_cnt;
                break;
            }
        } else {
            if ((fs_out == N9Ble_Swsrc_maping_table[i].fs_in) && (fs_in == N9Ble_Swsrc_maping_table[i].fs_out)) {
                fs_temp = N9Ble_Swsrc_maping_table[i].fs_tmp2;
                fs_temp2 = N9Ble_Swsrc_maping_table[i].fs_tmp1;
                swb_cnt = N9Ble_Swsrc_maping_table[i].swb_cnt;
                break;
            }
        }
    }

    if ((!fs_temp) && (!fs_temp2)) { /*swb_cnt=1*/
        fs_temp = fs_out;
        fs_temp2 = fs_out;
    }
    if ((!fs_temp) || (!fs_temp2)) { /*swb_cnt<3*/
        if (!fs_temp) {
            fs_temp = fs_temp2;
            fs_temp2 = fs_out;
        } else {
            fs_temp2 = fs_out;
        }
    }
    DSP_MW_LOG_I("[BLE] N9Ble_DL_SWB_Sample_Rate_Init %d %d %d %d %d", 5, fs_in, fs_temp, fs_temp2, fs_out, swb_cnt);

    smp_config = (src_fixed_ratio_config_t *)pvPortMalloc(sizeof(src_fixed_ratio_config_t));
    configASSERT(smp_config);

    smp_config->cvt_num = swb_cnt;
    smp_config->channel_number = channel_number;
    smp_config->resolution = dl_stream->callback.EntryPara.resolution.feature_res;
    smp_config->multi_cvt_mode = SRC_FIXED_RATIO_PORT_MUTI_CVT_MODE_CONSECUTIVE;

    smp_config->in_sampling_rate = internal_fs_converter(fs_in);
    smp_config->out_sampling_rate = internal_fs_converter(fs_temp);
    g_n9ble_dl_swb_fixed_ratio_port[0] = stream_function_src_fixed_ratio_get_port(source);
    stream_function_src_fixed_ratio_init(g_n9ble_dl_swb_fixed_ratio_port[0], smp_config);

    if (swb_cnt > 1) {
        smp_config->in_sampling_rate = internal_fs_converter(fs_temp);
        smp_config->out_sampling_rate = internal_fs_converter(fs_temp2);
        g_n9ble_dl_swb_fixed_ratio_port[1] = stream_function_src_fixed_ratio_get_2nd_port(source);
        stream_function_src_fixed_ratio_init(g_n9ble_dl_swb_fixed_ratio_port[1], smp_config);
    }

    if (swb_cnt > 2) {
        smp_config->in_sampling_rate = internal_fs_converter(fs_temp2);
        smp_config->out_sampling_rate = internal_fs_converter(fs_out);
        g_n9ble_dl_swb_fixed_ratio_port[2] = stream_function_src_fixed_ratio_get_3rd_port(source);
        stream_function_src_fixed_ratio_init(g_n9ble_dl_swb_fixed_ratio_port[2], smp_config);
    }

    DSP_MW_LOG_I("[BLE] N9Ble_DL_SWB_Sample_Rate_Init: channel_number %d, fs_in %d, fs_temp %d, fs_temp2 %d, fs_out %d", 5,
                 smp_config->channel_number, fs_in, fs_temp, fs_temp2, fs_out);

    if(smp_config) {
        vPortFree(smp_config);
    }
}

void N9Ble_DL_SWB_Sample_Rate_Deinit(void)
{
    uint32_t i;

    DSP_MW_LOG_I("[BLE]N9Ble_DL_SWB_Sample_Rate_Deinit", 0);

    for (i = 0 ; i < ARRAY_SIZE(g_n9ble_dl_swb_fixed_ratio_port) ; ++i) {
        if (g_n9ble_dl_swb_fixed_ratio_port[i]) {
            stream_function_src_fixed_ratio_deinit(g_n9ble_dl_swb_fixed_ratio_port[i]);
            g_n9ble_dl_swb_fixed_ratio_port[i] = NULL;
        }
    }
}

void N9Ble_UL_SWB_Sample_Rate_Init(void)
{
    uint32_t channel_number;
    DSP_STREAMING_PARA_PTR ul_stream;
    src_fixed_ratio_config_t *smp_config;
    SINK sink = Sink_blks[SINK_TYPE_N9BLE];

    ul_stream = DSP_Streaming_Get(sink->transform->source, sink);
    channel_number = stream_function_get_channel_number(&(ul_stream->callback.EntryPara));
    stream_samplerate_t fs_in = ul_stream->callback.EntryPara.in_sampling_rate;
    stream_samplerate_t fs_out = ul_stream->callback.EntryPara.codec_out_sampling_rate;
    stream_samplerate_t fs_temp = 0, fs_temp2 = 0;
    uint8_t swb_cnt = 0;
    /*fs_in = FS_RATE_16K;
    fs_temp = FS_RATE_32K;//fs_out;
    fs_temp2 = FS_RATE_96K;//fs_out;
    fs_out = FS_RATE_32K;
    swb_cnt = 1;*/

    uint32_t i;
    for (i = 0; i < ARRAY_SIZE(N9Ble_Swsrc_maping_table); i++) {
        if (fs_in <= fs_out) {
            if ((fs_in == N9Ble_Swsrc_maping_table[i].fs_in) && (fs_out == N9Ble_Swsrc_maping_table[i].fs_out)) {
                fs_temp = N9Ble_Swsrc_maping_table[i].fs_tmp1;
                fs_temp2 = N9Ble_Swsrc_maping_table[i].fs_tmp2;
                swb_cnt = N9Ble_Swsrc_maping_table[i].swb_cnt;
                break;
            }
        } else {
            if ((fs_out == N9Ble_Swsrc_maping_table[i].fs_in) && (fs_in == N9Ble_Swsrc_maping_table[i].fs_out)) {
                fs_temp = N9Ble_Swsrc_maping_table[i].fs_tmp2;
                fs_temp2 = N9Ble_Swsrc_maping_table[i].fs_tmp1;
                swb_cnt = N9Ble_Swsrc_maping_table[i].swb_cnt;
                break;
            }
        }
    }

    if ((!fs_temp) && (!fs_temp2)) {
        fs_temp = fs_out;
        fs_temp2 = fs_out;
    }
    if ((!fs_temp) || (!fs_temp2)) {
        if (!fs_temp) {
            fs_temp = fs_temp2;
            fs_temp2 = fs_out;
        } else {
            fs_temp2 = fs_out;
        }
    }

    DSP_MW_LOG_I("[BLE] N9Ble_UL_SWB_Sample_Rate_Init %d %d %d %d %d", 5, fs_in, fs_temp, fs_temp2, fs_out, swb_cnt);


    smp_config = pvPortMalloc(sizeof(src_fixed_ratio_config_t));
    configASSERT(smp_config);

    smp_config->cvt_num = swb_cnt;
    smp_config->channel_number = channel_number;
    smp_config->resolution = RESOLUTION_16BIT; // ul_stream->callback.EntryPara.resolution.feature_res;
    smp_config->multi_cvt_mode = SRC_FIXED_RATIO_PORT_MUTI_CVT_MODE_CONSECUTIVE;

    smp_config->in_sampling_rate = internal_fs_converter(fs_in);
    smp_config->out_sampling_rate = internal_fs_converter(fs_temp);
    g_n9ble_ul_swb_fixed_ratio_port[0] = stream_function_src_fixed_ratio_get_port(sink);
    stream_function_src_fixed_ratio_init(g_n9ble_ul_swb_fixed_ratio_port[0], smp_config);

    if (swb_cnt > 1) {
        smp_config->in_sampling_rate = internal_fs_converter(fs_temp);
        smp_config->out_sampling_rate = internal_fs_converter(fs_temp2);
        g_n9ble_ul_swb_fixed_ratio_port[1] = stream_function_src_fixed_ratio_get_2nd_port(sink);
        stream_function_src_fixed_ratio_init(g_n9ble_ul_swb_fixed_ratio_port[1], smp_config);
    }

    if (swb_cnt > 2) {
        smp_config->in_sampling_rate = internal_fs_converter(fs_temp2);
        smp_config->out_sampling_rate = internal_fs_converter(fs_out);
        g_n9ble_ul_swb_fixed_ratio_port[2] = stream_function_src_fixed_ratio_get_3rd_port(sink);
        stream_function_src_fixed_ratio_init(g_n9ble_ul_swb_fixed_ratio_port[2], smp_config);
    }

    DSP_MW_LOG_I("[BLE] N9Ble_UL_SWB_Sample_Rate_Init: channel_number %d, fs_in %d, fs_temp %d, fs_temp2 %d, fs_out %d", 5,
                 smp_config->channel_number, fs_in, fs_temp, fs_temp2, fs_out);

    if(smp_config) {
        vPortFree(smp_config);
    }
}

void N9Ble_UL_SWB_Sample_Rate_Deinit(void)
{
    uint32_t i;

    DSP_MW_LOG_I("[BLE]N9Ble_UL_SWB_Sample_Rate_Deinit", 0);

    for (i = 0 ; i < ARRAY_SIZE(g_n9ble_ul_swb_fixed_ratio_port) ; ++i) {
        if (g_n9ble_ul_swb_fixed_ratio_port[i]) {
            stream_function_src_fixed_ratio_deinit(g_n9ble_ul_swb_fixed_ratio_port[i]);
            g_n9ble_ul_swb_fixed_ratio_port[i] = NULL;
        }
    }
}

#endif
#if (defined(AIR_UL_FIX_SAMPLING_RATE_48K) && defined(AIR_FIXED_RATIO_SRC))
static src_fixed_ratio_port_t *g_n9ble_ul_src_fixed_ratio_port;

void N9Ble_UL_Fix_Sample_Rate_Init(void)
{
    uint32_t channel_number;
    DSP_STREAMING_PARA_PTR ul_stream;
    src_fixed_ratio_config_t smp_config;
    volatile SINK sink = Sink_blks[SINK_TYPE_N9BLE];

    ul_stream = DSP_Streaming_Get(sink->transform->source, sink);
    channel_number = stream_function_get_channel_number(&(ul_stream->callback.EntryPara));

    smp_config.channel_number = channel_number;
    smp_config.in_sampling_rate = internal_fs_converter((stream_samplerate_t)(ul_stream->callback.EntryPara.in_sampling_rate));
    smp_config.out_sampling_rate = 16000;//internal_fs_converter((stream_samplerate_t)(ul_stream->callback.EntryPara.codec_out_sampling_rate));
    smp_config.resolution = ul_stream->callback.EntryPara.resolution.feature_res;
    smp_config.multi_cvt_mode = SRC_FIXED_RATIO_PORT_MUTI_CVT_MODE_SINGLE;
    smp_config.cvt_num = 1;
    g_n9ble_ul_src_fixed_ratio_port = stream_function_src_fixed_ratio_get_port(sink);

    DSP_MW_LOG_I("[BLE] src_fixed_ratio_init: channel_number %d, in_sampling_rate %d, out_sampling_rate %d, resolution %d", 4,
                 smp_config.channel_number, smp_config.in_sampling_rate, smp_config.out_sampling_rate, smp_config.resolution);
    stream_function_src_fixed_ratio_init(g_n9ble_ul_src_fixed_ratio_port, &smp_config);
}

void N9Ble_UL_Fix_Sample_Rate_Deinit(void)
{
    if (g_n9ble_ul_src_fixed_ratio_port) {
        stream_function_src_fixed_ratio_deinit(g_n9ble_ul_src_fixed_ratio_port);
        g_n9ble_ul_src_fixed_ratio_port = NULL;
    }
}
#endif

#if defined(AIR_MUTE_MIC_DETECTION_ENABLE)
#include "volume_estimator_interface.h"
#include "stream_nvkey_struct.h"
#include "preloader_pisplit.h"
#include "audio_nvdm_common.h"
void *p_ble_ul_vol_estimator_nvkey_buf = NULL;
volume_estimator_port_t *p_ble_ul_meter_port;

void N9Ble_UL_Volume_Estimator_Init(SINK sink){
    /* init volume estimator port */
    p_ble_ul_vol_estimator_nvkey_buf = preloader_pisplit_malloc_memory(PRELOADER_D_HIGH_PERFORMANCE, sizeof(audio_spectrum_meter_nvkey_t));
    if (p_ble_ul_vol_estimator_nvkey_buf == NULL) {
        AUDIO_ASSERT(0);
    }
    if (nvkey_read_full_key(NVKEY_DSP_PARA_SILENCE_DETECTION2, p_ble_ul_vol_estimator_nvkey_buf, sizeof(audio_spectrum_meter_nvkey_t)) != NVDM_STATUS_NAT_OK) {
        AUDIO_ASSERT(0);
    }
    volume_estimator_config_t config;
    p_ble_ul_meter_port = volume_estimator_get_port(sink);
    if (p_ble_ul_meter_port == NULL) {
        AUDIO_ASSERT(0 && "[BLE] Audio Spectrum memter port is null.");
    }
    config.resolution = RESOLUTION_16BIT;
    config.frame_size = sink->transform->source->param.audio.rate/1000 * 15 * ((config.resolution == RESOLUTION_16BIT)? 2:4);
    //config.frame_size = sink->transform->source->param.audio.rate/1000 * sink->param.n9ble.frame_interval/1000 * ((config.resolution == RESOLUTION_16BIT)? 2:4);
    config.channel_num = 1;
    config.mode = VOLUME_ESTIMATOR_CHAT_INSTANT_MODE;
    config.sample_rate = sink->transform->source->param.audio.rate;
    config.nvkey_para = (void *)&(((audio_spectrum_meter_nvkey_t *)p_ble_ul_vol_estimator_nvkey_buf)->chat_vol_nvkey);
    config.internal_buffer = NULL;
    config.internal_buffer_size = 0;
    volume_estimator_init(p_ble_ul_meter_port, &config);
    DSP_MW_LOG_I("[BLE] volume estimator 0x%x info, %d, %d, %d,internal_buffer 0x%x, 0x%x\r\n", 6,
                p_ble_ul_meter_port,
                config.frame_size,
                config.channel_num,
                config.sample_rate,
                config.internal_buffer,
                config.internal_buffer_size);
}

void N9Ble_UL_Volume_Estimator_Deinit(void){
    volume_estimator_deinit(p_ble_ul_meter_port);
    if (p_ble_ul_vol_estimator_nvkey_buf) {
        preloader_pisplit_free_memory(p_ble_ul_vol_estimator_nvkey_buf);
        p_ble_ul_vol_estimator_nvkey_buf = NULL;
    }
    DSP_MW_LOG_I("[BLE] volume estimator deinit",0);
}
#endif

/**
 * SinkSlackN9Ble
 *
 * Function to query the remain buffer free size of BLE sink.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
ATTR_TEXT_IN_IRAM_LEVEL_2 static U32 SinkSlackN9Ble(SINK sink)
{
//    DSP_MW_LOG_I("[BLE] SinkSlackN9Ble    sink frame_length: %d  process_number: %d", 2, sink->param.n9ble.frame_length, sink->param.n9ble.process_number);
    if(ULL_NrOffloadFlag){
        return sink->param.n9ble.frame_length;
    }else{
        return sink->param.n9ble.frame_length * 3; /* always guarantee buffer for three frames*/
    }
}


/**
 * SinkClaimN9Ble
 *
 * Function to request the framework to write data into BLE sink.
 * Note: this function should NOT called by framework.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
static U32 SinkClaimN9Ble(SINK sink, U32 extra)
{
    UNUSED(sink);
    UNUSED(extra);

    DSP_MW_LOG_E("[BLE][sink] SinkClaimN9Ble called!!!", 0);
    AUDIO_ASSERT(0);

    return SINK_INVALID_CLAIM;
}

/**
 * SinkMapN9Ble
 *
 * Function to read the decoded data in BLE sink.
 * Note: this function should NOT called by framework.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
static U8 *SinkMapN9Ble(SINK sink)
{
    UNUSED(sink);

    DSP_MW_LOG_E("[BLE][sink] SinkMapN9Ble called!!!", 0);
    AUDIO_ASSERT(0);

    return 0;
}

/**
 * SinkFlushN9Ble
 *
 * Function to update the WPTR for BLE sink.
 *
 * param :amount - The amount of data written into sink.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
*/
ATTR_TEXT_IN_IRAM_LEVEL_2 static BOOL SinkFlushN9Ble(SINK sink, U32 amount)
{
    uint32_t ProcessFrameLen;
    DSP_STREAMING_PARA_PTR stream = NULL;
    stream = DSP_Streaming_Get(sink->transform->source, sink);
    stream->callback.EntryPara.out_channel_num = sink->param.n9ble.out_channel;

    if (ULL_NrOffloadFlag == true) {
        ProcessFrameLen = (g_ble_ul_abr_length - 1) * sink->param.n9ble.process_number;
    } else {
        ProcessFrameLen = g_ble_ul_abr_length * sink->param.n9ble.process_number;
    }

    if (amount % ProcessFrameLen) {
        DSP_MW_LOG_E("[BLE][sink] flush size mismatch %d, %d!!!", 2, amount, ProcessFrameLen);
        AUDIO_ASSERT(0);
        return FALSE;
    }

    uint32_t flush_num = sink->param.n9ble.process_number;
    sink->param.n9ble.predict_timestamp += flush_num * ((sink->param.n9ble.frame_interval << 1) / LE_TIME_BT_CLOCK);
    sink->param.n9ble.predict_timestamp &= 0xFFFFFFF;
    if (flush_num) {
        N9BleTx_update_from_share_information(sink);
        N9Ble_SinkUpdateLocalWriteOffset(sink, flush_num);
        N9Ble_update_writeoffset_share_information(sink, sink->streamBuffer.ShareBufferInfo.write_offset);

#ifdef AIR_WIRELESS_MIC_TX_ENABLE
#ifdef AIR_BT_LE_LC3PLUS_ENABLE
#ifdef AIR_AUDIO_DUMP_ENABLE
        /* dump channel 1 LC3+ codec in data */
        uint8_t *codec_in_data_address;
        uint32_t codec_in_data_frame_size;
        if (sink->param.n9ble.codec_type == BT_BLE_CODEC_LC3PLUS)
        {
            stream_codec_encoder_lc3plus_get_data_info(LC3PLUS_ENC_PORT_0, 1, &codec_in_data_address, &codec_in_data_frame_size);
            LOG_AUDIO_DUMP((uint8_t *)codec_in_data_address, codec_in_data_frame_size*2, AUDIO_SOURCE_IN_L);
        }
#endif
#endif
#endif
#ifdef AIR_BT_LE_LC3PLUS_ENABLE
        if ((sink->param.n9ble.context_type == BLE_CONTENT_TYPE_ULL_BLE) && (sink->param.n9ble.codec_type == BT_BLE_CODEC_LC3PLUS) && ((sink->streamBuffer.ShareBufferInfo.asi_cur < sink->param.n9ble.predict_timestamp)&&(sink->streamBuffer.ShareBufferInfo.asi_base & 0x80000000)))
        {
            DSP_MW_LOG_I("[BLE][sink] flush change frame size %d, %d!!!", 2, amount, (sink->streamBuffer.ShareBufferInfo.asi_base & 0xFFFF) * 8 * 1000 / (sink->param.n9ble.frame_interval));
            stream_codec_encoder_lc3plus_set_bitrate(LC3PLUS_ENC_PORT_0, (sink->streamBuffer.ShareBufferInfo.asi_base & 0xFFFF) * 8 * 1000 / (sink->param.n9ble.frame_interval) * 1000 );
            sink->param.n9ble.share_info_base_addr->asi_base &= 0xFFFF;
            g_ble_ul_abr_length = (U16)sink->param.n9ble.share_info_base_addr->asi_base;
            DSP_MW_LOG_I("[BLE][sink] flush change frame size done %d!!!",1, g_ble_ul_abr_length);

        }
#endif
    }
    /*
        DSP_MW_LOG_I("[BLE][sink] SinkFlushN9Ble flush_num: %d  sink local offset:%X", 2, flush_num, sink->streamBuffer.ShareBufferInfo.WriteOffset);
    */
#ifdef AIR_BLE_FEATURE_MODE_ENABLE
    if (HAL_NVIC_QUERY_EXCEPTION_NUMBER == HAL_NVIC_NOT_EXCEPTION) {
        if (g_ble_dl_ul_process_active == false) {
            audio_nvdm_update_status(AUDIO_NVDM_USER_BLE, AUDIO_NVDM_STATUS_POST_CHANGE);
            g_ble_dl_ul_process_active = true;
        }
        if ((sink->param.n9ble.ul_reinit == true) && (Source_blks[SOURCE_TYPE_N9BLE] != NULL) && (Source_blks[SOURCE_TYPE_N9BLE]->param.n9ble.dl_reinit == true)) {
            Source_blks[SOURCE_TYPE_N9BLE]->param.n9ble.dl_reinit = false;
            sink->param.n9ble.ul_reinit = false;
            audio_nvdm_update_status(AUDIO_NVDM_USER_BLE, AUDIO_NVDM_STATUS_POST_CHANGE);
        }
    }
#endif
    return TRUE;
}

#ifdef AIR_ULL_BLE_HEADSET_ENABLE
extern const uint32_t crc32_tab[];

ATTR_TEXT_IN_IRAM_LEVEL_1 static uint32_t CRC32_Generate(uint8_t *ptr, uint32_t length, uint32_t crc_init)
{
    const uint8_t *p;

    p = ptr;
    crc_init = crc_init ^ ~0U;

    while (length--) {
        crc_init = crc32_tab[(crc_init ^ *p++) & 0xFF] ^ (crc_init >> 8);
    }

    return crc_init ^ ~0U;
}
#endif


/**
 * SinkBufferWriteN9Ble
 *
 * Function to write the framwork data to BLE sink.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
ATTR_TEXT_IN_IRAM_LEVEL_2 static BOOL SinkBufferWriteN9Ble(SINK sink, U8 *src_addr, U32 length)
{
    U16 i;
    U8 *write_ptr;
    uint32_t ProcessFrameLen;
    LE_AUDIO_HEADER *buf_header;
    U32 timestamp = sink->param.n9ble.predict_timestamp;
    if (ULL_NrOffloadFlag == true) {
        ProcessFrameLen = (g_ble_ul_abr_length - 1) * sink->param.n9ble.process_number;
    } else {
        ProcessFrameLen = g_ble_ul_abr_length * sink->param.n9ble.process_number;
    }
    if (length % ProcessFrameLen) {
        DSP_MW_LOG_E("[BLE][sink] write size mismatch %d, %d!!!", 2, length, ProcessFrameLen);
        AUDIO_ASSERT(0);
        return FALSE;
    }

    N9BleTx_update_from_share_information(sink);

    uint32_t write_num = sink->param.n9ble.process_number;

    /*
        DSP_MW_LOG_I("SinkBufferWriteN9Ble src_addr:%X length:%d write_num:%d",3, src_addr, length, write_num);
    */

    for (i = 0 ; i < write_num; i++) {
        U8 *src_ptr = src_addr + (U32)(i * g_ble_ul_abr_length);
        write_ptr = (U8 *)(sink->streamBuffer.ShareBufferInfo.start_addr + sink->streamBuffer.ShareBufferInfo.write_offset);
        if(ULL_NrOffloadFlag){
            uint8_t PostEC_Gain = 0;
            memcpy(write_ptr + BLE_AVM_FRAME_HEADER_SIZE, src_ptr, g_ble_ul_abr_length-1);
#ifdef AIR_ECNR_PREV_PART_ENABLE
#ifndef AIR_ECNR_SEPARATE_MODE_ENABLE
            PostEC_Gain = voice_ecnr_ec_get_postec_gain();
#endif
#else
            PostEC_Gain = 0;
#endif
            memcpy(write_ptr + BLE_AVM_FRAME_HEADER_SIZE + g_ble_ul_abr_length-1, &PostEC_Gain, 1);
            DSP_MW_LOG_I("[DSP][VOICE_NR] send PostEC_Gain %d, sink->param.n9ble.frame_length %d", 2, PostEC_Gain, g_ble_ul_abr_length);
        }else{
            memcpy(write_ptr + BLE_AVM_FRAME_HEADER_SIZE, src_ptr, g_ble_ul_abr_length);
        }
        buf_header = (LE_AUDIO_HEADER *)write_ptr;
        buf_header->DataOffset = BLE_AVM_FRAME_HEADER_SIZE;
        buf_header->Pdu_LEN_Without_MIC = g_ble_ul_abr_length;
        buf_header->TimeStamp = timestamp;
        #ifdef AIR_ULL_BLE_HEADSET_ENABLE
        buf_header->crc32_value = CRC32_Generate((uint8_t *)src_ptr, g_ble_ul_abr_length, sink->param.n9ble.crc_init);
        #endif
        timestamp += ((sink->param.n9ble.frame_interval << 1) / LE_TIME_BT_CLOCK);
        //DSP_MW_LOG_I("[BLE][sink]offset %d, ts %d!!!", 2, sink->streamBuffer.ShareBufferInfo.WriteOffset, buf_header->TimeStamp);
        N9Ble_SinkUpdateLocalWriteOffset(sink, 1);
    }
    /*
        DSP_MW_LOG_I("[BLE][sink] SinkBufferWriteN9Ble sink local offset:%X", 1, sink->streamBuffer.ShareBufferInfo.WriteOffset);
    */
    return TRUE;
}

/**
 * SinkCloseN9Ble
 *
 * Function to shutdown BLE sink.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
static BOOL SinkCloseN9Ble(SINK sink)
{
    sink->param.n9ble.frame_length = 0;
    sink->param.n9ble.process_number = 0;
    sink->param.n9ble.share_info_base_addr = NULL;
#if defined(AIR_BLE_FIXED_RATIO_SRC_ENABLE) && defined(AIR_FIXED_RATIO_SRC)
    N9Ble_UL_SWB_Sample_Rate_Deinit();
#endif

#if defined(AIR_UL_FIX_SAMPLING_RATE_48K) && defined(AIR_FIXED_RATIO_SRC)
    N9Ble_UL_Fix_Sample_Rate_Deinit();
#endif

#ifdef AIR_MUTE_MIC_DETECTION_ENABLE
if ((sink->param.n9ble.context_type != BLE_CONTENT_TYPE_ULL_BLE) && (sink->param.n9ble.context_type != BLE_CONTENT_TYPE_WIRELESS_MIC)) {
    N9Ble_UL_Volume_Estimator_Deinit();
}
#endif

#ifdef AIR_BT_LE_LC3PLUS_ENABLE
    if(sink->param.n9ble.codec_type == BT_BLE_CODEC_LC3PLUS ) {
        DSP_MW_LOG_I("[BLE][LC3PLUS_ENC] deinit\r\n", 0);
        stream_codec_encoder_lc3plus_deinit(LC3PLUS_ENC_PORT_0,sink);
    }
#endif
#ifdef AIR_CELT_ENC_V2_ENABLE
    if(sink->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR ) {
        DSP_MW_LOG_I("[BLE][CELT] deinit\r\n", 0);
        stream_codec_encoder_celt_v2_deinit(CELT_ENC_PORT_0,sink);
    }
#endif

    return TRUE;
}

/**
 * SinkInitN9Ble
 *
 * Function to initialize BLE sink.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
VOID SinkInitN9Ble(SINK sink)
{
    N9Ble_Default_setting_init(NULL, sink);

    sink->buftype = BUFFER_TYPE_CIRCULAR_BUFFER;
    N9Ble_Tx_Buffer_Init(sink);

    sink->sif.SinkSlack       = SinkSlackN9Ble;
    sink->sif.SinkClaim       = SinkClaimN9Ble;
    sink->sif.SinkMap         = SinkMapN9Ble;
    sink->sif.SinkFlush       = SinkFlushN9Ble;
    sink->sif.SinkClose       = SinkCloseN9Ble;
    sink->sif.SinkWriteBuf    = SinkBufferWriteN9Ble;

    sink->param.n9ble.IsFirstIRQ = TRUE;
#ifdef AIR_BLE_FEATURE_MODE_ENABLE
    sink->param.n9ble.ul_reinit = false;
#endif
}

/**
 * SourceSizeN9Ble
 *
 * Function to report remaining Source buffer avail size.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
ATTR_TEXT_IN_IRAM static U32 SourceSizeN9Ble(SOURCE source)
{
#ifdef MTK_PEQ_ENABLE
    BTCLK bt_clk;
    BTPHASE bt_phase;
#endif
    U32 writeOffset, readOffset, length, ProcessFrameLen, RemainLen;
    LE_AUDIO_HEADER *buf_header;
    U8 *read_ptr;
    N9BleRx_update_from_share_information(source);

    writeOffset = source->streamBuffer.ShareBufferInfo.write_offset;
    readOffset  = source->streamBuffer.ShareBufferInfo.read_offset;
    length      = source->streamBuffer.ShareBufferInfo.length;
    read_ptr = (U8 *)(source->streamBuffer.ShareBufferInfo.start_addr + source->streamBuffer.ShareBufferInfo.read_offset);
    buf_header = (LE_AUDIO_HEADER *)read_ptr;

    ProcessFrameLen = source->param.n9ble.process_number * ALIGN_4(source->param.n9ble.frame_length + BLE_AVM_FRAME_HEADER_SIZE);
    RemainLen = (readOffset > writeOffset) ? (length - readOffset + writeOffset) : (writeOffset - readOffset);
    if (source->streamBuffer.ShareBufferInfo.bBufferIsFull == true) {
        RemainLen = length;
    }

    //if ((source->param.n9ble.write_offset_advance == 0) && (RemainLen < ProcessFrameLen)) {
    //    DSP_MW_LOG_E("[BLE][source] AVM buffer detect underflow!!! RO: %d, WO: %d", 2, readOffset, writeOffset);
    //}

    //if(source->param.n9ble.context_type == BLE_CONTENT_TYPE_ULL_BLE){
    //    g_ble_abr_length = source->param.n9ble.frame_length;
    //}else
    {
        if( N9Ble_check_avm_frame_valid(buf_header, FALSE)
            && (buf_header->Pdu_LEN_Without_MIC != g_ble_abr_length)
        )
        {
            if(buf_header->Pdu_LEN_Without_MIC <= source->param.n9ble.frame_length)
            {
                g_ble_abr_length = buf_header->Pdu_LEN_Without_MIC;
                DSP_MW_LOG_I("[BLE][source] ABR length: %d", 1, g_ble_abr_length);
            }
            else
            {
                DSP_MW_LOG_W("[BLE][source] ABR length: %d > %d, keep %d", 3, buf_header->Pdu_LEN_Without_MIC, source->param.n9ble.frame_length, g_ble_abr_length);
            }
        }
    }
    ProcessFrameLen = (source->param.n9ble.dual_cis_status != DUAL_CIS_DISABLED) ? g_ble_abr_length * source->param.n9ble.process_number * 2 : g_ble_abr_length * source->param.n9ble.process_number;
    ProcessFrameLen += source->param.n9ble.plc_state_len;

#ifdef MTK_PEQ_ENABLE
    MCE_GetBtClk(&bt_clk, &bt_phase, BT_CLK_Offset);
    PEQ_Update_Info(bt_clk, source->param.n9ble.predict_timestamp);
#endif
#ifdef AIR_CELT_DEC_V2_ENABLE
    if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
        ProcessFrameLen = 108;
    }
#endif

    return (source->param.n9ble.dl_afe_skip_time) ? 0 : ProcessFrameLen;

}

/**
 * SourceMapN9Ble
 *
 * Function to  read the received data in BLE source.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
static U8 *SourceMapN9Ble(SOURCE source)
{
    UNUSED(source);
    AUDIO_ASSERT(0);

    return NULL;
}

/**
 * SourceDropN9Ble
 *
 * Function to drop the data in BLE sink.
 *
 * param :amount - The amount of data to drop in sink.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
ATTR_TEXT_IN_IRAM_LEVEL_2 static VOID SourceDropN9Ble(SOURCE source, U32 amount)
{
    U16 i;
    U32 ProcessFrameLen;

    N9BleRx_update_from_share_information(source);

#ifdef AIR_CELT_DEC_V2_ENABLE
    if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
        ProcessFrameLen = 108;
    } else {
#endif
    ProcessFrameLen = (g_ble_abr_length * source->param.n9ble.process_number) << (source->param.n9ble.dual_cis_status != DUAL_CIS_DISABLED);
    ProcessFrameLen += source->param.n9ble.plc_state_len;
#ifdef AIR_CELT_DEC_V2_ENABLE
    }
#endif

    if (amount != ProcessFrameLen) {
        DSP_MW_LOG_E("[BLE][source] SourceDropN9Ble drop size mismatch %d, %d!!!", 2, amount, ProcessFrameLen);
        return;
    } else {
        for (i = 0 ; i < N9BLE_setting.N9Ble_source.Process_Frame_Num; i++) {
            LE_AUDIO_HEADER *buf_header;
            buf_header = (LE_AUDIO_HEADER *)(source->streamBuffer.ShareBufferInfo.start_addr + source->streamBuffer.ShareBufferInfo.read_offset);
            N9Ble_update_timestamp_share_information(&buf_header->TimeStamp, BLE_AVM_INVALID_TIMESTAMP); /* invalid the timestamp */
            if (source->param.n9ble.dual_cis_status != DUAL_CIS_DISABLED) {

                buf_header = (LE_AUDIO_HEADER *)((U32)source->param.n9ble.sub_share_info_base_addr + ((source->streamBuffer.ShareBufferInfo.read_offset + source->param.n9ble.dual_cis_buffer_offset)%source->streamBuffer.ShareBufferInfo.length));
                N9Ble_update_timestamp_share_information(&buf_header->TimeStamp, BLE_AVM_INVALID_TIMESTAMP); /* invalid the timestamp */
            }
            N9Ble_SourceUpdateLocalReadOffset(source, 1);
        }
        //DSP_MW_LOG_I("[BLE] source drop, update ro to:%d",1, source->streamBuffer.ShareBufferInfo.ReadOffset);
        N9Ble_update_readoffset_share_information(source, source->streamBuffer.ShareBufferInfo.read_offset);
    }
    source->param.n9ble.predict_frame_counter++;
    if (source->param.n9ble.predict_frame_counter == source->param.n9ble.frame_per_iso) {
        source->param.n9ble.predict_frame_counter = 0;
        source->param.n9ble.predict_timestamp += ((source->param.n9ble.iso_interval << 1) / LE_TIME_BT_CLOCK);
        source->param.n9ble.predict_timestamp = (source->param.n9ble.predict_timestamp & 0xFFFFFFF);
    }
    source->param.n9ble.write_offset_advance = 0;
    if (source->param.n9ble.seq_miss_cnt > LE_AUDIO_OFFSET_PROTECT) {
        LE_AUDIO_HEADER *buf_header;
        buf_header = (LE_AUDIO_HEADER *)(source->streamBuffer.ShareBufferInfo.start_addr + source->streamBuffer.ShareBufferInfo.read_offset);
        DSP_MW_LOG_E("[BLE][source] drop detect timestamp mismatch trigger offset re-sync,next TS : %d", 1, buf_header->TimeStamp);

        if (buf_header->TimeStamp <= source->param.n9ble.predict_timestamp) {
            N9Ble_SourceUpdateLocalReadOffset(source, (source->param.n9ble.predict_timestamp - buf_header->TimeStamp) / ((source->param.n9ble.frame_interval << 1) / LE_TIME_BT_CLOCK));
            DSP_MW_LOG_E("[BLE][source] offset adjust: %d", 1, (source->param.n9ble.predict_timestamp - buf_header->TimeStamp) / ((source->param.n9ble.frame_interval << 1) / LE_TIME_BT_CLOCK));
            source->param.n9ble.seq_miss_cnt = 0;
        } else if (buf_header->TimeStamp != BLE_AVM_INVALID_TIMESTAMP && (buf_header->_reserved_byte_0Dh & 0x01)) {
            N9Ble_SourceUpdateLocalReadOffset(source, 1);
        }
        N9Ble_update_readoffset_share_information(source, source->streamBuffer.ShareBufferInfo.read_offset);
    }
    source->param.n9ble.seq_num += source->param.n9ble.process_number;
    if (source->param.n9ble.skip_after_drop == TRUE) {
        DSP_MW_LOG_E("[BLE] SOURCE skip after drop", 0);
    }
    U32 mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (source->param.n9ble.skip_after_drop == TRUE) {
        source->param.n9ble.dl_afe_skip_time += 2;
        source->param.n9ble.skip_after_drop = FALSE;
    }
    hal_nvic_restore_interrupt_mask(mask);
}

/**
 * SourceConfigureN9Ble
 *
 * Function to configure BLE source.
 *
 * param :type - The configure type.
 *
 * param :value - The configure value.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
static BOOL SourceConfigureN9Ble(SOURCE source, stream_config_type type, U32 value)
{
    switch (type) {
        case SCO_SOURCE_WO_ADVANCE:
            source->param.n9ble.write_offset_advance = value;
            break;
        default:
            DSP_MW_LOG_E("[BLE][source] SourceConfigureN9Ble call with error type %d, value %d!!!", 2, type, value);
            AUDIO_ASSERT(0);
            return FALSE;
    }

    return TRUE;
}

/**
 * SourceReadBufN9Ble
 *
 * Function to read data from BLE source.
 *
 * param :dst_addr - The destination buffer to write data into.
 *
 * param :length -The leng of data to read.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
ATTR_TEXT_IN_IRAM_LEVEL_2 static BOOL SourceReadBufN9Ble(SOURCE source, U8 *dst_addr, U32 length)
{
    U16 i;
    U8 *read_ptr;
    U8 *write_ptr;
    U32 ProcessFrameLen;
    LE_AUDIO_HEADER *buf_header;

    ProcessFrameLen = (g_ble_abr_length * source->param.n9ble.process_number) << (source->param.n9ble.dual_cis_status != DUAL_CIS_DISABLED);
    ProcessFrameLen += source->param.n9ble.plc_state_len;

#if (defined(AIR_BT_LE_LC3PLUS_ENABLE))
    U32* plc_report_addr = (U32*)dst_addr;
#elif defined(AIR_CELT_DEC_V2_ENABLE)
    TRANSFORM transform =  source->transform;
    DSP_CALLBACK_PTR callback_ptr = NULL;
    U8 *dst_addr2 = NULL;
    if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
        if (transform != NULL && dst_addr == NULL  && source->param.n9ble.dual_cis_status != DUAL_CIS_DISABLED) {
            callback_ptr = DSP_Callback_Get(source, transform->sink);
            dst_addr = callback_ptr->EntryPara.in_ptr[0];
            dst_addr2 = callback_ptr->EntryPara.in_ptr[1];
        }
        ProcessFrameLen = 108;
    }
#endif

    if (ProcessFrameLen != length) {
        DSP_MW_LOG_E("[BLE][source] SourceReadBufN9Ble found size mismatch %d, %d!!!", 2, length, ProcessFrameLen);
        //return FALSE;
    }
    #ifdef AIR_BT_LE_LC3PLUS_ENABLE
    if (source->param.n9ble.plc_state_len != 0)
    {
        *plc_report_addr = LC3PLUS_DEC_FRAME_STATUS_NORMAL;
        dst_addr += source->param.n9ble.plc_state_len;
    }
    #endif

    N9BleRx_update_from_share_information(source);
    //Clock_Skew_Offset_Update_BLE(source);

    for (i = 0; i < source->param.n9ble.process_number; i++) {
        read_ptr = (U8 *)(source->streamBuffer.ShareBufferInfo.start_addr + source->streamBuffer.ShareBufferInfo.read_offset);
        write_ptr = (source->param.n9ble.dual_cis_status == DUAL_CIS_DISABLED) ? dst_addr + i * g_ble_abr_length : dst_addr + (i * 2) * g_ble_abr_length;

        buf_header = (LE_AUDIO_HEADER *)read_ptr;
       //DSP_MW_LOG_I("[BLE][source] Start_addr = 0x%x ,TimeStamp = 0x%08x, PduLen = %d", 3, source->streamBuffer.ShareBufferInfo.start_addr, buf_header->TimeStamp, buf_header->Pdu_LEN_Without_MIC);

#if 0
        DSP_MW_LOG_I("[BLE_DEBUG] BEFORE info_addr = 0x%08x, predict = 0x%08x, TimeStamp = 0x%08x, valid = %d cnt= %d, RO = %d, WO = %d", 7,
            source->param.n9ble.share_info_base_addr,
            source->param.n9ble.predict_timestamp,
            buf_header->TimeStamp,
            buf_header->_reserved_byte_0Dh,
            buf_header->EventCount,
            source->streamBuffer.ShareBufferInfo.read_offset,
            source->param.n9ble.share_info_base_addr->write_offset
        );
#endif

        if (N9Ble_check_avm_frame_valid(buf_header, TRUE)) {
            g_ble_pkt_lost[i][0] = false;
#ifdef AIR_CELT_DEC_V2_ENABLE
            if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
                *((U32*)dst_addr) = CELT_DEC_FRAME_STATUS_NORMAL;
                dst_addr += source->param.n9ble.plc_state_len;
                memcpy(dst_addr, read_ptr + BLE_AVM_FRAME_HEADER_SIZE, g_ble_abr_length/2);
                dst_addr += ALIGN_4(g_ble_abr_length/2);
                *((U32*)dst_addr) = CELT_DEC_FRAME_STATUS_NORMAL;
                dst_addr += source->param.n9ble.plc_state_len;
                memcpy(dst_addr, read_ptr + BLE_AVM_FRAME_HEADER_SIZE + g_ble_abr_length/2, g_ble_abr_length/2);
            } else {
#endif
            memcpy(write_ptr, read_ptr + BLE_AVM_FRAME_HEADER_SIZE, g_ble_abr_length);

#ifdef AIR_CELT_DEC_V2_ENABLE
            }
#endif
            if(!source->param.n9ble.predict_packet_cnt) {
                source->param.n9ble.predict_packet_cnt = buf_header->EventCount;
            }

            if(source->param.n9ble.predict_packet_cnt != buf_header->EventCount) {
                DSP_MW_LOG_W("[BLE][source] Rx packet cnt mismatch %d != %d RO:%d WO:%d", 4
                    , source->param.n9ble.predict_packet_cnt
                    , buf_header->EventCount
                    , source->streamBuffer.ShareBufferInfo.read_offset
                    , source->param.n9ble.share_info_base_addr->write_offset
                );
                source->param.n9ble.predict_packet_cnt = 0;
            }

           if (source->param.n9ble.pkt_lost_cnt) {
                DSP_MW_LOG_W("[BLE][source] Rx packet RECV with SEQ: %d, PTS:%d, TS: %d, PCNT: %d, CNT: %d, VALID: 0x%X, RO: %4d, WO: %4d", 8
                    , source->param.n9ble.seq_num + i
                    , source->param.n9ble.predict_timestamp
                    , buf_header->TimeStamp
                    , source->param.n9ble.predict_packet_cnt
                    , buf_header->EventCount
                    , buf_header->_reserved_byte_0Dh
                    , source->streamBuffer.ShareBufferInfo.read_offset
                    , source->param.n9ble.share_info_base_addr->write_offset
                );
            }
            source->param.n9ble.pkt_lost_cnt = 0;

            if (((abs32((S32)(buf_header->TimeStamp - source->param.n9ble.predict_timestamp)) * 625) >> 1) > source->param.n9ble.iso_interval) {
                DSP_MW_LOG_W("[BLE][source] ts info %d %d index:%d mis_cnt:%d", 4, buf_header->TimeStamp, source->param.n9ble.predict_timestamp, source->streamBuffer.ShareBufferInfo.read_offset, source->param.n9ble.seq_miss_cnt);
                source->param.n9ble.seq_miss_cnt++;
            } else {
                source->param.n9ble.seq_miss_cnt = 0;
            }

#if 0
            if(source->param.n9ble.predict_packet_cnt && source->param.n9ble.share_info_base_addr->write_offset == source->streamBuffer.ShareBufferInfo.read_offset) {
                DSP_MW_LOG_E("[BLE][source] AVM RW access conflict seq: %d, PTS: %d, RO: %d, WO %d", 4
                    , source->param.n9ble.seq_num + i
                    , source->param.n9ble.predict_timestamp
                    , source->streamBuffer.ShareBufferInfo.read_offset
                    , source->param.n9ble.share_info_base_addr->write_offset
                );
            }
#endif
        } else {
            g_ble_pkt_lost[i][0] = true;
#ifdef AIR_CELT_DEC_V2_ENABLE
            if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
                *((U32*)dst_addr) = CELT_DEC_FRAME_STATUS_PLC;
                dst_addr += source->param.n9ble.plc_state_len;
                memset(dst_addr, 0, g_ble_abr_length/2);
                dst_addr += ALIGN_4(g_ble_abr_length/2);
                *((U32*)dst_addr) = CELT_DEC_FRAME_STATUS_PLC;
                dst_addr += source->param.n9ble.plc_state_len;
                memset(dst_addr, 0, g_ble_abr_length/2);
            } else {
#endif
            memset(write_ptr, 0, g_ble_abr_length);
#ifdef AIR_CELT_DEC_V2_ENABLE
            }
#endif
            if (!source->param.n9ble.pkt_lost_cnt) {
                DSP_MW_LOG_W("[BLE][source] Rx packet LOST with SEQ: %d, PTS:%d, TS: %d, PCNT: %d, CNT: %d, VALID: 0x%X, RO: %4d, WO: %4d", 8
                    , source->param.n9ble.seq_num + i
                    , source->param.n9ble.predict_timestamp
                    , buf_header->TimeStamp
                    , source->param.n9ble.predict_packet_cnt
                    , buf_header->EventCount
                    , buf_header->_reserved_byte_0Dh
                    , source->streamBuffer.ShareBufferInfo.read_offset
                    , source->param.n9ble.share_info_base_addr->write_offset
                );
            }
            source->param.n9ble.pkt_lost_cnt = 1;

            #ifdef AIR_BT_LE_LC3PLUS_ENABLE
            if (source->param.n9ble.plc_state_len != 0)
            {
                *plc_report_addr = LC3PLUS_DEC_FRAME_STATUS_PLC;
            }
            #endif
            g_pkt_lost_count++;
        }

        if(source->param.n9ble.predict_packet_cnt) {
            ++source->param.n9ble.predict_packet_cnt;
        }

#if 0
        DSP_MW_LOG_I("[BLE_DEBUG] AFTER info_addr = 0x%08x, predict = 0x%08x, TimeStamp = 0x%08x, valid = %d cnt= %d, RO = %d, WO = %d", 7,
            source->param.n9ble.share_info_base_addr,
            source->param.n9ble.predict_timestamp,
            buf_header->TimeStamp,
            buf_header->_reserved_byte_0Dh,
            buf_header->EventCount,
            source->streamBuffer.ShareBufferInfo.read_offset,
            //source->streamBuffer.ShareBufferInfo.write_offset
            source->param.n9ble.share_info_base_addr->write_offset
        );

#endif

        if (source->param.n9ble.dual_cis_status != DUAL_CIS_DISABLED) {
            read_ptr = (U8 *)((U32)source->param.n9ble.sub_share_info_base_addr + ((source->streamBuffer.ShareBufferInfo.read_offset + source->param.n9ble.dual_cis_buffer_offset)%source->streamBuffer.ShareBufferInfo.length));

            write_ptr = (source->param.n9ble.dual_cis_status == DUAL_CIS_DISABLED) ? dst_addr + i * g_ble_abr_length : dst_addr + (i * 2 + 1) * g_ble_abr_length;

            buf_header = (LE_AUDIO_HEADER *)read_ptr;
            if (N9Ble_check_avm_frame_valid(buf_header, TRUE)) {
                g_ble_pkt_lost[i][1] = false;
#ifdef AIR_CELT_DEC_V2_ENABLE
                if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
                    *((U32*)dst_addr2) = CELT_DEC_FRAME_STATUS_NORMAL;
                    dst_addr2 += source->param.n9ble.plc_state_len;
                    memcpy(dst_addr2, read_ptr + BLE_AVM_FRAME_HEADER_SIZE, g_ble_abr_length/2);
                    dst_addr2 += ALIGN_4(g_ble_abr_length/2);
                    *((U32*)dst_addr2) = CELT_DEC_FRAME_STATUS_NORMAL;
                    dst_addr2 += source->param.n9ble.plc_state_len;
                    memcpy(dst_addr2, read_ptr + BLE_AVM_FRAME_HEADER_SIZE + g_ble_abr_length/2, g_ble_abr_length/2);
                } else {
#endif
                memcpy(write_ptr, read_ptr + BLE_AVM_FRAME_HEADER_SIZE, g_ble_abr_length);
#ifdef AIR_CELT_DEC_V2_ENABLE
                }
#endif
                if(!source->param.n9ble.predict_packet_cnt_sub) {
                    source->param.n9ble.predict_packet_cnt_sub = buf_header->EventCount;
                }

                if(source->param.n9ble.predict_packet_cnt_sub != buf_header->EventCount) {
                    DSP_MW_LOG_W("[BLE][source] Rx sub packet cnt mismatch %d != %d", 2
                        , source->param.n9ble.predict_packet_cnt_sub
                        , buf_header->EventCount
                    );
                    source->param.n9ble.predict_packet_cnt_sub = 0;
                }

                if (source->param.n9ble.pkt_lost_cnt_sub) {
                    DSP_MW_LOG_W("[BLE][source] Rx sub packet RECV with SEQ: %d, PTS:%d, TS: %d, PCNT: %d, CNT: %d, VALID: 0x%X", 6
                        , source->param.n9ble.seq_num + i
                        , source->param.n9ble.predict_timestamp
                        , buf_header->TimeStamp
                        , source->param.n9ble.predict_packet_cnt_sub
                        , buf_header->EventCount
                        , buf_header->_reserved_byte_0Dh
                    );
                }
                source->param.n9ble.pkt_lost_cnt_sub = 0;

                if ((((abs32((S32)(buf_header->TimeStamp - source->param.n9ble.predict_timestamp)) * 625) >> 1) > source->param.n9ble.iso_interval)&& ((source->param.n9ble.seq_num % 1000) == 0)) {
                    DSP_MW_LOG_W("[BLE][source] sub ts info %d %d index:%d", 3, buf_header->TimeStamp, source->param.n9ble.predict_timestamp, ((source->streamBuffer.ShareBufferInfo.read_offset + source->param.n9ble.dual_cis_buffer_offset)%source->streamBuffer.ShareBufferInfo.length));
                }

                #if 0
                if(source->param.n9ble.predict_packet_cnt && source->param.n9ble.sub_share_info_base_addr->write_offset == ((source->streamBuffer.ShareBufferInfo.read_offset + source->param.n9ble.dual_cis_buffer_offset)%source->streamBuffer.ShareBufferInfo.length)) {
                    DSP_MW_LOG_W("[BLE][source] sub AVM RW access conflict seq: %d, PTS: %d, RO: %d, WO %d", 4
                        , source->param.n9ble.seq_num + i
                        , source->param.n9ble.predict_timestamp
                        , ((source->streamBuffer.ShareBufferInfo.read_offset + source->param.n9ble.dual_cis_buffer_offset)%source->streamBuffer.ShareBufferInfo.length)
                        , source->param.n9ble.sub_share_info_base_addr->write_offset
                    );
                }
                #endif
            } else {
                g_ble_pkt_lost[i][1] = true;
#ifdef AIR_CELT_DEC_V2_ENABLE
                if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR){
                    *((U32*)dst_addr2) = CELT_DEC_FRAME_STATUS_PLC;
                    dst_addr2 += source->param.n9ble.plc_state_len;
                    memset(dst_addr2, 0, g_ble_abr_length/2);
                    dst_addr2 += ALIGN_4(g_ble_abr_length/2);
                    *((U32*)dst_addr2) = CELT_DEC_FRAME_STATUS_PLC;
                    dst_addr2 += source->param.n9ble.plc_state_len;
                    memset(dst_addr2, 0, g_ble_abr_length/2);
                } else {
#endif
                memset(write_ptr, 0, g_ble_abr_length);
#ifdef AIR_CELT_DEC_V2_ENABLE
                }
#endif
                if (!source->param.n9ble.pkt_lost_cnt_sub) {
                    DSP_MW_LOG_W("[BLE][source] Rx sub packet LOST with SEQ: %d, PTS:%d, TS: %d, PCNT: %d, CNT: %d, VALID: 0x%X", 6
                        , source->param.n9ble.seq_num + i
                        , source->param.n9ble.predict_timestamp
                        , buf_header->TimeStamp
                        , source->param.n9ble.predict_packet_cnt_sub
                        , buf_header->EventCount
                        , buf_header->_reserved_byte_0Dh
                    );
                }
                source->param.n9ble.pkt_lost_cnt_sub = 1;

                #ifdef AIR_BT_LE_LC3PLUS_ENABLE
                if (source->param.n9ble.plc_state_len != 0)
                {
                    *plc_report_addr = LC3PLUS_DEC_FRAME_STATUS_PLC;
                }
                #endif
            }

            if(source->param.n9ble.predict_packet_cnt_sub) {
                ++source->param.n9ble.predict_packet_cnt_sub;
            }
        }

        N9Ble_SourceUpdateLocalReadOffset(source, 1);
    }

    return TRUE;
}

bool ble_query_rx_packet_lost_status(uint32_t index)
{
    return g_ble_pkt_lost[index][0];
}
bool ble_query_rx_sub_cis_packet_lost_status(uint32_t index)
{
    return g_ble_pkt_lost[index][1];
}
/**
 * SourceCloseN9Ble
 *
 * Function to shutdown BLE source.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
static BOOL SourceCloseN9Ble(SOURCE source)
{
    source->param.n9ble.frame_length = 0;
    source->param.n9ble.process_number = 0;
    source->param.n9ble.share_info_base_addr = NULL;
    source->param.n9ble.seq_num = 0;

#if defined(AIR_BLE_FIXED_RATIO_SRC_ENABLE) && defined(AIR_FIXED_RATIO_SRC)
    N9Ble_DL_SWB_Sample_Rate_Deinit();
#endif

#ifdef AIR_BT_LE_LC3PLUS_ENABLE
       if(source->param.n9ble.codec_type == BT_BLE_CODEC_LC3PLUS ) {
           DSP_MW_LOG_I("[BLE][LC3PLUS_DEC] deinit\r\n", 0);
           stream_codec_decoder_lc3plus_deinit(LC3PLUS_DEC_PORT_0,source);
        }
#endif

#ifdef AIR_CELT_DEC_V2_ENABLE
       if(source->param.n9ble.codec_type == BT_BLE_CODEC_VENDOR) {
           DSP_MW_LOG_I("[BLE][CELT] deinit\r\n", 0);
           stream_codec_decoder_celt_v2_deinit(CELT_DEC_PORT_0,source);
       }
#endif

    DSP_MW_LOG_I("[BLE][source] total packet lost count %d", 1, g_pkt_lost_count);

    return TRUE;
}

/**
 * SourceInitBle
 *
 * Function to initialize BLE source.
 *
 * @Author : RyanHung <Ryan.Hung@airoha.com.tw>
 */
VOID SourceInitN9Ble(SOURCE source)
{
    N9Ble_Default_setting_init(source, NULL);

    source->buftype = BUFFER_TYPE_CIRCULAR_BUFFER;
    N9Ble_Rx_Buffer_Init(source);

    source->sif.SourceSize       = SourceSizeN9Ble;
    source->sif.SourceReadBuf    = SourceReadBufN9Ble;
    source->sif.SourceMap        = SourceMapN9Ble;
    source->sif.SourceConfigure  = SourceConfigureN9Ble;
    source->sif.SourceDrop       = SourceDropN9Ble;
    source->sif.SourceClose      = SourceCloseN9Ble;

    source->param.n9ble.IsFirstIRQ = TRUE;
    //source->param.n9ble.dl_enable_ul = !source->param.n9ble.dl_only;     // false = DL irq gpt already anchored yet
    source->param.n9ble.write_offset_advance = 1; // force stream process to prevent first package lost
    source->param.n9ble.seq_num = 0;
    source->param.n9ble.predict_packet_cnt = 0;
    source->param.n9ble.predict_packet_cnt_sub = 0;
#ifdef AIR_BLE_FEATURE_MODE_ENABLE
    source->param.n9ble.dl_reinit = false;
    g_ble_dl_ul_process_active = false;
#endif
    g_pkt_lost_count = 0;
    memset(g_ble_pkt_lost, 0, sizeof(g_ble_pkt_lost));
}

VOID SourceInitBleAvm(SOURCE source,SINK sink)
{
    N9Ble_Default_setting_init(source, sink);
    if(source != NULL){
        N9BleRx_update_from_share_information(source);
    }
    if(sink != NULL){
        N9BleTx_update_from_share_information(sink);
    }
}


////////////////////////////////////////////////////////////////////////////////
//              BLE Audio playback source related
////////////////////////////////////////////////////////////////////////////////

#define BLE_UL_MAX_NUM                  2

typedef struct {
    uint32_t buffer_start[BLE_UL_MAX_NUM];
    uint32_t buffer_offset[BLE_UL_MAX_NUM];
    uint16_t buffer_index;
    uint16_t buffer_index_max;
    uint16_t buffer_size;
    uint16_t frame_head_len;
    uint16_t frame_data_len;
    uint8_t  is_source;
    uint8_t  is_playback_mode;
    uint8_t  is_1k_tone_mode;
    uint8_t  sample_rate;
    uint8_t  bitrate;
    uint8_t  num_of_sink;
    uint8_t  seq_num;
} LE_AUDIO_SOURCE_CTRL;

static LE_AUDIO_SOURCE_CTRL le_source;
static n9_dsp_share_info_ptr ul_info[BLE_UL_MAX_NUM];
static n9_dsp_share_info_ptr dl_info;

void CB_N9_BLE_UL_INFO(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    UNUSED(ack);

    uint16_t index = (uint16_t)msg.ccni_message[0];

    le_source.is_source = TRUE; //this CCNI should only be used by SOURCE device
    le_source.is_playback_mode = TRUE;

    switch (index) {
        case 0x5A5A:
            le_source.is_playback_mode = FALSE;
            ul_info[0] = NULL;
            ul_info[1] = NULL;
            return;
        case 1:
            ul_info[0] = (msg.ccni_message[1] == 0) ? NULL : (n9_dsp_share_info_ptr)hal_memview_cm4_to_dsp0(msg.ccni_message[1]);
            ul_info[1] = NULL;

            le_source.buffer_start[0]  = hal_memview_cm4_to_dsp0(ul_info[0]->start_addr);
            le_source.buffer_offset[0] = 0;

            //DSP_MW_LOG_I("[le audio DSP] ul1 info = %X  ul1 buffer = %X", 2, ul_info[0], le_source.buffer_start[0]);
            break;
        case 2:
            ul_info[1] = (msg.ccni_message[1] == 0) ? NULL : (n9_dsp_share_info_ptr)hal_memview_cm4_to_dsp0(msg.ccni_message[1]);

            le_source.buffer_start[1]  = hal_memview_cm4_to_dsp0(ul_info[1]->start_addr);
            le_source.buffer_offset[1] = 0;

            //DSP_MW_LOG_I("[le audio DSP] ul2 info = %X  ul2 buffer = %X", 2, ul_info[1], le_source.buffer_start[1]);
            break;
        default:
            //DSP_MW_LOG_I("[le audio DSP] invalid UL info", 0);
            break;
    }
}

void CB_N9_BLE_DL_INFO(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    UNUSED(ack);

    le_source.is_source = TRUE; //this CCNI should only be used by SOURCE device
    le_source.is_playback_mode = FALSE;

    dl_info = (msg.ccni_message[1] == 0) ? NULL : (n9_dsp_share_info_ptr)hal_memview_cm4_to_dsp0(msg.ccni_message[1]);
    //DSP_MW_LOG_I("[le audio DSP] dl buffer = %X", 1, dl_info);

    if (le_source.is_playback_mode) {
        //DSP_MW_LOG_I("[le audio DSP] Music mode (playback)", 0);
    } else {
        //DSP_MW_LOG_I("[le audio DSP] Voice mode (loopback)", 0);
    }
}

void CB_N9_BLE_UL_UPDATE_TIMESTAMP(hal_ccni_event_t event, void *msg)
{
    uint32_t i, bt_count, buffer_offset;
    hal_ccni_message_t *ccni_msg = msg;
    LE_AUDIO_HEADER *buf_header = NULL;
    uint8_t *avm_buffer;
    uint32_t saved_mask;
    uint32_t buf_index;
    UNUSED(event);
    UNUSED(msg);
    UNUSED(avm_buffer);

    bt_count = ccni_msg->ccni_message[0];

    hal_nvic_save_and_set_interrupt_mask(&saved_mask);
    buf_index = le_source.buffer_index;
    if ((le_source.is_source) && (le_source.is_playback_mode)) {
        buffer_offset = (ALIGN_4(le_source.frame_head_len + le_source.frame_data_len)) * le_source.buffer_index;

        for (i = 0; i < BLE_UL_MAX_NUM; i++) {
            if (ul_info[i]) {
                buf_header = (LE_AUDIO_HEADER *)(le_source.buffer_start[i] + buffer_offset);
                buf_header->TimeStamp = bt_count;
            }
        }

        le_source.buffer_index = (le_source.buffer_index + 1) % le_source.buffer_index_max;
        le_source.seq_num = (le_source.seq_num + 1) & 0xff;
    }
    hal_nvic_restore_interrupt_mask(saved_mask);

    //DSP_MW_LOG_I("[le audio DSP] irq update timestamp, 0x%x, 0x%x, 0x%x", 3, buf_header, buf_index, bt_count);
}

void CB_N9_BLE_UL_PLAYBACK_DATA_INFO(hal_ccni_message_t msg, hal_ccni_message_t *ack)
{
    uint32_t saved_mask;
    UNUSED(ack);

    if ((uint16_t)msg.ccni_message[0] == 0xFFFF) {
        le_source.is_1k_tone_mode = !le_source.is_1k_tone_mode;
        //DSP_MW_LOG_I("[le audio DSP] toggle playback source between line_in/1K tone", 0);
    } else if ((uint16_t)msg.ccni_message[0] == 0x9999) {
//        hal_audio_trigger_start_parameter_t sw_trigger_start;
//        sw_trigger_start.enable = true;
//        sw_trigger_start.memory_select = playback_vp_if.sink->param.audio.mem_handle.memory_select;
//        hal_audio_set_value((hal_audio_set_value_parameter_t *)&sw_trigger_start,HAL_AUDIO_SET_TRIGGER_MEMORY_START);
        //DSP_MW_LOG_I("[le audio DSP] trigger line-in irq start", 0);
    } else {
        hal_nvic_save_and_set_interrupt_mask(&saved_mask);
        le_source.is_source = TRUE;
        le_source.is_playback_mode = TRUE;
        le_source.frame_head_len = (uint16_t)BLE_AVM_FRAME_HEADER_SIZE;
        le_source.frame_data_len = (uint16_t)msg.ccni_message[1];
        le_source.sample_rate    = (uint8_t)(msg.ccni_message[1] >> 16);
        le_source.bitrate        = (uint8_t)(msg.ccni_message[1] >> 24);
        le_source.num_of_sink    = (uint16_t)msg.ccni_message[0];
        le_source.buffer_size    = ALIGN_4(le_source.frame_data_len + le_source.frame_head_len) * N9Ble_calculate_avm_frame_num(((28+156)*6),le_source.frame_data_len);
        le_source.buffer_index   = 0;
        le_source.buffer_index_max = N9Ble_calculate_avm_frame_num(((28+156)*6),le_source.frame_data_len);
        le_source.seq_num = 0;

#ifdef AIR_AUDIO_TRANSMITTER_ENABLE
        /* register ccni callback */
        extern void audio_transmitter_register_isr_handler(uint32_t index, f_audio_transmitter_ccni_callback_t callback);
        audio_transmitter_register_isr_handler(0, CB_N9_BLE_UL_UPDATE_TIMESTAMP);
#endif /* AIR_AUDIO_TRANSMITTER_ENABLE */

        hal_nvic_restore_interrupt_mask(saved_mask);

        //DSP_MW_LOG_I("[le audio DSP] sink num: %d   frame_data_len:%d buffer_size:%d  sample_rate:%d bitrate:%d blocknum:%d", 6,
        //             le_source.num_of_sink, le_source.frame_data_len, le_source.buffer_size, le_source.sample_rate, le_source.bitrate, le_source.buffer_index_max);
    }
}

bool STREAM_BLE_UL_CHECK_MODE(void)
{
    return le_source.is_1k_tone_mode;
}

bool STREAM_BLE_UL_GET_PARAM(uint32_t *sample_rate, uint32_t *bitrate)
{
    if (le_source.is_source && le_source.is_playback_mode) {
        if (sample_rate) {
            *sample_rate = 1000 * le_source.sample_rate;
        }
        if (bitrate) {
            *bitrate = 1000 * le_source.bitrate;
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

bool STREAM_BLE_UL_CHECK_BUF(uint8_t index)
{
    if (le_source.is_source && le_source.is_playback_mode) {
        if (index < BLE_UL_MAX_NUM && ul_info[index]) {
            return TRUE;
        }
    }
    return FALSE;
}

uint32_t STREAM_BLE_UL_GET_BUF_INDEX(void)
{
    return le_source.buffer_index;
}

void STREAM_BLE_UL_WRITE_BUF(uint8_t index, uint8_t *buf, uint32_t len, uint32_t buffer_index)
{
    uint32_t buffer_offset;

    if (len != le_source.frame_data_len) {
        //DSP_MW_LOG_I("[le audio DSP] STREAM_BLE_UL_WRITE_BUF len abnormal: %d ", 1, len);
    }

    if (le_source.is_source && le_source.is_playback_mode && index < BLE_UL_MAX_NUM) {
        if (ul_info[index]) {

            buffer_offset = (ALIGN_4(le_source.frame_head_len + le_source.frame_data_len)) * buffer_index;
            LE_AUDIO_HEADER *buf_header = (LE_AUDIO_HEADER *)(le_source.buffer_start[index] + buffer_offset);
            uint8_t *avm_buffer = (uint8_t *)buf_header + le_source.frame_head_len;

            if ((uint32_t)avm_buffer & 0x80000000) {

                memcpy(avm_buffer, buf, len);
                buf_header->DataOffset              = le_source.frame_head_len;
                buf_header->Pdu_LEN_Without_MIC     = le_source.frame_data_len;

                // static uint32_t countttt = 0;
                // countttt++;

                // le_source.buffer_offset[index] += ALIGN_4(le_source.frame_head_len + le_source.frame_data_len);
                // if(countttt<50 && index==0)
                //     DSP_MW_LOG_I("[le audio DSP] 1.le_source.buffer_offset[index] : %d ", 1, le_source.buffer_offset[index] );
                // le_source.buffer_offset[index] %=  le_source.buffer_size;
                // if(countttt<50 && index==0)
                //     DSP_MW_LOG_I("[le audio DSP] 2.le_source.buffer_offset[index] : %d ", 1, le_source.buffer_offset[index] );
            } else {
                //DSP_MW_LOG_I("[le audio DSP] UL_GET_BUF AVM abnormal    avm_buffer:%X ", 1, avm_buffer);
            }

        } else {
            //DSP_MW_LOG_I("[le audio DSP] STREAM_BLE_UL_WRITE_BUF index invalid: %d", 1, index);
        }
    }
}


bool N9_BLE_SOURCE_ROUTINE(void)
{
    if (le_source.is_source) {
//
//        static uint8_t count = 0;
//        if(count<20)
//        {
//            count++;
//            if(ul1_info)
//                DSP_MW_LOG_I("ul1_info: start %X read %X write %X next %X sample %X length%X", 6,ul1_info->startaddr,ul1_info->ReadOffset,ul1_info->WriteOffset,ul1_info->sub_info.next,ul1_info->sample_rate,ul1_info->length);
//            else
//                DSP_MW_LOG_I("ul1_info empty",0);
//            if(dl_info)
//                DSP_MW_LOG_I("dl_info: start %X read %X write %X next %X sample %X length%X", 6,dl_info->startaddr,dl_info->ReadOffset,dl_info->WriteOffset,dl_info->sub_info.next,dl_info->sample_rate,dl_info->length);
//            else
//                DSP_MW_LOG_I("dl_info empty",0);
//        }
//
//        if(le_source.is_playback_mode && le_source.is_stream_data_valid)
//        {
//            SHARE_BUFFER_INFO avm_info;
//
//
//            memcpy((U32)&avm_info, (U32)ul1_info, 24);/* use first 24 bytes in info */
//
//            avm_info.startaddr = hal_memview_cm4_to_dsp0(avm_info.startaddr);
//            avm_info.length = BLE_AVM_FRAME_NUM*(BLE_AVM_FRAME_HEADER_SIZE+le_source.frame_length);
//
//            if(le_source.num_of_sink >= 1)
//            {
//                memcpy((U32)(avm_info.startaddr + avm_info.WriteOffset + BLE_AVM_FRAME_HEADER_SIZE), (U32)(le_source.stream_L_addr+le_source.stream_offset),le_source.frame_length);
//                avm_info.WriteOffset = (avm_info.WriteOffset+le_source.frame_length+BLE_AVM_FRAME_HEADER_SIZE)%avm_info.length;
//            }
//            if(le_source.num_of_sink >= 2)
//            {
//                memcpy((U32)(avm_info.startaddr + avm_info.WriteOffset + BLE_AVM_FRAME_HEADER_SIZE), (U32)(le_source.stream_R_addr+le_source.stream_offset),le_source.frame_length);
//                avm_info.WriteOffset = (avm_info.WriteOffset+le_source.frame_length+BLE_AVM_FRAME_HEADER_SIZE)%avm_info.length;
//            }
//
//            le_source.stream_offset = (le_source.frame_length+le_source.stream_offset)%le_source.stream_size;
//
//            if(le_source.stream_offset == 0)
//            {
//                printf("stream_offset == 0. Repeat again");
//            }
//
//            memcpy((U32)ul1_info, (U32)&avm_info, 24);/* use first 24 bytes in info */
//        }
//
        return TRUE;
    } else { // not source device
        return FALSE;
    }
}

#endif

