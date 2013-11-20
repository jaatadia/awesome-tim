#include "Superficie.h"
#include "ErrorLogHandler.h"
#include "SdlSurfaceManager.h"

//nueva superficie segun las constantes ANCHO y ALTO
Superficie::Superficie(){
	superficie = NULL;
}

//nueva superficie de las dimensiones pasadas
Superficie::Superficie(int ancho,int alto){
	try{
		if((ancho<=0)||(alto<=0)){
			superficie = SdlSurfaceManager::crearSup(10,10);
		}else{
			superficie = SdlSurfaceManager::crearSup(ancho,alto);
		}
		if(SdlSurfaceManager::huboFallas())	fallar();
		else restore();
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}

//destructor de la superficie
Superficie::~Superficie(void){
	try{
		if(superficie == NULL) return;
		SDL_FreeSurface(superficie);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}


//repinta el fondo de la imagen
void Superficie::restore(){
	try{
		if(superficie == NULL) return;
		Uint32 negro = SDL_MapRGBA(superficie->format,0,0,0,255);
		SdlSurfaceManager::pintarSup(superficie,negro);

	}catch(...){
		if(this!=NULL)this->fallar();
	}
}

void Superficie::restoreAlpha(){
	try{
		if(superficie == NULL) return;
		Uint32 alpha = SDL_MapRGBA(superficie->format,0,0,0,0);
		SdlSurfaceManager::pintarSup(superficie,alpha);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}


//devuelve el alto de la superficie
int Superficie::getAlto(){
	try{
		if(superficie == NULL) return -1;
		return superficie->clip_rect.h;
	}catch(...){
		if(this!=NULL)this->fallar();
		return 1;
	}
}
//devuelve el ancho de la superficie
int Superficie::getAncho(){
	try{
		if(superficie == NULL) return -1;
		return superficie->clip_rect.w;
	}catch(...){
		if(this!=NULL)this->fallar();
		return 1;
	}
}

//transparenta toda la superficie a lo pedido (0 completamente transparente 255 completamente opaco)
void Superficie::setTransparency(Uint8 alpha){
	try{
		if(superficie == NULL) return;
		SDL_SetSurfaceAlphaMod(superficie,alpha);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}


//dibuja en las pocisiones x/yDestino el rectOrigen de sup (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
void Superficie::dibujarSupreficie(Superficie* sup,Rectangulo* rectOrigen,int xDestino,int yDestino){
	try{
		if(superficie == NULL) return;
		if((this!=NULL)&&(sup!=NULL))
			SdlSurfaceManager::blitSurfaces(sup->superficie,this->superficie,rectOrigen,xDestino,yDestino);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}

//dibuja en las pocisiones x/yDestino el rectOrigen de sup (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
void Superficie::dibujarImagen(Imagen* img,Rectangulo* rectOrigen,int xDestino,int yDestino){
	try{
		if(superficie == NULL) return;
		if((this!=NULL)&&(img!=NULL))
			SdlSurfaceManager::blitSurfaces(img->superficie,this->superficie,rectOrigen,xDestino,yDestino);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}

//devuelve una copia rotada de la imagen
Superficie* Superficie::rotarSuperficie(double ang){
	try{
		if(superficie == NULL) return NULL;
		Superficie* sup = new Superficie();
		sup->superficie = SdlSurfaceManager::rotar(superficie,ang);
		if(SdlSurfaceManager::huboFallas()){
			delete sup;
			sup = NULL;
		}
		return sup;
	}catch(...){
		if(this!=NULL)this->fallar();
		return NULL;
	}
}

//devuelve una copia rotada de la imagen
Superficie* Superficie::scaleSurface(int pixelesAncho,int pixelesAlto){
	try{
		if(this == NULL) return NULL;
		if(superficie == NULL) return NULL;

		int pixAnc = 1,pixAlt = 1;

		if(pixelesAncho!=0){
			pixAnc = pixelesAncho;
		}
		if(pixelesAlto!=0){
			pixAlt = pixelesAlto;
		}

		Superficie* sup = new Superficie();
		if( this->superficie == NULL) return sup;

		sup->superficie = SdlSurfaceManager::scale(superficie,pixAnc,pixAlt);
		if(SdlSurfaceManager::huboFallas()){
			delete sup;
			sup = NULL;
		}
		return sup;
	}catch(...){
		if(this!=NULL)this->fallar();
		return NULL;
	}
}


//devuelve una copia rotada de la imagen conservando tamaño original
Superficie* Superficie::rotarCuadradoSuperficie(double ang){
	
	try{
		if(superficie == NULL) return NULL;

		Superficie* sup = new Superficie();
		sup->superficie = SdlSurfaceManager::rotarLock(superficie,ang);
		if(SdlSurfaceManager::huboFallas()){
			delete sup;
			sup = NULL;
		}
		return sup;
	}catch(...){
		if(this!=NULL)this->fallar();
		return NULL;
	}
}

void Superficie::dibujarCuadradoNegro(int x, int y, int ancho,int alto){
	try{
		if(superficie == NULL) return;
		Uint32 negro = SDL_MapRGBA(this->superficie->format,0,0,0,255);
		SdlSurfaceManager::dibujarCuadrado(superficie,x,y,ancho,alto,negro);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}

void Superficie::restoreGris(){
	try{
		if(superficie == NULL) return;
		Uint32 gris = SDL_MapRGBA(this->superficie->format,200,200,200,255);
		SdlSurfaceManager::pintarSup(superficie,gris);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}

Uint32 Superficie::getPixel(int x, int y) {
	try{
	if(superficie == NULL) return 0;
	return SdlSurfaceManager::getPixel(this->superficie, x, y);
	}catch(...){
		if(this!=NULL)this->fallar();
		return 0;
	}
}

void Superficie::dibujarLinea(int x1,int y1,int x2, int y2,int ancho,int r,int g,int b){
	try{
		if(superficie == NULL) return;
		SdlSurfaceManager::dibujarLinea(this->superficie,x1,y1,x2,y2,ancho,r,g,b);
	}catch(...){
		if(this!=NULL)this->fallar();
	}
}