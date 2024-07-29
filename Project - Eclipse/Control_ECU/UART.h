/*
 * UART.h
 *
 *      Author: ahmed mostafa
 */

#ifndef UART_H_
#define UART_H_
#include "std_types.h"

typedef enum
{
	bit_1 , bit_2
}UART_StopBit;

typedef enum
{
	_5_bit , _6_bit, _7_bit , _8_bit , _9_bit = 7
}UART_BitData;

typedef enum
{
	disabled , reserved, even_Parity , odd_Parity
}UART_Parity;



typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 uint16 baud_rate;
}UART_ConfigType;


void UART_init(const UART_ConfigType * Config_Ptr);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str ,uint8 end_of_str );

#endif /* UART_H_ */
