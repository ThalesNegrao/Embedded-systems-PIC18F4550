// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso / Thales Maia Mendonça Negrão
// -----------------------------------------------------------------------
//   Arquivo: main.c
//            Corpo do programa
//   Autor:   Lucas Wacho Precioso
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "pic18f45xx.h"
#include "pwm.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "ssd.h"
#include "keypad.h"
#include "event.h"
#include "var.h"
#include "output.h"
#include "stateMachine.h"
#include "serial.h"
#include "rtc.h"
#include "i2c.h"
#include "delay.h"
#include "dac.h"
#include "led.h"

void main(void) {
    unsigned char event, cont = 0;

    //inicilizar
    adcInit();
    lcdInit();
    serialInit();
    kpInit();
    eventInit();
    timerInit();
    varInit();
    outputInit();
    smInit();
    i2cinit();
    RTC_Init();
    dacInit();
    initLed();

    for (;;) {
        timerReset(getTime()); //Inicio da maquina

        kpADebounce(); //Debouce do teclado

        setAlarmLevel1(adcRead(0));

        event = eventRead();

        if (event != EV_NOEVENT) {
            smLoop(event);
        }

        if (getState() == RTC) {
            if (cont == 10) {
                outputPrint(getState(), getLanguage(), EV_NOEVENT);
                cont = 0;
            } else {
                cont++;
            }
        }

        timerWait(); //Fim da maquina
    }
}
