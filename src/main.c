/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "I2C_LCD.h"
#include "LightStruct.h"
#include "Light_Button.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char buff[20];
uint8_t flag = 0;
uint8_t togflag = 0;
uint8_t cnt=0;

uint8_t curState;
uint8_t prevState = 1;

enum buttonState{
	NOTPUSHED=1, PUSHED=0
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  Light_Switch led1;
  Light_Switch led2;
  Light_Switch led3;

  Light_Button btn1;
  Light_Button btn2;
  Light_Button btn3;
  Light_Button btn4;
  Light_Button btn5;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  light_init(&led1,GPIOB,GPIO_PIN_4);
  light_init(&led2,GPIOB,GPIO_PIN_5);
  light_init(&led3,GPIOB,GPIO_PIN_3);

  button_init(&btn1,GPIOC,GPIO_PIN_7);
  button_init(&btn2,GPIOA,GPIO_PIN_9);
  button_init(&btn3,GPIOA,GPIO_PIN_8);
  button_init(&btn4,GPIOB,GPIO_PIN_10);
  button_init(&btn5,GPIOA,GPIO_PIN_4);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);
  LCD_init();



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int flag = 0;	// on off state
  int i=50;
  int pmflag=0;
  while (1)
  {

	  sprintf(buff,"Simple Fan");
	  LCD_put_cursor(0, 0);
	  LCD_send_str(buff);
	  if(!(button(&btn1)))		//switch 1
	  {
		  led_off(&led1);
		  led_off(&led2);
		  led_off(&led3);
		  TIM3->CCR1 = 0;
		  HAL_Delay(5);
		  sprintf(buff,"Turn Off       ");
		  LCD_put_cursor(1, 0);
		  LCD_send_str(buff);
	  }
	  else if(!(button(&btn2)))	//switch 2
	  {
		  led_on(&led1);
		  led_off(&led2);
		  led_off(&led3);

		  TIM3->CCR1 = 350;
		  HAL_Delay(5);
		  sprintf(buff,"Speed : 35%       ");
		  LCD_put_cursor(1, 0);
		  LCD_send_str(buff);
	  }
	  else if(!(button(&btn3)))	//switch 3
	  {
		  led_off(&led1);
		  led_on(&led2);
		  led_off(&led3);
		  TIM3->CCR1 = 700;
		  HAL_Delay(5);
		  sprintf(buff,"Speed : 60%       ");
		  LCD_put_cursor(1, 0);
		  LCD_send_str(buff);
	  }
	  else if(!(button(&btn4)))	//switch 4
	  {
		  led_off(&led1);
		  led_off(&led2);
		  led_on(&led3);
		  TIM3->CCR1 = 1000;
		  HAL_Delay(5);
		  sprintf(buff,"Speed : 100%     ");
		  LCD_put_cursor(1, 0);
		  LCD_send_str(buff);
	  }
	  curState = button(&btn5);
	  if(curState == PUSHED && prevState == NOTPUSHED)
	  {
		  flag = !flag;
		  if(flag ==0)
		  {
			  sprintf(buff,"mode : normal ");

		  }
		  else
		  {
			  sprintf(buff,"mode : rotate ");
		  }
		  LCD_put_cursor(1, 0);
		  LCD_send_str(buff);

	  }
	  if(flag)
	  {
		TIM10-> CCR1 = i;
		if(pmflag ==0)
		{
			i++;

		}
		if(pmflag ==1)
		{
			i--;
		}

		if(pmflag ==0 && i==250)
		{
			pmflag =1;
		}
		else if (pmflag ==1 && i ==0)
		{
			pmflag =0;
		}
		prevState = 1;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
