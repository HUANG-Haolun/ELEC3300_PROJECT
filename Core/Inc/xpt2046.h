#ifndef __BSP_XPT2046_LCD_H
#define __BSP_XPT2046_LCD_H

#include "stm32f1xx_hal.h"

/*
#define             macXPT2046_EXTI_GPIO_CLK                        RCC_APB2Periph_GPIOE
#define             macXPT2046_EXTI_GPIO_PORT                       GPIOE
#define             macXPT2046_EXTI_GPIO_PIN                        GPIO_Pin_4
#define             macXPT2046_EXTI_SOURCE_PORT                     GPIO_PortSourceGPIOE
#define             macXPT2046_EXTI_SOURCE_PIN                      GPIO_PinSource4
#define             macXPT2046_EXTI_LINE                            EXTI_Line4
#define             macXPT2046_EXTI_IRQ                             EXTI4_IRQn
#define             macXPT2046_EXTI_INT_FUNCTION                    EXTI4_IRQHandler
*/

#define macXPT2046_EXTI_ActiveLevel 0

#define macXPT2046_EXTI_Read() HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)

/*
#define             macXPT2046_SPI_GPIO_CLK                     RCC_APB2Periph_GPIOE| RCC_APB2Periph_GPIOD

#define             macXPT2046_SPI_CS_PIN		            				GPIO_Pin_13
#define             macXPT2046_SPI_CS_PORT		            			GPIOD

#define	            macXPT2046_SPI_CLK_PIN	                    GPIO_Pin_0
#define             macXPT2046_SPI_CLK_PORT	                    GPIOE

#define	            macXPT2046_SPI_MOSI_PIN	                    GPIO_Pin_2
#define	            macXPT2046_SPI_MOSI_PORT	                  GPIOE

#define	            macXPT2046_SPI_MISO_PIN	                    GPIO_Pin_3
#define	            macXPT2046_SPI_MISO_PORT	                  GPIOE
*/

#define macXPT2046_CS_ENABLE() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET)
#define macXPT2046_CS_DISABLE() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET)

#define macXPT2046_CLK_HIGH() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET)
#define macXPT2046_CLK_LOW() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET)

#define macXPT2046_MOSI_1() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET)
#define macXPT2046_MOSI_0() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET)

#define macXPT2046_MISO() HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)

#define macXPT2046_Coordinate_GramScan 1
#define macXPT2046_THRESHOLD_CalDiff 2

#define macXPT2046_CHANNEL_X 0x90
#define macXPT2046_CHANNEL_Y 0xd0

typedef struct
{
   uint16_t x;
   uint16_t y;

} strType_XPT2046_Coordinate;

typedef struct
{
   long double An,
       Bn,
       Cn,
       Dn,
       En,
       Fn,
       Divider;

} strType_XPT2046_Calibration;

typedef struct
{
   long double dX_X,
       dX_Y,
       dX,
       dY_X,
       dY_Y,
       dY;

} strType_XPT2046_TouchPara;

extern volatile uint8_t ucXPT2046_TouchFlag;

extern strType_XPT2046_TouchPara strXPT2046_TouchPara;

void XPT2046_Init(void);

uint8_t XPT2046_Touch_Calibrate(void);
uint8_t XPT2046_Get_TouchedPoint(strType_XPT2046_Coordinate *displayPtr, strType_XPT2046_TouchPara *para);

void Check_touchkey(void);

//-----------------------------

#endif /* __BSP_TOUCH_H */
