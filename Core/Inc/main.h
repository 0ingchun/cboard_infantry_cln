/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CAN_receive.h"
#include "remote_control.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/*
typedef struct
{
    const motor_measure_t *chassis_motor_measure;
} chassis_motor_t;

typedef struct
{
    const motor_measure_t *gimbal_motor_measure;
    const RC_ctrl_t *GIMBAL;

} gimbal_motor_t;
/*

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB
#define REFEREE_UART_Pin GPIO_PIN_14
#define REFEREE_UART_GPIO_Port GPIOG
#define IMU_SPI_Pin GPIO_PIN_4
#define IMU_SPI_GPIO_Port GPIOB
#define IMU_SPIB3_Pin GPIO_PIN_3
#define IMU_SPIB3_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB
#define USER_UART_Pin GPIO_PIN_7
#define USER_UART_GPIO_Port GPIOB
#define DBUS_Pin GPIO_PIN_11
#define DBUS_GPIO_Port GPIOC
#define DBUSC10_Pin GPIO_PIN_10
#define DBUSC10_GPIO_Port GPIOC
#define REFEREE_UARTG9_Pin GPIO_PIN_9
#define REFEREE_UARTG9_GPIO_Port GPIOG
#define USER_I2C_Pin GPIO_PIN_0
#define USER_I2C_GPIO_Port GPIOF
#define USER_UARTA9_Pin GPIO_PIN_9
#define USER_UARTA9_GPIO_Port GPIOA
#define IST8310_I2C_Pin GPIO_PIN_9
#define IST8310_I2C_GPIO_Port GPIOC
#define IST8310_I2CA8_Pin GPIO_PIN_8
#define IST8310_I2CA8_GPIO_Port GPIOA
#define LAZER_Pin GPIO_PIN_8
#define LAZER_GPIO_Port GPIOC
#define USER_I2CF1_Pin GPIO_PIN_1
#define USER_I2CF1_GPIO_Port GPIOF
#define RSTN_IST8310_Pin GPIO_PIN_6
#define RSTN_IST8310_GPIO_Port GPIOG
#define IMU_HEATER_Pin GPIO_PIN_6
#define IMU_HEATER_GPIO_Port GPIOF
#define LED_R_Pin GPIO_PIN_12
#define LED_R_GPIO_Port GPIOH
#define DRDY_IST8310_Pin GPIO_PIN_3
#define DRDY_IST8310_GPIO_Port GPIOG
#define DRDY_IST8310_EXTI_IRQn EXTI3_IRQn
#define ADC_BAT_Pin GPIO_PIN_10
#define ADC_BAT_GPIO_Port GPIOF
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOH
#define LED_B_Pin GPIO_PIN_10
#define LED_B_GPIO_Port GPIOH
#define HW0_Pin GPIO_PIN_0
#define HW0_GPIO_Port GPIOC
#define HW1_Pin GPIO_PIN_1
#define HW1_GPIO_Port GPIOC
#define HW2_Pin GPIO_PIN_2
#define HW2_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_14
#define BUZZER_GPIO_Port GPIOD
#define KEY_Pin GPIO_PIN_0
#define KEY_GPIO_Port GPIOA
#define CS1_ACCEL_Pin GPIO_PIN_4
#define CS1_ACCEL_GPIO_Port GPIOA
#define INT1_ACCEL_Pin GPIO_PIN_4
#define INT1_ACCEL_GPIO_Port GPIOC
#define INT1_ACCEL_EXTI_IRQn EXTI4_IRQn
#define SOFT_INT_Pin GPIO_PIN_0
#define SOFT_INT_GPIO_Port GPIOG
#define SOFT_INT_EXTI_IRQn EXTI0_IRQn
#define INT1_GYRO_Pin GPIO_PIN_5
#define INT1_GYRO_GPIO_Port GPIOC
#define INT1_GYRO_EXTI_IRQn EXTI9_5_IRQn
#define USER_SPI_CS_Pin GPIO_PIN_12
#define USER_SPI_CS_GPIO_Port GPIOB
#define USER_SPI_Pin GPIO_PIN_13
#define USER_SPI_GPIO_Port GPIOB
#define IMU_SPIA7_Pin GPIO_PIN_7
#define IMU_SPIA7_GPIO_Port GPIOA
#define CS1_GYRO_Pin GPIO_PIN_0
#define CS1_GYRO_GPIO_Port GPIOB
#define USER_SPIB14_Pin GPIO_PIN_14
#define USER_SPIB14_GPIO_Port GPIOB
#define USER_SPIB15_Pin GPIO_PIN_15
#define USER_SPIB15_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
