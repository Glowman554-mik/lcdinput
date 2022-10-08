/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <lcd.hpp>

extern "C" {
    #include <calc.h>
}

#define SLEEP_TIME 100ms

DigitalIn up_button(PB_0, PullDown);
DigitalIn down_button(PB_3, PullDown);
DigitalIn ok_button(PB_4, PullDown);

int main() {
    software_lcd lcd;
    lcd.set_flags(LCD_CURSOR);

    
    char input[32];
    memset(input, ' ', sizeof(input));
    int idx = 0;


    while (true) {
        if (up_button) {
            input[idx]++;
        } else if(down_button) {
            input[idx]--;
        } else if (ok_button) {
            if (input[idx] == '=') {
                input[idx] = 0;
                
                char buf[16] = { 0 };
                sprintf(buf, "= %d", calc(input));
                lcd.puts(buf);

                idx = 0;
                memset(input, ' ', sizeof(input));
    
                ThisThread::sleep_for(SLEEP_TIME);
                goto skip_sleep_and_update;
            } else {
                idx++;
            }
        } else {
            goto skip_sleep_and_update;
        }

        lcd.clear();

        for (int i = 0; i < idx + 1; i++) {
            lcd.putc(input[i]);
        }
        lcd.cursor(idx);
        
        ThisThread::sleep_for(SLEEP_TIME);
    skip_sleep_and_update:;
    }
}
