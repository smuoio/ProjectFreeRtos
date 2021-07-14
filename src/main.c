/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "Config.h"
#include "SharedMemory.h"
#include "IOTask.h"
#include "IOMap.h"
#include "Console.h"
#include "FreeRTOS_CLI.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;
//DMA_HandleTypeDef hdma_usart2_rx;

osThreadId defaultTaskHandle;
osThreadId Task_I0Handle;
osThreadId ApplicationTaskHandle;
osThreadId ConsolleTaskHandle;
osMessageQId ConsoleQueueHandle;
osMutexId MutexMemRamHandle;
osMutexId MutexApplTaskHandle;
osSemaphoreId ConsoleBinarySemHandle;

/* USER CODE BEGIN PV */
TIM_HandleTypeDef htim2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
//static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);
void StartTaskIO(void const * argument);
void StartApplicationTask(void const * argument);
void StartConsolleTask(void const * argument);

static BaseType_t helpcommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
/* USER CODE BEGIN PFP */
static uint8_t rcvd;

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
  ConfigInit();
  MX_GPIO_Init();
  MX_TIM2_Init();
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  //MX_DMA_Init();
  MX_USART2_UART_Init();
  __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
  IOMap_init();
  sm_open();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* Create the mutex(es) */
  /* definition and creation of MutexMemRam */
  osMutexDef(MutexMemRam);
  MutexMemRamHandle = osMutexCreate(osMutex(MutexMemRam));
  osMutexDef(MutexApplTask);
  MutexApplTaskHandle = osMutexCreate(osMutex(MutexApplTask));
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* Create the semaphores(s) */
  /* definition and creation of ConsoleBinarySem */
  osSemaphoreDef(ConsoleBinarySem);
  ConsoleBinarySemHandle = osSemaphoreCreate(osSemaphore(ConsoleBinarySem), 1);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  osMessageQDef(ConsoleQueue, 1, uint8_t);
  ConsoleQueueHandle = osMessageCreate(osMessageQ(ConsoleQueue), NULL);
  printf("ConsoleQueueHandle = %x\n\r", ConsoleQueueHandle);

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
   osThreadDef(defaultTask, StartDefaultTask, osPriorityRealtime, 0, 128);
   defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

   /* definition and creation of Task_IO*/
   osThreadDef(Task_I0, StartTaskIO, osPriorityHigh, 0, 128);
   Task_I0Handle = osThreadCreate(osThread(Task_I0), NULL);

   /* definition and creation of ApplicationTAsk*/
   osThreadDef(ApplicationTask, StartApplicationTask, osPriorityNormal, 0, 128);
   ApplicationTaskHandle = osThreadCreate(osThread(ApplicationTask), NULL);

   /* definition and creation of ConsolleTask */
   osThreadDef(ConsolleTask, StartConsolleTask, osPriorityNormal, 0, 128);
   ConsolleTaskHandle = osThreadCreate(osThread(ConsolleTask), NULL);

   /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */
//   HAL_UART_Receive_IT(&huart2, (uint8_t*)&rcvd, 1);
  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 288;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
/*static void MX_DMA_Init(void)
{

//
  __HAL_RCC_DMA1_CLK_ENABLE();

  // DMA interrupt init
  // DMA1_Stream5_IRQn interrupt configuration
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}
*/

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
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xffff;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level*/
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
   GPIO_InitStruct.Pin = LD2_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}



/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  char *msg = "StartDefaultTask!\n\r";
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartTaskIO */
/**
* @brief Function implementing the Task_I0 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskIO */
void StartTaskIO(void const * argument)
{
  /* USER CODE BEGIN StartTaskIO */
  uint8_t iotask_is_master = 0x0U;
  //unsigned char *lBuffer;
  char *msg = "StartTaskIO!\n\r";
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
  /* Infinite loop */
  //lBuffer = &GetIoTask()->ownbus.buspacketrx.DataRx[0];
  for(;;)
  {
	osMutexWait(MutexMemRamHandle, 0);
	sm_rcvfromapplicationtask(RECV_FROM_APPLIACTION_TASK, GetIoTask(), (uint8_t*)&iotask_is_master);
	// protocol!!!->> layer red and write
	//HAL_UART_Receive_IT(&huart2, (uint8_t*)&rcvd, 1);
	IOTAsk_Input(GetIoTask(), GetApplicationTask());
	//ProtocolInput(lBuffer);
	// read the data from the hw
    sm_sendtoapplicationtask(IOTask_SEND_TO, GetApplicationTask(), 1);
    osDelay(1);
    osMutexRelease(MutexMemRamHandle);
  }
  /* USER CODE END StartTaskIO */
}

