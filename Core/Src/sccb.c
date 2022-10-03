#include "sccb.h"

#define DEV_ADR 0x42 

static void SCCB_delay(void)
{
	uint16_t i = 400;
	while (i)
	{
		i--;
	}
}
void SCCB_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStructure.Pin = GPIO_PIN_7;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM; //
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
}
static int SCCB_Start(void)
{
	SDA_H;
	SCL_H;
	SCCB_delay();
	if (!SDA_read)
		return DISABLE; 
	SCCB_delay();
	if (SDA_read)
		return DISABLE;
	SDA_L;
	SCCB_delay();
	return ENABLE;
}

static void SCCB_Stop(void)
{
	SCL_L;
	SCCB_delay();
	SDA_L;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	SDA_H;
	SCCB_delay();
}

static void SCCB_Ack(void)
{
	SCL_L;
	SCCB_delay();
	SDA_L;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	SCL_L;
	SCCB_delay();
}

static void SCCB_NoAck(void)
{
	SCL_L;
	SCCB_delay();
	SDA_H;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	SCL_L;
	SCCB_delay();
}

static int SCCB_WaitAck(void)
{
	SCL_L;
	SCCB_delay();
	SDA_H;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	while (SDA_read)
		;
	// {
	// 	SCL_L;
	// 	return DISABLE;
	// }
	SCL_L;
	return ENABLE;
}

static void SCCB_SendByte(uint8_t SendByte)
{
	uint8_t i = 8;
	while (i--)
	{
		SCL_L;
		SCCB_delay();
		if (SendByte & 0x80)
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		SendByte <<= 1;
		SCCB_delay();
		SCL_H;
		SCCB_delay();
	}
	SCL_L;
}

static int SCCB_ReceiveByte(void)
{
	uint8_t i = 8;
	uint8_t ReceiveByte = 0;

	SDA_H;
	while (i--)
	{
		ReceiveByte <<= 1;
		SCL_L;
		SCCB_delay();
		SCL_H;
		SCCB_delay();
		if (SDA_read)
		{
			ReceiveByte |= 0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
}

int SCCB_WriteByte(uint16_t WriteAddress, uint8_t SendByte)
{
	if (!SCCB_Start())
	{
		return DISABLE;
	}
	SCCB_SendByte(DEV_ADR);
	if (!SCCB_WaitAck())
	{
		SCCB_Stop();
		return DISABLE;
	}
	SCCB_SendByte((uint8_t)(WriteAddress & 0x00FF));
	SCCB_WaitAck();
	SCCB_SendByte(SendByte);
	SCCB_WaitAck();
	SCCB_Stop();
	return ENABLE;
}

int SCCB_ReadByte(uint8_t *pBuffer, uint16_t length, uint8_t ReadAddress)
{
	if (!SCCB_Start())
	{
		return DISABLE;
	}
	SCCB_SendByte(DEV_ADR); 
	if (!SCCB_WaitAck())
	{
		SCCB_Stop();
		return DISABLE;
	}
	SCCB_SendByte(ReadAddress); 
	SCCB_WaitAck();
	SCCB_Stop();

	if (!SCCB_Start())
	{
		return DISABLE;
	}
	SCCB_SendByte(DEV_ADR + 1); 
	if (!SCCB_WaitAck())
	{
		SCCB_Stop();
		return DISABLE;
	}
	while (length)
	{
		*pBuffer = SCCB_ReceiveByte();
		if (length == 1)
		{
			SCCB_NoAck();
		}
		else
		{
			SCCB_Ack();
		}
		pBuffer++;
		length--;
	}
	SCCB_Stop();
	return ENABLE;
}
/*********************************************END OF FILE**********************/
