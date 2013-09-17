#include "Contenedor.h"
#include "Imagen.h"
#include "ErrorLogHandler.h"
#include <iostream>

Contenedor* Contenedor::cont = NULL;

void Contenedor::putMultimedia(const char* ID,void* medio){
	if (cont == NULL){
		cont = new Contenedor();
		cont->mapa["NONE"] = new Imagen();
	}
	
	Imagen* img = (Imagen*) medio;
	if (img->huboFallos()){
		std::cout<< "--una imagen fallo\n";
		delete img;
		return;
	}else if(cont->mapa.find(ID)== cont->mapa.end()){
		std::cout<< "--A contenedor se le pide que se guarde algo con este ID: "<<ID<<"\n";
		cont->mapa[ID]=medio;
	}else{
		std::cout<< "--El medio: "<<ID<<" ya se encuentra en el contenedor\n";
		delete img;
	}
}

void* Contenedor::getMultimedia(const char* ID){
	if (cont == NULL){
		cont = new Contenedor();
	}
	if(cont->mapa.find(ID)!= cont->mapa.end()) return cont->mapa[ID];
	else {
		std::cout<< "--El medio: "<<ID<< " no se encuentra en el contenedor\n";
		ErrorLogHandler::addError("Contenedor","El archivo multimedia no ha podido cargarse.");
		return cont->mapa["NONE"];
	}
}

void Contenedor::deleteContenedor(){
	if (cont) delete cont;
	cont = NULL;
}


Contenedor::Contenedor(void){
}

Contenedor::~Contenedor(void){
	std::map<std::string ,void*>::iterator it;
	
	for (it = mapa.begin(); it != mapa.end(); ++it){
		Imagen* img = (Imagen*) it->second; //casteandolo a Imagen*
		delete img;
	};
};

void Contenedor::pruebaContenedor(){ //no se que clase de prueba es esta

	Imagen* img1 = new Imagen("hola que tal",12,255,255,255);
	Imagen* img2 = new Imagen("bien2",12,250,250,250);
	Imagen* img3 = new Imagen("hola que tal2",12,255,255,255);
	Imagen* img4 = new Imagen("bien3",12,250,250,250);
	Imagen* img5 = new Imagen("hola que tal3",12,255,255,255);
	Imagen* img6 = new Imagen("bien4",12,250,250,250);
	Imagen* img7 = new Imagen("hola que tal4",12,255,255,255);
	Imagen* img8 = new Imagen("bien5",12,250,250,250);
	Imagen* img9 = new Imagen("hola que tal5",12,255,255,255);
	Imagen* img10 = new Imagen("bien6",12,250,250,250);
	Imagen* img11 = new Imagen("hola que tal6",12,255,255,255);
	Imagen* img12 = new Imagen("bien7",12,250,250,250);
	Imagen* img13 = new Imagen("hola que tal7",12,255,255,255);
	Imagen* img14 = new Imagen("bien8",12,250,250,250);
	Imagen* img15 = new Imagen("hola que tal8",12,255,255,255);
	Imagen* img16 = new Imagen("bien9",12,250,250,250);
	Imagen* img17 = new Imagen("hola que tal9",12,255,255,255);
	Imagen* img18 = new Imagen("bien10",12,250,250,250);
	Imagen* img19 = new Imagen("hola que tal10",12,255,255,255);
	Imagen* img20 = new Imagen("bien11",12,250,250,250);
	Imagen* img21 = new Imagen("hola que tal11",12,255,255,255);
	Imagen* img22 = new Imagen("bien12",12,250,250,250);

	Contenedor::putMultimedia("hola que tal",img1);
	Contenedor::putMultimedia("bien2",img2);
	Contenedor::putMultimedia("hola que tal2",img3);
	Contenedor::putMultimedia("bien3",img4);
	Contenedor::putMultimedia("hola que tal3",img5);
	Contenedor::putMultimedia("bien4",img6);
	Contenedor::putMultimedia("hola que tal4",img7);
	Contenedor::putMultimedia("bien5",img8);
	Contenedor::putMultimedia("hola que tal5",img9);
	Contenedor::putMultimedia("bien6",img10);
	Contenedor::putMultimedia("hola que tal6",img11);
	Contenedor::putMultimedia("bien7",img12);
	Contenedor::putMultimedia("hola que tal7",img13);
	Contenedor::putMultimedia("bien8",img14);
	Contenedor::putMultimedia("hola que tal8",img15);
	Contenedor::putMultimedia("bien9",img16);
	Contenedor::putMultimedia("hola que tal9",img17);
	Contenedor::putMultimedia("bien10",img18);
	Contenedor::putMultimedia("hola que tal10",img19);
	Contenedor::putMultimedia("bien11",img20);
	Contenedor::putMultimedia("hola que tal11",img21);
	Contenedor::putMultimedia("bien12",img22);

	Contenedor::deleteContenedor();
};


bool Contenedor::estaMultimedia(const char* ID){

	if (cont == NULL){
		cont = new Contenedor();
	}

	if(cont->mapa.count(ID) == 0) return false;

	return true;
}