#include "GeneradorYaml.h"
#include "Botonera.h"
#include "Terreno.h"
#include "Figura.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include <iostream>
#include <fstream>


bool GeneradorYaml::guardarJuego(const char* file,Botonera* botonera,Terreno* terreno){

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

int GeneradorYaml::pruebayaml(){

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