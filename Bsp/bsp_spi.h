#ifndef BSP_SPI_H
#define BSP_SPI_H


#include "struct_typedef.h"


/**
  * @brief          SPI1 DMA初始化
  * @param[in,out]  tx_buf: 发送缓冲区
  * @param[in,out]  rx_buf: 接收缓冲区
  * @param[in]      num: 数据长度
  * @retval         无
  */
extern void SPI1_DMA_init(uint32_t tx_buf, uint32_t rx_buf, uint16_t num);


/**
  * @brief          SPI1 DMA 使能
  * @param[in,out]  tx_buf: 发送缓冲区
  * @param[in,out]  rx_buf: 接收缓冲区
  * @param[in]      ndtr: 剩余数据长度
  * @retval         无
  */
extern void SPI1_DMA_enable(uint32_t tx_buf, uint32_t rx_buf, uint16_t ndtr);


#endif
