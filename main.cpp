/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <lcd.hpp>

DigitalOut led(LED1);

int main() {
    software_lcd lcd;
    lcd.clear();
    lcd.puts("Hello world");
    lcd.set_flags(LCD_CURSOR | LCD_CURSOR_BLINK);

    while (true) {
        ThisThread::sleep_for(200ms);
        led = !led;
    }
}
