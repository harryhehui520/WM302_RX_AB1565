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

#include "hal_msdc.h"
#include "hal_sd.h"
#include "hal_sd_internal.h"
#include "hal_nvic.h"


#ifdef HAL_SD_MODULE_ENABLED
#include "hal_log.h"
#include "hal_gpt.h"
#include "assert.h"
#include "hal_clock.h"

#ifdef MTK_SWLA_ENABLE
#include "swla.h"
#endif /* MTK_SWLA_ENABLE */

extern sd_information_t sd_information;
extern msdc_config_t msdc_config[];
extern uint32_t sd_csd[];

extern ATTR_TEXT_IN_TCM hal_clock_status_t clock_mux_sel(clock_mux_sel_id mux_id, uint32_t mux_sel);

extern uint32_t input_freq;

#ifdef HAL_SLEEP_MANAGER_ENABLED
const sleep_management_lock_request_t sd_sleep_handle[MSDC_PORT_MAX] = {SLEEP_LOCK_MSDC};
#endif

#ifdef HAL_SD_CARD_DETECTION
hal_sd_status_t hal_sd_register_card_detection_callback(hal_sd_port_t sd_port, hal_sd_card_detect_callback_t sd_callback, void *user_data)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == sd_callback) {
        log_hal_msgid_error("SD card detection callback is NULL!\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }
    msdc_config[sd_port].msdc_card_detect_callback = sd_callback;
    msdc_config[sd_port].card_detect_user_data = user_data;

    return HAL_SD_STATUS_OK;
}
#endif

hal_sd_status_t hal_sd_register_callback(hal_sd_port_t sd_port, hal_sd_callback_t sd_callback, void *user_data)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == sd_callback) {
        return HAL_SD_STATUS_ERROR;
    }
    msdc_config[sd_port].msdc_sd_callback = sd_callback;
    return HAL_SD_STATUS_OK;
}

/*This API only used for SD card*/
hal_sd_status_t hal_sd_set_bus_width(hal_sd_port_t sd_port, hal_sd_bus_width_t bus_width)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t command6_argment = 0;
    uint32_t argument = 0;
    MSDC_REGISTER_T *msdc_register_base;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    msdc_register_base = MSDC0_REG;

    if (sd_information.card_type == HAL_SD_TYPE_SD_CARD       ||
        sd_information.card_type == HAL_SD_TYPE_SD20_LCS_CARD ||
        sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) {

        /*check whether sd card support 4 bit bus*/
        if (bus_width == HAL_SD_BUS_WIDTH_4 && !(sd_information.scr.bus_width & (1 << HAL_SD_BUS_WIDTH_4))) {
            status = ERROR_NOT_SUPPORT_4BITS;
            log_hal_msgid_error("msdc not support 4 bits width\r\n", 0);
            goto error;
        }

        status = sd_send_command55(sd_port, sd_information.rca);
        if (status != NO_ERROR) {
            log_hal_msgid_error("cmd 55 send error\r\n", 0);
            goto error;
        }

        command6_argment = (bus_width == HAL_SD_BUS_WIDTH_4) ? COMMAND6_BUS_WIDTH_4 : COMMAND6_BUS_WIDTH_1;
        status = sd_send_command(sd_port, MSDC_ACOMMAND6, command6_argment);
        if (status != NO_ERROR) {
            log_hal_msgid_error("acmd 6 send error\r\n", 0);
            goto error;
        }

        status = sd_check_card_status(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("sd card status error\r\n", 0);
            goto error;
        }

        if (bus_width == HAL_SD_BUS_WIDTH_4) {
            msdc_register_base->SDC_CFG = (msdc_register_base->SDC_CFG & (~SDC_CFG_BUSWIDTH_MASK)) | (MSDC_SDIO_BUS_WIDTH_4BITS << SDC_CFG_BUSWIDTH_OFFSET);
            sd_information.bus_width = HAL_SD_BUS_WIDTH_4;
        } else {
            msdc_register_base->SDC_CFG = msdc_register_base->SDC_CFG & (~SDC_CFG_BUSWIDTH_MASK);
        }
    } else if (sd_information.card_type == HAL_SD_TYPE_MMC_CARD ||
               sd_information.card_type == HAL_SD_TYPE_MMC42_CARD) {

        if (bus_width == HAL_SD_BUS_WIDTH_4) {
            argument = (EXT_CSD_ACCESS_MODE_WRITE_BYTE << MMC_COMMAND6_ACCESS_BIT_SHIFT) |
                       (EXT_CSD_BUS_WIDTH_INDEX << MMC_COMMAND6_INDEX_BIT_SHIFT)          |
                       (MMC_BUS_WIDTH_4 << MMC_COMMAND6_VALUE_BIT_SHIFT)                  |
                       (0);
        } else if (bus_width == HAL_SD_BUS_WIDTH_1) {
            argument = (EXT_CSD_ACCESS_MODE_WRITE_BYTE << MMC_COMMAND6_ACCESS_BIT_SHIFT) |
                       (EXT_CSD_BUS_WIDTH_INDEX << MMC_COMMAND6_INDEX_BIT_SHIFT)          |
                       (MMC_BUS_WIDTH_1 << MMC_COMMAND6_VALUE_BIT_SHIFT)                  |
                       (0);
        }

        /*because need read ext_csd after switch to bus width 4 in api mmc_switch, so need change msdc bus config to 4 bit frist */
        if (bus_width == HAL_SD_BUS_WIDTH_4) {
            msdc_register_base->SDC_CFG = (msdc_register_base->SDC_CFG & (~SDC_CFG_BUSWIDTH_MASK)) | (MSDC_SDIO_BUS_WIDTH_4BITS << SDC_CFG_BUSWIDTH_OFFSET);
            sd_information.bus_width = HAL_SD_BUS_WIDTH_4;
        } else {
            msdc_register_base->SDC_CFG = msdc_register_base->SDC_CFG & (~SDC_CFG_BUSWIDTH_MASK);
        }

        if (sd_information.csd.ext_csd->ext_csd_rev >= MMC_EXTENDED_CSD_VERSION_441) {
            status = mmc_switch(sd_port, argument);
            if (NO_ERROR != status) {
                log_hal_msgid_error("emmc switch error\r\n", 0);
                goto error;
            }
        }
    }

    return HAL_SD_STATUS_OK;

error:
    sd_information.error_status = status;
    log_hal_msgid_error("sd error status = %d\r\n", 1, status);

    return HAL_SD_STATUS_ERROR;
}

