/*
 * lab5_timer.c
 *
 *  Created on: Dec 7, 2021
 *      Author: QuocTrong
 */

#include "lab5_timer.h"

int timer0_counter = 0;
unsigned char timer0_flag = 0;
const int TIMER_CIRCLE = 10;


void setTimer0(int duration){
	timer0_counter = duration/TIMER_CIRCLE;
	timer0_flag = 0;
}

void timer0_run(){
	timer0_counter--;
	if(timer0_counter<=0){
		timer0_flag = 1;
	}
}

unsigned char get_timer0_flag(){
	return timer0_flag;
}
