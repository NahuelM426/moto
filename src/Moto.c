#include <sapi.h>
#include <sapi_gpio.h>
#include "../inc/Moto.h"

void MotoIniciar(Moto * mt,unsigned char arranque,unsigned char electricidad){
	mt->arrancado=arranque;
	mt->electricidad=electricidad;
}

unsigned char motoArrancado(Moto* model) {
	return model->arrancado;
}

unsigned char motoElectricidad(Moto* model) {
	return model->electricidad;
}

