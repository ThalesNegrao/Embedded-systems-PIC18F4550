// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: lcd.c
//            Biblioteca de manipulação do LCD
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
//   Alteração 1: Lucas Wacho Precioso
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


#include "lcd.h"
#include "pic18f45xx.h"
#include "delay.h"

/*bitis ligados no
 * RD0-pin14 ate RD3-pin11
 * RS-pin4 RB3
 * E-pin6 RB2
 */


#define RS 3
#define EN 2

#define D4 3
#define D5 2
#define D6 1
#define D7 0

void PulsoEN(void) {
    BitClr(PORTB, EN);

    BitSet(PORTB, EN); //Pulso no Enable
    Delay40us();

    BitClr(PORTB, EN);

}

void lcdCommand(unsigned char cmd) {

    BitClr(PORTB, RS);
    BitClr(PORTB, EN); //comando
    //BitClr(PORTE,RW);	// habilita escrita


    //Seleciona pinos de Dados: Nibble-High
    if (cmd & 0b00010000) {
        BitSet(PORTD, D4);
    } else {
        BitClr(PORTD, D4);
    }
    if (cmd & 0b00100000) {
        BitSet(PORTD, D5);
    } else {
        BitClr(PORTD, D5);
    }
    if (cmd & 0b01000000) {
        BitSet(PORTD, D6);
    } else {
        BitClr(PORTD, D6);
    }
    if (cmd & 0b10000000) {
        BitSet(PORTD, D7);
    } else {
        BitClr(PORTD, D7);
    }
    PulsoEN();

    //Seleciona pinos de Dados: Nibble-Low
    if (cmd & 0b00000001) {
        BitSet(PORTD, D4);
    } else {
        BitClr(PORTD, D4);
    }
    if (cmd & 0b00000010) {
        BitSet(PORTD, D5);
    } else {
        BitClr(PORTD, D5);
    }
    if (cmd & 0b00000100) {
        BitSet(PORTD, D6);
    } else {
        BitClr(PORTD, D6);
    }
    if (cmd & 0b00001000) {
        BitSet(PORTD, D7);
    } else {
        BitClr(PORTD, D7);
    }
    PulsoEN();

    if (cmd == 0x03 || cmd == 0x02 || cmd == 0x01) { //o comando de reset exige mais tempo
        Delay10ms();
    } else {
        Delay40us();
    }

}

void lcdInit(void) {
    // Inicializa o LCD

    // garante inicialização do LCD (+-10ms)
    Delay10ms();


    // configurações de direção dos terminais
    BitClr(TRISB, RS); //RS
    BitClr(TRISB, EN); //EN
    //BitClr(TRISE,RW);	//RW

    //CONFIGURA AS PORTAS COMO SAÍDA
    BitClr(TRISD, D4);
    BitClr(TRISD, D5);
    BitClr(TRISD, D6);
    BitClr(TRISD, D7);


    Delay2ms();

    //***********   INICIALIZAÇÃO	***********

    //3
    BitClr(PORTD, D7);
    BitClr(PORTD, D6);
    BitSet(PORTD, D5);
    BitSet(PORTD, D4);

    PulsoEN();
    Delay10ms();
    //3
    BitClr(PORTD, D7);
    BitClr(PORTD, D6);
    BitSet(PORTD, D5);
    BitSet(PORTD, D4);

    PulsoEN();
    Delay10ms();
    //3
    BitClr(PORTD, D7);
    BitClr(PORTD, D6);
    BitSet(PORTD, D5);
    BitSet(PORTD, D4);

    PulsoEN();
    Delay10ms();
    //2
    BitClr(PORTD, D7);
    BitClr(PORTD, D6);
    BitSet(PORTD, D5);
    BitClr(PORTD, D4);

    PulsoEN();
    Delay10ms();

    //***********   CONFIGURAÇÃO	***********

    lcdCommand(0x2b); //4bits, 2 linhas, 5x8 tamanho


    lcdCommand(0x01); //limpa o display

    lcdCommand(0x0f); //display on, cursor e blink off

    lcdCommand(0b00000110); // Entry mode set: Increment, Shift OFF

    lcdCommand(0b00010100); // Entry mode set

    lcdCommand(0x80); // Vai para primeira linha
    /*
     lcdCommand(0x28); //0b0010 1000 4bits, 2 linhas,
     lcdCommand(0x06); //0b0000 0110 modo incremental
     lcdCommand(0x0C); //0b0000 1111 display e cursor on, com blink
     lcdCommand(0x03); //0b0000 0011 zera variáveis internas
     lcdCommand(0x80); //0b1000 0000 muda o endereço para posição inicial (0,0)
     lcdCommand(0x01); //0b0000 0001 Limpa a tela
     */

}

