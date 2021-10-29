// -----------------------------------------------------------------------
//   Copyright (C) Lucas Wacho Precioso
// -----------------------------------------------------------------------
//   Arquivo: stateMachine.c
//            maquina de estado do programa
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

#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"
#include "pic18f45xx.h"
#include "event.h"
#include "keypad.h"
#include "adc.h"
#include "delay.h"

#define ALARMHIMAX 1000
#define ALARMLOWMIN 0

void smInit(void) {
    setState(Welcome);
    outputPrint(getState(), getLanguage(), EV_NOEVENT);
}

void FWelcome(char tec);
void FMenu(char tec);
void FSetLenguage(char tec);
void FSeleLanguage(char tec);
void FSetHigh1(char tec);
void FSetLow1(char tec);
void FSetHigh2(char tec);
void FSetLow2(char tec);
void FSetTime(char tec);
void FSetUnit(char tec);
void FRTC(char tec);
void FAlarm(char tec);

void smLoop(char event) { //máquina de estados

    if ((event == Hialarm1) || (event == Hialarm2) || (event == Lowalarm2) ||
            (event == Lowalarm1) || (event == ALARM1OK) || (event == ALARM2OK)) {
        setState(Alarm);
    }

    switch (getState()) {
        case Welcome:
        {
            FWelcome(event);
            break;
        }
        case Menu:
        {
            FMenu(event);
            break;
        }
        case SetLenguage:
        {
            FSetLenguage(event);
            break;
        }
        case SeleLanguage:
        {
            FSeleLanguage(event);
            break;
        }
        case SetHigh1:
        {
            FSetHigh1(event);
            break;
        }
        case SetLow1:
        {
            FSetLow1(event);
            break;
        }
        case SetHigh2:
        {
            FSetHigh2(event);
            break;
        }
        case SetLow2:
        {
            FSetLow2(event);
            break;
        }
        case SetTime:
        {
            FSetTime(event);
            break;
        }
        case SetUnit:
        {
            FSetUnit(event);
            break;
        }
        case RTC:
        {
            FRTC(event);
            break;
        }
        case Alarm:
        {
            FAlarm(event);
            break;
        }
    }
    outputPrint(getState(), getLanguage(), event);
}

void FWelcome(char tec) {
    if ((tec > 0) && (tec < 5)) {
        setState(Menu);
    }
}

void FMenu(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(SetLenguage);
            break;
        }
        case EV_LEFT:
        {
            setState(RTC);
            break;
        }

    }
}

void FSetLenguage(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(SetHigh1);
            break;
        }
        case EV_DOWN:
        {
            break;
        }
        case EV_LEFT:
        {
            setState(Menu);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            setState(SeleLanguage);
            break;
        }
    }
}

void FSetHigh1(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(SetLow1);
            break;
        }
        case EV_DOWN:
        {

            break;
        }
        case EV_LEFT:
        {
            setState(SetLenguage);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            setState(SetUnit);
            break;
        }
    }
}

void FSetLow1(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(SetHigh2);
            break;
        }
        case EV_DOWN:
        {
            break;
        }
        case EV_LEFT:
        {
            setState(SetHigh1);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            setState(SetUnit);
            break;
        }
    }
}

void FSetHigh2(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(SetLow2);
            break;
        }
        case EV_DOWN:
        {

            break;
        }
        case EV_LEFT:
        {
            setState(SetLow1);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            setState(SetUnit);
            break;
        }
    }
}

void FSetLow2(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(SetTime);
            break;
        }
        case EV_DOWN:
        {
            break;
        }
        case EV_LEFT:
        {
            setState(SetHigh2);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            setState(SetUnit);
            break;
        }
    }
}

void FSetTime(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(RTC);
            break;
        }
        case EV_DOWN:
        {
            break;
        }
        case EV_LEFT:
        {
            setState(SetLow2);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            setState(SetUnit);
            break;
        }
    }
}

void FSeleLanguage(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            break;
        }
        case EV_DOWN:
        {
            setLanguage(getLanguage() + 1);
            break;
        }
        case EV_LEFT:
        {
            break;
        }
        case EV_UP:
        {
            setLanguage(getLanguage() - 1);
            break;
        }
        case EV_ENTER:
        {
            setState(SetLenguage);
            break;
        }
    }
}

