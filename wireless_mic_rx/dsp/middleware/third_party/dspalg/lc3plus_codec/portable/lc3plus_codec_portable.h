/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#ifndef  __LC3PLUS_DEC_PORTABLE_H__
#define  __LC3PLUS_DEC_PORTABLE_H__

#ifdef AIR_BT_LE_LC3PLUS_USE_PIC

#include "lc3plus_codec_api.h"

#ifdef AIR_BT_LE_LC3PLUS_USE_ALL_MODE
typedef uint32_t (*LC3PLUS_Enc_Get_MemSize_t)(int32_t nChannels, int32_t SampleRate, uint16_t frame_ms);
typedef uint32_t (*LC3PLUS_Enc_Init_t)(void *p_lc3plus_mem_ext, uint16_t bits, uint32_t SampleRate, uint16_t nChannels, uint32_t BitRate, uint16_t frame_ms, uint16_t lfe);
typedef uint32_t (*LC3PLUS_Enc_Prcs_t)(void *p_lc3plus_mem_ext, uint8_t *bytes, uint8_t *BufI, uint32_t *nBytes);
typedef uint32_t (*LC3PLUS_Enc_Set_BitRate_t)(void *p_lc3plus_mem_ext, uint32_t BitRate);

typedef uint32_t (*LC3PLUS_Dec_Get_MemSize_t)(int32_t nChannels,  int32_t SampleRate, uint16_t frame_ms, int32_t plcMeth);
typedef void (*LC3PLUS_Dec_Get_Param_t)(void *p_lc3plus_mem_ext, uint32_t *nSamples, uint32_t *delay);
typedef uint32_t (*LC3PLUS_Dec_Init_t)(void *p_lc3plus_mem_ext, uint32_t bits, uint32_t SampleRate, uint16_t nChannels, uint16_t frame_ms, int32_t plcMeth);
typedef uint32_t (*LC3PLUS_Dec_Prcs_t)(void *p_lc3plus_mem_ext, uint8_t *bytes, uint8_t *BufO, uint32_t nBytes, uint16_t packet_lost_st, uint32_t bfi_ext);

typedef uint32_t (*LC3PLUS_Get_Version_t)(void);
#if defined(ROM_TABLE_ADDR_LC3_PLUS)
typedef void (*LC3PLUS_Set_ROM_Start_t)(void *lc3plus_addr, void *lc3_addr);
#endif
#else
typedef uint32_t (*LC3PLUSI_Enc_Prcs_t)(void *p_lc3plus_mem_ext, void *p_lc3plusi_tab, uint8_t *bytes, uint8_t *BufI, uint32_t *nBytes, LC3PLUSI_Multi_FFT *FFTx);
typedef uint32_t (*LC3PLUSI_Dec_Get_Param_t)(int32_t nChannels, int32_t SampleRate, uint16_t frame_ms, int32_t plcMeth);
typedef uint32_t (*LC3PLUSI_Dec_Prcs_t)(void *p_lc3plus_mem_ext, void *p_lc3plusi_tab, uint8_t *bytes, uint8_t *BufO, uint32_t nBytes, uint16_t packet_lost_st, uint32_t bfi_ext, LC3PLUSI_Multi_FFT *FFTx);

#endif

/* Referrence to the APIs of LC3PLUS library after preloader load done */
extern void *g_lc3plus_codec_export_parameters[];

#ifdef AIR_BT_LE_LC3PLUS_USE_ALL_MODE
#define LC3PLUS_Enc_Get_MemSize ((LC3PLUS_Enc_Get_MemSize_t)g_lc3plus_codec_export_parameters[0])
#define LC3PLUS_Enc_Init ((LC3PLUS_Enc_Init_t)g_lc3plus_codec_export_parameters[1])
#define LC3PLUS_Enc_Prcs ((LC3PLUS_Enc_Prcs_t)g_lc3plus_codec_export_parameters[2])
#define LC3PLUS_Enc_Set_BitRate ((LC3PLUS_Enc_Set_BitRate_t)g_lc3plus_codec_export_parameters[3])

#define LC3PLUS_Dec_Get_MemSize ((LC3PLUS_Dec_Get_MemSize_t)g_lc3plus_codec_export_parameters[4])
#define LC3PLUS_Dec_Get_Param ((LC3PLUS_Dec_Get_Param_t)g_lc3plus_codec_export_parameters[5])
#define LC3PLUS_Dec_Init ((LC3PLUS_Dec_Init_t)g_lc3plus_codec_export_parameters[6])
#define LC3PLUS_Dec_Prcs ((LC3PLUS_Dec_Prcs_t)g_lc3plus_codec_export_parameters[7])
#define LC3PLUS_Get_Version ((LC3PLUS_Get_Version_t)g_lc3plus_codec_export_parameters[8])
#if defined(ROM_TABLE_ADDR_LC3_PLUS)
#define LC3PLUS_Set_ROM_Start ((LC3PLUS_Set_ROM_Start_t)g_lc3plus_codec_export_parameters[9])
#endif
#else
/**/
#define LC3PLUSI_Enc_Prcs ((LC3PLUSI_Enc_Prcs_t)g_lc3plus_codec_export_parameters[0])
#define LC3PLUSI_Dec_Prcs ((LC3PLUSI_Dec_Prcs_t)g_lc3plus_codec_export_parameters[1])
#define LC3PLUSI_Dec_Get_Param ((LC3PLUSI_Dec_Get_Param_t)g_lc3plus_codec_export_parameters[2])

