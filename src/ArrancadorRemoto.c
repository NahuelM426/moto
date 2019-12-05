/*
 * ArrancadorRemoto.c
 *
 *  Created on: 12 oct. 2019
 *      Author: nahuel
 */
#include "ArrancadorRemoto.h"
#include "sapi.h"


void ArrancadorRemoto_initBt(
		ArrancadorRemoto * uartConnector,
		Moto * model,
		Handler byteReadedEventHandler,
		buttonhander oup
		){
	ArrancadorRemoroUartConnector_init(
		uartConnector,
		UART_232,
		model,
		byteReadedEventHandler,
		oup,
		9600,
		10,
		"\r\n"
		);
}

void ArrancadorRemoroUartConnector_init( ArrancadorRemoto * uartConnector,uartMap_t map, Moto * model,
		Handler byteReadedEventHandler,buttonhander oup,
		unsigned int baudRate,
		unsigned int maxBytesReadedPerCycle,
		char * endOfPackage
		){
	uartConnector->map = map;
	uartConnector->model = model;
	uartConnector->byteReadedEventHandler = byteReadedEventHandler;
	uartConnector->Oup=oup;
	uartConnector->maxBytesReadedPerCycle = maxBytesReadedPerCycle;
	uartConnector->endOfPackage = endOfPackage;
	uartConfig(map, baudRate);
}
int pasotiempo (ArrancadorRemoto * bn){
	Moto * model = (Moto *)bn;
	return delayRead(&model->tickDelStart);
}
int tiempoActivo(ArrancadorRemoto * uar){
	Moto * model = (Moto *)uar;
	return model->tiempo;
}

void uartConnector_update(ArrancadorRemoto * uartConnector) {
	int i = 0;
	uint8_t byte;

	while (i < uartConnector->maxBytesReadedPerCycle && uartReadByte(uartConnector->map, &byte)) {
		uartConnector->byteReadedEventHandler(uartConnector->model, byte);
		i++;

	}
	if(pasotiempo(uartConnector->model)&& tiempoActivo(uartConnector->model)==Iniciar){
		uartConnector->Oup(uartConnector->model);
	}
	;

}
void ArrancarRemoto_send(ArrancadorRemoto * uartConnector, char * string) {
	uartWriteString(uartConnector->map, string);
	uartWriteString(uartConnector->map, uartConnector->endOfPackage);
}

