// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: delay.c
//            tempo em espera
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


void Delay40us(void) {
    unsigned char i;
    for (i = 0; i < 5; i++); //valor aproximado
}

void Delay_ms(unsigned int t) {
    unsigned char i, j;
    for (j = 0; j < t; j++) {
        for (i = 0; i < 25; i++) {
            Delay40us();
        }
    }

}

void Delay2ms(void) {
    unsigned char i;
    for (i = 0; i < 50; i++) {
        Delay40us();
    }
}

void Delay10ms(void) {
    unsigned char i;
    for (i = 0; i < 250; i++) {
        Delay40us();
    }
}
