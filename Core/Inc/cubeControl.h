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
void K()
{
    HAL_Delay(800);
    rotateInPosMode(3, 0, 90, 1);
    rotateInPosMode(1, 1, 90, 0);
    ++rotate_flag;
}

void C()

{
    rotateInPosMode(2, 1, 119, 1);
    HAL_Delay(50);
    rotateInPosMode(2, 0, 29, 1);
}

void C1()

{
    rotateInPosMode(2, 0, 117, 1);
    HAL_Delay(50);
    rotateInPosMode(2, 1, 27, 1);
}

void C2()

{
    rotateInPosMode(2, 0, 207, 1);
    HAL_Delay(50);
    rotateInPosMode(2, 1, 27, 1);
}

void b()
{
    while (rotate_flag % 4 != 0)
        K();
    HAL_Delay(500);
    C();
}

void b1()
{
    while (rotate_flag % 4 != 0)
        K();
    HAL_Delay(500);
    C1();
}

void b2()
{
    while (rotate_flag % 4 != 0)
        K();
    HAL_Delay(500);
    C2();
}

void u()
{
    while (rotate_flag % 4 != 1)
        K();
    HAL_Delay(500);
    C();
}

void u1()
{
    while (rotate_flag % 4 != 1)
        K();
    HAL_Delay(500);
    C1();
}

void u2()
{
    while (rotate_flag % 4 != 1)
        K();
    HAL_Delay(500);
    C2();
}

void f()
{
    while (rotate_flag % 4 != 2)
        K();
    HAL_Delay(500);
    C();
}

void f1()
{
    while (rotate_flag % 4 != 2)
        K();
    HAL_Delay(500);
    C1();
}

void f2()
{
    while (rotate_flag % 4 != 2)
        K();
    HAL_Delay(500);
    C2();
}

void d()
{
    while (rotate_flag % 4 != 3)
        K();
    HAL_Delay(500);
    C();
}

void d1()
{
    while (rotate_flag % 4 != 3)
        K();
    HAL_Delay(500);
    C1();
}

void d2()
{
    while (rotate_flag % 4 != 3)
        K();
    HAL_Delay(500);
    C2();
}

void r() { rotateInPosMode(1, 0, 270, 1); }
void r1() { rotateInPosMode(1, 0, 180, 1); }
void r2() { rotateInPosMode(1, 0, 90, 1); }

void l() { rotateInPosMode(3, 1, 90, 1); }
void l1() { rotateInPosMode(3, 1, 180, 1); }
void l2() { rotateInPosMode(3, 1, 270, 1); }
