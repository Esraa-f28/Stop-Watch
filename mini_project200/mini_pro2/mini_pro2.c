/*
 * mini_project.c
 *
 *  Created on: Aug 30, 2022
 *      Author: Esraa Fawzy
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile unsigned char seconds_counter=0;
unsigned char minutes_counter=0;
unsigned char hours_counter=0;

void INT0_init()
{
	DDRD &=~(1<<PD2);
	PORTD |=(1<<PD2); 	/*enable internal pull up */
	MCUCR |=(1<<ISC01);	/* make INT0 as falling edge*/
	GICR |= (1<<INT0);	/*enable interrupt 0*/


}
/*reset the system*/
ISR(INT0_vect)
{
	PORTA=0x3F;
	seconds_counter=0;
	minutes_counter=0;
	hours_counter=0;
	TCNT1 = 0;
	while(!(PIND&(1<<PD2)));
}
void INT1_init()
{
	DDRD &=~(1<<PD3);	/*PD3 input*/
	MCUCR |=(1<<ISC11) |(1<<ISC10); /*make 	INT 1 as rising edge*/
	GICR |= (1<<INT1);	/*enable interrupt 1*/

}
/*pause the system by stop timer */
ISR(INT1_vect)
{
	TCCR1B &=~(1<<CS10);
	TCCR1B &=~(1<<CS11);
	TCCR1B &=~(1<<CS12);
}
void INT2_init()
{
	DDRB&=~(1<<PB2);	/*PB3 input*/
	PORTB |= (1<<PB2);	/*enable internal pull up */
	MCUCSR &=~ (1<<ISC2); /*make 	INT 1 as falling edge*/
	GICR |= (1<<INT2);

}
/*resume the system by enable timer */
ISR(INT2_vect)
{
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

void timer_init()
{

	TCNT1 = 0;
	OCR1A=1000;
	TIMSK= (1<<OCIE1A);
	TCCR1A = (1<<FOC1A) ;
	TCCR1B=(1<<CS12) | (1<<CS10)| (1<<WGM12);
}
/* Description:
 * For System Clock=1Mhz and timer prescaler is F_CPU/1024.
 * Timer frequency will be around 1Khz, Ttimer = 1ms
 * For initial timer counter = 0.
 * compare mode  interrupt will be generated every 1 second.
 */
ISR(TIMER1_COMPA_vect)
{
	SREG |= (1<<7); 	/*enable I bit to support nested interrupt*/
	seconds_counter++;	/*increase seconds by one */
}
void seven_segments_init(void)
{
	DDRC=0x0F;	/*make 4-pins in port c as output*/
	DDRA=0x3F;	/*make 6-pins in port A as output (enable of 7-seg)*/
	PORTC = 0x00; /* as 7-seg is common anode , make first 4 pins in port c=0*/
}
/*function to write value in 7-seg*/
void seven_seg_write(unsigned char value)
{

	PORTC = (PORTC & 0xF0) | ( value& 0x0F);
}

int main(void)
{
	SREG |=(1<<7); // enable I-bit
	seven_segments_init();
	INT0_init();
	INT1_init();
	INT2_init();
	timer_init();
	while(1)
	{
		/*delay between every 7-seg ,as the max freq cac human see is 30hz */
		/*enable every 7 segement by put logic high in anode */
		PORTA=0x01;
		seven_seg_write(seconds_counter%10);
		_delay_ms(5);
		PORTA=0x02;
		seven_seg_write(seconds_counter/10);
		_delay_ms(5);
		PORTA=0x04;
		seven_seg_write(minutes_counter%10);
		_delay_ms(5);
		PORTA=0x08;
		seven_seg_write(minutes_counter/10);
		_delay_ms(5);
		PORTA=0x10;
		seven_seg_write(hours_counter%10);
		_delay_ms(5);
		PORTA=0x20;
		seven_seg_write(hours_counter/10);
		_delay_ms(5);

		if(seconds_counter==60)
		{
			seconds_counter=0;
			minutes_counter++;
		}

		if(minutes_counter==60)
		{
			minutes_counter=0;
			hours_counter++;
		}
		if(hours_counter==24)
		{
			hours_counter=0;
		}
	}


}
