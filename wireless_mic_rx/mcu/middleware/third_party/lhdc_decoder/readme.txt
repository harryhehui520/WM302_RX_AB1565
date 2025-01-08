LHDC decoder module usage guide

Brief:           This module is for middleware third party LHDC decoder implementation.
Usage:           GCC:  For LHDC decoder, add the following module.mk for libs and source file:
                       include $(SOURCE_DIR))/middleware/third_party/lhdc_decoder/module.mk
Dependency:      To enable it, please define AIR_BT_A2DP_LHDC_ENABLE to "y".
Notice:          N/A
Relative doc:    N/A
Example project: earbuds_ref_design
