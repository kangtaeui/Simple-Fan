/*
 * LightButton.c
 *
 *  Created on: Sep 26, 2023
 *      Author: user
 */
#include "Light_Button.h"
void button_init(Light_Button *btn, GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN_x)
{
	btn->GPIOx = GPIOx;
	btn->GPIO_PIN_x = GPIO_PIN_x;
}

int button(Light_Button *btn)
{
	return HAL_GPIO_ReadPin(btn ->GPIOx, btn->GPIO_PIN_x);
}
