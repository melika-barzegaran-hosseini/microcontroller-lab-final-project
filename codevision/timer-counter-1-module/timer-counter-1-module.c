/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
� Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : timer-counter-1-module
Version : 1.0.0
Date    : 7/6/2017
Author  : melika barzegaran hosseini 9231035 - soroush kavousi 9231077
Company : 
Comments: 
a script to test whether the timer/counter #1 works correctly


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
    - CKSEL[3:0] = 1111
    - CKOPT = 0
    - SUT[1:0] = 11
1. disable led module (JP1).
2. disable buzzer module (JP2).
3. disable 7segment module (JP3).
4. diable pwm module (JP4).
5. disable analog comparator module (JP5 and JP6).
7. add the lcd to the board.

SPECIAL: connect a pulse signal with an specified 
frequency to the pin PB1 (T1) and observe the frequency
on the lcd.
*****************************************************/

#include <mega32a.h>
#include <alcd.h>     
#include <stdlib.h>

int total_overflow;

void show();

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    // increase the number of times overflow has occured by one.
    total_overflow++;
                                           
    // check if overflow has occured for 4 times (equivalent to 1 second delay with 1(MHz) cpu speed and 1024 prescaler).
    if(total_overflow >= 4)
    {                                          
        //write the time on the lcd screen.
        show(); 
        
         //and start counting from the begining.
        total_overflow = 0;
        TCNT0 = 0x00;
        TCNT1H = 0x00;
        TCNT1L = 0x00;
    }
}

//convert the time to a decimal number, and then to a string and show it on the lcd.
void show()
{
    char number[3];
    lcd_clear();
    itoa(TCNT1L, number);
    lcd_puts(number);
}

void main(void)
{
    // setup timer/counter #0.
    TCNT0=0x00;
    OCR0=0x00;
    
    // enable timer/counter #0 mode as normal.
    TCCR0 |= (0 << WGM01) | (0 << WGM00);    
    
    // enable timer/counter #0 prescaler as 1024.
    TCCR0 |= (1 << CS02) | (0 << CS01) | (1 << CS00);
    
    // enable timer/counter #0 overflow interrupt.
    TIMSK |= (1 << TOIE0);
    
    // setup timer/counter #1.
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    
    // enable timer/counter #1 external clock source on T1 pin. clock on rising edge.
    TCCR1B |= (1 << CS12)| (1 << CS11) | (1 << CS10);   
    
    // initalize the number of timer/counter #0's overflows as 0.
    total_overflow = 0; 
    
    // setup lcd.
    lcd_init(16);

    // enable interrupts.
    #asm("sei")

    // endless loop.
    while (1);
}