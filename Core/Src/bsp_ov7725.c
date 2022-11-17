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

uint16_t squareColors[9];
uint16_t true_colors[6] = { 0x31be,0xdA03, 0x2d63, 0xdc63,0xfdee, 0x0000}; 
uint16_t true1_colors[6] = {BLUE,RED, GREEN, ORANGE,WHITE, YELLOW}; 

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

void ImagDisp(int start_x, int start_y, int end_x, int end_y)
{
	//	LCD_Rst();

	//	uint16_t x, y;
	uint16_t Camera_Data;
	memset(squareColors, 0, sizeof(squareColors));
	LCD_Cam_Gram();
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 320; j++)
		{
			READ_FIFO_PIXEL(Camera_Data);
			LCD_Write_Data(Camera_Data);
			// bottom row
			if( j == 110 && i == 60)
				squareColors[0] = Camera_Data;
			
			if( j == 110 && i == 120)
				squareColors[1] = Camera_Data;
			
			if( j == 110 && i == 170)
				squareColors[2] = Camera_Data;
			
			// // middle row
			if (j == 160 && i == 60)
				squareColors[3] = Camera_Data;

			if (j == 160 && i == 120)
				squareColors[4] = Camera_Data;
			
			if (j == 160 && i == 170)
				squareColors[5] = Camera_Data;
			
			// top row

			if (j==210 && i==60)
				squareColors[6] = Camera_Data;
			
			if (j==210 && i==120)
				squareColors[7] = Camera_Data;
			
			if (j==210 && i==170)
				squareColors[8] = Camera_Data;
		}
	}
	//	LCD_DrawLine(75,35,230,35, 0x0000);
	//	LCD_DrawLine(75,190,230,190, 0x0000);
	//	LCD_DrawLine(75,35,75,190, 0x0000);
	//	LCD_DrawLine(230,35,230,190, 0x0000);
	// j , i
	uint16_t temp_colors[9];
	KNearest_match(temp_colors);
	LCD_DrawEllipse(110, 60, 5, 5, temp_colors[0]); // 0 bottom left
	LCD_DrawEllipse(110,120,5,5, temp_colors[1]); //1 bottom mid
	LCD_DrawEllipse(110,170,5,5, temp_colors[2]); //2 bottom right

	LCD_DrawEllipse(160,60,5,5, temp_colors[3]); // 3 mid left
	LCD_DrawEllipse(160,120,5,5, temp_colors[4]);// 4 center
	LCD_DrawEllipse(160,170,5,5, temp_colors[5]);// 5 mid right

	LCD_DrawEllipse(210,60,5,5, temp_colors[6]); // 6 top left
	LCD_DrawEllipse(210,120,5,5, temp_colors[7]); //7 top mid
	LCD_DrawEllipse(210,170,5,5, temp_colors[8]); //8 top right

	HAL_Delay(1000);
}


// Do a KNN match on the colors
// KNN match
void KNearest_match(uint16_t temp_colors[9])
{
	for (int i = 0; i < 9; i++)
	{
		int8_t temp[3];
		temp[0] = squareColors[i] & 0x1F;
		temp[1] = (squareColors[i] >> 5) & 0x3F;
		temp[2] = (squareColors[i] >> 11) & 0x1F;
		uint16_t min_dist = 0xFFFF;
		int min_index = -1;
		for (size_t i = 0; i < 6; i++)
		{
			int8_t temp2[3];
			temp2[0] = true_colors[i] & 0x1F;
			temp2[1] = (true_colors[i] >> 5) & 0x3F;
			temp2[2] = (true_colors[i] >> 11) & 0x1F;
			uint16_t dist = sqrt(pow(temp[0] - temp2[0], 2) + pow(temp[1] - temp2[1], 2) + pow(temp[2] - temp2[2], 2));
			if (dist < min_dist)
			{
				min_dist = dist;
				min_index = i;
			}
		}
		temp_colors[i] = true1_colors[min_index];
		
	}
	return;
}