hal_sd_status_t hal_sd_init(hal_sd_port_t sd_port, hal_sd_config_t *sd_config)
{
    sd_internal_status_t status = NO_ERROR;

    MSDC_REGISTER_T *msdc_register_base;
    uint32_t nvic_mask = 0;

    input_freq = sd_config->clock;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    msdc_register_base = MSDC0_REG;

    if (NULL == sd_config) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    hal_nvic_save_and_set_interrupt_mask(&nvic_mask);
    if (sd_information.is_busy) {
        hal_nvic_restore_interrupt_mask(nvic_mask);
        log_hal_msgid_error("msdc is busy now\r\n", 0);
        return HAL_SD_STATUS_BUSY;
    } else {
        sd_information.is_busy = true;
    }
    hal_nvic_restore_interrupt_mask(nvic_mask);

    /*cofirm whether MSDC have used by SDIO*/
    if (MSDC_INITIALIZED == msdc_init((msdc_port_t)sd_port, sd_config->bus_width)) {
        if (MSDC_OWNER_SDIO == msdc_get_owner((msdc_port_t)sd_port)) {
            sd_information.is_busy = false;
            log_hal_msgid_error("msdc used by SDIO\r\n", 0);
            return HAL_SD_STATUS_ERROR;
        }
    }
    msdc_nvic_set((msdc_port_t)sd_port, false);

#ifdef HAL_SLEEP_MANAGER_ENABLED
    sleep_management_register_suspend_callback(SLEEP_BACKUP_RESTORE_MSDC, (sleep_management_suspend_callback_t)sd_backup_all, NULL);
    sleep_management_register_resume_callback(SLEEP_BACKUP_RESTORE_MSDC, (sleep_management_resume_callback_t)sd_restore_all, NULL);
#endif

    /*disable MSDC DMA*/
    msdc_dma_disable((msdc_port_t)sd_port);

    msdc_card_power_set((msdc_port_t)sd_port, false);

    msdc_wait(1);

    msdc_card_power_set((msdc_port_t)sd_port, true);

    /*save MSDC owner*/
    msdc_set_owner((msdc_port_t)sd_port, MSDC_OWNER_SD);

    /*switch INCR1 to single burst.*/
    msdc_register_base->PATCH_BIT1 |= (1 << 16);

    msdc_reset((msdc_port_t)sd_port);

    msdc_clock_init((msdc_port_t)sd_port);

    /*disable 4 bit mode*/
    msdc_register_base->SDC_CFG = msdc_register_base->SDC_CFG & (~SDC_CFG_BUSWIDTH_MASK);

    /*init global structure*/
    memset(&sd_information, 0, sizeof(sd_information_t));
    sd_information.block_length = SD_BLOCK_LENGTH;
    sd_information.rca = 0;
    sd_information.is_inactive = false;
    sd_information.sd_state = IDLE_STA;
    sd_information.bus_width = HAL_SD_BUS_WIDTH_1;
    sd_information.is_initialized = false;

    /*for debugging,enable serial clock*/
    msdc_register_base->MSDC_CFG = msdc_register_base->MSDC_CFG | MSDC_CFG_CKPDN_MASK;

    msdc_wait(1);

    /*disable serial clock*/
    msdc_register_base->MSDC_CFG = msdc_register_base->MSDC_CFG & (~MSDC_CFG_CKPDN_MASK);

    /*send CMD0*/
    status = sd_reset(sd_port);
    if (NO_ERROR != status) {
        log_hal_msgid_error("sd card reset error\r\n", 0);
        goto error;
    }

    /*send CMD8 and ADMD41 for SD, send CMD1 for eMMC*/
    if (sd_check_card_type(sd_port) == HAL_SD_TYPE_UNKNOWN_CARD) {
        status = ERROR_INVALID_CARD;
        log_hal_msgid_error("msdc detect invalid card\r\n", 0);
        goto error;
    } else {
        /*need reset error status because error status changed in sd_check_card_type*/
        sd_information.error_status = NO_ERROR;
    }

    /*senc CMD2*/
    status = sd_get_card_id(sd_port);
    if (NO_ERROR != status) {
        log_hal_msgid_error("cmd2 send error\r\n", 0);
        goto error;
    }

    /*send CMD3*/
    status = sd_get_rca(sd_port);
    if (NO_ERROR != status) {
        log_hal_msgid_error("cmd3 send error\r\n", 0);
        goto error;
    }

    /*send CMD9*/
    status = sd_get_csd(sd_port);
    if (NO_ERROR != status) {
        log_hal_msgid_error("cmd9 send error\r\n", 0);
        goto error;
    }

    if (sd_information.csd.dsr_imp) {
        status = sd_set_dsr(sd_port);
        if (NO_ERROR != status) {
            log_hal_msgid_error("sd card dsr check error\r\n", 0);
            goto error;
        }
    }

    /*send CMD7*/
    status = sd_select_card(sd_port, sd_information.rca);
    if (status == ERROR_CARD_IS_LOCKED) {
        sd_information.is_locked = true;
    } else if (NO_ERROR != status) {
        log_hal_msgid_error("cmd 7 send error\r\n", 0);
        goto error;
    }

    msdc_set_output_clock((msdc_port_t)sd_port, MSDC_OUTPUT_CLOCK);

    if (sd_information.card_type == HAL_SD_TYPE_SD_CARD       ||
        sd_information.card_type == HAL_SD_TYPE_SD20_LCS_CARD ||
        sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) {

        status = sd_get_scr(sd_port);
        if (NO_ERROR != status) {
            log_hal_msgid_error("sd card get scr error\r\n", 0);
            goto error;
        }

        if (HAL_SD_STATUS_OK != hal_sd_set_bus_width(HAL_SD_PORT_0, sd_config->bus_width)) {
            msdc_deinit((msdc_port_t)sd_port);
            sd_information.is_busy = false;
            log_hal_msgid_error("msdc bus width set error\r\n", 0);
            return HAL_SD_STATUS_ERROR;
        }

        status = sd_acommand42(sd_port);
        if (NO_ERROR != status) {
            log_hal_msgid_error("send acmd 42 error\r\n", 0);
            goto error;
        }

        if (sd_information.scr.spec_ver > SD_SPECIFICATION_101) {
            status = sd_select_high_speed(sd_port);
            if (NO_ERROR != status) {
                /*if card not support high speed, the max speed is 25MHZ*/
                sd_information.is_high_speed = false;
            }
        }
    } else if (sd_information.card_type == HAL_SD_TYPE_MMC_CARD ||
               sd_information.card_type == HAL_SD_TYPE_MMC42_CARD) {

        /*before set emmc bus width should call set high speed frist,because extended csd register frist be readed in mmc_set_high_speed*/
        status = mmc_set_high_speed(sd_port);
        if (NO_ERROR != status) {
            log_hal_msgid_error("emmc set high speed error\r\n", 0);
            goto error;
        }

        if (HAL_SD_STATUS_OK != hal_sd_set_bus_width(HAL_SD_PORT_0, sd_config->bus_width)) {
            msdc_deinit((msdc_port_t)sd_port);
            sd_information.is_busy = false;
            log_hal_msgid_error("msdc bus width set error\r\n", 0);
            return HAL_SD_STATUS_ERROR;
        }
    }

    if (sd_information.card_type == HAL_SD_TYPE_MMC42_CARD) {
        sd_information.csd.capacity = (uint64_t)sd_information.csd.ext_csd->sec_count << 9; /*sec_cout * 512byte*/
    }

    status = sd_set_block_length(sd_port, SD_BLOCK_LENGTH);
    if (NO_ERROR != status) {
        log_hal_msgid_error("sd set blk length error\r\n", 0);
        goto error;
    }

    sd_information.is_busy = false;

    sd_information.is_initialized = true;

    /*config clk freq by device type,SD card max freq = 48m,emmc max freq =  52m*/
    if ((sd_information.card_type == HAL_SD_TYPE_SD_CARD) || (sd_information.card_type == HAL_SD_TYPE_SD20_LCS_CARD) || (sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD)) {
        ;

        /* changed by 60731 on 2020.04.01:it should be 50m for sd card£¬but we cannot get 50m,
         * clock can be divided into 52m and 41.6m£¬we use 52m temporarily.
        */
        clock_mux_sel(CLK_SDIOMST0_SEL, 2); //52m
        //clock_mux_sel(CLK_SDIOMST0_SEL,3);    //41.6m

        /*SD card type*/
        msdc_set_output_clock((msdc_port_t)sd_port, sd_config->clock);

    } else if ((sd_information.card_type == HAL_SD_TYPE_MMC_CARD) || (sd_information.card_type == HAL_SD_TYPE_MMC42_CARD)) {

        clock_mux_sel(CLK_SDIOMST0_SEL, 2); //52m src clk

        msdc_set_output_clock((msdc_port_t)sd_port, sd_config->clock);
    } else {
        log_hal_msgid_error("card type wrong \r\n!", 0);
        goto error;
    }

    return HAL_SD_STATUS_OK;

error:
    memset(&sd_information, 0, sizeof(sd_information_t));
    sd_information.block_length = SD_BLOCK_LENGTH;
    sd_information.rca = 0;
    sd_information.is_inactive = false;
    sd_information.sd_state = IDLE_STA;
    sd_information.bus_width = HAL_SD_BUS_WIDTH_1;
    sd_information.is_initialized = false;

    sd_information.error_status = status;
    log_hal_msgid_error("sd error status = %d \r\n", 1, status);
    msdc_deinit((msdc_port_t)sd_port);

    sd_information.is_busy = false;

    return HAL_SD_STATUS_ERROR;
}

