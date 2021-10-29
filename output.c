// -----------------------------------------------------------------------
//   Copyright (C) Thales Maia Mendonça Negrão
// -----------------------------------------------------------------------
//   Arquivo: output.c
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

#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "rtc.h"
#include "event.h"

#define NUM_IDIOMAS 2
#define STATE_FIM 8
//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs1[STATE_FIM + 6][NUM_IDIOMAS] = {//primeira linha do LCD. Estados:
    {"Bem Vindo PBLE01", "Welcome - PBLE01"}, //0 Walcome
    {"<MENU>          ", "<MENU>          "}, //1 MENU
    {"Alterar idioma  ", "Change language "}, //2 SetLanguage
    {"Portugues       ", "English         "}, //3 SeleLanguage
    {"Tempe Alar alt-\0", "<Set High Temp>\0"}, //4 SetTempHi
    {"Tempe Alar bai-\0", "<Set Low Temp> \0"}, //5 SetTempLow
    {"Tempo de aquisic", "<Set Test Time> "}, //6 SetTimeAquis
    {"xxxxxxxxxxxxxxxx", "xxxxxxxxxxxxxxxx"}, //7 //não imprime nada por aqui
    {"ATENCAO  !!!    ", "ATENTION !!!    "}, //8 ALARM 1 Hi
    {"ATENCAO  !!!    ", "ATENTION !!!    "}, //9 ALARM 1 Low
    {"ATENCAO  !!!    ", "ATENTION !!!    "}, //10 ALARM 2 Hi
    {"ATENCAO  !!!    ", "ATENTION !!!    "}, //11 ALARM 2 Low
    {"ATENCAO  !!!    ", "ATENTION !!!    "}, //12 ALARM 1 OK
    {"ATENCAO  !!!    ", "ATENTION !!!    "}, //13 ALARM 2 OK
};
static char * msgs2[STATE_FIM + 6][NUM_IDIOMAS] = {//segunda linha do LCD. Estados
    {"Pressione um bot", "Press any button"}, //0 Walcome
    {"<< selecionar >>", "<< select >>    "}, //1 MENU
    {"o Enter         ", "o Enter         "}, //2 SetLanguage
    {"o Enter         ", "o Enter         "}, //3 SeleLanguage
    {"o Enter         ", "o Enter         "}, //4 SetTempHi
    {"o Enter         ", "o Enter         "}, //5 SetTempLow
    {"o Enter         ", "o Enter         "}, //6 SetTimeAquis
    {"o Enter  +-Mudar", "o Enter   Change"}, //7
    {"ALARME 1 ALTO   ", "Hi Alarm 1 Error"}, //8 ALARM 1 Hi
    {"ALARME 1 BAIXO  ", "Lo Alarm 1 Error"}, //9 ALARM 1 Low
    {"ALARME 2 ALTO   ", "Hi Alarm 2 Error"}, //10 ALARM 2 Hi
    {"ALARME 2 BAIXO  ", "Lo Alarm 1 Error"}, //11 ALARM 2 Low
    {"ALARME 1 OK     ", "Alarm 1 OK      "}, //12 ALARM 1 OK
    {"ALARME 2 OK     ", "Alarm 2 OK      "}, //13 ALARM 2 OK
};

void outputInit(void) {
    lcdInit(); //ja esta inicializado na main
}

