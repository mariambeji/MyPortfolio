/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
extern void initialise_monitor_handles(void);
#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_gyro.h"
#include "math.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define PI 3.14159265359
#define MAX_SIZE 100
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/*################# RAW DATA ##################*/

int16_t Data_Mag_i16[3];
int16_t Data_Accel_i16[3];
float Data_Gyro_f[3];

/*################# CONVERTED DATA ############*/

float Data_f[9];
float Angle_f[3] ;
float measure_f=0;
float round_measure_f=0;

float Measured_Angle=0;
float Measured_Angle_Pred=0;
float vitesse_f=0;

uint8_t pData[10]={1,0xA,3,4,5,6,7,8,9,0xA};
uint8_t RxBuffer[MAX_SIZE]={0};
uint8_t Size=10;
uint8_t WaitForTx=0;
uint8_t WaitForRx=0;
uint8_t i=0;

char test[MAX_SIZE];
char Consigne_str[40];
float consigne=0;
char Start_str[40];
float Start=0;
char Kp_str[40];
float Kp=0;
char Ki_str[40];
float Ki=0;
char Kd_str[40];
float Kd=0;
uint8_t j=0;
float P=0,I=0,D=0,erreur=0,somme=0,erreur_pred=0;
float cons=0;

char Buf[40];

float magx,magy,magz;
char donne[10] ;
char mazzz[7];
int token = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM2_Init(void);
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
	MX_I2C2_Init();
	MX_USART1_UART_Init();
	MX_TIM6_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	// UART Init
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, RxBuffer, MAX_SIZE);
	// BSP Init
	BSP_ACCELERO_Init();
	BSP_GYRO_Init();
	BSP_MAGNETO_Init();
	// Motor Timer Init
	TIM2->CCR1=TIM2->ARR;
	TIM2->CCR3=TIM2->ARR;
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	// Sampling Timer Init
	HAL_TIM_Base_Start_IT(&htim6);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
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

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void)
{

	/* USER CODE BEGIN I2C2_Init 0 */

	/* USER CODE END I2C2_Init 0 */

	/* USER CODE BEGIN I2C2_Init 1 */

	/* USER CODE END I2C2_Init 1 */
	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x10909CEC;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C2_Init 2 */

	/* USER CODE END I2C2_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 10-1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 8000-1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */
	HAL_TIM_MspPostInit(&htim2);

}

/**
 * @brief TIM6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM6_Init(void)
{

	/* USER CODE BEGIN TIM6_Init 0 */

	/* USER CODE END TIM6_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM6_Init 1 */

	/* USER CODE END TIM6_Init 1 */
	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 10-1;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 40000-1;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM6_Init 2 */

	/* USER CODE END TIM6_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, M24SR64_Y_RF_DISABLE_Pin|M24SR64_Y_GPO_Pin|ISM43362_RST_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, ARD_D8_Pin|ISM43362_BOOT0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, PMOD_RESET_Pin|STSAFE_A100_RESET_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(SPSGRF_915_SPI3_CSN_GPIO_Port, SPSGRF_915_SPI3_CSN_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(ISM43362_SPI3_CSN_GPIO_Port, ISM43362_SPI3_CSN_Pin, GPIO_PIN_SET);

	/*Configure GPIO pins : M24SR64_Y_RF_DISABLE_Pin M24SR64_Y_GPO_Pin ISM43362_RST_Pin ISM43362_SPI3_CSN_Pin */
	GPIO_InitStruct.Pin = M24SR64_Y_RF_DISABLE_Pin|M24SR64_Y_GPO_Pin|ISM43362_RST_Pin|ISM43362_SPI3_CSN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : USB_OTG_FS_OVRCR_EXTI3_Pin SPBTLE_RF_IRQ_EXTI6_Pin ISM43362_DRDY_EXTI1_Pin */
	GPIO_InitStruct.Pin = USB_OTG_FS_OVRCR_EXTI3_Pin|SPBTLE_RF_IRQ_EXTI6_Pin|ISM43362_DRDY_EXTI1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : BUTTON_EXTI13_Pin */
	GPIO_InitStruct.Pin = BUTTON_EXTI13_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BUTTON_EXTI13_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PC5 LSM3MDL_DRDY_EXTI8_Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_5|LSM3MDL_DRDY_EXTI8_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : ARD_D3_Pin */
	GPIO_InitStruct.Pin = ARD_D3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ARD_D3_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : ARD_D8_Pin ISM43362_BOOT0_Pin SPSGRF_915_SPI3_CSN_Pin */
	GPIO_InitStruct.Pin = ARD_D8_Pin|ISM43362_BOOT0_Pin|SPSGRF_915_SPI3_CSN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : LPS22HB_INT_DRDY_EXTI0_Pin LSM6DSL_INT1_EXTI11_Pin PMOD_IRQ_EXTI12_Pin */
	GPIO_InitStruct.Pin = LPS22HB_INT_DRDY_EXTI0_Pin|LSM6DSL_INT1_EXTI11_Pin|PMOD_IRQ_EXTI12_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : PMOD_RESET_Pin STSAFE_A100_RESET_Pin */
	GPIO_InitStruct.Pin = PMOD_RESET_Pin|STSAFE_A100_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
