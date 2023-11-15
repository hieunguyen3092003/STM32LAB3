/*
 * global.c
 *
 *  Created on: Nov 13, 2023
 *      Author: hieun
 */
#include "global.h"

int count = 0;

int status = 0;
int red_time = 5;
int green_time = 3;
int yellow_time = 2;

//SET TRAFFIC LIGHT FUNCTION
void setTrafficRed()
{
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, RESET);
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, SET);
	HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, SET);
}
void setTrafficGreen()
{
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, SET);
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, RESET);
	HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, SET);
}
void setTrafficYellow()
{
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, SET);
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, SET);
	HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, RESET);
}

void setTrafficRed1()
{
	HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, RESET);
	HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, SET);
	HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, SET);
}
void setTrafficGreen1()
{
	HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, SET);
	HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, RESET);
	HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, SET);
}
void setTrafficYellow1()
{
	HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, SET);
	HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, SET);
	HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, RESET);
}

const int scan_led_time = 25;

int led_buffer[4] = {1, 2, 3, 4};
void setLedBuffer(int first_led_time, int second_led_time)
{
	led_buffer[0] = first_led_time / 10;
	led_buffer[1] = first_led_time % 10;
	led_buffer[2] = second_led_time / 10;
	led_buffer[3] = second_led_time % 10;
}

void updateLedBuffer()
{
	//TODO
	if(led_buffer[1] <= 0)
	{
		led_buffer[0]--;
		led_buffer[1] = 9;
	}
	else
	{
		led_buffer[1]--;
	}
	if(led_buffer[3] <= 0)
	{
		led_buffer[2]--;
		led_buffer[3] = 9;
	}
	else
	{
		led_buffer[3]--;
	}
}


void sevenSegDisplay(int num)
{
	uint16_t LED7SEG[10] = {0x003F, 0x0006, 0x005B, 0x004F, 0x0066, 0x006D, 0x007D, 0x0007, 0x007F, 0x006F};
	GPIOB->ODR = ~LED7SEG[led_buffer[num]];
	switch(num)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA,EN1_Pin|EN2_Pin|EN3_Pin, SET);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA,EN0_Pin|EN2_Pin|EN3_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA,EN0_Pin|EN1_Pin|EN3_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA,EN0_Pin|EN1_Pin|EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		break;
	default:

		break;
	}
}

void resetInitialState()
{
	count = 0;
	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|GREEN_LED1_Pin|YELLOW_LED1_Pin|RED_LED_Pin
	                          |GREEN_LED_Pin|YELLOW_LED_Pin|EN0_Pin|EN1_Pin
	                          |EN2_Pin|EN3_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
	                          |E_LED_Pin|F_LED_Pin|G_LED_Pin, SET);

	timer1_flag = 0;
	timer2_flag = 0;
	timer3_flag = 0;
	timer4_flag = 0;

	isButton1Pressed(); // delete all button_flag
	isButton2Pressed();
	isButton3Pressed();
}

