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

#include "keypad.h"
#include "event.h"
#include "pic18f45xx.h"
#include "serial.h"
#include "var.h"
#include "rtc.h"
#include "led.h"

#define KeypressSpeed 50 //velocidade da repetição da tecla pressionada

static unsigned char key_ant;
unsigned char string[9] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char posit = 0;
unsigned char Keypress = 0;
unsigned int valR = 0;
static unsigned char alarm = 0; /* BIT 0 ALARME 1 ALTO
                                 * BIT 1 AlARME 1 BAIXO
                                 * BIT 2 ALARME 2 ALTO
                                 * BIT 3 ALARME 2 BAIXO
                                 */

unsigned char checkalarm(void);

void eventInit(void) {
    key_ant = EV_NOEVENT; //aqui estava inicializa KPint()
}

unsigned char eventRead(void) {

    unsigned char key = EV_NOEVENT, serialR, alarmR;

    //Verifica eventos no alarme
    alarmR = checkalarm();
    if (alarmR != EV_NOEVENT) {
        serialAlarm(alarmR);
        return alarmR;
    }

    //Verifica eventos no teclado
    key = kpARead();
    if (key != key_ant) {
        key_ant = key;
        Keypress = 0;
        return key;
    } else {
        Keypress++;
        if (Keypress > KeypressSpeed) {
            Keypress = 10*Keypress/11;
            return key;
        }

    }

    //verifica eventos no serial
    serialR = serialRead();
    if (serialR != 0) {
        return serialcommand(serialR);
    }

    //se não tiver nenhum evento
    return EV_NOEVENT;
}

unsigned char checkalarm(void) {

    //ALARM 1
    if (getAlarmLevel1() >= getHiAlarm1()) {//verifica alarme alto
        if (BitTst(alarm, ALARME1ALTO)) {//verifica se o alarme ja estava alto
        } else {//se não estava no alarme alto antes
            BitSet(alarm, ALARME1ALTO); //indica alarme alto
            ledON(1);
            return Hialarm1;
        }
    } else {
        if (getAlarmLevel1() <= getLowAlarm1()) {//verifica alarme baixo
            if (BitTst(alarm, ALARME1BAIXO)) {//verifica se o alarme ja estava baixo antes
            } else {//se não estava no alarme alto antes
                BitSet(alarm, ALARME1BAIXO); //indica alarme baixo
                ledON(1);
                return Lowalarm1;
            }
        } else {
            if (BitTst(alarm, ALARME1ALTO) || BitTst(alarm, ALARME1BAIXO)) {// se estava alarme alto ou baixo anteriormente
                BitClr(alarm, ALARME1ALTO); //alarme alto normal
                BitClr(alarm, ALARME1BAIXO); //alarme baixo normal
                ledOFF(1);
                return ALARM1OK;
            }
        }
    }

    //ALARM 2
    if (getAlarmLevel2() >= getHiAlarm2()) {
        if (BitTst(alarm, ALARME2ALTO)) {
        } else {
            BitSet(alarm, ALARME2ALTO);
            ledON(2);
            return Hialarm2;
        }
    } else {
        if (getAlarmLevel2() <= getLowAlarm2()) {
            if (BitTst(alarm, ALARME2BAIXO)) {
            } else {
                BitSet(alarm, ALARME2BAIXO);
                ledON(2);
                return Lowalarm2;
            }
        } else {
            if (BitTst(alarm, ALARME2ALTO) || BitTst(alarm, ALARME2BAIXO)) {
                BitClr(alarm, ALARME2ALTO);
                BitClr(alarm, ALARME2BAIXO);
                ledOFF(2);
                return ALARM2OK;
            }
        }
    }
    return EV_NOEVENT;
}