/*############################## Kalman function ##############################*/
float kalman_filter( float ADC_Value)
{
	float x_k1_k1,x_k_k1;
	static float ADC_OLD_Value;
	float Z_k;
	static float P_k1_k1;

	static float Q = 0.0001;//Q: Regulation noise, Q increases, dynamic response becomes faster, and convergence stability becomes worse
	static float R = 0.005; //R: Test noise, R increases, dynamic response becomes slower, convergence stability becomes better
	static float Kg = 0;
	static float P_k_k1 = 1;

	float kalman_adc;
	static float kalman_adc_old=0;
	Z_k = ADC_Value;
	x_k1_k1 = kalman_adc_old;

	x_k_k1 = x_k1_k1;
	P_k_k1 = P_k1_k1 + Q;

	Kg = P_k_k1/(P_k_k1 + R);

	kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
	P_k1_k1 = (1 - Kg)*P_k_k1;
	P_k_k1 = P_k1_k1;

	ADC_OLD_Value = ADC_Value;
	kalman_adc_old = kalman_adc;

	return kalman_adc;
}


/*############################## Normalize angles ###############################*/

void vNormalizeAngles(float *pData)
{

	float NormAccel = 0.0 ;
	float NormGyro = 0.0 ;
	float NormMag	= 0.0 ;

	NormMag = sqrt((pData[0]*pData[0])+(pData[1]*pData[1])+(pData[2]*pData[2])) ;
	NormGyro = sqrt((pData[3]*pData[3])+(pData[4]*pData[4])+(pData[5]*pData[5])) ;
	NormAccel= sqrt((pData[6]*pData[6])+(pData[7]*pData[7])+(pData[8]*pData[8])) ;


	pData[0] = pData[0]/NormMag;
	pData[1] = pData[1]/NormMag;
	pData[2] = pData[2]/NormMag;

	pData[3] = pData[3]/NormGyro;
	pData[4] = pData[4]/NormGyro;
	pData[5] = pData[5]/NormGyro;

	pData[6] = pData[6]/NormAccel;
	pData[7] = pData[7]/NormAccel;
	pData[8] = pData[8]/NormAccel;

}

/*############################## Convert Data ###################################*/

void vConvertData(int16_t *pDataMag ,float *pDataGyro , int16_t *pDataAccel,float* Data_f)
{

	Data_f[0] =(Data_Mag_i16[0]/1000.0) ;
	Data_f[1] =(Data_Mag_i16[1]/1000.0);
	Data_f[2] =(Data_Mag_i16[2]/1000.0) ;

	Data_f[3] =  Data_Gyro_f[0]/1000.0 ;
	Data_f[4] =  Data_Gyro_f[1]/1000.0 ;
	Data_f[5] =  Data_Gyro_f[2]/1000.0 ;

	Data_f[6] = ((Data_Accel_i16[0]*9.81)/1000) ;
	Data_f[7] = ((Data_Accel_i16[1]*9.81)/1000) ;
	Data_f[8] =((Data_Accel_i16[2]*9.81)/1000) ;

}

