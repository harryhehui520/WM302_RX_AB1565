LC3 module usage guide

Brief:          This module is the LC3plus codec implementation for audio. It provides support for LC3plus encode and decode.

Usage:          XT-XCC:  For LC3plus, make sure to include the following:
                      1) Add the following module.mk for libs and source file:
                         include $(SOURCE_DIR)/middleware/third_party/dspalg/lc3plus_codec/module.mk
                      2) module.mk provides different options to enable or disable according to the profiles.
                         Please configure the related options on the specified XT-XCC/feature.mk.
                         AIR_BT_LE_LC3PLUS_ENABLE
                         AIR_BT_LE_LC3PLUS_USE_PIC
                      3) Add the header file path:
                         CFLAGS += -I$(SOURCE_DIR)/middleware/third_party/dspalg/lc3plus_codec/inc
                      4) Add CODEC_ENCODER_LC3PLUS/CODEC_DECODER_LC3PLUS into the feature table in dsp_sdk.c to apply LC3plus codec in the specified scenario, like AudioFeatureList_BLE_Call_UL[].

Dependency:     None.

Notice:         1) AIR_BT_LE_LC3PLUS_ENABLE must be set as "y" on the specified XT-XCC/feature.mk.

Relative doc:   None

Example project: None
