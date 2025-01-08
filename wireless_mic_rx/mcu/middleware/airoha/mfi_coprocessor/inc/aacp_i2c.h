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


#ifndef __AACP_I2C_H__
#define __AACP_I2C_H__


#include <aacp_types.h>

#if !defined(PCFG_OS) || (PCFG_OS != 2)
#include <base/cerr.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern const char MFI_CP_LOG_IIC_DMA_ISR_CB[];
extern const char MFI_CP_LOG_IIC_START_INIT[];
extern const char MFI_CP_LOG_IIC_INIT[];
extern const char MFI_CP_LOG_IIC_INIT_SUCCESS[];
extern const char MFI_CP_LOG_IIC_INIT_FAILED[];
extern const char MFI_CP_LOG_IIC_WAKE_FAILD[];
extern const char MFI_CP_LOG_IIC_READ_OP[];
extern const char MFI_CP_LOG_IIC_SEND_DMA_FAILED[];
extern const char MFI_CP_LOG_IIC_READ_DMA_FAILED[];
extern const char MFI_CP_LOG_IIC_READ_LEN[];
extern const char MFI_CP_LOG_IIC_WRITE_OP[];

int aacp_i2c_reset(void);


#if !defined(PCFG_OS) || (PCFG_OS != 2)
/**
 * AACP constructor.
 *
 * @param o The object instance.
 * @return  An error handling object.
 */
exc_t aacp_i2c_init(aacp_t *o);
#endif


int aacp_i2c_wake(void);


int aacp_i2c_read(__u8 addr, __u8 *buf, unsigned int len);


int aacp_i2c_write(__u8 addr, const __u8 *buf, unsigned int len);


void os_delay_us(unsigned int us);


#ifdef __cplusplus
}
#endif

#endif /* __AACP_I2C_H__ */
