#include "ErrorLogHandler.h"
#include <ctime>

ErrorLogHandler* ErrorLogHandler::logHandler = NULL; //inicializo el puntero estatico en null

void ErrorLogHandler::addError(const char* tag, const char* error){
		if(logHandler == NULL){ //si no se creo el singleton lo creo
			logHandler = new ErrorLogHandler();
		}
		logHandler->addErrorRecord(tag,error);
}

void ErrorLogHandler::closeLog(){
	if(logHandler!=NULL)delete logHandler; //eliminacion del singleton que conlleva a la terminacion de la generacion del archivo
}


//devuelve la fecha en formato en el buffer de tamanio size "nombre de dia" "nombre de mes" "numero de dia" "anyo"
void ErrorLogHandler::getDate(char* buffer,size_t size){
	
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);

	strftime (buffer,size,"%a %b %d %Y",&timeinfo);
}

//devuelve la fecha en formato en el buffer de tamanio size "hh:mm:ss"
void ErrorLogHandler::getHour(char* buffer,size_t size){
	
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);

	strftime (buffer,size,"%X",&timeinfo);
}

//constructor que incializa el estado de variables internas 
ErrorLogHandler::ErrorLogHandler()
{
	myFile.open(ERROR_FILE,std::ios::app); //abro el archivo en donde se van a imprimir los errores
	iniciar(); //si se crea es por que se necesita escribir algo, en caso contrario no se crea
}

//destructor que llama a los metodos para terminar de escribir cosas y cerrar el archivo
ErrorLogHandler::~ErrorLogHandler()
{
	finalizar(); //se agregan las lineas de finalizacion
	if(myFile.is_open())myFile.close(); //se cierra el archivo donde se escribieron los errores
}


//se agrega al registro la informacion del error pasado
void ErrorLogHandler::addErrorRecord(const char* tag,const char* error){
	if(myFile.is_open()){
		char time[80];
		getHour(time,80);

		myFile << time <<" IN: " << tag <<" ERROR: "<< error <<"\n";
	};
}


//Inicializa la cabezera de la secion del archivo de errores poniendo fecha y otros datos necesarios
void ErrorLogHandler::iniciar(){
	if(myFile.is_open()){
		char buffer[80];
		getDate(buffer,80);
		myFile << "-----------------------------------\n";
		myFile << buffer <<"\n";
	};
}

//escribe la terminacion del archivo
void ErrorLogHandler::finalizar(){
	if(myFile.is_open()){
		myFile << "------------------------------------\n";
	}
}