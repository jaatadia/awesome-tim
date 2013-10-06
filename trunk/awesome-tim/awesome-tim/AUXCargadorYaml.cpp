#include "AUXCargadorYaml.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yml"

#define CANT_CAR 40

std::string AUXCargadorYaml::ruta_archivo = "";

/**********************************************************
**                                                       **
**                OBTENER PARAMETROS                     **
**                                                       **
**********************************************************/

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

	Imagen* img = new Imagen((*ID).c_str());
	if (img->huboFallos()) {
		int linea = nodoFigura["ID"].GetMark().line;
		imprimir_error_linea("No se pudo crear la imagen, ID invalido. La figura no tendra imagen.",linea);
	}
	Contenedor::putMultimedia((*ID).c_str(),img);

}

void AUXCargadorYaml::obtenerLargo(const YAML::Node& nodoFigura, double* largo){
	try{
		nodoFigura["largo"] >> *largo;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe largo de figura. Se carga largo por defecto.",e.what());
		*largo = LARGO_PLATAFORMA_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del largo de figura. Se carga largo por defecto.",e.what());
		*largo = LARGO_PLATAFORMA_DEFAULT;
	}

	if(!largo_valido(*largo)){
		int linea = nodoFigura["largo"].GetMark().line;
		imprimir_error_linea("Largo de Figura invalido. Se carga largo por defecto.", linea);
		*largo = LARGO_PLATAFORMA_DEFAULT;
	}
}
void AUXCargadorYaml::obtenerBaseTriangulo(const YAML::Node& nodoFigura, double* base){
	try{
		nodoFigura["base"] >> *base;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe base de figura. Se carga base por defecto.",e.what());
		*base = BASE_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de base de figura. Se carga base por defecto.",e.what());
		*base = BASE_DEFAULT;
	}

	if(!base_triangulo_valida(*base)){
		int linea = nodoFigura["base"].GetMark().line;
		imprimir_error_linea("Base de Figura invalida. Se carga base por defecto.", linea);
		*base = BASE_DEFAULT;
	}
}

void AUXCargadorYaml::obtenerAlto(const YAML::Node& nodoFigura, double* alto){
	try{
		nodoFigura["alto"] >> *alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe alto de figura. Se carga alto por defecto.",e.what());
		*alto = ALTO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del alto de figura. Se carga alto por defecto.",e.what());
		*alto = ALTO_DEFAULT;
	}

	if(!alto_valido(*alto)){
		int linea = nodoFigura["alto"].GetMark().line;
		imprimir_error_linea("Alto de Figura invalido. Se carga alto por defecto.", linea);
		*alto = ALTO_DEFAULT;
	}
}

void AUXCargadorYaml::obtenerAncho(const YAML::Node& nodoFigura, double* ancho){
	try{
		nodoFigura["ancho"] >> *ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe ancho de figura. Se carga ancho por defecto.",e.what());
		*ancho = ANCHO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del ancho de figura. Se carga ancho por defecto.",e.what());
		*ancho = ANCHO_DEFAULT;
	}

	if(!ancho_valido(*ancho)){
		int linea = nodoFigura["ancho"].GetMark().line;
		imprimir_error_linea("Ancho de Figura invalido. Se carga ancho por defecto.", linea);
		*ancho = ANCHO_DEFAULT;
	}
}

void AUXCargadorYaml::obtenerRadio(const YAML::Node& nodoFigura,double* radio){
	try{
		nodoFigura["radio"] >> *radio;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe radio de figura. Se carga radio por defecto.",e.what());
		*radio = RADIO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del radio de figura. Se carga radio por defecto.",e.what());
		*radio = RADIO_DEFAULT;
	}

	if(!radio_valido(*radio)){
		int linea = nodoFigura["radio"].GetMark().line;
		imprimir_error_linea("Radio de Figura invalido. Se carga radio por defecto.", linea);
		*radio = RADIO_DEFAULT;
	}
}

