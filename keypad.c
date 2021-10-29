// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operação de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
//   Alteração 1: Thales Maia Mendonça Negrão
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
#include "pic18f45xx.h"
#include "event.h"

static unsigned int valor = 0x00;

void kpInit(void) {
    BitSet(TRISA, 3); //seta o bit 0 como entrada
    TRISB = 0xF0; //quatro entradas e quatro saidas
    BitClr(INTCON2, 7); //liga pull up
    // ADCON1 = 0b00001110; //inicializado no ad

#ifdef PIC18F4550
    SPPCFG = 0x00; // SFR nao presente no PIC18F4520
#endif
}

unsigned char kpARead(void) {

    unsigned int valorR = 0;

    valorR = valor;

    if ((valorR >= 250) && (valorR <= 300)) { //primeiro botão
        return EV_RIGHT;
    }
    if ((valorR >= 300) && (valorR <= 400)) { //segundo botão
        return EV_LEFT;
    }
    if ((valorR >= 400) && (valorR <= 600)) { //terceiro botão
        return EV_DOWN;
    }
    if ((valorR >= 600) && (valorR <= 800)) { //quarto botão
        return EV_UP;
    }
    if ((valorR >= 800) && (valorR <= 1200)) { //quinto botão
        return EV_ENTER;
    } else {
        return EV_NOEVENT;
    }
}

void kpADebounce(void) {
    static unsigned char tempo = 6;
    static unsigned int valorNovo = 0;
    static unsigned int valorAntigo = 0;

    ADCON0 = 0b00001111; //inicia conversao

    while (BitTst(ADCON0, 1)); // espera terminar a conversão;

    valorNovo = ADRESH; // le o resultado
    valorNovo <<= 8;
    valorNovo += ADRESL;

    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 6;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
}
//------------->Teclado Binario<----------------------------------------
/*
unsigned char kpRead(void) {
    return valor;
}

void kpDebounce(void) {
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned char valorNovo = 0x0000;
    static unsigned char valorAntigo = 0x0000;

    for (i = 0; i < 4; i++) {
        TRISB = ~((unsigned char)1<<i);
        PORTB = ~((unsigned char)1<<i);

        //realiza o teste para cada bit e atualiza a variável
        for (j = 0; j < 2; j++) {
            if (!BitTst(PORTB, j + 4)) {
                BitSet(valorNovo, (i * 2) + j);
            } else {
                BitClr(valorNovo, (i * 2) + j);
            }
        }
    }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
}
 ----------------------------------------------------------------------------
 */