hal_sd_status_t hal_sd_deinit(hal_sd_port_t sd_port)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    msdc_reset((msdc_port_t)sd_port);

    memset(&sd_information, 0, sizeof(sd_information_t));

    msdc_deinit((msdc_port_t)sd_port);

    return HAL_SD_STATUS_OK;
}


hal_sd_status_t hal_sd_get_capacity(hal_sd_port_t sd_port, uint64_t *capacity)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == capacity) {
        log_hal_msgid_error("parameter error.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if ((0 != sd_information.csd.capacity) && (sd_information.is_initialized == true)) {
        *capacity = sd_information.csd.capacity;
        return HAL_SD_STATUS_OK;
    } else {
        log_hal_msgid_error("sd capacity check error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }
}

/*for SD card densities greater than 2GB, start_sector unit is write block size, otherwise the unit is byte, and should write block size align.
  for MMC card densities greater than 2GB, start_sector unit is erase group size, otherwise the unit is byte, and should erase group size align*/
hal_sd_status_t hal_sd_erase_sectors(hal_sd_port_t sd_port, uint32_t start_sector, uint32_t sector_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t sector_multiplier = 0;
    uint32_t start_address_command = 0;
    uint32_t end_address_command = 0;
    uint32_t nvic_mask = 0;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    hal_nvic_save_and_set_interrupt_mask(&nvic_mask);
    if (sd_information.is_busy) {
        hal_nvic_restore_interrupt_mask(nvic_mask);
        log_hal_msgid_error("msdc is busy now\r\n", 0);
        return HAL_SD_STATUS_BUSY;
    } else {
        sd_information.is_busy = true;
    }
    hal_nvic_restore_interrupt_mask(nvic_mask);

#ifdef HAL_DVFS_MODULE_ENABLED
    /*lock dvfs before start transfer. */
    msdc_dvfs_lock_current((msdc_port_t)sd_port);
#endif

    /*data address is in byte units in a SD1.0 memory card and in block(512byte)  units in a High Capacity SD memory card.
    for eMMC, data address for densities =< 2GB is a 32bit byte address and data address densities > 2GB is a 32bit erase group size address.*/
    if ((sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) || (sd_information.card_type == HAL_SD_TYPE_MMC42_CARD)) {
        sector_multiplier = 1;
    } else if (sd_information.card_type == HAL_SD_TYPE_MMC_CARD) {
        /*for emmc, erase group size is mutil blocks*/
        sector_multiplier = sd_information.csd.erase_grp_size_mmc >> 9;
    } else {
        sector_multiplier = SD_BLOCK_LENGTH;
    }

    /*set erase start address command and erase end address command adopt*/
    if ((sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) ||
        (sd_information.card_type == HAL_SD_TYPE_SD20_LCS_CARD) ||
        (sd_information.card_type == HAL_SD_TYPE_SD_CARD)) {
        start_address_command = MSDC_COMMAND32;
        end_address_command = MSDC_COMMAND33;
    } else {
        start_address_command = MSDC_COMMAND35_MMC;
        end_address_command = MSDC_COMMAND36_MMC;
    }

    /*send erase start sector address*/
    status = sd_send_erase_command(sd_port, start_address_command, sector_multiplier * start_sector);
    if (NO_ERROR != status) {
        log_hal_msgid_error("erase cmd start addr send error\r\n", 0);
        goto error;
    }

    /*send erase end sector address*/
    status = sd_send_erase_command(sd_port, end_address_command, sector_multiplier * (start_sector + sector_number - 1));
    if (NO_ERROR != status) {
        log_hal_msgid_error("erase cmd end addr send error\r\n", 0);
        goto error;
    }

    /*start erase*/
    status = sd_send_erase_command(sd_port, MSDC_COMMAND38, COMMAND_NO_ARGUMENT);
    if (NO_ERROR != status) {
        log_hal_msgid_error("erase cmd send error\r\n", 0);
        goto error;
    }

    sd_information.is_busy = false;

#ifdef HAL_DVFS_MODULE_ENABLED
    /*unlock dvfs before end transfer.*/
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif

    return HAL_SD_STATUS_OK;

error:

    sd_information.error_status = status;
    msdc_power_set((msdc_port_t)sd_port, false);

    sd_information.is_busy = false;
    log_hal_msgid_error("sd error status = %d \r\n", 1, status);

#ifdef HAL_DVFS_MODULE_ENABLED
    /*unlock dvfs before end transfer.*/
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif

    return HAL_SD_STATUS_ERROR;
}

hal_sd_status_t hal_sd_read_blocks(hal_sd_port_t sd_port, uint32_t *read_buffer,  uint32_t read_address, uint32_t block_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t read_command = 0;
    uint32_t index = 0;
    uint64_t read_word_count = 0;
    uint32_t response = 0;
    uint32_t block_multiplier = 0;
    uint32_t interrupte_status = 0;
    uint32_t count = 0;
    uint32_t fifo_count = 0;
    MSDC_REGISTER_T *msdc_register_base;
    uint32_t nvic_mask = 0;
    uint32_t interrupt_status = 0;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    msdc_register_base = MSDC0_REG;

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == read_buffer) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    hal_nvic_save_and_set_interrupt_mask(&nvic_mask);
    if (sd_information.is_busy) {
        hal_nvic_restore_interrupt_mask(nvic_mask);
        log_hal_msgid_error("msdc is busy now\r\n", 0);
        return HAL_SD_STATUS_BUSY;
    } else {
        sd_information.is_busy = true;
    }
    hal_nvic_restore_interrupt_mask(nvic_mask);

#ifdef HAL_DVFS_MODULE_ENABLED
    /*lock dvfs before start transfer.*/
    msdc_dvfs_lock_current((msdc_port_t)sd_port);
#endif

    msdc_reset((msdc_port_t)sd_port);
    msdc_clear_fifo((msdc_port_t)sd_port);

    /*disable DMA mode, use PIO mode.*/
    msdc_dma_disable((msdc_port_t)sd_port);

    /*read clear to make sure we will read latest one in the future*/
    interrupte_status = msdc_register_base->MSDC_INT;
    if (0 != interrupte_status) {
        msdc_register_base->MSDC_INT |= interrupte_status;
    }

    /*data address is in byte units in a SD1.0 memory card and in block(512byte)  units in a High Capacity SD memory card.
      for eMMC, data address for densities =< 2GB is a 32bit byte address and data address densities > 2GB is a 32bit erase group size address.*/
    if ((sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) || (sd_information.card_type == HAL_SD_TYPE_MMC42_CARD)) {
        block_multiplier = 1;
    } else if (sd_information.card_type == HAL_SD_TYPE_MMC_CARD) {
        /*for emmc densities =< 2GB, access mode is byte mode*/
        block_multiplier = sd_information.csd.read_bl_len;
    } else {
        block_multiplier = SD_BLOCK_LENGTH;
    }

    /*set block number.*/
    msdc_register_base->SDC_BLK_NUM = block_number;

    read_command = ((block_number > 1) ? MSDC_COMMAND18 : MSDC_COMMAND17) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, read_command, (read_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("read blk cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("sd card status error\r\n", 0);
        goto error;
    }

    read_word_count = (uint64_t)(((uint64_t)block_number * SD_BLOCK_LENGTH) >> 2);

    while (index < read_word_count) {
        /*check MSDC_INT data status error,prevent hang issue*/
        interrupt_status = msdc_register_base->MSDC_INT;
        if (interrupt_status & MSDC_INT_DATTMO_MASK) {
            log_hal_msgid_error("polling data error,MSDC_INT = %x\r\n", 1, (unsigned int)interrupt_status);
            status = ERROR_DATA_TIMEOUT;
            goto error;
        } else if (interrupt_status & MSDC_INT_DATCRCERR_MASK) {
            log_hal_msgid_error("polling data error,MSDC_INT = %x\r\n", 1, (unsigned int)interrupt_status);
            status = ERROR_DATA_CRC_ERROR;
            goto error;
        }
        /*polling data*/
        fifo_count = ((msdc_register_base->MSDC_FIFOCS & MSDC_FIFOCS_RXCNT_MASK) >> 0);

        if ((read_word_count < (MSDC_FIFO_SIZE >> 2)) && (read_word_count <= (fifo_count >> 2))) {
            do {
                *read_buffer++ = msdc_register_base->MSDC_RXDATA;
            } while (--read_word_count);
        } else if (read_word_count >= (MSDC_FIFO_SIZE >> 2) && (MSDC_FIFO_SIZE <= fifo_count)) {
            count = MSDC_FIFO_SIZE >> 2;
            do {
                *read_buffer++ = msdc_register_base->MSDC_RXDATA;
            } while (--count);
            read_word_count = read_word_count - (MSDC_FIFO_SIZE >> 2);
        }
    }

    status = sd_wait_data_ready(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("wait sd data ready error\r\n", 0);
        goto error;
    }

    msdc_reset((msdc_port_t)sd_port);

    /*clear msdc interrupt status*/
    msdc_register_base->MSDC_INT = MSDC_DAT_INTS;

    if (1 == block_number) {
        status = sd_wait_card_not_busy(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("wait card not busy error\r\n", 0);
            goto error;
        }
    } else {
        status = sd_stop_transfer(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("stop transfer cmd send error\r\n", 0);
            goto error;
        }
    }

    while (msdc_card_is_present((msdc_port_t)sd_port)) {
        /*read card status*/
        status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
        if (NO_ERROR != status) {
            log_hal_msgid_error("card status read error\r\n", 0);
            goto error;
        }

        response = msdc_register_base->SDC_RESP0;

        if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK) &&
            ((response & SD_CARD_STATUS_STATE_BIT_MASK) >> SD_CARD_STATUS_STATE_BIT_SHIFT) == TRAN_STA) {
            break;
        }
    }

    msdc_reset((msdc_port_t)sd_port);

    sd_information.is_busy = false;

#ifdef HAL_DVFS_MODULE_ENABLED
    /*unlock dvfs before end transfer.*/
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif

    return HAL_SD_STATUS_OK;

error:

    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;
}


