// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: stdio.c
//            biblioteca de escrita LCD
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


#include "lcd.h"

void printf(char txt[16]) {
    int i;
    for (i = 0; i < 16; i++) {
        lcdData(txt[i]);
    }
}
