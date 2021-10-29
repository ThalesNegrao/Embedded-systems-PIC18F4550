// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: i2c.h
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

#ifndef I2C_H
#define	I2C_H

#include "pic18f45xx.h"


void i2cinit(void);
void i2cwrite(char dev, char addr, char data);
char ic2read(char dev, char addr);

#endif	/* I2C_H */

/*
enum { //Bits SSPCON2
    SEN,
    RSEN,
    PEN,
    RCEN,
    ACKEN,
    ACKDT,
    ACKSTAT,
    GCEN
};

enum {// Bits SSPSTAT
    BF,
    UA,
    RW,
    S,
    P,
    DA,
    CKE,
    SMP
};
 */
