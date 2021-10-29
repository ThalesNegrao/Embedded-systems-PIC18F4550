// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: led.c
//            Acender ou apagar LEDs na porta digital
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

#include "pic18f45xx.h"

void initLed(void) {
    BitClr(TRISC, 0);
    BitClr(PORTC, 0);
    BitClr(TRISA, 4);
    BitClr(PORTA, 4);
}

void ledON(int x) {
    if (x >= 1)BitSet(PORTC, 0);
    if (x <= 0)BitSet(PORTA, 4);
}

void ledOFF(int x) {
    if (x >= 1)BitClr(PORTC, 0);
    if (x <= 0)BitClr(PORTA, 4);
}
