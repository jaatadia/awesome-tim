#include "Ventana.h"
#include "Constantes.h"
#include "ErrorLogHandler.h"
#include "SdlSurfaceManager.h"

//crea la ventana
Ventana::Ventana(void)
{
	icon = SdlSurfaceManager::cargarImagen("../images/Bowling.png");
	int res = SDL_CreateWindowAndRenderer(ANCHO_PANTALLA,ALTO_PANTALLA,SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN,&win,&ren);
	if(res == -1){
		ErrorLogHandler::addError(VENTANA_TAG,SDL_GetError());
		fallar();
	}else{
		SDL_SetWindowTitle(win,NOMBRE_JUEGO);
		SDL_SetWindowMinimumSize(win,150,150);
		SDL_SetWindowPosition(win,10,10);
		SDL_SetWindowIcon(win,icon);
	}
}

//destruye la ventana
Ventana::~Ventana(void)
{
	try{
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_FreeSurface(icon);
	}catch(...){
	}
}

//dibuja en la ventana la superficie pasada
void Ventana::dibujar(Superficie* sup){
	
	if(sup==NULL) return;
	if (sup->superficie == NULL) return;

	try{
		SDL_Texture* tex = NULL;
		tex = SDL_CreateTextureFromSurface(ren,sup->superficie);
		if(tex!=NULL){
			SDL_RenderCopy(ren,tex,NULL,NULL);
			SDL_DestroyTexture(tex);
			SDL_RenderPresent(ren);
		}else{
			ErrorLogHandler::addError(VENTANA_TAG,SDL_GetError());
		}
	}catch(...){
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

void Ventana::resize(int ancho,int alto){
	SDL_SetWindowSize(win,ancho,alto);
}