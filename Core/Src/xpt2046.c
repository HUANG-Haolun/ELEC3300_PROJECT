#include "xpt2046.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>

static void XPT2046_DelayUS(__IO uint32_t ulCount);
static void XPT2046_WriteCMD(uint8_t ucCmd);
static uint16_t XPT2046_ReadCMD(void);
static uint16_t XPT2046_ReadAdc(uint8_t ucChannel);
static void XPT2046_ReadAdc_XY(int16_t *sX_Ad, int16_t *sY_Ad);
static uint8_t XPT2046_ReadAdc_Smooth_XY(strType_XPT2046_Coordinate *pScreenCoordinate);
static uint8_t XPT2046_Calculate_CalibrationFactor(strType_XPT2046_Coordinate *pDisplayCoordinate, strType_XPT2046_Coordinate *pScreenSample, strType_XPT2046_Calibration *pCalibrationFactor);

strType_XPT2046_TouchPara strXPT2046_TouchPara = {0.085958, -0.001073, -4.979353, -0.001750, 0.065168, -13.318824};
// { 0.001030, 0.064188, -10.804098, -0.085584, 0.001420, 324.127036 };

volatile uint8_t ucXPT2046_TouchFlag = 0;

static void XPT2046_DelayUS(__IO uint32_t ulCount)
{
	uint32_t i;

	for (i = 0; i < ulCount; i++)
	{
		uint8_t uc = 12;

		while (uc--)
			;
	}
}

static void XPT2046_WriteCMD(uint8_t ucCmd)
{
	uint8_t i;

	macXPT2046_MOSI_0();

	macXPT2046_CLK_LOW();

	for (i = 0; i < 8; i++)
	{
		((ucCmd >> (7 - i)) & 0x01) ? macXPT2046_MOSI_1() : macXPT2046_MOSI_0();

		XPT2046_DelayUS(5);

		macXPT2046_CLK_HIGH();

		XPT2046_DelayUS(5);

		macXPT2046_CLK_LOW();
	}
}

static uint16_t XPT2046_ReadCMD(void)
{
	uint8_t i;
	uint16_t usBuf = 0, usTemp;

	macXPT2046_MOSI_0();

	macXPT2046_CLK_HIGH();

	for (i = 0; i < 12; i++)
	{
		macXPT2046_CLK_LOW();

		usTemp = macXPT2046_MISO();

		usBuf |= usTemp << (11 - i);

		macXPT2046_CLK_HIGH();
	}

	return usBuf;
}

static uint16_t XPT2046_ReadAdc(uint8_t ucChannel)
{
	XPT2046_WriteCMD(ucChannel);

	return XPT2046_ReadCMD();
}

static void XPT2046_ReadAdc_XY(int16_t *sX_Ad, int16_t *sY_Ad)
{
	int16_t sX_Ad_Temp, sY_Ad_Temp;

	sX_Ad_Temp = XPT2046_ReadAdc(macXPT2046_CHANNEL_X);

	XPT2046_DelayUS(1);

	sY_Ad_Temp = XPT2046_ReadAdc(macXPT2046_CHANNEL_Y);

	*sX_Ad = sX_Ad_Temp;
	*sY_Ad = sY_Ad_Temp;
}