hal_sd_status_t hal_sd_write_blocks(hal_sd_port_t sd_port, const uint32_t *write_buffer,  uint32_t write_address, uint32_t block_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t write_command = 0;
    uint32_t index = 0;
    uint64_t write_word_count = 0;
    uint32_t response = 0;
    uint32_t block_multiplier = 0;
    uint32_t interrupte_status = 0;
    uint32_t count = 0;
    MSDC_REGISTER_T *msdc_register_base;
    uint32_t nvic_mask = 0;
    uint32_t interrupt_status = 0;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    msdc_register_base = MSDC0_REG;

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == write_buffer) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    hal_nvic_save_and_set_interrupt_mask(&nvic_mask);
    if (sd_information.is_busy) {
        hal_nvic_restore_interrupt_mask(nvic_mask);
        log_hal_msgid_error("msdc is busy now\r\n", 0);
        return HAL_SD_STATUS_BUSY;
    } else {
        sd_information.is_busy = true;
    }
    hal_nvic_restore_interrupt_mask(nvic_mask);

#ifdef HAL_DVFS_MODULE_ENABLED
    /*lock dvfs before start transfer.*/
    msdc_dvfs_lock_current((msdc_port_t)sd_port);
#endif

    msdc_reset((msdc_port_t)sd_port);
    msdc_clear_fifo((msdc_port_t)sd_port);

    /*read clear to make sure we will read latest one in the future*/
    interrupte_status = msdc_register_base->MSDC_INT;
    if (0 != interrupte_status) {
        msdc_register_base->MSDC_INT |= interrupte_status;
    }

    /*disable DMA mode, use PIO mode.*/
    msdc_dma_disable((msdc_port_t)sd_port);

    if (sd_information.is_write_protection) {
        log_hal_msgid_error("card is write protection.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    /*data address is in byte units in a SD1.0 memory card and in block(512byte)  units in a High Capacity SD memory card.
      for eMMC, data address for densities =< 2GB is a 32bit byte address and data address densities > 2GB is a 32bit erase group size address.*/
    if ((sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) || (sd_information.card_type == HAL_SD_TYPE_MMC42_CARD)) {
        block_multiplier = 1;
    } else if (sd_information.card_type == HAL_SD_TYPE_MMC_CARD) {
        /*for emmc densities =< 2GB, access mode is byte mode*/
        block_multiplier = sd_information.csd.read_bl_len;
    } else {
        block_multiplier = SD_BLOCK_LENGTH;
    }

    /*set block number.*/
    msdc_register_base->SDC_BLK_NUM = block_number;

    write_command = ((block_number > 1) ? MSDC_COMMAND25 : MSDC_COMMAND24) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, write_command, (write_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("write blk cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("sd card status error\r\n", 0);
        goto error;
    }

    write_word_count = (uint64_t)(((uint64_t)block_number * SD_BLOCK_LENGTH) >> 2);

    while (index < write_word_count) {
        /*check MSDC_INT data status error,prevent hang issue*/
        interrupt_status = msdc_register_base->MSDC_INT;
        if (interrupt_status & MSDC_INT_DATTMO_MASK) {
            log_hal_msgid_error("polling data error,MSDC_INT = %x\r\n", 1, (unsigned int)interrupt_status);
            status = ERROR_DATA_TIMEOUT;
            goto error;
        } else if (interrupt_status & MSDC_INT_DATCRCERR_MASK) {
            log_hal_msgid_error("polling data error,MSDC_INT = %x\r\n", 1, (unsigned int)interrupt_status);
            status = ERROR_DATA_CRC_ERROR;
            goto error;
        }
        /*polling data*/
        if ((write_word_count < (MSDC_FIFO_SIZE >> 2)) && (0 == MSDC_TXFIFOCNT(msdc_register_base))) {
            do {
                msdc_register_base->MSDC_TXDATA = *write_buffer++;
            } while (--write_word_count);
        } else if (write_word_count >= (MSDC_FIFO_SIZE >> 2) && (0 == MSDC_TXFIFOCNT(msdc_register_base))) {
            count = MSDC_FIFO_SIZE >> 2;
            do {
                msdc_register_base->MSDC_TXDATA = *write_buffer++;
            } while (--count);
            write_word_count = write_word_count - (MSDC_FIFO_SIZE >> 2);
        }
    }

    status = sd_wait_data_ready(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("sd wait data ready error\r\n", 0);
        goto error;
    }

    if (1 < block_number) {
        status = sd_stop_transfer(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("stop transfer cmd error\r\n", 0);
            goto error;
        }

    } else if (1 ==  block_number) {
        status = sd_wait_card_not_busy(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("wait card not busy error\r\n", 0);
            goto error;
        }
    }

    while (msdc_card_is_present((msdc_port_t)sd_port)) {
        /*read card status*/
        status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
        if (NO_ERROR != status) {
            log_hal_msgid_error("read card status error\r\n", 0);
            goto error;
        }

        response = msdc_register_base->SDC_RESP0;

        /*check corresponds to buffer empty singaling on the bus*/
        if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK) &&
            ((response & SD_CARD_STATUS_STATE_BIT_MASK) >> SD_CARD_STATUS_STATE_BIT_SHIFT) == TRAN_STA) {
            break;
        }
    }

    msdc_reset((msdc_port_t)sd_port);

    sd_information.is_busy = false;

#ifdef HAL_DVFS_MODULE_ENABLED
    /*unlock dvfs before end transfer.*/
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif

    return HAL_SD_STATUS_OK;

error:

    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;
}


