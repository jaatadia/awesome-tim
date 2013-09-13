#include "Ventana.h"
#include "Constantes.h"
#include "ErrorLogHandler.h"

//crea la ventana
Ventana::Ventana(void)
{
	win = NULL;
	win = SDL_CreateWindow(NOMBRE_JUEGO,100,100,ANCHO_PANTALLA,ALTO_PANTALLA,SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN);
	if(win == NULL){
		ErrorLogHandler::addError(VENTANA_TAG,SDL_GetError());
		fallar();
	}else{
		SDL_SetWindowMinimumSize(win,150,150);
		ren = NULL;
		ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(ren == NULL){
			ErrorLogHandler::addError(VENTANA_TAG,SDL_GetError());
			SDL_DestroyWindow(win);
			fallar();
		}
	}
}

//destruye la ventana
Ventana::~Ventana(void)
{
	if(!huboFallos()){
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
	}
}

//dibuja en la ventana la superficie pasada
void Ventana::dibujar(Superficie* sup){
	
	SDL_Texture* tex = NULL;
	tex = SDL_CreateTextureFromSurface(ren,sup->superficie);
	if(tex!=NULL){
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren,tex,NULL,NULL);
		SDL_RenderPresent(ren);
		SDL_DestroyTexture(tex);
	}else{
		ErrorLogHandler::addError(VENTANA_TAG,SDL_GetError());
	}
}

//devuelve el ID de la ventana
int Ventana::getID(){
	return SDL_GetWindowID(win);
}

int Ventana::getAncho(){
	int ancho;
	int alto;
	SDL_GetWindowSize(win,&ancho,&alto);
	std::cout << "ancho: "<<ancho<<" alto: "<<alto<<"\n";
	return ancho;
}

int Ventana::getAlto(){
	int ancho;
	int alto;
	SDL_GetWindowSize(win,&ancho,&alto);
	return alto;
}