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

#ifndef RTC_H
#define RTC_H

#include "i2c.h"

/**
 * The RTC address on I2C bus
 */
#define RTC_ADDR 0x68

/**
 * RTC parameter type
 */
typedef enum{
    rtcSECOND,
    rtcMINUTE,
    rtcHOUR,
    rtcDAY,
    rtcDATE,
    rtcMONTH,
    rtcYEAR,
    rtcEND,
    rtcSTATE,
    rtcSTATEANT,
    rtcSTATEANTANT,
    rtcLANGUAGE,
    rtcTIME,
    rtcInALARM1,
    rtcInALARM11,
    rtcInALARM2,
    rtcInALARM22,
    rtcLOWALARM1,
    rtcLOWALARM11,
    rtcLOWALARM2,
    rtcLOWALARM22,
    rtcHIALARM1,
    rtcHIALARM11,
    rtcHIALARM2,
    rtcHIALARM22,
    rtcINIT
}rtcParam;

/**
 * @brief Initializes the external RTC.
 *
 * @warning This routine must be called before
 * any other.
 */
void RTC_Init(void);

/**
 * @brief Set a RTC internal parameter
 *
 * @param p RTC parameter
 * @param v The value to be changed to it.
 */
void RTC_SetParam(rtcParam p, unsigned char v);

/**
 * @brief Read a RTC internal parameter
 *
 * @param p RTC parameter
 * @return v The value read from RTC internal parameter.
 */
unsigned char RTC_ReadParam(rtcParam p);

#endif
