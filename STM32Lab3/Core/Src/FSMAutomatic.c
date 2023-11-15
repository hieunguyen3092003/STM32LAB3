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
		isButton1Pressed(); // xóa cờ của nút nhấn
		break;
	case AUTO_RED:
		//TODO
		setTrafficRed();

		if(timer1_flag == 1)
		{
			status = AUTO_GREEN;
			setTimer1(300);
		}

		if(isButton1Pressed()==1)
		{
			status = MAN_RED;
			setTimer1(1000);
		}
		break;
	case AUTO_GREEN:
		//TODO
		setTrafficGreen();

		if(timer1_flag == 1)
		{
			status = AUTO_YELLOW;
			setTimer1(200);
		}

		if(isButton1Pressed()==1)
		{
			status = MAN_GREEN;
			setTimer1(1000);
		}
		break;
	case AUTO_YELLOW:
		//TODO
		setTrafficYellow();

		if(timer1_flag == 1){
			status = AUTO_RED;
			setTimer1(500);
		}

		if(isButton1Pressed()==1)
		{
			status = MAN_YELLOW;
			setTimer1(1000);
		}
		break;
	default:
		break;
	}
}


