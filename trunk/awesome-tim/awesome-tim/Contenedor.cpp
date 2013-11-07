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
	/*if (img->huboFallos()){
		//std::cout<< "--una imagen fallo\n";
		delete img;
		return;
	}else*/ if(cont->mapa.find(ID)== cont->mapa.end()){
		//std::cout<< "--A contenedor se le pide que se guarde algo con este ID: "<<ID<<"\n";
		cont->mapa[ID]=medio;
	}else{
		//std::cout<< "--El medio: "<<ID<<" ya se encuentra en el contenedor\n";
		delete img;
	}
}

void* Contenedor::getMultimedia(const char* ID){
	if (cont == NULL){
		cont = new Contenedor();
	}
	if(cont->mapa.find(ID)!= cont->mapa.end()) return cont->mapa[ID];
	else {
		std::string st = "El archivo multimedia: ";
		st+= ID;
		st+= " no ha podido cargarse.";
		ErrorLogHandler::addError("Contenedor",st.c_str());
		return cont->mapa["NONE"];
	}
}

void Contenedor::deleteContenedor(){
	if (cont) delete cont;
	cont = NULL;
}


Contenedor::Contenedor(void){

	////cargo las imagenes de los elementos del juego
	mapa[ID_PLATAFORMA] = new Imagen(ID_PLATAFORMA); //si el id estuviese en el archivo yaml esto no iria
//	mapa[ImgSegmSoga]= new Imagen(ImgSegmSoga);
	mapa[ID_GLOBO] = new Imagen(ID_GLOBO);
	mapa[ID_PELOTATENIS] = new Imagen(ID_PELOTATENIS);
	mapa[ID_PELOTABASQUET] = new Imagen(ID_PELOTABASQUET);
	mapa[ID_PELOTABOWLING] = new Imagen(ID_PELOTABOWLING);
//	mapa[ID_PUNTA_CINTA_IZQ] = new Imagen(ID_PUNTA_CINTA_IZQ); //punta izq de cinta
//	mapa[ID_PUNTA_CINTA_DER] = new Imagen(ID_PUNTA_CINTA_DER); //punta der de cinta
	mapa[ID_MOTOR] = new Imagen(ID_MOTOR); //motor
	mapa[ID_CORREA] = new Imagen(ID_CORREA); //correa
	mapa[ID_ENGRANAJE] = new Imagen(ID_ENGRANAJE); //engranaje
	mapa[ID_MOTOR_1] = new Imagen(ID_MOTOR_1); //engranaje
	mapa[ID_MOTOR_2] = new Imagen(ID_MOTOR_2); //engranaje
	mapa[ID_TABLA_BALANCIN] = new Imagen(ID_TABLA_BALANCIN); //tabla balancin
	mapa[ID_PUNTA_BALANCIN] = new Imagen(ID_PUNTA_BALANCIN); //puntas balancin
	mapa[ID_BALANCIN_IZQ] = new Imagen(ID_BALANCIN_IZQ);
	mapa[ID_BALANCIN_DER] = new Imagen(ID_BALANCIN_DER);
	mapa[ID_SOGA] = new Imagen(ID_SOGA); //soga
	mapa[ID_CINTA_TRANSPORTADORA] = new Imagen(ID_CINTA_TRANSPORTADORA); //Cinta Transportadora
	mapa[ID_CTRANSP_CIRC] = new Imagen(ID_CTRANSP_CIRC);
	mapa[ID_CTRANSP_CLAVO] = new Imagen(ID_CTRANSP_CLAVO);
	mapa[ID_CINTA] = new Imagen(ID_CINTA);
	mapa[ID_VELA_CERA] = new Imagen(ID_VELA_CERA);
	mapa[ID_LLAMA] = new Imagen(ID_LLAMA);
	mapa[ID_POLEA] = new Imagen(ID_POLEA);
	mapa[ID_ARO] = new Imagen(ID_ARO);
	mapa[ID_YUNQUE] = new Imagen(ID_YUNQUE);
	mapa[ID_CLAVO] = new Imagen(ID_CLAVO);
	mapa[ID_CHINCHE] = new Imagen(ID_CHINCHE);
	mapa[ID_TIJERA] = new Imagen(ID_TIJERA);
	mapa[ID_TIJERA_CERRADA] = new Imagen(ID_TIJERA_CERRADA);
	mapa[ID_HUEVO] = new Imagen(ID_HUEVO);
	mapa[ID_HUEVO_ROMPIENDO1] = new Imagen(ID_HUEVO_ROMPIENDO1);
	mapa[ID_HUEVO_ROMPIENDO2] = new Imagen(ID_HUEVO_ROMPIENDO2);
	mapa[ID_HUEVO_ROMPIENDO3] = new Imagen(ID_HUEVO_ROMPIENDO3);
	mapa[ID_DOMINO] = new Imagen(ID_DOMINO);
	mapa[ID_BASE_CARRITO] = new Imagen(ID_BASE_CARRITO);
	mapa[ID_RUEDA_CARRITO] = new Imagen(ID_RUEDA_CARRITO);

	mapa[COLOR_CELESTE] = new Imagen(COLOR_CELESTE);
	mapa[COLOR_ROJO] = new Imagen(COLOR_ROJO);
	mapa[COLOR_VERDE] = new Imagen(COLOR_VERDE);
	mapa[COLOR_AMARILLO] = new Imagen(COLOR_AMARILLO);
	mapa[COLOR_ROSA] = new Imagen(COLOR_ROSA);
	mapa[COLOR_VIOLETA] = new Imagen(COLOR_VIOLETA);
	mapa[ID_GLOBO_EXPLOTANDO1] = new Imagen(ID_GLOBO_EXPLOTANDO1);
	//mapa[ID_GLOBO_EXPLOTANDO2] = new Imagen(ID_GLOBO_EXPLOTANDO2);
	//mapa[ID_GLOBO_EXPLOTANDO3] = new Imagen(ID_GLOBO_EXPLOTANDO3);

	mapa[GANO_1] = new Imagen(GANO_1);
	mapa[GANO_2] = new Imagen(GANO_2);
	mapa[GANO_3] = new Imagen(GANO_3);
	mapa[GANO_4] = new Imagen(GANO_4);
	mapa[GANO_5] = new Imagen(GANO_5);
	mapa[GANO_6] = new Imagen(GANO_6);
}

