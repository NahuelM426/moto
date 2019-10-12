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



enum EstadoMotoEletricidad{
	NotengoEletricidad,TengoElectricidad
};
enum EstadoMoto{
	PararArranque,DarArranque
};


typedef struct moto{
	int arrancado;
	int electricidad;
}Moto;

void MotoIniciar(Moto * mt,unsigned char arranque,unsigned char electricidad);

void controladorEncedido(Moto * bn);



#endif /* PROGRAMS_TP_MOTO_INC_MOTO_H_ */