void AUXCargadorYaml::obtenerVertices(const YAML::Node& nodoFigura,int* vertices){
	try{
		nodoFigura["cant_vertices"] >> *vertices;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe cant_vertices de figura. Se carga cantidad de vertices por defecto.",e.what());
		*vertices = VERTICES_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de la cantidad de vertices de figura. Se carga cantidad por defecto.",e.what());
		*vertices = VERTICES_DEFAULT;
	}

	if(!cant_vertices_valida(*vertices)){
		int linea = nodoFigura["cant_vertices"].GetMark().line;
		imprimir_error_linea("Cantidad de Vertices de Figura invalida. Se carga cantidad por defecto.", linea);
		*vertices = VERTICES_DEFAULT;
	}
}

/**********************************************************
**                                                       **
**                    CREAR FIGURAS                      **
**                                                       **
**********************************************************/
Figura* AUXCargadorYaml::crearGloboHelio(const YAML::Node& nodoFigura){
	//FIXME: GLOBO de HELIO no deberia ser una dimension sino una figura
	double posX,posY,radio,angulo;
	std::string ID;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerRadio(nodoFigura,&radio);
	obtenerID(nodoFigura, &ID);

	return new Figura(ID.c_str(), new GloboHelio(radio,posX,posY,angulo));
}

Figura* AUXCargadorYaml::crearBolaBowling(const YAML::Node& nodoFigura){
	//FIXME: BOLA DE BOWLING no deberia ser una dimension sino una figura
	double posX,posY,radio,angulo;
	std::string ID;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerRadio(nodoFigura,&radio);
	obtenerID(nodoFigura, &ID);

	return new Figura(ID.c_str(), new PelotaBowling(radio,posX,posY,angulo));
}

Figura* AUXCargadorYaml::crearPelotaBasquet(const YAML::Node& nodoFigura){
	//FIXME: PELOTA DE BASQUET no deberia ser una dimension sino una figura
	double posX,posY,radio,angulo;
	std::string ID;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerRadio(nodoFigura,&radio);
	obtenerID(nodoFigura, &ID);

	return new Figura(ID.c_str(), new PelotaBasquet(radio,posX,posY,angulo));
}

