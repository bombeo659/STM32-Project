/*
 * input_reading.c
 *
 *  Created on: Sep 30, 2021
 *      Author: QuocTrong
 */


#include "main.h"
#define N0_OF_BUTTONS 				       3

////timer interrupt duration is 10ms, so to pass 1 second,
////we need to jump to the interrupt service routine 100 time
//#define DURATION_FOR_AUTO_INCREASING	   100

#define BUTTON_IS_PRESSED                  0
#define BUTTON_IS_RELEASED                 1

static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

//we define a flag for a button pressed more than 1 second.
//static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];

//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
//static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];


void button_reading(void){
	for(int i = 0; i < N0_OF_BUTTONS; i ++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOA, 0x2000<<(uint16_t)i);

		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];

//		if(buttonBuffer[i] == BUTTON_IS_PRESSED){
//			//if a button is pressed, we start counting
//			if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
//				counterForButtonPress1s[i] +=1;
//			} else{
//				flagForButtonPress1s[i] = 1;
//			}
//		} else{
//			counterForButtonPress1s[i] = 0;
//			flagForButtonPress1s[i] = 0;
//		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

//unsigned char is_button_pressed_1s(unsigned char index){
//	if(index >= N0_OF_BUTTONS) return 0xff;
//	return (flagForButtonPress1s[index] == 1);
//}

