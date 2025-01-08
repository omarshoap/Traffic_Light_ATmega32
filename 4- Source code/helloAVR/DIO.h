/*
 * DIO.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_


#include "STD_TYPES.h"


#define DIO_PORTA    0
#define DIO_PORTB    1
#define DIO_PORTC    2
#define DIO_PORTD    3

#define INPUT    0
#define OUTPUT   1

#define HIGH     1
#define LOW      0

void DIO_PIN_DIRECTION(u8,u8,u8);
void DIO_PIN_WRITE(u8,u8,u8);
void DIO_PIN_TOG(u8 ,u8 );
void DIO_PORT_DIRECTION(u8 ,u8 );
void DIO_PORT_WRITE(u8 ,u8 );
u8 DIO_PIN_READ(u8 ,u8 );


#endif /* MCAL_DIO_DIO_H_ */
