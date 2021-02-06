#ifndef _KEYPAD_IS31FL3218_H
#define _KEYPAD_IS31FL3218_H

#include <stdbool.h>
#include <stdint.h>

#define IS31FL3218_ADDRESS 0xA8
#define IS31FL3218_CHANNEL_COUNT 18

#define IS31FL3218_REG_SHUTDOWN 0x00
#define IS31FL3218_REG_PWM_01 0x01
#define IS31FL3218_REG_PWM_02 0x02
#define IS31FL3218_REG_PWM_03 0x03
#define IS31FL3218_REG_PWM_04 0x04
#define IS31FL3218_REG_PWM_05 0x05
#define IS31FL3218_REG_PWM_06 0x06
#define IS31FL3218_REG_PWM_07 0x07
#define IS31FL3218_REG_PWM_08 0x08
#define IS31FL3218_REG_PWM_09 0x09
#define IS31FL3218_REG_PWM_10 0x0A
#define IS31FL3218_REG_PWM_11 0x0B
#define IS31FL3218_REG_PWM_12 0x0C
#define IS31FL3218_REG_PWM_13 0x0D
#define IS31FL3218_REG_PWM_14 0x0E
#define IS31FL3218_REG_PWM_15 0x0F
#define IS31FL3218_REG_PWM_16 0x10
#define IS31FL3218_REG_PWM_17 0x11
#define IS31FL3218_REG_PWM_18 0x12
#define IS31FL3218_REG_LED_1 0x13
#define IS31FL3218_REG_LED_2 0x14
#define IS31FL3218_REG_LED_3 0x15
#define IS31FL3218_REG_UPDATE 0x16
#define IS31FL3218_REG_RESET 0x17

bool is31fl3218_init();
void is31fl3218_set_brightness(uint8_t b);
void is31fl3218_set_leds(uint16_t leds);
void is31fl3218_update();

#endif