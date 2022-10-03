/**
 * @file ov7670.c
 * @author HUANG haolun (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ov7670.h"
#include "lcd.h"
typedef struct Reg
{
    uint8_t Address;
    uint8_t Value;
} Reg_Info;
volatile uint8_t OV7670_vsync ;
/* 寄存器参数配置 */
Reg_Info Sensor_Config[] =
    {
        {REG_CLKRC, 0x00}, /*clock config*/
        {REG_COM7, 0x46},  /*QVGA RGB565 */
        {REG_HSTART, 0x3f},
        {REG_HSIZE, 0x50},
        {REG_VSTRT, 0x03},
        {REG_VSIZE, 0x78},
        {REG_HREF, 0x00},
        {REG_HOutSize, 0x50},
        {REG_VOutSize, 0x78},
        {REG_EXHCH, 0x00},

        /*DSP control*/
        {REG_TGT_B, 0x7f},
        {REG_FixGain, 0x09},
        {REG_AWB_Ctrl0, 0xe0},
        {REG_DSP_Ctrl1, 0xff},
        {REG_DSP_Ctrl2, 0x20},
        {REG_DSP_Ctrl3, 0x00},
        {REG_DSP_Ctrl4, 0x00},

        /*AGC AEC AWB*/
        {REG_COM8, 0xf0},
        {REG_COM4, 0x81}, /*Pll AEC CONFIG*/
        {REG_COM6, 0xc5},
        {REG_COM9, 0x21},
        {REG_BDBase, 0xFF},
        {REG_BDMStep, 0x01},
        {REG_AEW, 0x34},
        {REG_AEB, 0x3c},
        {REG_VPT, 0xa1},
        {REG_EXHCL, 0x00},
        {REG_AWBCtrl3, 0xaa},
        {REG_COM8, 0xff},
        {REG_AWBCtrl1, 0x5d},

        {REG_EDGE1, 0x0a},
        {REG_DNSOff, 0x01},
        {REG_EDGE2, 0x01},
        {REG_EDGE3, 0x01},

        {REG_MTX1, 0x5f},
        {REG_MTX2, 0x53},
        {REG_MTX3, 0x11},
        {REG_MTX4, 0x1a},
        {REG_MTX5, 0x3d},
        {REG_MTX6, 0x5a},
        {REG_MTX_Ctrl, 0x1e},

        {REG_BRIGHT, 0x00},
        {REG_CNST, 0x25},
        {REG_USAT, 0x65},
        {REG_VSAT, 0x65},
        {REG_UVADJ0, 0x81},
        //{REG_SDE,		  0x20},
        {REG_SDE, 0x06},

        /*GAMMA config*/
        {REG_GAM1, 0x0c},
        {REG_GAM2, 0x16},
        {REG_GAM3, 0x2a},
        {REG_GAM4, 0x4e},
        {REG_GAM5, 0x61},
        {REG_GAM6, 0x6f},
        {REG_GAM7, 0x7b},
        {REG_GAM8, 0x86},
        {REG_GAM9, 0x8e},
        {REG_GAM10, 0x97},
        {REG_GAM11, 0xa4},
        {REG_GAM12, 0xaf},
        {REG_GAM13, 0xc5},
        {REG_GAM14, 0xd7},
        {REG_GAM15, 0xe8},
        {REG_SLOP, 0x20},

        {REG_HUECOS, 0x80},
        {REG_HUESIN, 0x80},
        {REG_DSPAuto, 0xff},
        {REG_DM_LNL, 0x00},
        {REG_BDBase, 0x99},
        {REG_BDMStep, 0x03},
        {REG_LC_RADI, 0x00},
        {REG_LC_COEF, 0x13},
        {REG_LC_XC, 0x08},
        {REG_LC_COEFB, 0x14},
        {REG_LC_COEFR, 0x17},
        {REG_LC_CTR, 0x05},

        {REG_COM3, 0xd0}, /*Horizontal mirror image*/

        /*night mode auto frame rate control*/
        {REG_COM5, 0xf5},
        //{REG_COM5,		0x31}
};