Figura* AUXCargadorYaml::crearMotor(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearSoga(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearCorrea(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearEngranaje(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearCintaTransportadora(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* AUXCargadorYaml::crearBalancin(const YAML::Node& nodoFigura){
	return NULL;
}


Figura* AUXCargadorYaml::crearTriangulo(const YAML::Node& nodoFigura){
	double posX,posY,angulo,base,altura;
	std::string ID;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerBaseTriangulo(nodoFigura,&base);
	obtenerAlto(nodoFigura,&altura);
	obtenerID(nodoFigura,&ID);

	return new Figura(ID.c_str(), new Triangulo(posX,posY,angulo,base,altura));
}

Figura* AUXCargadorYaml::crearPoligono(const YAML::Node& nodoFigura){

	double posX,posY,angulo,radio;
	int vertices;
	std::string ID;

	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerID(nodoFigura,&ID);
	obtenerRadio(nodoFigura,&radio);
	obtenerVertices(nodoFigura,&vertices);

	return new Figura(ID.c_str(), new PoligonoRegular(posX,posY,radio,vertices,angulo));
}

Figura* AUXCargadorYaml::crearPlataforma(const YAML::Node& nodoFigura){
	double posX,posY,angulo,largo;

	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerLargo(nodoFigura, &largo);

	return new Plataforma(largo,posX,posY,angulo);
}

Figura* AUXCargadorYaml::crearCirculo(const YAML::Node& nodoFigura){
	
	double posX,posY,angulo,radio;
	std::string ID;
	
	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerID(nodoFigura,&ID);
	obtenerRadio(nodoFigura,&radio);

	//FIXME: Circulo la pusieron como clase abstracta xq hicieron heredar a pelota de ahi, eso hay que cambiarlo.
	//return new Figura(ID.c_str(), new Circulo(radio,posX,posY,angulo));
	return new Figura(ID.c_str(), new PelotaBasquet(radio,posX,posY,angulo));
}

Figura* AUXCargadorYaml::crearCuadrado(const YAML::Node& nodoFigura){

	double posX, posY,angulo,ancho,alto;
	std::string ID;

	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAncho(nodoFigura,&ancho);
	obtenerAlto(nodoFigura,&alto);
	obtenerID(nodoFigura, &ID);

	return new Figura(ID.c_str(),new Cuadrado(ancho,alto,posX,posY,angulo));
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

	if (strcmp(tipo_figura,"TRIANGULO") == 0){
		Figura* figura = crearTriangulo(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Triangular."); 	
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

	if (strcmp(tipo_figura,"CINTA_TRANSPORTADORA") == 0){
		Figura* figura = crearCintaTransportadora(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Cinta Transportadora."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"ENGRANAJE") == 0){
		Figura* figura = crearEngranaje(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Engranaje."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CORREA") == 0){
		Figura* figura = crearCorrea(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Correa."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"SOGA") == 0){
		Figura* figura = crearCorrea(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Soga."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"MOTOR") == 0){
		Figura* figura = crearMotor(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Motor."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"PELOTA_BASQUET") == 0){
		Figura* figura = crearMotor(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Pelota de Basquet."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"BOLA_BOWLING") == 0){
		Figura* figura = crearBolaBowling(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Bola de Bowling."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"GLOBO_HELIO") == 0){
		Figura* figura = crearGloboHelio(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("AUXCargadorYaml","Error al crear figura Globo de Helio."); 	
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
	
		Figura* fig = cargar_figura(listaFiguras[i]["figura"]);

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
	bool triangulo = (strcmp(tipo_figura,"TRIANGULO") == 0);
	bool poligono = (strcmp(tipo_figura,"POLIGONOREGULAR") == 0);

	bool figuraSimple = (cuadrado || circulo || triangulo || poligono);

	bool plataforma = (strcmp(tipo_figura,"PLATAFORMA") == 0);
	bool balancin = (strcmp(tipo_figura,"BALANCIN") == 0);
	bool cintaTrans = (strcmp(tipo_figura,"CINTA_TRANSPORTADORA") == 0);
	bool engranaje = (strcmp(tipo_figura,"ENGRANAJE") == 0);
	bool correa = (strcmp(tipo_figura,"CORREA") == 0);
	bool soga = (strcmp(tipo_figura,"SOGA") == 0);
	bool motor = (strcmp(tipo_figura,"MOTOR") == 0);
	bool pelotaBask = (strcmp(tipo_figura,"PELOTA_BASQUET") == 0);
	bool bowling = (strcmp(tipo_figura,"BOLA_BOWLING") == 0);
	bool globoHelio = (strcmp(tipo_figura,"GLOBO_HELIO") == 0);

	bool figuraCompleja = (plataforma || balancin || cintaTrans || engranaje || correa || soga || motor || pelotaBask || bowling || globoHelio);

	return (figuraSimple || figuraCompleja);
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

bool AUXCargadorYaml::largo_valido(double largo){
	//FIXME: cuando es un largo valido?
	return ancho_valido(largo);
}

bool AUXCargadorYaml::alto_valido(double alto){
	return ((alto > 0) && (alto < ALTO_TERRENO_LOGICO));
}

bool AUXCargadorYaml::ancho_valido(double ancho){
	return ((ancho > 0) && (ancho < ANCHO_TERRENO_LOGICO));
}

bool AUXCargadorYaml::base_triangulo_valida(double base){
	return ancho_valido(base);
}

bool AUXCargadorYaml::radio_valido(double radio){
	return ((radio > 0) && (radio < ANCHO_TERRENO_LOGICO));
}

bool AUXCargadorYaml::cant_vertices_valida(int cant){
	return ((cant >= 3) && (cant < 100));
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

