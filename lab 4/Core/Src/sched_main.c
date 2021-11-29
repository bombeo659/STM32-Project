/*
 * sched_main.c
 *
 *  Created on: Nov 28, 2021
 *      Author: QuocTrong
 */

#include "sched_timer.h"
#include "sched_main.h"
#include "sched_display.h"

enum typeTask {
	STASK, QTASK
};

static uint8_t num_current_tasks, num_current_tasks_run, TASKID;
static uint32_t RUNME;

void SCH_Init(){
	int i = 0;
	while(i < SCH_MAX_TASKS && i < MAX_QUEUE) {
		SCH_Delete_Task(i);
		pop_out_run_queue();
		i++;
	}
	num_current_tasks = 0;
	num_current_tasks_run = 0;
	RUNME = 0;
	TASKID = 0;
	Error_code_G = FREE_OF_ERROR;
	Timer_Init();
	Watchdog_Init();
}
void SCH_Update(){
	if(SCH_tasks_G[0].pTask) {
		if(SCH_tasks_G[0].Delay > 0) {
			SCH_tasks_G[0].Delay--;
		}
		if(SCH_tasks_G[0].Delay == 0) {
			SCH_tasks_G[0].RunMe++;
		}
	}
}

void SCH_Dispatch_Tasks(){
	if(SCH_tasks_G[0].pTask && SCH_tasks_G[0].Delay == 0 && SCH_tasks_G[0].RunMe > 0) {
		// push task to queue
		push_to_run_queue(SCH_tasks_G[0]);
		// update info task
		SCH_tasks_G[0].RunMe--;
		if(SCH_tasks_G[0].Period > 0) {
			SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
			sTask temp_task = SCH_tasks_G[0];
			RUNME = temp_task.RunMe;
			SCH_Delete_Task(0);
			SCH_Add_Task(temp_task.pTask, temp_task.Delay, temp_task.Period);
		} else {
			SCH_Delete_Task(0);
		}
	}
	if(Run_Tasks_G[0].pTask) {
		// display info of task run current
		display_task(0);
		// process task
		(*Run_Tasks_G[0].pTask)();
		// pop to queue
		pop_out_run_queue();
	}
	// Report system status
	SCH_Report_Status();
	// The scheduler enters idle mode at this point
	SCH_Go_To_Sleep();
}

uint32_t SCH_Add_Task(void (*pfunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(num_current_tasks == SCH_MAX_TASKS) {
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}

	int index = 0; // index of new task
	int slot = -1; // slot of new task
	uint32_t delayTime = 0, tmpTime = 0;

	while(index < num_current_tasks){
		if(slot == -1) {
			tmpTime = delayTime;
			delayTime += SCH_tasks_G[index].Delay;
		}
		if(delayTime > DELAY) {
			slot = index;
			break;
		}
		index++;
	}
	num_current_tasks++; // increase num of task

	if(slot == -1) {
		SCH_tasks_G[index].pTask = pfunction;
		SCH_tasks_G[index].Delay = DELAY - delayTime; //update time delay of task
		SCH_tasks_G[index].Period = PERIOD;
		SCH_tasks_G[index].RunMe = RUNME;
		SCH_tasks_G[index].TaskID = (TASKID != 0)? TASKID : num_current_tasks;
	} else {
		// shift right task list to free slot for new task
		SCH_Shift_End_Tasks(slot, STASK); // flag STASK: SCH task list
		// add task into slot
		SCH_tasks_G[slot].pTask = pfunction;
		SCH_tasks_G[slot].Delay = DELAY - tmpTime; //update time delay of task
		SCH_tasks_G[slot].Period = PERIOD;
		SCH_tasks_G[slot].RunMe = RUNME;
		SCH_tasks_G[slot].TaskID = (TASKID != 0)? TASKID : num_current_tasks;
		// calculate delay time of task[slot+1]
		SCH_tasks_G[slot + 1].Delay -= SCH_tasks_G[slot].Delay;
	}
	RUNME = 0;
	TASKID = 0;

	return index;
}

uint8_t SCH_Delete_Task(uint32_t taskID){
	unsigned char code_state;
	if(!SCH_tasks_G[taskID].pTask){
		//No task at this location
		//Set the global error variable
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		code_state = _ERROR_;
	}
	else{
		code_state = _SUCCESS_;
		if(SCH_tasks_G[taskID].Period > 0) {
			TASKID = SCH_tasks_G[taskID].TaskID;
		}
		// shift right task list from index = taskID to delete task
		SCH_Shift_Start_Tasks(taskID, STASK);
		// update lastest task in list
		SCH_tasks_G[num_current_tasks-1].pTask = 0x0000;
		SCH_tasks_G[num_current_tasks-1].Delay = 0;
		SCH_tasks_G[num_current_tasks-1].Period = 0;
		SCH_tasks_G[num_current_tasks-1].RunMe = 0;
		SCH_tasks_G[num_current_tasks-1].TaskID = 0;
		// update num tasks
		num_current_tasks--;
	}
	return code_state;
}

uint32_t push_to_run_queue(sTask task) {
	if(num_current_tasks_run == MAX_QUEUE)
		return 0;
	Run_Tasks_G[num_current_tasks_run].pTask = task.pTask;
	Run_Tasks_G[num_current_tasks_run].TaskID = task.TaskID;
	num_current_tasks_run++;
	return 1;
}
uint8_t pop_out_run_queue() {
	if(num_current_tasks_run == 0)
		return 0;
	// shift right from 0 to delete first task
	SCH_Shift_Start_Tasks(0, QTASK); // flag QTASK: run task queue

	Run_Tasks_G[num_current_tasks_run-1].pTask = 0x0000;
	Run_Tasks_G[num_current_tasks_run-1].TaskID = 0;
	num_current_tasks_run--;
	return 1;
}

void Timer_Init(){

}
void Watchdog_Init(){

}
void SCH_Report_Status(){
#ifdef SCH_REPORT_ERRORS

#define Error_Port GPIOA
#endif
}
void SCH_Go_To_Sleep(){

}

void SCH_Shift_End_Tasks(uint32_t index, int typeArr) {
	if(typeArr == STASK) {
		for(int i = num_current_tasks - 1; i > index; i--) {
			SCH_tasks_G[i] = SCH_tasks_G[i-1];
		}
	}
	else if(typeArr == QTASK) {
		for(int i = num_current_tasks_run - 1; i > index; i--) {
			Run_Tasks_G[i] = Run_Tasks_G[i-1];
		}
	}
}
void SCH_Shift_Start_Tasks(uint32_t index, int typeArr) {
	if(typeArr == STASK) {
		for(int i = index; i < num_current_tasks - 1; i++) {
			SCH_tasks_G[i] = SCH_tasks_G[i+1];
		}
	}
	else if(typeArr == QTASK) {
		for(int i = index; i < num_current_tasks_run-1; i++) {
			Run_Tasks_G[i] = Run_Tasks_G[i+1];
		}
	}
}

