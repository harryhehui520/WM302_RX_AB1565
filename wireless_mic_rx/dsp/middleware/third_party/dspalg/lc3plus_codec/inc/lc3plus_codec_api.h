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

#ifndef __LC3PLUS_CODEC_API_H__
#define __LC3PLUS_CODEC_API_H__

#include "dsp_rom_table.h"

#ifndef _MSC_VER
#include <stdint.h>
#else
typedef unsigned char uint8_t;
typedef __int16       int16_t;
typedef __int32       int32_t;
#endif

/*! Maximum number of supported channels. 
 */
#define LC3PLUS_MAX_CHANNELS 2

/*! Maximum number of samples per channel that can be stored in one LC3 frame.
 */
#define LC3PLUS_MAX_SAMPLES  960

/*! Maximum number of bytes of one LC3 frame. 
 */
#define LC3PLUS_MAX_BYTES   (625 * LC3PLUS_MAX_CHANNELS)

typedef struct LC3PLUS_Enc LC3PLUS_Enc; /*!< Opaque encoder struct. */
typedef struct LC3PLUS_Dec LC3PLUS_Dec; /*!< Opaque decoder struct. */

/*! Architectures */
typedef enum {
    LC3PLUS_ARCH_FX,
    LC3PLUS_ARCH_FLT
} LC3PLUS_Architecture;

/*! Error codes returned by functions. */
typedef enum {
    LC3_UNUSED  = -1,                     /*!< Used for debugging purposes, not used by the library */
    LC3PLUS_OK,                               /*!< No error occurred */
    LC3PLUS_ALIGN_ERROR,                      /*!< Unaligned pointer */
    LC3PLUS_BITRATE_ERROR,                    /*!< Invalid bitrate */
    LC3PLUS_BITRATE_SET_ERROR,                /*!< Function called after bitrate has been set */
    LC3PLUS_BITRATE_UNSET_ERROR,              /*!< Function called before bitrate has been set */
    LC3PLUS_CHANNELS_ERROR,                   /*!< Invalid number of channels */
    LC3PLUS_DECODE_ERROR,                     /*!< Frame failed to decode and was concealed */
    LC3PLUS_EPMODE_ERROR,                     /*!< Invalid EP mode */
    LC3PLUS_EPMR_ERROR,                       /*!< Invalid EPMR */
    LC3PLUS_BITDEPTH_ERROR,                   /*!< Function called with illegal bit depth */
    LC3PLUS_FRAMEMS_ERROR,                    /*!< Invalid frame_ms */
    LC3PLUS_FRAMESIZE_ERROR,                  /*!< Frame size below minimum or above maximum */
    LC3PLUS_HRMODE_ERROR,                     /*!< Invalid usage of hrmode, sampling rate and frame size */
    LC3PLUS_NULL_ERROR,                       /*!< Pointer argument is null */
    LC3PLUS_NUMBYTES_ERROR,                   /*!< Invalid number of bytes */
    LC3PLUS_PADDING_ERROR,                    /*!< Padding error */
    LC3PLUS_PLCMODE_ERROR,                    /*!< Invalid PLC method */
    LC3PLUS_PLCMODE_CONF_ERROR,               /*!< PLC method not supported due to hrmode or frame size */
    LC3PLUS_RESTRICT_BT_BINARY_ERROR,         /*!< Unsupported combination of frame length, sampling rate and bitrate */
    LC3PLUS_SAMPLERATE_ERROR,                 /*!< Invalid sample rate */
    LC3PLUS_SCRATCH_INVALID_ERROR,            /*!< Scratch space not allocated or size invalidated */
    LC3PLUS_SET_BANDWIDTH_NOT_SUPPORTED,      /*!< Bandwidth controller not available */
    LC3PLUS_LFE_MODE_NOT_SUPPORTED,           /*!< LFE support not available */
    LC3PLUS_ERROR_PROTECTION_NOT_SUPPORTED,   /*!< Error protection not available */
    LC3PLUS_ALLOC_ERROR,                      /*!< Table allocation failed */
    LC3PLUS_WAV_FORMAT_NOT_SUPPORTED,         /*!< Unsupported waveform format */

    /* START WARNING */
    LC3PLUS_WARNING,
    LC3PLUS_BW_WARNING,                       /*!< Invalid bandwidth cutoff frequency */
    LC3PLUS_Error_LAST,                       /*!< Invalid error code */
	// Add
	LC3PLUS_MEM_NO_ENOUGH,
	LC3PLUS_PERMISSION_ERROR                  /*!< Invalid permission type */
} LC3PLUS_ErrorCode;

typedef enum
{
	C_PKT_Good 			= 0,
	C_PKT_Loss  		= 1,
	C_PKT_L_Good_R_Loss = 2,
	C_PKT_L_Loss_R_Good	= 3,
} PKT_ST;

