/*
 * Light_Button.h
 *
 *  Created on: Sep 26, 2023
 *      Author: user
 */

#ifndef INC_LIGHT_BUTTON_H_
#define INC_LIGHT_BUTTON_H_
#include "stm32f4xx.h"


typedef struct{
		GPIO_TypeDef *GPIOx;
		uint16_t GPIO_PIN_x;
}Light_Button;

void button_init(Light_Button *btn,GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x);
int button1(Light_Button *btn1);
int button2(Light_Button *btn2);
int button3(Light_Button *btn3);
int button4(Light_Button *btn4);

#endif /* INC_LIGHT_BUTTON_H_ */
