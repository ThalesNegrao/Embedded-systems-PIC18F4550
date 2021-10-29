// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: stateMachine.h
//            Header maquina de estado do programa
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


#ifndef STATEMACHINE_H
#define	STATEMACHINE_H


//estados da maquina de Estados

enum {
    Welcome, //0
    Menu, //1
    SetLenguage, //2
    SeleLanguage, //3
    SetHigh1, //4
    SetLow1, //5
    SetHigh2, //6
    SetLow2, //7
    SetTime, //8
    SetUnit, //9
    RTC, //10
    Alarm //11
};

void smInit(void);
void smLoop(char);


#endif	/* STATEMACHINE_H */

