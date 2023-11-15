/*
 * FSMLightModification.c
 *
 *  Created on: Nov 15, 2023
 *      Author: hieun
 */

#include "FSMLightModification.h"

void FSMLightModification()
{
	switch(status)
	{
	case MODIFY_TIME_RED:
		if(timer4_flag == 1)
		{
			setTimer4(25);
			HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
			HAL_GPIO_TogglePin(RED_LED1_GPIO_Port, RED_LED1_Pin);
		}

		if(timer2_flag == 1)
		{
			setTimer2(scan_led_time);
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
		}

		if(isButton2Pressed() == 1)
		{
			resetInitialState();

			red_time++;
			setLedBuffer(red_time, 1);
		}

		if(isButton3Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_YELLOW;	//next mode
			setTimer4(25);

			setLedBuffer(0, 2);
		}
		break;

	case MODIFY_TIME_YELLOW:
		if(timer4_flag == 1)
		{
			setTimer4(25);
			HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);
			HAL_GPIO_TogglePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin);
		}

		if(timer2_flag == 1)
		{
			setTimer2(scan_led_time);
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
		}

		if(isButton2Pressed() == 1)
		{
			resetInitialState();

			yellow_time++;
			setLedBuffer(yellow_time, 2);
		}

		if(isButton3Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_GREEN;	//next mode
			setTimer4(25);

			setLedBuffer(0, 3);
		}
		break;

	case MODIFY_TIME_GREEN:
		if(timer4_flag == 1)
		{
			setTimer4(25);

			HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
			HAL_GPIO_TogglePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin);
		}

		if(timer2_flag == 1)
		{
			setTimer2(scan_led_time);
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
		}

		if(isButton2Pressed() == 1)
		{
			resetInitialState();

			green_time++;
			setLedBuffer(green_time, 3);
		}

		if(isButton3Pressed() == 1)
		{
			if(red_time == green_time+yellow_time)
			{
				status = NORMAL_MODE;
			}
			else
			{
				if(red_time > green_time+yellow_time)
				{
					green_time = red_time - yellow_time;
					status = NORMAL_MODE;
				}
				else
				{
					red_time = green_time + yellow_time;
					status = NORMAL_MODE;
				}
			}
		}
		break;
	default:
		break;
	}
}

