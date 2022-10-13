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

#define B                           \
    do                              \
    {                               \
        rotateInPosMode(2, 1, 119); \
        HAL_Delay(1000);            \
        rotateInPosMode(2, 0, 29);  \
        HAL_Delay(1000);            \
    } while (0)

#define B1                          \
    do                              \
    {                               \
        rotateInPosMode(2, 0, 117); \
        HAL_Delay(1000);            \
        rotateInPosMode(2, 1, 27);  \
        HAL_Delay(1000);            \
    } while (0)

#define B2                          \
    do                              \
    {                               \
        rotateInPosMode(2, 0, 207); \
        HAL_Delay(1500);            \
        rotateInPosMode(2, 1, 27);  \
        HAL_Delay(1000);            \
    } while (0)

#define R  rotateInPosMode(1, 0, 270)
#define R1  rotateInPosMode(1, 0, 180)
#define R2  rotateInPosMode(1, 0, 90)

#define R  rotateInPosMode(1, 0, 270)
#define R1  rotateInPosMode(1, 0, 180)
#define R2  rotateInPosMode(1, 0, 90)