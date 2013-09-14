#include "CargadorYaml.h"
#include "ErrorLogHandler.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yaml"

Dimension* CargadorYaml::crearCirculo(const YAML::Node& dimension, double angulo,double posX,double posY){
	double radio;	
	try{
		dimension["radio"] >> radio;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No existe radio de dimension circulo. Se carga radio por defecto. \n"); 
		radio = RADIO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del radio de dimension circulo. Se carga radio por defecto. \n"); 
		radio = RADIO_DEFAULT;
	}
	
	Dimension* dim = new Circulo(radio,posX,posY,angulo);
	
	if(!dim)
		ErrorLogHandler::addError("CargadorYaml","Error al crear la dimension Circulo. \n"); 
	
	return dim;

}

Dimension* CargadorYaml::crearCuadrado(const YAML::Node& dimension, double angulo,double posX,double posY){
	double ancho, alto;	
	try{
		dimension["ancho"] >> ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No existe ancho de dimension cuadrado. Se carga ancho por defecto. \n"); 
		ancho = ANCHO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del ancho de dimension cuadrado. Se carga ancho por defecto. \n"); 
		ancho = ANCHO_DEFAULT;
	}

	try{
		dimension["alto"] >> alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No existe alto de dimension cuadrado. Se carga alto por defecto. \n"); 
		alto = ALTO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del alto de dimension cuadrado. Se carga alto por defecto. \n"); 
		alto = ALTO_DEFAULT;
	}

	Dimension* dim = new Cuadrado(ancho,alto,posX,posY,angulo);

	if(!dim)
		ErrorLogHandler::addError("CargadorYaml","Error al crear la dimension Cuadrado. \n"); 
	
	return dim;

}

Dimension* CargadorYaml::crearDimension(const YAML::Node& dimension, double angulo,double posX,double posY, const char* tipo_dimension){

	if(strcmp(tipo_dimension,"CIRCULO") == 0)
		return crearCirculo(dimension,angulo,posX,posY);

	if(strcmp(tipo_dimension,"CUADRADO") == 0)
		return crearCuadrado(dimension,angulo,posX,posY);

	ErrorLogHandler::addError("CargadorYaml","Error del tipo dimension. El tipo de dimension no es un tipo valido. \n"); 	
	return NULL;
}

Dimension* CargadorYaml::obtener_dimension(const YAML::Node& dimension,const char* tipo_dimension){

	double posX, posY,angulo;

	//Cargo el angulo
	try{
		dimension["angulo"] >> angulo;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No existe angulo de figura. Se carga angulo por defecto en 0 grados. \n"); 
		angulo = ANGULO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del angulo de figura. Se carga angulo por defecto en 0 grados. \n"); 
		angulo = ANGULO_DEFAULT;
	}

	//Cargo posX y posY
	try{
		dimension["posX"] >> posX;
		dimension["posY"] >> posY;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Posicion de figura no esta definida. Se carga posicion por defecto. \n"); 
		posX = POSX_DEFAULT;
		posY = POSY_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo en Posicion de figura. Se carga posicion por defecto. \n"); 
		posX = POSX_DEFAULT;
		posY = POSY_DEFAULT;
	}

	return crearDimension(dimension, angulo, posX, posY, tipo_dimension);

}

Figura* CargadorYaml::cargarFigura(const char* tipo_figura,const char* ID,Dimension* dimension){

	if (strcmp(tipo_figura,"CUADRADO") == 0){
		//Figura* figura = new FiguraCuadrada(ID,dimension);
		Figura* figura = new FiguraCuadrada(ID,0,0,0,0,0);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Cuadrada. \n"); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CIRCULO") == 0){
		//Figura* figura = new FiguraCircular(ID,dimension);
		Figura* figura = new FiguraCircular(ID,0,0,0,0);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Circular. \n"); 	
		return figura;
	}

	ErrorLogHandler::addError("CargadorYaml","Error del tipo figura. El tipo de figura no es un tipo valido. \n"); 	
	return NULL;
}

void CargadorYaml::cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno){

	std::string ID,tipo_dimension;

	for(unsigned i=0;i<listaFiguras.size();i++) {
		try{
			listaFiguras[i]["ID"] >> ID;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen. \n"); 
			//como se pone la crucesita de que no hay imagen???
			//ID = ID_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen. \n"); 
			//idem :P	
		}

		try{
			listaFiguras[i]["tipo_dimension"] >> tipo_dimension;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar dimension para la figura. La figura no sera cargada. \n"); 
			continue;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar dimension para la figura. La figura no sera cargada. \n"); 
			continue;	
		}


		Dimension* dimension = obtener_dimension(listaFiguras[i]["dimension"],tipo_dimension.c_str());
		
		//Si no hay dimension, continuo a la siguiente figura.
		if(!dimension){
			ErrorLogHandler::addError("CargadorYaml","No se pudo crear la dimensión. La figura no sera cargada. \n"); 
			continue;
		}

		//FIXME:
		//Esta linea es HARCODEO!! esta porque no existe el tipo figura todavia!!!
		const char* tipo_figura = tipo_dimension.c_str();
		Figura * figura = cargarFigura(tipo_figura,ID.c_str(),dimension);

		if(!figura){
			ErrorLogHandler::addError("CargadorYaml","No se pudo crear la figura. La figura no sera cargada. \n"); 
			continue;
		}
		
		terreno->agregarFigura(figura);		
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
	cargar_figuras(listaFiguras,terreno);

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
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
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
		std::cout << e.what();
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