/**
 * @file cubeControl.h
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

extern void rotateInPosMode(uint8_t ID, uint8_t dir, uint16_t angle, uint8_t wait_flag);

extern void rotateInSpdMode(uint8_t ID, uint8_t dir, uint16_t speed);

volatile int rotate_flag = 0;
volatile unsigned char cube[6][9] = {0};
#define K                             \
    do                                \
    {                                 \
        HAL_Delay(800);               \
        rotateInPosMode(3, 0, 90, 1); \
        rotateInPosMode(1, 1, 90, 0); \
        ++rotate_flag;                \
    } while (0)

#define C                              \
    do                                 \
    {                                  \
        rotateInPosMode(2, 1, 119, 1); \
        HAL_Delay(50);                 \
        rotateInPosMode(2, 0, 29, 1);  \
    } while (0)

#define C1                             \
    do                                 \
    {                                  \
        rotateInPosMode(2, 0, 117, 1); \
        HAL_Delay(50);                 \
        rotateInPosMode(2, 1, 27, 1);  \
    } while (0)

#define C2                             \
    do                                 \
    {                                  \
        rotateInPosMode(2, 0, 207, 1); \
        HAL_Delay(50);                 \
        rotateInPosMode(2, 1, 27, 1);  \
    } while (0)

#define B                            \
    do                               \
    {                                \
        while (rotate_flag % 4 != 0) \
            K;                       \
        HAL_Delay(500);              \
        C;                           \
    } while (0)

#define B1                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 0) \
            K;                       \
        HAL_Delay(500);              \
        C1;                          \
    } while (0)

#define B2                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 0) \
            K;                       \
        HAL_Delay(500);              \
        C2;                          \
    } while (0)

#define U                            \
    do                               \
    {                                \
        while (rotate_flag % 4 != 1) \
            K;                       \
        HAL_Delay(500);              \
        C;                           \
    } while (0)

#define U1                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 1) \
            K;                       \
        HAL_Delay(500);              \
        C1;                          \
    } while (0)

#define U2                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 1) \
            K;                       \
        HAL_Delay(500);              \
        C2;                          \
    } while (0)

#define F                            \
    do                               \
    {                                \
        while (rotate_flag % 4 != 2) \
            K;                       \
        HAL_Delay(500);              \
        C;                           \
    } while (0)

#define F1                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 2) \
            K;                       \
        HAL_Delay(500);              \
        C1;                          \
    } while (0)

#define F2                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 2) \
            K;                       \
        HAL_Delay(500);              \
        C2;                          \
    } while (0)

#define D                            \
    do                               \
    {                                \
        while (rotate_flag % 4 != 3) \
            K;                       \
        HAL_Delay(500);              \
        C;                           \
    } while (0)

#define D1                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 3) \
            K;                       \
        HAL_Delay(500);              \
        C1;                          \
    } while (0)

#define D2                           \
    do                               \
    {                                \
        while (rotate_flag % 4 != 3) \
            K;                       \
        HAL_Delay(500);              \
        C2;                          \
    } while (0)

#define R rotateInPosMode(1, 0, 270, 1)
#define R1 rotateInPosMode(1, 0, 180, 1)
#define R2 rotateInPosMode(1, 0, 90, 1)

#define L rotateInPosMode(3, 1, 90, 1)
#define L1 rotateInPosMode(3, 1, 180, 1)
#define L2 rotateInPosMode(3, 1, 270, 1)
