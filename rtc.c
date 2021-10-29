// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: rtc.c
//            biblioteca relógio
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

#include "rtc.h"
#include "lcd.h"

#define YEAR 17
#define MONTH 11
#define DAY 1
#define HOUR 03
#define MINUTE 02
#define SECOND 55
#define DATE 27

void RTC_Init(void) {
    i2cinit();
    // init RTC parameters
        RTC_SetParam(rtcSECOND, SECOND);
        RTC_SetParam(rtcMINUTE, MINUTE);
        RTC_SetParam(rtcHOUR, HOUR);
        RTC_SetParam(rtcDAY, DAY);
        RTC_SetParam(rtcDATE, DATE);
        RTC_SetParam(rtcMONTH, MONTH);
        RTC_SetParam(rtcYEAR, YEAR);
    i2cwrite(RTC_ADDR, rtcSECOND, 0x56);


}

void RTC_SetParam(rtcParam p, unsigned char v) {
    unsigned char BCD = 0;

    if ((p >= rtcSECOND) && (p <= rtcYEAR)) {
        if (v < 100) {
            BCD = ((v / 10) % 10) << 4;
            BCD = BCD + (v % 10);
            i2cwrite(RTC_ADDR, p, BCD);
        } else {
            return;
        }
    } else {
        i2cwrite(RTC_ADDR, p, v);
    }
}

unsigned char RTC_ReadParam(rtcParam p) {
    unsigned char BCD = 0, valor = 0;

    BCD = ic2read(RTC_ADDR, p);

    if ((p >= rtcSECOND) && (p <= rtcYEAR)) {
        valor = BCD & 0b00001111;
        valor = valor + ((BCD & 0b11110000)>>4)*10;
        return valor;
    }
    return BCD;
}
