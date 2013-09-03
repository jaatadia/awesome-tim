#include "ManejadorEventos.h"

ManejadorEventos::ManejadorEventos(void)
{
}

ManejadorEventos::~ManejadorEventos(void)
{
}

bool ManejadorEventos::onEvent(Juego* juego){

//SDL_Event* evento;

//while (SDL_PollEvent(evento) != NULL){
//
//	switch(evento->type){
//		case SDL_WINDOWEVENT:
//		{
//			if (evento->window.windowID == /*id ventana principal*/){ // hacer else en caso de un pop-up, mejor seria hacer un ciclo por todas las ventanas
//				switch (evento->window.event){
//					case SDL_WINDOWEVENT_ENTER:
//
//					case SDL_WINDOWEVENT_LEAVE:
//					//las 2 de mouse dentro o fuera
//					//ahora las de teclado
//					case SDL_WINDOWEVENT_FOCUS_GAINED:
//
//					case SDL_WINDOWEVENT_FOCUS_LOST:
//
//					case SDL_WINDOWEVENT_CLOSE://cerrar juego, es decir meter evento de quit
//
//					case SDL_WINDOWEVENT_SIZE_CHANGED://guardar tamanio original
//
//					case SDL_WINDOWEVENT_RESIZED://calcular nuevo ratio logico/real
//				}
//
//			}
//			break;
//		}
//
//		case SDL_KEYDOWN || SDL_KEYUP:
//		{
//
//			break;
//		}
//		case SDL_TEXTINPUT:
//		{
//
//			break;
//		}
//		case SDL_MOUSEMOTION:
//		{
//
//			break;
//		}
//		case SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP:
//		{
//			std::cout<<evento->button.x<<endl;
//			std::cout<<evento->button.y<<endl;
//			break;
//		}
//		case SDL_MOUSEWHEEL:
//		{
//
//			break;
//		}
//		case SDL_QUIT: //salir del juego
//		{
//			
//			break;
//		}
//
//	}

return true;
}


//SDL_WaitEvent para la pausa