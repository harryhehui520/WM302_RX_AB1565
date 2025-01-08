
###################################################
CELT_ENC_PATH = middleware/third_party/dspalg/celt_encoder
ifeq ($(AIR_CELT_ENC_ENABLE), y)
C_SRC += $(CELT_ENC_PATH)/src/celt_enc_interface.c
endif
ifeq ($(AIR_CELT_ENC_V2_ENABLE), y)
C_SRC += $(CELT_ENC_PATH)/src/celt_enc_interface_v2.c
endif
ifneq ($(MTK_BT_CELT_USE_PIC), y)
    LIBS += $(strip $(LIBDIR3))/celt_decoder/$(IC_CONFIG)/libcelt_codec_1565.a
endif

###################################################
# include path

INC += $(CELT_ENC_PATH)/inc
