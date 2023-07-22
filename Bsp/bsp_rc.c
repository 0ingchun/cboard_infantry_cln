#include "bsp_rc.h"
#include "main.h"
#include "usart.h"


extern DMA_HandleTypeDef hdma_usart3_rx;


/**
  * @brief          初始化遥控器双缓冲区接收
  * @param[in,out]  rx1_buf: 缓冲区1指针
  * @param[in,out]  rx2_buf: 缓冲区1指针
  * @param[in]      dma_buf_num: 数据长度
  * @retval         无
  */
void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
    //使能DMA串口接收
    SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);

    //使能空闲中断
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

    //失效DMA
    __HAL_DMA_DISABLE(&hdma_usart3_rx);
    while(hdma_usart3_rx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart3_rx);
    }

    hdma_usart3_rx.Instance->PAR = (uint32_t) & (USART3->DR);
    //内存缓冲区1
    hdma_usart3_rx.Instance->M0AR = (uint32_t)(rx1_buf);
    //内存缓冲区2
    hdma_usart3_rx.Instance->M1AR = (uint32_t)(rx2_buf);
    //数据长度
    hdma_usart3_rx.Instance->NDTR = dma_buf_num;
    //使能双缓冲区
    SET_BIT(hdma_usart3_rx.Instance->CR, DMA_SxCR_DBM);

    //使能DMA
    __HAL_DMA_ENABLE(&hdma_usart3_rx);
}


/**
  * @brief          关闭遥控器接收
  * @retval         无
  */
void RC_unable(void)
{
    __HAL_UART_DISABLE(&huart3);
}


/**
  * @brief          重启遥控器接收
  * @param[in]      dma_buf_num: 数据长度
  * @retval         无
  */
void RC_restart(uint16_t dma_buf_num)
{
    __HAL_UART_DISABLE(&huart3);
    __HAL_DMA_DISABLE(&hdma_usart3_rx);

    hdma_usart3_rx.Instance->NDTR = dma_buf_num;

    __HAL_DMA_ENABLE(&hdma_usart3_rx);
    __HAL_UART_ENABLE(&huart3);
}
