LHDC decoder module usage guide

Brief:          This module is the LHDC decoder implementation.

Usage:          XT-XCC:  For LHDC decoder, make sure to include the following:
                      1) Add the following module.mk for libs and source file:
                         include $(SOURCE_DIR)/middleware/third_party/dspalg/lhdc_decoder/module.mk
                      2) module.mk provides different options to enable or disable according to the profiles.
                         Please configure the related options on the specified XT-XCC/feature.mk.
                         AIR_BT_A2DP_LHDC_ENABLE
                      3) Add the header file path:
                         CFLAGS += -I$(SOURCE_DIR)/middleware/third_party/dspalg/lhdc_decoder/inc
                      4) Add CODEC_DECODER_VENDOR_2 into the feature table in dsp_sdk.c to apply LHDC decoder in the specified scenario, e.g., stream_feature_list_a2dp[].

Dependency:      None
Notice:          None
Relative doc:    None
Example project: None
