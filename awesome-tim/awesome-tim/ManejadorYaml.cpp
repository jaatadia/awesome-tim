#include "ManejadorYaml.h"
#include "Posicion.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define RUTA_DEFAULT "../yaml/archivoDefault.yaml"

//Abre un archivo Yaml en el que se encuentre el estado del juego guardado
bool ManejadorYaml::cargarJuego(const char* file,Botonera* botonera,Terreno* terreno){

	std::ifstream mi_archivo(RUTA_DEFAULT);
	YAML::Parser parser(mi_archivo);

	YAML::Node doc;
	
	parser.GetNextDocument(doc);

	//Busco el nodo raiz, al que estan asociados los demas nodos
	const YAML::Node& nodoRaiz = doc["juego"];
	std::string fondo;
	nodoRaiz["fondo"] >> fondo;
	std::cout << fondo; //Imprimo en pantalla la ruta del fondo

	const YAML::Node& nodoPos = nodoRaiz["posiciones"];
	int posX, posY;
	for(unsigned i=0;i<nodoPos.size();i++) {
		nodoPos[i]["posX"] >> posX;
		nodoPos[i]["posY"] >> posY;
		Posicion(posX,posY);
	}

	getc(stdin);
	return true;
}

bool ManejadorYaml::guardarJuego(const char* file,Botonera* botonera,Terreno* terreno){

	return false;
}