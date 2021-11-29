/*
 * input_processing.c
 *
 *  Created on: Sep 30, 2021
 *      Author: QuocTrong
 */


#include "main.h"
#include "input_reading.h"
int TIMER_CYCLE = 10;
int timer0_counter = 0;
int timer0_flag = 0;
void setTimer0 (int duration){
	timer0_counter = duration/TIMER_CYCLE;
	timer0_flag = 0;
}
void timer_run0(){
	if(timer0_counter > 0){
		timer0_counter --;
		if( timer0_counter == 0)
			timer0_flag = 1;
	}
}
void reset_12LED(){
	HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin
	                          |LED4_Pin|LED5_Pin, GPIO_PIN_RESET);
}
void display_12LED(int status){
	switch (status) {
	case 0: // RED - GREEN - col
		HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_RESET);
		break;
	case 1: // RED - YELLOW - row
		HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_SET);
		break;
	case 2: // RED - GREEN - row
		HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_SET);
		break;
	case 3: // RED - YELLOW - col
		HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_SET);
		break;
	case 4: // RED - YELLOW - col
		if(timer0_flag){
			setTimer0(500);
			HAL_GPIO_TogglePin(GPIOA, LED0_Pin);
			HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
		}
		HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_SET);
		break;
	case 5: // RED - YELLOW - col
		if(timer0_flag){
			setTimer0(500);
			HAL_GPIO_TogglePin(GPIOA, LED1_Pin);
			HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
		}
		HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_SET);
		break;
	case 6: // RED - YELLOW - col
		if(timer0_flag){
			setTimer0(500);
			HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
			HAL_GPIO_TogglePin(GPIOA, LED5_Pin);
		}
		HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void display_7SEG_1(int num){
	uint8_t val = num;
	if(val < 0x0A){
		HAL_GPIO_WritePin(GPIOB, MODE0_Pin, ((val>>3)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE1_Pin, ((val>>2)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE2_Pin, ((val>>1)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE3_Pin, ((val>>0)&0x01));

		HAL_GPIO_WritePin(GPIOB, MODE4_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, MODE5_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, MODE6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, MODE7_Pin, 0);
	}
	if(val >= 0x0A && val < 0x64){
		uint8_t val1 = 0x0A;
		if(val>= val1){
			val = val - val1;
			while(val >= 0x0A){
				val = val + val1;
				val1 += 0x0A;
				val = val - val1;
			}
		}
		HAL_GPIO_WritePin(GPIOB, MODE0_Pin, ((val>>3)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE1_Pin, ((val>>2)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE2_Pin, ((val>>1)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE3_Pin, ((val>>0)&0x01));

		uint8_t a = val1/0x0A;
		HAL_GPIO_WritePin(GPIOB, MODE4_Pin, ((a>>3)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE5_Pin, ((a>>2)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE6_Pin, ((a>>1)&0x01));
		HAL_GPIO_WritePin(GPIOB, MODE7_Pin, ((a>>0)&0x01));
	}
}
void display_7SEG_2(int num){
	uint8_t val = num;
	if(val < 0x0A){
		HAL_GPIO_WritePin(GPIOB, VAL0_Pin, ((val>>3)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL1_Pin, ((val>>2)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL2_Pin, ((val>>1)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL3_Pin, ((val>>0)&0x01));

		HAL_GPIO_WritePin(GPIOB, VAL4_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, VAL5_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, VAL6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, VAL7_Pin, 0);
	}
	if(val >= 0x0A && val < 0x64){
		uint8_t val1 = 0x0A;
		if(val>= val1){
			val = val - val1;
			while(val >= 0x0A){
				val = val + val1;
				val1 += 0x0A;
				val = val - val1;
			}
		}
		HAL_GPIO_WritePin(GPIOB, VAL0_Pin, ((val>>3)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL1_Pin, ((val>>2)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL2_Pin, ((val>>1)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL3_Pin, ((val>>0)&0x01));

		uint8_t a = val1/0x0A;
		HAL_GPIO_WritePin(GPIOB, VAL4_Pin, ((a>>3)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL5_Pin, ((a>>2)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL6_Pin, ((a>>1)&0x01));
		HAL_GPIO_WritePin(GPIOB, VAL7_Pin, ((a>>0)&0x01));
	}
}
void func_mode1(){
	if(timer0_flag){
		setTimer0(1000);
		if(state_mode1 == 0){
			if(timeTotal > 0){
				display_7SEG_1(timeTotal);
				if((timeTotal - timeAmber) > 0){
					display_7SEG_2(timeTotal - timeAmber);
					display_12LED(0);
				} else{
					display_12LED(1);
					display_7SEG_2(timeTotal);
				}
				timeTotal --;
			} else {
				state_mode1 = 1;
				timeTotal = timeRed;
			}
		}
		if(state_mode1 == 1){
			if(timeTotal > 0){
				display_7SEG_2(timeTotal);
				if((timeTotal - timeAmber) > 0){
					display_7SEG_1(timeTotal - timeAmber);
					display_12LED(2);
				} else{
					display_12LED(3);
					display_7SEG_1(timeTotal);
				}
				timeTotal --;
			} else {
				state_mode1 = 0;
				timeTotal = timeRed;
			}
		}
	}
}
void func_mode2(){
	display_7SEG_1(02);
	display_12LED(4);
	if(is_button_pressed(1)){
		if(press[1]){
			timeRed ++;
			if(timeRed>99) timeRed = 0;
			press[1] = 0;
		}
	} else press[1] = 1;
	display_7SEG_2(timeRed);

	if(is_button_pressed(2)){
		if(press[2]){
			timeGreen += timeRed - time_buffer[0];
			time_buffer[0] = timeRed;
			reset_12LED();
			flagPressButton3 = 1;
			press[2] = 0;
		}
	} else{
		press[2] = 1;
	}
}

void func_mode3(){
	display_7SEG_1(03);
	display_12LED(5);
	if(is_button_pressed(1)){
		if(press[1]){
			timeAmber ++;
			if(timeAmber>99) timeAmber = 0;
			press[1] = 0;
		}
	} else press[1] = 1;

	display_7SEG_2(timeAmber);

	if(is_button_pressed(2)){
		if(press[2]){
			timeRed += timeAmber - time_buffer[1];
			time_buffer[1] = timeAmber;
			reset_12LED();
			flagPressButton3 = 1;
			press[2] = 0;
		}
	} else{
		press[2] = 1;
	}
}
void func_mode4(){
	display_7SEG_1(04);
	display_12LED(6);
	if(is_button_pressed(1)){
		if(press[1]){
			timeGreen ++;
			if(timeGreen>99) timeGreen = 0;
			press[1] = 0;
		}
	} else press[1] = 1;

	display_7SEG_2(timeGreen);

	if(is_button_pressed(2)){
		if(press[2]){
			timeRed += timeGreen - time_buffer[2];
			time_buffer[2] = timeGreen;
			reset_12LED();
			flagPressButton3 = 1;
			press[2] = 0;
		}
	} else{
		press[2] = 1;
	}
}
enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState = BUTTON_RELEASED;
enum Mode {MODE1, MODE2, MODE3, MODE4};
enum Mode mode = MODE1;

void fsm_for_input_processing(void){
	switch (mode){
	case MODE1:
		if(is_button_pressed(0)){
			if(press[0] == 1){
				mode = MODE2;
				reset_12LED();
				press[0] = 0;
			}
		} else{
			press[0] = 1;
		}
		func_mode1();
		break;
	case MODE2:
		if(is_button_pressed(0)){
			if(press[0] == 1){
				mode = MODE3;
				reset_12LED();
				if(flagPressButton3 == 0){
					timeRed = time_buffer[0];
				} else flagPressButton3 = 0;
				press[0] = 0;
			}
		} else{
			press[0] = 1;
		}
		func_mode2();
		break;
	case MODE3:
		if(is_button_pressed(0)){
			if(press[0] == 1){
				mode = MODE4;
				reset_12LED();
				if(flagPressButton3 == 0){
					timeAmber = time_buffer[1];
				} else flagPressButton3 = 0;
				press[0] = 0;
			}
		} else{
			press[0] = 1;
		}
		func_mode3();
		break;
	case MODE4:
		if(is_button_pressed(0)){
			if(press[0] == 1){
				mode = MODE1;
				reset_12LED();
				if(flagPressButton3 == 0){
					timeGreen = time_buffer[2];
				} else flagPressButton3 = 0;
				timeTotal = timeRed;
				press[0] = 0;
			}
		} else{
			press[0] = 1;
		}
		func_mode4();
		break;
	}
}
