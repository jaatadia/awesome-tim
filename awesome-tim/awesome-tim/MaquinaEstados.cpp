#include "MaquinaEstados.h"
#include <iostream>

int MaquinaEstados::nroCliente = -1;

void MaquinaEstados::putMensaje(int tipo, int nroFigura, int data1, int data2){
	std::cout<<"Tipo: "<<tipo<<" Cliente Nro: "<<nroCliente<<" Numero Fig: "<<nroFigura<<" Data: "<<data1<<data2<<"\n";
	aEnviar.push_back("Mensaje\n");
}
std::list<std::string> MaquinaEstados::aEnviar = std::list<std::string>();
std::list<std::string> MaquinaEstados::aProcesar = std::list<std::string>();