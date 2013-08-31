#include "Superficie.h"
#include "ErrorLogHandler.h"
#include "SdlSurfaceManager.h"

//nueva superficie segun las constantes ANCHO y ALTO
Superficie::Superficie(){
	superficie = NULL;
}

//nueva superficie de las dimensiones pasadas
Superficie::Superficie(int ancho,int alto){
	superficie = SdlSurfaceManager::crearSup(ancho,alto);
	if(SdlSurfaceManager::huboFallas())	fallar();
}

//destructor de la superficie
Superficie::~Superficie(void){
	if(!huboFallos()) SDL_FreeSurface(superficie);
}


//repinta el fondo de la imagen
void Superficie::restore(){
	Uint32 alpha = SDL_MapRGBA(superficie->format,0,0,0,255);
	SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = getAlto();
    rect.w = getAncho();
    SDL_FillRect(superficie,&rect,alpha);
}

//devuelve el alto de la superficie
int Superficie::getAlto(){
	return superficie->clip_rect.h;
}
//devuelve el ancho de la superficie
int Superficie::getAncho(){
	return superficie->clip_rect.w;
}

//transparenta toda la superficie a lo pedido (0 completamente transparente 255 completamente opaco)
void Superficie::setTransparency(Uint8 alpha){
	SDL_SetSurfaceAlphaMod(superficie,alpha);
}


//dibuja en las pocisiones x/yDestino el rectOrigen de sup (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
void Superficie::dibujarSupreficie(Superficie* sup,Rectangulo* rectOrigen,int xDestino,int yDestino){
	if((this->superficie!=NULL)&&(sup->superficie!=NULL))
		SdlSurfaceManager::blitSurfaces(sup->superficie,this->superficie,rectOrigen,xDestino,yDestino);
}

//dibuja en las pocisiones x/yDestino el rectOrigen de sup (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
void Superficie::dibujarImagen(Imagen* img,Rectangulo* rectOrigen,int xDestino,int yDestino){
	SdlSurfaceManager::blitSurfaces(img->superficie,this->superficie,rectOrigen,xDestino,yDestino);
}

//devuelve una copia rotada de la imagen
Superficie* Superficie::rotarSuperficie(double ang){
	Superficie* sup = new Superficie();
	sup->superficie = SdlSurfaceManager::rotar(superficie,ang);
	if(SdlSurfaceManager::huboFallas()){
		delete sup;
		sup = NULL;
	}
	return sup;
}

//devuelve una copia rotada de la imagen
Superficie* Superficie::scaleSurface(int pixelesAncho,int pixelesAlto){
	
	Superficie* sup = new Superficie();
	sup->superficie = SdlSurfaceManager::scale(superficie,pixelesAncho,pixelesAlto);
	if(SdlSurfaceManager::huboFallas()){
		delete sup;
		sup = NULL;
	}
	return sup;
}


//devuelve una copia rotada de la imagen conservando tamaño original
Superficie* Superficie::rotarCuadradoSuperficie(double ang){
	
	Superficie* sup = new Superficie();
	sup->superficie = SdlSurfaceManager::rotarLock(superficie,ang);
	if(SdlSurfaceManager::huboFallas()){
		delete sup;
		sup = NULL;
	}
	return sup;
}