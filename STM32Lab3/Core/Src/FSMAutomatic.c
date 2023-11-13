/*
 * FSMAutomatic.c
 *
 *  Created on: Nov 13, 2023
 *      Author: hieun
 */
#include "FSMAutomatic.h"

void FSMAutomaticRun() // 1 trạng thái chỉ có 2 phần 1 là todo 2 là chuyển trạng thái và setTimer
{
	switch(status)
	{
	case INIT:
		//TODO
		HAL_GPIO_WritePin(GPIOA, RED_LED_Pin|GREEN_LED_Pin|YELLOW_LED_Pin, SET);

		status = AUTO_RED;
		setTimer1(500); //set timer for AUTO_RED state
		break;
	case AUTO_RED:
		//TODO
		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, RESET);
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, SET);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, SET);

		if(timer1_flag == 1)
		{
			status = AUTO_GREEN;
			setTimer1(300);
		}
		break;
	case AUTO_GREEN:
		//TODO
		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, SET);
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, SET);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, RESET);


		if(timer1_flag == 1)
		{
			status = AUTO_YELLOW;
			setTimer1(200);
		}
		break;
	case AUTO_YELLOW:
		//TODO
		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, SET);
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, RESET);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, SET);

		if(timer1_flag == 1){
			status = AUTO_RED;
			setTimer1(500);
		}
		break;
	default:
		break;
	}
}