unsigned char serialcommand(char serialR) {
    unsigned char j;

    switch (serialR) {
        case 'w':
        {
            serialR = 0;
            return EV_UP;
        }
        case 'a':
        {
            serialR = 0;
            return EV_LEFT;
        }
        case 's':
        {
            serialR = 0;
            return EV_DOWN;
        }
        case 'd':
        {
            serialR = 0;
            return EV_RIGHT;
        }
        case ' ':
        {
            serialR = 0;
            return EV_ENTER;
        }
        case '*':
        {
            for (j = 0; j < 8; j++) {
                string[j] = 0;
            }
            for (j = 0; j < (posit + 12); j++) {
                serialSend(8);
            }
            serialString("Digite comand:");
            posit = 0;
            string[posit] = serialR;
            posit = 1;
            return EV_NOEVENT;
        }
    }
    if (string[0] == '*') {
        string[posit] = serialR;
        serialSend(string[posit]);
        posit++;

        if (string[7] != 0) {
            serialSend(' ');

            switch (string[1]) {
                case 'H':
                {
                    if (string[2] == 'T') {//Temperatura alta
                        valR = (string[3] - 48)*10000;
                        valR = (string[4] - 48)*1000;
                        valR = (string[5] - 48)*100;
                        valR += (string[6] - 48)*10;
                        valR += (string[7] - 48);
                        setHiAlarm1(valR);
                        valR = 0;
                        serialString("Hi Al alt");
                        break;
                    }

                }
                case 'L':
                {
                    if (string[2] == 'T') {//Temperatura baixa
                        valR = (string[3] - 48)*10000;
                        valR = (string[4] - 48)*1000;
                        valR = (string[5] - 48)*100;
                        valR += (string[6] - 48)*10;
                        valR += (string[7] - 48);
                        setLowAlarm1(valR);
                        valR = 0;
                        serialString("Low Al Alt");
                        break;
                    }
                    if (string[2] == 'A') {//idioma
                        if (string[3] == 'N') {
                            if (string[4] == 'G') {
                                if (string[5] == 'p') {
                                    if (string[6] == 'o') {
                                        if (string[7] == 'r') {
                                            setLanguage(0);
                                            serialString("Lang:Pot");
                                            break;
                                        }
                                    }
                                }
                                if (string[5] == 'e') {
                                    if (string[6] == 'n') {
                                        if (string[7] == 'g') {
                                            setLanguage(1);
                                            serialString("Lang:eng");
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                case 'T':
                {
                    if (string[2] == 'I') {//tempo de aquisição
                        if (string[3] == 'M') {
                            if (string[4] == 'E') {
                                valR = string[6]*10;
                                valR += string[7];
                                if (valR <= 30) {
                                    setTime(0);
                                } else {
                                    setTime(1);
                                }
                                valR = 0;
                                serialString("set t alt");
                            }
                        }
                    }
                    break;
                }
                case 'D':
                {//DATA
                    valR = string[2]*10;
                    valR += string[3];
                    //RTC_SetParam(rtcDAY, valR); //valR dia
                    valR = string[4]*10;
                    valR += string[5];
                    //RTC_SetParam(rtcMONTH, valR); //valR mes
                    valR = string[6]*10;
                    valR += string[7];
                    //RTC_SetParam(rtcYEAR, valR); //valR ano
                    serialString("Date alt");
                    break;
                }
                case 'C':
                {//Relogio
                    valR = string[2]*10;
                    valR += string[3];
                    //RTC_SetParam(rtcHOUR, valR); //valR Horas
                    valR = string[4]*10;
                    valR += string[5];
                    //RTC_SetParam(rtcMINUTE, valR); //valR Minutos
                    valR = string[6]*10;
                    valR += string[7];
                    //RTC_SetParam(rtcSECOND, valR); //valR Segundos
                    serialString("Clock Alt");
                    break;
                }
            }
            posit = 0;
            for (j = 0; j < 9; j++) { //limpa o buffer
                string[j] = 0;
            }
        }
    }
    return EV_NOEVENT;
}

void serialAlarm(unsigned char event) {
    switch (event) {
        case Hialarm1:
        {
            serialString("Alerta de alarme 1 alto");
            serialSend(32);
            break;
        }
        case Hialarm2:
        {
            serialString("Alerta de alarme 2 alto");
            serialSend(32);
            break;
        }
        case Lowalarm1:
        {
            serialString("Alerta de alarme 1 baixo");
            serialSend(32);
            break;
        }
        case Lowalarm2:
        {
            serialString("Alerta de alarme 2 baixo");
            serialSend(32);
            break;
        }
        case ALARM1OK:
        {
            serialString("Alerta de alarme 1 normalizado");
            serialSend(32);
            break;
        }
        case ALARM2OK:
        {
            serialString("Alerta de alarme 2 normalizado");
            serialSend(32);
            break;
        }
    }
    serialString(" Date ");
    serialSend((RTC_ReadParam(rtcDATE) / 10) % 10 + 48);
    serialSend((RTC_ReadParam(rtcDATE)) % 10 + 48);
    serialSend('/');
    serialSend((RTC_ReadParam(rtcMONTH) / 10) % 10 + 48);
    serialSend((RTC_ReadParam(rtcMONTH)) % 10 + 48);
    serialSend('/');
    serialSend((RTC_ReadParam(rtcYEAR) / 10) % 10 + 48);
    serialSend((RTC_ReadParam(rtcYEAR)) % 10 + 48);
    serialSend(' ');
    serialSend(' ');
    serialSend(32);
    serialString(" Hora ");
    serialSend((RTC_ReadParam(rtcHOUR) / 10) % 10 + 48);
    serialSend((RTC_ReadParam(rtcHOUR)) % 10 + 48);
    serialSend(':');
    serialSend((RTC_ReadParam(rtcMINUTE) / 10) % 10 + 48);
    serialSend((RTC_ReadParam(rtcMINUTE)) % 10 + 48);
    serialSend(':');
    serialSend((RTC_ReadParam(rtcSECOND) / 10) % 10 +48);
    serialSend((RTC_ReadParam(rtcSECOND)) % 10 + 48);
    serialSend(' ');
    serialSend(' ');
}

//*HTXXXXX  - alarme alto xxx
//*LTXXXXX  - alarme baixo xxx
//*TIMEXXX  - Tempo de aquisição
//*D(DIA)(mes)(ano) -
//*C(hora)(min)(seg) -
//*LANG(port) ou (engl) - alterar idioma
