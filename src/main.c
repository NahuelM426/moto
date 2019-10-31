#include <sapi.h>        // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232


#include "Button.h"
#include "pulsador.h"
#include "../inc/Moto.h"
#include "MotoRender.h"
#include "ArrancadorRemoto.h"

/*==================[funcion principal]======================================*/

//Este es un handler del boton


void moto_comenzarArranque(void * p){
	((Moto *)p)->arrancado = PararArranque;
	((Moto *)p)->electricidad =TengoElectricidad;
	((Moto *)p)->tiempo =Detener;

}

void moto_pararArranque(void * p){
	((Moto *)p)->arrancado = DarArranque;
}
void moto_cortarCircuito(void * p){
	((Moto *)p)->electricidad=NotengoEletricidad;
}
void moto_Opt(void * p){
	((Moto *)p)->arrancado = DarArranque;
}


void bluetoothCommandReceived(void * Motopointer, uint8_t byte) {
	if(byte == 'a') {
		moto_comenzarArranque((Moto *)Motopointer);
		Moto * model = (Moto *)Motopointer;
		delayInit(&model->tickDelStart,3000);
		model->tiempo = Iniciar;
	}
	if(byte == 'f') {
		moto_pararArranque((Moto *)Motopointer);
	}
	if(byte == 'p') {
		moto_cortarCircuito((Moto *)Motopointer);
		moto_pararArranque((Moto *)Motopointer);
	}
}
//void modelChanged(void * uartConnectorPointer, Moto * model) {
//	ArrancadorRemoto * uartConnector = (ArrancadorRemoto *) uartConnectorPointer;
//	if(motoArrancado(model)) {
//		uartConnector_send(uartConnector, "LED_ON");
//	}
//	else{
//		uartConnector_send(uartConnector, "LED_OFF");
//	}
//}


// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_232 para conectar al modulo bluetooth
   //uartWriteString( UART_PC, "UART_BLUETOOTH para modulo Bluetooth configurada.\r\n" );
   //uartConfig( UART_BLUETOOTH, 9600 );

   //uint8_t data = 0;

   gpioInit(GPIO0,GPIO_OUTPUT);
   gpioInit(GPIO2,GPIO_OUTPUT);

   Button button;
   Pulsador pulsador;
   MotoRender controladorDeSalida;
   Moto moto;
   ArrancadorRemoto uartConnector;


   MotoIniciar(&moto,DarArranque,NotengoEletricidad);

   iniciarMotoRender(&controladorDeSalida,GPIO0,LED2, &moto);

   inciarPulsador(&pulsador,TEC2,moto_comenzarArranque,moto_pararArranque, &moto);

   ArrancadorRemoto_initBt(&uartConnector, &moto, bluetoothCommandReceived,moto_Opt);

   //Moto_setObserver(&moto, (void *)&uartConnector, modelChanged);

   button_init(&button, TEC1,moto_cortarCircuito,&moto);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
	   button_update(&button);
	   controladorBoton(&pulsador);
	   uartConnector_update(&uartConnector);
	   controladorMotoRender(&controladorDeSalida);
	   delay(1);
   }

   return 0;
}


