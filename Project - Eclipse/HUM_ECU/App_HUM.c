/*
 * AppHUM.c
 *DEVSTYLE
 *      Author: Ahmed Mostafa
 */

#include "LCD.h"
#include "UART.h"
#include "keypad.h"
#include "std_types.h"
#include "Timer_1.h"
#include "util/delay.h"
#include "avr/io.h"

#define SIZE_PASS        5

#define SUCESS           1
#define ERORR            0

#define MATCHED          0
#define UNMATCHED        1


#define UART_IS_REDY          0
#define UART_PASS_INIT       '*'
#define UART_PASS_UNINIT     '!'
#define UART_DC_MOTOR_OPEN   '#'
#define UART_BZZER_MODE      '$'
#define UART_CHANG_PASS      'A'






uint8 g_passInit[SIZE_PASS] ={0} , g_passcheak[SIZE_PASS] = {0};
uint8   i,g_keyMood , flag_uartPassInit = 0  ,g_tick, g_warning = 0 ;


uint8 cheak_pass (void);
void pass_init (void);
uint8 re_enter (void);
uint8 resevebyte_from_uart(void);
void send_to_uart(uint8 data);
void resevePass(void);
void sendPass(void);
void cullBackTimer_1(void);
int main()
{
	SREG = (1<<7);


	UART_ConfigType confing_uart = {_8_bit ,disabled , bit_1 , 9600};
	UART_init(&confing_uart);
	Timer1_ConfigType confing_timer1 = {0 , 7810 , _1024 , COMPARE_MODE } ;
	Timer1_init(&confing_timer1);
	Timer1_setCallBack(cullBackTimer_1);


	LCD_init();
	flag_uartPassInit = resevebyte_from_uart();

	if (flag_uartPassInit == UART_PASS_INIT )
	{
		resevePass();
		LCD_clearScreen();
		LCD_displayString("pass init");
		_delay_ms(1000);
	}
	else if (flag_uartPassInit == UART_PASS_UNINIT)
	{
		do{
			pass_init();

		}while(re_enter());
		sendPass();
	}
	LCD_clearScreen();


	while (1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+ : OPEN DOOR");
		LCD_displayStringRowColumn(1, 0, "- : CHANGE PASS");
		g_keyMood = KEYPAD_getPressedKey();
		_delay_ms(500);
		switch (g_keyMood)
		{
		case '+':
			if (cheak_pass())
			{
				send_to_uart(UART_DC_MOTOR_OPEN);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "DOOR is OPINIG");
				g_tick = 0;
				while(g_tick !=33);

			}
			else
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "NOT matching");
				g_warning++;
				LCD_moveCursor(1,3);
				LCD_intgerToString((3 - g_warning));
				LCD_displayString(" chanses");
				_delay_ms(1500);

			}

			break;
		case '-':
			if (cheak_pass())
			{
				LCD_clearScreen();
				do{
					pass_init();

				}while(re_enter());
				send_to_uart(UART_CHANG_PASS);
				sendPass();
				LCD_clearScreen();
				LCD_displayString("PASS is change");
				_delay_ms(1000);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "NOT matching");
				g_warning++;
				LCD_moveCursor(1,3);
				LCD_intgerToString((3 - g_warning));
				LCD_displayString(" chanses");
				_delay_ms(1500);

			}
			break;
		}
		if (g_warning == 3)
		{

			send_to_uart(UART_BZZER_MODE);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,2,"!!warning!!");
			g_tick = 0;
			while (g_tick !=60 );
		}

	}

}
uint8 cheak_pass (void)
{
	uint8 l_key , l_flagCheakPass = SUCESS;
	LCD_clearScreen();
	LCD_displayString("Enter Pass check:");
	for (i = 0 ; i  < SIZE_PASS ; i ++ )
	{
		l_key= KEYPAD_getPressedKey();

		if (!((l_key >= 0  ) && (l_key <= 9  )))
		{
			i--;

		}
		else
		{
			g_passcheak[i] = l_key;
			_delay_ms(300);

			LCD_moveCursor(1 , (i+2));
			LCD_displayStringRowColumn(1 ,(i+2) ,"*" );

			if (g_passcheak[i] != g_passInit[i])
			{
				l_flagCheakPass = ERORR ;
			}


		}
	}

	return l_flagCheakPass ;
}


void pass_init (void)
{
	uint8 l_key  ;

	LCD_clearScreen();
	LCD_displayString("Enter Pass init:");

	for (i = 0 ; i < SIZE_PASS ; i ++ )
	{
		l_key= KEYPAD_getPressedKey();
		_delay_ms(300);

		/*
		 * to make sure input is PIN
		 * */
		if (!((l_key >= 0  ) && (l_key <= 9  )))
		{
			i--;
			_delay_ms(500);

		}
		else
		{
			g_passInit[i] = l_key;

			LCD_moveCursor(1 , i+2);

			LCD_displayStringRowColumn(1 ,(i+2) ,"*" );
		}
	}


}
uint8 re_enter (void)
{
	uint8 l_key , l_flagPassInit = MATCHED ;

	LCD_clearScreen();
	LCD_displayString("re-Enter Pass :");
	for (i = 0 ; i < SIZE_PASS ; i ++ )
	{
		l_key= KEYPAD_getPressedKey();
		_delay_ms(300);

		/*
		 * to make sure input is PIN
		 * */
		if (!((l_key >= 0  ) && (l_key <= 9  )))
		{
			i--;
		}
		else
		{
			g_passcheak[i] = l_key;
			LCD_moveCursor(1 , i+2);
			LCD_displayStringRowColumn(1 ,i+2  ,"*" );
			if (g_passcheak[i] != g_passInit[i])
			{
				l_flagPassInit = UNMATCHED;
			}

		}

	}

	return l_flagPassInit;
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
		g_passInit[i] = UART_recieveByte();
	}


}

void sendPass(void)
{
	while (UART_recieveByte() != UART_IS_REDY);
	UART_sendByte(UART_IS_REDY);

	for (i = 0; i < SIZE_PASS ; i ++)
	{
		UART_sendByte(g_passInit[i]);
	}

}


void cullBackTimer_1(void)
{
	g_tick++;
}