#ifdef AIR_WIRELESS_MIC_TX_ENABLE
#include "ff.h"
extern uint32_t start_record_flag;
extern uint32_t fs_clust_size;
extern uint32_t fs_write_flag;
extern FIL *app_wireless_writefs_point;
extern void app_wireless_mic_update_read_point(uint32_t len);

static uint32_t buffer_block_address;
static uint8_t *ptempbuffer;
// 1: only the cluster parameter of create_chain(clust)  which is changed    0: others
static uint32_t winsect_changed;

#define FS_SECTOR_SIZE   (512)
//write buffer size should be  (fs_clust_size/2)
#define FS_WRTITE_BUFF_SIZE   (0x4000)
//((FS_WRTITE_BUFF_SIZE/FS_SECTOR_SIZE) - 1)
#define SECTOR_NUM    (31)

#define EMMC_FS_RECORD_START                   (1)
#define EMMC_FS_RECORD_ALLOCATE                (2)
#define EMMC_FS_RECORD_STOP                    (5)

#define EMMC_FS_WRITE_FINISH                   (0)
#define EMMC_FS_WRITE_START                    (1)
#define EMMC_FS_WRITE_WRITE_SECTOR             (2)
#define EMMC_FS_WRITE_WRITE_CLUSTER            (3)
#define EMMC_FS_WRITE_WRITE_FAT_SECTOR         (4)
#define EMMC_FS_WRITE_WRITE_FAT_SECTOR_1       (5)
#define EMMC_FS_WRITE_WRITE_FAT_SECTOR_2       (6)
#define  EMMC_FS_WRITE_WRITE_FAT_SECTOR_3      (7)
#define EMMC_FS_WRITE_WRITE_FAT_0_1_DONE       (8)
#define EMMC_FS_WRITE_WRITE_CLUST_CHANGED      (9)

//#define EMMC_WRITE_DEBUG_LOG
hal_sd_status_t hal_sd_read_blocks_dma_blocking(hal_sd_port_t sd_port, uint32_t *read_buffer, uint32_t read_address, uint32_t block_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t response = 0;
    uint32_t read_command = 0;
    uint32_t block_multiplier = 0;
    MSDC_REGISTER_T *msdc_register_base;
    uint32_t winsect_loc,sect;

    if(fs_write_flag == EMMC_FS_WRITE_WRITE_FAT_SECTOR){
        winsect_loc = app_wireless_writefs_point->obj.fs->winsect;
        sect = app_wireless_writefs_point->obj.fs->fatbase + (app_wireless_writefs_point->clust / (512 / 4));
#ifdef EMMC_WRITE_DEBUG_LOG
        log_hal_msgid_info("[MSDC] read_address = 0x%x, sect = 0x%x, winsect = 0x%x", 3, read_address,  sect, winsect_loc);
#endif
        sect = read_address;
        if (winsect_loc != sect) {
            winsect_changed = 1;
        }
    }

    msdc_register_base = MSDC0_REG;
    status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)read_buffer,block_number,&block_multiplier);
    if (status != NO_ERROR) {
        return status;
    }

    read_command = ((block_number > 1) ? MSDC_COMMAND18 : MSDC_COMMAND17) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, read_command, (read_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("[MSDC] read cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("[MSDC] sd card status error\r\n", 0);
        goto error;
    }

    /*start DMA transcation.*/
    msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

    status = sd_wait_data_ready_dma(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("[MSDC] msdc wait dma transfer ready error\r\n", 0);
        goto error;
    }

    msdc_reset((msdc_port_t)sd_port);
    msdc_dma_disable((msdc_port_t)sd_port);

    if (1 == block_number) {
        status = sd_wait_card_not_busy(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("[MSDC] wait card not busy error\r\n", 0);
            goto error;
        }
    } else {
        status = sd_stop_transfer(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("[MSDC] stop transfer cmd send error\r\n", 0);
            goto error;
        }
    }

    while (msdc_card_is_present((msdc_port_t)sd_port)) {
        /*read card status*/
        status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
        if (NO_ERROR != status) {
            log_hal_msgid_error("[MSDC] read card status error\r\n", 0);
            goto error;
        }

        response = msdc_register_base->SDC_RESP0;

        if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK) &&
            ((response & SD_CARD_STATUS_STATE_BIT_MASK) >> SD_CARD_STATUS_STATE_BIT_SHIFT) == TRAN_STA) {
            break;
        }
    }

    msdc_reset((msdc_port_t)sd_port);

    sd_information.is_busy = false;

#ifdef HAL_DVFS_MODULE_ENABLED
#ifndef AIR_WIRELESS_MIC_ENABLE
    /*unlock dvfs before end transfer.*/
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif
#endif

    return HAL_SD_STATUS_OK;

error:

    msdc_dma_disable((msdc_port_t)sd_port);
    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;
}


