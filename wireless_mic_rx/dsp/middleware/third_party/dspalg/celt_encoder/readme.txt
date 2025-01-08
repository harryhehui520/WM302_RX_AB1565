celt encoder module usage guide

Brief:          This module is the celt encoder implementation.

Usage:          GCC:  For celt encoder, include the module with
                      1) Add the following module.mk for libs and source file:
                         include $(ROOTDIR)/middleware/third_party/dspalg/celt_encoder/module.mk
                      2) module.mk provide different options to enable or disable according profiles, please configure these options on specified GCC/feature.mk:
                         AIR_CELT_ENC_ENABLE
                      3) Add the module.mk path to the [project]/XT-XCC/Makefile
                         # audio middleware files
                         include $(ROOTDIR)/middleware/third_party/dspalg/celt_encoder/module.mk
                         in your XT-XCC project Makefile.

Dependency:     None.

Notice:         None.

Relative doc:   None.

Example project:None.
