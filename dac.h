// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: dac.h
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

#ifndef DAC_H
#define	DAC_H

#include "i2c.h"

#define DAC_ADDR 0b01100001

void dacInit(void);
void dacWrite(int valor);

#endif	/* DAC_H */

