/**
 * @file solve.h
 * @author HUANG Haolun (mihawkhhuang@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */
//                           --------------------------
//                           | U1(0)   U2(1)   U3(2)  |
//                           |                        |
//                           | U4(3)   U5(4)   U6(5)  |
//                           |                        |
//                           | U7(6)   U8(7)   U9(8)  |
//  ------------------------------------------------------------------------------------------------------
//  | L1(36)  L2(37)  L3(38) | F1(18)  F2(19)  F3(20) | R1(9)   R2(10)  R3(11) |  B1(45)  B2(46)  B3(47) |
//  |                        |                        |                        |                         |
//  | L4(39)  L5(40)  L6(41) | F4(21)  F5(22)  F6(23) | R4(12)  R5(13)  R6(14) | B4(48)  B5(49)  B6(50)  |
//  |                        |                        |                        |                         |
//  | L7(42)  L8(43)  L9(44) | F7(24)  F8(25)  F9(26) | R7(15)  R8(16)  R9(17) |  B7(51)  B8(52)  B9(53) |
//  ------------------------------------------------------------------------------------------------------
//                           | D1(27)  D2(28)  D3(29) |
//                           |                        |
//                           | D4(30)  D5(31)  D6(32) |
//                           |                        |
//                           | D7(33)  D8(34)  D9(35) |
//                           --------------------------
#pragma once
#include "stm32f1xx_hal.h"
typedef struct cube_struct
{
    char face[54];
    uint8_t route[250];
    uint8_t routeLen;
} cube_t;


