// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: i2c.c
//            I2C comunication
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

#include "i2c.h"
#include "lcd.h"
#include "pic18f45xx.h"

void i2cinit(void) {

    TRISB = TRISB | 0b00000011;

    //ADCON1 &= 0xf0;
    //ADCON1 = 0x05;

    SSPSTAT = 0b10000000;
    SSPADD = 0x63;
    SSPCON1 = 0b00101000;
    SSPCON2 = 0b01000000;
}

void i2cwrite(char dev, char addr, char data) {
    /*    if (SSPCON1 & 0x80)
            SSPCON1 &= ~0x80;
        if (SSPCON1 & 0x40)
            SSPCON1 &= ~0x40;
     */
    while (SSPCON2 & 0b0010111);
    SSPCON2 |= 0x01; //manda start
    //PIR1 &= ~0x80;
    while (SSPCON2 & 0x01); //verifica se mandou o 0
    //PORTA |= 0x10;
    // PORTA &= ~0x10;

    SSPBUF = (dev << 1)&0b11111110; //manda o dev e da o shift e coloca o bit0 em 0
    while (SSPSTAT & 0b100);
    SSPBUF = addr;
    while (SSPSTAT & 0b100);
    SSPBUF = data;
    while (SSPSTAT & 0b100);

    SSPCON2 = SSPCON2 | 0b00000100; //manda stop
    //while (SSPCON2 | 0b00000100);
}

char ic2read(char dev, char addr) {
    char read;

    //SSPCON1 &= 0b00111111;


    while (SSPCON2 & 0b0010111);
    SSPCON2 = SSPCON2 | 0b00000001; //manda start
    while (SSPCON2 & 0b00000001); //verifica se mandou o start

    SSPBUF = (dev << 1) & 0b11111110; //manda o dev e da o shift e coloca o bit0 em 0
    while (SSPSTAT & 0b100);

    SSPBUF = addr;
    while (SSPSTAT & 0b100);


    SSPCON2 = SSPCON2 | 0b00000010; //manda repeated start
    while (SSPCON2 & 0b00000010); //verifica se mandou o repeated start

    SSPBUF = (dev << 1) | 0b00000001; //manda o dev e da o shift e coloca o bit0 em 1
    while (SSPSTAT & 0b100);

    SSPCON2 = SSPCON2 | 0b00001000; //entrada
    while ((SSPSTAT & 0b00000001) == 0);

    read = SSPBUF;

    SSPCON2 = SSPCON2 | 0b00100000; //nack
    SSPCON2 = SSPCON2 | 0b00010000;
    while (SSPCON2 & 0b00010000);

    SSPCON2 = SSPCON2 | 0b00000100; //manda stop

    return read;
}