void lcdInt(int linha) {
    if (linha == 2) {
        lcdCommand(0xC0);
    } else {
        lcdCommand(0x80);
    }
}

void lcdData(unsigned char valor) {
    Delay2ms();

    BitSet(PORTB, RS);
    BitClr(PORTB, EN); //comando
    //BitClr(PORTE,RW);	// habilita escrita

    Delay2ms();

    //Seleciona pinos de Dados: Nibble-High
    if (valor & 0b00010000) {
        BitSet(PORTD, D4);
    } else {
        BitClr(PORTD, D4);
    }
    if (valor & 0b00100000) {
        BitSet(PORTD, D5);
    } else {
        BitClr(PORTD, D5);
    }
    if (valor & 0b01000000) {
        BitSet(PORTD, D6);
    } else {
        BitClr(PORTD, D6);
    }
    if (valor & 0b10000000) {
        BitSet(PORTD, D7);
    } else {
        BitClr(PORTD, D7);
    }
    PulsoEN();

    //Seleciona pinos de Dados: Nibble-Low
    if (valor & 0b00000001) {
        BitSet(PORTD, D4);
    } else {
        BitClr(PORTD, D4);
    }
    if (valor & 0b00000010) {
        BitSet(PORTD, D5);
    } else {
        BitClr(PORTD, D5);
    }
    if (valor & 0b00000100) {
        BitSet(PORTD, D6);
    } else {
        BitClr(PORTD, D6);
    }
    if (valor & 0b00001000) {
        BitSet(PORTD, D7);
    } else {
        BitClr(PORTD, D7);
    }
    PulsoEN();


    BitClr(PORTB, RS);
}

void lcdString(char vector[]) {
    char i = 0;

    while (vector[i]) {
        lcdData(vector[i]);
        i++;
    }
}








/*
#define RS 0
#define EN 1
#define RW 2


void Delay40us(void) {
    unsigned char i;
    for (i = 0; i < 25; i++); //valor aproximado
}

void Delay2ms(void) {
    unsigned char i;
    for (i = 0; i < 50; i++) {
        Delay40us();
    }
}

void lcdCommand(unsigned char cmd) {
    BitClr(PORTE, RS); //comando
    BitClr(PORTE, RW); // habilita escrita

    PORTD = cmd;

    BitSet(PORTE, EN); //Pulso no Enable
    BitClr(PORTE, EN);

    if (BitTst(cmd, 1)) { //o comando de reset exige mais tempo
        Delay2ms();
    } else {
        Delay40us();
    }
}

void lcdData(unsigned char valor) {
    BitSet(PORTE, RS); //dados
    BitClr(PORTE, RW); // habilita escrita

    PORTD = valor;

    BitSet(PORTE, EN); //Pulso no Enable
    BitClr(PORTE, EN);

    BitClr(PORTE, RS); //deixa em nivel baixo por causa do display de 7 seg
    Delay40us();
}

//int max 5 digitos

void lcdInt(int val) {
    if (val < 0) {
        val = val * (-1);
        lcdData('-');
    }
    lcdData((val / 10000) % 10 + 48);
    lcdData((val / 1000) % 10 + 48);
    lcdData((val / 100) % 10 + 48);
    lcdData((val / 10) % 10 + 48);
    lcdData((val / 1) % 10 + 48);

}

void lcdString(char msg[]) {
    int i=0;
    while (msg[i]!=0) {
        lcdData(msg[i]);
        i++;
    }
}

void lcdInit(void) {
    // Inicializa o LCD

    // garante inicialização do LCD (+-10ms)
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();

    // configurações de direção dos terminais
    BitClr(TRISE, RS); //RS
    BitClr(TRISE, EN); //EN
    BitClr(TRISE, RW); //RW
    TRISD = 0x00; //dados
    ADCON1 = 0b00001110; //apenas

    //configura o display
    lcdCommand(0x38); //0b0011 1000 8bits, 2 linhas, 5x8
    lcdCommand(0x0F); //0b0000 1111 display e cursor on, com blink
    lcdCommand(0x06); //0b0000 0110 modo incremental
    lcdCommand(0x03); //0b0000 0011 zera variáveis internas
    lcdCommand(0x01); //0b0000 0001 Limpa a tela
}*/
