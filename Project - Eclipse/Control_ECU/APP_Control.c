/*
 * APP_Control.c
 *
 *      Author: Ahemd Mostafa
 */

#include "avr/io.h"
#include "UART.h"
#include "Timer_1.h"
#include "std_types.h"
#include "motor.h"
#include "twi.h"
#include "external_eeprom.h"
#include "util/delay.h"
#include "BUZZER.h"

#define UART_IS_REDY          0
#define UART_PASS_INIT       '*'
#define UART_PASS_UNINIT     '!'
#define UART_DC_MOTOR_OPEN   '#'
#define UART_BZZER_MODE      '$'
#define UART_CHANG_PASS      'A'
#define SIZE_PASS             5

uint8   g_flagUart = 1 ,g_dataUart ,i,
g_tick = 0  , readbyteEEPROM  ;
uint8  passbuff[SIZE_PASS] = {0};

void  sendPassToEEPROM (void);
void  send_to_uart(uint8);
uint8 resevebyte_from_uart(void);
void  dc_motor_open (void);
void  sendPass(void);
void  resevePass(void);
void  cullBackTimer_1(void);
void resevePassEEPROM(void);



int main()
{
	DcMotor_Init();
	Buzzer_init();

	TWI_ConfigType confing_twi = {0x01 , baudrate_400};
	TWI_init(&confing_twi);

	Timer1_ConfigType confing_timer1 = {0 , 7810 , _1024 , COMPARE_MODE } ;
	Timer1_init(&confing_timer1);
	Timer1_setCallBack(cullBackTimer_1);

	UART_ConfigType confing_uart = {_8_bit ,disabled , bit_1 , 9600};
	UART_init(&confing_uart);

	SREG |= (1<<7);


	 EEPROM_readByte(0x100 , &readbyteEEPROM);
		_delay_ms(15);

	if (readbyteEEPROM == 0xFF)
	{
		send_to_uart(UART_PASS_UNINIT);
		resevePass();
		sendPassToEEPROM();
		EEPROM_writeByte(0x100 , 0);
		_delay_ms(15);
	}
	else if (readbyteEEPROM == 0)
	{
		send_to_uart(UART_PASS_INIT);
		resevePassEEPROM();
		sendPass();
	}

	while (1)
	{
		g_dataUart =resevebyte_from_uart();
		switch (g_dataUart)
		{
		case UART_DC_MOTOR_OPEN:
			dc_motor_open();
			break;
		case UART_CHANG_PASS:
			resevePass();
			sendPassToEEPROM();
			break;
		case UART_BZZER_MODE:

			Buzzer_on();
			g_tick = 0;
			while (g_tick !=60 );
			Buzzer_off();
			break;
		}


	}
}


void send_to_uart(uint8 data)
{
	while (UART_recieveByte() != UART_IS_REDY);
	UART_sendByte(UART_IS_REDY);
	UART_sendByte(data);

}

void resevePass(void)
{
	uint8 flag_uart_redy = 1 ;
	while (flag_uart_redy)
	{
		UART_sendByte(UART_IS_REDY);
		flag_uart_redy = UART_recieveByte();
	}
	for (i = 0 ; i < SIZE_PASS ; i ++ )
	{
		passbuff[i] = UART_recieveByte();
	}


}

void sendPass(void)
{
	while (UART_recieveByte() != UART_IS_REDY);
	UART_sendByte(UART_IS_REDY);

	for (i = 0; i < SIZE_PASS ; i ++)
	{
		UART_sendByte(passbuff[i]);
	}

}

uint8 resevebyte_from_uart(void)
{
	uint8 flag_uart_redy = 1 ;
	while (flag_uart_redy)
	{
		UART_sendByte(UART_IS_REDY);
		flag_uart_redy = UART_recieveByte();
	}

	return UART_recieveByte();
}

void dc_motor_open (void)
{
	DcMotor_Rotate(CLOCKWISE , 100);
	g_tick = 0;
	while (g_tick != 15);

	g_tick = 0 ;
	DcMotor_Rotate(stop , 0);
	while (g_tick != 3);
	g_tick = 0 ;
	DcMotor_Rotate(ANTI_CLOCKWISE , 100);
	while(g_tick != 15);
	DcMotor_Rotate(stop , 0);

}

void cullBackTimer_1(void)
{
	g_tick++;
}


void sendPassToEEPROM (void)
{
	for (i = 0 ; i < SIZE_PASS ; i ++ )
	{
		EEPROM_writeByte( i , passbuff[i]);
		_delay_ms(10);
	}
}

void resevePassEEPROM(void)
{
	for (i = 0 ; i < SIZE_PASS ; i ++ )
	{
		EEPROM_readByte(i , &passbuff[i]);
		_delay_ms(10);
	}

}
