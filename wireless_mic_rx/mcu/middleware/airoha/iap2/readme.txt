iAP2 module usage guide

Brief:          This module is the Apple iPod Accessory Protocol (iAP2) porting layer implementation.

Usage:          GCC:  Include the module with the following module.mk for libs and source file:
                      include $(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/iap2/GCC/module.mk
                      include $(SOURCE_DIR)/$(MIDDLEWARE_PROPRIETARY)/mfi_coprocessor/module.mk

Dependency:     This module has the dependency with Bluetooth. Please include Bluetooth module.mk in your project.

Notice:         None.

Relative doc:   None.

Example project:Please find the earbuds_ref_design project under the project folder.
