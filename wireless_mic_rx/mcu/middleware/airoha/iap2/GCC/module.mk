iAP2_SRC_PATH = $(MIDDLEWARE_PROPRIETARY)/iap2/src

ifeq ($(MTK_IAP2_PROFILE_ENABLE),y)
C_FILES  += $(iAP2_SRC_PATH)/iAP2_spp.c \
            $(iAP2_SRC_PATH)/iAP2_sdp.c \
            $(iAP2_SRC_PATH)/iAP2.c \
            $(iAP2_SRC_PATH)/iAP2_transports.c \
            $(iAP2_SRC_PATH)/iAP2_task.c \
            $(iAP2_SRC_PATH)/iAP2_utils.c \
            $(iAP2_SRC_PATH)/iAP2_log.c \
            $(iAP2_SRC_PATH)/iAP2_rho.c
ifeq ($(AIR_USB_MFI_ENABLE),y)
C_FILES  += $(iAP2_SRC_PATH)/iAP2_usb.c
endif
endif
#################################################################################
#include path
#################################################################################
CFLAGS 	+= -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/iap2/inc
CFLAGS 	+= -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/bluetooth/inc
CFLAGS	+= -I$(SOURCE_DIR)/kernel/rtos/$(IC_CONFIG)/FreeRTOS/Source/include 
CFLAGS  += -I$(SOURCE_DIR)/kernel/rtos/$(IC_CONFIG)/FreeRTOS/Source/portable/GCC/ARM_CM4F
CFLAGS  += -I$(SOURCE_DIR)/driver/chip/mt7687/inc
CFLAGS  += -I$(SOURCE_DIR)/driver/chip/inc
CFLAGS  += -I$(SOURCE_DIR)/kernel/service/inc 
CFLAGS  += -I$(SOURCE_DIR)/kernel/service/syslog/inc
CFLAGS  += -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/bt_callback_manager/inc
CFLAGS  += -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/mfi_coprocessor/inc
CFLAGS  += -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/bt_role_handover/inc

ifeq ($(AIR_USB_MFI_ENABLE),y)
CFLAGS  += -I$(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/usb/inc
endif

ifeq ($(MTK_IAP2_PROFILE_ENABLE),y)
LIBS += $(SOURCE_DIR)/prebuilt/$(MIDDLEWARE_PROPRIETARY)/iap2/$(IC_CONFIG)/lib_iap2.a
endif

