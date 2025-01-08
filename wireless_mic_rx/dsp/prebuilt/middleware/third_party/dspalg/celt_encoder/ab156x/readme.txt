CELT encoder prebuilt module usage guide

Brief:          This module contains the third party library for CELT encoder.

Usage:          GCC:  For CELT encoder prebuilt module, make sure to include the following:
                      1) Add the following module.mk for libs and source file:
                         include $(ROOTDIR)/middleware/third_party/dspalg/celt_encoder/module.mk
                      2) module.mk provides different options to enable or disable according to the profiles.
                         Please configure the related options on the specified XT-XCC/feature.mk.
                         AIR_CELT_ENC_ENABLE = y

Dependency:     CELT encoder prebuilt module is only effective when CELT encoder module also exists.

Notice:         1) AIR_CELT_ENC_ENABLE must be set as "y" on the specified DSP side XT-XCC/feature.mk.

Relative doc:   None.

Example project:None.