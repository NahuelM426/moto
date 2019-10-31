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

struct Moto;

enum EstadoMotoEletricidad{
	NotengoEletricidad,TengoElectricidad
};
enum EstadoMoto{
	PararArranque,DarArranque
};
enum Tiempo{
	Detener,Iniciar
};
typedef void (*MotoChangeObserver)(void * , struct Moto * );


typedef struct moto{
	int arrancado;
	int electricidad;
	int tiempo;
	MotoChangeObserver observerFunction;
	delay_t tickDelStart;
	void * observerObject;
}Moto;

void MotoIniciar(Moto * mt,unsigned char arranque,unsigned char electricidad);

void controladorEncedido(Moto * bn);
void Moto_setObserver(Moto * model, void * observerObject, MotoChangeObserver observerFunction );
void appModel_enable(Moto * model);
void appModel_disable(Moto * model);
void appModel_toggle(Moto * model);



#endif /* PROGRAMS_TP_MOTO_INC_MOTO_H_ */
