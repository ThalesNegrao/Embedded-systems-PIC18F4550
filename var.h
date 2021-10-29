// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: var.h
//            Header menu
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


#ifndef VAR_H
#define	VAR_H

//unsigned char getMem(unsigned char addr);
//void setMem(unsigned char addr, unsigned char data);

void varInit(void);
unsigned char getState(void);
void setState(unsigned char newState);
unsigned char getTime(void);
void setTime(unsigned char newTime);
unsigned char getLanguage(void);
void setLanguage(unsigned char newLanguage);
short int getLowAlarm1(void);
void setLowAlarm1(short int newLowAlarm);
void setHiAlarm1(short int nwHiAlarm);
short int getHiAlarm1(void);
short int getLowAlarm2(void);
void setLowAlarm2(short int newLowAlarm);
void setHiAlarm2(short int nwHiAlarm);
short int getHiAlarm2(void);
unsigned char getstateAnt(void);
char getstateAntAnt(void);
short int getAlarmLevel1(void);
void setAlarmLevel1(int newAlarmLevel);
short int getAlarmLevel2(void);
void setAlarmLevel2(int newAlarmLevel);

#endif	/* VAR_H */
