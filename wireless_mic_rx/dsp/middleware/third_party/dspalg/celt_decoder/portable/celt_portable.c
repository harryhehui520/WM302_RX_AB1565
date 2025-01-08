/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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
#include <xtensa/tie/xt_hifi2.h>
#include <xtensa/hal.h>
#include "assert.h"

#include "xt_library_loader.h"
#include "preloader_pisplit.h"
#include "celt_portable.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "dsp_feature_interface.h"


#define CELT_CODEC_MIN_COMPATIBLE_VERSION 0x22041502
#define CELT_CODEC_LATEST_VERSION 0x22051601

/***********************************************************************/
static SemaphoreHandle_t celt_load_lib_xSemaphore = NULL;
static uint32_t celt_codec_version = CELT_CODEC_LATEST_VERSION;

/***********************************************************************/


void celt_default_function_parameter()
{
    DSP_MW_LOG_I("function point is NULL!!! celt library not load or had been unload!!!", 0);
    AUDIO_ASSERT(0);
}


void *celt_export_parameters[7]     = {celt_default_function_parameter,
                                       celt_default_function_parameter,
                                       celt_default_function_parameter,
                                       celt_default_function_parameter,
                                       celt_default_function_parameter,
                                       celt_default_function_parameter,
                                       celt_default_function_parameter};
#if PIC_LOGPRINT
void *celt_import_parameters[1] = {printf};//
#else
void *celt_import_parameters[1] = {fake_printf};//
#endif





static preloader_pisplit_handle_t p_celt_pisplit_library_handle = NULL;
static uint32_t celt_lib_loaded_counter = 0;

uint32_t stream_codec_celt_get_version(void)
{
    return celt_codec_version;
}

uint32_t stream_codec_celt_set_version(uint32_t version)
{
    celt_codec_version = version;
    return 0;
}

xtlib_packaged_library *celt_library_get_by_version(uint32_t version)
{
    xtlib_packaged_library *library;

    if (version >= CELT_CODEC_MIN_COMPATIBLE_VERSION)
    {
        library = &pisplit_celt_codec_1565;
    }
#ifdef AIR_CELT_MULTI_VERSIONS_SUPPORT
    else if (version == 0x21073101)
    {
        library = &pisplit_celt_codec_21073101_1565;
    }
#endif /* AIR_CELT_MULTI_VERSIONS_SUPPORT */
    else
    {
        library = &pisplit_celt_codec_1565;
    }

    return library;
}

void celt_load_library_callback(preloader_pisplit_handle_t handle)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t *p_export_parameters;
    p_export_parameters = preloader_pisplit_get_export_parameter(handle,celt_import_parameters);

    if(p_export_parameters == NULL)
    {
       DSP_MW_LOG_I("p_export_parameters is NULL, please check!!!", 0);
    }
    else
    {
        celt_export_parameters[0] = (void *)p_export_parameters[0];
        celt_export_parameters[1] = (void *)p_export_parameters[1];
        celt_export_parameters[2] = (void *)p_export_parameters[2];
        celt_export_parameters[3] = (void *)p_export_parameters[3];
        celt_export_parameters[4] = (void *)p_export_parameters[4];
        celt_export_parameters[5] = (void *)p_export_parameters[5];
        celt_export_parameters[6] = (void *)p_export_parameters[6];

        xSemaphoreGiveFromISR( celt_load_lib_xSemaphore, &xHigherPriorityTaskWoken );
    }
}

uint32_t celt_library_load(void *code_address, void *data_address, uint32_t *dram_pic_usage)
{
    if (celt_load_lib_xSemaphore == NULL)
    {
        celt_load_lib_xSemaphore = xSemaphoreCreateBinary();

        if( celt_load_lib_xSemaphore == NULL )
        {
            AUDIO_ASSERT(0);
        }
    }
    if(p_celt_pisplit_library_handle == NULL)
    {
        if(PRELOADER_PISPLIT_XTLIB_NO_ERR != preloader_pisplit_get_handle(&p_celt_pisplit_library_handle, celt_library_get_by_version(stream_codec_celt_get_version()), celt_load_library_callback) )
        {
            DSP_MW_LOG_I("pisplit_celt preloader_pisplit_get_handle() error!!!!", 0);
            AUDIO_ASSERT(0);
        }
    }
  if(celt_lib_loaded_counter == 0)
  {
#ifdef AIR_DSP_MEMORY_REGION_ENABLE
        if(PRELOADER_PISPLIT_XTLIB_NO_ERR != preloader_pisplit_load_v1(p_celt_pisplit_library_handle, code_address, data_address))
#else
        if(PRELOADER_PISPLIT_XTLIB_NO_ERR != preloader_pisplit_load(p_celt_pisplit_library_handle,PRELOADER_I_HIGH_PERFORMANCE,PRELOADER_D_HIGH_PERFORMANCE) )
#endif
        {
            DSP_MW_LOG_I("pisplit_celt preloader_pisplit_load() error!!!!", 0);
            preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_I_HIGH_PERFORMANCE);
            preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_I_LOW_PERFORMANCE);
            preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_D_HIGH_PERFORMANCE);
            preloader_pisplit_dump_pic_memory_heap_info(PRELOADER_D_LOW_PERFORMANCE);
            AUDIO_ASSERT(0);
        }
        celt_lib_loaded_counter = 1;
        if(xSemaphoreTake( celt_load_lib_xSemaphore, portMAX_DELAY) == pdTRUE)
        {
        }
        else
        {
            AUDIO_ASSERT(0);
        }
  }
  else
  {
        celt_lib_loaded_counter++;
        //printf("clk_skew_library_load preloader_pisplit_load() had been loaded!!!");
  }
#ifdef AIR_DSP_MEMORY_REGION_ENABLE
    preloader_pisplit_get_library_code_and_data_size(p_celt_pisplit_library_handle, NULL, dram_pic_usage);
#else
    UNUSED(code_address);
    UNUSED(data_address);
    UNUSED(dram_pic_usage);
#endif
    return celt_lib_loaded_counter;
}

uint32_t celt_library_unload()
{
    if(celt_lib_loaded_counter == 1)
    {

#ifdef AIR_DSP_MEMORY_REGION_ENABLE
        if(PRELOADER_PISPLIT_XTLIB_NO_ERR != preloader_pisplit_unload_v1(p_celt_pisplit_library_handle))
#else
        if(PRELOADER_PISPLIT_XTLIB_NO_ERR != preloader_pisplit_unload(p_celt_pisplit_library_handle))
#endif
        {
            DSP_MW_LOG_I("pisplit_celt preloader_pisplit_unload() error!!!!", 0);
            AUDIO_ASSERT(0);
        }
        celt_export_parameters[0] = (void *)celt_default_function_parameter;
        celt_export_parameters[1] = (void *)celt_default_function_parameter;
        celt_export_parameters[2] = (void *)celt_default_function_parameter;
        celt_export_parameters[3] = (void *)celt_default_function_parameter;
        celt_export_parameters[4] = (void *)celt_default_function_parameter;
        celt_export_parameters[5] = (void *)celt_default_function_parameter;
        celt_export_parameters[6] = (void *)celt_default_function_parameter;

        //p_celt_pisplit_library_handle = NULL;
        celt_lib_loaded_counter = 0;
    }
    else
    {
        celt_lib_loaded_counter--;
    }

    return celt_lib_loaded_counter;

}


