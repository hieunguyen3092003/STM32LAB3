/*
 * FSMManual.c
 *
 *  Created on: Nov 14, 2023
 *      Author: hieun
 */
#include "FSMManual.h"

void FSMManualRun()
{
	switch(status)
	{
		case MAN_RED:
			//TODO
			setTrafficRed();

			if(timer1_flag == 1)
			{
				status = AUTO_RED;
				setTimer1(500);
			}
			if(isButton1Pressed() == 1) // nhấn thì hàm isButtonPressed() trả về giá trị 1
			{
				status = MAN_GREEN;
				setTimer1(1000);
			}
			break;
		case MAN_GREEN:
			//TODO
			setTrafficGreen();

			if(timer1_flag == 1)
			{
				status = AUTO_GREEN;
				setTimer1(300);
			}
			if(isButton1Pressed() ==  1)
			{
				status = MAN_YELLOW;
				setTimer1(1000);
			}
			break;
		case MAN_YELLOW:
			//TODO
			setTrafficYellow();

			if(timer1_flag == 1)
			{
				status = AUTO_YELLOW;
				setTimer1(200);
			}
			if(isButton1Pressed() == 1)
			{
				status = MAN_RED;
				setTimer1(1000);
			}
			break;
		default:
			break;
	}
}