/*############################## Calculate Angles #################################*/

void vCalculateAngles(float *pData,float* Angle_f)
{
	Angle_f[0] =  180*atan2(Data_f[7],Data_f[8])/PI;
	Angle_f[1] = 180*atan2(Data_f[6],Data_f[8])/PI;
	Angle_f[2]=180*atan2((-Data_f[1]*cos(Angle_f[0])+Data_f[3]*sin(Angle_f[0])),(Data_f[0]*cos(Angle_f[1])+Data_f[1]*sin(Angle_f[1])*sin(Angle_f[0])+Data_f[2]*sin(Angle_f[1])*cos(Angle_f[0])))/PI ;
}


/*############################## Calculate Angles #################################*/
float fRound(float var)
{
	char str[40];
	sprintf(str, "%.1f", var);
	// scan string value in var
	sscanf(str, "%f", &var);
	return var;
}


/*############################## Callback function ##############################*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
// Data acquisition
	BSP_MAGNETO_GetXYZ(&Data_Mag_i16[0]);
	BSP_GYRO_GetXYZ(&Data_Gyro_f[0]);
	BSP_ACCELERO_AccGetXYZ(&Data_Accel_i16[0]);

// Data normalization
	vConvertData(&Data_Mag_i16[0],&Data_Gyro_f[0],&Data_Accel_i16[0],&Data_f[0]);
	vNormalizeAngles(&Data_f[0]);
	vCalculateAngles(&Data_f[0],&Angle_f[0]);
	measure_f = kalman_filter(Angle_f[0]);
	round_measure_f = fRound(measure_f);

// Data sending
	Measured_Angle_Pred = Measured_Angle;
	Measured_Angle = round_measure_f+90;
	vitesse_f = ((Measured_Angle - Measured_Angle_Pred)/5);
	sprintf(Buf,"%.1f\n",Measured_Angle);
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)Buf, 5);

// PID mode
	if(Start==1)
	{
		erreur=consigne-round_measure_f;
		P=Kp*erreur;
		somme=somme+erreur;
		I=somme*Ki;
		D=(erreur-erreur_pred)*Kd;
		cons=P+I+D;
		// Simple Saturation
		if(cons>TIM2->ARR)
		{
			cons=TIM2->ARR;
		}
		else if(cons<0)
		{
			cons=0;
		}
		TIM2->CCR3=cons;
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

	}
// Stop mode
	else if(Start==0)
	{
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	}

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	// UART function for communication with LabVIEW interface
	if(huart==&huart1)
	{
		HAL_UARTEx_ReceiveToIdle_IT(&huart1, RxBuffer, MAX_SIZE);
		sprintf(test,"%s",RxBuffer);
		i=0;
		uint8_t k=0;
		for(j=0;j<MAX_SIZE;j++)
		{
			if(i==0)
			{
				if(test[j]==',')
				{
					test[j]='.';
				}
				Consigne_str[k]=test[j];
				k++;
				if(test[j]=='\n')
				{
					k=0;
					i++;
				}
			}
			else if(i==1)
			{
				if(test[j]==',')
				{
					test[j]='.';
				}
				Start_str[k]=test[j];
				k++;
				if(test[j]=='\n')
				{
					k=0;
					i++;
				}
			}
			else if(i==2)
			{
				if(test[j]==',')
				{
					test[j]='.';
				}
				Kp_str[k]=test[j];
				k++;
				if(test[j]=='\n')
				{
					k=0;
					i++;
				}
			}
			else if(i==3)
			{
				if(test[j]==',')
				{
					test[j]='.';
				}
				Ki_str[k]=test[j];
				k++;
				if(test[j]=='\n')
				{
					k=0;
					i++;
				}
			}
			else if(i==4)
			{
				if(test[j]==',')
				{
					test[j]='.';
				}
				Kd_str[k]=test[j];
				k++;
				if(test[j]=='\n')
				{
					k=0;
					i++;
				}
			}
		}
		i=0;
		consigne = atof(Consigne_str);
		Start = atof(Start_str);
		Kp = atof(Kp_str);
		Ki = atof(Ki_str);
		Kd = atof(Kd_str);
	}
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
