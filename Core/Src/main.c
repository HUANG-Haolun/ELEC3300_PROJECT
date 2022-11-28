/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "color_detection.h"
#include "lcd.h"
#include "solve.h"
#include "string.h"
#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "cubeControl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint16_t red = 100;
volatile uint16_t green = 50;
volatile uint16_t blue = 0;
volatile uint8_t fy;
volatile uint8_t Ov7725_vsync;
volatile uint8_t rx_buffer;
extern volatile uint8_t bt_flags;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  motor_flag = 7;
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxBuffer, 3);
  LCD_INIT();
  cube_t cube;
  memset(cube.face, 0, 54);
  // char line_buffer[54]  = "BBBFULRUBUURFRRRDFDFLUFDLRUUUFFDRLDLRRFLLBBLFDLUBBDDBD";
  // memcpy(cube.face, line_buffer, 54);
  LCD_Clear(50, 80, 140, 70, RED);
  LCD_DrawString(75, 100, "CAMERA TESTER");

  HAL_Delay(2000);

  while (Ov7725_Init() != SUCCESS)
    ;
  Ov7725_vsync = 0;
  uint8_t cnt = 0;
  uint8_t startCam = 0;
  while (1 && bt_flags != 4)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (bt_flags == 2)
    {
      startCam = 1;
    }
    if (startCam)
    {
      if (Ov7725_vsync == 2 && cnt < 12)
      {
        FIFO_PREPARE;
        //	LCD_Rst();
        uint16_t temp_colors[9];
        uint16_t squareColors[9];
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
            if (j == 110 && i == 60)
              squareColors[0] = Camera_Data;

            if (j == 110 && i == 120)
              squareColors[1] = Camera_Data;

            if (j == 110 && i == 170)
              squareColors[2] = Camera_Data;

            // // middle row
            if (j == 160 && i == 60)
              squareColors[3] = Camera_Data;

            if (j == 160 && i == 120)
              squareColors[4] = Camera_Data;

            if (j == 160 && i == 170)
              squareColors[5] = Camera_Data;

            // top row

            if (j == 210 && i == 60)
              squareColors[6] = Camera_Data;

            if (j == 210 && i == 120)
              squareColors[7] = Camera_Data;

            if (j == 210 && i == 170)
              squareColors[8] = Camera_Data;
          }
        }
        // j , i
        if (bt_flags == 1)
          cnt++;
        KNearest_match(squareColors, temp_colors, cnt, cube.face, bt_flags);

        LCD_DrawEllipse(110, 60, 5, 5, temp_colors[0]);  // 0 bottom left
        LCD_DrawEllipse(110, 120, 5, 5, temp_colors[1]); // 1 bottom mid
        LCD_DrawEllipse(110, 170, 5, 5, temp_colors[2]); // 2 bottom right

        LCD_DrawEllipse(160, 60, 5, 5, temp_colors[3]);  // 3 mid left
        LCD_DrawEllipse(160, 120, 5, 5, temp_colors[4]); // 4 center
        LCD_DrawEllipse(160, 170, 5, 5, temp_colors[5]); // 5 mid right

        LCD_DrawEllipse(210, 60, 5, 5, temp_colors[6]);  // 6 top left
        LCD_DrawEllipse(210, 120, 5, 5, temp_colors[7]); // 7 top mid
        LCD_DrawEllipse(210, 170, 5, 5, temp_colors[8]); // 8 top right
        if (bt_flags == 1)
        {
          bt_flags = 0;
          HAL_UART_Transmit(&huart3, (uint8_t *)cube.face, 54, 100);
        }

        if (cnt < 4)
        {
          K;
        }
        else
        {
          switch (cnt)
          {
          case 4:
            C;
            K;
            K;
            K;
            break;
          case 5:
          case 6:
          case 7:
            K;
            C1;
            K;
            C;
            K;
            K;
            K;
            break;
          case 8:
            K;
            C2;
            K;
            K;
            K;
          case 9:
          case 10:
            K;
            C;
            K;
            C1;
            K;
            K;
            K;
            break;
          case 11:
            K;
            C;
            K;
            K;
            K;
            break;
          }
        }

        HAL_Delay(1000);
        Ov7725_vsync = 0;
        continue;
      }
      if (cnt == 12)
      {
        LCD_Clear(0, 0, 240, 320, BACKGROUND);
        LCD_Clear(50, 80, 140, 70, ORANGE);
        LCD_DrawString(75, 100, "DETECTION DONE, WAITING FOR COMMAND");
        cnt++;
      }
        if (bt_flags == 3)
        {
          solve_Naive(&cube);
          for (uint16_t i = 0; i < cube.routeLen; i++)
          {
            switch (cube.route[i])
            {
            case 0:
              l();
              break;
            case 1:
              l1();
              break;
            case 2:
              l2();
              break;
            case 3:
              r();
              break;
            case 4:
              r1();
              break;
            case 5:
              r2();
              break;
            case 6:
              u();
              break;
            case 7:
              u1();
              break;
            case 8:
              u2();
              break;
            case 9:
              d();
              break;
            case 10:
              d1();
              break;
            case 11:
              d2();
              break;
            case 12:
              f();
              break;
            case 13:
              f1();
              break;
            case 14:
              f2();
              break;
            case 15:
              b();
              break;
            case 16:
              b1();
              break;
            case 17:
              b2();
              break;
            default:
              break;
            }
          }
        }
    }
  }

  LCD_Clear(0, 0, 240, 320, BACKGROUND);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
    // cnt++;
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
