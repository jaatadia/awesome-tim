#include "Contenedor.h"
#include "Imagen.h"
#include <iostream>

Contenedor* Contenedor::cont = NULL;

void Contenedor::putMultimedia(const char* ID,void* medio){
	if (cont == NULL){
		cont = new Contenedor();
		cont->mapa["NONE"] = new Imagen();
	}
	cont->mapa[ID]=medio;
}

void* Contenedor::getMultimedia(const char* ID){
	if (cont == NULL){
		cont = new Contenedor();
	}
	if(cont->mapa.find(ID)!= cont->mapa.end()) return cont->mapa[ID];
	else return cont->mapa["NONE"];
}

void Contenedor::deleteContenedor(){
	if (cont) delete cont;
}


Contenedor::Contenedor(void){
}

Contenedor::~Contenedor(void){
	std::map<const char* ,void*>::iterator it;
	
	for (it = mapa.begin(); it != mapa.end(); ++it){
		Imagen* img = (Imagen*) it->second; //casteandolo a Imagen*
		delete img;
	};
};

void Contenedor::pruebaContenedor(){ //no se que clase de prueba es esta

	Imagen* img1 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img2 = new Imagen("bien",12,250,250,250);
	Imagen* img3 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img4 = new Imagen("bien",12,250,250,250);
	Imagen* img5 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img6 = new Imagen("bien",12,250,250,250);
	Imagen* img7 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img8 = new Imagen("bien",12,250,250,250);
	Imagen* img9 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img10 = new Imagen("bien",12,250,250,250);
	Imagen* img11 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img12 = new Imagen("bien",12,250,250,250);
	Imagen* img13 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img14 = new Imagen("bien",12,250,250,250);
	Imagen* img15 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img16 = new Imagen("bien",12,250,250,250);
	Imagen* img17 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img18 = new Imagen("bien",12,250,250,250);
	Imagen* img19 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img20 = new Imagen("bien",12,250,250,250);
	Imagen* img21 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img22 = new Imagen("bien",12,250,250,250);

	Contenedor::putMultimedia("hola que tal",img1);
	Contenedor::putMultimedia("bien",img2);
	Contenedor::putMultimedia("hola que tal",img3);
	Contenedor::putMultimedia("bien",img4);
	Contenedor::putMultimedia("hola que tal",img5);
	Contenedor::putMultimedia("bien",img6);
	Contenedor::putMultimedia("hola que tal",img7);
	Contenedor::putMultimedia("bien",img8);
	Contenedor::putMultimedia("hola que tal",img9);
	Contenedor::putMultimedia("bien",img10);
	Contenedor::putMultimedia("hola que tal",img11);
	Contenedor::putMultimedia("bien",img12);
	Contenedor::putMultimedia("hola que tal",img13);
	Contenedor::putMultimedia("bien",img14);
	Contenedor::putMultimedia("hola que tal",img15);
	Contenedor::putMultimedia("bien",img16);
	Contenedor::putMultimedia("hola que tal",img17);
	Contenedor::putMultimedia("bien",img18);
	Contenedor::putMultimedia("hola que tal",img19);
	Contenedor::putMultimedia("bien",img20);
	Contenedor::putMultimedia("hola que tal",img21);
	Contenedor::putMultimedia("bien",img22);

	Contenedor::deleteContenedor();
};
