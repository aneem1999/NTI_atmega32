
/**
 * @file main.c
 * @author Ahmed Naeem
 * @brief
 * @version 0.1
 * @date 2023-05-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#define F_CPU 16000000U
#include "SERVICES/SCM/SCM_int.h"

#include "HAL/LED/led.h"
#include "HAL/SSD/seven_seg.h"
#include "HAL/LCD/LCD.h"
#include "HAL/KEYPAD/keyPad.h"

#include "../SERVICES/FreeRTOS/FreeRTOSConfig.h"
#include "../SERVICES/FreeRTOS/FreeRTOS.h"
#include "../SERVICES/FreeRTOS/task.h"
#include "../SERVICES/FreeRTOS/semphr.h"
#include "../SERVICES/FreeRTOS/queue.h"
#include "../SERVICES/FreeRTOS/event_groups.h"

char Password[6] = {1, 2, 3, 4, 5, 6};

/*********************************************************
 *  queues
 */
QueueHandle_t passwordQ, equationQ;

/*********************************************************
 *  event groups
 */
EventGroupHandle_t CheckPasswordEventHandle;
/*********************************************************
 *  Semphores
 */
SemaphoreHandle_t keypadSemaphore;
SemaphoreHandle_t LCDSemaphore;

/************************************************************
 * 	Tasks
 */
BaseType_t CheckPasswordReturned;
TaskHandle_t CheckPasswordHandle = NULL;

BaseType_t getPasswordReturned;
TaskHandle_t getPasswordHandle = NULL;

BaseType_t getEquationReturned;
TaskHandle_t getEquationHandle = NULL;

BaseType_t calEquationReturned;
TaskHandle_t calEquationHandle = NULL;

void getPassword(void *ptr)
{

	u8 pass;
	static u8 index = 0;

	while (1)
	{
		vTaskSuspend(getEquationHandle);
		vTaskSuspend(CheckPasswordHandle);
		vTaskSuspend(calEquationHandle);

		/* Take Password from keypad*/
		xSemaphoreTake(LCDSemaphore, 10);
		if (index == 0)
		{
			LCD_ClearDisplay();
			LCD_WriteString("Enter Password :");
		}

		xSemaphoreTake(keypadSemaphore, 10);
		while (GetKeyPressed(&pass, 0) != KEY_PRESSED)
			;
		xSemaphoreGive(keypadSemaphore);
		LCD_GoToXY(1, index + 5);
		LCD_WriteData(pass);
		xSemaphoreGive(LCDSemaphore);

		index++;
		xQueueSend(passwordQ, &pass, 10);

		if (index >= 6)
		{

			vTaskResume(CheckPasswordHandle);
			index = 0;

			vTaskSuspend(getPasswordHandle);
		}

		vTaskDelay(200);
	}
}

void checkPassword(void *ptr)
{

	char temp;
	u8 index = 0, flag = 0;
	while (1)
	{
		vTaskSuspend(calEquationHandle);

		LCD_ClearDisplay();

		for (index = 0; index < 6; index++)
		{
			xQueueReceive(passwordQ, &temp, 10);

			if (Password[index] == (temp - 48))
			{

				flag++;
				xEventGroupSetBits(CheckPasswordEventHandle, (1 << index));
			}
			else
			{
			}
		}

		if (xEventGroupGetBits(CheckPasswordEventHandle) == 0x3F)
		// if (flag >= 5)
		{
			/* true password message */
			xSemaphoreTake(LCDSemaphore, 10);
			vTaskDelay(500);
			LCD_ClearDisplay();
			LCD_WriteString("True Password :");

			xSemaphoreGive(LCDSemaphore);
			xEventGroupClearBits(CheckPasswordEventHandle, 0x3F);

			vTaskDelay(1000);
			vTaskResume(getEquationHandle);

			flag = 0;
		}
		else
		{
			/* wrong password message */
			xSemaphoreTake(LCDSemaphore, 10);
			LCD_ClearDisplay();
			LCD_WriteString("Wrong Password :");
			xSemaphoreGive(LCDSemaphore);

			xEventGroupClearBits(CheckPasswordEventHandle, 0x3F);

			vTaskDelay(1000);

			vTaskResume(getPasswordHandle);
		}
		vTaskSuspend(CheckPasswordHandle);

		vTaskDelay(1000);
	}
}

