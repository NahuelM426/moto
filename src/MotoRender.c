#include <sapi.h>
#include "MotoRender.h"

void iniciarMotoRender(MotoRender * Mt, gpioMap_t pin,gpioMap_t pin2, Moto * moto){
	Mt->moto=moto;
	Mt->Arranque=pin;
	Mt->Circuito=pin2;
}

void controladorMotoRender(MotoRender * Mt){
	gpioWrite(Mt->Arranque, motoArrancado(Mt->moto));
	gpioWrite(Mt->Circuito, motoElectricidad(Mt->moto));
}


