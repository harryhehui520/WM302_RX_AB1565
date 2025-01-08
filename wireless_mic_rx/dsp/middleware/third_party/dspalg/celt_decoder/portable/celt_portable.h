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

#ifndef  __CELT_PORTABLE_H__
#define  __CELT_PORTABLE_H__

#ifdef MTK_BT_CELT_USE_PIC


typedef int (*p_celt_codec_get_version)(void);
typedef int (*p_celt_encode_get_size)(int rate, int channels, int frame_size, int version);
typedef int (*p_celt_encode_init)(void **enc, void *p_enc_mem, int rate, int channels, int frame_size, int complexity, int bytes_per_packet, int version);
typedef int (*p_celt_encode_prcs)(void *st_t, const int16_t *pcm, int frame_size, unsigned char *compressed, int nbCompressedBytes);
typedef int (*p_celt_decode_get_size)(int rate, int channels, int frame_size, int version);
typedef int (*p_celt_decode_init)(void **dec, void *p_dec_mem, int rate, int channels, int frame_size, int *skip, int bytes_per_packet, int version);
typedef int (*p_celt_decode_prcs)(void *st_t, const unsigned char *data, int len, int16_t* pcm, int frame_size, int packet_lost_st);



extern void *celt_import_parameters[];

/*for export parameters*************************************************/
extern void *celt_export_parameters[];

// {skew_ctrl_init, skew_ctrl_process};

#define celt_codec_get_version          ((p_celt_codec_get_version)celt_export_parameters[0])
#define celt_encode_get_size            ((p_celt_encode_get_size)celt_export_parameters[1])
#define celt_encode_init                ((p_celt_encode_init)celt_export_parameters[2])
#define celt_encode_prcs                ((p_celt_encode_prcs)celt_export_parameters[3])
#define celt_decode_get_size            ((p_celt_decode_get_size)celt_export_parameters[4])
#define celt_decode_init                ((p_celt_decode_init)celt_export_parameters[5])
#define celt_decode_prcs                ((p_celt_decode_prcs)celt_export_parameters[6])

extern uint32_t stream_codec_celt_get_version(void);
extern uint32_t stream_codec_celt_set_version(uint32_t version);

#endif

#endif

