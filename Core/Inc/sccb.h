#ifndef __SCCB_H
#define __SCCB_H
#include "main.h"
#include "stm32f1xx_hal.h"
#define SCL_H         HAL_GPIO_WritePin(GPIOC , GPIO_PIN_6,GPIO_PIN_SET) 
#define SCL_L         HAL_GPIO_WritePin(GPIOC , GPIO_PIN_6,GPIO_PIN_RESET) 

#define SDA_H         HAL_GPIO_WritePin(GPIOC , GPIO_PIN_7,GPIO_PIN_SET) 
#define SDA_L         HAL_GPIO_WritePin(GPIOC , GPIO_PIN_7,GPIO_PIN_RESET) 

 #define SCL_read      HAL_GPIO_ReadPin(GPIOC , GPIO_PIN_6)
 #define SDA_read      HAL_GPIO_ReadPin(GPIOC , GPIO_PIN_7)

int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte);
int SCCB_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint8_t ReadAddress);
void SCCB_GPIO_Config(void);
#endif 
