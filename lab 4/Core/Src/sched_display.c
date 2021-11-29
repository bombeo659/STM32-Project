/*
 * sched_display.c
 *
 *  Created on: Nov 28, 2021
 *      Author: QuocTrong
 */

#include "main.h"
#include "sched_main.h"
#include "sched_display.h"

UART_HandleTypeDef huart1;

void display_task(int idx) {
	uint32_t time = HAL_GetTick();
	uint32_t tmp = time;
	int index = 0;
	while(tmp > 0) {
		index++;
		tmp /= 10;
	}
	uint8_t msg[index];
	sprintf(msg, "%ld", time);

	uint8_t task[15] = "ms - Task -\n\r";
	task[10] = Run_Tasks_G[idx].TaskID + '0';
	uint8_t endline[30] = "---------------\n\r";
	HAL_UART_Transmit(&huart1, msg, sizeof(msg), 100);
	HAL_UART_Transmit(&huart1, task, sizeof(task), 100);
	HAL_UART_Transmit(&huart1, endline, sizeof(endline), 100);
}
