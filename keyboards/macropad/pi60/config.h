// Copyright 2022 ziptyze (@ziptyze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define NUM_ENCODER 1

#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD0

#define I2C0_SDA_PIN GP20
#define I2C0_SCL_PIN GP21


#define I2C1_SDA_PIN GP20
#define I2C1_SCL_PIN GP21

#define RGB_DI_PIN GP19
#define RGBLED_NUM 20
#define RGB_MATRIX_LED_COUNT 20
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define NOP_FUDGE 0.4

#define WS2812_PIO_USE_PIO1


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED 25 // Specify a optional status led by GPIO number which blinks when entering the bootloader