void outputPrint(char numTela, char idioma, char event) {

    switch (numTela) {
        case Welcome:
        {
            lcdCommand(0x80);
            lcdString(msgs1[Welcome][idioma]);
            lcdCommand(0xC0);
            lcdString(msgs2[Welcome][idioma]);
            break;
        }
        case (Menu):
        {
            lcdCommand(0x80);
            lcdString(msgs1[Menu][idioma]);
            lcdCommand(0xC0);
            lcdString(msgs2[Menu][idioma]);
            break;
        }
        case (SetLenguage):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SetLenguage][idioma]);
            lcdCommand(0xC0);
            lcdString(msgs2[SetLenguage][idioma]);
            break;
        }
        case (SetLow1):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SetLow1][idioma]);
            lcdData(1 + 48);
            lcdCommand(0xC0);
            lcdString(msgs2[SetLow1][idioma]);
            break;
        }
        case (SetHigh1):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SetHigh1][idioma]);
            lcdData(1 + 48);
            lcdCommand(0xC0);
            lcdString(msgs2[SetHigh1][idioma]);
            break;
        }
        case (SetLow2):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SetLow1][idioma]);
            lcdData(2 + 48);
            lcdCommand(0xC0);
            lcdString(msgs2[SetLow1][idioma]);
            break;
        }
        case (SetHigh2):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SetHigh1][idioma]);
            lcdData(2 + 48);
            lcdCommand(0xC0);
            lcdString(msgs2[SetHigh1][idioma]);
            break;
        }
        case (SetTime):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SetTime - 2][idioma]);
            lcdCommand(0xC0);
            lcdString(msgs2[SetTime - 2][idioma]);
            break;
        }
        case (SeleLanguage):
        {
            lcdCommand(0x80);
            lcdString(msgs1[SeleLanguage][idioma]);
            lcdCommand(0xC0);
            lcdString(msgs2[SeleLanguage][idioma]);
            break;
        }
        case (SetUnit):
        {
            if (getstateAnt() == SetHigh1) {
                lcdCommand(0x80);
                lcdString("TH1 = ");
                lcdData((getHiAlarm1() / 1000) % 10 + 48);
                lcdData((getHiAlarm1() / 100) % 10 + 48);
                lcdData((getHiAlarm1() / 10) % 10 + 48);
                lcdData(getHiAlarm1() % 10 + 48);
                lcdString("       ");
            }
            if (getstateAnt() == SetLow1) {
                lcdCommand(0x80);
                lcdString("TL1 = ");
                lcdData((getLowAlarm1() / 1000) % 10 + 48);
                lcdData((getLowAlarm1() / 100) % 10 + 48);
                lcdData((getLowAlarm1() / 10) % 10 + 48);
                lcdData(getLowAlarm1() % 10 + 48);
                lcdString("       ");

            }
            if (getstateAnt() == SetHigh2) {
                lcdCommand(0x80);
                lcdString("TH2 = ");
                lcdData((getHiAlarm2() / 1000) % 10 + 48);
                lcdData((getHiAlarm2() / 100) % 10 + 48);
                lcdData((getHiAlarm2() / 10) % 10 + 48);
                lcdData(getHiAlarm2() % 10 + 48);
                lcdString("       ");
            }
            if (getstateAnt() == SetLow2) {
                lcdCommand(0x80);
                lcdString("TL2 = ");
                lcdData((getLowAlarm2() / 1000) % 10 + 48);
                lcdData((getLowAlarm2() / 100) % 10 + 48);
                lcdData((getLowAlarm2() / 10) % 10 + 48);
                lcdData(getLowAlarm2() % 10 + 48);
                lcdString("         ");
            }
            if (getstateAnt() == SetTime) {
                lcdCommand(0x80);
                lcdString("time = ");
                lcdData((getTime() / 10) % 10 + 48);
                lcdData(getTime() % 10 + 48);
                lcdString("       ");
            }
            lcdCommand(0xC0);
            lcdString(msgs2[SetUnit - 2][idioma]);
            break;
        }
        case (RTC):
        {
            lcdCommand(0x80);
            lcdString(" Hora ");
            lcdData((RTC_ReadParam(rtcDATE) / 10) % 10 + 48);
            lcdData((RTC_ReadParam(rtcDATE)) % 10 + 48);
            lcdData(':');
            lcdData((RTC_ReadParam(rtcMINUTE) / 10) % 10 + 48);
            lcdData((RTC_ReadParam(rtcMINUTE)) % 10 + 48);
            lcdData(':');
            lcdData((RTC_ReadParam(rtcSECOND) / 10) % 10 +48);
            lcdData((RTC_ReadParam(rtcSECOND)) % 10 + 48);
            lcdData(' ');
            lcdData(' ');
            lcdCommand(0xC0);
            lcdString(" Date ");
            lcdData((RTC_ReadParam(rtcDAY) / 10) % 10 + 48);
            lcdData((RTC_ReadParam(rtcDAY)) % 10 + 48);
            lcdData('/');
            lcdData((RTC_ReadParam(rtcMONTH) / 10) % 10 + 48);
            lcdData((RTC_ReadParam(rtcMONTH)) % 10 + 48);
            lcdData('/');
            lcdData((RTC_ReadParam(rtcYEAR) / 10) % 10 + 48);
            lcdData((RTC_ReadParam(rtcYEAR)) % 10 + 48);
            lcdData(' ');
            lcdData(' ');
            break;
        }
        case (Alarm):
        {
            switch (event) {
                case Hialarm1:
                {
                    lcdCommand(0x80);
                    lcdString(msgs1[8][idioma]);
                    lcdData(1 + 48);
                    lcdCommand(0xC0);
                    lcdString(msgs2[8][idioma]);
                    break;
                }
                case Hialarm2:
                {
                    lcdCommand(0x80);
                    lcdString(msgs1[10][idioma]);
                    lcdData(1 + 48);
                    lcdCommand(0xC0);
                    lcdString(msgs2[10][idioma]);
                    break;
                }
                case Lowalarm1:
                {
                    lcdCommand(0x80);
                    lcdString(msgs1[9][idioma]);
                    lcdData(1 + 48);
                    lcdCommand(0xC0);
                    lcdString(msgs2[9][idioma]);
                    break;
                }
                case Lowalarm2:
                {
                    lcdCommand(0x80);
                    lcdString(msgs1[11][idioma]);
                    lcdData(1 + 48);
                    lcdCommand(0xC0);
                    lcdString(msgs2[11][idioma]);
                    break;
                }
                case ALARM1OK:
                {
                    lcdCommand(0x80);
                    lcdString(msgs1[12][idioma]);
                    lcdData(1 + 48);
                    lcdCommand(0xC0);
                    lcdString(msgs2[12][idioma]);
                    break;
                }
                case ALARM2OK:
                {
                    lcdCommand(0x80);
                    lcdString(msgs1[13][idioma]);
                    lcdData(1 + 48);
                    lcdCommand(0xC0);
                    lcdString(msgs2[13][idioma]);
                    break;
                }
            }

        }
    }
}

