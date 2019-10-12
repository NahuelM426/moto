#include <sapi.h>        // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232


#include "Button.h"
#include "pulsador.h"
#include "../inc/Moto.h"
#include "MotoRender.h"
#include "UartConnector.h"

/*==================[funcion principal]======================================*/

//Este es un handler del boton


void moto_comenzarArranque(void * p){
	((Moto *)p)->arrancado = PararArranque;
	((Moto *)p)->electricidad =TengoElectricidad;
}

void moto_pararArranque(void * p){
	((Moto *)p)->arrancado = DarArranque;
}
void moto_cortarCircuito(void * p){
	((Moto *)p)->electricidad=NotengoEletricidad;
}








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


   MotoIniciar(&moto,DarArranque,NotengoEletricidad);

   iniciarMotoRender(&controladorDeSalida,GPIO0,LED2, &moto);

   inciarPulsador(&pulsador,TEC2,moto_comenzarArranque,moto_pararArranque, &moto);

   button_init(&button, TEC1,moto_cortarCircuito,&moto);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
	   button_update(&button);
	   controladorBoton(&pulsador);
	   controladorMotoRender(&controladorDeSalida);
	   delay(1);
   }

   return 0;
}