#if 0                 
static uint8_t XPT2046_ReadAdc_Smooth_XY ( strType_XPT2046_Coordinate * pScreenCoordinate )
{
	uint8_t ucCount = 0;
	
	int16_t sAD_X, sAD_Y;
	int16_t sBufferArray [ 2 ] [ 9 ] = { { 0 }, { 0 } };  

	int32_t lAverage  [ 3 ], lDifference [ 3 ];
	

	do
	{		   
		XPT2046_ReadAdc_XY ( & sAD_X, & sAD_Y );
		
		sBufferArray [ 0 ] [ ucCount ] = sAD_X;  
		sBufferArray [ 1 ] [ ucCount ] = sAD_Y;
		
		ucCount ++; 
			 
	} while ( ( macXPT2046_EXTI_Read() == macXPT2046_EXTI_ActiveLevel ) && ( ucCount < 9 ) ); 	//??????????????TP_INT_IN?z???? ???? ucCount<9*/
	 
	

	if ( macXPT2046_EXTI_Read() != macXPT2046_EXTI_ActiveLevel )
		ucXPT2046_TouchFlag = 0;			


	if ( ucCount == 9 )   								
	{  

		lAverage  [ 0 ] = ( sBufferArray [ 0 ] [ 0 ] + sBufferArray [ 0 ] [ 1 ] + sBufferArray [ 0 ] [ 2 ] ) / 3;
		lAverage  [ 1 ] = ( sBufferArray [ 0 ] [ 3 ] + sBufferArray [ 0 ] [ 4 ] + sBufferArray [ 0 ] [ 5 ] ) / 3;
		lAverage  [ 2 ] = ( sBufferArray [ 0 ] [ 6 ] + sBufferArray [ 0 ] [ 7 ] + sBufferArray [ 0 ] [ 8 ] ) / 3;
		

		lDifference [ 0 ] = lAverage  [ 0 ]-lAverage  [ 1 ];
		lDifference [ 1 ] = lAverage  [ 1 ]-lAverage  [ 2 ];
		lDifference [ 2 ] = lAverage  [ 2 ]-lAverage  [ 0 ];
		

		lDifference [ 0 ] = lDifference [ 0 ]>0?lDifference [ 0 ]: ( -lDifference [ 0 ] );
		lDifference [ 1 ] = lDifference [ 1 ]>0?lDifference [ 1 ]: ( -lDifference [ 1 ] );
		lDifference [ 2 ] = lDifference [ 2 ]>0?lDifference [ 2 ]: ( -lDifference [ 2 ] );
		

		if (  lDifference [ 0 ] > macXPT2046_THRESHOLD_CalDiff  &&  lDifference [ 1 ] > macXPT2046_THRESHOLD_CalDiff  &&  lDifference [ 2 ] > macXPT2046_THRESHOLD_CalDiff  ) 
			return 0;
		

		if ( lDifference [ 0 ] < lDifference [ 1 ] )
		{
			if ( lDifference [ 2 ] < lDifference [ 0 ] ) 
				pScreenCoordinate ->x = ( lAverage  [ 0 ] + lAverage  [ 2 ] ) / 2;
			else 
				pScreenCoordinate ->x = ( lAverage  [ 0 ] + lAverage  [ 1 ] ) / 2;	
		}
		
		else if ( lDifference [ 2 ] < lDifference [ 1 ] ) 
			pScreenCoordinate -> x = ( lAverage  [ 0 ] + lAverage  [ 2 ] ) / 2;
		
		else 
			pScreenCoordinate ->x = ( lAverage  [ 1 ] + lAverage  [ 2 ] ) / 2;
		
		

		lAverage  [ 0 ] = ( sBufferArray [ 1 ] [ 0 ] + sBufferArray [ 1 ] [ 1 ] + sBufferArray [ 1 ] [ 2 ] ) / 3;
		lAverage  [ 1 ] = ( sBufferArray [ 1 ] [ 3 ] + sBufferArray [ 1 ] [ 4 ] + sBufferArray [ 1 ] [ 5 ] ) / 3;
		lAverage  [ 2 ] = ( sBufferArray [ 1 ] [ 6 ] + sBufferArray [ 1 ] [ 7 ] + sBufferArray [ 1 ] [ 8 ] ) / 3;
		
		lDifference [ 0 ] = lAverage  [ 0 ] - lAverage  [ 1 ];
		lDifference [ 1 ] = lAverage  [ 1 ] - lAverage  [ 2 ];
		lDifference [ 2 ] = lAverage  [ 2 ] - lAverage  [ 0 ];
		

		lDifference [ 0 ] = lDifference [ 0 ] > 0 ? lDifference [ 0 ] : ( - lDifference [ 0 ] );
		lDifference [ 1 ] = lDifference [ 1 ] > 0 ? lDifference [ 1 ] : ( - lDifference [ 1 ] );
		lDifference [ 2 ] = lDifference [ 2 ] > 0 ? lDifference [ 2 ] : ( - lDifference [ 2 ] );
		
		
		if ( lDifference [ 0 ] > macXPT2046_THRESHOLD_CalDiff && lDifference [ 1 ] > macXPT2046_THRESHOLD_CalDiff && lDifference [ 2 ] > macXPT2046_THRESHOLD_CalDiff ) 
			return 0;
		
		if ( lDifference [ 0 ] < lDifference [ 1 ] )
		{
			if ( lDifference [ 2 ] < lDifference [ 0 ] ) 
				pScreenCoordinate ->y =  ( lAverage  [ 0 ] + lAverage  [ 2 ] ) / 2;
			else 
				pScreenCoordinate ->y =  ( lAverage  [ 0 ] + lAverage  [ 1 ] ) / 2;	
		}
		else if ( lDifference [ 2 ] < lDifference [ 1 ] ) 
			pScreenCoordinate ->y =  ( lAverage  [ 0 ] + lAverage  [ 2 ] ) / 2;
		else
			pScreenCoordinate ->y =  ( lAverage  [ 1 ] + lAverage  [ 2 ] ) / 2;
		
		
		return 1;
		
		
	}
	
	else if ( ucCount > 1 )
	{
		pScreenCoordinate ->x = sBufferArray [ 0 ] [ 0 ];
		pScreenCoordinate ->y = sBufferArray [ 1 ] [ 0 ];
	
		return 0;
		
	}  
	
	
	return 0; 
	
	
}

