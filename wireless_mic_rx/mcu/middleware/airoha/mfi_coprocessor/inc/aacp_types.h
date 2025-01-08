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


#ifndef __AACP_TYPES_H__
#define __AACP_TYPES_H__

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif


/* AACP: Apple Authentication Coprocessor */
#define AACP_DEVICE_VERSION                   0x00
#define AACP_FIRMWARE_VERSION                 0x01
#define AACP_AUTH_PROTO_MAJOR_VERSION         0x02
#define AACP_AUTH_PROTO_MINOR_VERSION         0x03
#define AACP_DEVICE_ID                        0x04
#define AACP_ERROR_CODE                       0x05

#define AACP_AUTH_CTRL_AND_STATUS             0x10
#define AACP_CHALLENGE_RESP_DATA_LEN          0x11
#define AACP_CHALLENGE_RESP_DATA              0x12

#define AACP_CHALLENGE_DATA_LEN               0x20
#define AACP_CHALLENGE_DATA                   0x21

#define AACP_ACCESSORY_CERT_DATA_LEN          0x30
#define AACP_ACCESSORY_CERT_DATA01            0x31
#define AACP_ACCESSORY_CERT_DATA02            0x32
#define AACP_ACCESSORY_CERT_DATA03            0x33
#define AACP_ACCESSORY_CERT_DATA04            0x34
#define AACP_ACCESSORY_CERT_DATA05            0x35
#define AACP_ACCESSORY_CERT_DATA06            0x36
#define AACP_ACCESSORY_CERT_DATA07            0x37
#define AACP_ACCESSORY_CERT_DATA08            0x38
#define AACP_ACCESSORY_CERT_DATA09            0x39
#define AACP_ACCESSORY_CERT_DATA10            0x3A

#define AACP_ACCESSORY_CERT_DATA_START        AACP_ACCESSORY_CERT_DATA01
#define AACP_ACCESSORY_CERT_DATA_END          AACP_ACCESSORY_CERT_DATA10

#define AACP_SELFTEST_CTRL_AND_STATUS         0x40
/* Reserved: 0x41~0x4C */
#define AACP_SYSTEM_EVENT_COUNTER             0x4D

#define AACP_DEVICE_CERT_DATA_LEN             0x50
#define AACP_DEVICE_CERT_DATA01               0x51
#define AACP_DEVICE_CERT_DATA02               0x52
#define AACP_DEVICE_CERT_DATA03               0x53
#define AACP_DEVICE_CERT_DATA04               0x54
#define AACP_DEVICE_CERT_DATA05               0x55
#define AACP_DEVICE_CERT_DATA06               0x56
#define AACP_DEVICE_CERT_DATA07               0x57
#define AACP_DEVICE_CERT_DATA08               0x58

#define AACP_DEVICE_CERT_DATA_START           AACP_DEVICE_CERT_DATA01
#define AACP_DEVICE_CERT_DATA_END             AACP_DEVICE_CERT_DATA08

#define NO_ERROR                              0x00
#define INVALID_REG_READ                      0x01
#define INVALID_REG_WRITE                     0x02
#define INVALID_CHALLENGE_RESP_LEN            0x03
#define INVALID_CHALLENGE_LEN                 0x04
#define INVALID_CERT_LEN                      0x05
#define IPE_CHALLENGE_RESP_GEN                0x06 /* IPE: Internal Process Error during */
#define IPE_CHALLENGE_GEN                     0x07
#define IPE_CHALLENGE_RESP_VERIFICATION       0x08
#define IPE_CERT_VALIDATION                   0x09
#define INVALID_PROCESS_CTRL                  0x0A
#define PROESS_CTRL_OUT_OF_SEQ                0x0B
/* Reserved: 0x0C~0xFF */

#define CHALLENGE_RESP_DATA_LEN_DEFAULT       128
#define CHALLENGE_DATA_LEN_DEFAULT            20
#define ACCESSORY_CERT_DATA_LEN_MAX           1280

/* CHALLENGE_DATA_LEN: 2 bytes, default: 20 */
#define CHALLENGE_DATA_LEN_MAX                256

/* CHALLENGE_RESPONSE_DATA_LEN: 2 bytes, default:128 */
#define CHALLENGE_RESPONSE_DATA_LEN_MAX       256

#define AACP_AUTH_CTRL_NOOP_0                 0
#define AACP_AUTH_CTRL_CHALLENGE_RESP         1
#define AACP_AUTH_CTRL_CHALLENGE_GEN          2
#define AACP_AUTH_CTRL_CHALLENGE_RESP_VERIFY  3
#define AACP_AUTH_CTRL_CERT_VALID             4
#define AACP_AUTH_CTRL_NOOP_5                 5
#define AACP_AUTH_CTRL_RESV6                  6
#define AACP_AUTH_CTRL_RESV7                  7

#define AACP_AUTH_PROC_RESULT_NP                                (0<<4)
#define AACP_AUTH_PROC_RESULT_CHALLENGE_RESP_GEN_OK             (1<<4)
#define AACP_AUTH_PROC_RESULT_CHALLENGE_GEN_OK                  (2<<4)
#define AACP_AUTH_PROC_RESULT_DEV_CHALLENGE_RESP_VERIFY_OK      (3<<4)
#define AACP_AUTH_PROC_RESULT_DEV_CERT_VALID_OK                 (4<<4)

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef AACP_ADDR
/* apple accessory coprocessor address */
//#define AACP_ADDR                            (0x22)

#define AACP_ADDR                            (0x20)
#endif

#define AACP_RESET_PIN_DEFAULT               9

/**
 * @brief the aacp object
 */
typedef struct _aacp {
    int     field; ///<  ...description for field1
} aacp_t;

/**
 * Linus Torvalds does not like uint8_t and prefers __u8.
 * Defines __u8 here for non-Linux platform to achieve cross platform.
 */
#ifndef __KERNEL__
typedef uint8_t     __u8;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AACP_TYPES_H__ */