Contenedor::~Contenedor(void){
	std::map<std::string ,void*>::iterator it;
	
	for (it = mapa.begin(); it != mapa.end(); ++it){
		Imagen* img = (Imagen*) it->second; //casteandolo a Imagen*
		delete img;
	};
};

void Contenedor::pruebaContenedor(){ //no se que clase de prueba es esta

	//Imagen* img1 = new Imagen("hola que tal",12,255,255,255);
	//Imagen* img2 = new Imagen("bien2",12,250,250,250);
	//Imagen* img3 = new Imagen("hola que tal2",12,255,255,255);
	//Imagen* img4 = new Imagen("bien3",12,250,250,250);
	//Imagen* img5 = new Imagen("hola que tal3",12,255,255,255);
	//Imagen* img6 = new Imagen("bien4",12,250,250,250);
	//Imagen* img7 = new Imagen("hola que tal4",12,255,255,255);
	//Imagen* img8 = new Imagen("bien5",12,250,250,250);
	//Imagen* img9 = new Imagen("hola que tal5",12,255,255,255);
	//Imagen* img10 = new Imagen("bien6",12,250,250,250);
	//Imagen* img11 = new Imagen("hola que tal6",12,255,255,255);
	//Imagen* img12 = new Imagen("bien7",12,250,250,250);
	//Imagen* img13 = new Imagen("hola que tal7",12,255,255,255);
	//Imagen* img14 = new Imagen("bien8",12,250,250,250);
	//Imagen* img15 = new Imagen("hola que tal8",12,255,255,255);
	//Imagen* img16 = new Imagen("bien9",12,250,250,250);
	//Imagen* img17 = new Imagen("hola que tal9",12,255,255,255);
	//Imagen* img18 = new Imagen("bien10",12,250,250,250);
	//Imagen* img19 = new Imagen("hola que tal10",12,255,255,255);
	//Imagen* img20 = new Imagen("bien11",12,250,250,250);
	//Imagen* img21 = new Imagen("hola que tal11",12,255,255,255);
	//Imagen* img22 = new Imagen("bien12",12,250,250,250);

	//Contenedor::putMultimedia("hola que tal",img1);
	//Contenedor::putMultimedia("bien2",img2);
	//Contenedor::putMultimedia("hola que tal2",img3);
	//Contenedor::putMultimedia("bien3",img4);
	//Contenedor::putMultimedia("hola que tal3",img5);
	//Contenedor::putMultimedia("bien4",img6);
	//Contenedor::putMultimedia("hola que tal4",img7);
	//Contenedor::putMultimedia("bien5",img8);
	//Contenedor::putMultimedia("hola que tal5",img9);
	//Contenedor::putMultimedia("bien6",img10);
	//Contenedor::putMultimedia("hola que tal6",img11);
	//Contenedor::putMultimedia("bien7",img12);
	//Contenedor::putMultimedia("hola que tal7",img13);
	//Contenedor::putMultimedia("bien8",img14);
	//Contenedor::putMultimedia("hola que tal8",img15);
	//Contenedor::putMultimedia("bien9",img16);
	//Contenedor::putMultimedia("hola que tal9",img17);
	//Contenedor::putMultimedia("bien10",img18);
	//Contenedor::putMultimedia("hola que tal10",img19);
	//Contenedor::putMultimedia("bien11",img20);
	//Contenedor::putMultimedia("hola que tal11",img21);
	//Contenedor::putMultimedia("bien12",img22);

	//Contenedor::deleteContenedor();
};


bool Contenedor::estaMultimedia(const char* ID){

	if (cont == NULL){
		cont = new Contenedor();
	}

	if(cont->mapa.count(ID) == 0) return false;

	return true;
}