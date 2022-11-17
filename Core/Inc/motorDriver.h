/**
 * @file motorDriver.hpp
 * @author HUANG Haolun (mihawkhhuang@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "stm32f1xx_hal.h"
#include "usart.h"
#define SPEED 16
#define ACCELERATION 0
#define STEP_DGREE 1.8
#define M_STEP 16
#define CHECK_BIT 0x6b
#define POS_REG 0xfd
#define SPD_REG 0xf6
#define ENABLE_REG 0xf3
#define SPD_FLAG 0xff

#define RXBUFFERSIZE 3
extern uint8_t RxBuffer[RXBUFFERSIZE];
extern volatile uint8_t motor_flag;

void rotateInPosMode(uint8_t ID, uint8_t dir, uint16_t angle, uint8_t wait_flag);

void rotateInSpdMode(uint8_t ID, uint8_t dir, uint16_t speed);

/**
 * @brief
 *
 * @param ID enable and disable motor
 * @param enable non zero is enable, zero is disable
 */
void enable(uint8_t ID, uint8_t enable);

/**
 * @brief Set the Spd State object
 *
 * @param ID
 * @param set non zero is set, zero is clear
 */
void setSpdState(uint8_t ID, uint8_t set);
