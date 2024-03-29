/**
 * Button.h
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 *
 * Es un botón que tiene antirebote.
 * Es un TAD que se crea a partir de un un modelo y un pin gpio.
 * Además se le configura las funciones onPress y OnRelease que son invocadas
 * cuando corresponden pasando el modelo como parámetro en un puntero a void.
 * Puede no configurarse alguna función si no se desea
 */

#ifndef PROGRAMS_SEMAFORO_INC_BUTTON_H_
#define PROGRAMS_SEMAFORO_INC_BUTTON_H_

#include "sapi.h"

typedef enum {
	UP, FALLING, DOWN, RISING,
} ButtonState;

typedef void (*buttonhander)(void *);

typedef struct Button {
	gpioMap_t gpio;
	buttonhander onRelease;
	void * model;
	ButtonState state;
	delay_t delay;
	delay_t apagar;
} Button;



void button_init(Button * button , gpioMap_t gpio,buttonhander onRelease, void * model);
void button_update(Button * button);

#endif /* PROGRAMS_SEMAFORO_INC_BUTTON_H_ */
