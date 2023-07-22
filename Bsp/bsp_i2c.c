#include "bsp_i2c.h"
#include "i2c.h"


/**
  * @brief          I2C发送
  * @param[in]      I2C: 要发送的I2C
  * @param[in]      I2C_address: 要发送的地址
  * @param[in]      data: 要发送的数据
  * @param[in]      len: 要发送数据的长度
  * @retval         无
  */
void bsp_I2C_master_transmit(I2C_TypeDef *I2C, uint16_t I2C_address, uint8_t *data, uint16_t len)
{
    if(I2C == I2C1)
    {
        HAL_I2C_Master_Transmit(&hi2c1, I2C_address, data, len, 100);
    }
    else if(I2C == I2C2)
    {
        HAL_I2C_Master_Transmit(&hi2c2, I2C_address, data, len, 100);
    }
}


/**
  * @brief          I2C复位
  * @param[in]      I2C: 要复位的I2C
  * @retval         无
  */
void bsp_I2C_reset(I2C_TypeDef *I2C)
{
    I2C_HandleTypeDef *hi2c = NULL;

    if(I2C == I2C1)
    {
        hi2c = &hi2c1;
    }
    else if(I2C == I2C2)
    {
        hi2c = &hi2c2;
    }

    if (hi2c == NULL) return;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_SWRST);
    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_SWRST);
    if (HAL_I2C_Init(hi2c) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
  * @brief          检查I2C是否收到应答
  * @param[in]      I2C: 要检查的I2C
  * @param[in]      I2C_address: 要检查的地址
  * @retval         I2C_ACK 或 I2C_NO_ACK
  */
bool_t bsp_I2C_check_ack(I2C_TypeDef *I2C, uint16_t I2C_address)
{
    I2C_HandleTypeDef *hi2c = NULL;

    if(I2C == I2C1)
    {
        hi2c = &hi2c1;
    }
    else if(I2C == I2C2)
    {
        hi2c = &hi2c2;
    }

    if((hi2c->Instance->CR2 & I2C_CR2_DMAEN) && ((hi2c->hdmatx != NULL && hi2c->hdmatx->Instance->NDTR != 0) || (hi2c->hdmarx != NULL && hi2c->hdmarx->Instance->NDTR != 0)))
    {
        return I2C_ACK;
    }
    else
    {
        uint16_t timeout = 0;

        timeout = 0;
        while(hi2c->Instance->SR2 & 0x02)
        {
            timeout ++;
            if(timeout > 100)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

        timeout = 0;
        while(!(hi2c->Instance->SR1 & 0x01))
        {
            timeout ++;
            if(timeout > 100)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(I2C_address);

        timeout = 0;
        while(!(hi2c->Instance->SR1 & 0x02))
        {
            timeout ++;
            if(timeout > 500)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        do{
            __IO uint32_t tmpreg = 0x00U;
            tmpreg = hi2c->Instance->SR1;
            tmpreg = hi2c->Instance->SR2;
            UNUSED(tmpreg);
        } while(0);

        timeout = 0;
        while(!(hi2c->Instance->SR1 & 0x80))
        {
            timeout ++;
            if(timeout > 500)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

        return I2C_ACK;
    }
}
