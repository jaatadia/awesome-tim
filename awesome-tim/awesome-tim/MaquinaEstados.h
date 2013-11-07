#pragma once
#include <list>
#include <string>

class Terrreno;

class MaquinaEstados
{
public:
	static std::list<std::string> aEnviar;
	static std::list<std::string> aProcesar;
	static int nroCliente;
	static void putMensaje(int tipo,int nroFigura,int data1,int data2);

public:
	virtual ~MaquinaEstados(){};
	virtual void salir()=0;
	virtual void editor()=0;
	virtual void play(void* ter)=0;
};