void FSetUnit(char tec) {
    unsigned char statAnt = getstateAnt();

    if (statAnt == SetHigh1) {
        switch (tec) {
            case EV_RIGHT:
            {
                break;
            }
            case EV_DOWN:
            {
                if ((getHiAlarm1()) > (getLowAlarm1()) + 1) {
                    setHiAlarm1(getHiAlarm1() - 1);
                }
                break;
            }
            case EV_LEFT:
            {
                break;
            }
            case EV_UP:
            {
                if (getHiAlarm1() < ALARMHIMAX) {
                    setHiAlarm1(getHiAlarm1() + 1);
                }
                break;
            }
            case EV_ENTER:
            {
                setState(statAnt);
                break;
            }

        }
    }
    if (statAnt == SetLow1) {
        switch (tec) {
            case EV_RIGHT:
            {
                break;
            }
            case EV_DOWN:
            {
                if (getLowAlarm1() > ALARMLOWMIN) {
                    setLowAlarm1(getLowAlarm1() - 1);
                }
                break;
            }
            case EV_LEFT:
            {
                break;
            }
            case EV_UP:
            {
                if ((getLowAlarm1()) < (getHiAlarm1()) - 1) {
                    setLowAlarm1(getLowAlarm1() + 1);
                }
                break;
            }
            case EV_ENTER:
            {
                setState(statAnt);
                break;
            }
        }
    }

    if (statAnt == SetHigh2) {
        switch (tec) {
            case EV_RIGHT:
            {
                break;
            }
            case EV_DOWN:
            {
                if ((getHiAlarm2()) > (getLowAlarm2()) + 1) {
                    setHiAlarm2(getHiAlarm2() - 1);
                }
                break;
            }
            case EV_LEFT:
            {
                break;
            }
            case EV_UP:
            {
                if (getHiAlarm2() < ALARMHIMAX) {
                    setHiAlarm2(getHiAlarm2() + 1);
                }
                break;
            }
            case EV_ENTER:
            {
                setState(statAnt);
                break;
            }

        }
    }
    if (statAnt == SetLow2) {
        switch (tec) {
            case EV_RIGHT:
            {
                break;
            }
            case EV_DOWN:
            {
                if (getLowAlarm2() > ALARMLOWMIN) {
                    setLowAlarm2(getLowAlarm2() - 1);
                }
                break;
            }
            case EV_LEFT:
            {
                break;
            }
            case EV_UP:
            {
                if ((getLowAlarm2()) < (getHiAlarm2()) - 1) {
                    setLowAlarm2(getLowAlarm2() + 1);
                }
                break;
            }
            case EV_ENTER:
            {
                setState(statAnt);
                break;
            }
        }
    }
    if (statAnt == SetTime) {
        switch (tec) {
            case EV_RIGHT:
            {
                break;
            }
            case EV_DOWN:
            {
                setTime(0);
                break;
            }
            case EV_LEFT:
            {
                break;
            }
            case EV_UP:
            {
                setTime(1);
                break;
            }
            case EV_ENTER:
            {
                setState(statAnt);
                break;
            }
        }
    }
}

void FRTC(char tec) {
    switch (tec) {
        case EV_RIGHT:
        {
            setState(Menu);
            break;
        }
        case EV_DOWN:
        {

            break;
        }
        case EV_LEFT:
        {
            setState(SetTime);
            break;
        }
        case EV_UP:
        {
            break;
        }
        case EV_ENTER:
        {
            break;
        }
    }
}

void FAlarm(char event) {

    if ((event == Hialarm1) || (event == Hialarm2) || (event == Lowalarm2) ||
            (event == Lowalarm1) || (event == ALARM1OK) || (event == ALARM2OK)) {
        switch (event) {
            case Hialarm1:
            {
            }
            case Hialarm2:
            {
            }
            case Lowalarm1:
            {
            }
            case Lowalarm2:
            {
            }
            case ALARM1OK:
            {
            }
            case ALARM2OK:
            {
            }
        }
    } else {
        setState(getstateAntAnt());
        setState(getstateAntAnt());
    }
}
