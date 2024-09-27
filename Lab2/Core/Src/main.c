/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "time_set.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void Display7SEG(int num);
void Exercise1_Run();
void Exercise2_Run();
void Exercise3_Run();
void Exercise4_Run();
void Exercise5_Run();
void Exercise9_Run();
void Exercise10_Run();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t matrix_buffer [8] ={0b00111100 ,
  							0b01100110 ,
  							0b01100110 ,
  							0b01111110 ,
  							0b01111110 ,
  							0b01100110 ,
  							0b01100110 ,
  							0b01100110 };
  uint16_t column_buffer [8] = {ENM0_Pin,ENM1_Pin,ENM2_Pin,ENM3_Pin,ENM4_Pin,ENM5_Pin,ENM6_Pin,ENM7_Pin};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 ) ;
  Exercise10_Run();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG_D_Pin|SEG_E_Pin|SEG_F_Pin
                          |SEG_G_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_A_Pin SEG_B_Pin SEG_C_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG_D_Pin SEG_E_Pin SEG_F_Pin
                           SEG_G_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG_D_Pin|SEG_E_Pin|SEG_F_Pin
                          |SEG_G_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

 void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
	 timerRun();
}
 void Display7SEG(int num){
	switch(num){
	case 0:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 8:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(SEG_A_GPIO_Port , SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_B_GPIO_Port , SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_C_GPIO_Port , SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_D_GPIO_Port , SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_E_GPIO_Port , SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG_F_GPIO_Port , SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG_G_GPIO_Port , SEG_G_Pin, GPIO_PIN_RESET);
		break;

	}
}
void Exercise1_Run(){
	  setTimer1(50);
	  int led_status = 0;
	  while (1)
	  {
		  if(timer1_flag == 1){
			  switch(led_status){
				  case 0:
					  HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_RESET);
					  HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
					  Display7SEG(1);
					  break;
				  case 1:
					  HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_RESET);
					  HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
					  Display7SEG(2);
					  break;
				  default:
					  break;
			  }
		  setTimer1(50);
		  led_status = 1 - led_status;
		  }
	  }
}
void Exercise2_Run(){
	setTimer1(50);
	setTimer2(100);
	int led_status = 0;
	while (1)
	{
		if(timer1_flag == 1){
			switch(led_status){
			   case 0:
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(1);
				   break;
			   case 1:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(2);
				   break;
			   case 2:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(3);
				   break;
			   case 3:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_RESET);
				   Display7SEG(0);
				   break;
			   default:
				   break;
				   }
			   setTimer1(50);
			   led_status ++;
			   if(led_status >= 4){
				   led_status = 0;
			   }
		 }
		if(timer2_flag == 1){
			HAL_GPIO_TogglePin(DOT_GPIO_Port , DOT_Pin);
			setTimer2(100);
		}
	}
}
void Exercise3_Run(){
	const int MAX_LED = 4;
	int index_led = 0;
	int led_buffer [4] = {9 , 8 , 7 , 6};
	setTimer1(25);
	setTimer2(100);
	int led_status = 0;
	while (1)
	{
		if(timer1_flag == 1){
			switch(led_status){
			   case 0:
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 1:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 2:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 3:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_RESET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   default:
				   break;
				   }
			   setTimer1(25);
			   led_status ++;
			   index_led ++;
			   if(led_status >= 4){
				   led_status = 0;
			   }
			   if(index_led >= MAX_LED){
			   	   index_led = 0;
			   }
		 }
		if(timer2_flag == 1){
			HAL_GPIO_TogglePin(DOT_GPIO_Port , DOT_Pin);
			setTimer2(100);
		}
	}
}
void Exercise4_Run(){
	const int MAX_LED = 4;
	int index_led = 0;
	int led_buffer [4] = {9 , 8 , 7 , 6};
	setTimer1(25);
	setTimer2(100);
	int led_status = 0;
	while (1)
	{
		if(timer1_flag == 1){
			switch(led_status){
			   case 0:
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 1:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 2:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 3:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_RESET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   default:
				   break;
				   }
			   setTimer1(25);
			   led_status ++;
			   index_led ++;
			   if(led_status >= 4){
				   led_status = 0;
			   }
			   if(index_led >= MAX_LED){
			   	   index_led = 0;
			   }
		 }
		if(timer2_flag == 1){
			HAL_GPIO_TogglePin(DOT_GPIO_Port , DOT_Pin);
			setTimer2(100);
		}
	}
}
void Exercise5_Run(){
	int hour = 15, minute = 8, second = 50;
	const int MAX_LED = 4;
	int index_led = 0;
	int led_buffer [4] = {9 , 8 , 7 , 6};
	void updateClockBuffer(){
		led_buffer[0] = hour / 10;
		led_buffer[1] = hour % 10;
		led_buffer[2] = minute / 10;
		led_buffer[3] = minute % 10;
	}
	updateClockBuffer();
	setTimer1(17);
	setTimer2(1);
	int led_status = 0;
	while (1)
	{
		if(timer1_flag == 1){
			switch(led_status){
			   case 0:
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 1:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 2:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   case 3:
				   HAL_GPIO_WritePin(EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN0_GPIO_Port , EN0_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET);
				   HAL_GPIO_WritePin(EN3_GPIO_Port , EN3_Pin , GPIO_PIN_RESET);
				   Display7SEG(led_buffer[index_led]);
				   break;
			   default:
				   break;
				   }

			   setTimer1(17);
			   led_status ++;
			   index_led ++;
			   if(led_status >= MAX_LED){
				   led_status = 0;
			   }
			   if(index_led >= MAX_LED){
			   	   index_led = 0;
			   }
		 }
		if(timer2_flag == 1){
			HAL_GPIO_TogglePin(DOT_GPIO_Port , DOT_Pin);
			if(second >= 60){
			   second = 0;
			   minute ++;
		    }
			if(minute >= 60){
			   minute = 0;
			   hour ++;
			}
		    if(hour >= 12){
			   hour %= 12;
			}
		    second ++;
		    updateClockBuffer();
			setTimer2(1);
		}
	}
}
void clearMatrix(){
	HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);
}
void clearMatrixRow(int index){
  switch ( index ) {
	case 0:
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
		break ;
	case 1:
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
		break ;
	case 2:
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
		break ;
	case 3:
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
		break ;
	case 4:
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
		break ;
	case 5:
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
		break ;
	case 6:
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
		break ;
	case 7:
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);
		break ;
	default :
		break ;
  }
}
void updateLEDMatrix(int index){
  switch ( index ) {
	case 0:
		HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
		break ;
	case 1:
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
		break ;
	case 2:
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
		break ;
	case 3:
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
		break ;
	case 4:
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
		break ;
	case 5:
		HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
		break ;
	case 6:
		HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
		break ;
	case 7:
		HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);
		break ;
	default :
		break ;
  }
  //uint8_t row_data = matrix_buffer[index];
  HAL_GPIO_WritePin(GPIOA, column_buffer[0], (matrix_buffer[index] & 0x01)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[1], (matrix_buffer[index] & 0x02)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[2], (matrix_buffer[index] & 0x04)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[3], (matrix_buffer[index] & 0x08)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[4], (matrix_buffer[index] & 0x10)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[5], (matrix_buffer[index] & 0x20)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[6], (matrix_buffer[index] & 0x40)? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, column_buffer[7], (matrix_buffer[index] & 0x80)? GPIO_PIN_RESET : GPIO_PIN_SET);
}
void Exercise9_Run(){
	setTimer1(2);
	clearMatrix();
	int i = 0;
	while (1) {
		if(timer1_flag == 1) {
			setTimer1(2);
			if(i >= 8) i = 0;

			updateLEDMatrix(i);
			i ++;
		}
	}

}
void Exercise10_Run(){
	setTimer1(2);
	setTimer2(40);
	int i = 0;
	while (1) {
		if(timer1_flag == 1) {
			setTimer1(2);
			if(i >= 8) i = 0;
			clearMatrixRow(i - 1);
			updateLEDMatrix(i);
			i ++;
		}
		if(timer2_flag == 1){
			setTimer2(40);
			for(int i = 0; i < 8; i++){
				uint8_t tmp = matrix_buffer[i] & 0x01;
				matrix_buffer[i] = (matrix_buffer[i] >> 1) | (tmp << 7);
			}
		}
	}
}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
