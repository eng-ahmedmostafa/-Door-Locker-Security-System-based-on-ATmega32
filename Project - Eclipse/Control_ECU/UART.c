/*
 * UART.c
 *
 *      Author: Ahmed Mostafa
 */

#include "UART.h"
#include "avr/io.h"
#include "common_macros.h"
void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value = 0 ;
	UCSRA = (1<<U2X);


	UCSRB = (1<<RXEN) | (1<<TXEN);

	UCSRC =  ( 1<<URSEL ) | (Config_Ptr->parity <<UPM0) | (Config_Ptr->stop_bit << 3);


	UCSRC = ((UCSRC & 0xF9)| ( (Config_Ptr->bit_data  & 0x3 ) << 1) );

	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);


	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}


/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one
	 * by poling  */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i;

	/* Send the whole string */
	for(i = 0 ; Str[i] != '\0'; i ++)
	{
		UART_sendByte(Str[i]);
	}
}
/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str ,uint8 end_of_str )
{
	uint8 i = 0;
	for( i = 0 ; Str[i] != end_of_str ;i ++ )
	{
		Str[i] = UART_recieveByte();
	}
	/* After receiving the whole string plus the end of str, replace to '\0' */
	Str[i] = '\0';

}

