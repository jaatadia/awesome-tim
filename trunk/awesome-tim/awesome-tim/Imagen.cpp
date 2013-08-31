#include "Imagen.h"
#include "ErrorLogHandler.h"
#include "SdlSurfaceManager.h"
#include "SDL_ttf.h"

//crea una imagen sin superficie
Imagen::Imagen(){
	superficie = NULL;
}

//crea una imagen a partir del directorio pasado en caso de no lograrse se pone como fallado
Imagen::Imagen(const char* file)
{
	superficie = SdlSurfaceManager::cargarImagen(file);
	if (SdlSurfaceManager::huboFallas()){
		fallar();
	}
}

//crea una imagen a partir del texto pasado
Imagen::Imagen(const char* texto,int alto,int r,int g,int b){
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("../images/font.ttf", alto);
	if(font ==NULL){
		ErrorLogHandler::addError(IMAGEN_TAG,TTF_GetError());
	}else{
		SDL_Color text_color = {r,g,b};
		this->superficie =  TTF_RenderText_Solid(font, texto,text_color);
		TTF_CloseFont(font);
	}
	TTF_Quit();
}

//destructor que libera la memoria de la superfice
Imagen::~Imagen(void)
{
	SDL_FreeSurface(superficie);
}

//devuelve el alto de la superficie
int Imagen::getAlto(){
	return superficie->clip_rect.h;
}
//devuelve el ancho de la superficie
int Imagen::getAncho(){
	return superficie->clip_rect.w;
}

//transparenta toda la imagen a lo pedido (0 completamente transparente 255 completamente opaco)
void Imagen::setTransparency(Uint8 alpha){
	SDL_SetSurfaceAlphaMod(superficie,alpha);
}


//devuelve una copia rotada de la imagen
Imagen* Imagen::rotarImagen(double ang){
	
	Imagen* img = new Imagen();
	img->superficie = SdlSurfaceManager::rotar(superficie,ang);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}

//devuelve una copia rotada de la imagen conservando las dimensiones
Imagen* Imagen::rotarCuadradoImagen(double ang){
	
	Imagen* img = new Imagen();
	img->superficie = SdlSurfaceManager::rotarLock(superficie,ang);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}

//devuelve una copia resizeada de la imagen
Imagen* Imagen::scaleImagen(int pixelesAncho,int pixelesAlto){
	Imagen* img = new Imagen();
	img->superficie = SdlSurfaceManager::scale(this->superficie,pixelesAncho,pixelesAlto);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}