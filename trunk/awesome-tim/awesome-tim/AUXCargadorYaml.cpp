#include "AUXCargadorYaml.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yml"

#define CANT_CAR 40

std::string AUXCargadorYaml::ruta_archivo = "";

void AUXCargadorYaml::obtenerPosicion(const YAML::Node& nodoFigura, double* posX, double* posY){

	try{
		nodoFigura["posX"] >> *posX;
		nodoFigura["posY"] >> *posY;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Posicion de figura no esta definida. Se carga posicion por defecto.",e.what());
		*posX = POSX_DEFAULT;
		*posY = POSY_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo en Posicion de figura. Se carga posicion por defecto.",e.what());
		*posX = POSX_DEFAULT;
		*posY = POSY_DEFAULT;
	}

	if(!posicion_validaX(*posX)){
		int linea = nodoFigura["posX"].GetMark().line;
		imprimir_error_linea("Posicion X de Figura invalida. Se carga posicion X por defecto.",linea);
		*posX = POSX_DEFAULT;
	}

	if(!posicion_validaY(*posY)){
		int linea = nodoFigura["posY"].GetMark().line;
		imprimir_error_linea("Posicion Y de Figura invalida. Se carga posicion Y por defecto.",linea);
		*posY = POSY_DEFAULT;
	}
}

void AUXCargadorYaml::obtenerAngulo(const YAML::Node& nodoFigura, double* angulo){
	try{
		nodoFigura["angulo"] >> *angulo;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe angulo de figura. Se carga angulo por defecto en 0 grados.",e.what());
		*angulo = ANGULO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del angulo de figura. Se carga angulo por defecto en 0 grados.",e.what());
		*angulo = ANGULO_DEFAULT;
	}

	if(!angulo_valido(*angulo)){
		int linea = nodoFigura["angulo"].GetMark().line;
		imprimir_error_linea("Angulo de Figura invalido. Se carga angulo por defecto en 0 grados.", linea);
		*angulo = ANGULO_DEFAULT;
	}
}

void AUXCargadorYaml::obtenerID(const YAML::Node& nodoFigura, std::string* ID){

	try{
		nodoFigura["ID"] >> *ID;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("AUXCargadorYaml","Error al cargar ID de figura. La figura no tendra imagen."); 
		ErrorLogHandler::addError("AUXCargadorYaml: ",e.what()); 
		*ID = ID_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("AUXCargadorYaml","Error al cargar ID de figura. La figura no tendra imagen."); 
		ErrorLogHandler::addError("AUXCargadorYaml: ",e.what()); 
		*ID = ID_DEFAULT;
	}
}


