#include "ManejadorEventos.h"

EscalasDeEjes* ManejadorEventos::escalasDeEjes=NULL;

ManejadorEventos::ManejadorEventos(void)
{
}

ManejadorEventos::~ManejadorEventos(void)
{
}

bool ManejadorEventos::categorizarEvento(SDL_Event evento){

switch(evento.type){
	case SDL_WINDOWEVENT:
	{
		actuarVentana(evento.window.windowID,evento.window,this->escalasDeEjes);//tipo escala

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

		break;
	}
	case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
	{
		std::cout<<evento.button.x<<std::endl;
		std::cout<<evento.button.y<<std::endl;
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

return true;
}

void ManejadorEventos::actuarVentana(Uint32 IDventana,SDL_WindowEvent evento,EscalasDeEjes* escalas){
//esto va a ir en la redefinicion
	
//if (evento->window.windowID == ventana->getID()){
//	switch (evento->window.event){
//		case SDL_WINDOWEVENT_ENTER:
//			break;
//		case SDL_WINDOWEVENT_LEAVE:
//		//las 2 de mouse dentro o fuera
//		//ahora las de teclado
//			break;
//		case SDL_WINDOWEVENT_FOCUS_GAINED:
//			break;
//		case SDL_WINDOWEVENT_FOCUS_LOST:
//			break;
//		case SDL_WINDOWEVENT_CLOSE://cerrar juego, es decir meter evento de quit
//			break;
//		case SDL_WINDOWEVENT_SIZE_CHANGED://guardar tamanio original o no...verificar cuentas
//			break;
//		case SDL_WINDOWEVENT_RESIZED://calcular nuevo ratio logico/real
//			break;
//	}
}

void ManejadorEventos::quit(){
}

//SDL_WaitEvent para la pausa?