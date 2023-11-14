

#include "LightStruct.h"


void light_init(Light_Switch* light, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  light->GPIOx = GPIOx;
  light->GPIO_PIN_x= GPIO_Pin;
}


void led_on(Light_Switch *On)
{
	HAL_GPIO_WritePin(On->GPIOx, On->GPIO_PIN_x, SET);
}


void led_off(Light_Switch *Off)
{
	HAL_GPIO_WritePin(Off->GPIOx, Off->GPIO_PIN_x, RESET);
}
