#include "Imagen.h"
#include "ErrorLogHandler.h"
#include "SdlSurfaceManager.h"
#include "SDL_ttf.h"

//crea una imagen sin superficie

//nueva superficie de las dimensiones pasadas
Imagen::Imagen(int ancho,int alto){
	if(ancho == 0) ancho = 10;
	if(alto == 0) alto = 10;
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

#include "Fuente.h"

//crea una imagen a partir del texto pasado
Imagen::Imagen(const char* texto,int alto,int r,int g,int b){
	
	try{
		TTF_Font* font = Fuente::openFont("../images/font.ttf", alto);
		if(font ==NULL){
			ErrorLogHandler::addError(IMAGEN_TAG,TTF_GetError());
			superficie = SdlSurfaceManager::crearSup();
			this->fallar();
		}else{
			SDL_Color text_color = {r,g,b};
			this->superficie =  TTF_RenderText_Solid(font, texto,text_color);
			Fuente::closeFont(font);
		}
	}catch(...){
	}
}

//destructor que libera la memoria de la superfice
Imagen::~Imagen(void)
{
	if(superficie!=NULL){
		if(superficie->map!=NULL){
			try{
				SDL_FreeSurface(superficie);
			}catch(...){
			}
		}
	}
}

//devuelve el alto de la superficie
int Imagen::getAlto(){
	if(superficie!=NULL){
		return superficie->clip_rect.h;
	}else{
		return 10;
	}
}
//devuelve el ancho de la superficie
int Imagen::getAncho(){
	if(superficie!=NULL){
		return superficie->clip_rect.w;
	}else{
		return 10;
	}
}

//transparenta toda la imagen a lo pedido (0 completamente transparente 255 completamente opaco)
void Imagen::setTransparency(Uint8 alpha){
	SDL_SetSurfaceAlphaMod(superficie,alpha);
}


//devuelve una copia rotada de la imagen
Imagen* Imagen::rotarImagen(double ang){
	if((this==NULL)||(superficie==NULL)) return NULL;
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

void Imagen::pintar(int r,int g,int b,int a){
	SdlSurfaceManager::pintar(superficie,r,g,b,a);
}

void Imagen::colorear(int r,int g,int b,int a){
	Uint32 color = SDL_MapRGBA(superficie->format,r,g,b,a);
	SdlSurfaceManager::dibujarCuadrado(superficie,0,0,superficie->w,superficie->h,color);
}

Uint32 Imagen::atransparentar(){
	Uint32 color = SDL_MapRGBA(superficie->format,255,0,255,255);
	SdlSurfaceManager::dibujarCuadrado(superficie,0,0,superficie->w,superficie->h,color);
	return color;
}

void Imagen::atransparentar(Uint32 col1){
	Uint32 col2 = SDL_MapRGBA(superficie->format,0,0,0,0);
	SdlSurfaceManager::replace(superficie,col1,col2);
}