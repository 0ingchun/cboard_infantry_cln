#ifndef BSP_USART_H
#define BSP_USART_H


#include "struct_typedef.h"


/**
  * @brief          初始化UART1发送DMA
  * @retval         无
  */
extern void usart1_tx_dma_init(void);


/**
  * @brief          使能UART1发送DMA
  * @param[in,out]  data: 缓冲区指针
  * @param[in]      len: 数据长度
  * @retval         无
  */
extern void usart1_tx_dma_enable(uint8_t *data, uint16_t len);


/**
  * @brief          使能UART6
  * @param[in,out]  rx1_buf: 缓冲区1指针
  * @param[in,out]  rx2_buf: 缓冲区2指针
  * @param[in]      dma_buf_num: 数据长度
  * @retval         无
  */
extern void usart6_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);


/**
  * @brief          使能UART6发送DMA
  * @param[in]      data: 缓冲区指针
  * @param[in]      len: 数据长度
  * @retval         无
  */
extern void usart6_tx_dma_enable(uint8_t *data, uint16_t len);


#endif