#else
static uint8_t XPT2046_ReadAdc_Smooth_XY(strType_XPT2046_Coordinate *pScreenCoordinate)
{
	uint8_t ucCount = 0, i;

	int16_t sAD_X, sAD_Y;
	int16_t sBufferArray[2][10] = {{0}, {0}};

	int32_t lX_Min, lX_Max, lY_Min, lY_Max;

	do
	{
		XPT2046_ReadAdc_XY(&sAD_X, &sAD_Y);

		sBufferArray[0][ucCount] = sAD_X;
		sBufferArray[1][ucCount] = sAD_Y;

		ucCount++;

	} while ((macXPT2046_EXTI_Read() == macXPT2046_EXTI_ActiveLevel) && (ucCount < 10));

	if (macXPT2046_EXTI_Read() != macXPT2046_EXTI_ActiveLevel)
		ucXPT2046_TouchFlag = 0;

	if (ucCount == 10)
	{
		lX_Max = lX_Min = sBufferArray[0][0];
		lY_Max = lY_Min = sBufferArray[1][0];

		for (i = 1; i < 10; i++)
		{
			if (sBufferArray[0][i] < lX_Min)
				lX_Min = sBufferArray[0][i];

			else if (sBufferArray[0][i] > lX_Max)
				lX_Max = sBufferArray[0][i];
		}

		for (i = 1; i < 10; i++)
		{
			if (sBufferArray[1][i] < lY_Min)
				lY_Min = sBufferArray[1][i];

			else if (sBufferArray[1][i] > lY_Max)
				lY_Max = sBufferArray[1][i];
		}

		pScreenCoordinate->x = (sBufferArray[0][0] + sBufferArray[0][1] + sBufferArray[0][2] + sBufferArray[0][3] + sBufferArray[0][4] +
								sBufferArray[0][5] + sBufferArray[0][6] + sBufferArray[0][7] + sBufferArray[0][8] + sBufferArray[0][9] - lX_Min - lX_Max) >>
							   3;

		pScreenCoordinate->y = (sBufferArray[1][0] + sBufferArray[1][1] + sBufferArray[1][2] + sBufferArray[1][3] + sBufferArray[1][4] +
								sBufferArray[1][5] + sBufferArray[1][6] + sBufferArray[1][7] + sBufferArray[1][8] + sBufferArray[1][9] - lY_Min - lY_Max) >>
							   3;

		return 1;
	}

	return 0;
}

#endif

