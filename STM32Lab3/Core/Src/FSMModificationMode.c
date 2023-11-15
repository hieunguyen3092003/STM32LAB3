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
		isButton1Pressed();
		status = MODIFY_RED;
		setTimer2(25);
		break;

	case MODIFY_RED:
		if(timer2_flag == 1)
		{
			setTimer2(25);
			HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
			HAL_GPIO_TogglePin(RED_LED1_GPIO_Port, RED_LED1_Pin);
		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFY_YELLOW;
			setTimer2(25);
		}
		break;

	case MODIFY_YELLOW:
		if(timer2_flag == 1)
		{
			setTimer2(25);
			HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);
			HAL_GPIO_TogglePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin);
		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFY_GREEN;
			setTimer2(25);
		}
		break;

	case MODIFY_GREEN:
		if(timer2_flag == 1)
		{
			setTimer2(25);
			HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
			HAL_GPIO_TogglePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin);
		}

		if(isButton1Pressed() == 1)
		{
			if(red_time == green_time+yellow_time)
			{
			status = NORMAL_MODE;
			}
		}
		break;

	default:
		break;
	}
}