/*lc3plus 2p5MS*/
uint32_t lc3plusi_fft2_5ms_library_load(void *code_address, void *data_address, uint32_t *dram_pic_usage);
uint32_t lc3plusi_fft2_5ms_library_unload(void);
typedef void (*fix_fft_Init_2p5_MS_t)(void);
typedef void (*FFT8N_2p5_MS_t)(void);
typedef void (*fix_fft10_2p5_MS_t)(void);
typedef void (*fix_fft15_2p5_MS_t)(void);
typedef void (*fix_fft30_2p5_MS_t)(void);
typedef void (*fix_fft40_2p5_MS_t)(void);

extern void *g_lc3plusi_fft2_5ms_export_parameters[];
#define fix_fft_Init_2p5_MS ((fix_fft_Init_2p5_MS_t)g_lc3plusi_fft2_5ms_export_parameters[0])
#define FFT4N_2p5_MS        ((FFT8N_2p5_MS_t)g_lc3plusi_fft2_5ms_export_parameters[1])
#define FFT8N_2p5_MS        ((FFT8N_2p5_MS_t)g_lc3plusi_fft2_5ms_export_parameters[2])
#define fix_fft15_2p5_MS    ((fix_fft15_2p5_MS_t)g_lc3plusi_fft2_5ms_export_parameters[3])
#define fix_fft20_2p5_MS    ((fix_fft30_2p5_MS_t)g_lc3plusi_fft2_5ms_export_parameters[4])
#define fix_fft40_2p5_MS    ((fix_fft40_2p5_MS_t)g_lc3plusi_fft2_5ms_export_parameters[5])


/*lc3plus 5MS*/
uint32_t lc3plusi_fft5_0ms_library_load(void *code_address, void *data_address, uint32_t *dram_pic_usage);
uint32_t lc3plusi_fft5_0ms_library_unload(void);
typedef void (*fix_fft_Init_5_MS_t)(void);
typedef void (*FFT8N_5_MS_t)(void);
typedef void (*fix_fft10_5_MS_t)(void);
typedef void (*fix_fft15_5_MS_t)(void);
typedef void (*fix_fft30_5_MS_t)(void);
typedef void (*fix_fft40_5_MS_t)(void);

extern void *g_lc3plusi_fft5_0ms_export_parameters[];
#define fix_fft_Init_5_MS   ((fix_fft_Init_5_MS_t)g_lc3plusi_fft5_0ms_export_parameters[0])
#define FFT8N_5_MS          ((FFT8N_5_MS_t)g_lc3plusi_fft5_0ms_export_parameters[1])
#define fix_fft10_5_MS      ((fix_fft10_5_MS_t)g_lc3plusi_fft5_0ms_export_parameters[2])
#define fix_fft15_5_MS      ((fix_fft15_5_MS_t)g_lc3plusi_fft5_0ms_export_parameters[3])
#define fix_fft30_5_MS      ((fix_fft30_5_MS_t)g_lc3plusi_fft5_0ms_export_parameters[4])
#define fix_fft40_5_MS      ((fix_fft40_5_MS_t)g_lc3plusi_fft5_0ms_export_parameters[5])

/*lc3plus 10MS*/
uint32_t lc3plusi_fft10_0ms_library_load(void *code_address, void *data_address, uint32_t *dram_pic_usage);
uint32_t lc3plusi_fft10_0ms_library_unload(void);
typedef void (*fix_fft_Init_10_MS_t)(void);
typedef void (*FFFT8N_10_MS_t)(void);
typedef void (*fix_fft10_10_MS_t)(void);
typedef void (*FFT16N_10_MS_t)(void);
typedef void (*fix_fft20_10_MS_t)(void);
typedef void (*fix_fft30_10_MS_t)(void);
typedef void (*fix_fft40_10_MS_t)(void);

extern void *g_lc3plusi_fft10_0ms_export_parameters[];
#define fix_fft_Init_10_MS ((fix_fft_Init_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[0])
#define FFT8N_10_MS        ((FFFT8N_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[1])
#define fix_fft10_10_MS    ((fix_fft10_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[2])
#define FFT16N_10_MS       ((FFT16N_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[3])
#define fix_fft20_10_MS    ((fix_fft20_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[4])
#define fix_fft30_10_MS    ((fix_fft30_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[5])
#define fix_fft40_10_MS    ((fix_fft40_10_MS_t)g_lc3plusi_fft10_0ms_export_parameters[6])
#endif
#endif

#endif