static uint8_t XPT2046_Calculate_CalibrationFactor(strType_XPT2046_Coordinate *pDisplayCoordinate, strType_XPT2046_Coordinate *pScreenSample, strType_XPT2046_Calibration *pCalibrationFactor)
{
	uint8_t ucRet = 1;

	pCalibrationFactor->Divider = ((pScreenSample[0].x - pScreenSample[2].x) * (pScreenSample[1].y - pScreenSample[2].y)) -
								  ((pScreenSample[1].x - pScreenSample[2].x) * (pScreenSample[0].y - pScreenSample[2].y));

	if (pCalibrationFactor->Divider == 0)
		ucRet = 0;

	else
	{

		pCalibrationFactor->An = ((pDisplayCoordinate[0].x - pDisplayCoordinate[2].x) * (pScreenSample[1].y - pScreenSample[2].y)) -
								 ((pDisplayCoordinate[1].x - pDisplayCoordinate[2].x) * (pScreenSample[0].y - pScreenSample[2].y));

		pCalibrationFactor->Bn = ((pScreenSample[0].x - pScreenSample[2].x) * (pDisplayCoordinate[1].x - pDisplayCoordinate[2].x)) -
								 ((pDisplayCoordinate[0].x - pDisplayCoordinate[2].x) * (pScreenSample[1].x - pScreenSample[2].x));

		pCalibrationFactor->Cn = (pScreenSample[2].x * pDisplayCoordinate[1].x - pScreenSample[1].x * pDisplayCoordinate[2].x) * pScreenSample[0].y +
								 (pScreenSample[0].x * pDisplayCoordinate[2].x - pScreenSample[2].x * pDisplayCoordinate[0].x) * pScreenSample[1].y +
								 (pScreenSample[1].x * pDisplayCoordinate[0].x - pScreenSample[0].x * pDisplayCoordinate[1].x) * pScreenSample[2].y;

		pCalibrationFactor->Dn = ((pDisplayCoordinate[0].y - pDisplayCoordinate[2].y) * (pScreenSample[1].y - pScreenSample[2].y)) -
								 ((pDisplayCoordinate[1].y - pDisplayCoordinate[2].y) * (pScreenSample[0].y - pScreenSample[2].y));

		pCalibrationFactor->En = ((pScreenSample[0].x - pScreenSample[2].x) * (pDisplayCoordinate[1].y - pDisplayCoordinate[2].y)) -
								 ((pDisplayCoordinate[0].y - pDisplayCoordinate[2].y) * (pScreenSample[1].x - pScreenSample[2].x));

		pCalibrationFactor->Fn = (pScreenSample[2].x * pDisplayCoordinate[1].y - pScreenSample[1].x * pDisplayCoordinate[2].y) * pScreenSample[0].y +
								 (pScreenSample[0].x * pDisplayCoordinate[2].y - pScreenSample[2].x * pDisplayCoordinate[0].y) * pScreenSample[1].y +
								 (pScreenSample[1].x * pDisplayCoordinate[0].y - pScreenSample[0].x * pDisplayCoordinate[1].y) * pScreenSample[2].y;
	}

	return ucRet;
}

