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

#define B                              \
    do                                 \
    {                                  \
        rotateInPosMode(2, 1, 119, 1); \
        rotateInPosMode(2, 0, 29, 1);  \
    } while (0)

#define B1                             \
    do                                 \
    {                                  \
        rotateInPosMode(2, 0, 117, 1); \
        rotateInPosMode(2, 1, 27, 1);  \
    } while (0)

#define B2                             \
    do                                 \
    {                                  \
        rotateInPosMode(2, 0, 207, 1); \
        rotateInPosMode(2, 1, 27, 1);  \
    } while (0)

#define R rotateInPosMode(1, 0, 270, 1)
#define R1 rotateInPosMode(1, 0, 180, 1)
#define R2 rotateInPosMode(1, 0, 90, 1)

#define L rotateInPosMode(3, 1, 90, 1)
#define L1 rotateInPosMode(3, 1, 180, 1)
#define L2 rotateInPosMode(3, 1, 270, 1)

#define F                             \
    do                                \
    {                                 \
        rotateInPosMode(3, 1, 90, 1); \
        rotateInPosMode(1, 0, 90, 0); \
    } while (0)