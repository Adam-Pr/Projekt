/**
  ******************************************************************************
  * @file    main.c
  * @author  Miroslav Malus, Adam Prochazka,
  *          Brno University of Technology, Czechia
  * @version V1.0
  * @date    Nov 27, 2018
  * @brief   LCD display with LEDs controled by buttons.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
/**
*@mainpage
*@author Miroslav Malus, Adam Prochazka
*/

#include "settings.h"
#include <avr/io.h>
#include <stdlib.h>
#include "lcd.h"            /* Modified version of Peter Fleury's LCD library */
#include <util/delay.h>
#include <avr/interrupt.h>

/* Constants and macros ------------------------------------------------------*/
#define N 950

/* Function prototypes -------------------------------------------------------*/
void setup(void);

/**
  * @brief Main function.
  */
int main(void)
{
    /* Local variables -----------------------------------------------------------*/
    uint8_t number=1,numberSub=0;
    uint8_t run=0,condition=0,time=0, seconds=0, minutes=0, menu1=0, info=1;
    uint16_t i, j;
    char lcd_string[10];

    /* Initializations */
    setup();
    lcd_clrscr();   /* Clear display and set cursor to home position */
    lcd_puts("Informace");  /* Display string */
    lcd_gotoxy(0,1);
    lcd_puts("Vyh. odpovedi");
    lcd_gotoxy(15,0);   /* Set cursor to specified position */
    lcd_putc('*');              /* Display cursor * */
/**
* @par LCD display control
*       - the currently selected item is indicated by *
*       - button DOWN at PD2 is used for scrolling
*       - button SELECT at PD3 is used for selecting chosen item
*
*/


    /* Forever loop */
    while (1)
    {



        /* Button DOWN at PD2 to scroll through the list */
        if(bit_is_clear(PIND,2))
        {
			condition=0;
			time=0;
			menu1=0;
			/* Number stands for the current position in the list */
            number=number+1;

            /* Overrun control */
            if (number==7)
			{
				number = 1;
			}
            switch (number)
            {
                case 1:
                    _delay_ms(250);
                    lcd_gotoxy(0,0);
                    lcd_clrscr();
                    lcd_puts("Informace");
                    lcd_gotoxy(0,1);
                    lcd_puts("Vyh. odpovedi");
                    lcd_gotoxy(15,0);
                    lcd_putc('*');
					break;

                case 2:
                    _delay_ms(250);
                    lcd_gotoxy(0,0);
                    lcd_clrscr();
                    lcd_puts("Informace");
                    lcd_gotoxy(0,1);
                    lcd_puts("Vyh. odpovedi");
                    lcd_gotoxy(15,1);
                    lcd_putc('*');
					break;

                case 3:
                    _delay_ms(250);
                    lcd_gotoxy(0,0);
                    lcd_clrscr();
                    lcd_puts("Podmenu");
                    lcd_gotoxy(0,1);
                    lcd_puts("Odpocet");
                    lcd_gotoxy(15,0);
                    lcd_putc('*');
                    break;

                case 4:
                    _delay_ms(250);
                    lcd_gotoxy(0,0);
                    lcd_clrscr();
                    lcd_puts("Podmenu");
                    lcd_gotoxy(0,1);
                    lcd_puts("Odpocet");
                    lcd_gotoxy(15,1);
                    lcd_putc('*');
                    break;

                case 5:
                    _delay_ms(250);
                    lcd_gotoxy(0,0);
                    lcd_clrscr();
                    lcd_puts("Volny slot-1");
                    lcd_gotoxy(0,1);
                    lcd_puts("Volny slot-2");
                    lcd_gotoxy(15,0);
                    lcd_putc('*');
					break;

                case 6:
                    _delay_ms(250);
                    lcd_gotoxy(0,0);
                    lcd_clrscr();
                    lcd_puts("Volny slot-1");
                    lcd_gotoxy(0,1);
                    lcd_puts("Volny slot-2");
                    lcd_gotoxy(15,1);
                    lcd_putc('*');
					break;

                default:
                    number = 1;
            }  /* End of switch (number) */
        }
        /* Button SELECT at PD3 to choose from the list */
        if(bit_is_clear(PIND,3))
        {
            switch (number)
			{
				case 1:
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("INFORMACE:");
					lcd_gotoxy(0,1);
					lcd_puts("Pouzity Hardware:");

					if(bit_is_clear(PIND,3))
					{
						_delay_ms(250);
						menu1=1;    /* Set menu1 to 1 for browsing through the list of components */
					}
                    break;

				case 2:
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("Vyh. odpovedi");

					if(bit_is_clear(PIND,3))
					{
						_delay_ms(250);
						run=1;  /* Set run to 1 for start of decision application with LEDs */
					}
                    break;

				case 3:
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("POD menu");

					if(bit_is_clear(PIND,3))
					{
						_delay_ms(250);
						condition=1; /* Set condition to 1 to show submenu example */
					}
                    break;

				case 4:
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("Nastaveni casu:");

					if(bit_is_clear(PIND, 3))
					{
						time=1; /* Set time to 1 to set the countdown */
					}
                    break;

				case 5:
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("POD menu-5");
                    break;

				case 6:
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("POD menu-6");
                    break;

				default:
                        number = 1;
			}
        }  /* End of switch (number) */

        /**
        * @par LED diodes control
        *       -  Green LEDs are controled by button at PD0
        *       -  Red LEDs are controled by button at PD1
        *       -  The application is closed by pressing button PD3  (SELECT)
        */


        /* If the condition is met, the evaluation application starts */
        if(run==1)
        {
            /* Green LEDs are controled by button at PD0 */
            if (bit_is_clear(PIND, 0))
            {
                PORTB &= ~_BV(PB4);
                PORTB |= _BV(PB3);
                _delay_ms(1000);
                PORTB &= ~_BV(PB3);
                _delay_ms(1000);
                PORTB |= _BV(PB3);
                _delay_ms(1000);
                PORTB &= ~_BV(PB3);
                _delay_ms(1000);
                PORTB |= _BV(PB3);
                _delay_ms(3000);
                PORTB &= ~_BV(PB3);
            }

            /* Red LEDs are controled by button at PD1*/
            if (bit_is_clear(PIND, 1))
            {
                PORTB &= ~_BV(PB4);
                PORTB |= _BV(PB2);
                _delay_ms(1000);
                PORTB &= ~_BV(PB2);
                _delay_ms(1000);
                PORTB |= _BV(PB2);
                _delay_ms(1000);
                PORTB &= ~_BV(PB2);
                _delay_ms(1000);
                PORTB |= _BV(PB2);
                _delay_ms(3000);
                PORTB &= ~_BV(PB2);
            }
            /* If button PD3 (SELECT) is pressed, the application is closed */
            if(bit_is_clear(PIND, 3))
            {
                PORTB &= ~_BV(PB4);
                _delay_ms(250);
                run=2;          /* Turn off the evaluation application */

            }

            else
            for (i = 1; i < N; i++)
			{
			    /* Green LEDs controled by button on PD0*/
				if (bit_is_clear(PIND, 0))
                {
                    PORTB &= ~_BV(PB4);
                    PORTB |= _BV(PB3);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB3);
                    _delay_ms(1000);
                    PORTB |= _BV(PB3);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB3);
                    _delay_ms(1000);
                    PORTB |= _BV(PB3);
                    _delay_ms(3000);
                    PORTB &= ~_BV(PB3);
                }

                /* Red LEDs controled by button on PD1*/
                if (bit_is_clear(PIND, 1))
                {
                    PORTB &= ~_BV(PB4);
                    PORTB |= _BV(PB2);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB2);
                    _delay_ms(1000);
                    PORTB |= _BV(PB2);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB2);
                    _delay_ms(1000);
                    PORTB |= _BV(PB2);
                    _delay_ms(3000);
                    PORTB &= ~_BV(PB2);
                }

                /* If button PD3 (SELECT) is pressed, the application is closed */
                if(bit_is_clear(PIND, 3))
                {
                    PORTB &= ~_BV(PB4);
                    _delay_ms(250);
                    run=2;      /* Turn off the evaluation application */

                }

                /* Blinking with waiting LEDs */
                PORTB &= ~_BV(PB4);
                for (j = 0; j < i; j++)
                _delay_us(1);

                PORTB |= _BV(PB4);
                for (j = 0; j < (N-i); j++)
                _delay_us(1);


            }

            for (i = N; i > 0; i--)
			{
				/* Blinking with wrong (red) LEDs */
				if (bit_is_clear(PIND, 0))
				{
                    PORTB &= ~_BV(PB4);
                    PORTB |= _BV(PB3);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB3);
                    _delay_ms(1000);
                    PORTB |= _BV(PB3);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB3);
                    _delay_ms(1000);
                    PORTB |= _BV(PB3);
                    _delay_ms(3000);
                    PORTB &= ~_BV(PB3);
                }
                /* Blinking with right (green) LEDs */
                if (bit_is_clear(PIND, 1))
                {
                    PORTB &= ~_BV(PB4);
                    PORTB |= _BV(PB2);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB2);
                    _delay_ms(1000);
                    PORTB |= _BV(PB2);
                    _delay_ms(1000);
                    PORTB &= ~_BV(PB2);
                    _delay_ms(1000);
                    PORTB |= _BV(PB2);
                    _delay_ms(3000);
                    PORTB &= ~_BV(PB2);
                }

                /* If button PD3 (SELECT) is pressed, the application is closed */
                if(bit_is_clear(PIND, 3))
                {
                    PORTB &= ~_BV(PB4);
                    _delay_ms(250);
                    run=2;
                }
                /* Decreasing blinking with waiting (yellow) LEDs */
                PORTB &= ~_BV(PB4);         /* Turn the waiting (yellow) LEDs off */
                for (j = 0; j < i; j++)
                _delay_us(1);

                PORTB |= _BV(PB4);          /* Turn the waiting (yellow) LEDs off */
                for (j = 0; j < (N-i); j++)
                _delay_us(1);
            }
        }  /* End of if (run == 1) */

        /* Turn the waiting (yellow) LEDs off */
        if(run==2)
        {
            PORTB &= ~_BV(PB4);
        }

        /**
        * @par countdown application
        *       - Use button PD0 to set the value of minutes
        *       - Use button PD1 to set the value of seconds
        *       - Use button PD5 to start countdown
        *       - The application shuts down after the countdown ends
        */

        /* If the condition is met, the countdown application starts */
        if(time==1)
        {
			condition=0;
			lcd_gotoxy(10,1);

            /* Use button PD0 to set the value of minutes*/
            if(bit_is_clear(PIND, 0))
            {
				_delay_ms(250);
                minutes++;
                /* Convert int data type to string data type. Function defined in stdlib.h */
                itoa(minutes, lcd_string, 10);      /* Here 10 means Decimal */
                lcd_puts(lcd_string);

                if(minutes==60)
                {
                    minutes=-1;
                }
            }
            /* Use button PD1 to set the value of seconds */
            if(bit_is_clear(PIND, 1))
            {
				_delay_ms(250);
                lcd_gotoxy(12,1);
                lcd_puts(":");
                lcd_gotoxy(13,1);
                seconds++;
                itoa(seconds, lcd_string, 10);
                lcd_puts(lcd_string);

                /* Overrun control */
                if(seconds==60)
                {
                    seconds=-1;
                }
            }
            /* Use button PD5 to start countdown*/
            if(bit_is_clear(PINB, 5))
            {
				if(seconds==0 && minutes==0)
				{
					seconds=0;
					itoa(seconds, lcd_string, 10);
					lcd_puts(lcd_string);
					minutes=0;
					itoa(minutes, lcd_string, 10);
					lcd_puts(lcd_string);

				}

                for(seconds=seconds;seconds<=59;seconds--)
                {
				    _delay_ms(250);
					lcd_gotoxy(13,1);
					itoa(seconds, lcd_string, 10);
					lcd_puts(lcd_string);

					if(seconds==0)
					{
						lcd_gotoxy(10,1);
						minutes--;
						itoa(minutes, lcd_string, 10);
						lcd_puts(lcd_string);
						lcd_gotoxy(13,1);
						seconds=59;
						itoa(seconds, lcd_string, 10);
						lcd_puts(lcd_string);
						if(minutes==0)
						{
							minutes=0;
							itoa(minutes, lcd_string, 10);
							lcd_puts(lcd_string);
							for(seconds=59;seconds>0; seconds--)
							{
								_delay_ms(250);
								lcd_gotoxy(13,1);
								itoa(seconds, lcd_string, 10);
								lcd_puts(lcd_string);
								if(seconds==1)
								{
									seconds=0;
									itoa(seconds, lcd_string, 10);
									lcd_puts(lcd_string);
									lcd_clrscr();
									lcd_puts("Nastaveni casu:");
									lcd_gotoxy(10,1);
									lcd_puts("00:00");
									seconds=1;
								}
							}
						}
					}
				}
				time = 0; /* After the countdown is finished, the application is turned off */
            }
		}  /* End of if (time == 1) */

		/**
        * @par components list
        *       - Use button PD0 to browse through list of components
        */

        /* If the condition is met, the components list is open */
		if(menu1==1)
		{
		    /* Use button PD0 to browse through list of components */
			if(bit_is_clear(PIND, 0))
			{
				info=info+1;
				/* Overrun control */
				if (info==8)
				{
					info = 1;
				}

				switch (info) {
					case 1:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("1x Arduino UNO");
						lcd_gotoxy(0,1);
						lcd_puts("1x LCD displej");
                        break;

					case 2:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("1x LCD displej");
						lcd_gotoxy(0,1);
						lcd_puts("2x NKP");
                        break;

					case 3:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("2x NKP");
						lcd_gotoxy(0,1);
						lcd_puts("1x poten. 10K");
                        break;

					case 4:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("1x poten. 10K");
						lcd_gotoxy(0,1);
						lcd_puts("5x tlacitko");
                        break;

					case 5:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("5x tlacitko");
						lcd_gotoxy(0,1);
						lcd_puts("18x LED");
                        break;

					case 6:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("18x LED");
						lcd_gotoxy(0,1);
						lcd_puts("9x rezistor 1K");
                        break;

					case 7:
						_delay_ms(250);
						lcd_clrscr();
						lcd_gotoxy(0,0);
						lcd_puts("9x rezistor 1K");
						lcd_gotoxy(0,1);
						lcd_puts("propojovaci draty");
                        break;

                    default:
                        info = 1;
				}  /* End of switch (info) */
			}
		}  /* End of if (menu1) */

        /**
        * @par submenu example
        *       - Use button PD1 to browse down through the list
        *       - This demo shows 3 submenus
        */


        /* If the condition is met, the submenu example is ready for browse*/
		if(condition==1)
		{
			/* Use button PD1 to browse down through the list */
			if(bit_is_clear(PIND, 1))
			{
				numberSub=numberSub+1;
				if (numberSub==4)
				{
				numberSub = 1;
				}

				switch (numberSub)
				{
					case 1:
						lcd_gotoxy(12,1);
						_delay_ms(250);
						lcd_gotoxy(0,0);
						lcd_clrscr();
						lcd_puts("pod-pod-MENU-1");
						lcd_gotoxy(0,1);
						lcd_puts("pod-pod-MENU-2");
						lcd_gotoxy(15,0);
						lcd_putc('*');
					break;

					case 2:
						lcd_gotoxy(12,1);
						_delay_ms(250);
						lcd_gotoxy(0,0);
						lcd_clrscr();
						lcd_puts("pod-pod-MENU-1");
						lcd_gotoxy(0,1);
						lcd_puts("pod-pod-MENU-2");
						lcd_gotoxy(15,1);
						lcd_putc('*');
					break;

					case 3:
						lcd_gotoxy(12,1);
						_delay_ms(250);
						lcd_gotoxy(0,0);
						lcd_clrscr();
						lcd_puts("pod-pod-MENU-3");
						lcd_gotoxy(15,0);
						lcd_putc('*');
					break;
				}
			}
		}
    }
	return 0;

}
/**
  * @brief Setup all peripherals.
  * @par
  *     - internal pull-ups resistors at pins are enable for buttons
  *     - input pins for buttons are set
  *     - output pins for LEDs are set
  *     - LEDs are turn off
  */
void setup(void)
{
	/* Initialize display and select type of cursor */
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    /* Clear display and set cursor to home position */
    lcd_clrscr();

	/* Set output pins */
    DDRB |= _BV(PB4);
    DDRB |= _BV(PB3);
    DDRB |= _BV(PB2);

    /* Turn LEDs off */
    PORTB &= ~_BV(PB4);
    PORTB &= ~_BV(PB3);
    PORTB &= ~_BV(PB2);

    /* Set input pins for buttons*/
    DDRD &= ~_BV(PD0);
	DDRD &= ~_BV(PD1);
	DDRD &= ~_BV(PD2);
	DDRD &= ~_BV(PD3);
	DDRB &= ~_BV(PB5);

    /* Activate internal pull-ups for pins */
    PORTD |= _BV(PD0);
    PORTD |= _BV(PD1);
	PORTD |= _BV(PD2);
	PORTD |= _BV(PD3);
	PORTB |= _BV(PB5);

}
/* END OF FILE ****************************************************************/
