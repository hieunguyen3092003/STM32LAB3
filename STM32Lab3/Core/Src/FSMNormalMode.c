/*
 * FSMNormalMode.c
 *
 *  Created on: Nov 14, 2023
 *      Author: hieun
 */

#include "FSMNormalMode.h"


void FSMNormalModeRun()
{
	switch(status)
	{
	case NORMAL_MODE:
		resetInitialState(); 	// reset all all the varialbles thats affect FSMNormalModeRun

		status = RED0_GREEN1; 	//next mode
		setTimer1(green_time);	//set timer for next state

		// initial setting led 7 seg
		setLedBuffer(red_time, green_time);
		setTimer2(scan_led_time);
		timer2_flag = 1; // ngay lap tuc chay led 7 doan
		setTimer3(100); // timer update buffer in led 7 seg
		break;

	case RED0_GREEN1:
		setTrafficRed();
		setTrafficGreen1();

		if(timer2_flag == 1)	// display 4 segment led
		{
			setTimer2(scan_led_time);
			if(count > 3)
			{
				count = 0;
			}
			sevenSegDisplay(count++);
		}

		if(timer3_flag == 1)	//update buffer every second
		{
			updateLedBuffer();
			setTimer3(100);
		}

		if(timer1_flag == 1)
		{
			status = RED0_YELLOW1;	//next mode
			setTimer1(yellow_time);

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

		if(timer2_flag == 1)	// display 4 segment led
		{
			if(count > 3)
			{
				count = 0;
			}

			sevenSegDisplay(count++);
			setTimer2(scan_led_time);
		}

		if(timer3_flag == 1)	//update buffer every second
		{
			updateLedBuffer();
			setTimer3(100);
		}

		if(timer1_flag == 1)
		{
			status = GREEN0_RED1;	//next mode
			setTimer1(green_time);	//set_timer for next mode

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
			status = YELLOW0_RED1;
			setTimer1(yellow_time);

			setLedBuffer(yellow_time, yellow_time);	// set buffer for led 7 seg
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
			status = RED0_GREEN1;
			setTimer1(green_time);

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
