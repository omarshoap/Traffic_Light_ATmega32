/*
 * REG.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_REG_H_
#define MCAL_REG_H_

#include "STD_TYPES.h"

/*************** DIO_REGISTERS *************/

#define PORTA      (*((volatile u8*)0x3B))
#define DDRA       (*((volatile u8*)0x3A))
#define PINA       (*((volatile u8*)0x39))

#define PORTB      (*((volatile u8*)0x38))
#define DDRB       (*((volatile u8*)0x37))
#define PINB       (*((volatile u8*)0x36))

#define PORTC      (*((volatile u8*)0x35))
#define DDRC       (*((volatile u8*)0x34))
#define PINC       (*((volatile u8*)0x33))

#define PORTD      (*((volatile u8*)0x32))
#define DDRD       (*((volatile u8*)0x31))
#define PIND       (*((volatile u8*)0x30))

/*************** EX_INT_REGISTERS *************/

#define SREG        (*((volatile u8*)0x5F))
#define MCUCR       (*((volatile u8*)0x55))
#define GICR        (*((volatile u8*)0x5B))
#define GIFR        (*((volatile u8*)0x5A))

/*************** ADC_REGISTERS ****************/

#define ADMUX       (*((volatile u8*)0x27))
#define ADCSRA      (*((volatile u8*)0x26))
#define ADCH        (*((volatile u8*)0x25))
#define ADCL        (*((volatile u8*)0x24))
#define ADC_DATA    (*((volatile u16*)0x24))

/************* TIMER_0_REGISTERS **************/

#define TCNT0       (*((volatile u8*)0x52))
#define TCCR0       (*((volatile u8*)0x53))
#define TIMSK       (*((volatile u8*)0x59))
#define TIMSK       (*((volatile u8*)0x59))
#define OCR0        (*((volatile u8*)0x5C))

/************* TIMER_1_REGISTERS **************/

#define TCCR1A      (*((volatile u8*)0x4F))
#define TCCR1B      (*((volatile u8*)0x4E))
#define OCR1A       (*((volatile u16*)0x4A))
#define ICR1        (*((volatile u16*)0x46))

/************* SPI_REGISTERS **************/

#define SPCR      (*((volatile u8*)0x2D))
#define SPSR      (*((volatile u8*)0x2E))
#define SPDR       (*((volatile u16*)0x2F))


/************* UART_REGISTERS **************/
/*
 * UDR	2C
UCSRA	2B
UCSRB	2A
UCSRC	40
UBRRH	40
UBRRL	29
*/
#define UDR       (*((volatile u8*)0x2C))
#define UCSRA       (*((volatile u8*)0x2E))
/************* I2C_REGISTERS **************/

#define TWBR      (*((volatile u8*)0x20))
#define TWCR      (*((volatile u8*)0x56))
#define TWSR      (*((volatile u16*)0x2F))
#define TWDR      (*((volatile u8*)0x23))
#define TWAR      (*((volatile u16*)0x22))


#endif /* MCAL_REG_H_ */
