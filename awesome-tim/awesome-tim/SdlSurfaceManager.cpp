#include "SdlSurfaceManager.h"
#include "ErrorLogHandler.h"
#include "SDL_image.h"
#include <cmath>

//incializo que no hubo fallas
bool SdlSurfaceManager:: fallo = false;

//devuelvo si hubo o no fallas y si hubo reinicio
bool SdlSurfaceManager::huboFallas(){
	
	bool temp = fallo;
	fallo = false;
	return temp;
}

//funcion interna para decir que fallo
void SdlSurfaceManager::fallar(){
	fallo = true;
}

//devuelve el pixel xy de la superficie
Uint32 SdlSurfaceManager::getPixel( SDL_Surface *surface, int x, int y ){
	if((surface==NULL)||(x>=surface->w)||(x<0)||(y<0)||(y>=surface->h))return 0;
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[ ( y * surface->w ) + x ];
}

//pone el pixel en el xy de la superficie
void SdlSurfaceManager::putPixel( SDL_Surface *surface,int x, int y, Uint32 pixel ){
			
	if((surface==NULL)||(x>=surface->w)||(x<0)||(y<0)||(y>=surface->h))return;
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[ ( y * surface->w ) + x ] = pixel;
}

//pinta la superficie de un color
void SdlSurfaceManager::pintarSup(SDL_Surface *sup, Uint32 color){
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = sup->h;
	rect.w = sup->w;
	SDL_FillRect(sup,&rect,color);
}

void SdlSurfaceManager::dibujarCuadrado(SDL_Surface* sup, int x, int y, int ancho,int alto,Uint32 color){
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = alto;
	rect.w = ancho;
	SDL_FillRect(sup,&rect,color);

}

//carga una imagen de direccion cadena
SDL_Surface* SdlSurfaceManager::cargarImagen(const char *cadena){
	
	
	/*char cadena[256];
	
	int i=0;
	bool termino = false;
	while((i<255)&&(!termino)){
		char c = cad[i];
		cadena[i] = '\0';
		if (((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z'))||((c>='0')&&(c<='9'))||(c==' ')||(c=='.')||(c=='-')||(c=='_')||(c=='/')){
			cadena[i] = c;
		}else{
			termino = true;
		}
		i++;
	}
	std::cout<<cadena<<"\n";
	*/
	
	
		
	SDL_Surface* temp = NULL; 
	SDL_Surface* superficie = NULL; 
	temp = IMG_Load(cadena);
    if(temp == NULL){
        ErrorLogHandler::addError(SSM_TAG,SDL_GetError());
		fallar();
	}else{
		superficie = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGBA8888,0);
		if(superficie == NULL){
			ErrorLogHandler::addError(SSM_TAG,SDL_GetError());
			fallar();
		}else SDL_SetSurfaceBlendMode(superficie,SDL_BLENDMODE_BLEND);
		SDL_FreeSurface(temp);
	}
	return superficie;
}


//crea una sdl surface de anchoxalto
SDL_Surface* SdlSurfaceManager::crearSup(int ancho,int alto){
	
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	SDL_Surface* sur = NULL;
	SDL_Surface* temp = NULL;
	
	temp = SDL_CreateRGBSurface(0,ancho,alto,32,rmask,gmask,bmask,amask);
	if(temp == NULL){
		ErrorLogHandler::addError(SSM_TAG,SDL_GetError());
		fallar();
	}else{
		sur = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGBA8888,0);
		SDL_FreeSurface(temp);
		if(sur == NULL){
			ErrorLogHandler::addError(SSM_TAG,SDL_GetError());
			fallar();
		}else{
			SDL_SetSurfaceBlendMode(sur,SDL_BLENDMODE_BLEND);
			Uint32 alpha = SDL_MapRGBA(sur->format,0,0,0,0);
			pintarSup(sur,alpha);
		}
	}
	return sur;
}

