CELT decoder prebuilt module usage guide

Brief:          This module contains the third party library for CELT decoder.

Usage:          GCC:  For CELT decoder prebuilt module, make sure to include the following:
                      1) Add the following module.mk for libs and source file:
                         include $(ROOTDIR)/middleware/third_party/dspalg/celt_decoder/module.mk
                      2) module.mk provides different options to enable or disable according to the profiles.
                         Please configure the related options on the specified XT-XCC/feature.mk.
                         MTK_BT_A2DP_AIRO_CELT_ENABLE = y

Dependency:     CELT decoder prebuilt module is only effective when CELT decoder module also exists.

Notice:         1) MTK_BT_A2DP_AIRO_CELT_ENABLE must be set as "y" on the specified DSP side XT-XCC/feature.mk.

Relative doc:   None.

Example project:None.