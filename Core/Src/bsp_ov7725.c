#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "lcd.h"
#include "stdarg.h"
#include "math.h"

typedef struct Reg
{
	uint8_t Address;
	uint8_t Value;
} Reg_Info;

Reg_Info Sensor_Config[] =
	{
		{CLKRC, 0x00}, /*clock config*/
		{COM7, 0x46},  /*QVGA RGB565 */
		{HSTART, 0x3f},
		{HSIZE, 0x50},
		{VSTRT, 0x03},
		{VSIZE, 0x78},
		{HREF, 0x00},
		{HOutSize, 0x50},
		{VOutSize, 0x78},
		{EXHCH, 0x00},

		/*DSP control*/
		{TGT_B, 0x7f},
		{FixGain, 0x09},
		{AWB_Ctrl0, 0xe0},
		{DSP_Ctrl1, 0xff},
		{DSP_Ctrl2, 0x20},
		{DSP_Ctrl3, 0x00},
		{DSP_Ctrl4, 0x00},

		/*AGC AEC AWB*/
		{COM8, 0xf0},
		{COM4, 0x81}, /*Pll AEC CONFIG*/
		{COM6, 0xc5},
		{COM9, 0x21},
		{BDBase, 0xFF},
		{BDMStep, 0x01},
		{AEW, 0x34},
		{AEB, 0x3c},
		{VPT, 0xa1},
		{EXHCL, 0x00},
		{AWBCtrl3, 0xaa},
		{COM8, 0xff},
		{AWBCtrl1, 0x5d},

		{EDGE1, 0x0a},
		{DNSOff, 0x01},
		{EDGE2, 0x01},
		{EDGE3, 0x01},

		{MTX1, 0x5f},
		{MTX2, 0x53},
		{MTX3, 0x11},
		{MTX4, 0x1a},
		{MTX5, 0x3d},
		{MTX6, 0x5a},
		{MTX_Ctrl, 0x1e},

		{BRIGHT, 0x00},
		{CNST, 0x25},
		{USAT, 0x65},
		{VSAT, 0x65},
		{UVADJ0, 0x81},
		{SDE, 0x06},

		/*GAMMA config*/
		{GAM1, 0x0c},
		{GAM2, 0x16},
		{GAM3, 0x2a},
		{GAM4, 0x4e},
		{GAM5, 0x61},
		{GAM6, 0x6f},
		{GAM7, 0x7b},
		{GAM8, 0x86},
		{GAM9, 0x8e},
		{GAM10, 0x97},
		{GAM11, 0xa4},
		{GAM12, 0xaf},
		{GAM13, 0xc5},
		{GAM14, 0xd7},
		{GAM15, 0xe8},
		{SLOP, 0x20},

		{HUECOS, 0x80},
		{HUESIN, 0x80},
		{DSPAuto, 0xff},
		{DM_LNL, 0x00},
		{BDBase, 0x99},
		{BDMStep, 0x03},
		{LC_RADI, 0x00},
		{LC_COEF, 0x13},
		{LC_XC, 0x08},
		{LC_COEFB, 0x14},
		{LC_COEFR, 0x17},
		{LC_CTR, 0x05},

		{COM3, 0xd0}, /*Horizontal mirror image*/

		/*night mode auto frame rate control*/
		{COM5, 0xf5}, /*auto reduce rate*/
					  //{COM5,		0x31},	/*no auto*/
};

uint8_t OV7725_REG_NUM = sizeof(Sensor_Config) / sizeof(Sensor_Config[0]);

extern uint8_t Ov7725_vsync;

// static int face = 0;
uint16_t pixels[100][150];
/************************************************
 * Sensor_Init
 ************************************************/
ErrorStatus Ov7725_Init(void)
{
	uint16_t i = 0;
	uint8_t Sensor_IDCode = 0;

	if (0 == SCCB_WriteByte(0x12, 0x80)) /*reset sensor */
	{
		return ERROR;
	}

	if (0 == SCCB_ReadByte(&Sensor_IDCode, 1, 0x0b)) /* read sensor ID*/
	{
		return ERROR;
	}
	// DEBUG("Sensor ID is 0x%x", Sensor_IDCode);

	if (Sensor_IDCode == OV7725_ID)
	{
		for (i = 0; i < OV7725_REG_NUM; i++)
		{
			if (0 == SCCB_WriteByte(Sensor_Config[i].Address, Sensor_Config[i].Value))
			{
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}

	return SUCCESS;
}

void ImagDisp()
{

}
