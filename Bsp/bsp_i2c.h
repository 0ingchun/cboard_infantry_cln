#ifndef BSP_I2C_H
#define BSP_I2C_H


#include "struct_typedef.h"
#include "main.h"


#define I2C_ACK 1
#define I2C_NO_ACK  0


/**
  * @brief          I2C复位
  * @param[in]      I2C: 要复位的I2C
  * @retval         无
  */
extern void bsp_I2C_reset(I2C_TypeDef *I2C);


/**
  * @brief          I2C发送
  * @param[in]      I2C: 要发送的I2C
  * @param[in]      I2C_address: 要发送的地址
  * @param[in]      data: 要发送的数据
  * @param[in]      len: 要发送数据的长度
  * @retval         无
  */
extern void bsp_I2C_master_transmit(I2C_TypeDef *I2C, uint16_t I2C_address, uint8_t *data, uint16_t len);


/**
  * @brief          检查I2C是否收到应答
  * @param[in]      I2C: 要检查的I2C
  * @param[in]      I2C_address: 要检查的地址
  * @retval         I2C_ACK 或 I2C_NO_ACK
  */
extern bool_t bsp_I2C_check_ack(I2C_TypeDef *I2C, uint16_t I2C_address);


#endif
