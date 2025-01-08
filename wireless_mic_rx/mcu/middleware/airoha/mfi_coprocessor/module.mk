# Copyright Statement:
#
# (C) 2019  Airoha Technology Corp. All rights reserved.
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
# Airoha restricted information

ifeq (1,$(r))
# For release package which do not contains the BT debug information
CFLAGS += -DBT_NO_DEBUG
TARGET_LIB=lib_mfi_coprocessor
else
# For debug package which contains the BT debug information
CFLAGS += -DBT_DEBUG
TARGET_LIB=lib_mfi_coprocessor
endif

MFI_LIB = lib_mfi_coprocessor.a

MFI_SOURCE = $(MIDDLEWARE_PROPRIETARY)/mfi_coprocessor/src

ifeq ($(findstring 155, $(IC_TYPE)), 155)
CFLAGS += -I$(SOURCE_DIR)/project/ab155x_evk/apps/$(PROJ_NAME)/inc/boards/$(BOARD_TYPE)/
endif

ifeq ($(findstring 156, $(IC_TYPE)), 156)
CFLAGS += -I$(SOURCE_DIR)/project/ab156x/apps/$(PROJ_NAME)/inc/boards/$(BOARD_TYPE)/
endif

ifeq ($(findstring 157, $(IC_TYPE)), 157)
CFLAGS += -I$(SOURCE_DIR)/project/ab157x/apps/$(PROJ_NAME)/inc/boards/$(BOARD_TYPE)/
endif

ifeq ($(findstring 2821, $(PROJ_PATH)), 2821)
CFLAGS += -I$(SOURCE_DIR)/project/mt2821/apps/$(PROJ_NAME)/inc/boards/$(BOARD_TYPE)/
#else
ifeq ($(findstring 2822, $(IC_TYPE)), 2822)
CFLAGS += -I$(SOURCE_DIR)/project/mt2822/apps/$(PROJ_NAME)/inc/boards/$(BOARD_TYPE)/
endif
endif

ifeq ($(findstring am255, $(IC_TYPE)), am255)
CFLAGS += -I$(SOURCE_DIR)/project/am255x_evk/apps/$(PROJ_NAME)/inc/boards/$(BOARD_TYPE)/
endif


CFLAGS 	+= -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/mfi_coprocessor/inc
C_FILES += $(MFI_SOURCE)/mfi_coprocessor_log.c
C_FILES += $(MFI_SOURCE)/mfi_gpio_config.c
C_FILES += $(MFI_SOURCE)/aacp_i2c.c

LIBS += $(SOURCE_DIR)/prebuilt/$(MIDDLEWARE_PROPRIETARY)/mfi_coprocessor/$(IC_CONFIG)/lib/$(MFI_LIB)
