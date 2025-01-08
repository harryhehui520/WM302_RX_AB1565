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
/* Airoha restricted information */

/****************************************************************************
 * Header Files
 ****************************************************************************/


#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "assert.h"
#include <hal_platform.h>
#include "hal_gpio.h"
#include "hal_i2c_master.h"
#include "hal_pinmux_define.h"
//#include <timer.h>
#include "string.h"

#include "aacp_i2c.h"
#include "mfi_coprocessor_log.h"
#include "memory_attribute.h"

#ifdef HAL_I2C_MASTER_FRATURE_NONE_BLOCKING

/****************************************************************************
 * Macros
 ****************************************************************************/

#define CERT_READ_UNIT          (128)
#define AACP_I2C_ADDR           (0x10)

#define MAX_DELAY_TIMES         (600/portTICK_RATE_MS)

#define PRE_WAIT_I2C()              \
    do {                            \
        xSemaphoreTake(g_i2c_semaphore, 1);  \
        s_callback_result = HAL_I2C_EVENT_SUCCESS;  \
    } while (0)

#define WAIT_I2C()                      \
    do {                                \
        if (pdTRUE!= xSemaphoreTake(g_i2c_semaphore, MAX_DELAY_TIMES)){\
            s_callback_result = HAL_I2C_EVENT_TIMEOUT_ERROR;\
        }                                                   \
    } while (0)


/****************************************************************************
 * Static Variables
 ****************************************************************************/

extern hal_i2c_port_t g_mfi_i2c_port;
extern hal_gpio_pin_t g_mfi_i2c_scl_pin;
extern hal_gpio_pin_t g_mfi_i2c_sda_pin;
extern uint8_t g_mfi_i2c_scl_pinmux;
extern uint8_t g_mfi_i2c_sda_pinmux;

static SemaphoreHandle_t g_i2c_semaphore = NULL;
static char             s_aacp_mod_init = 0;
static hal_i2c_send_to_receive_config_ex_no_busy_t  g_i2c_config = { {0}, NULL, NULL, {0}};
static volatile hal_i2c_callback_event_t    s_callback_result = HAL_I2C_EVENT_SUCCESS;
static ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t       s_read_addr[2];
static ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t       s_send_data[CERT_READ_UNIT];

/****************************************************************************
 * Local Functions
 ****************************************************************************/
static int _aacp_mod_initialize(void)
{
    if (s_aacp_mod_init) {
        return 0;
    }

    s_aacp_mod_init = 1;

    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_START_INIT, 0);

    g_i2c_semaphore = xSemaphoreCreateBinary();
    assert(g_i2c_semaphore != NULL);

//    hal_gpio_init(g_mfi_i2c_scl_pin);
//    hal_gpio_init(g_mfi_i2c_sda_pin);
//
//    hal_gpio_disable_pull(g_mfi_i2c_scl_pin);
//    hal_gpio_disable_pull(g_mfi_i2c_sda_pin);
//
//    hal_pinmux_set_function(g_mfi_i2c_scl_pin, g_mfi_i2c_scl_pinmux);
//    hal_pinmux_set_function(g_mfi_i2c_sda_pin, g_mfi_i2c_sda_pinmux);
    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_INIT, 4, g_mfi_i2c_scl_pin, g_mfi_i2c_sda_pin, g_mfi_i2c_scl_pinmux, g_mfi_i2c_sda_pinmux);
    if (g_mfi_i2c_scl_pin == 0xFF || g_mfi_i2c_sda_pin == 0xFF) {
        s_aacp_mod_init = 0;
        MFI_IIC_LOG_E(MFI_CP_LOG_IIC_INIT_FAILED, 0); /* Please config mfi i2c EPT. */
    }

    return 0;
}

static void i2c_callback(uint8_t slave_address, hal_i2c_callback_event_t event, void *user_data)
{
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_DMA_ISR_CB, 2, slave_address, event);
    if (event == HAL_I2C_NON_BLOCKING_FUNCTION_ERROR) {
        return;
    }
    s_callback_result = event;

    xSemaphoreGiveFromISR(g_i2c_semaphore, &xHigherPriorityTaskWoken);
}


