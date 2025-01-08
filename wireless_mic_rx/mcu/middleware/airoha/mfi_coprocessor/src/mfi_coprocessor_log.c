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

#include "mfi_coprocessor_log.h"

#include "syslog.h"

log_create_module(MFI_COMMON, PRINT_LEVEL_INFO);
log_create_module(MFI_IIC, PRINT_LEVEL_INFO);

/* CP means coprocessor */

ATTR_LOG_STRING_LIB MFI_CP_LOG_READ_CERT_ERR_CODE[]     = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] reg_addr:0x%x, err: 0x%x";
ATTR_LOG_STRING_LIB MFI_CP_LOG_READ_CERT_FAILED[]       = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] MFI read cert data failed.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_READ_CERT_LEN[]          = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] MFI cert data len = %d.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_NOOP_CMD[]               = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] conttrol command: noop";
ATTR_LOG_STRING_LIB MFI_CP_LOG_NOOP_RESULT[]            = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] noop result: %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_ERROR_REG[]              = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] error code register: %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_CTRL_STATUS_REG[]        = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] control and status register:%d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_CHALLENGE_DATA_LEN[]     = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] challenge data len:%d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_DIGEST_WRITE_RST[]       = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] write challenge data ret:%d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_GENERATION_START[]       = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] start generate process.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_CTRL_STATUS_OP_RST[]     = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] control and status register read or write bytes:%d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_CHALLENGE_RESP_LEN[]     = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] challenge response len: %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_CHALLENGE_RESP_RST[]     = LOG_INFO_PREFIX(MFI_COMMON)"[MFI_COMMON] challenge response final len: %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_DMA_ISR_CB[]         = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] dma isr address = %d, event = %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_START_INIT[]         = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] mfi iic start init process.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_INIT_SUCCESS[]       = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] mfi iic init successed.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_INIT_FAILED[]        = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] mfi iic init failed.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_INIT[]               = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] mfi iic init: i2c_scl_pin=0x%x, i2c_sda_pin=0x%x, i2c_scl_pinmux=0x%x, i2c_sda_pinmux=0x%x.";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_WAKE_FAILD[]         = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] aacp wake send dma fail, err code: %d. %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_READ_OP[]            = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] iic read start, len: %d, addr: 0x%x";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_SEND_DMA_FAILED[]    = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] iic send dma failed, addr = 0x%x, err: %d, callback = %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_READ_DMA_FAILED[]    = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] iic read dma failed, addr = 0x%x, err: %d, callback = %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_READ_LEN[]           = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] iic read data bytes: %d";
ATTR_LOG_STRING_LIB MFI_CP_LOG_IIC_WRITE_OP[]           = LOG_INFO_PREFIX(MFI_IIC)"[MFI_IIC] iic write start, len: %d, addr: 0x%x";

void MFI_LOG_PRINT(mfi_log_type_t type, mfi_log_level_t printLevel, const char *logString, unsigned int argc, ...)
{
    print_level_t l;

    va_list ap;

    log_control_block_t *block_name = NULL;
    if (printLevel == MFI_LOG_LEVEL_INFO) {
        l = PRINT_LEVEL_INFO;
    } else {
        l = PRINT_LEVEL_ERROR;
    }
    switch (type) {
        case MFI_LOG_TYPE_COMMON:
            block_name = &log_control_block_MFI_COMMON;
            break;

        case MFI_LOG_TYPE_IIC:
            block_name = &log_control_block_MFI_IIC;
            break;
    }

    va_start(ap, argc);
    log_print_msgid(block_name, l, logString, argc, ap);
    va_end(ap);
}
