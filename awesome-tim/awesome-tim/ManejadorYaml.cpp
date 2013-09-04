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

	const YAML::Node& nodoRaiz = doc["juego"];
	std::string autor;
	nodoRaiz["autor"] >> autor;
	std::cout << autor;

	const YAML::Node& nodoPos = nodoRaiz["posiciones"];
	int posX, posY;
	for(unsigned i=0;i<nodoPos.size();i++) {
		nodoPos[i]["posX"] >> posX;
		nodoPos[i]["posY"] >> posY;
		std::cout << posX;
		std::cout << posY;
		Posicion(posX,posY);
	}

	getc(stdin);
	return true;
}

bool ManejadorYaml::guardarJuego(const char* file,Botonera* botonera,Terreno* terreno){

	return false;
}