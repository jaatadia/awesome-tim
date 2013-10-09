#pragma once
#include "SDL.h"
#include "Rectangulo.h"
#include "Constantes.h"


#define SSM_TAG "SdlSurfaceManager"


/* ejemplo de uso:
	es una clase que contiene funciones nomas asi que los ejemplos de uso serian usar las funiones
	notese que tiene un metodo hubo fallas que deberia ser llamado despues de cada uso de alguna funcion para corroborar
	si se pudo completar correctamente
*/


class SdlSurfaceManager
{
private:
	static bool fallo;
public:
	static bool huboFallas();//indica si se produjeron fallas al realizar una operacion
		
	static SDL_Surface* cargarImagen(const char* cadena);//carga la imagen
	static SDL_Surface* crearSup (int ancho,int alto);//crea una superficie de las dimensiones pasadas
	static SDL_Surface* crearSup ();//crea una superficie dedault	
	static void pintarSup(SDL_Surface* sup, Uint32 color);//pinta la superficie de un color
	static void dibujarCuadrado(SDL_Surface* sup, int x, int y, int ancho,int alto,Uint32 color);

	static SDL_Surface* rotar90(SDL_Surface *sur);//rota la imagen 90 grados
	static SDL_Surface* rotar180(SDL_Surface *sur);//rota la imagen 180 grados
	static SDL_Surface* rotar270(SDL_Surface *sur);//rota la imagen 270 grados
	static SDL_Surface* rotar(SDL_Surface* sur,double angulo);// rota la imagen
	static SDL_Surface* rotarLock90(SDL_Surface *sur);//rota la imagen 90 grados mantiene el tamaño original de la imagen
	static SDL_Surface* rotarLock180(SDL_Surface *sur);//rota la imagen 180 grados mantiene el tamaño original de la imagen
	static SDL_Surface* rotarLock270(SDL_Surface *sur);//rota la imagen 270 grados mantiene el tamaño original de la imagen
	static SDL_Surface* rotarLock(SDL_Surface* sur,double angulo);// rota la imagen y mantiene el tamaño original de la imagen
	static SDL_Surface* rotarZoom(SDL_Surface* sur,int ancho,int alto,double angulo);//rota y zoomea la img
	static SDL_Surface* rotarZoom2(SDL_Surface* sur,int ancho,int alto,double angulo);//rota y zoomea la img

	static SDL_Surface* scale(SDL_Surface* superficie,int pixelesAncho,int pixelesAlto);//escala la superficie


	//para el siguiente grupo de funciones no es necesario llamar a hubo fallas

	//imprime en la las coordenadas x/yDestino de la superficie destino el rectoOrigen de la superficieOrigen
	static void blitSurfaces(SDL_Surface* supOrigen,SDL_Surface* supDestino,Rectangulo* rectOrigen,int xDestino,int yDestino);
	static Uint32 getPixel( SDL_Surface* surface,int x,int y );//devueleve el pixel que se encuentra en la posicion xy
	static void putPixel(SDL_Surface* surface,int x,int y, Uint32 pixel );//pone en la posicion xy el pixel
	static Uint32 blendPixels(SDL_PixelFormat* format,Uint32 pixel1,Uint32 pixel2);//devuelve la mescla de dos pixles

	static void dibujarLinea(SDL_Surface* sup,int x1,int y1,int x2, int y2,int ancho);
	
private:
	static void fallar();//le indica que tiene que fallar(uso interno)
	static SDL_Surface* rotar90(SDL_Surface *sur,bool mismaSup);//rota la imagen 90 grados
	static SDL_Surface* rotar180(SDL_Surface *sur,bool mismaSup);//rota la imagen 180 grados
	static SDL_Surface* rotar270(SDL_Surface *sur,bool mismaSup);//rota la imagen 270 grados
	static SDL_Surface* rotar(SDL_Surface* sur,double angulo,bool mismaSup);// rota la imagen

	static void dibujarDiagonales(SDL_Surface* sup,Uint32 colorD,Uint32 colorB);
	static SDL_Surface* scale(SDL_Surface* superficie,int pixelesAncho,int pixelesAlto,int anchoOrig,int altoOrig,double extra);
};
