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
#pragma once
#include "motorDriver.h"
#include "usart.h"
#include <string.h>

void getFeedBack(uint16_t id) {
    // HAL_UART_Transmit(&huart2, (uint8_t *)&RxBuffer, 9, 0xFFFF);
}

void rotateInPosMode(uint8_t ID, uint8_t dir, uint16_t angle)
{
    uint32_t steps = angle / STEP_DGREE * M_STEP;
    uint8_t RxBuffer[9];
    memcpy(RxBuffer, &ID, 1);
    RxBuffer[1] = POS_REG;
    uint16_t speed = (SPEED | (uint8_t)dir << 15);
    RxBuffer[2] = (uint8_t)(speed >> 8);
    RxBuffer[3] = (uint8_t)(speed & 0x00FF);
    RxBuffer[4] = (uint8_t)ACCELERATION;
    RxBuffer[5] = (uint8_t)(steps >> 16);
    RxBuffer[6] = (uint8_t)(steps >> 8);
    RxBuffer[7] = (uint8_t)(steps & 0x00FF);
    RxBuffer[8] = CHECK_BIT;
    HAL_UART_Transmit(&huart2, (uint8_t *)&RxBuffer, 9, 0xFFFF);
}
// void turn180(uint8_t dir) {}
void rotateInSpdMode(uint8_t ID, uint8_t dir, uint16_t speed)
{
    uint8_t RxBuffer[6];
    memcpy(RxBuffer, &ID, 1);
    RxBuffer[1] = SPD_REG;
    uint16_t temp = (speed | (uint8_t)dir << 15);
    RxBuffer[2] = (uint8_t)(temp >> 8);
    RxBuffer[3] = (uint8_t)(temp & 0x00FF);
    RxBuffer[4] = (uint8_t)ACCELERATION;
    RxBuffer[5] = CHECK_BIT;
    HAL_UART_Transmit(&huart2, (uint8_t *)&RxBuffer, 6, 0xFFFF);
}

void enable(uint8_t ID, uint8_t enable)
{
    uint8_t RxBuffer[4];
    memcpy(RxBuffer, &ID, 1);
    RxBuffer[1] = ENABLE_REG;
    RxBuffer[2] = (uint8_t)(enable & 0x01);
    RxBuffer[3] = CHECK_BIT;
    HAL_UART_Transmit(&huart2, (uint8_t *)&RxBuffer, 4, 0xFFFF);
}

void setSpdState(uint8_t ID, uint8_t set)
{

    uint8_t RxBuffer[4];
    memcpy(RxBuffer, &ID, 1);
    RxBuffer[1] = SPD_FLAG;
    if (set)
        RxBuffer[2] = 0xc8;
    else
        RxBuffer[2] = 0xca;
    RxBuffer[3] = CHECK_BIT;
    HAL_UART_Transmit(&huart2, (uint8_t *)&RxBuffer, 4, 0xFFFF);
}
