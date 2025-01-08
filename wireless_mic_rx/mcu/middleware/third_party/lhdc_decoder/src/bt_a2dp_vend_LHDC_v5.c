/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
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
/* Airoha restricted information */

#include <stdlib.h>
#include "bt_a2dp.h"
#include "syslog.h"
#include "vendor_2_dec_parser_interface.h"

#define A2DP_VENDOR_ID_SAMPLE                   (0x053A)

#define A2DP_VENDOR_CODEC_ID_SAMPLE             (0x4C35)

#define A2DP_VENDOR_SAMPLE_FREQ_192000          (0x01)
#define A2DP_VENDOR_SAMPLE_FREQ_176400          (0x02)
#define A2DP_VENDOR_SAMPLE_FREQ_96000           (0x04)
#define A2DP_VENDOR_SAMPLE_FREQ_88200           (0x08)
#define A2DP_VENDOR_SAMPLE_FREQ_48000           (0x10)
#define A2DP_VENDOR_SAMPLE_FREQ_44100           (0x20)
#define A2DP_VENDOR_SAMPLE_FREQ_MASK            (0x3F)

#define A2DP_VENDOR_SAMPLE_RESOLUTION_32BITS    (0x01)
#define A2DP_VENDOR_SAMPLE_RESOLUTION_24BITS    (0x02)
#define A2DP_VENDOR_SAMPLE_RESOLUTION_16BITS    (0x04)
#define A2DP_VENDOR_SAMPLE_RESOLUTION_MODE      A2DP_VENDOR_SAMPLE_RESOLUTION_24BITS
#define A2DP_VENDOR_SAMPLE_RESOLUTION_MASK      (A2DP_VENDOR_SAMPLE_RESOLUTION_32BITS | A2DP_VENDOR_SAMPLE_RESOLUTION_24BITS |A2DP_VENDOR_SAMPLE_RESOLUTION_16BITS)

#define A2DP_VENDOR_SAMPLE_MAXBITRATE_1000      (0x00)
#define A2DP_VENDOR_SAMPLE_MAXBITRATE_900       (0x30)
#define A2DP_VENDOR_SAMPLE_MAXBITRATE_500       (0x20)
#define A2DP_VENDOR_SAMPLE_MAXBITRATE_400       (0x10)
#define A2DP_VENDOR_SAMPLE_MINBITRATE_400       (0xC0)
#define A2DP_VENDOR_SAMPLE_MINBITRATE_256       (0x80)
#define A2DP_VENDOR_SAMPLE_MINBITRATE_128       (0x40)
#define A2DP_VENDOR_SAMPLE_MINBITRATE_64        (0x00)

#define A2DP_VENDOR_SAMPLE_MAXBITRATE_MASK      (A2DP_VENDOR_SAMPLE_MAXBITRATE_1000 | A2DP_VENDOR_SAMPLE_MAXBITRATE_900 | A2DP_VENDOR_SAMPLE_MAXBITRATE_500 | A2DP_VENDOR_SAMPLE_MAXBITRATE_400)
#define A2DP_VENDOR_SAMPLE_MINBITRATE_MASK      (A2DP_VENDOR_SAMPLE_MINBITRATE_400 | A2DP_VENDOR_SAMPLE_MINBITRATE_256 | A2DP_VENDOR_SAMPLE_MINBITRATE_128 | A2DP_VENDOR_SAMPLE_MINBITRATE_64)

#define A2DP_VENDOR_SAMPLE_LOW_LATENCY_MODE     (0x40)

#define A2DP_VENDOR_SAMPLE_FREQ_DEFAULT  A2DP_VENDOR_SAMPLE_FREQ_48000
#define A2DP_VENDOR_SAMPLE_RESOLUTION_MODE_DEFAULT  A2DP_VENDOR_SAMPLE_RESOLUTION_MODE
#define A2DP_VENDOR_SAMPLE_MAXBITRATE_DEFAULT	A2DP_VENDOR_SAMPLE_MAXBITRATE_400
#define A2DP_VENDOR_SAMPLE_MINBITRATE_DEFAULT	A2DP_VENDOR_SAMPLE_MINBITRATE_400

#define A2DP_LHDCV5_VERSION_NUM                 (0x01)
#define A2DP_LHDCV5_VERSION_MASK                (0x0F)

