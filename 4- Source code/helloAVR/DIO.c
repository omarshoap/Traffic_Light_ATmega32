/*
 * DIO.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


/*
 * DIO.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "REG.h"
#include "BIT_MATH.h"
#include "DIO.h"


void DIO_PIN_DIRECTION(u8 port,u8 pin,u8 status)
{
	switch (status)
	{
	case INPUT:
		switch(port)
		{
		case DIO_PORTA:
			CLR_BIT(DDRA,pin);
			break;
		case DIO_PORTB:
			CLR_BIT(DDRB,pin);
			break;
		case DIO_PORTC:
			CLR_BIT(DDRC,pin);
			break;
		case DIO_PORTD:
			CLR_BIT(DDRD,pin);
			break;
		}
		break;

	case OUTPUT:
		switch(port)
		{
		case DIO_PORTA:
			SET_BIT(DDRA,pin);
			break;
		case DIO_PORTB:
			SET_BIT(DDRB,pin);
			break;
		case DIO_PORTC:
			SET_BIT(DDRC,pin);
			break;
		case DIO_PORTD:
			SET_BIT(DDRD,pin);
			break;
		}
	}
}




void DIO_PIN_WRITE(u8 port,u8 pin,u8 status)
{
	switch (status)
	{
	case LOW:
		switch(port)
		{
		case DIO_PORTA:
			CLR_BIT(PORTA,pin);
			break;
		case DIO_PORTB:
			CLR_BIT(PORTB,pin);
			break;
		case DIO_PORTC:
			CLR_BIT(PORTC,pin);
			break;
		case DIO_PORTD:
			CLR_BIT(PORTD,pin);
			break;
		}
		break;

	case HIGH:
		switch(port)
		{
		case DIO_PORTA:
			SET_BIT(PORTA,pin);
			break;
		case DIO_PORTB:
			SET_BIT(PORTB,pin);
			break;
		case DIO_PORTC:
			SET_BIT(PORTC,pin);
			break;
		case DIO_PORTD:
			SET_BIT(PORTD,pin);
			break;
		}
	}
}

u8 DIO_PIN_READ(u8 port,u8 pin)
{
	u8 value = 0;

		switch(port)
		{
		case DIO_PORTA:
			value = GET_BIT(PINA,pin);
			break;
		case DIO_PORTB:
			value = GET_BIT(PINB,pin);
			break;
		case DIO_PORTC:
			value = GET_BIT(PINC,pin);
			break;
		case DIO_PORTD:
			value = GET_BIT(PIND,pin);
			break;
		}
		return value;
}

void DIO_PIN_TOG(u8 port,u8 pin)
{
		switch(port)
		{
		case DIO_PORTA:
			TOG_BIT(PORTA,pin);
			break;
		case DIO_PORTB:
			TOG_BIT(PORTB,pin);
			break;
		case DIO_PORTC:
			TOG_BIT(PORTC,pin);
			break;
		case DIO_PORTD:
			TOG_BIT(PORTD,pin);
			break;
		}
}



void DIO_PORT_DIRECTION(u8 port,u8 value)
{
	switch(port)
	{
	case DIO_PORTA:
		DDRA = value;
		break;
	case DIO_PORTB:
		DDRB = value;
			break;
	case DIO_PORTC:
		DDRC = value;
			break;
	case DIO_PORTD:
		DDRD = value;
			break;

	}
}

void DIO_PORT_WRITE(u8 port,u8 value)
{

	switch(port)
	{
	case DIO_PORTA:
		PORTA = value;
		break;
	case DIO_PORTB:
		PORTB = value;
			break;
	case DIO_PORTC:
		PORTC = value;
			break;
	case DIO_PORTD:
		PORTD = value;
			break;

	}
}

