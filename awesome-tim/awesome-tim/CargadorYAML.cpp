#include "CargadorYaml.h"
#include "ErrorLogHandler.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yaml"

#define CANT_CAR 40

Dimension* CargadorYaml::crearCirculo(const YAML::Node& dimension, double angulo,double posX,double posY){
	double radio;	
	try{
		dimension["radio"] >> radio;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No existe radio de dimension circulo. Se carga radio por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		radio = RADIO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del radio de dimension circulo. Se carga radio por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		radio = RADIO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!radio_valido(radio)){
		int linea = dimension["radio"].GetMark().line;
		imprimir_error_linea("Radio de Circulo invalido.", linea);
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
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		ancho = ANCHO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del ancho de dimension cuadrado. Se carga ancho por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		ancho = ANCHO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!ancho_cuadrado_valido(ancho)){
		int linea = dimension["ancho"].GetMark().line;
		imprimir_error_linea("Ancho de Cuadrado invalido.", linea);
		ancho = ANCHO_DEFAULT;
	}

	try{
		dimension["alto"] >> alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No existe alto de dimension cuadrado. Se carga alto por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		alto = ALTO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del alto de dimension cuadrado. Se carga alto por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		alto = ALTO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!alto_cuadrado_valido(alto)){
		int linea = dimension["alto"].GetMark().line;
		imprimir_error_linea("Alto de Cuadrado invalido.", linea);
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

	//No deberia llegar a este error porque ya deberia haber saltado antes.
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
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		angulo = ANGULO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo del angulo de figura. Se carga angulo por defecto en 0 grados. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		angulo = ANGULO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!angulo_valido(angulo)){
		int linea = dimension["angulo"].GetMark().line;
		imprimir_error_linea("Angulo de Figura invalido.", linea);
		angulo = ANGULO_DEFAULT;
	}

	//Cargo posX y posY
	try{
		dimension["posX"] >> posX;
		dimension["posY"] >> posY;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Posicion de figura no esta definida. Se carga posicion por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		posX = POSX_DEFAULT;
		posY = POSY_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Dato erroneo en Posicion de figura. Se carga posicion por defecto. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		posX = POSX_DEFAULT;
		posY = POSY_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!posicion_validaX(posX)){
		int linea = dimension["posX"].GetMark().line;
		imprimir_error_linea("Posicion X de Figura invalida.", linea);
		posX = POSX_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!posicion_validaY(posY)){
		int linea = dimension["posY"].GetMark().line;
		imprimir_error_linea("Posicion Y de Figura invalida.", linea);
		posY = POSY_DEFAULT;
	}

	return crearDimension(dimension, angulo, posX, posY, tipo_dimension);

}

Figura* CargadorYaml::cargarFigura(const char* tipo_figura,const char* ID,Dimension* dimension){

	if (strcmp(tipo_figura,"CUADRADO") == 0){
		//Figura* figura = new FiguraCuadrada(ID,dimension);
		Figura* figura = new Figura(ID,new Cuadrado(0,0,0,0,0));
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Cuadrada. \n"); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CIRCULO") == 0){
		//Figura* figura = new FiguraCircular(ID,dimension);
		Figura* figura = new Figura(ID,new Circulo(0,0,0,0));
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Circular. \n"); 	
		return figura;
	}

	//No deberia llegar a este caso porque el error deberia haber saltado antes.
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
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			//como se pone la crucesita de que no hay imagen???
			//ID = ID_DEFECTO;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			//idem :P	
		}

		//Va if de ID?????????

		try{
			listaFiguras[i]["tipo_dimension"] >> tipo_dimension;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar dimension para la figura. La figura no sera cargada. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar dimension para la figura. La figura no sera cargada. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;	
		}

		//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
		if(!tipo_dimension_valida(tipo_dimension.c_str())){
			int linea = listaFiguras[i]["tipo_dimension"].GetMark().line;
			imprimir_error_linea("Tipo de dimension invalida.", linea);
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
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		img = FONDO_TERRENO;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar terreno. Se carga imagen de fondo default. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		img = FONDO_TERRENO;	
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!fondo_terreno_valido(img.c_str())){
		int linea = nodoTerreno["fondo"].GetMark().line;
		imprimir_error_linea("Fondo de terreno invalido.", linea);
		img = FONDO_TERRENO;
	}

	terreno->setFondo(img.c_str());

	//Cargo las figuras del terreno
	try{
		const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de figuras terreno. Se carga terreno sin figuras. \n");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		return;
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de figuras terreno. Se carga terreno sin figuras. \n");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		return;
	}

	const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];
	cargar_figuras(listaFiguras,terreno);

}