void getEquation(void *ptr)
{

	u8 index = 0;
	u8 temp;
	while (1)
	{
		xSemaphoreTake(LCDSemaphore, 10);
		xSemaphoreTake(keypadSemaphore, 10);

		if (index == 0)
		{
			LCD_ClearDisplay();
			LCD_WriteString(" Enter Equation ");
			LCD_GoToXY(1, 0);
		}
		while (GetKeyPressed(&temp, 0) != KEY_PRESSED)
			;
		LCD_WriteData(temp);
		index++;
		xQueueSend(equationQ, &temp, 10);

		xSemaphoreGive(keypadSemaphore);

		xSemaphoreGive(LCDSemaphore);

		if (index == 4)
		{
			vTaskResume(calEquationHandle);
			index = 0;
		}
		vTaskDelay(1000);
	}
}

void calEquation(void *ptr)
{
	u8 EquationArr[6], temp;
	while (1)
	{
		for (u8 i = 0; i < 4; i++)
		{
			EquationArr[i] = xQueueReceive(equationQ, &EquationArr[i], 10);
		}
			LCD_WriteData(EquationArr[0]);
			

		switch (EquationArr[1])
		{
		case 'A':

			LCD_WriteData(EquationArr[0] + EquationArr[2]);

			break;
		case 'B':

			LCD_WriteData(EquationArr[0] - EquationArr[2] );

			break;
		case 'C':

			LCD_WriteData((EquationArr[0] * EquationArr[2]) );

			break;

		default:

			LCD_ClearDisplay();
			LCD_WriteString("Try again  ");
			LCD_WriteData(EquationArr[1]);

			break;
		}

		xSemaphoreTake(keypadSemaphore, 10);
		while (GetKeyPressed(&temp, 0) != KEY_PRESSED)
			;
		vTaskResume(getEquationHandle);
		xSemaphoreGive(keypadSemaphore);

		vTaskDelay(1000);
	}
}

int main()
{

	LCD_Init();
	KeyPad_init();

	/* Create the task, storing the handle. */
	CheckPasswordReturned = xTaskCreate(
		checkPassword,		   /* Function that implements the task. */
		"CheckPassword",	   /* Text name for the task. */
		100,				   /* Stack size in words, not bytes. */
		(void *)1,			   /* Parameter passed into the task. */
		2,					   /* Priority at which the task is created. */
		&CheckPasswordHandle); /* Used to pass out the created task's handle. */

	/* Create the task, storing the handle. */
	getPasswordReturned = xTaskCreate(
		getPassword,		 /* Function that implements the task. */
		"GetPassword",		 /* Text name for the task. */
		100,				 /* Stack size in words, not bytes. */
		(void *)1,			 /* Parameter passed into the task. */
		2,					 /* Priority at which the task is created. */
		&getPasswordHandle); /* Used to pass out the created task's handle. */

	/* Create the task, storing the handle. */
	getEquationReturned = xTaskCreate(
		getEquation,		 /* Function that implements the task. */
		"GetEquation,",		 /* Text name for the task. */
		100,				 /* Stack size in words, not bytes. */
		(void *)1,			 /* Parameter passed into the task. */
		1,					 /* Priority at which the task is created. */
		&getEquationHandle); /* Used to pass out the created task's handle. */

	/* Create the task, storing the handle. */
	calEquationReturned = xTaskCreate(
		calEquation,		 /* Function that implements the task. */
		"calEquation",		 /* Text name for the task. */
		100,				 /* Stack size in words, not bytes. */
		(void *)1,			 /* Parameter passed into the task. */
		1,					 /* Priority at which the task is created. */
		&calEquationHandle); /* Used to pass out the created task's handle. */

	/* creat Queue*/
	passwordQ = xQueueCreate(6, 1);
	equationQ = xQueueCreate(4, 1);

	/*Create semphores*/
	keypadSemaphore = xSemaphoreCreateBinary();
	LCDSemaphore = xSemaphoreCreateBinary();
	/* Creat event Group */
	CheckPasswordEventHandle = xEventGroupCreate();

	vTaskStartScheduler();

	while (1)
	{
	}
}