hal_sd_status_t hal_sd_write_blocks_dma_blocking(hal_sd_port_t sd_port, const uint32_t *write_buffer,  uint32_t write_address, uint32_t block_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t response = 0;
    uint32_t write_command = 0;
    uint32_t block_multiplier = 0;
    MSDC_REGISTER_T *msdc_register_base;
    uint32_t write_block = block_number;
    msdc_register_base = MSDC0_REG;
    uint32_t need_update_read_point = 0;

    if (sd_information.is_write_protection) {
        log_hal_msgid_error("[MSDC] card is write protection", 0);
        return HAL_SD_STATUS_ERROR;
    }

#ifdef EMMC_WRITE_DEBUG_LOG
    log_hal_msgid_info("[MSDC] write address = 0x%x, block_number = %d ", 2, write_address, block_number);
#endif

    if (start_record_flag == EMMC_FS_RECORD_START) {
        if(ptempbuffer==NULL) {
            //it is the write data size, now it should be 16KB.  it will format FS with  cluster size 32KB
            ptempbuffer = (uint8_t *)pvPortMallocNC(fs_clust_size/2);
            log_hal_msgid_info("[MSDC] malloc buffer size = 0x%x, pbuf = 0x%x", 2, fs_clust_size/2, ptempbuffer);
            if (ptempbuffer == NULL) {
                log_hal_msgid_error("[MSDC] EMMC write malloc fail", 0);
                fs_write_flag = EMMC_FS_WRITE_FINISH;
            }
            start_record_flag = EMMC_FS_RECORD_ALLOCATE;
        }
    }

    /*fs will write 1 sector + next sectors during during f_write for fatfs;  buffer the 16KB data and write to EMMC */
    if (fs_write_flag == EMMC_FS_WRITE_START && block_number == 1 && ptempbuffer !=NULL) {
        memcpy(ptempbuffer,write_buffer,FS_SECTOR_SIZE);
        fs_write_flag = EMMC_FS_WRITE_WRITE_SECTOR;
        buffer_block_address = write_address;
        return HAL_SD_STATUS_OK;
    } else if (fs_write_flag == EMMC_FS_WRITE_WRITE_SECTOR && block_number == SECTOR_NUM) {
        memcpy((uint8_t *)(ptempbuffer + FS_SECTOR_SIZE), write_buffer, FS_SECTOR_SIZE * SECTOR_NUM);
        fs_write_flag = EMMC_FS_WRITE_WRITE_CLUSTER;
        write_block = (SECTOR_NUM+1);
        write_address = buffer_block_address;
    }  else if (fs_write_flag == EMMC_FS_WRITE_WRITE_FAT_SECTOR) {
        uint32_t winsect_loc = app_wireless_writefs_point->obj.fs->winsect;
        uint32_t sect = app_wireless_writefs_point->obj.fs->fatbase + (app_wireless_writefs_point->clust / (FS_SECTOR_SIZE / 4));
#ifdef EMMC_WRITE_DEBUG_LOG
        log_hal_msgid_info("[MSDC] winsect = 0x%x, sect = 0x%x", 2, winsect_loc, sect);
#endif
        if((winsect_changed == 0) && (winsect_loc == sect)) {
            //create_chain: it allocate the next cluster; winsect_change is 0 as it does not do sd_read.
            //so the next write is continues, it can be merge and write one time.
            //but there has one exception if it the next cluster is taken by other file.
            //the two times write logical address is continue at most time, so it can bel merge and write one time
            //at the step the winsect and sect should be same as winsect had been sync in FS
            memcpy(ptempbuffer, write_buffer, FS_SECTOR_SIZE);
            fs_write_flag = EMMC_FS_WRITE_WRITE_FAT_SECTOR_1;
            buffer_block_address = write_address;
            write_block = 1;
            winsect_changed = 0;
#ifdef EMMC_WRITE_DEBUG_LOG
            log_hal_msgid_info("[MSDC] write FAT 0-1 addr = 0x%x, num = %d", 2, write_address, write_block);
#endif
            return HAL_SD_STATUS_OK;
        } else {
            //create_chain: the custer is not in winset when create or strench a new chain, it will write one time as the winsect changed
            fs_write_flag = EMMC_FS_WRITE_WRITE_CLUST_CHANGED;
#ifdef EMMC_WRITE_DEBUG_LOG
            log_hal_msgid_info("[MSDC] write FAT addr = 0x%x, num = %d", 2, write_address, write_block);
#endif
        }
    } else if (fs_write_flag == EMMC_FS_WRITE_WRITE_FAT_SECTOR_1) {
        if ((buffer_block_address +1) == write_address) {
            //continue cluster, can be write in one time
            memcpy((uint8_t *)(ptempbuffer + FS_SECTOR_SIZE), write_buffer, FS_SECTOR_SIZE);
            write_block = 2;
            write_address = buffer_block_address;
            fs_write_flag = EMMC_FS_WRITE_WRITE_FAT_SECTOR_2;
#ifdef EMMC_WRITE_DEBUG_LOG
            log_hal_msgid_info("[MSDC] write FAT 0-2 addr = 0x%x, num = %d", 2, write_address, write_block);
#endif
        } else {
            // 2 time write logical address is not continue, write two sectors directly
#ifdef EMMC_WRITE_DEBUG_LOG
            log_hal_msgid_info("[MSDC] write FAT 0&1 addr = 0x%x, num = %d", 2, buffer_block_address, write_block);
#endif
            fs_write_flag = EMMC_FS_WRITE_WRITE_FAT_SECTOR_3;

            {
            //write buffered 512 byte fat table
            status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)ptempbuffer,write_block,&block_multiplier);
            if (status != NO_ERROR) {
                return status;
            }

            write_command = ((write_block > 1) ? MSDC_COMMAND25 : MSDC_COMMAND24) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
            status = sd_send_command(sd_port, write_command, (write_address * block_multiplier));
            if (status != NO_ERROR) {
                log_hal_msgid_error("[MSDC] write cmd send error\r\n", 0);
                goto error;
            }

            status = sd_check_card_status(sd_port);
            if (status != NO_ERROR) {
                log_hal_msgid_error("[MSDC] sd card status error\r\n", 0);
                goto error;
            }

            /*start DMA transcation.*/
            msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

            status = sd_wait_data_ready_dma(sd_port);
            if (status != NO_ERROR) {
                log_hal_msgid_error("[MSDC] wait dma ready error\r\n", 0);
                goto error;
            }

            msdc_dma_disable((msdc_port_t)sd_port);

            if (1 < write_block) {
                status = sd_stop_transfer(sd_port);
                if (status != NO_ERROR) {
                    log_hal_msgid_error("[MSDC] stop cmd send error\r\n", 0);
                    goto error;
                }

            } else if (1 ==  write_block) {
                status = sd_wait_card_not_busy(sd_port);
                if (status != NO_ERROR) {
                    log_hal_msgid_error("[MSDC] wait sd card not busy error\r\n", 0);
                    goto error;
                }
            }

            while (msdc_card_is_present((msdc_port_t)sd_port)) {
                /*read card status*/
                status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
                if (NO_ERROR != status) {
                    log_hal_msgid_error("[MSDC] read card status error\r\n", 0);
                    goto error;
                }

                response = msdc_register_base->SDC_RESP0;

                /*check corresponds to buffer empty singaling on the bus*/
                if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK)) {
                    break;
                }
            }

            msdc_reset((msdc_port_t)sd_port);
            sd_information.is_busy = false;
            }
            //write second fat table
        }
    }

    if (fs_write_flag == EMMC_FS_WRITE_WRITE_CLUSTER || fs_write_flag == EMMC_FS_WRITE_WRITE_FAT_SECTOR_2) {
        status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)ptempbuffer,write_block,&block_multiplier);
#ifdef EMMC_WRITE_DEBUG_LOG
        log_hal_msgid_info("[MSDC] pckage write address = %d, num = 0x%x", 2, write_address, write_block);
#endif
        if (fs_write_flag == EMMC_FS_WRITE_WRITE_CLUSTER) {
            fs_write_flag = EMMC_FS_WRITE_WRITE_FAT_SECTOR;
            need_update_read_point = 1;
        }
        if (fs_write_flag == EMMC_FS_WRITE_WRITE_FAT_SECTOR_2) {
            fs_write_flag = EMMC_FS_WRITE_WRITE_FAT_0_1_DONE;
            need_update_read_point = 0;
        }
        winsect_changed = 0;
    } else {
        status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)write_buffer,write_block,&block_multiplier);
#ifdef EMMC_WRITE_DEBUG_LOG
        log_hal_msgid_info("[MSDC] org write address = %d, num = 0x%x ", 2, write_address, write_block);