/****************************************************************************
 * API Functions
 ****************************************************************************/
int aacp_i2c_wake(void)
{
    int ret = 0;

    /* use fack addr 0x0 to wake up mfi chip. */
    ret = aacp_i2c_write(0x0, NULL, 0);
    if (ret < 0) {
        MFI_IIC_LOG_E(MFI_CP_LOG_IIC_WAKE_FAILD, 2, ret, s_callback_result);
    }

    return ret;
}


int aacp_i2c_read(__u8 addr, __u8 *buf, unsigned int len)
{
    int i = 0;
    hal_i2c_status_t ret = HAL_I2C_STATUS_OK;

    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_READ_OP, 2, len, addr);

    if (len < 1 || len > CERT_READ_UNIT) {
        return -1;
    }

    if (!s_aacp_mod_init) {
        _aacp_mod_initialize();
    }

    memset(s_send_data, 0, CERT_READ_UNIT);
    s_read_addr[0] = addr;

    g_i2c_config.i2c_config.frequency = HAL_I2C_FREQUENCY_400K;
    g_i2c_config.i2c_callback = i2c_callback;
    g_i2c_config.user_data = NULL;
    g_i2c_config.i2c_send_to_receive_config_ex.slave_address = AACP_I2C_ADDR;
    g_i2c_config.i2c_send_to_receive_config_ex.send_data = s_read_addr;
    g_i2c_config.i2c_send_to_receive_config_ex.send_packet_length = 1;
    g_i2c_config.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = 1;

    g_i2c_config.i2c_send_to_receive_config_ex.receive_buffer = NULL;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_packet_length = 0;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = 0;

    for (i = 0; i < 3; i++) {
        PRE_WAIT_I2C();

        ret = hal_i2c_master_send_to_receive_dma_ex_none_blocking(g_mfi_i2c_port, &g_i2c_config);
        if (HAL_I2C_STATUS_OK != ret) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_SEND_DMA_FAILED, 3, s_read_addr[0], ret, s_callback_result);
            os_delay_us(3000);
            continue;
        }

        WAIT_I2C();

        if (s_callback_result != HAL_I2C_EVENT_SUCCESS) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_SEND_DMA_FAILED, 3, s_read_addr[0], ret, s_callback_result);
            os_delay_us(3000);
            continue;
        }

        break;
    }
    if (i >= 3) {
        return -1;
    }

    os_delay_us(10 * 1000);

    g_i2c_config.i2c_send_to_receive_config_ex.send_data = NULL;
    g_i2c_config.i2c_send_to_receive_config_ex.send_packet_length = 0;
    g_i2c_config.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = 0;

    g_i2c_config.i2c_send_to_receive_config_ex.receive_buffer = s_send_data;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_packet_length = 1;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = len;
    for (i = 0; i < 3; i++) {
        PRE_WAIT_I2C();

        ret = hal_i2c_master_send_to_receive_dma_ex_none_blocking(g_mfi_i2c_port, &g_i2c_config);
        if (HAL_I2C_STATUS_OK != ret) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_READ_DMA_FAILED, 3, s_read_addr[0], ret, s_callback_result);
            os_delay_us(3000);
            continue;
        }

        WAIT_I2C();

        if (s_callback_result != HAL_I2C_EVENT_SUCCESS) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_READ_DMA_FAILED, 3, s_read_addr[0], ret, s_callback_result);
            os_delay_us(3000);
            continue;
        }

        break;
    }

    len = s_callback_result == HAL_I2C_EVENT_SUCCESS ? len : 0;
    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_READ_LEN, 1, len);
    if (len > 0) {
        memcpy(buf, s_send_data, len);
    }

    return (s_callback_result == HAL_I2C_EVENT_SUCCESS ? len : -1);
}


