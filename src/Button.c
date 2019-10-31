/*
 * Button.c
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 */

#include "Button.h"



void initDelayCounter(Button * button);
void changeState(Button * button, ButtonState state);


void button_init(Button * button, gpioMap_t gpio,buttonhander onReleaseApagar ,void * model) {
	button->gpio = gpio;
	button->onRelease = onReleaseApagar;
	button->state = UP;
	button->model = model;
}

void changeState(Button * button, ButtonState state) {
	button->state = state;
}

void initDelayCounter(Button * button) {
	delayInit(&button->delay, 40);
}

void button_update(Button * button) {
	bool_t readed = gpioRead( button->gpio );

	bool_t pressed = !readed;
	switch(button->state) {

		case UP : {
			if(pressed) {
				changeState(button, FALLING);
				initDelayCounter(button);
			}
			break;
		};
		case DOWN : {
			if(!pressed) {
				changeState(button, RISING);
				initDelayCounter(button);
			}
			break;
		};
		case FALLING : {
			if(delayRead(&button->delay)) {
				if(pressed) {
					changeState(button, DOWN);
					button->onRelease(button->model);
				}
				else {
					changeState(button, UP);
				}
			}
			break;
		}
		case RISING : {
			if(delayRead(&button->delay)) {
				if(!pressed) {
					changeState(button, UP);
				}
				else {
					changeState(button, DOWN);
				}
			}
			break;
		}
		default : {
			//error
			changeState(button, pressed ? DOWN : UP);
		}

	}
}