/* USER CODE BEGIN Header_StartApplicationTask */
/**
* @brief Function implementing the ApplicationTAsk thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartApplicationTask */
void StartApplicationTask(void const * argument)
{
  /* USER CODE BEGIN StartApplicationTask */
  /* Infinite loop */
  uint8_t applicationtask_is_master = 0x0U;
  static char *msg = "StartApplicationTask-loop!\n\r";
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
  for(;;)
  {
	  osMutexWait(MutexApplTaskHandle, 0);
	//sm_rcvfromiotask(RECV_FROM_IOTASK, GetApplicationTask(), (uint8_t*)&applicationtask_is_master);
   //HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
	//sm_sendtoiotask(APPLIACTION_TASK_SEND_TO, GetIoTask(), 1);

/*	  		if(HAL_UART_Receive_IT(&huart2, (uint8_t*)&rcvd, 1) == HAL_OK)//, 0x64);
	  		{
	  			HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
	  		}*/
	  //HAL_UART_Receive_IT(&huart2, (uint8_t*)&rcvd, 1);
	  //osMessagePut(ConsoleQueueHandle, '\r', 10);
    osDelay(50);
    osMutexRelease(MutexApplTaskHandle);
  }
  /* USER CODE END StartApplicationTask */
}

/* USER CODE BEGIN Header_StartConsolleTask */
/**
* @brief Function implementing the ConsolleTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartConsolleTask */

static const CLI_Command_Definition_t helpCmd =
{
	"h", /* The command string to type. */
	"\r\n h <help>:\r\n help function\r\n",
	helpcommand, /* The function to run. */
	1 /* One parameter is expected. */
};



void StartConsolleTask(void const * argument)
{
  /* USER CODE BEGIN StartConsolleTask */
  /* Infinite loop */
  //uint32_t TickDelay = pdMS_TO_TICKS(3000);
  char *pcOutputString;
  static char *msg = "StartConsolleTask-loop!\n\r";
  //Peripheral_Descriptor_t xConsole;
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
  FreeRTOS_CLIRegisterCommand(&helpCmd);
  pcOutputString = FreeRTOS_CLIGetOutputBuffer();
  for(;;)
  {
	  Console();
	  //HAL_UART_Receive_IT(&huart2, &rcvd, 1);
	 // osMessageGet(ConsoleQueueHandle, 10);
	  //	  HAL_UART_Receive_IT(&huart2, (uint8_t*)&rcvd, 1);
//	  if(rcvd == '\r')
	  //HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
	  //Console();
	//HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
	//if(osSemaphoreWait(ConsoleBinarySemHandle, osWaitForever) == osOK)
	osDelay(100);
  }
  /* USER CODE END StartConsolleTask */
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	  //Peripheral_Descriptor_t xConsole;
	HAL_UART_Receive_IT(huart, &rcvd, 1);
	if (huart->Instance == USART2)
    {
        if(rcvd == '\r'){
        	//osSemaphoreRelease(ConsoleBinarySemHandle);
        	HAL_UART_Transmit(&huart2, (uint8_t*)&rcvd, 1, 0xFFFF);

        }else {
        	HAL_UART_Transmit(&huart2, (uint8_t*)&rcvd, 1, 0xFFFF);
        	//osSemaphoreRelease(ConsoleBinarySemHandle);
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{

	}
}

static BaseType_t helpcommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
	BaseType_t xReturn = 0x0;

	return(xReturn);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