int aacp_i2c_write(__u8 addr, const __u8 *buf, unsigned int len)
{
    hal_i2c_status_t ret = HAL_I2C_STATUS_OK;
    int8_t       i;

    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_WRITE_OP, 2, len, addr);

    if (len + 1 > CERT_READ_UNIT) {
        return -1;
    }

    if (!s_aacp_mod_init) {
        _aacp_mod_initialize();
    }

    s_send_data[0] = (uint8_t)addr;
    memcpy(&s_send_data[1], buf, len);

    g_i2c_config.i2c_config.frequency = HAL_I2C_FREQUENCY_400K;
    g_i2c_config.i2c_callback = i2c_callback;
    g_i2c_config.user_data = NULL;
    g_i2c_config.i2c_send_to_receive_config_ex.slave_address = AACP_I2C_ADDR;
    g_i2c_config.i2c_send_to_receive_config_ex.send_data = s_send_data;
    g_i2c_config.i2c_send_to_receive_config_ex.send_packet_length = 1;
    g_i2c_config.i2c_send_to_receive_config_ex.send_bytes_in_one_packet = len + 1;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_buffer = NULL;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_packet_length = 0;
    g_i2c_config.i2c_send_to_receive_config_ex.receive_bytes_in_one_packet = 0;

    for (i = 0; i < 3; i++) {
        PRE_WAIT_I2C();
        ret = hal_i2c_master_send_to_receive_dma_ex_none_blocking(g_mfi_i2c_port, &g_i2c_config);
        if (HAL_I2C_STATUS_OK != ret) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_SEND_DMA_FAILED, 3, s_read_addr, ret, s_callback_result);
            os_delay_us(3000);
            continue;
        }

        WAIT_I2C();

        if (s_callback_result != HAL_I2C_EVENT_SUCCESS) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_SEND_DMA_FAILED, 3, s_read_addr, ret, s_callback_result);
            os_delay_us(3000);
            continue;
        }

        break;
    }

    return (s_callback_result == HAL_I2C_EVENT_SUCCESS ? len : -1);
}


void os_delay_us(unsigned int us)
{
    vTaskDelay((us + 999) / 1000 / portTICK_RATE_MS);;
}

#else

/****************************************************************************
 * Macros
 ****************************************************************************/

#define I
#define O

#define CERT_READ_UNIT          (128)
#define AACP_I2C_ADDR           (0x10)

#define PRE_WAIT_DMA()              \
    do {                            \
        s_dma_waiting = 1;          \
        s_callback_result = HAL_I2C_EVENT_SUCCESS;  \
    } while (0)
#if 1
#define WAIT_DMA()                  \
    do {                            \
        while (s_dma_waiting) {     \
        }                           \
    } while (0)
#endif
#if 0
#define WAIT_DMA()                  \
    do {                            \
        while (i2c_is_busy()) {     \
            ;                       \
        }                           \
    } while (0)
#endif
/****************************************************************************
 * Static Variables
 ****************************************************************************/

extern hal_i2c_port_t g_mfi_i2c_port;
extern hal_gpio_pin_t g_mfi_i2c_scl_pin;
extern hal_gpio_pin_t g_mfi_i2c_sda_pin;
extern uint8_t g_mfi_i2c_scl_pinmux;
extern uint8_t g_mfi_i2c_sda_pinmux;

static char             s_aacp_mod_init = 0;
static hal_i2c_port_t          i2c_bus = HAL_I2C_MASTER_1;
static volatile int                         s_dma_waiting = 0;
static volatile hal_i2c_callback_event_t    s_callback_result = HAL_I2C_EVENT_SUCCESS;
static ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t       s_read_addr = 0;
static ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t       s_send_data[CERT_READ_UNIT] = { 0 };

/****************************************************************************
 * Local Functions
 ****************************************************************************/