uint8_t XPT2046_Touch_Calibrate(void)
{
#if 1
	uint8_t i;

	char cStr[10];

	uint16_t usScreenWidth, usScreenHeigth;
	uint16_t usTest_x = 0, usTest_y = 0, usGap_x = 0, usGap_y = 0;

	char *pStr = 0;

	strType_XPT2046_Coordinate strCrossCoordinate[4], strScreenSample[4];

	strType_XPT2046_Calibration CalibrationFactor;

#if (macXPT2046_Coordinate_GramScan == 1) || (macXPT2046_Coordinate_GramScan == 4)
	usScreenWidth = LCD_Default_Max_Width;
	usScreenHeigth = LCD_Default_Max_Heigth;

#elif (macXPT2046_Coordinate_GramScan == 2) || (macXPT2046_Coordinate_GramScan == 3)
	usScreenWidth = LCD_Default_Max_Heigth;
	usScreenHeigth = LCD_Default_Max_Width;

#endif

	strCrossCoordinate[0].x = usScreenWidth >> 2;
	strCrossCoordinate[0].y = usScreenHeigth >> 2;

	strCrossCoordinate[1].x = strCrossCoordinate[0].x;
	strCrossCoordinate[1].y = (usScreenHeigth * 3) >> 2;

	strCrossCoordinate[2].x = (usScreenWidth * 3) >> 2;
	strCrossCoordinate[2].y = strCrossCoordinate[1].y;

	strCrossCoordinate[3].x = strCrossCoordinate[2].x;
	strCrossCoordinate[3].y = strCrossCoordinate[0].y;

	LCD_GramScan(1);

	// for (i = 0; i < 4; i++)
	// {
	// 	LCD_Clear(0, 0, usScreenWidth, usScreenHeigth, BACKGROUND);

	// 	pStr = "Touch Calibrate ......";
	// 	LCD_DrawString_Color((usScreenWidth - (strlen(pStr) - 7) * WIDTH_EN_CHAR) >> 1, usScreenHeigth >> 1, pStr, BACKGROUND, RED);

	// 	sprintf(cStr, "%d", i + 1);
	// 	LCD_DrawString_Color(usScreenWidth >> 1, (usScreenHeigth >> 1) - HEIGHT_EN_CHAR, cStr, BACKGROUND, RED);

	// 	XPT2046_DelayUS(100000);

	// 	LCD_DrawCross(strCrossCoordinate[i].x, strCrossCoordinate[i].y);

	// 	while (!XPT2046_ReadAdc_Smooth_XY(&strScreenSample[i]))
	// 		;
	// }

	XPT2046_Calculate_CalibrationFactor(strCrossCoordinate, strScreenSample, &CalibrationFactor);

	// if (CalibrationFactor.Divider == 0)
	// 	goto Failure;

	usTest_x = ((CalibrationFactor.An * strScreenSample[3].x) + (CalibrationFactor.Bn * strScreenSample[3].y) + CalibrationFactor.Cn) / CalibrationFactor.Divider;
	usTest_y = ((CalibrationFactor.Dn * strScreenSample[3].x) + (CalibrationFactor.En * strScreenSample[3].y) + CalibrationFactor.Fn) / CalibrationFactor.Divider;

	usGap_x = (usTest_x > strCrossCoordinate[3].x) ? (usTest_x - strCrossCoordinate[3].x) : (strCrossCoordinate[3].x - usTest_x);
	usGap_y = (usTest_y > strCrossCoordinate[3].y) ? (usTest_y - strCrossCoordinate[3].y) : (strCrossCoordinate[3].y - usTest_y);

	// if ((usGap_x > 10) || (usGap_y > 10))
		// goto Failure;

	strXPT2046_TouchPara.dX_X = (CalibrationFactor.An * 1.0) / CalibrationFactor.Divider;
	strXPT2046_TouchPara.dX_Y = (CalibrationFactor.Bn * 1.0) / CalibrationFactor.Divider;
	strXPT2046_TouchPara.dX = (CalibrationFactor.Cn * 1.0) / CalibrationFactor.Divider;

	strXPT2046_TouchPara.dY_X = (CalibrationFactor.Dn * 1.0) / CalibrationFactor.Divider;
	strXPT2046_TouchPara.dY_Y = (CalibrationFactor.En * 1.0) / CalibrationFactor.Divider;
	strXPT2046_TouchPara.dY = (CalibrationFactor.Fn * 1.0) / CalibrationFactor.Divider;

#endif

	// LCD_Clear(0, 0, usScreenWidth, usScreenHeigth, BACKGROUND);

	// pStr = "Calibrate Succed";
	// LCD_DrawString_Color((usScreenWidth - strlen(pStr) * WIDTH_EN_CHAR) >> 1, usScreenHeigth >> 1, pStr, BACKGROUND, RED);

	// XPT2046_DelayUS(200000);

	return 1;

Failure:

	LCD_Clear(0, 0, usScreenWidth, usScreenHeigth, BACKGROUND);

	pStr = "Calibrate fail";
	LCD_DrawString_Color((usScreenWidth - strlen(pStr) * WIDTH_EN_CHAR) >> 1, usScreenHeigth >> 1, pStr, BACKGROUND, RED);

	pStr = "try again";
	LCD_DrawString_Color((usScreenWidth - strlen(pStr) * WIDTH_EN_CHAR) >> 1, (usScreenHeigth >> 1) + HEIGHT_EN_CHAR, pStr, BACKGROUND, RED);

	XPT2046_DelayUS(1000000);

	return 0;
}

uint8_t XPT2046_Get_TouchedPoint(strType_XPT2046_Coordinate *pDisplayCoordinate, strType_XPT2046_TouchPara *pTouchPara)
{
	uint8_t ucRet = 1;

	strType_XPT2046_Coordinate strScreenCoordinate;

	if (XPT2046_ReadAdc_Smooth_XY(&strScreenCoordinate))
	{
		pDisplayCoordinate->x = ((pTouchPara->dX_X * strScreenCoordinate.x) + (pTouchPara->dX_Y * strScreenCoordinate.y) + pTouchPara->dX);
		pDisplayCoordinate->y = ((pTouchPara->dY_X * strScreenCoordinate.x) + (pTouchPara->dY_Y * strScreenCoordinate.y) + pTouchPara->dY);
	}

	else
		ucRet = 0;

	return ucRet;
}

void Check_touchkey(void)
{
	strType_XPT2046_Coordinate strDisplayCoordinate;

	if (XPT2046_Get_TouchedPoint(&strDisplayCoordinate, &strXPT2046_TouchPara))
	{
		if ((strDisplayCoordinate.y > 232) && (strDisplayCoordinate.y < 282))
		{
			if ((strDisplayCoordinate.x > 95) && (strDisplayCoordinate.x < 145))
			{
				GPIOB->ODR ^= GPIO_PIN_1;
			}
		}
	}
}
