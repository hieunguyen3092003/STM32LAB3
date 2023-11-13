/*
 * button.c
 *
 *  Created on: Nov 12, 2023
 *      Author: hieun
 */

#include "button.h"

int key_reg0 = NORMAL_STATE;
int key_reg1 = NORMAL_STATE;
int key_reg2 = NORMAL_STATE; // #define NORMAL_STATE  GPIO_PIN_SET

int key_reg3 = NORMAL_STATE; // key_reg3 dùng để xử lý nhấn đè
int timer_for_key_press = 200;

int button1_flag = 0;

int isButton1Pressed() // nếu nút được nhấn thì hàm trả về 1
{
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	else return 0;
}

void flagProcess() // hàm này chỉ đề set cờ khi mà nút được nhấn
{
	button1_flag = 1; // set flag để xử lý trên while(1)
}

void getKeyInput()  //goi = timer moi 10ms 1 lan
{
	key_reg0 = key_reg1;
	key_reg1 = key_reg2;
	key_reg2 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin); // key_reg2 đọc giá trị của nút nhấn
	if((key_reg0 == key_reg1) && (key_reg1 == key_reg2)) // chống rung
	{
		if(key_reg3 != key_reg2) // xử lý khi nhấn
		{
			key_reg3 = key_reg2;
			if(key_reg2 == PRESSED_STATE)
			{
				flagProcess();
				timer_for_key_press = 200; // gán lại lên 2s
			}
		}
		else // xử lý nhấn đè (key_reg3 == key_reg2)
		{
			timer_for_key_press--;
			if(timer_for_key_press == 0)
			{
				key_reg3 = NORMAL_STATE; // gán key_reg3 thành NORMAL_STATE sẽ reset trường hợp nhấn đè lên lại trường hợp nhấn
			}
		}
	}
}

