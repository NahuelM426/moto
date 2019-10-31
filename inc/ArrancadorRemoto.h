/*
 * ArrancadorRemoto.h
 *
 *  Created on: 12 oct. 2019
 *      Author: nahuel
 */

#ifndef PROGRAMS_TP_MOTO_INC_ARRANCADORREMOTO_H_
#define PROGRAMS_TP_MOTO_INC_ARRANCADORREMOTO_H_
#include "Moto.h"
#include "sapi.h"

typedef void (*Handler)(Moto * model, uint8_t byte);

typedef void (*buttonhander)(void *);

typedef struct uartConnector{
	uartMap_t map;
	Moto * model;
	Handler byteReadedEventHandler;
	delay_t tickDelStart;
	buttonhander Oup;
	unsigned int maxBytesReadedPerCycle;
	char * endOfPackage;
} ArrancadorRemoto;

void ArrancadorRemoto_initBt(ArrancadorRemoto * uartConnector, Moto * model, Handler byteReadedEventHandler,buttonhander oup);

void ArrancadorRemoroUartConnector_init(ArrancadorRemoto * uartConnector, uartMap_t map,
		Moto * model, Handler byteReadedEventHandler,buttonhander oup,
		unsigned int baudRate, unsigned int maxBytesReadedPerCycle,
		char * endOfPackage);

void uartConnector_update(ArrancadorRemoto * uartConnector);
void uartConnector_send(ArrancadorRemoto * uartConnector, char * string);

#endif /* PROGRAMS_TP_MOTO_INC_ARRANCADORREMOTO_H_ */
