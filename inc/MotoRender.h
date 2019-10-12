/*
 * MotoRender.h
 *
 *  Created on: 12 oct. 2019
 *      Author: nahuel
 */

#ifndef PROGRAMS_TP_MOTO_INC_MOTORENDER_H_
#define PROGRAMS_TP_MOTO_INC_MOTORENDER_H_
#include <sapi.h>
#include "Moto.h"

typedef struct MotoRender{
	Moto * moto;
	gpioMap_t Arranque;
	gpioMap_t Circuito;
}MotoRender;

void iniciarMotoRender(MotoRender * Mt, gpioMap_t pin,gpioMap_t pin2, Moto * moto);
void controladorMotoRender(MotoRender * Mt);

#endif /* PROGRAMS_TP_MOTO_INC_MOTORENDER_H_ */
