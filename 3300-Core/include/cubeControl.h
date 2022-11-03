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
volatile int faceMotor = 0;
volatile unsigned char cube[6][9] = {0};
void test()
{
    unsigned char test[54] = {'L', 'L', 'U', 'B', 'U', 'L', 'D', 'R', 'U',
                              'R', 'F', 'R', 'R', 'R', 'F', 'L', 'U', 'F',
                              'R', 'D', 'F', 'R', 'F', 'B', 'L', 'U', 'F',
                              'F', 'R', 'U', 'L', 'D', 'L', 'D', 'B', 'D',
                              'B', 'U', 'B', 'R', 'L', 'F', 'L', 'B', 'R',
                              'B', 'D', 'U', 'U', 'B', 'F', 'L', 'D', 'B'};
    memcpy(cube, test, 54);
}

#define Z                             \
    do                                \
    {                                 \
        rotateInPosMode(3, 1, 90, 1); \
        rotateInPosMode(1, 0, 90, 0); \
        faceMotor++;                  \
        faceMotor %= 4;               \
    } while (0)
#define K(FLAG)                        \
    do                                 \
    {                                  \
        while (faceMotor != FLAG)      \
            Z;                         \
        rotateInPosMode(2, 1, 119, 1); \
        rotateInPosMode(2, 0, 29, 1);  \
    } while (0)

#define K1(FLAG)                       \
    do                                 \
    {                                  \
        while (faceMotor != FLAG)      \
            Z;                         \
        rotateInPosMode(2, 0, 117, 1); \
        rotateInPosMode(2, 1, 27, 1);  \
    } while (0)

#define K2(FLAG)                       \
    do                                 \
    {                                  \
        while (faceMotor != FLAG)      \
            Z;                         \
        rotateInPosMode(2, 0, 207, 1); \
        rotateInPosMode(2, 1, 27, 1);  \
    } while (0)

#define R rotateInPosMode(1, 0, 270, 1)
#define R1 rotateInPosMode(1, 0, 180, 1)
#define R2 rotateInPosMode(1, 0, 90, 1)

#define L rotateInPosMode(3, 1, 90, 1)
#define L1 rotateInPosMode(3, 1, 180, 1)
#define L2 rotateInPosMode(3, 1, 270, 1)

