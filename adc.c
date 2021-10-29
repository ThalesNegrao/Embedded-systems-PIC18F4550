// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: adc.c
//            Biblioteca do conversor AD para o PIC18F4520
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
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

#include "adc.h"
#include "pic18f45xx.h"

void adcInit(void) {
    BitSet(TRISA, 0); //seta o bit 0 como entrada
    ADCON0 = 0b00000001; //seleciona o canal 0 e liga o ad
    ADCON1 = 0b00000111; //analogico 0 a 7, a referencia é baseada na fonte
    ADCON2 = 0b10101010; //FOSC /32, Alinhamento à direita e tempo de conv = 12 TAD
}

int adcRead(unsigned char adc) {
    unsigned int ADvalor;
    switch (adc) {
        case AD0: //AD0 (PORTA,0)
        {
            ADCON0 = 0b00000011; // Potenciometro
            break;
        }
        case AD1: //AD1 (PORTA,1)
        {
            ADCON0 = 0b00000111; //AOP A
            break;
        }
        case AD2: //AD2 (PORTA,2)
        {
            ADCON0 = 0b00001011; //AOP B
            break;
        }
        case AD3: //AD3 (PORTA,3) // teclado
        {
            ADCON0 = 0b00001111;
            break;
        }
        case AD4: //AD4 (PORTA,5)
        {
            ADCON0 = 0b00001001;
            break;
        }
        case AD5: //AD5 (PORTD,0)
        {
            ADCON0 = 0b00010111;
            break;
        }
        case AD6: //AD6 (PORTD,1)
        {
            ADCON0 = 0b00011011;
            break;
        }
        case AD7: //AD7 (PORTD,3)
        {
            ADCON0 = 0b00011111;
            break;
        }

    }

    while (BitTst(ADCON0, 1)); // espera terminar a conversão;

    ADvalor = ADRESH; // le o resultado
    ADvalor <<= 8;
    ADvalor += ADRESL;

    return ADvalor;
}