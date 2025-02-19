/* Copyright Statement:
 *
 * (C) 2022  Airoha Technology Corp. All rights reserved.
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

#include <string.h>
#include <stdbool.h>
#include <xtensa/tie/xt_hifi2.h>
#include <xtensa/hal.h>
#include "assert.h"
#include "xt_library_loader.h"
#include "preloader_pisplit.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "dsp_feature_interface.h"

#ifdef AIR_AUDIO_ULD_DECODE_USE_PIC_ENABLE

#include "uld_decode_portable.h"

static void uld_decode_default_function_parameter(void);

static SemaphoreHandle_t g_uld_decode_load_lib_xSemaphore = NULL;
static uint32_t g_uld_decode_lib_loaded_counter = 0;
static preloader_pisplit_handle_t g_uld_decode_pisplit_library_handle = NULL;

void *g_uld_decode_export_parameters[] = {
    uld_decode_default_function_parameter,
    uld_decode_default_function_parameter,
    uld_decode_default_function_parameter,
    uld_decode_default_function_parameter,
    uld_decode_default_function_parameter,
};

/* Add for UT of PIC */
#if !PIC_LOGPRINT
#ifndef UNUSED
#define UNUSED(p) ((void)(p))
#endif
extern uint32_t fake_printf(const char *format, ...);
#endif

#if PIC_LOGPRINT
void *g_uld_decode_import_parameters[3] = {
    printf,
    memcpy,
    memset
};
#else
void *g_uld_decode_import_parameters[3] = {
    fake_printf,
    memcpy,
    memset
};
#endif

static void uld_decode_default_function_parameter(void)
{
    DSP_MW_LOG_E("[uld] decode library not load or had been unload!!!", 0);
    assert(0);
}

static void uld_decode_load_library_callback(preloader_pisplit_handle_t handle)
{
    uint32_t i;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t *p_export_parameters;

    p_export_parameters = preloader_pisplit_get_export_parameter(handle, g_uld_decode_import_parameters);
    if (p_export_parameters == NULL) {
        DSP_MW_LOG_E("[uld] preloader_pisplit_get_export_parameter() fail", 0);
        assert(0);
        return;
    }

    for (i = 0; i < (sizeof(g_uld_decode_export_parameters)/sizeof(void *)); i++) {
        g_uld_decode_export_parameters[i] = (void *)p_export_parameters[i];
    }

    xSemaphoreGiveFromISR(g_uld_decode_load_lib_xSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

uint32_t uld_decode_library_load(void *code_address, void *data_address, uint32_t *dram_pic_usage)
{
    uint32_t i, irq_mask;
    preloader_pisplit_error_handling_t error_handling;

#ifdef AIR_DSP_MEMORY_REGION_ENABLE
        UNUSED(code_address);
        UNUSED(data_address);
        UNUSED(dram_pic_usage);
#else
        UNUSED(code_address);
        UNUSED(data_address);
        UNUSED(dram_pic_usage);
#endif

    hal_nvic_save_and_set_interrupt_mask(&irq_mask);
    g_uld_decode_lib_loaded_counter++;
    if (g_uld_decode_lib_loaded_counter != 1) {
        hal_nvic_restore_interrupt_mask(irq_mask);
        DSP_MW_LOG_I("[uld] uld_decode_library_load() has been called", 0);
        return g_uld_decode_lib_loaded_counter;
    }
    hal_nvic_restore_interrupt_mask(irq_mask);

    DSP_MW_LOG_I("[uld] uld_decode_library_load() begin", 0);

    if (g_uld_decode_load_lib_xSemaphore == NULL) {
        g_uld_decode_load_lib_xSemaphore = xSemaphoreCreateBinary();
        assert(g_uld_decode_load_lib_xSemaphore != NULL);
    }
    error_handling = preloader_pisplit_get_handle(&g_uld_decode_pisplit_library_handle, &pisplit_uld_dec, uld_decode_load_library_callback);
    if (error_handling != PRELOADER_PISPLIT_XTLIB_NO_ERR) {
        DSP_MW_LOG_E("[uld] preloader_pisplit_get_handle() fail %d", 1, error_handling);
        assert(0);
    }
    error_handling = preloader_pisplit_load(g_uld_decode_pisplit_library_handle, PRELOADER_I_HIGH_PERFORMANCE, PRELOADER_D_HIGH_PERFORMANCE);
    if (error_handling != PRELOADER_PISPLIT_XTLIB_NO_ERR) {
        DSP_MW_LOG_E("[uld] preloader_pisplit_load() fail %d", 1, error_handling);
        preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_I_HIGH_PERFORMANCE);
        preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_I_LOW_PERFORMANCE);
        preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_D_HIGH_PERFORMANCE);
        preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_D_LOW_PERFORMANCE);
        assert(0);
    }
    if (xSemaphoreTake( g_uld_decode_load_lib_xSemaphore, portMAX_DELAY) != pdTRUE) {
        assert(0);
    }
    vSemaphoreDelete(g_uld_decode_load_lib_xSemaphore);
    g_uld_decode_load_lib_xSemaphore = NULL;
    for (i = 0; i < (sizeof(g_uld_decode_export_parameters)/sizeof(void *)); i++) {
        DSP_MW_LOG_I("[uld] g_uld_decode_export_parameters[%d] = 0x%08x", 2, i, g_uld_decode_export_parameters[i]);
    }

    DSP_MW_LOG_I("[uld] uld_decode_library_load() end", 0);

    return g_uld_decode_lib_loaded_counter;
}

uint32_t uld_decode_library_unload(void)
{
    uint32_t i;
    preloader_pisplit_error_handling_t error_handling;

    if (g_uld_decode_lib_loaded_counter != 1) {
        DSP_MW_LOG_W("[uld] uld_decode_library_load() has been called before", 0);
        g_uld_decode_lib_loaded_counter--;
        return g_uld_decode_lib_loaded_counter;
    }

    DSP_MW_LOG_I("[uld] uld_decode_library_unload() begin", 0);

    error_handling = preloader_pisplit_unload(g_uld_decode_pisplit_library_handle);
    if (PRELOADER_PISPLIT_XTLIB_NO_ERR != error_handling) {
        DSP_MW_LOG_E("[uld] preloader_pisplit_unload() fail %d", 1, error_handling);
        assert(0);
    }
    error_handling = preloader_pisplit_release_handle(g_uld_decode_pisplit_library_handle);
    if (PRELOADER_PISPLIT_XTLIB_NO_ERR != error_handling) {
        DSP_MW_LOG_E("[uld] preloader_pisplit_release_handle() fail %d", 1, error_handling);
        assert(0);
    }
    for (i = 0; i < (sizeof(g_uld_decode_export_parameters)/sizeof(void *)); i++) {
        g_uld_decode_export_parameters[i] = uld_decode_default_function_parameter;
    }
    g_uld_decode_pisplit_library_handle = NULL;

    g_uld_decode_lib_loaded_counter = 0;

    DSP_MW_LOG_I("[uld] uld_decode_library_unload() end", 0);

    return g_uld_decode_lib_loaded_counter;
}

#endif

