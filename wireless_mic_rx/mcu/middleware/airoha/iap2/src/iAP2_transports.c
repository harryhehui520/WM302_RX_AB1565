/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#ifdef MTK_IAP2_PROFILE_ENABLE

#include "iAP2_spp.h"
#include "iAP2_usb.h"
#include "iAP2_transports.h"


int32_t iap2_send_data_over_transport(uint32_t linkIndex, uint8_t *packet, uint16_t packet_size)
{
#ifdef AIR_USB_MFI_ENABLE
    if (linkIndex == IAP2_USB_LINK_INDEX) {
        return iap2_usb_send_data(linkIndex, packet, packet_size);
    }
#endif

    return (int32_t)bt_iap2_send_data(linkIndex, packet, packet_size);
}

iap2_link_info_t *iap2_get_link_info(uint32_t linkIndex)
{
#ifdef AIR_USB_MFI_ENABLE
    if (linkIndex == IAP2_USB_LINK_INDEX) {
        return iap2_usb_get_link_info(linkIndex);
    }
#endif

    return (iap2_link_info_t *)bt_iap2_get_link_info(linkIndex);

}

uint32_t iap2_get_current_linkIndex(void)
{
    uint32_t linkIndex = 0;

#ifdef AIR_USB_MFI_ENABLE
    linkIndex = iap2_usb_get_link_index();

    if (linkIndex != 0) {
        return linkIndex;
    }
#endif

    linkIndex = bt_iap2_get_link_handle();

    return linkIndex;
}

void iap2_hold_data_by_transport(uint8_t *packet)
{
#ifdef AIR_USB_MFI_ENABLE
    if (iap2_get_current_linkIndex() == IAP2_USB_LINK_INDEX) {
        iap2_usb_hold_data(packet);
        return;
    }
#endif

    bt_iap2_hold_data(packet);
}

void iap2_release_data_by_transport(uint8_t *packet)
{
#ifdef AIR_USB_MFI_ENABLE
    if (iap2_get_current_linkIndex() == IAP2_USB_LINK_INDEX) {
        iap2_usb_release_data(packet);
        return;
    }
#endif

    bt_iap2_release_data(packet);
}

#endif

