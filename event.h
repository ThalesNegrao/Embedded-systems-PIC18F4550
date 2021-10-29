// -----------------------------------------------------------------------
//   Copyright (C) Thales Maia Mendonça Negrão
// -----------------------------------------------------------------------
//   Arquivo: event.h
//            mmonitoramento de um sinal analogico evento
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


#ifndef EVENT_H
#define	EVENT_H

enum {
    EV_NOEVENT, //0
    EV_RIGHT, //1
    EV_DOWN, //2
    EV_LEFT, //3
    EV_UP, //4
    EV_ENTER, //5
    HiAlalt, //6
    LoAlalt, //7
    Datealt, //8
    Hialarm1, //9
    Lowalarm1, //10
    ALARM1OK, //11
    Hialarm2, //12
    Lowalarm2, //13
    ALARM2OK, //14
};

enum {
    ALARME1ALTO,
    ALARME1BAIXO,
    ALARME2ALTO,
    ALARME2BAIXO
};

void eventInit(void);
unsigned char eventRead(void);
void serialCheck(void);
unsigned char serialcommand(char serialR);
void serialAlarm(unsigned char event);

#endif	/* EVENT_H */

