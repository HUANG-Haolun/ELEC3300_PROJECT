/**
 * @file motorDriver.c
 * @author HUANG Haolun (mihawkhhuang@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "motorDriver.h"
#include "usart.h"
#include <string.h>
volatile uint8_t motor_flag;

uint8_t RxBuffer[RXBUFFERSIZE];
void rotateInPosMode(uint8_t ID, uint8_t dir, uint16_t angle, uint8_t wait_flag)
{
    uint32_t steps = angle / STEP_DGREE * M_STEP;
    uint8_t TxBuffer[9];
    memcpy(TxBuffer, &ID, 1);
    TxBuffer[1] = POS_REG;
    uint16_t speed = (SPEED | (uint8_t)dir << 15);
    TxBuffer[2] = (uint8_t)(speed >> 8);
    TxBuffer[3] = (uint8_t)(speed & 0x00FF);
    TxBuffer[4] = (uint8_t)ACCELERATION;
    TxBuffer[5] = (uint8_t)(steps >> 16);
    TxBuffer[6] = (uint8_t)(steps >> 8);
    TxBuffer[7] = (uint8_t)(steps & 0x00FF);
    TxBuffer[8] = CHECK_BIT;
    HAL_Delay(50);
    while (!(motor_flag & (0x01 << (ID - 1))))
        ;
    while (wait_flag && motor_flag != 7)
        ;

    HAL_UART_Transmit(&huart1, (uint8_t *)&TxBuffer, 9, 0xFFFF);
    motor_flag &= ~(0x01 << (ID - 1));
}
void rotateInSpdMode(uint8_t ID, uint8_t dir, uint16_t speed)
{
    uint8_t TxBuffer[6];
    memcpy(TxBuffer, &ID, 1);
    TxBuffer[1] = SPD_REG;
    uint16_t temp = (speed | (uint8_t)dir << 15);
    TxBuffer[2] = (uint8_t)(temp >> 8);
    TxBuffer[3] = (uint8_t)(temp & 0x00FF);
    TxBuffer[4] = (uint8_t)ACCELERATION;
    TxBuffer[5] = CHECK_BIT;
    HAL_UART_Transmit(&huart1, (uint8_t *)&TxBuffer, 6, 0xFFFF);
}

void enable(uint8_t ID, uint8_t enable)
{
    uint8_t TxBuffer[4];
    memcpy(TxBuffer, &ID, 1);
    TxBuffer[1] = ENABLE_REG;
    TxBuffer[2] = (uint8_t)(enable & 0x01);
    TxBuffer[3] = CHECK_BIT;
    HAL_UART_Transmit(&huart1, (uint8_t *)&TxBuffer, 4, 0xFFFF);
}

void setSpdState(uint8_t ID, uint8_t set)
{

    uint8_t TxBuffer[4];
    memcpy(TxBuffer, &ID, 1);
    TxBuffer[1] = SPD_FLAG;
    if (set)
        TxBuffer[2] = 0xc8;
    else
        TxBuffer[2] = 0xca;
    TxBuffer[3] = CHECK_BIT;
    HAL_UART_Transmit(&huart1, (uint8_t *)&TxBuffer, 4, 0xFFFF);
}