Figura* AUXCargadorYaml::crearBalancin(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearPoligono(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearPlataforma(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearCirculo(const YAML::Node& nodoFigura){
	
	double posX,posY,angulo;
	std::string ID;
	
	obtenerAngulo(nodoFigura,&angulo);

	obtenerPosicion(nodoFigura,&posX,&posY);

	obtenerID(nodoFigura,&ID);

	//FIXME: Circulo la pusieron como clase abstracta xq hicieron heredar a pelota de ahi, eso hay que cambiarlo.
	//return new Figura(ID.c_str(), new Circulo(RADIO_DEFAULT,posX,posY,angulo));
	return new Figura(ID.c_str(), new PelotaBasquet(RADIO_DEFAULT,posX,posY,angulo));
}

Figura* AUXCargadorYaml::crearCuadrado(const YAML::Node& nodoFigura){

	double posX, posY,angulo;
	std::string ID;

	obtenerAngulo(nodoFigura,&angulo);

	obtenerPosicion(nodoFigura,&posX,&posY);

	obtenerID(nodoFigura, &ID);

	return new Figura(ID.c_str(),new Cuadrado(ANCHO_DEFAULT,ALTO_DEFAULT,posX,posY,angulo));
}

Figura* AUXCargadorYaml::crearFigura(const YAML::Node& nodoFigura, const char* tipo_figura){

	if (strcmp(tipo_figura,"CUADRADO") == 0){
		Figura* figura = crearCuadrado(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Cuadrada."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CIRCULO") == 0){
		Figura* figura = crearCirculo(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Circular."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"POLIGONOREGULAR") == 0){
		Figura* figura = crearPoligono(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Poligono Regular."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"BALANCIN") == 0){
		Figura* figura = crearBalancin(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Balancin."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"PLATAFORMA") == 0){
		Figura* figura = crearPlataforma(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Plataforma."); 	
		return figura;
	}

	//No deberia llegar a este caso porque el error deberia haber saltado antes.
	ErrorLogHandler::addError("AUXCargadorYaml","Error del tipo figura. El tipo de figura no es un tipo valido."); 	
	return NULL;
}

Figura* AUXCargadorYaml::cargar_figura(const YAML::Node& nodoFig){

	std::string tipo_figura;

	try{
		nodoFig["tipo_figura"] >> tipo_figura;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Error al cargar el tipo de figura. La figura no sera cargada.",e.what());
		return NULL;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Error al cargar el tipo de figura. La figura no sera cargada.",e.what());
		return NULL;
	}

	if(!tipo_figura_valida(tipo_figura.c_str())){
		int linea = nodoFig["tipo_figura"].GetMark().line;
		imprimir_error_linea("Tipo de figura invalida. La figura no sera cargada.",linea);
		return NULL;
	}

	Figura* figura = crearFigura(nodoFig,tipo_figura.c_str());

	if(!figura){
		if (figura) delete(figura);
		ErrorLogHandler::addError("AUXCargadorYaml","No se pudo crear la figura. La figura no sera cargada.");
	}

	return figura;
}

void AUXCargadorYaml::cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno){

	//Cargo el fondo del terreno
	std::string img;
	try{
		nodoTerreno["fondo"] >> img;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Error al cargar terreno. Se carga imagen de fondo default.",e.what());
		img = FONDO_TERRENO;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Error al cargar terreno. Se carga imagen de fondo default.",e.what());
		img = FONDO_TERRENO;	
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!terreno->setFondo(img.c_str())){
		int linea = nodoTerreno["fondo"].GetMark().line;
		imprimir_error_linea("Fondo de terreno invalido. Se carga imagen de fondo default.",linea);
		img = FONDO_TERRENO;
		terreno->setFondo(img.c_str());
	}

	//Cargo las figuras del terreno
	try{
		const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Error al cargar lista de figuras terreno. Se carga terreno sin figuras.",e.what());
		return;
	}catch(YAML::BadDereference &e){
		imprimir_error_excepcion("Error al cargar lista de figuras terreno. Se carga terreno sin figuras.",e.what());
		return;
	}

	const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];

	for(unsigned i=0;i<listaFiguras.size();i++) {
	
		Figura* fig = cargar_figura(listaFiguras[i]);

		if (!fig) continue;
		
		terreno->agregarFigura(fig);	
	}
}

void AUXCargadorYaml::cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera){

	try{
		const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Error al cargar lista de botones de la Botonera. Se carga botonera con botones por defecto.",e.what());
		botonera->agregarBotonesDefault();
		return;
	}catch(YAML::BadDereference &e){
		imprimir_error_excepcion("Error al cargar lista de botones de la Botonera. Se carga botonera con botones por defecto.",e.what());
		botonera->agregarBotonesDefault();
		return;
	}

	const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	
	if (listaFiguras.size() == 0) {
		imprimir_error_linea("La lista de figuras de la botonera se encuentra vacia. Se carga botonera con botones por defecto.",listaFiguras.GetMark().line);
		botonera->agregarBotonesDefault();
	};
	int cant_botones = 0;
	for(unsigned i=0;i<listaFiguras.size();i++) {
		
		int instancias;
	
		try {
			const YAML::Node& nodoFig = listaFiguras[i]["figura"];
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			imprimir_error_excepcion("No se encontro el nodo figura. El boton no sera cargado",e.what());
			continue;
		}catch(YAML::InvalidScalar &e){
			imprimir_error_excepcion("No se encontro el nodo figura. El boton no sera cargado",e.what());
			continue;
		}

		const YAML::Node& nodoFig = listaFiguras[i]["figura"];
		Figura* fig = cargar_figura(nodoFig);
		
		if (!fig) continue;
		
		try{
			listaFiguras[i]["cantidad_de_instancias"] >> instancias;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			imprimir_error_excepcion("No se encontro el nodo cantidad de instancias. Se cargan instancias por defecto.",e.what());
			instancias = INSTANCIAS_DEFAULT;
		}catch(YAML::InvalidScalar &e){
			imprimir_error_excepcion("Cantidad de instancias invalida. Se carga cantidad de instancias por defecto.",e.what());
			instancias = INSTANCIAS_DEFAULT;		
		}

		if(!cant_instancias_valida(instancias)){
			int linea = listaFiguras[i]["cantidad_de_instancias"].GetMark().line;
			imprimir_error_linea("Cantidad de instancias invalida. Se carga cantidad de instancias por defecto.",linea);
			instancias = INSTANCIAS_DEFAULT;
		};
		
		botonera->agregarBoton(fig,instancias);
		cant_botones++;
	};
	if (cant_botones == 0){
		imprimir_error_linea("Las figuras de los botones no fueron cargadas. Se cargan botones por defecto",listaFiguras.GetMark().line);
		botonera->agregarBotonesDefault();
	};
}


/**********************************************************
**                                                       **
**                      CARGADOR                         **
**                                                       **
**********************************************************/
bool AUXCargadorYaml::cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	//Abro el archivo Yaml para parsearlo.
	YAML::Node doc;
	std::ifstream mi_archivo;
	mi_archivo.open(file,std::ios::in);
	ruta_archivo = string(file);
	
	if(!mi_archivo.is_open()){
		mi_archivo.open(RUTA_DEFAULT,std::ios::out);
		AUXCargadorYaml::imprimir_error_sin_linea("No se encontro el abrir archivo de juego indicado. Se carga archivo default.");
		if (!mi_archivo.is_open()){
			ErrorLogHandler::addError("AUXCargadorYaml","Error al abrir archivo de juego default."); 
			return false;
		}
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}
	
	try{
		YAML::Parser parser(mi_archivo);
		parser.GetNextDocument(doc);
	} catch(YAML::ParserException &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("Error al parsear el archivo. Se continua con archivo default.",e.what());
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("Error al parsear el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}

	//Busco el nodo raiz, al que estan asociados los demas nodos
	try{
		const YAML::Node& nodoRaiz = doc["juego"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("No se encontro nodo raiz juego. Se carga archivo default.",e.what());
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("No se encontro nodo raiz juego en el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}catch(YAML::BadDereference &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("No hay nodo raiz juego. Se carga archivo default.",e.what());
			std::cout << e.what();
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("No hay nodo raiz juego en el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}

	const YAML::Node& nodoRaiz = doc["juego"];

	//Busco la botonera
	try{
		const YAML::Node& nodoBotonera = nodoRaiz["botonera"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("No se encontro nodo botonera. Se carga archivo default.",e.what());
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("No se encontro nodo botonera en el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}catch(YAML::BadDereference &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("No se encontro nodo botonera. Se carga archivo default.",e.what()); 
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("No se encontro nodo botonera en el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}

	const YAML::Node& nodoBotonera = nodoRaiz["botonera"];

	//Busco nodo Terreno

	try{
		const YAML::Node& nodoBotonera = nodoRaiz["terreno"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("No se encontro nodo terreno. Se carga archivo default.",e.what()); 
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("No se encontro nodo terreno en el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}catch(YAML::BadDereference &e){
		if(file != RUTA_DEFAULT) {
			imprimir_error_excepcion("No se encontro nodo terreno. Se carga archivo default.",e.what()); 
			mi_archivo.close();
			return cargarJuego(RUTA_DEFAULT,botonera,terreno);
		} else {
			imprimir_error_excepcion("No se encontro nodo terreno en el archivo default.",e.what());
			mi_archivo.close();
			return false;
		}
	}

	const YAML::Node& nodoTerreno = nodoRaiz["terreno"];

	//Cargo la botonera	
	cargar_botones(nodoBotonera,botonera);

	//Cargo el terreno
	cargar_terreno(nodoTerreno,terreno);

	mi_archivo.close();

	return true;

}

/**********************************************************
**                                                       **
**                    VALIDACIONES                       **
**                                                       **
**********************************************************/
bool AUXCargadorYaml::tipo_figura_valida(const char* tipo_figura){
	bool cuadrado = (strcmp(tipo_figura,"CUADRADO") == 0);
	bool circulo = (strcmp(tipo_figura,"CIRCULO") == 0);
	bool poligono = (strcmp(tipo_figura,"POLIGONOREGULAR") == 0);
	bool plataforma = (strcmp(tipo_figura,"PLATAFORMA") == 0);
	bool balancin = (strcmp(tipo_figura,"BALANCIN") == 0);
	return (cuadrado || circulo || poligono || plataforma || balancin);
}

bool AUXCargadorYaml::posicion_validaX(double posX){
	return ((posX >= 0) && (posX <= ANCHO_TERRENO_LOGICO)); //menor estricto o no???
}

bool AUXCargadorYaml::posicion_validaY(double posY){
	return ((posY >= 0) && (posY <= ALTO_TERRENO_LOGICO)); //menor estricto o no???;
}

bool AUXCargadorYaml::angulo_valido(double angulo){
	return ((angulo >=0) && (angulo < 360));
}

bool AUXCargadorYaml::cant_instancias_valida(int instancias){
	return (instancias >= 0);
}

/**********************************************************
**                                                       **
**                    IMPRESIONES                        **
**                                                       **
**********************************************************/

std::string AUXCargadorYaml::concatenar_archivo(std::string mensaje, int linea, std::string archivo){
	char buffer[CANT_CAR];
	itoa(linea,buffer,10);//el ultimo valor es la base
	std::string line = string(buffer);
	std::string msj = mensaje + " Error en archivo Yaml: " + archivo + " - Linea nro: " + line; 
	return msj;
}

std::string AUXCargadorYaml::concatenar_archivo(std::string mensaje, std::string archivo){
	std::string msj = mensaje + " Error en archivo Yaml: " + archivo; 
	return msj;
}

void AUXCargadorYaml::imprimir_error_linea(std::string mensaje, int linea){
	linea = linea + 1; //Porque empieza a contar en 0
	std::string msj = AUXCargadorYaml::concatenar_archivo(mensaje,linea,ruta_archivo);
	ErrorLogHandler::addError("AUXCargadorYaml",msj.c_str());
}

void AUXCargadorYaml::imprimir_error_sin_linea(std::string mensaje){
	std::string msj = AUXCargadorYaml::concatenar_archivo(mensaje,ruta_archivo);
	ErrorLogHandler::addError("AUXCargadorYaml",msj.c_str());
}
void AUXCargadorYaml::imprimir_error_excepcion(std::string mensaje,std::string what){
	std::string msj = AUXCargadorYaml::concatenar_archivo(mensaje,ruta_archivo);
	std::string full_msj = msj + what;
	ErrorLogHandler::addError("AUXCargadorYaml",full_msj.c_str());
}

/**********************************************************
**                                                       **
**                       PRUEBAS                         **
**                                                       **
**********************************************************/

void AUXCargadorYaml::pruebaCargador(){

	BotoneraController* bot = new BotoneraController(20,20,3);
	Terreno* terr = new Terreno(80,80);

	//habria q imprimir en el error el nombre del archivo que no se pudo cargar, no?
	AUXCargadorYaml::cargarJuego("../yaml/testcargar.yml",bot,terr); //no existe archivo
	AUXCargadorYaml::cargarJuego("../yaml/testsinNodoJuego.yml",bot,terr); 
	AUXCargadorYaml::cargarJuego("../yaml/testvacio.yml",bot,terr); //arch vacio
	AUXCargadorYaml::cargarJuego("../yaml/testsinTerreno.yml",bot,terr);
	AUXCargadorYaml::cargarJuego("../yaml/testsinBotonera.yml",bot,terr);
	AUXCargadorYaml::cargarJuego("../yaml/testterrenoVacio.yml",bot,terr);

}