/*! Decoder packet loss concealment mode */
typedef enum
{
    LC3PLUS_PLCMETH_STD,              /*!< Noise Substitution as specified in Bluetooth */
    LC3PLUS_PLCMETH_ADV_PHECU_TDC_NS, /*!< Enhanced concealment as specified in ETSI */
    LC3PLUS_PLCMETH_ADV_PHECU,        /*!< Phase ECU */
    LC3PLUS_PLCMETH_ADV_TDC_NS,       /*!< Time Domain Concealment + Advanced Noise Substitution */
    LC3PLUS_PLCMETH_ADV_NS,           /*!< Advanced Noise Substitution */
    LC3PLUS_PLCMETH_MUTING,           /*!< Muting */
    LC3PLUS_PLCMETH_MAXVAL,           /*!< max value */
    LC3PLUS_PLCMETH_UNSUPPORTED       /*!< unsupported marker */
} LC3PLUS_PlcMethod;

/*! Error protection mode. LC3PLUS_EP_ZERO differs to LC3PLUS_EP_OFF in that
 *  errors can be detected but not corrected. */
typedef enum
{
    LC3PLUS_EP_OFF    = 0, /*!< Error protection is disabled */
    LC3PLUS_EP_ZERO   = 1, /*!< Error protection with 0 bit correction */
    LC3PLUS_EP_LOW    = 2, /*!< Error protection correcting one symbol per codeword */
    LC3PLUS_EP_MEDIUM = 3, /*!< Error protection correcting two symbols per codeword */
    LC3PLUS_EP_HIGH   = 4  /*!< Error protection correcting three symbols per codeword */
} LC3PLUS_EpMode;

/*! Error protection mode request. On the encoder side, LC3PLUS_EPMR_ZERO to LC3PLUS_EPMR_HIGH
 *  can be set. The decoder returns mode requests with different confidences. */
typedef enum
{
    LC3PLUS_EPMR_ZERO      =  0, /*!< Request no error correction. High confidence if returned by decoder. */
    LC3PLUS_EPMR_LOW       =  1, /*!< Request low error correction. High confidence if returned by decoder. */
    LC3PLUS_EPMR_MEDIUM    =  2, /*!< Request medium error correction. High confidence if returned by decoder. */
    LC3PLUS_EPMR_HIGH      =  3, /*!< Request high error correction. High confidence if returned by decoder. */
    LC3PLUS_EPMR_ZERO_MC   =  4, /*!< No error correction requested, medium confidence. */
    LC3PLUS_EPMR_LOW_MC    =  5, /*!< Low error correction requested, medium confidence. */
    LC3PLUS_EPMR_MEDIUM_MC =  6, /*!< Medium error correction requested, medium confidence. */
    LC3PLUS_EPMR_HIGH_MC   =  7, /*!< High error correction requested, medium confidence. */
    LC3PLUS_EPMR_ZERO_NC   =  8, /*!< No error correction requested, unvalidated. */
    LC3PLUS_EPMR_LOW_NC    =  9, /*!< Low error correction requested, unvalidated. */
    LC3PLUS_EPMR_MEDIUM_NC = 10, /*!< Medium error correction requested, unvalidated. */
    LC3PLUS_EPMR_HIGH_NC   = 11  /*!< High error correction requested, unvalidated. */
} LC3PLUS_EpModeRequest;

typedef struct {
    int16_t frame_ms;      // LC3plus: 25(2.5ms), 50(5ms) and 100(10ms)
    int32_t   sr;          // set samplerate = 48K is input as 48000
} LC3PLUS_Param;

typedef struct {
    void (*fix_fft_Init)(void);
    void (*FFT4N)(void);
    void (*FFT8N)(void);
    void (*FFT16N)(void);
    void (*fix_fft10)(void);
    void (*fix_fft15)(void);
    void (*fix_fft16)(void);
    void (*fix_fft20)(void);
    void (*fix_fft30)(void);
    void (*fix_fft40)(void);
} LC3PLUSI_Multi_FFT;

/* V1.0 API
 */
#if defined(AIR_BT_LE_LC3PLUS_USE_ALL_MODE) || !defined(AIR_BT_LE_LC3PLUS_USE_PIC)
#if defined(ROM_TABLE_ADDR_LC3_PLUS)
void LC3PLUS_Set_ROM_Start(void *lc3plus_addr, void *lc3_addr);
#endif
uint32_t LC3PLUS_Enc_Get_MemSize(int32_t nChannels, int32_t SampleRate, uint16_t frame_ms);
LC3PLUS_ErrorCode LC3PLUS_Enc_Init(void *p_lc3plus_mem_ext, uint16_t bits, uint32_t SampleRate, uint16_t nChannels, uint32_t BitRate, uint16_t frame_ms, uint16_t lfe);
LC3PLUS_ErrorCode LC3PLUS_Enc_Prcs(void	*p_lc3plus_mem_ext, uint8_t *bytes, uint8_t *BufI, uint32_t *nBytes);
LC3PLUS_ErrorCode LC3PLUS_Enc_Set_BitRate(void *p_lc3plus_mem_ext, uint32_t BitRate);