#endif
        if (fs_write_flag == EMMC_FS_WRITE_WRITE_CLUST_CHANGED) {
            winsect_changed = 0;
        }
    }

    if (status != NO_ERROR) {
        return status;
    }

    if (ptempbuffer != NULL && start_record_flag == EMMC_FS_RECORD_STOP) {
        vPortFreeNC(ptempbuffer);
        ptempbuffer = NULL;
    }

    write_command = ((write_block > 1) ? MSDC_COMMAND25 : MSDC_COMMAND24) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, write_command, (write_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("[MSDC] write cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("[MSDC] sd card status error\r\n", 0);
        goto error;
    }

    /*start DMA transcation.*/
    msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

#ifdef MTK_SWLA_ENABLE
    SLA_CustomLogging("SDW",SA_START);
#endif

    status = sd_wait_data_ready_dma(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("[MSDC] wait dma ready error\r\n", 0);
        goto error;
    }

    msdc_dma_disable((msdc_port_t)sd_port);

    if (1 < write_block) {
        status = sd_stop_transfer(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("[MSDC] stop cmd send error\r\n", 0);
            goto error;
        }

    } else if (1 ==  write_block) {
        status = sd_wait_card_not_busy(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("[MSDC] wait sd card not busy error\r\n", 0);
            goto error;
        }
    }

    while (msdc_card_is_present((msdc_port_t)sd_port)) {
        /*read card status*/
        status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
        if (NO_ERROR != status) {
            log_hal_msgid_error("[MSDC] read card status error\r\n", 0);
            goto error;
        }

        response = msdc_register_base->SDC_RESP0;

        /*check corresponds to buffer empty singaling on the bus*/
        if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK)) {
            break;
        }
    }

    msdc_reset((msdc_port_t)sd_port);
    sd_information.is_busy = false;

    if (need_update_read_point == 1) {
        app_wireless_mic_update_read_point(0x4000);
        log_hal_msgid_info("[MSDC] write ok + update read point", 0);
        need_update_read_point = 0;
    } else {
        log_hal_msgid_info("[MSDC] write ok", 0);
    }

#ifdef HAL_DVFS_MODULE_ENABLED
    /*unlock dvfs before end transfer.*/
#ifndef AIR_WIRELESS_MIC_ENABLE
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif
#endif

#ifdef AIR_WIRELESS_MIC_ENABLE
#ifdef MTK_SWLA_ENABLE
    SLA_CustomLogging("SDW",SA_STOP);
#endif
#endif
    return HAL_SD_STATUS_OK;

error:
    msdc_dma_disable((msdc_port_t)sd_port);
    sd_error_handle(sd_port, status, write_block);

    return HAL_SD_STATUS_ERROR;
}
#else
hal_sd_status_t hal_sd_read_blocks_dma_blocking(hal_sd_port_t sd_port, uint32_t *read_buffer, uint32_t read_address, uint32_t block_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t response = 0;
    uint32_t read_command = 0;
    uint32_t block_multiplier = 0;
    MSDC_REGISTER_T *msdc_register_base;

    msdc_register_base = MSDC0_REG;

    status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)read_buffer,block_number,&block_multiplier);
    if (status != NO_ERROR) {
        return status;
    }

    read_command = ((block_number > 1) ? MSDC_COMMAND18 : MSDC_COMMAND17) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, read_command, (read_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("read cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("sd card status error\r\n", 0);
        goto error;
    }

    /*start DMA transcation.*/
    msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

    status = sd_wait_data_ready_dma(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("msdc wait dma transfer ready error\r\n", 0);
        goto error;
    }

    msdc_reset((msdc_port_t)sd_port);
    msdc_dma_disable((msdc_port_t)sd_port);

    if (1 == block_number) {
        status = sd_wait_card_not_busy(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("wait card not busy error\r\n", 0);
            goto error;
        }
    } else {
        status = sd_stop_transfer(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("stop transfer cmd send error\r\n", 0);
            goto error;
        }
    }

    while (msdc_card_is_present((msdc_port_t)sd_port)) {
        /*read card status*/
        status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
        if (NO_ERROR != status) {
            log_hal_msgid_error("read card status error\r\n", 0);
            goto error;
        }

        response = msdc_register_base->SDC_RESP0;

        if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK) &&
            ((response & SD_CARD_STATUS_STATE_BIT_MASK) >> SD_CARD_STATUS_STATE_BIT_SHIFT) == TRAN_STA) {
            break;
        }
    }

    msdc_reset((msdc_port_t)sd_port);

    sd_information.is_busy = false;

#ifdef HAL_DVFS_MODULE_ENABLED
#ifndef AIR_WIRELESS_MIC_ENABLE
    /*unlock dvfs before end transfer.*/
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif
#endif

    return HAL_SD_STATUS_OK;

error:

    msdc_dma_disable((msdc_port_t)sd_port);
    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;
}