#define A2DP_LHDCV5_FRAME_5MS                   (0x10)
typedef enum __LHDCV5_QUALITY__
{
  LHDCV5_QUALITY_LOW0 = 0,	//64
  LHDCV5_QUALITY_LOW1,		//128
  LHDCV5_QUALITY_LOW2,		//192
  LHDCV5_QUALITY_LOW3,		//256
  LHDCV5_QUALITY_LOW4,		//320
  LHDCV5_QUALITY_LOW,		//400
  LHDCV5_QUALITY_MID,		//500
  LHDCV5_QUALITY_HIGH,		//900
  LHDCV5_QUALITY_HIGH1,		//1000
  LHDCV5_QUALITY_AUTO,
  LHDCV5_QUALITY_RESET_AUTO,
  LHDCV5_QUALITY_INVALID
} LHDCV5_QUALITY_T;

log_create_module(LHDC, PRINT_LEVEL_INFO);

bool check_is_power_of_2(uint32_t num) {
    if(num && (num & (num-1)) == 0) {
        return true;
    } else {
        return false;
    }
}

uint32_t get_data_within_specified_bit(uint32_t data, uint32_t bit_num)
{
    uint32_t a_idx=0, b_idx = bit_num-1;
    while (a_idx <= b_idx) {
        if (data & (1 << a_idx)) {
            return (1 << a_idx);
        }
        ++a_idx;
    }

    return 0;
}

uint8_t get_max_bitrate_idx(uint8_t data)
{
	uint8_t target=0;
	
    switch (data){
		case A2DP_VENDOR_SAMPLE_MAXBITRATE_1000:
			target = LHDCV5_QUALITY_HIGH1;
			break;
		
		case A2DP_VENDOR_SAMPLE_MAXBITRATE_900:
			target = LHDCV5_QUALITY_HIGH;
			break;
		
		case A2DP_VENDOR_SAMPLE_MAXBITRATE_500:
			target = LHDCV5_QUALITY_MID;
			break;
		
		case A2DP_VENDOR_SAMPLE_MAXBITRATE_400:
			target = LHDCV5_QUALITY_LOW;
			break;	
		
		default:
			target = LHDCV5_QUALITY_INVALID;
			break;
	}
	return target;
}

uint8_t get_max_bitrate(uint8_t idx)
{
	uint8_t br=0;

    switch (idx){
		case LHDCV5_QUALITY_HIGH1:
			br = A2DP_VENDOR_SAMPLE_MAXBITRATE_1000;
			break;
		
		case LHDCV5_QUALITY_HIGH:
			br = A2DP_VENDOR_SAMPLE_MAXBITRATE_900;
			break;
		
		case LHDCV5_QUALITY_MID:
			br = A2DP_VENDOR_SAMPLE_MAXBITRATE_500;
			break;
		
		case LHDCV5_QUALITY_LOW:
			br = A2DP_VENDOR_SAMPLE_MAXBITRATE_400;
			break;	
		
		default:
			br = A2DP_VENDOR_SAMPLE_MAXBITRATE_DEFAULT;
			break;
	}
	return br;
}

uint8_t get_min_bitrate_idx(uint8_t data)
{
	uint8_t target=0;
	
    switch (data){
		case A2DP_VENDOR_SAMPLE_MINBITRATE_400:
			target = LHDCV5_QUALITY_LOW;
			break;
		
		case A2DP_VENDOR_SAMPLE_MINBITRATE_256:
			target = LHDCV5_QUALITY_LOW3;
			break;
		
		case A2DP_VENDOR_SAMPLE_MINBITRATE_128:
			target = LHDCV5_QUALITY_LOW1;
			break;
		
		case A2DP_VENDOR_SAMPLE_MINBITRATE_64:
			target = LHDCV5_QUALITY_LOW0;
			break;	
		
		default:
			target = LHDCV5_QUALITY_INVALID;
			break;
	}
	return target;
}

