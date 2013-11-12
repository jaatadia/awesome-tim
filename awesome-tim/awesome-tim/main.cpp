#include "MEstados.h"
#include "MEstadosCliente.h"
#include "ErrorLogHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "Constantes.h"

#include "Contenedor.h"
#include "GeneradorYaml.h"

#include "Server.h"
#include "Client.h"

#define RUTA_DEFAULT_IN "../yaml/archivoDefault.yml"
#define RUTA_DEFAULT_OUT "../yaml/nuevoJuego.yml"

#define OPC_ERROR -1
#define OPC_IMPRIMIR_AYUDA 0
#define OPC_IMPRIMIR_AYUDA_AVANZADA 1
#define OPC_IMPRIMIR_VERSION 2
#define OPC_JUEGO 3
#define OPC_CORRER_TEST 4

bool es_igual(char* comando,char* com_largo,char* com_corto){
	return ((strcmp(comando,com_largo) == 0) || (strcmp(comando,com_corto)==0));
}

bool es_erroneo(char* comando){

	bool ayuda = (es_igual(comando,"--help","-h") || es_igual(comando,"--complexHelp","-c"));
	bool version = (es_igual(comando,"--version","-v"));
	bool juego = (es_igual(comando,"--save","-s") || es_igual(comando,"--load","-l"));
	bool test = (es_igual(comando,"--test","-t"));
	bool Ip = (es_igual(comando,"--IP","-i"));
	bool erroneo = ((!ayuda) && (!version) && (!test) && (!juego) && (!Ip));
	return erroneo;
}

int obtener_parametros(int argc,char* argv[],char** rutaIn, char** rutaOut,char** IP){

	int opcion = OPC_JUEGO;//opcion default

	*rutaIn = RUTA_DEFAULT_IN; //directorio default
	*rutaOut = RUTA_DEFAULT_OUT; //directorio default

	int i = 1;
	//mientras haya opciones las lee y las procesa
	while (i < argc){

		if(es_igual(argv[i],"--help","-h"))
			return OPC_IMPRIMIR_AYUDA;
		
		if(es_igual(argv[i],"--complexHelp","-c"))
			return OPC_IMPRIMIR_AYUDA_AVANZADA;

		if(es_igual(argv[i],"--version","-v"))
			return OPC_IMPRIMIR_VERSION;

		if(es_igual(argv[i],"--load","-l")){
			opcion = OPC_JUEGO;
			if(i >= argc){
				ErrorLogHandler::addError("main","Se especifico que se desea cargar un archivo pero no la ruta. Se usan valores default");
				opcion = OPC_JUEGO;
				i++;
				continue;
			}
			*rutaIn = argv[i+1];
			if(strcmp(*rutaOut,RUTA_DEFAULT_OUT) == 0)
				*rutaOut = argv[i+1];
			i = i+2;
			continue;
		}

		if(es_igual(argv[i],"--save","-s")){
			opcion = OPC_JUEGO;
			if(i >= argc){
				ErrorLogHandler::addError("main","Se especifico que se desea guardar un archivo pero no la ruta. Se usan valores default");
				opcion = OPC_JUEGO;
				i++;
				continue;
			}
			*rutaOut = argv[i+1];
			i = i+2;
			continue;
		}

		if(es_igual(argv[i],"--IP","-i")){
			opcion = OPC_JUEGO;
			if(i >= argc){
				ErrorLogHandler::addError("main","Se especifico que se desea conectar a una ip pero no se especifico a cual");
				opcion = OPC_JUEGO;
				i++;
				continue;
			}
			*IP = argv[i+1];
			i = i+2;
			continue;
		}

		if(es_igual(argv[i],"--test","-t"))
			return OPC_CORRER_TEST;

		if(es_erroneo(argv[i]))
			return OPC_ERROR;

		i++; //Por las dudas, para que no me haga un loop infinito :P
	}

	return opcion;
}

//Imprimir Ayuda
void imprimir_ayuda(){
	fprintf(stdout,"OPCIONES \n");
	fprintf(stdout,"-h	--help          Imprime en pantalla informacion de Ayuda. \n");
	fprintf(stdout,"-c	--complexHelp   Imprime en pantalla informacion de Ayuda con comandos especiales. \n");
	fprintf(stdout,"-v	--version	    Imprime en pantalla la version del juego. \n");
	fprintf(stdout,"-l	--load          Especifica la ruta para cargar un juego desde un archivo. \n");
	fprintf(stdout,"-s	--save	        Especifica la ruta para guardar el juego. Por default es la misma que la de carga. \n");
}

//Imprime ayuda avanzada
void imprimir_ayuda_avanzada(){
	imprimir_ayuda();
	fprintf(stdout,"Comandos Avanzados: \n");
	fprintf(stdout,"-t	--test	        Corre tests de prueba. \n");
}