//crea una sdl surface de anchoxalto
SDL_Surface* SdlSurfaceManager::crearSup(){
	SDL_Surface* sup = crearSup(100,100);
	Uint32 rojo = SDL_MapRGBA(sup->format,255,0,0,255);
	Uint32 blanco = SDL_MapRGBA(sup->format,255,255,255,255);
	Uint32 negro = SDL_MapRGBA(sup->format,0,0,0,255);

	SDL_LockSurface(sup);
	double r2 = pow(double(50),2);
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			if( pow(double(i-50),2)+pow(double(j-50),2) <= r2) putPixel(sup,i,j,blanco);
		}
	}
	SDL_UnlockSurface(sup);

	dibujarDiagonales(sup,rojo,negro);

	return sup;
}


void SdlSurfaceManager::dibujarDiagonales(SDL_Surface* sup,Uint32 colorD,Uint32 colorB){
	
	SDL_LockSurface(sup); 
	
	int inicio = sup->w/3;
	int fin = sup->w*2/3;
	
	putPixel(sup,inicio,inicio-3,colorB);
	putPixel(sup,inicio,inicio-2,colorB);
	putPixel(sup,inicio,inicio-1,colorB);
	putPixel(sup,inicio,inicio,colorB);
	putPixel(sup,inicio,inicio+1,colorB);
	putPixel(sup,inicio,inicio+2,colorB);
	putPixel(sup,inicio,inicio+3,colorB);

	putPixel(sup,inicio,sup->h-(inicio-3),colorB);
	putPixel(sup,inicio,sup->h-(inicio-2),colorB);
	putPixel(sup,inicio,sup->h-(inicio-1),colorB);
	putPixel(sup,inicio,sup->h-inicio,colorB);
	putPixel(sup,inicio,sup->h-(inicio+1),colorB);
	putPixel(sup,inicio,sup->h-(inicio+2),colorB);
	putPixel(sup,inicio,sup->h-(inicio+3),colorB);

	for(int i = inicio;i<fin;i++){
		putPixel(sup,i,i-3,colorB);
		putPixel(sup,i,i-2,colorD);
		putPixel(sup,i,i-1,colorD);
		putPixel(sup,i,i,colorD);
		putPixel(sup,i,i+1,colorD);
		putPixel(sup,i,i+2,colorD);
		putPixel(sup,i,i+3,colorB);

		putPixel(sup,i,sup->h-(i-3),colorB);
		putPixel(sup,i,sup->h-(i-2),colorD);
		putPixel(sup,i,sup->h-(i-1),colorD);
		putPixel(sup,i,sup->h-i,colorD);
		putPixel(sup,i,sup->h-(i+1),colorD);
		putPixel(sup,i,sup->h-(i+2),colorD);
		putPixel(sup,i,sup->h-(i+3),colorB);

	}
	
	putPixel(sup,fin,fin-3,colorB);
	putPixel(sup,fin,fin-2,colorB);
	putPixel(sup,fin,fin-1,colorB);
	putPixel(sup,fin,fin,colorB);
	putPixel(sup,fin,fin+1,colorB);
	putPixel(sup,fin,fin+2,colorB);
	putPixel(sup,fin,fin+3,colorB);

	putPixel(sup,fin,sup->h-(fin-3),colorB);
	putPixel(sup,fin,sup->h-(fin-2),colorB);
	putPixel(sup,fin,sup->h-(fin-1),colorB);
	putPixel(sup,fin,sup->h-fin,colorB);
	putPixel(sup,fin,sup->h-(fin+1),colorB);
	putPixel(sup,fin,sup->h-(fin+2),colorB);
	putPixel(sup,fin,sup->h-(fin+3),colorB);

	SDL_UnlockSurface(sup); 
}

//rota la imagen 90 grados
SDL_Surface* SdlSurfaceManager::rotar90(SDL_Surface *sur){
	return  rotar90(sur,false);
}

//rota la imagen 180 grados
SDL_Surface* SdlSurfaceManager::rotar180(SDL_Surface *sur){
	return rotar180(sur,false);
}

//rota la imagen 270 grados
SDL_Surface* SdlSurfaceManager::rotar270(SDL_Surface *sur){
	return rotar270(sur,false);
}

// rota la imagen
SDL_Surface* SdlSurfaceManager::rotar(SDL_Surface* sur,double angulo){
	return rotar(sur,angulo,false);
};

//rota la imagen 90 grados y mantiene el tamaño original de la imagen
SDL_Surface* SdlSurfaceManager::rotarLock90(SDL_Surface *sur){
	return  rotar90(sur,true);
}

