
###################################################
CELT_DEC_PATH = middleware/third_party/dspalg/celt_decoder
ifeq ($(MTK_BT_A2DP_AIRO_CELT_ENABLE), y)
C_SRC += $(CELT_DEC_PATH)/src/celt_dec_interface.c
endif
ifeq ($(AIR_CELT_DEC_V2_ENABLE), y)
C_SRC += $(CELT_DEC_PATH)/src/celt_dec_interface_v2.c
endif
ifneq ($(MTK_BT_CELT_USE_PIC), y)
    LIBS += $(strip $(LIBDIR3))/celt_decoder/$(IC_CONFIG)/libcelt_codec_1565.a
else
    PIC   += $(strip $(LIBDIR3))/celt_decoder/$(IC_CONFIG)/pisplit/pisplit_celt_codec_1565.o
    ifeq ($(AIR_CELT_MULTI_VERSIONS_SUPPORT), y)
    PIC   += $(strip $(LIBDIR3))/celt_decoder/$(IC_CONFIG)/pisplit_celt_codec_21073101_1565/pisplit_celt_codec_21073101_1565.o
    endif
    C_SRC += $(CELT_DEC_PATH)/portable/celt_portable.c
endif

###################################################
# include path

INC += $(CELT_DEC_PATH)/inc
ifeq ($(MTK_BT_CELT_USE_PIC), y)
    INC += $(CELT_DEC_PATH)/portable
endif
