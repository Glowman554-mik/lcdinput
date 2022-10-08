/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <lcd.hpp>

DigitalIn up_button(PB_0, PullDown);
DigitalIn down_button(PB_3, PullDown);
DigitalIn ok_button(PB_4, PullDown);

char input[] = "                ";
int idx = 0;

void update(software_lcd& lcd) {
    lcd.clear();

    for (int i = 0; i < idx + 1; i++) {
        lcd.putc(input[i]);
    }
}

int main() {
    software_lcd lcd;

    while (true) {
        if (up_button) {
            input[idx]++;
        } else if(down_button) {
            input[idx]--;
        } else if (ok_button) {
            idx++;
        } else {
            goto skip_sleep_and_update;
        }

        update(lcd);
        ThisThread::sleep_for(200ms);
    skip_sleep_and_update:;
    }
}
