/*
 * estadosBoton.h
 *
 *  Created on: 20 sep. 2019
 *      Author: nahuel
 */

#ifndef PROGRAMS_MANEJODEBOTONES_INC_ESTADOSBOTON_H_
#define PROGRAMS_MANEJODEBOTONES_INC_ESTADOSBOTON_H_
#include <sapi_gpio.h>

enum Estado{
 Button_up,Button_falling,Button_down,Button_rising
};


typedef void (* buttonhander)(void * );

typedef struct Pulsador{
	int estado;
	int ultimoCambio;
	int quePaso;
	int boton;
	buttonhander onPress;
	buttonhander onRelease;
	void * modelo;
}Pulsador;


void inciarPulsador(Pulsador * bn,gpioMap_t botonn, buttonhander onPress,buttonhander onRelease, void * modelo);
void controladorBoton(Pulsador * bn);
void controlDeLed(Pulsador * bn);
void pulsador_onPress(Pulsador * pulsador, buttonhander eventHandler);
void pulsador_onRelease(Pulsador * pulsador, buttonhander eventHandler);
int pasoTiempo(Pulsador * bn);



#endif /* PROGRAMS_MANEJODEBOTONES_INC_ESTADOSBOTON_H_ */
