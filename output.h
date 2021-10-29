// -----------------------------------------------------------------------
//   Copyright (C) Thales Maia Mendonça Negrão
// -----------------------------------------------------------------------
//   Arquivo: output.h
//            Look up table para mostrar no LCD
//   Autor:   Thales Maia Mendonça Negrão
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


#ifndef OUTPUT_H
#define	OUTPUT_H

void outputInit(void);
void outputPrint(char numTela, char idioma, char event);

#endif	/* OUTPUT_H */

