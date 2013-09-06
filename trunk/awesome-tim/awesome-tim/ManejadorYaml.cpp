#include "ManejadorYaml.h"
#include "Posicion.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define RUTA_DEFAULT "../yaml/archivoDefault.yaml"

	/*
Dimension* ManejadorYaml::obtener_dimension(const YAML::Node& figura,const char* tipo_dimension){

	if (tipo_dimension == "CUADRADO"){
		int ancho, alto;
		figura[0] >> ancho;
		figura[1] >> alto;
		return (new Cuadrado(ancho,alto));
	}

	return (new Dimension());

}

Figura* ManejadorYaml::cargarFigura(const char* tipo_figura,const char* imagen,int posX,int posY,Dimension* dimension){

	if (tipo_figura == "CUADRADO"){
		int ancho, alto;
		figura[0] >> ancho;
		figura[1] >> alto;
		return (new Cuadrado(ancho,alto));
	}


	return (new Figura());
}

void ManejadorYaml::cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno){

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

void ManejadorYaml::cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno){

	int ancho, alto;

	std::string img;
	nodoTerreno["imagen"] >> img;
	terreno->setFondo(img.c_str());
	
	const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];

	cargar_figuras(listaFiguras,terreno);

}


void ManejadorYaml::cargar_botones(const YAML::Node& nodoBotonera, Botonera* botonera){

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
bool ManejadorYaml::cargarJuego(const char* file,Botonera* botonera,Terreno* terreno){

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


bool ManejadorYaml::guardarJuego(const char* file,Botonera* botonera,Terreno* terreno){

	return false;
}


YAML::Emitter& operator << (YAML::Emitter& out,Figura* fig){
/*out << YAML::BeginMap;
out << YAML::Key << "x";
out << YAML::Value << posicion.getX();
out << YAML::Key << "y";
out << YAML::Value << posicion.getY();
out << YAML::EndMap;*/
return out;
};

int pruebayaml(){

Cuadrado* dim_cuad = new Cuadrado(10,10,3,3,60);
Circulo* dim_circ = new Circulo(5,30,40,9);
Figura* fig1 = new Figura("../img/Cuadrado.jpg",dim_cuad);
Figura* fig2 = new Figura("../img/Circulo.jpg",dim_circ);


std::list<Figura*> lista_fig = std::list<Figura*>();
lista_fig.push_back(fig1);
lista_fig.push_back(fig2);


//creacion del arhchivo
std::ofstream arch;
arch.open("GameState.yaml",std::ios::out);

//creacion del emiter
YAML::Emitter out;

//llenar el emiter con lo que nos interesa
out << YAML::BeginDoc;
//out;


//pasar el emiter al archivo
arch << out.c_str() << "\n";

//cerrar el archivo
arch.close();

delete dim_cuad;
delete dim_circ;
delete fig1;
delete fig2;

return 0;
}