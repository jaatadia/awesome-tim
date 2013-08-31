#pragma once

#include <fstream>
#include <iostream>

#define ERROR_FILE "../logs/errorlog.txt"

/* Ejemplo de uso: 

	1-la funcion foobar llama al metodo foo que puede lanzar una excepcion cualquiera

	void foobar(){
		try{
			foo();
		}catch(...){
			ErrorLogHandler::addError("foobar","excepcion al utilizar el metodo foo");
		}
		bar();
	
	}
	
	2-otro caso:
	int foobar(){
		int aux = bar();
		if(aux == -1) ErrorLogHandler::addError("foobar","bar se rompio");
		return aux;
	}


	seria bueno que en cada clase en la que se llame se definan constantes en ves de pasar asi alegremente char*

	antes de cerrar el programa se debe llamar para liberar memoria y cerrar el archivo de log a:
	
	ErrorLogHandler::closeLog();
	

*/


class ErrorLogHandler{

private:
	static ErrorLogHandler* logHandler; //puntero para implementacion del singleton

public:
	static void addError(const char* tag, const char* error); //agrega el error bajo indicando que se produjo en tag
	static void closeLog();//finalizacion del log

private:
	static void getDate(char* buffer,size_t size);//devuelve la fecha en formato en el buffer de tamanio size "nombre de dia" "nombre de mes" "numero de dia" "anyo"
	static void getHour(char* buffer,size_t size);//devuelve la fecha en formato en el buffer de tamanio size "hh:mm:ss"

private: 
	std::ofstream myFile;//file stream del singleton
	
private:
	ErrorLogHandler();//constructor que incializa el estado de variables internas 
	~ErrorLogHandler();//destructor que llama a los metodos para terminar de escribir cosas y cerrar el archivo
	void addErrorRecord(const char* tag,const char* error);//se agrega al registro la informacion del error pasado
	void iniciar();//Inicializa la cabezera de la secion del archivo de errores poniendo fecha y otros datos necesarios
	void finalizar();//escribe la terminacion del archivo
};
