#include <sapi.h>
#include <sapi_gpio.h>
#include "../inc/Moto.h"
#ifndef NULL
	#define NULL 0
#endif

void MotoIniciar(Moto * mt,unsigned char arranque,unsigned char electricidad){
	mt->arrancado=arranque;
	mt->electricidad=electricidad;
	mt->observerObject = NULL;
	mt->observerFunction = NULL;
}
void Moto_setObserver(Moto * model, void * observerObject, MotoChangeObserver observerFunction ) {
	model->observerObject = observerObject;
	model->observerFunction = observerFunction;
}

unsigned char motoArrancado(Moto* model) {
	return model->arrancado;
}
void setValue(Moto * model, unsigned char value) {
	model->arrancado = value;
	if(model->observerFunction != NULL) {
		model->observerFunction(model->observerObject, model);
	}
}
unsigned char motoElectricidad(Moto* model) {
	return model->electricidad;
}
void Moto_enable(Moto * model) {
	setValue(model, 1);
}

void Moto_disable(Moto * model) {
	setValue(model, 0);
}