uint8_t get_min_bitrate(uint8_t idx)
{
	uint8_t br=0;
	
    switch (idx){
		case LHDCV5_QUALITY_LOW:
			br = A2DP_VENDOR_SAMPLE_MINBITRATE_400;
			break;
		
		case LHDCV5_QUALITY_LOW3:
			br = A2DP_VENDOR_SAMPLE_MINBITRATE_256;
			break;
		
		case LHDCV5_QUALITY_LOW1:
			br = A2DP_VENDOR_SAMPLE_MINBITRATE_128;
			break;
		
		case LHDCV5_QUALITY_LOW0:
			br = A2DP_VENDOR_SAMPLE_MINBITRATE_64;
			break;	
		
		default:
			br = A2DP_VENDOR_SAMPLE_MINBITRATE_DEFAULT;
			break;
	}
	return br;
}
/**

@brief This function is used to validate the vendor codec parameters configured from remote end.
@param[in] codec is the configured codec form remote, which is requested to check the validation by local end.
@return true, the codec is configured reasonable, and local end will accept this configuration.
false, the codec is configured wrongly, and local end will reject this configuration.
*/
bool bt_a2dp_validate_vendor_codec(const bt_a2dp_vendor_codec_t *codec, uint32_t length)
{
    LHDC_LOG_W("[AVDTP] bt_a2dp_validate_vendor_codec()\r\n", 0);

    bool ret = false;

    LHDC_LOG_W("[AVDTP] vendor_id=0x%X, codec_id: 0x%X\r\n", 2, codec->vendor_id, codec->codec_id);

    if (codec->vendor_id != A2DP_VENDOR_ID_SAMPLE || codec->codec_id != A2DP_VENDOR_CODEC_ID_SAMPLE) {
        return ret;
    }

    uint32_t freq = (codec->value[0] & A2DP_VENDOR_SAMPLE_FREQ_MASK);
    bool freq_valid = check_is_power_of_2(freq);
    if (!freq_valid) LHDC_LOG_W("[AVDTP] freq_valid :%d freq 0x%x\r\n", 2, freq_valid, freq);

    uint32_t resolution = (codec->value[1]& A2DP_VENDOR_SAMPLE_RESOLUTION_MASK);
    bool resolution_valid = check_is_power_of_2(resolution);
    if (!resolution_valid) LHDC_LOG_W("[AVDTP] resolution_valid :%d resolution 0x%x\r\n", 2, resolution_valid, resolution);

    uint32_t max_br = (codec->value[1] & A2DP_VENDOR_SAMPLE_MAXBITRATE_MASK) >> 4;
    bool max_br_valid = (max_br < 4)? true: false;
    if (!max_br_valid) LHDC_LOG_W("[AVDTP] max_br_valid :%d max_br 0x%x\r\n", 2, max_br_valid, max_br);

    uint32_t min_br = (codec->value[1] & A2DP_VENDOR_SAMPLE_MINBITRATE_MASK) >> 6;
    bool min_br_valid = (min_br < 4)? true: false;
    if (!min_br_valid) LHDC_LOG_W("[AVDTP] min_br_valid :%d min_br 0x%x\r\n", 2, min_br_valid, min_br);

    //uint32_t ver = (codec->value[2] & A2DP_LHDCV5_VERSION_MASK);
    //bool ver_valid = (ver == A2DP_LHDCV5_VERSION_NUM)? true: false;
    //if (!ver_valid) LOG_MSGID_I(VENDOR_CODEC, "ver_valid :%d ver 0x%x codec->value[2]0x%x \r\n", 3, ver_valid, ver, codec->value[2]); 

    //uint32_t LL_MODE = (codec->value[3] & A2DP_VENDOR_SAMPLE_LOW_LATENCY_MODE); // Current value smaller than 3
  
    ret = (freq_valid && resolution_valid && max_br_valid && min_br_valid /*&& ver_valid*/);

    LHDC_LOG_W("[AVDTP] (valid) ret: %d\r\n", 1, ret);

    return ret;
}
/**

@brief This function is used to negotiate the configuration of A2DP vendor codec while local initiates
the A2DP connection to remote, and then output the negotiation result with the local codec and remote codec.
@param[out] result is the negotiation result of the A2DP vendor codec.
@param[in] local is the A2DP vendor codec local supported.
@param[in] remote is the A2DP vendor codec local supported.
@return true, a configuratioin supported in both local and remote.
false, there is no configuration supported in local or remote.
*/
bool bt_a2dp_negotiate_vendor_codec(bt_a2dp_vendor_codec_t *result, const bt_a2dp_vendor_codec_t *local, const bt_a2dp_vendor_codec_t *remote)
{
//    if (vendor->vendor_id != A2DP_VENDOR_ID_SAMPLE || local->codec_id != A2DP_VENDOR_CODEC_ID_SAMPLE) {
//        return false;
//    }
    LHDC_LOG_W("[AVDTP] bt_a2dp_negotiate_vendor_codec()\r\n", 0);

    result->vendor_id = local->vendor_id;
    result->codec_id = local->codec_id;

    uint8_t freq = (local->value[0] & remote->value[0]) & A2DP_VENDOR_SAMPLE_FREQ_MASK;
    uint8_t resolution = (local->value[1] & remote->value[1]) & A2DP_VENDOR_SAMPLE_RESOLUTION_MASK;
    uint8_t Maxbitrate = remote->value[1] & A2DP_VENDOR_SAMPLE_MAXBITRATE_MASK;
	uint8_t Minbitrate = remote->value[1] & A2DP_VENDOR_SAMPLE_MINBITRATE_MASK;
    //uint8_t LL_MODE = (vendor->value[3] & A2DP_VENDOR_SAMPLE_LOW_LATENCY_MODE); // Current value smaller than 3
	
	uint8_t local_max_br_idx = get_max_bitrate_idx(local->value[1] & A2DP_VENDOR_SAMPLE_MAXBITRATE_MASK); 
	uint8_t remote_max_br_idx = get_max_bitrate_idx(remote->value[1] & A2DP_VENDOR_SAMPLE_MAXBITRATE_MASK);
	uint8_t local_min_br_idx = get_min_bitrate_idx(local->value[1] & A2DP_VENDOR_SAMPLE_MINBITRATE_MASK); 
	uint8_t remote_min_br_idx = get_min_bitrate_idx(remote->value[1] & A2DP_VENDOR_SAMPLE_MINBITRATE_MASK);	
	
	if (freq & A2DP_VENDOR_SAMPLE_FREQ_DEFAULT) {
		freq = A2DP_VENDOR_SAMPLE_FREQ_DEFAULT;
	}
    if (freq == 0)
    {
		LHDC_LOG_W("[AVDTP] negotiate freq error\r\n", 0);
		return false;
    }
	
    if (resolution & A2DP_VENDOR_SAMPLE_RESOLUTION_MODE_DEFAULT) {
        resolution = A2DP_VENDOR_SAMPLE_RESOLUTION_MODE_DEFAULT;
    }
	
    if (resolution == 0){
		LHDC_LOG_W("[AVDTP] negotiate resolution error\r\n", 0);
		return false;
    }
	
	if ((local_max_br_idx == LHDCV5_QUALITY_INVALID) || (remote_max_br_idx == LHDCV5_QUALITY_INVALID)) {
		LHDC_LOG_W("[AVDTP] negotiate max bitrate error\r\n", 0);
		return false;
	}
	
	if (local_max_br_idx == remote_max_br_idx)
		Maxbitrate = get_max_bitrate(local_max_br_idx);
	else if (local_max_br_idx < remote_max_br_idx)
		Maxbitrate = get_max_bitrate(local_max_br_idx);
	else
		Maxbitrate = get_max_bitrate(remote_max_br_idx);
	
	if ((local_min_br_idx == LHDCV5_QUALITY_INVALID) || (remote_min_br_idx == LHDCV5_QUALITY_INVALID)){
		LHDC_LOG_W("[AVDTP] negotiate min bitrate error\r\n", 0);
		return false;
	}
	
	if (local_min_br_idx == remote_min_br_idx)
		Minbitrate = get_min_bitrate(local_min_br_idx);
	else if (local_min_br_idx < remote_min_br_idx)
		Minbitrate = get_min_bitrate(remote_min_br_idx);
	else
		Minbitrate = get_min_bitrate(local_min_br_idx);

    result->value[0] = freq;
    result->value[1] = Minbitrate | Maxbitrate | resolution;
    result->value[2] = A2DP_LHDCV5_FRAME_5MS | A2DP_LHDCV5_VERSION_NUM;
    result->value[4] = local->value[4] & remote->value[4];

    LHDC_LOG_W("[AVDTP] value[0]: 0x%X; value[1]: 0x%X; value[2]: 0x%X\r\n", 3, result->value[0], result->value[1], result->value[2]);

    return true;
}