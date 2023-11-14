/*
 * LightStruct.h
 *
 *  Created on: Sep 26, 2023
 *      Author: user
 */

#ifndef INC_LIGHTSTRUCT_H_
#define INC_LIGHTSTRUCT_H_
#include "stm32f4xx.h"



typedef struct {
		GPIO_TypeDef * GPIOx;
		uint16_t GPIO_PIN_x;
}Light_Switch;

void light_init(Light_Switch* light, GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN);
void led_on(Light_Switch *On);
void led_off(Light_Switch *Off);

#endif /* INC_LIGHTSTRUCT_H_ */
