/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for test */
osThreadId_t testHandle;
uint32_t test_taskBuffer[ 128 ];
osStaticThreadDef_t test_taskControlBlock;
const osThreadAttr_t test_attributes = {
  .name = "test",
  .cb_mem = &test_taskControlBlock,
  .cb_size = sizeof(test_taskControlBlock),
  .stack_mem = &test_taskBuffer[0],
  .stack_size = sizeof(test_taskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
osThreadId_t test_robotmovetaskHandle;
uint32_t test_robotmovetaskBuffer[ 512 ];//改大点防溢出
osStaticThreadDef_t test_robotmovetaskControlBlock;
const osThreadAttr_t test_robotmovetask_attributes = {
        .name = "test_robotmovetask",
        .cb_mem = &test_robotmovetaskControlBlock,
        .cb_size = sizeof(test_robotmovetaskControlBlock),
        .stack_mem = &test_robotmovetaskBuffer[0],
        .stack_size = sizeof(test_robotmovetaskBuffer),
        .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for battery_voltage */
osThreadId_t battery_voltageHandle;
uint32_t battery_voltageBuffer[ 128 ];
osStaticThreadDef_t battery_voltageControlBlock;
const osThreadAttr_t battery_voltage_attributes = {
  .name = "battery_voltage",
  .cb_mem = &battery_voltageControlBlock,
  .cb_size = sizeof(battery_voltageControlBlock),
  .stack_mem = &battery_voltageBuffer[0],
  .stack_size = sizeof(battery_voltageBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for led_flow */
osThreadId_t led_flowHandle;
uint32_t led_flow_taskBuffer[ 128 ];
osStaticThreadDef_t led_flow_taskControlBlock;
const osThreadAttr_t led_flow_attributes = {
  .name = "led_flow",
  .cb_mem = &led_flow_taskControlBlock,
  .cb_size = sizeof(led_flow_taskControlBlock),
  .stack_mem = &led_flow_taskBuffer[0],
  .stack_size = sizeof(led_flow_taskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buzzer */
osThreadId_t buzzerHandle;
uint32_t buzzerBuffer[ 128 ];
osStaticThreadDef_t buzzerControlBlock;
const osThreadAttr_t buzzer_attributes = {
  .name = "buzzer",
  .cb_mem = &buzzerControlBlock,
  .cb_size = sizeof(buzzerControlBlock),
  .stack_mem = &buzzerBuffer[0],
  .stack_size = sizeof(buzzerBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for detect */
osThreadId_t detectHandle;
uint32_t detectBuffer[ 128 ];
osStaticThreadDef_t detectControlBlock;
const osThreadAttr_t detect_attributes = {
  .name = "detect",
  .cb_mem = &detectControlBlock,
  .cb_size = sizeof(detectControlBlock),
  .stack_mem = &detectBuffer[0],
  .stack_size = sizeof(detectBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for referee_usart */
osThreadId_t referee_usartHandle;
uint32_t referee_usartBuffer[ 128 ];
osStaticThreadDef_t referee_usartControlBlock;
const osThreadAttr_t referee_usart_attributes = {
  .name = "referee_usart",
  .cb_mem = &referee_usartControlBlock,
  .cb_size = sizeof(referee_usartControlBlock),
  .stack_mem = &referee_usartBuffer[0],
  .stack_size = sizeof(referee_usartBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for INS */
osThreadId_t INSHandle;
uint32_t INSBuffer[ 128 ];
osStaticThreadDef_t INSControlBlock;
const osThreadAttr_t INS_attributes = {
  .name = "INS",
  .cb_mem = &INSControlBlock,
  .cb_size = sizeof(INSControlBlock),
  .stack_mem = &INSBuffer[0],
  .stack_size = sizeof(INSBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for encoder */
osThreadId_t encoderHandle;
uint32_t encoderBuffer[ 128 ];
osStaticThreadDef_t encoderControlBlock;
const osThreadAttr_t encoder_attributes = {
  .name = "encoder",
  .cb_mem = &encoderControlBlock,
  .cb_size = sizeof(encoderControlBlock),
  .stack_mem = &encoderBuffer[0],
  .stack_size = sizeof(encoderBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for can */

/* Definitions for motor */

/* Definitions for IR */
osThreadId_t IRHandle;
uint32_t IRBuffer[ 128 ];
osStaticThreadDef_t IRControlBlock;
const osThreadAttr_t IR_attributes = {
  .name = "IR",
  .cb_mem = &IRControlBlock,
  .cb_size = sizeof(IRControlBlock),
  .stack_mem = &IRBuffer[0],
  .stack_size = sizeof(IRBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for remote_control */

/* Definitions for gimbal */
osThreadId_t gimbalHandle;
uint32_t gimbalBuffer[ 128 ];
osStaticThreadDef_t gimbalControlBlock;
const osThreadAttr_t gimbal_attributes = {
  .name = "gimbal",
  .cb_mem = &gimbalControlBlock,
  .cb_size = sizeof(gimbalControlBlock),
  .stack_mem = &gimbalBuffer[0],
  .stack_size = sizeof(gimbalBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for chassis */
osThreadId_t chassisHandle;
uint32_t chassisBuffer[ 128 ];
osStaticThreadDef_t chassisControlBlock;
const osThreadAttr_t chassis_attributes = {
  .name = "chassis",
  .cb_mem = &chassisControlBlock,
  .cb_size = sizeof(chassisControlBlock),
  .stack_mem = &chassisBuffer[0],
  .stack_size = sizeof(chassisBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void test_task(void *argument);
void robot_move_task(void *argument);
extern void battery_voltage_task(void *argument);
extern void led_flow_task(void *argument);
extern void buzzer_task(void *argument);
extern void detect_task(void *argument);
extern void referee_usart_task(void *argument);
extern void INS_task(void *argument);
extern void encoder_task(void *argument);
extern void can_task(void *argument);
extern void motor_task(void *argument);
extern void IR_task(void *argument);
extern void remote_control_task(void *argument);
extern void gimbal_task(void *argument);
extern void chassis_task(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of test */
  testHandle = osThreadNew(test_task, NULL, &test_attributes);

  test_robotmovetaskHandle = osThreadNew(robot_move_task, NULL, &test_robotmovetask_attributes); //开始拉屎

  /* creation of battery_voltage */
//  battery_voltageHandle = osThreadNew(battery_voltage_task, NULL, &battery_voltage_attributes);

  /* creation of led_flow */
  led_flowHandle = osThreadNew(led_flow_task, NULL, &led_flow_attributes);

  /* creation of buzzer */
//  buzzerHandle = osThreadNew(buzzer_task, NULL, &buzzer_attributes);

  /* creation of detect */
  detectHandle = osThreadNew(detect_task, NULL, &detect_attributes);

  /* creation of referee_usart */
//  referee_usartHandle = osThreadNew(referee_usart_task, NULL, &referee_usart_attributes);

  /* creation of INS */
  INSHandle = osThreadNew(INS_task, NULL, &INS_attributes);

  /* creation of encoder */
//  encoderHandle = osThreadNew(encoder_task, NULL, &encoder_attributes);

  /* creation of can */
//  canHandle = osThreadNew(can_task, NULL, &can_attributes);

  /* creation of motor */
//  motorHandle = osThreadNew(motor_task, NULL, &motor_attributes);

  /* creation of IR */
//  IRHandle = osThreadNew(IR_task, NULL, &IR_attributes);

  /* creation of remote_control */
 // remote_controlHandle = osThreadNew(remote_control_task, NULL, &remote_control_attributes);

  /* creation of gimbal */
  //gimbalHandle = osThreadNew(gimbal_task, NULL, &gimbal_attributes);

  /* creation of chassis */
  //chassisHandle = osThreadNew(chassis_task, NULL, &chassis_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_test_task */
/**
  * @brief  Function implementing the test thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_test_task */

extern float INS_gyro[3];
extern float INS_accel[3];
extern float INS_mag[3];
extern float INS_quat[4];

uint8_t buff[256];

__weak void test_task(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN test_task */
  /* Infinite loop */
  for(;;)
  {
      int i = sprintf((char *) &buff, "{%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f}\r\n", INS_quat[0], INS_quat[1], INS_quat[2], INS_quat[3], INS_gyro[0], INS_gyro[1], INS_gyro[2], INS_accel[0], INS_accel[1], INS_accel[2]);
      CDC_Transmit_FS(buff, i);
    osDelay(10);
  }
  /* USER CODE END test_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

