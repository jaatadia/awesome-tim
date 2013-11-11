#pragma once

#include "SDL_ttf.h"

class Fuente
{
private:
	static bool initialized;

public:
	static void initialize(){
		TTF_Init();
		initialized = true;
	}
	
	static TTF_Font* openFont(const char* dit,int alto){
		if(!initialized){
			initialize();
		}
		return TTF_OpenFont("../images/font.ttf", alto);
	}
	static void closeFont(TTF_Font* fuente){
		TTF_CloseFont(fuente);
	}
	static void end(){
		if(initialized){
			TTF_Quit();
		}
	}
};
