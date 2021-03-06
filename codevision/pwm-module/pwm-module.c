/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
� Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : pwm-module
Version : 1.0.0
Date    : 7/6/2017
Author  : melika barzegaran hosseini 9231035 - soroush kavousi 9231077
Company : 
Comments: 
a script to test whether the pwm module works correctly


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

/*****************************************************
instructions:
0. fuse bit setup:
    - CKSEL[3:0] = 0001
    - CKOPT = 1
    - SUT[1:0] = 10
1. disable led module (JP1).
2. disable buzzer module (JP2).
3. disable 7segment module (JP3).
4. enable pwm module (JP4).
5. disable analog comparator module (JP5 and JP6). 
6. remove the lcd from the board.
*****************************************************/

#include <mega32a.h>
#include <delay.h>

void main(void)
{
    // make the pwm led port output.
    // turn the pwm led off.
    DDRD=0x60;
    PORTD=0x00;
    
    // enable timer/counter #1 output compare (A).
    TCCR1A = (1 << COM1A1) | (1 << COM1A0);
    
    // enable timer/counter #1 mode as fast pwm with top = 0x00FF.
    TCCR1A |= (0 << WGM11) | (1 << WGM10);
    TCCR1B = (0 << WGM13) | (1 << WGM12);
    
    // enable timer/counter #1 prescaling as 8.
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
    
    // setup timer/counter #1.
    TCNT1H=0x00;
    TCNT1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;

    // enable interrupts.
    #asm("sei")

    // endless loop.
    while (1)
    {
		OCR1AL++;
		delay_ms(50);
    }
}