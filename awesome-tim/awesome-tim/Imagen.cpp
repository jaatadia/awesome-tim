#include "Imagen.h"
#include "ErrorLogHandler.h"
#include "SdlSurfaceManager.h"
#include "SDL_ttf.h"

//crea una imagen sin superficie

//nueva superficie de las dimensiones pasadas
Imagen::Imagen(int ancho,int alto){
	superficie = SdlSurfaceManager::crearSup(ancho,alto);
	Uint32 negro = SDL_MapRGBA(superficie->format,0,0,0,255);
	SdlSurfaceManager::pintarSup(superficie,negro);
}

//dibuja en las pocisiones x/yDestino el rectOrigen de sup (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
void Imagen::dibujarImagen(Imagen* img,Rectangulo* rectOrigen,int xDestino,int yDestino){
	if((this!=NULL)&&(img!=NULL))
		SdlSurfaceManager::blitSurfaces(img->superficie,this->superficie,rectOrigen,xDestino,yDestino);
}


Imagen::Imagen(bool flag){
	superficie = NULL;
}

//crea una imagen sin superficie
Imagen::Imagen(){
	superficie = SdlSurfaceManager::crearSup();
}

//crea una imagen a partir del directorio pasado en caso de no lograrse se pone como fallado
Imagen::Imagen(const char* file)
{
	superficie = SdlSurfaceManager::cargarImagen(file);
	if (SdlSurfaceManager::huboFallas()){
		this->fallar();
		superficie = SdlSurfaceManager::crearSup();
	}
}

//crea una imagen a partir del texto pasado
Imagen::Imagen(const char* texto,int alto,int r,int g,int b){
	
	try{
		TTF_Init();
		TTF_Font* font = TTF_OpenFont("../images/font.ttf", alto);
		if(font ==NULL){
			ErrorLogHandler::addError(IMAGEN_TAG,TTF_GetError());
			superficie = SdlSurfaceManager::crearSup();
			this->fallar();
		}else{
			SDL_Color text_color = {r,g,b};
			this->superficie =  TTF_RenderText_Solid(font, texto,text_color);
			TTF_CloseFont(font);
		}
		TTF_Quit();
	}catch(...){
	}
}

//destructor que libera la memoria de la superfice
Imagen::~Imagen(void)
{
	if(superficie!=NULL){
		if(superficie->map!=NULL){
			SDL_FreeSurface(superficie);
		}
	}
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
	
	Imagen* img = new Imagen(false);
	img->superficie = SdlSurfaceManager::rotar(superficie,ang);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}

//devuelve una copia rotada de la imagen conservando las dimensiones
Imagen* Imagen::rotarCuadradoImagen(double ang){
	
	Imagen* img = new Imagen(false);
	img->superficie = SdlSurfaceManager::rotarLock(superficie,ang);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}

//devuelve una copia resizeada de la imagen
Imagen* Imagen::scaleImagen(int pixelesAncho,int pixelesAlto){
	Imagen* img = new Imagen(false);
	img->superficie = SdlSurfaceManager::scale(this->superficie,pixelesAncho,pixelesAlto);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}

//rota y zoomea la img
Imagen* Imagen::rotarZoom(int ancho,int alto,double angulo){
	Imagen* img = new Imagen(false);
	img->superficie = SdlSurfaceManager::rotarZoom2(this->superficie,ancho,alto,angulo);
	if(SdlSurfaceManager::huboFallas()){
		delete img;
		img = NULL;
	}
	return img;
}

void Imagen::pintarRojo(){
	SdlSurfaceManager::pintar(superficie,255,0,0,150);
}