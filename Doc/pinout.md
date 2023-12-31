## GPIO
```
PA0   GPIO_IN    KEY
PA4   SPI1_CS    IMU_ACCEL
PB0   SPI1_CS    IMU_GYRO
PB12  SPI2_CS    USER_SPI
PC4   EXTI_4     IMU_ACCEL_INT
PC5   EXTI_9:5   IMU_GYRO_INT
PG3   EXTI_3     IST8310_DRDY
PG6   GPIO_OUT   IST8310_RSTN
```
## ADC
```
PF10  ADC3_IN8   ADC_BAT
```
## CAN
```
PD0   CAN1_RX    CAN_MOTOR
PD1   CAN1_TX    CAN_MOTOR
PB5   CAN2_RX    CAN_COMMUNICATION
PB6   CAN2_TX    CAN_COMMUNICATION
```
## I2C
```
PF0   I2C2_SDA   USER_I2C
PF1   I2C2_SCL   USER_I2C
PC9   I2C3_SDA   IST8310_I2C
PA8   I2C3_SCL   IST8310_I2C
```
## CLOCK
```
PH0   RCC_OSC_IN
PH1   RCC_OSC_OUT
```
## SPI
```
PA7   SPI1_MOSI  IMU_SPI
PB3   SPI1_SCK   IMU_SPI
PB4   SPI1_MISO  IMU_SPI
PB13  SPI2_SCK   USER_SPI
PB14  SPI2_MISO  USER_SPI
PB15  SPI2_MOSI  USER_SPI
```
## SYS
```
PA13  SWDIO      SWD
PA14  SWCLK      SWD
```
## TIM
```
PC8   TIM3_CH3   LAZER
PD14  TIM4_CH3   BUZZER
PF6   TIM10_CH1  IMU_HEATER
PH10  TIM5_CH1   LED_R
PH11  TIM5_CH2   LED_G
PH12  TIM5_CH3   LED_B
```
## USART
```
PA9   UART1_TX   USER_UART
PB7   UART1_RX   USER_UART
PC10  UART3_TX   DBUS_UART
PC11  UART3_RX   DBUS_UART
PG14  UART6_TX   REFEREE_UART
PG9   UART6_RX   REFEREE_UART
```
## USB
```
PA11  USB_DM
PA12  USB_DP
```
