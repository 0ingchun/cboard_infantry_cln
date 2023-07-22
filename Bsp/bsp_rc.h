#ifndef BSP_RC_H
#define BSP_RC_H


#include "struct_typedef.h"


/**
  * @brief          初始化遥控器双缓冲区接收
  * @param[in,out]  rx1_buf: 缓冲区1指针
  * @param[in,out]  rx2_buf: 缓冲区1指针
  * @param[in]      dma_buf_num: 数据长度
  * @retval         无
  */
extern void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);


/**
  * @brief          关闭遥控器接收
  * @retval         无
  */
extern void RC_unable(void);


/**
  * @brief          重启遥控器接收
  * @param[in]      dma_buf_num: 数据长度
  * @retval         无
  */
extern void RC_restart(uint16_t dma_buf_num);


#endif