//rota la imagen 180 grados y mantiene el tamaño original de la imagen
SDL_Surface* SdlSurfaceManager::rotarLock180(SDL_Surface *sur){
	return rotar180(sur,true);
}

//rota la imagen 270 grados y mantiene el tamaño original de la imagen
SDL_Surface* SdlSurfaceManager::rotarLock270(SDL_Surface *sur){
	return rotar270(sur,true);
}

// rota la imagen y mantiene el tamaño original de la imagen
SDL_Surface* SdlSurfaceManager::rotarLock(SDL_Surface* sur,double angulo){
	return rotar(sur,angulo,true);
};

//imprime en la las coordenadas x/yDestino de la superficie destino el rectoOrigen de la superficieOrigen
void SdlSurfaceManager::blitSurfaces(SDL_Surface* supOrigen,SDL_Surface* supDestino,Rectangulo* rectOrigen,int xDestino,int yDestino){
	if((supOrigen==NULL)||(supDestino==NULL))return;
	SDL_Rect* rO;
	SDL_Rect rectO,rectD;
	if(rectOrigen == NULL) rO = NULL;
	else{
		rectO.x = int(rectOrigen->x);
		rectO.y = int(rectOrigen->y);
		rectO.h = int(rectOrigen->alto);
		rectO.w = int(rectOrigen->ancho);
		rO = &rectO;
	}
		rectD.x = xDestino;
		rectD.y = yDestino;

	SDL_BlitSurface(supOrigen,rO,supDestino,&rectD);
}

//rota la imagen 90 grados
SDL_Surface* SdlSurfaceManager::rotar90(SDL_Surface *sur,bool mismaSup){
	int alto = sur->w;
	int ancho = sur->h;
	
	if(mismaSup){
		ancho = sur->w;
		alto = sur->h;
	}

	SDL_Surface* img = crearSup(ancho,alto);
	if(img == NULL) return NULL;

	SDL_LockSurface(sur); 
	SDL_LockSurface(img); 
	
	for(int i=0;i<sur->w;i++){
		for(int j=0;j<sur->h;j++)
			putPixel(img,j,(img->h -1)-i,getPixel(sur,i,j));
	}
	
	SDL_UnlockSurface(sur); 
	SDL_UnlockSurface(img); 
	return img;
}

//rota la imagen 180 grados
SDL_Surface* SdlSurfaceManager::rotar180(SDL_Surface *sur,bool mismaSup){
	int ancho = sur->w;
	int alto = sur->h;
	
	SDL_Surface* img = crearSup(ancho,alto);
	if(img == NULL) return NULL;
	
	SDL_LockSurface(sur); 
	SDL_LockSurface(img); 
	
	for(int i=0;i<sur->w;i++){
		for(int j=0;j<sur->h;j++)
			putPixel(img,(img->w -1) - i,(img->h -1) -j ,getPixel(sur,i,j));
	}

	SDL_UnlockSurface(sur); 
	SDL_UnlockSurface(img); 

	return img;
}
//rota la imagen 270 grados
SDL_Surface* SdlSurfaceManager::rotar270(SDL_Surface *sur,bool mismaSup){
	int ancho = sur->h;
	int alto = sur->w;

	if(mismaSup){
		ancho = sur->w;
		alto = sur->h;
	}

	SDL_Surface* img = crearSup(ancho,alto);
	if(img == NULL) return NULL;

	SDL_LockSurface(sur); 
	SDL_LockSurface(img); 
	
	for(int i=0;i<sur->w;i++){
		for(int j=0;j<sur->h;j++)
			putPixel(img,(img->w -1) - j,i ,getPixel(sur,i,j));
	}

	SDL_UnlockSurface(sur); 
	SDL_UnlockSurface(img); 

	return img;
}