#if 0
static hal_i2c_running_status_t s_running_status;
static bool i2c_is_busy()
{
    if (hal_i2c_master_get_running_status(i2c_bus, &s_running_status) != HAL_I2C_STATUS_OK) {
        return false;
    }
    if (s_running_status.running_status == HAL_I2C_STATUS_BUS_BUSY) {
        return true;
    }
    return false;
}
#endif

static void i2c_dma_isr(uint8_t slave_address, hal_i2c_callback_event_t event, void *user_data)
{
    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_DMA_ISR_CB, 2, slave_address, event);
    s_callback_result = event;
    s_dma_waiting = 0;
}

static void wire_i2c_bus_set(hal_i2c_port_t bus)
{
    i2c_bus = bus;
    hal_i2c_config_t i2c_config;
    i2c_config.frequency = HAL_I2C_FREQUENCY_400K;

    I;
    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_START_INIT, 0);
    hal_gpio_init(g_mfi_i2c_scl_pin);
    hal_gpio_init(g_mfi_i2c_sda_pin);

    hal_pinmux_set_function(g_mfi_i2c_scl_pin, g_mfi_i2c_scl_pinmux);
    hal_pinmux_set_function(g_mfi_i2c_sda_pin, g_mfi_i2c_sda_pinmux);

    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_INIT, 4, g_mfi_i2c_scl_pin, g_mfi_i2c_sda_pin, g_mfi_i2c_scl_pinmux, g_mfi_i2c_sda_pinmux);
    if (g_mfi_i2c_scl_pin == 0xFF || g_mfi_i2c_sda_pin == 0xFF) {
        s_aacp_mod_init = 0;
        MFI_IIC_LOG_E(MFI_CP_LOG_IIC_INIT_FAILED, 0); /* Please config mfi i2c EPT. */
    }

    if (HAL_I2C_STATUS_OK == hal_i2c_master_init(bus, &i2c_config)) {
        hal_i2c_master_register_callback(bus, i2c_dma_isr, NULL);
        MFI_IIC_LOG_I(MFI_CP_LOG_IIC_INIT_SUCCESS, 0);
    }
    O;
}


static int _aacp_mod_initialize(void)
{
    I;

    if (s_aacp_mod_init) {
        O;
        return 0;
    }

    s_aacp_mod_init = 1;

    // wire_i2c_bus_set(0);
    wire_i2c_bus_set(g_mfi_i2c_port);
    O;

    return 0;
}

#ifdef AACP_DEINIT
static int _aacp_mod_deinit(void)
{
    I;

    s_aacp_mod_init = 0;
    //vSemaphoreDelete(i2c_done_semaphore);
    O;

    return 0;
}
#endif

/**
 * Send an empty write to wake up AACP.
 *
 * @note This is needed because there is no API to get the NACK status from
 *       AACP at the moement. No matter AACP is responding ACK or NACK
 *       (Not-ACK) is received, the next request will work as expected.
 */
static void _aacp_wake(void)
{
    uint8_t     *local_buf = NULL;
    uint8_t      fake_addr = 0;
    int             n = 0;

    local_buf = s_send_data;
    local_buf[0] = fake_addr;
    PRE_WAIT_DMA();

    n = hal_i2c_master_send_dma(i2c_bus, AACP_I2C_ADDR, local_buf, 1);

    if (n == HAL_I2C_STATUS_OK) {
        WAIT_DMA();
    }
    if (n != HAL_I2C_STATUS_OK || s_callback_result != HAL_I2C_EVENT_SUCCESS) {
        MFI_IIC_LOG_E(MFI_CP_LOG_IIC_WAKE_FAILD, 2, n, s_callback_result);
        os_delay_us(1000);
    }
}


/****************************************************************************
 * API Functions
 ****************************************************************************/


int aacp_i2c_reset(void)
{
    return 0;
}


int aacp_i2c_wake(void)
{
    if (!s_aacp_mod_init) {
        _aacp_mod_initialize();
        //_aacp_detect_idle();
    }

    _aacp_wake();

    return 0;
}


