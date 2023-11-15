/*
 * FSMNormalMode.c
 *
 *  Created on: Nov 14, 2023
 *      Author: hieun
 */

#include "FSMNormalMode.h"

int count = 0;

void FSMNormalModeRun()
{
	switch(status)
	{
	case NORMAL_MODE:
		HAL_GPIO_WritePin(GPIOA, RED_LED_Pin|GREEN_LED_Pin|YELLOW_LED_Pin|RED_LED1_Pin|GREEN_LED1_Pin|YELLOW_LED1_Pin, SET);

		status = RED0_GREEN1;
		setTimer1(green_time);

		setLedBuffer(red_time, green_time); // set buffer for led 7 seg
		setTimer2(scan_led_time);
		timer2_flag = 1; // ngay lap tuc chay led 7 doan
		setTimer3(100); // 1s sau update led_buffer

		isButton1Pressed(); // delete button1_flag
		break;

	case RED0_GREEN1:
		setTrafficRed();
		setTrafficGreen1();

		if(timer2_flag == 1)
		{
			setTimer2(scan_led_time);
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
		}

		if(timer3_flag == 1)
		{
			updateLedBuffer();
			setTimer3(100);
		}

		if(timer1_flag == 1)
		{
			setTimer1(yellow_time);
			status = RED0_YELLOW1;

			setLedBuffer(yellow_time, yellow_time); // set buffer for led 7 seg

		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
		}
		break;

	case RED0_YELLOW1:
		setTrafficRed();
		setTrafficYellow1();

		if(timer2_flag == 1)
		{
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
			setTimer2(scan_led_time);
		}

		if(timer3_flag == 1)
		{
			updateLedBuffer();
			setTimer3(100);
		}

		if(timer1_flag == 1)
		{
			setTimer1(green_time);
			status = GREEN0_RED1;

			setLedBuffer(green_time, red_time); // set buffer for led 7 seg
		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
		}
		break;

	case GREEN0_RED1:
		setTrafficGreen();
		setTrafficRed1();

		//set led 7 seg
		if(timer2_flag == 1)
		{
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
			setTimer2(scan_led_time);
		}

		if(timer3_flag == 1)
		{
			updateLedBuffer();
			setTimer3(100);
		}

		if(timer1_flag==1)
		{
			setTimer1(yellow_time);
			status = YELLOW0_RED1;

			setLedBuffer(yellow_time, yellow_time); // set buffer for led 7 seg
		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
		}
		break;

	case YELLOW0_RED1:
		setTrafficYellow();
		setTrafficRed1();

		if(timer2_flag == 1)
		{
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
			setTimer2(scan_led_time);
		}

		if(timer3_flag == 1)
		{
			updateLedBuffer();
			setTimer3(100);
		}

		if(timer1_flag == 1)
		{
			setTimer1(green_time);
			status = RED0_GREEN1;

			setLedBuffer(red_time, green_time); // set buffer for led 7 seg
		}
		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
		}
		break;

	default:
		break;
	}
}
