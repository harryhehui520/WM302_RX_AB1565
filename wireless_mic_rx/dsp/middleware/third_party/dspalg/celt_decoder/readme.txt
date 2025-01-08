CELT decoder module usage guide

Brief:          This module is the celt decoder implementation.

Usage:          GCC:  For celt decoder, make sure to include the following:
                      1) Add the following module.mk for libs and source file:
                         include $(SOURCE_DIR)/middleware/third_party/dspalg/celt_decoder/module.mk
                      2) module.mk provides different options to enable or disable according to the profiles.
                         Please configure the related options on the specified XT-XCC/feature.mk.
                         AIR_AUDIO_VEND_CODEC_ENABLE
                      3) Add the header file path:
                         CFLAGS += -I$(SOURCE_DIR)/middleware/third_party/dspalg/celt_decoder/inc
                      4) Add CODEC_DECODER_OPUS_V2 into the feature table in dsp_sdk.c
                         to apply celt decoder in the specified scenario.

Dependency:     None.

Notice:         None.

Relative doc:   None.

Example project:None.