int aacp_i2c_read(__u8 addr, __u8 *buf, unsigned int len)
{
    int                 read_len = 0;
    int                 i = 0;
    hal_i2c_status_t    n = 0;

    I;
    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_READ_OP, 2, len, addr);
    if (!s_aacp_mod_init) {
        _aacp_mod_initialize();
        //_aacp_detect_idle();
    }

    if (len < 1 || len > CERT_READ_UNIT) {
        O;
        return -1;
    }

    s_read_addr = addr;
    memset(s_send_data, 0, CERT_READ_UNIT);
    while ((read_len != len) && (i < 10)) {

        read_len = 0;
        //os_delay_us(3000);
        //vTaskSuspendAll();
        PRE_WAIT_DMA();

        n = hal_i2c_master_send_dma(i2c_bus, AACP_I2C_ADDR, &s_read_addr, 1);

        //n = hal_i2c_master_send_dma(i2c_bus, AACP_I2C_ADDR, &s_read_addr, 1);
        if (n == HAL_I2C_STATUS_OK) {
            WAIT_DMA();
        }
//        if (!xTaskResumeAll()) {
//            taskYIELD();
//        }
        //n = i2c_write_via_mcu(i2c_bus, AACP_I2C_ADDR, (uint8_t *)&addr, 1);
        if (n != HAL_I2C_STATUS_OK || s_callback_result != HAL_I2C_EVENT_SUCCESS) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_SEND_DMA_FAILED, 3, s_read_addr, n, s_callback_result);
            i++;
            os_delay_us(3000);
            continue;
        }
        /*
         * based on experiment, 3 ms is needed for the next read to work
         * properly.
         */
        os_delay_us(3000);
        PRE_WAIT_DMA();

        n = hal_i2c_master_receive_dma(i2c_bus, AACP_I2C_ADDR, s_send_data, len);

        if (n == HAL_I2C_STATUS_OK) {
            WAIT_DMA();
        }
        if (n != HAL_I2C_STATUS_OK || s_callback_result != HAL_I2C_EVENT_SUCCESS) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_READ_DMA_FAILED, 3, s_read_addr, n, s_callback_result);
            i++;
            read_len = 0;
            os_delay_us(3000);
        } else {
            read_len = len;
            memcpy(buf, s_send_data, len);
            break;
        }
    }
    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_READ_LEN, 1, read_len);
    O;
    return (read_len ? read_len : -1);
}


int aacp_i2c_write(__u8 addr, const __u8 *buf, unsigned int len)
{
    uint8_t     *local_buf = NULL;
    int         n = 0;
    int8_t       i;
    int ret = len;

    I;

    MFI_IIC_LOG_I(MFI_CP_LOG_IIC_WRITE_OP, 2, len, addr);
    if (!s_aacp_mod_init) {
        _aacp_mod_initialize();
    }

    if (len + 1 > CERT_READ_UNIT) {
        return -1;
    }

    local_buf = s_send_data;
    local_buf[0] = (uint8_t)addr;
    memcpy(local_buf + 1, buf, len);
    //os_delay_us(3000);
//    vTaskSuspendAll();
    for (i = 0; i < 10; i++) {
        PRE_WAIT_DMA();

        n = hal_i2c_master_send_dma(i2c_bus, AACP_I2C_ADDR, local_buf, len + 1);

        if (n == HAL_I2C_STATUS_OK) {
            WAIT_DMA();
        }
        if (n != HAL_I2C_STATUS_OK || s_callback_result != HAL_I2C_EVENT_SUCCESS) {
            MFI_IIC_LOG_E(MFI_CP_LOG_IIC_SEND_DMA_FAILED, 3, addr, n, s_callback_result);
            ret = HAL_I2C_STATUS_ERROR;
            os_delay_us(3000);
        } else {
            ret = len;
            break;
        }
    }

    O;

    return ret;
}


void os_delay_us(unsigned int us)
{
    vTaskDelay((us + 999) / 1000 / portTICK_RATE_MS);;
}

#endif
