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

/* Airoha restricted information. */

#ifndef __IAP2_LOG_H__
#define __IAP2_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "syslog.h"

extern const char IAP2_001[];
extern const char IAP2_002[];
extern const char IAP2_003[];
extern const char IAP2_004[];
extern const char IAP2_005[];
extern const char IAP2_006[];
extern const char IAP2_007[];
extern const char IAP2_008[];
extern const char IAP2_009[];
extern const char IAP2_010[];
extern const char IAP2_011[];
extern const char IAP2_012[];
extern const char IAP2_013[];
extern const char IAP2_SPP_001[];
extern const char IAP2_SPP_002[];
extern const char IAP2_SPP_003[];
extern const char IAP2_SPP_004[];
extern const char IAP2_SPP_005[];
extern const char IAP2_SPP_006[];
extern const char IAP2_SPP_007[];
extern const char IAP2_SPP_008[];
extern const char IAP2_SPP_009[];
extern const char IAP2_SPP_010[];
extern const char IAP2_SPP_011[];
extern const char IAP2_SPP_012[];
extern const char IAP2_SPP_013[];
extern const char IAP2_TASK_001[];
extern const char IAP2_TASK_002[];
extern const char IAP2_TASK_003[];
extern const char IAP2_TASK_004[];
extern const char IAP2_TASK_005[];
extern const char IAP2_TASK_006[];
extern const char IAP2_TASK_007[];
extern const char IAP2_UTIL_001[];
extern const char IAP2_UTIL_002[];
extern const char IAP2_UTIL_003[];
extern const char IAP2_UTIL_004[];
extern const char IAP2_UTIL_005[];
extern const char IAP2_UTIL_006[];
extern const char IAP2_UTIL_007[];
extern const char IAP2_UTIL_008[];
extern const char IAP2_UTIL_009[];
extern const char IAP2_UTIL_010[];
extern const char IAP2_UTIL_011[];
extern const char IAP2_UTIL_012[];
extern const char IAP2_UTIL_013[];
extern const char IAP2_UTIL_014[];
extern const char IAP2_UTIL_015[];
extern const char IAP2_UTIL_016[];
extern const char IAP2_UTIL_017[];
extern const char IAP2_UTIL_018[];
extern const char IAP2_UTIL_019[];
extern const char IAP2_UTIL_020[];
extern const char IAP2_UTIL_021[];
extern const char IAP2_UTIL_022[];
extern const char IAP2_UTIL_023[];
extern const char IAP2_UTIL_024[];
extern const char IAP2_SPEC_001[];
extern const char IAP2_SPEC_002[];
extern const char IAP2_SPEC_003[];
extern const char IAP2_SPEC_004[];
extern const char IAP2_SPEC_005[];
extern const char IAP2_SPEC_006[];
extern const char IAP2_SPEC_007[];
extern const char IAP2_SPEC_008[];
extern const char IAP2_SPEC_009[];
extern const char IAP2_SPEC_010[];
extern const char IAP2_SPEC_011[];
extern const char IAP2_SPEC_012[];
extern const char IAP2_SPEC_013[];
extern const char IAP2_SPEC_014[];
extern const char IAP2_SPEC_015[];
extern const char IAP2_SPEC_016[];
extern const char IAP2_SPEC_017[];
extern const char IAP2_SPEC_018[];
extern const char IAP2_SPEC_019[];
extern const char IAP2_SPEC_020[];
extern const char IAP2_SPEC_021[];
extern const char IAP2_SPEC_022[];
extern const char IAP2_SPEC_023[];
extern const char IAP2_SPEC_024[];
extern const char IAP2_SPEC_025[];
extern const char IAP2_SPEC_026[];
extern const char IAP2_SPEC_027[];
extern const char IAP2_SPEC_028[];
extern const char IAP2_SPEC_029[];
extern const char IAP2_SPEC_030[];
extern const char IAP2_SPEC_031[];
extern const char IAP2_SPEC_032[];
extern const char IAP2_SPEC_033[];
extern const char IAP2_SPEC_034[];
extern const char IAP2_SPEC_035[];
extern const char IAP2_SPEC_036[];
extern const char IAP2_SPEC_037[];
extern const char IAP2_SPEC_038[];
extern const char IAP2_SPEC_039[];
extern const char IAP2_SPEC_040[];
extern const char IAP2_SPEC_041[];
extern const char IAP2_SPEC_042[];
extern const char IAP2_SPEC_043[];
extern const char IAP2_SPEC_044[];
extern const char IAP2_SPEC_045[];
extern const char IAP2_SPEC_046[];
extern const char IAP2_SPEC_047[];
extern const char IAP2_SPEC_048[];
extern const char IAP2_SPEC_049[];
extern const char IAP2_SPEC_050[];
extern const char IAP2_SPEC_051[];
extern const char IAP2_SPEC_052[];
extern const char IAP2_SPEC_053[];
extern const char IAP2_SPEC_054[];
extern const char IAP2_SPEC_055[];
extern const char IAP2_SPEC_056[];
extern const char IAP2_SPEC_057[];
extern const char IAP2_RHO_001[];
extern const char IAP2_RHO_002[];
extern const char IAP2_RHO_003[];
extern const char IAP2_RHO_004[];
extern const char IAP2_RHO_005[];
extern const char IAP2_RHO_006[];
extern const char IAP2_RHO_007[];
extern const char IAP2_RHO_008[];
extern const char IAP2_RHO_009[];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IAP2_LOG_H__ */

