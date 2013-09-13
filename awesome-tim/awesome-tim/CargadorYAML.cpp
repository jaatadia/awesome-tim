#include "CargadorYaml.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yaml"

Dimension* CargadorYaml::obtener_dimension(const YAML::Node& dimension,int tipo_dimension){

	double posX, posY,angulo;
	dimension["angulo"] >> angulo;
	dimension["posX"] >> posX;
	dimension["posY"] >> posY;

	switch(tipo_dimension){
		case CIRCULO:
			double radio;
			//xq me falta obtener el radio
			radio = 10;
			//dimension["radio"] >> radio;
			return new Circulo(radio,posX,posY,angulo);
			break;
		case CUADRADO:
			double alto, ancho;
			//xq me falta obtenerlas:
			alto = 10;
			ancho = 10;
			//dimension["alto"] >> alto;
			//dimension["ancho"] >> ancho;
			return new Cuadrado(ancho, alto, posX, posY, angulo);
			break;
		case TRIANGULO:
			double base, altura;
			//xq me faltan:
			base = 10;
			altura = 10;
			//dimension["base"] >> base;
			//dimension["altura"] >> altura;
			return new 	Triangulo(posX, posY, angulo, base, altura);
			break;
	};

	return NULL;

}
/*
Figura* CargadorYaml::cargarFigura(const char* tipo_figura,const char* imagen,int posX,int posY,Dimension* dimension){

	if (tipo_figura == "CUADRADO"){
		int ancho, alto;
		figura[0] >> ancho;
		figura[1] >> alto;
		return (new Cuadrado(ancho,alto));
	}


	return (new Figura());
}
*/

void CargadorYaml::cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno){

	std::string ID;
	int tipo_dimension;

	for(unsigned i=0;i<listaFiguras.size();i++) {
		listaFiguras[i]["ID"] >> ID;
		listaFiguras[i]["tipo_dimension"] >> tipo_dimension;
		Dimension* dimension = obtener_dimension(listaFiguras[i]["dimension"],tipo_dimension);
//		terreno->agregarFigura(cargarFigura(tipo_figura.c_str(),imagen.c_str(),posX,posY,dimension));		
	}

}

void CargadorYaml::cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno){

	//Cargo el fondo del terreno
	std::string img;
	try{
		nodoTerreno["fondo"] >> img;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar terreno. Se carga imagen de fondo default. \n"); 
		img = FONDO_TERRENO;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar terreno. Se carga imagen de fondo default. \n"); 
		img = FONDO_TERRENO;	
	}
		
	terreno->setFondo(img.c_str());
	
	//Cargo las figuras del terreno
	try{
		const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de figuras terreno. Se carga terreno sin figuras. \n");
		return;
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de figuras terreno. Se carga terreno sin figuras. \n");
		return;
	}

	const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];
	//cargar_figuras(listaFiguras,terreno);

}

/*
void CargadorYaml::cargar_botones(const YAML::Node& nodoBotonera, Botonera* botonera){

	int ancho, alto;
	nodoBotonera["ancho"] >> ancho;
	nodoBotonera["alto"] >> alto;

//	botonera->
	
	const YAML::Node& listaBotones = nodoBotonera["lista_botones"];
	std::string img;
	for(unsigned i=0;i<listaBotones.size();i++) {
		listaBotones[i]["imagen"] >> img;
		Boton* boton = crearBoton(img, pos) //:P
		botonera.agregarBoton(boton);
	}

}
*/

//Abre un archivo Yaml en el que se encuentre el estado del juego guardado
bool CargadorYaml::cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	//Abro el archivo Yaml para parsearlo.
	YAML::Node doc;
	std::ifstream mi_archivo;
	mi_archivo.open(file,std::ios::out);
	
	if(!mi_archivo.is_open()){
		mi_archivo.open(RUTA_DEFAULT,std::ios::out);
		ErrorLogHandler::addError("CargadorYaml","Error al abrir archivo de juego. Se carga archivo default. \n"); 
		if (!mi_archivo.is_open()){
			ErrorLogHandler::addError("CargadorYaml","Error al abrir archivo de juego default. \n"); 
			return false;
		}
	}
	
	try{
		YAML::Parser parser(mi_archivo);
		parser.GetNextDocument(doc);
	} catch(YAML::ParserException &e){
		ErrorLogHandler::addError("CargadorYaml","Error al parsear el archivo. Se continua con archivo default. \n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	//Busco el nodo raiz, al que estan asociados los demas nodos
	try{
		const YAML::Node& nodoRaiz = doc["juego"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo raiz juego. Se carga archivo default. \n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("cargadorYaml","No hay nodo raiz juego. Se carga archivo default. \n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoRaiz = doc["juego"];

	//Busco los nodos asociados al juego:
	
	//Busco la botonera
	try{
		const YAML::Node& nodoBotonera = nodoRaiz["botonera"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo botonera. Se carga archivo default.\n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo botonera. Se carga archivo default.\n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoBotonera = nodoRaiz["botonera"];

	//Busco nodo Terreno

	try{
		const YAML::Node& nodoBotonera = nodoRaiz["terreno"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo terreno. Se carga archivo default.\n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo terreno. Se carga archivo default.\n"); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoTerreno = nodoRaiz["terreno"];

	//Cargo la botonera	
	//cargar_botones(nodoBotonera, botonera);

	//Cargo el terreno
	cargar_terreno(nodoTerreno,terreno);

	mi_archivo.close();

	return true;

}