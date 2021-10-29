// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: dac.c
//            biblioteca relógio e memória
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


#include "dac.h"
#include "pic18f45xx.h"

void dacInit(void) {
    i2cinit();
}

void dacWrite(int valor) {
    unsigned char valor1, valor2;

    valor2 = valor;
    valor1 = (valor >> 8);
    i2cwrite(DAC_ADDR, valor1, valor2);
}