uint32_t LC3PLUS_Dec_Get_MemSize(int32_t nChannels, int32_t SampleRate, uint16_t frame_ms, int32_t plcMeth);
void LC3PLUS_Dec_Get_Param(void *p_lc3plus_mem_ext, uint32_t *nSamples, uint32_t *delay);
LC3PLUS_ErrorCode LC3PLUS_Dec_Init(void *p_lc3plus_mem_ext, uint32_t bits, uint32_t SampleRate, uint16_t nChannels, uint16_t frame_ms, int32_t plcMeth);
LC3PLUS_ErrorCode LC3PLUS_Dec_Prcs(void *p_lc3plus_mem_ext, uint8_t *bytes, uint8_t *BufO, uint32_t nBytes, uint16_t packet_lost_st, uint32_t bfi_ext);
uint32_t LC3PLUS_Get_Version(void);
#else
uint32_t  LC3PLUSI_Get_Version(void);
void LC3PLUSI_Set_ROM_Start(void *lc3plus_addr, void *lc3_addr);
uint32_t LC3PLUSI_Enc_Get_MemSize(int nChannels, int sampleRate, short frame_ms);
uint32_t LC3PLUSI_Dec_Get_MemSize(int nChannels, int sampleRate, short frame_ms, int plcMeth);
void LC3PLUSI_Dec_Get_Param(void *p_lc3plus_mem_ext, uint32_t *nSamples, uint32_t *delay);
LC3PLUS_ErrorCode LC3PLUSI_Enc_Init(void *p_lc3plus_mem_ext, uint16_t bits, uint32_t SampleRate, uint16_t nChannels, uint32_t bitrate, uint16_t frame_ms, uint16_t lfe);
LC3PLUS_ErrorCode LC3PLUSI_Enc_Set_BitRate(void *p_lc3plus_mem_ext, int bitrate);
LC3PLUS_ErrorCode LC3PLUSI_Enc_Prcs(void *p_lc3plus_mem_ext, void *p_lc3plusi_tab, uint8_t *bytes, uint8_t *BufI, uint32_t *nBytes, LC3PLUSI_Multi_FFT *FFTx);
LC3PLUS_ErrorCode LC3PLUSI_Dec_Init(void *p_lc3plus_mem_ext, int bits, int SampleRate, int nChannels, uint16_t frame_ms, int plcMeth);
LC3PLUS_ErrorCode LC3PLUSI_Dec_Prcs(void *p_lc3plus_mem_ext, void *p_lc3plusi_tab, uint8_t *bytes, uint8_t *BufO, uint32_t nBytes, uint16_t packet_lost_st, uint32_t bfi_ext, LC3PLUSI_Multi_FFT *FFTx);
void lc3plus_get_enc_tab_memsize(int nChannels, int sampleRate, int frame_ms, int *encoder_size, int *scratch_size);
void lc3plus_get_dec_tab_memsize(int nChannels, int sampleRate, int frame_ms, int plcMeth, int *decoder_size, int *scratch_size);

/*Get size*/
int LC3PLUSI_Tab_Common_Get_MemSize(void);
int LC3PLUSI_Tab_Enc_Get_MemSize(LC3PLUS_Param *para);
#define LC3PLUSI_Tab_Dec_Get_MemSize LC3PLUSI_Tab_Enc_Get_MemSize

/* Init */
int LC3PLUSI_Tab_Common_Init(void *p_lc3plusi_tab);
int LC3PLUSI_Tab_Enc_Init(void *p_lc3plusi_tab, void *p_tab_mem, LC3PLUS_Param *para);
int LC3PLUSI_Tab_Dec_Init(void *p_lc3plusi_tab, void *p_tab_mem, LC3PLUS_Param *para);
//void LC3PLUSI_Tab_Link(void *p_lc3plusi_tab);


#define LC3PLUS_Enc_Get_MemSize LC3PLUSI_Enc_Get_MemSize
#define LC3PLUS_Enc_Init        LC3PLUSI_Enc_Init
#define LC3PLUS_Enc_Prcs        LC3PLUSI_Enc_Prcs
#define LC3PLUS_Enc_Set_BitRate LC3PLUSI_Enc_Set_BitRate
#define LC3PLUS_Dec_Get_MemSize LC3PLUSI_Dec_Get_MemSize
#define LC3PLUS_Dec_Get_Param   LC3PLUSI_Dec_Get_Param
#define LC3PLUS_Dec_Init        LC3PLUSI_Dec_Init
#define LC3PLUS_Dec_Prcs        LC3PLUSI_Dec_Prcs
#define LC3PLUS_Get_Version     LC3PLUSI_Get_Version
#endif


#endif /* LC3PLUS_CODEC_API_H */