void CargadorYaml::cargar_figuras_botones(const YAML::Node& listaFiguras,BotoneraController* botonera){

	int tipo_figura, instancias;

	for(unsigned i=0;i<listaFiguras.size();i++) {
		try{
			listaFiguras[i]["tipo_figura"] >> tipo_figura;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al tipo de figura de Botonera. No se carga el boton. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Tipo de figura de Botonera invalida. No se carga el boton. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}

		//Si entro aca es porque lei realmente un tipo de figura, entonces el nodo existe y no va a tirar excepcion
		if(!tipo_figura_botonera_valida(tipo_figura)){
			int linea = listaFiguras[i]["tipo_figura"].GetMark().line;
			imprimir_error_linea("Tipo de figura de botonera invalida.", linea);
			continue;
		}

		try{
			listaFiguras[i]["cantidad_de_instancias"] >> instancias;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","No se encontro el nodo cantidad de instancias. Se cargan instancias default. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			instancias = INSTANCIAS_DEFAULT;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Cantidad de instancias invalida. Se carga cantidad de instancias default. \n"); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			instancias = INSTANCIAS_DEFAULT;		
		}

		//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
		if(!cant_instancias_valida(instancias)){
			int linea = listaFiguras[i]["cantidad_de_instancias"].GetMark().line;
			imprimir_error_linea("Cantidad de instancias invalida.", linea);
		}

		//botonera->agregarBoton(tipo_figura,instancias,);
	}

}
void CargadorYaml::cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera){

	try{
		const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de botones de la Botonera. Se carga botonera sin botones. \n");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		//???????????? sin botones??????
		return;
	}catch(YAML::BadDereference &e){
		//???????????? sin botones??????
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de botones de ña Botonera. Se carga botonera sin botones. \n");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		return;
	}

	const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	
	cargar_figuras_botones(listaFiguras,botonera);
}


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
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	//Busco el nodo raiz, al que estan asociados los demas nodos
	try{
		const YAML::Node& nodoRaiz = doc["juego"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","No se encontro nodo raiz juego. Se carga archivo default. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("CargadorYaml","No hay nodo raiz juego. Se carga archivo default. \n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
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
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo botonera. Se carga archivo default.\n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoBotonera = nodoRaiz["botonera"];

	//Busco nodo Terreno

	try{
		const YAML::Node& nodoBotonera = nodoRaiz["terreno"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo terreno. Se carga archivo default.\n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("cargadorYaml","No se encontro nodo terreno. Se carga archivo default.\n"); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoTerreno = nodoRaiz["terreno"];

	//Cargo la botonera	
	cargar_botones(nodoBotonera, botonera);

	//Cargo el terreno
	cargar_terreno(nodoTerreno,terreno);

	mi_archivo.close();

	return true;

}



//Funciones de validaciones:

bool CargadorYaml::cant_instancias_valida(int instancias){
	return false;
}

bool CargadorYaml::tipo_figura_botonera_valida(int tipo_figura){
	return true;
}
bool CargadorYaml::fondo_terreno_valido(const char* fondo){
	return true;
}
bool CargadorYaml::tipo_dimension_valida(const char* tipo_dimension){
	return true;
}
bool CargadorYaml::radio_valido(double radio){
	return true;
}
bool CargadorYaml::alto_cuadrado_valido(double alto){
	return true;
}
bool CargadorYaml::ancho_cuadrado_valido(double ancho){
	return true;
}
bool CargadorYaml::posicion_validaX(double posX){
	return true;
}

bool CargadorYaml::posicion_validaY(double posY){
	return true;
}

bool CargadorYaml::angulo_valido(double angulo){
	return true;
}

void CargadorYaml::imprimir_error_linea(std::string mensaje, int linea){
		linea = linea + 1; //Porque empieza a contar en 0
		char buffer[CANT_CAR];
		itoa(linea,buffer,10);//el ultimo valor es la base
		std::string line = string(buffer);
		std::string msj = mensaje + " Linea Yaml: " + line + "\n"; 
		ErrorLogHandler::addError("CargadorYaml",msj.c_str()); 
}