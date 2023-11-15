/*
 * FSMModificationMode.c
 *
 *  Created on: Nov 15, 2023
 *      Author: hieun
 */
#include "FSMModificationMode.h"

void FSMModificationModeRun()
{
	switch(status)
	{
	case MODIFICATION_MODE:
		HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|GREEN_LED1_Pin|YELLOW_LED1_Pin|RED_LED_Pin
		                          |GREEN_LED_Pin|YELLOW_LED_Pin|EN0_Pin|EN1_Pin
		                          |EN2_Pin|EN3_Pin, SET);
		HAL_GPIO_WritePin(GPIOB, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
		                          |E_LED_Pin|F_LED_Pin|G_LED_Pin, SET);
		count = 0; // reset count
		isButton1Pressed(); // reset button1_flag
		isButton2Pressed();
		isButton3Pressed();

		status = MODIFY_RED;
		setTimer2(scan_led_time);
		timer2_flag = 1; // ngay lap tuc chay led 7 doan
		setLedBuffer(0, 1);

		setTimer4(25);
		break;

	case MODIFY_RED:
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


		if(isButton1Pressed() == 1)
		{
			status = MODIFY_YELLOW;

			isButton1Pressed(); // reset button_flag
			isButton2Pressed();
			isButton3Pressed();

			count = 0;
			setLedBuffer(0, 2);
			setTimer4(25);
			setTimer2(scan_led_time);
			timer2_flag = 1; // ngay lap tuc chay led 7 doan
		}

		if(isButton2Pressed() == 1)
		{
			HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|GREEN_LED1_Pin|YELLOW_LED1_Pin|RED_LED_Pin
			                          |GREEN_LED_Pin|YELLOW_LED_Pin|EN0_Pin|EN1_Pin
			                          |EN2_Pin|EN3_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
			                          |E_LED_Pin|F_LED_Pin|G_LED_Pin, SET);
			count = 0;
			red_time = 1;
			setLedBuffer(red_time, 1);
			status = MODIFY_TIME_RED;

			isButton1Pressed(); // reset button1_flag
			isButton2Pressed();
			isButton3Pressed();
		}
		break;

	case MODIFY_YELLOW:
		if(timer4_flag == 1)
		{
			setTimer4(25);

			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, SET);
			HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, SET);
			HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, SET);
			HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, SET);

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

		if(isButton1Pressed() == 1)
		{
			status = MODIFY_GREEN;

			isButton1Pressed(); // reset button1_flag
			isButton2Pressed();
			isButton3Pressed();

			count = 0;
			setLedBuffer(0, 3);
			setTimer4(25);
		}

		if(isButton2Pressed() == 1)
		{
			HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|GREEN_LED1_Pin|YELLOW_LED1_Pin|RED_LED_Pin
			                          |GREEN_LED_Pin|YELLOW_LED_Pin|EN0_Pin|EN1_Pin
			                          |EN2_Pin|EN3_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
			                          |E_LED_Pin|F_LED_Pin|G_LED_Pin, SET);
			count = 0;
			yellow_time = 1;
			setLedBuffer(yellow_time, 2);
			status = MODIFY_TIME_YELLOW;

			isButton1Pressed(); // reset button1_flag
			isButton2Pressed();
			isButton3Pressed();
		}
		break;

	case MODIFY_GREEN:
		if(timer4_flag == 1)
		{
			setTimer4(25);

			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, SET);
			HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, SET);
			HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, SET);
			HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, SET);

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

		if(isButton1Pressed() == 1)
		{
			count = 0;
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

		if(isButton2Pressed() == 1)
		{
			HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|GREEN_LED1_Pin|YELLOW_LED1_Pin|RED_LED_Pin
			                          |GREEN_LED_Pin|YELLOW_LED_Pin|EN0_Pin|EN1_Pin
			                          |EN2_Pin|EN3_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
			                          |E_LED_Pin|F_LED_Pin|G_LED_Pin, SET);
			count = 0;
			green_time = 1;
			setLedBuffer(green_time, 3);
			status = MODIFY_TIME_GREEN;

			isButton1Pressed(); // reset button1_flag
			isButton2Pressed();
			isButton3Pressed();
		}
		break;

	default:
		break;
	}
}
