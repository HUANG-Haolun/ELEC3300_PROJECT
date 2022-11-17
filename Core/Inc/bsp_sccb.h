#ifndef __SCCB_H
#define __SCCB_H

#include "stm32f1xx_hal.h"

#define SCL_H         GPIOC -> BSRR = GPIO_PIN_6 
#define SCL_L         GPIOC -> BRR = GPIO_PIN_6 
   
#define SDA_H         GPIOC -> BSRR = GPIO_PIN_7 
#define SDA_L         GPIOC -> BRR = GPIO_PIN_7  

#define SCL_read      HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)
#define SDA_read      HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7) 

#define ADDR_OV7725   0x42

int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte);
int SCCB_ReadByte(uint8_t* pBuffer, uint16_t length, uint8_t ReadAddress);

#endif 