static void FIFO_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;


    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Pin = OV7725_OE_GPIO_PIN;
    HAL_GPIO_Init(OV7725_OE_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OV7725_WRST_GPIO_PIN;
    HAL_GPIO_Init(OV7725_WRST_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OV7725_RRST_GPIO_PIN;
    HAL_GPIO_Init(OV7725_RRST_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OV7725_RCLK_GPIO_PIN;
    HAL_GPIO_Init(OV7725_RCLK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OV7725_WE_GPIO_PIN;
    HAL_GPIO_Init(OV7725_WE_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OV7725_DATA_0_GPIO_PIN | OV7725_DATA_1_GPIO_PIN |
                             OV7725_DATA_2_GPIO_PIN | OV7725_DATA_3_GPIO_PIN |
                             OV7725_DATA_4_GPIO_PIN | OV7725_DATA_5_GPIO_PIN |
                             OV7725_DATA_6_GPIO_PIN | OV7725_DATA_7_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OV7725_DATA_GPIO_PORT, &GPIO_InitStructure);

    FIFO_OE_L(); 
    FIFO_WE_H(); 
}

static void VSYNC_GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.Pin = OV7725_VSYNC_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OV7725_VSYNC_GPIO_PORT, &GPIO_InitStructure);

    HAL_NVIC_SetPriority(OV7725_VSYNC_EXTI_IRQ, 0, 3);
    HAL_NVIC_EnableIRQ(OV7725_VSYNC_EXTI_IRQ);
}

HAL_StatusTypeDef OV7670_INIT()
{

    SCCB_GPIO_Config();
    FIFO_GPIO_Config();
    VSYNC_GPIO_Config();
    if (!SCCB_WriteByte(0x12, 0X80)) // Reset SCCB
    {
        return HAL_ERROR;
    }
    for (size_t i = 0; i < OV7670_REG_NUM; i++)
    {
        if (!SCCB_WriteByte(Sensor_Config[i].Address, Sensor_Config[i].Value))
            return ERROR;
    }

    return HAL_OK;
}

void OV7725_Window_Set(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
	uint8_t reg_raw, cal_temp;

	/*QVGA RGB565 */
	SCCB_WriteByte(REG_COM7, 0x46);

	/***************HSTART*********************/
	SCCB_ReadByte(&reg_raw, 1, REG_HSTART);

	cal_temp = (reg_raw + (sx >> 2));
	SCCB_WriteByte(REG_HSTART, cal_temp);

	/***************HSIZE*********************/
	SCCB_WriteByte(REG_HSIZE, width >> 2); 

	/***************VSTART*********************/
	SCCB_ReadByte(&reg_raw, 1, REG_VSTRT);
	cal_temp = (reg_raw + (sy >> 1));

	SCCB_WriteByte(REG_VSTRT, cal_temp);

	/***************VSIZE*********************/
	SCCB_WriteByte(REG_VSIZE, height >> 1); //

	/***************VSTART*********************/
	SCCB_ReadByte(&reg_raw, 1, REG_HREF);
	cal_temp = (reg_raw | (width & 0x03) | ((height & 0x01) << 2) | ((sx & 0x03) << 4) | ((sy & 0x01) << 6));

	SCCB_WriteByte(REG_HREF, cal_temp);

	/***************HOUTSIZIE /VOUTSIZE*********************/
	SCCB_WriteByte(REG_HOutSize, width >> 2);
	SCCB_WriteByte(REG_VOutSize, height >> 1);

	SCCB_ReadByte(&reg_raw, 1, REG_EXHCH);
	cal_temp = (reg_raw | (width & 0x03) | ((height & 0x01) << 2));

	SCCB_WriteByte(REG_EXHCH, cal_temp);
}

void Image_Display(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
	uint16_t i, j;
	uint16_t Camera_Data;

	LCD_OpenWindow(sx, sy, width, height);
	LCD_Write_Cmd(CMD_SetPixel);

	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			READ_FIFO_PIXEL(Camera_Data); 
			LCD_Write_Data(Camera_Data);
		}
	}
}
