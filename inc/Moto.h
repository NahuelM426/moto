/*
 * PrenderMoto.h
 *
 *  Created on: 7 oct. 2019
 *      Author: nahuel
 */

#ifndef PROGRAMS_TP_MOTO_INC_MOTO_H_
#define PROGRAMS_TP_MOTO_INC_MOTO_H_
#include <sapi.h>
#include <sapi_gpio.h>

struct moto;

enum EstadoMotoEletricidad{
	NotengoEletricidad,TengoElectricidad
};
enum EstadoMoto{
	PararArranque,DarArranque
};
enum Tiempo{
	Detener,Iniciar
};
typedef void (*MotoChangeObserver)(void * , struct moto * );


typedef struct moto{
	int arrancado;
	unsigned char electricidad;
	int tiempo;
	MotoChangeObserver observerFunction;
	delay_t tickDelStart;
	void * observerObject;
}Moto;

void MotoIniciar(Moto * mt,unsigned char arranque,unsigned char electricidad);

void controladorEncedido(Moto * bn);
void Moto_setObserver(Moto * model, void * observerObject, MotoChangeObserver observerFunction );
void Moto_enable(Moto * model);
void Moto_disable(Moto * model);
unsigned char motoElectricidad(Moto* model);

#endif /* PROGRAMS_TP_MOTO_INC_MOTO_H_ */