//rota la superficie pasada en ang sentido antihorario
SDL_Surface* SdlSurfaceManager::rotar(SDL_Surface *sur, double ang,bool mismaSup){
	
	SDL_Surface* img;
	bool destruir = true;

	while(ang>=360) ang -= 360;
	while(ang<0) ang += 360;

	double angulo = (ang*PI/180);
	
	double alto, ancho;
	if ((mismaSup)||(ang==0)||(ang==180)){
		ancho = sur->w;
		alto = sur->h;
	}else if((ang == 90)||(ang==270)){
		ancho = sur->h;
		alto = sur->w;
	}else if(ang<90){
		ancho = sur->w*cos(angulo)+sur->h*sin(angulo);
		alto = sur->w*sin(angulo)+sur->h*cos(angulo);
	}else if(ang<180){
		ancho = sur->h*cos(angulo-PI/2)+sur->w*sin(angulo-PI/2);
		alto = sur->h*sin(angulo-PI/2)+sur->w*cos(angulo-PI/2);
	}else if(ang<270){
		ancho = sur->w*cos(angulo-PI)+sur->h*sin(angulo-PI);
		alto = sur->w*sin(angulo-PI)+sur->h*cos(angulo-PI);
	}else{
		ancho = sur->h*cos(angulo-PI*3/2)+sur->w*sin(angulo-PI*3/2);
		alto = sur->h*sin(angulo-PI*3/2)+sur->w*cos(angulo-PI*3/2);
	}
	double centroX = ((double)sur->w)/2;
	double centroY = ((double)sur->h)/2;
	double nuevoCentroX = ancho/2;
	double nuevoCentroY = alto/2;

	img = crearSup(int(ancho),int(alto));
	if(img == NULL) return NULL;

	Uint32 alpha = SDL_MapRGBA(sur->format,0,0,0,0);

	SDL_LockSurface(sur); 
	SDL_LockSurface(img); 

	double coseno = cos(-angulo);
	double seno = sin(-angulo);
	
	for(int i=0;i<sur->w;i++){
		double temp1 = (i-centroX)*coseno;
		double temp2 = (i-centroX)*seno;
		for(int j=0;j<sur->h;j++){
			Uint32 pixel = getPixel(sur,i,j);
			if((pixel!=alpha)&&((i-centroX != 0)||(j-centroY!=0))){	
				int nuevoX = int((nuevoCentroX + temp1 - (j-centroY)*seno)+0.99);
				int nuevoY = int((nuevoCentroY + temp2 + (j-centroY)*coseno)+0.99);
				putPixel(img,nuevoX,nuevoY,pixel);
			}
		}	
	}
	
	
	for(int i=0;i<img->w;i++){
		for(int j=0;j<img->h;j++){
			if(getPixel(img,i,j)==alpha){
				Uint32 pix1 = getPixel(img,i,j-1);
				Uint32 pix2 = getPixel(img,i,j+1);
				if((pix1!=alpha)&&(pix2!=alpha)){
					putPixel(img,i,j,blendPixels(img->format,pix1,pix2));
				}else if((pix1!=alpha)||(pix2!=alpha)){
					Uint32 pix3 = getPixel(img,i+1,j+1);
					Uint32 pix4 = getPixel(img,i-1,j-1);
					if((pix3!=alpha)&&(pix4!=alpha)) putPixel(img,i,j,blendPixels(img->format,pix3,pix4));
				}
			}
		}	
	}
	
	SDL_UnlockSurface(sur); 
	SDL_UnlockSurface(img); 

	return img;
}

Uint32 SdlSurfaceManager::blendPixels(SDL_PixelFormat* format,Uint32 pixel1,Uint32 pixel2){
	Uint8 r1,g1,b1,a1,r2,g2,b2,a2;
	
	SDL_GetRGBA(pixel1,format,&r1,&g1,&b1,&a1);
	SDL_GetRGBA(pixel2,format,&r2,&g2,&b2,&a2);
	
	/*
	r1=(r1+r2)/2;
	g1=(g1+g2)/2;
	b1=(b1+b2)/2;
	if(a2>a1) a1 = a2;
	*/
	
	/*
	if(r2>r1) r1 = r2;
	if(g2>g1) g1 = g2;
	if(b2>b1) b1 = b2;
	if(a2>a1) a1 = a2;
	*/	
	
	/*
	if(a2>a1){
		r1 = r2;
		g1 = g2;
		b1 = b2;
		a1 = a2;
	}
	*/
		
	if (a1 == 0){
		r1 = r2;
		g1 = g2;
		b1 = b2;
		a1 = a2;
	}else if(a2 != 0){
		if(a2<a1){
			r1 = r2;
			g1 = g2;
			b1 = b2;
			a1 = a2;
		}
	}


	return SDL_MapRGBA(format,r1,g1,b1,a1);

}

