#include "CargadorYaml.h"


#define RUTA_DEFAULT "../yaml/archivoDefault.yaml"

/*
Dimension* CargadorYaml::obtener_dimension(const YAML::Node& figura,const char* tipo_dimension){

	if (tipo_dimension == "CUADRADO"){
		int ancho, alto;
		figura[0] >> ancho;
		figura[1] >> alto;
		return (new Cuadrado(ancho,alto));
	}

	return (new Dimension());

}

Figura* CargadorYaml::cargarFigura(const char* tipo_figura,const char* imagen,int posX,int posY,Dimension* dimension){

	if (tipo_figura == "CUADRADO"){
		int ancho, alto;
		figura[0] >> ancho;
		figura[1] >> alto;
		return (new Cuadrado(ancho,alto));
	}


	return (new Figura());
}

void CargadorYaml::cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno){

	std::string tipo_figura;
	std::string imagen;
	std:: string tipo_dimension;
	int posX, posY;
	for(unsigned i=0;i<listaFiguras.size();i++) {
		listaFiguras[i]["figura"] >> tipo_figura;
		listaFiguras[i]["imagen"] >> imagen;
		const YAML::Node& posicion = listaFiguras["posicion"];
		posicion["posX"] >> posX;
		posicion["posY"] >> posY;
		listaFiguras[i]["dimension"] >> tipo_dimension;
		Dimension* dimension = obtener_dimension(listaFiguras[i],tipo_dimension.c_str());
		terreno->agregarFigura(cargarFigura(tipo_figura.c_str(),imagen.c_str(),posX,posY,dimension));		
	}

}

void CargadorYaml::cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno){

	int ancho, alto;

	std::string img;
	nodoTerreno["imagen"] >> img;
	terreno->setFondo(img.c_str());
	
	const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];

	cargar_figuras(listaFiguras,terreno);

}


void CargadorYaml::cargar_botones(const YAML::Node& nodoBotonera, Botonera* botonera){

	int ancho, alto;
	nodoBotonera["ancho"] >> ancho;
	nodoBotonera["alto"] >> alto;
	
/*	const YAML::Node& listaBotones = nodoBotonera["lista_botones"];
	std::string img;
	for(unsigned i=0;i<listaBotones.size();i++) {
		listaBotones[i]["imagen"] >> img;
		Boton* boton = crearBoton(img, pos) //:P
		botonera.agregarBoton(boton);
	}

}
*/

//Abre un archivo Yaml en el que se encuentre el estado del juego guardado
bool CargadorYaml::cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	std::ifstream mi_archivo(RUTA_DEFAULT);
	YAML::Parser parser(mi_archivo);

	YAML::Node doc;
	
	parser.GetNextDocument(doc);

	//Busco el nodo raiz, al que estan asociados los demas nodos
	const YAML::Node& nodoRaiz = doc["juego"];

	//Busco los nodos asociados al juego:
	const YAML::Node& nodoBotonera = nodoRaiz["botonera"];
	const YAML::Node& nodoTerreno = nodoRaiz["terreno"];

	//Cargo la botonera	
//	cargar_botones(nodoBotonera, botonera);

	//Cargo el terreno
//	cargar_terreno(nodoTerreno,terreno);

	mi_archivo.close();

	return true;

}
