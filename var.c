// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: var.c
//            Header menu
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

#include "var.h"
#include "i2c.h"
#include "rtc.h"
#include "stateMachine.h"

#define MemAddr 0x68       //0b01010111
#define DefaultLanguage 0 //0-Portuguese 1-English
#define Hiin 512
#define Lowin 15
#define Timein 0 //0=30 1=60

void varInit(void) {
    i2cinit();
    RTC_Init();
    if (RTC_ReadParam(rtcINIT) != 0xF0);
    {

        RTC_SetParam(rtcINIT, 0xF0);

        RTC_SetParam(rtcSTATEANTANT, 0);
        RTC_SetParam(rtcSTATEANT, 0);
        RTC_SetParam(rtcSTATE, 0);

        RTC_SetParam(rtcLANGUAGE, DefaultLanguage);
        RTC_SetParam(rtcTIME, Timein);

        setAlarmLevel1(150);
        setAlarmLevel2(150);

        setHiAlarm1(Hiin);
        setLowAlarm1(Lowin);
        setHiAlarm2(Hiin);
        setLowAlarm2(Lowin);
    }
}

unsigned char getState(void) {
    return (RTC_ReadParam(rtcSTATE));
}

void setState(unsigned char newState) {
    RTC_SetParam(rtcSTATEANTANT, RTC_ReadParam(rtcSTATEANT));
    RTC_SetParam(rtcSTATEANT, getState());
    RTC_SetParam(rtcSTATE, newState);
}

char getstateAnt(void) {
    return (RTC_ReadParam(rtcSTATEANT));
}

char getstateAntAnt(void) {
    return (RTC_ReadParam(rtcSTATEANTANT));
}

char getLanguage(void) {
    return RTC_ReadParam(rtcLANGUAGE);
}

void setLanguage(char newLanguage) {
    RTC_SetParam(rtcLANGUAGE, newLanguage % 2); //usando resto pra evitar colocar valor errado
}

unsigned char getTime(void) {
    return RTC_ReadParam(rtcTIME);
}

void setTime(unsigned char newTime) {
    unsigned char time;

    if (newTime == 1) {
        time = 60;
    } else
        time = 30;

    RTC_SetParam(rtcTIME, time);
}

/////////////////////////////////////////////////////

short int getAlarmLevel1(void) {
    short int valor = 0;
    valor = RTC_ReadParam(rtcInALARM1);
    valor = valor + (RTC_ReadParam(rtcInALARM11) << 8);
    return valor;
}

void setAlarmLevel1(short int newAlarmLevel) {
    unsigned char b0, b1;
    b0 = 0b0000000011111111 & newAlarmLevel;
    b1 = (0b1111111100000000 & newAlarmLevel) >> 8;
    RTC_SetParam(rtcInALARM1, b0);
    RTC_SetParam(rtcInALARM11, b1);
}

short int getHiAlarm1(void) {
    short int valor = 0;
    valor = RTC_ReadParam(rtcHIALARM1);
    valor = valor + (RTC_ReadParam(rtcHIALARM11) << 8);
    return valor;
}

short int getLowAlarm1(void) {
    short int valor = 0;
    valor = RTC_ReadParam(rtcLOWALARM1);
    valor = valor + (RTC_ReadParam(rtcLOWALARM11) << 8);
    return valor;
}

void setHiAlarm1(short int newHiAlarm) {
    unsigned char b0, b1;
    b0 = 0b0000000011111111 & newHiAlarm;
    b1 = (0b1111111100000000 & newHiAlarm) >> 8;
    RTC_SetParam(rtcHIALARM1, b0);
    RTC_SetParam(rtcHIALARM11, b1);
}

void setLowAlarm1(short int newLowAlarm) {
    unsigned char b0, b1;
    b0 = 0b0000000011111111 & newLowAlarm;
    b1 = (0b1111111100000000 & newLowAlarm) >> 8;
    RTC_SetParam(rtcLOWALARM1, b0);
    RTC_SetParam(rtcLOWALARM11, b1);
}

//////////////////////////////////////////////////

short int getAlarmLevel2(void) {
    short int valor = 0;
    valor = RTC_ReadParam(rtcInALARM2);
    valor = valor + (RTC_ReadParam(rtcInALARM22) << 8);
    return valor;
}

void setAlarmLevel2(short int newAlarmLeve2) {
    unsigned char b0, b1;
    b0 = 0b0000000011111111 & newAlarmLeve2;
    b1 = (0b1111111100000000 & newAlarmLeve2) >> 8;
    RTC_SetParam(rtcInALARM2, b0);
    RTC_SetParam(rtcInALARM22, b1);
    ;
}

short int getHiAlarm2(void) {
    short int valor = 0;
    valor = RTC_ReadParam(rtcHIALARM2);
    valor = valor + (RTC_ReadParam(rtcHIALARM22) << 8);
    return valor;
}

void setHiAlarm2(short int newHiAlarm) {
    unsigned char b0, b1;
    b0 = 0b0000000011111111 & newHiAlarm;
    b1 = (0b1111111100000000 & newHiAlarm) >> 8;
    RTC_SetParam(rtcHIALARM2, b0);
    RTC_SetParam(rtcHIALARM22, b1);
}

short int getLowAlarm2(void) {
    short int valor = 0;
    valor = RTC_ReadParam(rtcLOWALARM2);
    valor = valor + (RTC_ReadParam(rtcLOWALARM22) << 8);
    return valor;
}

void setLowAlarm2(short int newLowAlarm) {
    unsigned char b0, b1;
    b0 = 0b0000000011111111 & newLowAlarm;
    b1 = (0b1111111100000000 & newLowAlarm) >> 8;
    RTC_SetParam(rtcLOWALARM2, b0);
    RTC_SetParam(rtcLOWALARM22, b1);
}