SDL_Surface* SdlSurfaceManager::scale(SDL_Surface* superficie,int pixelesAncho,int pixelesAlto){
	if(superficie==NULL)return NULL;
	double relacionPixelX = pixelesAncho/(double(superficie->w));
	double relacionPixelY = pixelesAlto/(double(superficie->h));
	
	SDL_Surface* res = crearSup(pixelesAncho,pixelesAlto);
	if(res == NULL) return NULL;

	Uint32 alpha = SDL_MapRGBA(superficie->format,0,0,0,0);
	
	for(int i = 0;i<superficie->w;i++){
		for(int j = 0;j<superficie->h;j++){
			Uint32 pixelOrigen = getPixel(superficie,i,j);
			if(pixelOrigen!=alpha){
				for(int k = 0;k<(relacionPixelX+0.99);k++){
					int destinoX = int (i*relacionPixelX + k);
					for(int l = 0;l<(relacionPixelY+0.99);l++){
						int destinoY = int (j*relacionPixelY + l);
						Uint32 pixelDestino = getPixel(res,destinoX,destinoY);
						if(pixelDestino!=alpha) putPixel(res,destinoX,destinoY,pixelOrigen);
						else putPixel(res,destinoX,destinoY,blendPixels(res->format,pixelOrigen,pixelDestino));
					}
				}
			}
		}
	}
	return res;
}

SDL_Surface* SdlSurfaceManager::rotarZoom(SDL_Surface* sur, int pixAncho, int pixAlto, double ang){
	
	SDL_Surface* img;
	
	while(ang>=360) ang -= 360;
	while(ang<0) ang += 360;

	double angulo = (ang*PI/180);
	
	double extra = sqrt(pow((double)sur->w,2)+pow((double)sur->h,2));
	
	double alto = 2*extra;
	double ancho = 2*extra;
	double centroX = ((double)sur->w)/2;
	double centroY = ((double)sur->h)/2;
	double nuevoCentroX = ancho/2;
	double nuevoCentroY = alto/2;

	img = crearSup(int(ancho),int(alto));
	if(img == NULL) return NULL;

	Uint32 alpha = SDL_MapRGBA(sur->format,0,0,0,0);

	SDL_LockSurface(sur); 
	SDL_LockSurface(img); 

	double coseno = cos(-angulo);
	double seno = sin(-angulo);
	
	
	for(int i=0;i<sur->w;i++){
		double temp1 = (i-centroX)*coseno;
		double temp2 = (i-centroX)*seno;
		for(int j=0;j<sur->h;j++){
			Uint32 pixel = getPixel(sur,i,j);
			if((pixel!=alpha)&&((i-centroX != 0)||(j-centroY!=0))){	
				int nuevoX = int((nuevoCentroX + temp1 - (j-centroY)*seno)+0.99);
				int nuevoY = int((nuevoCentroY + temp2 + (j-centroY)*coseno)+0.99);
				putPixel(img,nuevoX,nuevoY,pixel);
			}else if((pixel!=alpha)){
				putPixel(img,int(nuevoCentroX),int(nuevoCentroX),pixel);
			}
		}	
	}
	
	
	for(int i=0;i<img->w;i++){
		for(int j=0;j<img->h;j++){
			if(getPixel(img,i,j)==alpha){
				Uint32 pix1 = getPixel(img,i,j-1);
				Uint32 pix2 = getPixel(img,i,j+1);
				if((pix1!=alpha)&&(pix2!=alpha)){
					putPixel(img,i,j,blendPixels(img->format,pix1,pix2));
				}else if((pix1!=alpha)||(pix2!=alpha)){
					Uint32 pix3 = getPixel(img,i+1,j+1);
					Uint32 pix4 = getPixel(img,i-1,j-1);
					if((pix3!=alpha)&&(pix4!=alpha))putPixel(img,i,j,blendPixels(img->format,pix3,pix4));
				}
			}
		}	
	}
	
	SDL_UnlockSurface(sur); 
	SDL_UnlockSurface(img); 

	SDL_Surface* temp = scale(img,pixAncho,pixAlto,sur->w,sur->h,extra);
	
	SDL_FreeSurface(img);
	return temp;
}

