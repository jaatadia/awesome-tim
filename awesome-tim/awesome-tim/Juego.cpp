#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "ManejadorYaml.h"
#include "Cuadrado.h"

Juego::Juego(const char *file){
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(JUEGO_TAG,SDL_GetError());
		fallar();
	}
	
	this->file = file;
	running = true;

	ventana = new Ventana();
	superficie = new Superficie(ANCHO_PANTALLA,ALTO_PANTALLA);
	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO);
	botonera = new Botonera(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	comandos = new Comandos(ANCHO_COMANDOS,ALTO_COMANDOS);
	escalas = new EscalasDeEjes();
	figuraEnAire=NULL;

//	cargar();

	if(superficie->huboFallos()||ventana->huboFallos()){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(JUEGO_TAG,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}

/******************para test de arrastrar figura por el terreno**********************/

	Contenedor::putMultimedia("../images/cuadrado.jpg",new Imagen("../images/Cuadrado.png"));
	Figura* fig = new Figura("../images/cuadrado.jpg",new Cuadrado(20,20,50,50,0));
	terreno->agregarFigura(fig);
}

bool Juego::cargar(){
	ManejadorYaml::cargarJuego(file,botonera,terreno);
	return true;
}

bool Juego::guardar(){
	ManejadorYaml::guardarJuego(file,botonera,terreno);
	return true;
}

Juego::~Juego(){
	delete ventana;
	delete superficie;
	delete terreno;
	delete botonera;
	delete comandos;
	delete escalas;
	if(figuraEnAire!=NULL)delete figuraEnAire;
	SDL_Quit();
	ErrorLogHandler::closeLog();
}


bool Juego::isRunning(){
	return running;
}

//dibuja en pantalla
void Juego:: onRender(){
	
	
	if(terreno->huboCambios()){
		superficie->dibujarSupreficie(terreno->getImpresion(escalas),NULL,X_TERRENO,Y_TERRENO);
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,X_BOTONERA,Y_BOTONERA);
	}
	
	if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(),NULL,X_COMANDOS,Y_COMANDOS);
	}

	ventana->dibujar(superficie);
	
}

void Juego:: onLoop(){
}



//manejo de eventos
void Juego:: onEvent(){

//SDL_Event evento;

//int hayEvento = SDL_PollEvent(&evento);

//while ( hayEvento != 0)
//	this->categorizarEvento(evento);
SDL_Event evento;
while(SDL_PollEvent(&evento)){
	switch(evento.type){
		case SDL_WINDOWEVENT:
		{
			actuarVentana(evento.window.windowID,evento.window,this->escalas);//tipo escala

			//actualiza las escalas si fue un resize
			break;
		}
		case SDL_KEYDOWN: case SDL_KEYUP:
		{

			break;
		}
		case SDL_TEXTINPUT:
		{

			break;
		}
		case SDL_MOUSEMOTION:
		{
			//convertir a unidades logicas
			double posClickX, posClickY;

			posClickX = escalas->getCantidadUnidadesLogicasX(evento.motion.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.motion.y);

			//averiguar si esta en terreno, botonera o otro lado

				//Aca el juego conoce todas las posiciones o son constantes o ...?

			//verificar que el boton izq este apretado o no deberia pasar nada

			if (evento.motion.state == SDL_BUTTON_LMASK){				
				double cantMovX = escalas->getCantidadUnidadesLogicasX(evento.motion.xrel);
				double cantMovY = escalas->getCantidadUnidadesLogicasY(evento.motion.yrel);

//				terreno->arrastrarFigura(posClickX - X_TERRENO, posClickY - Y_TERRENO, cantMovX, cantMovY);
				terreno->arrastrarFigura(posClickX , posClickY , cantMovX, cantMovY);
			}

			break;
		}
		case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
		{
			//verificar que boton es el apretado

			/*std::cout<<evento.button.x<<std::endl;
			std::cout<<evento.button.y<<std::endl;*/
			break;
		}
		case SDL_MOUSEWHEEL:
		{

			break;
		}
		case SDL_QUIT: //salir del juego
		{
			quit();
			break;
		}
	}
}

}


void Juego::quit(){
	running = false;
}

void Juego::actuarVentana(Uint32 IDventana,SDL_WindowEvent evento,EscalasDeEjes* escalas){

	if(evento.event == SDL_WINDOWEVENT_CLOSE){
		if (evento.windowID == ventana->getID())
			running = false;
	}


//SDL_WINDOWEVENT_SHOWN este es el 1

//Uint32 myEventType = SDL_RegisterEvents(1);
//if (myEventType != ((Uint32)-1)) {
//    SDL_Event evento2;
//    SDL_zero(evento2);
//    evento2.type = SDL_QUIT;
//    evento2.user.code = 1;
//    evento2.user.data1 = 0;
//    evento2.user.data2 = 0;
//	SDL_PushEvent(&evento2);
//}

	// este es el evento 12 SDL_WINDOWEVENT_FOCUS_GAINED
}