hal_sd_status_t hal_sd_write_blocks_dma_blocking(hal_sd_port_t sd_port, const uint32_t *write_buffer,  uint32_t write_address, uint32_t block_number)
{
    sd_internal_status_t status = NO_ERROR;
    uint32_t response = 0;
    uint32_t write_command = 0;
    uint32_t block_multiplier = 0;
    MSDC_REGISTER_T *msdc_register_base;

    msdc_register_base = MSDC0_REG;

    if (sd_information.is_write_protection) {
        log_hal_msgid_error("card is write protection.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)write_buffer,block_number,&block_multiplier);
    if (status != NO_ERROR) {
        return status;
    }

    write_command = ((block_number > 1) ? MSDC_COMMAND25 : MSDC_COMMAND24) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, write_command, (write_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("write cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("sd card status error\r\n", 0);
        goto error;
    }

    /*start DMA transcation.*/
    msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

    status = sd_wait_data_ready_dma(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("msdc wait dma ready error\r\n", 0);
        goto error;
    }

    msdc_dma_disable((msdc_port_t)sd_port);

    if (1 < block_number) {
        status = sd_stop_transfer(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("stop cmd send error\r\n", 0);
            goto error;
        }

    } else if (1 ==  block_number) {
        status = sd_wait_card_not_busy(sd_port);
        if (status != NO_ERROR) {
            log_hal_msgid_error("wait sd card not busy error\r\n", 0);
            goto error;
        }
    }

    while (msdc_card_is_present((msdc_port_t)sd_port)) {
        /*read card status*/
        status = sd_send_command(sd_port, MSDC_COMMAND13, sd_information.rca << COMMAND_RCA_ARGUMENT_SHIFT);
        if (NO_ERROR != status) {
            log_hal_msgid_error("read card status error\r\n", 0);
            goto error;
        }

        response = msdc_register_base->SDC_RESP0;

        /*check corresponds to buffer empty singaling on the bus*/
        if ((response & SD_CARD_STATUS_READ_FOR_DATA_BIT_MASK)) {
            break;
        }
    }

    msdc_reset((msdc_port_t)sd_port);

    sd_information.is_busy = false;

#ifdef HAL_DVFS_MODULE_ENABLED
    /*unlock dvfs before end transfer.*/
#ifndef AIR_WIRELESS_MIC_ENABLE
    msdc_dvfs_unlock_current((msdc_port_t)sd_port);
#endif
#endif

    return HAL_SD_STATUS_OK;

error:

    msdc_dma_disable((msdc_port_t)sd_port);
    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;
}
#endif

hal_sd_status_t hal_sd_read_blocks_dma(hal_sd_port_t sd_port, uint32_t *read_buffer, uint32_t read_address, uint32_t block_number)
{
    sd_dma_interrupt_context_t context;
    sd_internal_status_t status = NO_ERROR;
    uint32_t read_command = 0;
    uint32_t block_multiplier = 0;
    MSDC_REGISTER_T *msdc_register_base;

    msdc_register_base = MSDC0_REG;

    if (NULL == msdc_config[sd_port].msdc_sd_callback) {
        log_hal_msgid_error("msdc_sd_dma_interrupt_callback null\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)read_buffer,block_number,&block_multiplier);
    if (status != NO_ERROR) {
        return status;
    }

    read_command = ((block_number > 1) ? MSDC_COMMAND18 : MSDC_COMMAND17) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, read_command, (read_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("read blk cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("card status error\r\n", 0);
        goto error;
    }

    /*save the transfer context using in dma interrupt*/
    context.sd_current_write_read_block_num = block_number;
    sd_save_dma_interrupt_context(sd_port, &context);
    /*enable msdc data interrupt*/
    msdc_register_base->MSDC_INTEN |= (MSDC_INT_XFER_COMPL_MASK | MSDC_INT_DXFER_DONE_MASK | MSDC_INT_DATTMO_MASK | MSDC_INT_DATCRCERR_MASK);
    msdc_nvic_set((msdc_port_t)sd_port, true);

#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sleep_manager_lock_sleep(sd_sleep_handle[(msdc_port_t)sd_port]);
#endif

    /*start DMA transcation.*/
    msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

    return HAL_SD_STATUS_OK;

error:

    msdc_dma_disable((msdc_port_t)sd_port);
    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;

}

hal_sd_status_t hal_sd_write_blocks_dma(hal_sd_port_t sd_port, const uint32_t *write_buffer,  uint32_t write_address, uint32_t block_number)
{
    sd_dma_interrupt_context_t context;
    sd_internal_status_t status = NO_ERROR;
    uint32_t write_command = 0;
    uint32_t block_multiplier = 0;
    MSDC_REGISTER_T *msdc_register_base;

    msdc_register_base = MSDC0_REG;

    if (NULL == msdc_config[sd_port].msdc_sd_callback) {
        log_hal_msgid_error("msdc_sd_dma_interrupt_callback null\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (sd_information.is_write_protection) {
        log_hal_msgid_error("card is write protection.\r\n", 0);

        return HAL_SD_STATUS_ERROR;
    }

    status = sd_read_write_blocks_dma_init(sd_port,(uint32_t)write_buffer,block_number,&block_multiplier);
    if (status != NO_ERROR) {
        return status;
    }

    write_command = ((block_number > 1) ? MSDC_COMMAND25 : MSDC_COMMAND24) | (SD_BLOCK_LENGTH << SDC_CMD_LEN_OFFSET);
    status = sd_send_command(sd_port, write_command, (write_address * block_multiplier));
    if (status != NO_ERROR) {
        log_hal_msgid_error("write blk cmd send error\r\n", 0);
        goto error;
    }

    status = sd_check_card_status(sd_port);
    if (status != NO_ERROR) {
        log_hal_msgid_error("card status error\r\n", 0);
        goto error;
    }

    /*save the transfer context using in dma interrupt*/
    context.sd_current_write_read_block_num = block_number;
    sd_save_dma_interrupt_context(sd_port, &context);
    /*enable msdc data interrupt*/
    msdc_register_base->MSDC_INTEN |= (MSDC_INT_XFER_COMPL_MASK | MSDC_INT_DXFER_DONE_MASK | MSDC_INT_DATTMO_MASK | MSDC_INT_DATCRCERR_MASK);
    msdc_nvic_set((msdc_port_t)sd_port, true);

#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sleep_manager_lock_sleep(sd_sleep_handle[(msdc_port_t)sd_port]);
#endif

    /*start DMA transcation.*/
    msdc_register_base->DMA_CTRL |= MSDC_DMA_CTRL_START_MASK;

    return HAL_SD_STATUS_OK;

error:

    msdc_dma_disable((msdc_port_t)sd_port);
    sd_error_handle(sd_port, status, block_number);

    return HAL_SD_STATUS_ERROR;
}

hal_sd_status_t hal_sd_set_clock(hal_sd_port_t sd_port, uint32_t clock)
{
    uint32_t nvic_mask = 0;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }


    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    hal_nvic_save_and_set_interrupt_mask(&nvic_mask);
    if (sd_information.is_busy) {
        hal_nvic_restore_interrupt_mask(nvic_mask);
        return HAL_SD_STATUS_BUSY;
    } else {
        sd_information.is_busy = true;
    }
    hal_nvic_restore_interrupt_mask(nvic_mask);
    if (((!sd_information.is_high_speed) && (clock > SD_DEFAULT_SPEED_MAX)) ||
        (clock > SD_HIGH_SPEED_MAX)) {

        msdc_set_output_clock((msdc_port_t)sd_port, SD_DEFAULT_SPEED_MAX);

        sd_information.is_busy = false;

        return HAL_SD_STATUS_ERROR;
    } else {
        if (false == sd_output_clock_tuning(sd_port, clock)) {
            log_hal_msgid_error("sd clock tuning error \r\n!", 0);
            sd_information.is_busy = false;
            return HAL_SD_STATUS_ERROR;
        }
    }

    sd_information.is_busy = false;

    return HAL_SD_STATUS_OK;
}

hal_sd_status_t hal_sd_get_clock(hal_sd_port_t sd_port, uint32_t *clock)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == clock) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    *clock = msdc_get_output_clock((msdc_port_t)sd_port);

    return HAL_SD_STATUS_OK;
}

hal_sd_status_t hal_sd_get_card_type(hal_sd_port_t sd_port, hal_sd_card_type_t *card_type)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == card_type) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    *card_type = sd_information.card_type;

    return HAL_SD_STATUS_OK;
}

hal_sd_status_t hal_sd_get_ocr(hal_sd_port_t sd_port, uint32_t *ocr)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == ocr) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    *ocr = sd_information.sd_ocr;

    return HAL_SD_STATUS_OK;
}


hal_sd_status_t hal_sd_get_card_status(hal_sd_port_t sd_port, uint32_t *card_status)
{
    sd_internal_status_t status = NO_ERROR;

    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }


    if (NULL == card_status) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    status = sd_get_card_status(sd_port, card_status);

    if (NO_ERROR != status) {
        sd_information.error_status = status;
        return HAL_SD_STATUS_ERROR;
    }

    return HAL_SD_STATUS_OK;
}

hal_sd_status_t hal_sd_get_erase_sector_size(hal_sd_port_t sd_port, uint32_t *erase_sector_size)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == erase_sector_size) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if ((sd_information.card_type == HAL_SD_TYPE_MMC_CARD) || (sd_information.card_type == HAL_SD_TYPE_MMC42_CARD)) {
        *erase_sector_size = sd_information.csd.erase_grp_size_mmc;
    } else if ((sd_information.card_type == HAL_SD_TYPE_SD20_HCS_CARD) ||
               (sd_information.card_type == HAL_SD_TYPE_SD20_LCS_CARD) ||
               (sd_information.card_type == HAL_SD_TYPE_SD_CARD)) {
        *erase_sector_size = sd_information.csd.write_bl_len;
    }

    return HAL_SD_STATUS_OK;
}

hal_sd_status_t hal_sd_get_cid(hal_sd_port_t sd_port, uint32_t *cid)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == cid) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    *(cid + 0) = sd_information.cid[0];
    *(cid + 1) = sd_information.cid[1];
    *(cid + 2) = sd_information.cid[2];
    *(cid + 3) = sd_information.cid[3];

    return HAL_SD_STATUS_OK;
}

hal_sd_status_t hal_sd_get_csd(hal_sd_port_t sd_port, uint32_t *csd)
{
    if (NO_ERROR != sd_check_msdc_port_valid(sd_port)) {
        log_hal_msgid_error("invalid msdc port\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (NULL == csd) {
        log_hal_msgid_error("parameter error\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    if (false == sd_information.is_initialized) {
        log_hal_msgid_error("card not initialize.\r\n", 0);
        return HAL_SD_STATUS_ERROR;
    }

    *(csd + 0) = sd_csd[0];
    *(csd + 1) = sd_csd[1];
    *(csd + 2) = sd_csd[2];
    *(csd + 3) = sd_csd[3];

    return HAL_SD_STATUS_OK;
}

#endif /*HAL_SD_MODULE_ENABLE*/

