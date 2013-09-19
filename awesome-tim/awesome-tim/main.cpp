#include "Juego.h"
#include "ErrorLogHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "Constantes.h"

//Inclusion de Test
#include "Test_Cuadrado.h"
#include "Contenedor.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"

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
	bool erroneo = ((!ayuda) && (!version) && (!test) && (!juego));
	return erroneo;
}

int obtener_parametros(int argc,char* argv[],char** rutaIn, char** rutaOut){

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
	fprintf(stdout,"The Incredible Machine \n");
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
	CargadorYaml::pruebaCargador();
	Test_Cuadrado::prueba_cuadrado();
	Contenedor::pruebaContenedor();
}

//Corre el programa del juego
void jugar(char* rutaIn, char* rutaOut){
	Juego juego = Juego(rutaIn,rutaOut);//Falta agregarle al juego la rutaOut
	
	while (juego.isRunning()&&(!juego.huboFallos())){
		

		clock_t tInicial = clock();
		
		juego.onEvent();
		juego.onLoop();
		juego.onRender();
		
		clock_t tFinal = clock();
		double tiempoTardado = ((double)(tFinal - tInicial))*1000/CLOCKS_PER_SEC;
		double tiempoExtra = FRAME_FRECUENCY - tiempoTardado;

		if(tiempoExtra>=0) juego.esperar(tiempoExtra);
		else{
			while(tiempoExtra<0){
				juego.onEvent();
				juego.onLoop();
				tiempoExtra += FRAME_FRECUENCY;
			}

		}
		

	}
}

int main (int argc, char** argv){

	int opcion; //guarda el modo del programa

	char* rutaIn = NULL;
	char* rutaOut = NULL;

	opcion = obtener_parametros(argc,argv,&rutaIn, &rutaOut);

	if (!rutaIn || !rutaOut){
		ErrorLogHandler::addError("main","No es posible cargar rutas de archivos. Fin del programa.");			
		return 1;
	}

	switch (opcion){
		case OPC_JUEGO:
			jugar(rutaIn, rutaOut);
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