SDL_Surface* SdlSurfaceManager::scale(SDL_Surface* superficie,int pixelesAncho,int pixelesAlto,int anchoOrig,int altoOrig,double extra){
	
	
	if(superficie==NULL)return NULL;

	double relacionPixelX = pixelesAncho/(double(anchoOrig));
	double relacionPixelY = pixelesAlto/(double(altoOrig));
	
	SDL_Surface* res = crearSup(int(pixelesAncho+(relacionPixelX*(2*extra-anchoOrig))),int(pixelesAlto+(relacionPixelY*(2*extra-altoOrig))));
	if(res == NULL) return NULL;

	Uint32 alpha = SDL_MapRGBA(superficie->format,0,0,0,0);
	
	for(int i = 0;i<superficie->w;i++){
		for(int j = 0;j<superficie->h;j++){
			Uint32 pixelOrigen = getPixel(superficie,i,j);
			if(pixelOrigen!=alpha){
				for(int k = 0;k<(relacionPixelX+0.99);k++){
					int destinoX = int (i*relacionPixelX + k);
					for(int l = 0;l<(relacionPixelY+0.99);l++){
						int destinoY = int (j*relacionPixelY + l);
						Uint32 pixelDestino = getPixel(res,destinoX,destinoY);
						if(pixelDestino!=alpha) putPixel(res,destinoX,destinoY,pixelOrigen);
						else putPixel(res,destinoX,destinoY,blendPixels(res->format,pixelOrigen,pixelDestino));
					}
				}
			}
		}
	}
	return res;
}


SDL_Surface* SdlSurfaceManager::rotarZoom2(SDL_Surface* sur, int pixAncho, int pixAlto, double ang){
	
	while(ang>=360) ang -= 360;
	while(ang<0) ang += 360;

	double extra = sqrt(pow((double)sur->w,2)+pow((double)sur->h,2));
	
	double alto = 2*extra;
	double ancho = 2*extra;
	double centroX = ((double)sur->w)/2;
	double centroY = ((double)sur->h)/2;
	double nuevoCentroX = ancho/2;
	double nuevoCentroY = alto/2;
	double angulo = (ang*PI/180.0);
	

	double coseno = cos(-angulo);
	double seno = sin(-angulo);
	
	double relacionPixelX = pixAncho/(double(sur->w));
	double relacionPixelY = pixAlto/(double(sur->h));
	
	SDL_Surface* res = crearSup(int(pixAncho+(relacionPixelX*(2*extra-sur->w))),int(pixAlto+(relacionPixelY*(2*extra-sur->h))));
	if(res == NULL) return NULL;

	SDL_LockSurface(sur); 
	SDL_LockSurface(res); 
	
	Uint32 alpha = SDL_MapRGBA(sur->format,0,0,0,0);


	for(int i=0;i<sur->w;i++){
		double temp1 = (i-centroX)*coseno;
		double temp2 = (i-centroX)*seno;
		for(int j=0;j<sur->h;j++){
			
			Uint32 pixelOrigen = getPixel(sur,i,j);

			if(pixelOrigen!=alpha){
				int nuevoX = int((nuevoCentroX + temp1 - (j-centroY)*seno)+0.99);
				int nuevoY = int((nuevoCentroY + temp2 + (j-centroY)*coseno)+0.99);

				for(int k = 0;k<(relacionPixelX+0.99);k++){
					int destinoX = int (nuevoX*relacionPixelX + k);
					for(int l = 0;l<(relacionPixelY+0.99);l++){
						int destinoY = int (nuevoY*relacionPixelY + l);
						Uint32 pixelDestino = getPixel(res,destinoX,destinoY);
						if(pixelDestino!=alpha) putPixel(res,destinoX,destinoY,pixelOrigen);
						else putPixel(res,destinoX,destinoY,blendPixels(res->format,pixelOrigen,pixelDestino));
					}
				}
			}
		}	
	}
	
	
	SDL_UnlockSurface(sur); 
	SDL_UnlockSurface(res); 

	return res;
}