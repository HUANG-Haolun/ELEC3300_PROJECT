/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  ELEC 3300 HW1 main.c
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "sdio.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX 8
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int i, j;
float x;
double y;
int ANDresult = 0;
int ORresult = 0;
int XORresult = 0;

// Please fill the array stdid with your Student ID
// Say if your student ID is 20123456, array will be
// int stdid[8] = {2,0,1,2,3,4,5,6};
int stdid[8] = {2, 0, 7, 6, 0, 7, 3, 5};
int swapid[8];
int oddid[8];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  // debug
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
  MX_DMA_Init();
  MX_SDIO_SD_Init();
  MX_SPI1_Init();
  MX_USART3_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  int counter = 0;
  int sum = 0;

  i = 0x20760735;
  // i is called Binary Coded Decimal (BCD) representation of your student ID
  // i.e. i = 0x20123456

  j = 0x53706702;
  // j is the reverse Binary Coded Decimal (BCD) representation of your student ID
  // i.e. j = 0x65432102

  x = 2076.0735;
  // x is a decimal floating point number of your student ID with
  // first 4 digits before the decimal point and last 4 digits after the decimal point

  y = 20760735.53706702;
  // y is a decimal floating point number of your student ID with
  // all 8 digits before the decimal point and reverse 8 digits after the decimal point

  for (counter = 0; counter < MAX; counter++)
  {
    // write ONE line of code to store your stdid reversely and store it in swapid
    // Say if your int stdid[8] = {2,0,1,2,3,4,5,6};
    // Your int swapid[8] will be finally = {6,5,4,3,2,1,0,2} after the for loop.
    swapid[counter] = stdid[7-counter];

    // write ONE line of code to store check if your stdid[?] is odd and store it in oddid
    // Say if your int stdid[8] = {2,0,1,2,3,4,5,6};
    // Your int oddid[8] will be finally = {0,0,1,0,1,0,1,0} after the for loop
    oddid[counter] = stdid[counter]%2;

    // Write ONE line to sum the stdid digits
    // AFTER the for loop, sum should return the summation of your student id digits.
    sum += stdid[counter];
  };

  __asm("NOP"); // Check Point for Question 2.

  // Write ONE line of code to perform bitwise AND between i and j, and store it in ANDresult
  ANDresult = i & j;
  // Write ONE line of code to perform bitwise OR between i and j, and store it in ORresult
  ORresult = i | j;
  // Write ONE line of code to perform bitwise XOR between i and j, and store it in XORresult
  XORresult = i ^ j;
  __asm("NOP"); // Check Point for Question 4 and 5.

  __asm("MOV  R1, 0x0735"); // Make R1 = i
  __asm("MOVT R1, 0x2076"); // Replace the corresponding digits according to your SID

  __asm("MOV  R2, 0x6702"); // Make R2 = j
  __asm("MOVT R2, 0x5370"); // Replace the corresponding digits according to your SID

  __asm("MOV  R0, 0x0"); // Make R0 = 0

  __asm("ADDS R3, R0, R0");
  // Look at the Hex value of xpsr register **AFTER** addition.
  // What are the statuses of the N, Z, C, V flags **AFTER** addition ?
  // Please explain the result.

  __asm("NOP"); // Check Point for Question 6

  __asm("ADDS R3, R1, R2"); // i + j
  // Look at the Hex value of xpsr register **AFTER** addition.
  // What are the statuses of C and V flags **AFTER** addition ?
  // Please explain your result **IN DETAIL** with respect to your value in R3 to R1 and R2.

  __asm("NOP"); // Check Point for Question 7

  __asm("ADDS R3, R0, R0");
  // Just guess what I want to do in here ? :-P.

  __asm("SUBS R3, R1, R2"); // i - j
  // Look at the Hex value of xpsr register **AFTER** addition.
  // What are the statuses of C and V flags **AFTER** addition ?
  // Please explain your result in **IN DETAIL** with respect to your value in R3 to R1 and R2.

  __asm("NOP"); // Check Point for Question 8

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    __asm("NOP"); // While Loop
  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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
