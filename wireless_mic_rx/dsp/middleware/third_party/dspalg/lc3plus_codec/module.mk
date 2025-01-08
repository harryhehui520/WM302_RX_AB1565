# Copyright Statement:
#
# (C) 2017  Airoha Technology Corp. All rights reserved.
#
# This software/firmware and related documentation ("Airoha Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
# Without the prior written permission of Airoha and/or its licensors,
# any reproduction, modification, use or disclosure of Airoha Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.
# You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
# if you have agreed to and been bound by the applicable license agreement with
# Airoha ("License Agreement") and been granted explicit permission to do so within
# the License Agreement ("Permitted User").  If you are not a Permitted User,
# please cease any access or use of Airoha Software immediately.
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
# ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
# WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
# AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
#

LC3PLUS_CODEC_PATH = middleware/third_party/dspalg/lc3plus_codec

ifeq ($(AIR_BT_LE_LC3PLUS_ENABLE), y)
    C_SRC += $(LC3PLUS_CODEC_PATH)/src/lc3plus_dec_interface.c
    C_SRC += $(LC3PLUS_CODEC_PATH)/src/lc3plus_enc_interface.c
ifneq ($(AIR_BT_LE_LC3PLUS_USE_PIC), y)
ifeq ($(AIR_BT_LE_LC3PLUS_USE_ALL_MODE), y)
    LIBS += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/all/liblc3plus_codec.a
else
    LIBS += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/liblc3plus_codec.a
endif
else
ifeq ($(AIR_BT_LE_LC3PLUS_USE_ALL_MODE), y)
    PIC   += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/all/pisplit/pisplit_lc3plus_codec_all.o
else
    PIC   += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/pisplit/codec_lib/pisplit_lc3plusi_codec.o
    PIC   += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/pisplit/fft2p5ms/pisplit_lc3plusi_fft2p5ms.o
    PIC   += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/pisplit/fft5ms/pisplit_lc3plusi_fft5ms.o
    PIC   += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/pisplit/fft10ms/pisplit_lc3plusi_fft10ms.o
    LIBS  += $(strip $(LIBDIR3))/lc3plus_codec/$(IC_CONFIG)/pisplit/liblc3plusi_codec.a
endif
    C_SRC += $(LC3PLUS_CODEC_PATH)/portable/lc3plus_codec_portable.c
endif
endif

ifeq ($(AIR_BT_LE_LC3PLUS_ENABLE), y)
    INC += $(LC3PLUS_CODEC_PATH)/inc
    INC += $(LC3PLUS_CODEC_PATH)/portable
endif