//imprime la version del programa al stdout
void imprimir_version(){
	fprintf(stdout,"Trabajo Practico - Taller de Programacion I \n");
	fprintf(stdout,"The Incredible Machine \n Version 1.0 \n");
	fprintf(stdout,"Segundo Cuatrimestre - 2013 \n \n");
	fprintf(stdout,"Grupo: \n");
	fprintf(stdout," ATADIA, Javier Alejandro (93223) \n");
	fprintf(stdout," FULD, Juan Federico (93395) \n");
	fprintf(stdout," WOITES, Jennifer Andrea (93274) \n");
	fprintf(stdout," ALVAREZ ETCHEVERRY, Florencia (93408) \n");
	fprintf(stdout," MANZANO, Matias Sebastian (83425) \n \n");
}


void test(void){
	GeneradorYaml::pruebayaml();
	Contenedor::pruebaContenedor();
}
/*
void iniciarClienteOServer(){

#ifdef ES_SERVIDOR
Server server();
server.run();
#else
//lo creo y dentro hace toda la inicializacion necesaria
//y se pone a correr el programa.
ClientTIM cliente;
#endif
}
*/
#include<sys/timeb.h>

//Corre el programa del juego
void jugar(char* rutaIn, char* rutaOut,char* IP){
	MEstados juego = MEstados(rutaIn,rutaOut);
	//MEstadosCliente juego = MEstadosCliente(1);

#ifdef SERVER_MODE
	if (IP==NULL){
		std::cout << "Initializing game in: SERVER MODE" << std::endl;
		Server * server = new Server(&juego);
	}else{
		std::cout << "Initializing game in: CLIENT MODE" << std::endl;
		Client * client = new Client(&juego,IP);
	}
#else
	std::cout << "Initializing game in: CLIENT MODE" << std::endl;
	Client * client = new Client(&juego,IP);
#endif // SERVER_MODE

	double tiempoTardado = 0;
	double tiempoExtra = 0;
	double frames = 0;
	double tiempo = 0;
	double cant = 0;

	struct timeb tInicial, tFinal;

	while (juego.isRunning()&&(!juego.huboFallos())){
		
		if(tiempo>=1000){
			std::cout<<"FPS: "<< frames*1000/tiempo << " FramesSkipped: "<<cant<<"\n";
			tiempo = 0;
			frames = 0;
			cant=0;
		}
		
		frames++;

   		ftime(&tInicial);

		bool aux = juego.onEvent();
		juego.onLoop();
		juego.onRender();
		
		if (aux){
			continue;
		}

		ftime(&tFinal);
		
		tiempoTardado = (1000.0 *tFinal.time + tFinal.millitm) - (1000.0 *tInicial.time + tInicial.millitm);

		tiempoExtra += FRAME_FRECUENCY - tiempoTardado;
		tiempoExtra = FRAME_FRECUENCY - tiempoTardado;

		tiempo += tiempoTardado;

		if(tiempoExtra>=0){
			juego.esperar(tiempoExtra);
			tiempo+=tiempoExtra;;
			tiempoExtra=0;
		}else{
			int ciclos = 0;
			while(tiempoExtra<0){
				ciclos ++;
				cant++;
				
				ftime(&tInicial);
				juego.onEvent();
				juego.onLoop();
				ftime(&tFinal);

				tiempoTardado = (1000.0 *tFinal.time + tFinal.millitm) - (1000.0 *tInicial.time + tInicial.millitm);
				tiempo += tiempoTardado;
				tiempoExtra += (FRAME_FRECUENCY /*-tiempoTardado*/);

				if (ciclos>5) break;
			}

		}
		

	}
}

int main (int argc, char** argv){

	int opcion; //guarda el modo del programa

	char* rutaIn = NULL;
	char* rutaOut = NULL;
	char* IP = NULL;
	bool server = true;

	opcion = obtener_parametros(argc,argv,&rutaIn, &rutaOut,&IP);

	if (!rutaIn || !rutaOut){
		ErrorLogHandler::addError("main","No es posible cargar rutas de archivos. Fin del programa.");			
		return 1;
	}

	switch (opcion){
		case OPC_JUEGO:
			//compilo como cliente o como servidor
			//en sus initThread va el jugar()
			jugar(rutaIn, rutaOut,IP);
			//iniciarClienteOServer();
			break;
		case OPC_IMPRIMIR_AYUDA:
			imprimir_ayuda();
			break;
		case OPC_IMPRIMIR_AYUDA_AVANZADA:
			imprimir_ayuda_avanzada();
			break;
		case OPC_IMPRIMIR_VERSION:
			imprimir_version();
			break;
		case OPC_CORRER_TEST:
			test();
			break;
		case OPC_ERROR:
			ErrorLogHandler::addError("main","Parametros invalidos. Fin del programa.");			
			fprintf(stderr,"Parametros no validos. Intente nuevamente \n");
			break;
	}

	return 0;
}
