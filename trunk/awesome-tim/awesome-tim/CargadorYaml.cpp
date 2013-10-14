#include "CargadorYaml.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yml"

#define CANT_CAR 40

std::string CargadorYaml::ruta_archivo = "";

/**********************************************************
**                                                       **
**                OBTENER PARAMETROS                     **
**                                                       **
**********************************************************/

void CargadorYaml::obtenerPosicion(const YAML::Node& nodoFigura, double* posX, double* posY){

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

void CargadorYaml::obtenerAngulo(const YAML::Node& nodoFigura, double* angulo){
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

void CargadorYaml::obtenerID(const YAML::Node& nodoFigura, std::string* ID){

	try{
		nodoFigura["ID"] >> *ID;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen."); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		*ID = ID_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen."); 
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		*ID = ID_DEFAULT;
	}

	Imagen* img = new Imagen((*ID).c_str());
	if (img->huboFallos()) {
		int linea = nodoFigura["ID"].GetMark().line;
		imprimir_error_linea("No se pudo crear la imagen, ID invalido. La figura no tendra imagen.",linea);
	}
	Contenedor::putMultimedia((*ID).c_str(),img);

}

void CargadorYaml::obtenerLargo(const YAML::Node& nodoFigura, double* largo){
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
void CargadorYaml::obtenerBaseTriangulo(const YAML::Node& nodoFigura, double* base){
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

void CargadorYaml::obtenerAlto(const YAML::Node& nodoFigura, double* alto){
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

void CargadorYaml::obtenerAncho(const YAML::Node& nodoFigura, double* ancho){
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

void CargadorYaml::obtenerRadio(const YAML::Node& nodoFigura,double* radio){
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

void CargadorYaml::obtenerVertices(const YAML::Node& nodoFigura,int* vertices){
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
void CargadorYaml::obtenerExtremos(const YAML::Node& nodoFigura,double* x1,double* y1,double* x2,double* y2){

	try{
		const YAML::Node& nodoPos = nodoFigura["extremo1"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe extremo1 de figura. No se carga la figura.",e.what());
		return;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de extremo1 de figura. No se carga la figura.",e.what());
		return;
	}
	const YAML::Node& nodoPos = nodoFigura["extremo1"];
	//std::cout << x1 << "   " << y1 << "\n";
	obtenerPosicion(nodoPos,x1,y1);

	try{
		const YAML::Node& nodoPos2 = nodoFigura["extremo2"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe extremo2 de figura. No se carga la figura.",e.what());
		return;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de extremo2 de figura. No se carga la figura.",e.what());
		return;
	}
	const YAML::Node& nodoPos2 = nodoFigura["extremo2"];
	obtenerPosicion(nodoPos2,x2,y2);
}
/**********************************************************
**                                                       **
**                    CREAR FIGURAS                      **
**                                                       **
**********************************************************/
Figura* CargadorYaml::crearGloboHelio(const YAML::Node& nodoFigura){
	double posX,posY;

	obtenerPosicion(nodoFigura,&posX,&posY);

	Figura* figura = new GloboHelio(posX,posY);

	return figura;
}

Figura* CargadorYaml::crearBolaBowling(const YAML::Node& nodoFigura){
	double posX,posY;

	obtenerPosicion(nodoFigura,&posX,&posY);

	Figura* figura = new PelotaBowling(posX,posY);

	return figura;
}

Figura* CargadorYaml::crearPelotaBasquet(const YAML::Node& nodoFigura){
	double posX,posY;

	obtenerPosicion(nodoFigura,&posX,&posY);

	Figura* figura = new PelotaBasquet(posX,posY);

	return figura;
}

Figura* CargadorYaml::crearPelotaTenis(const YAML::Node& nodoFigura){
	double posX,posY,angulo;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);

	Figura* figura = new PelotaTenis(posX,posY,angulo) ;

	return figura;
}

Figura* CargadorYaml::crearMotor(const YAML::Node& nodoFigura){
	return NULL;
}

Figura* CargadorYaml::crearSoga(const YAML::Node& nodoFigura){
	double x1,y1,x2,y2;
	
	obtenerExtremos(nodoFigura,&x1,&y1,&x2,&y2);

	return new Soga(x1,y1,x2,y2);
}

Figura* CargadorYaml::crearCorrea(const YAML::Node& nodoFigura){
	double x1,y1,x2,y2;
	
	obtenerExtremos(nodoFigura,&x1,&y1,&x2,&y2);

	return new Linea(x1,y1,x2,y2);
}

Figura* CargadorYaml::crearEngranaje(const YAML::Node& nodoFigura){
	double posX,posY,angulo,radio;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerRadio(nodoFigura,&radio);

	Figura* fig = new Engranaje(posX,posY,radio,angulo);
	return fig;
}
Figura* CargadorYaml::crearEngranaje2(const YAML::Node& nodoFigura){ //FIX
	double posX,posY,angulo,radio;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerRadio(nodoFigura,&radio);

	return new Engranaje2(posX,posY,radio,angulo);
}

Figura* CargadorYaml::crearCintaTransportadora(const YAML::Node& nodoFigura){
	double posX,posY,angulo;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);

	return new CintaTransportadora(LARGO_CINTA_TRANSPORTADORA,posX,posY,angulo);
}

Figura* CargadorYaml::crearBalancin(const YAML::Node& nodoFigura, int sentido){
	double posX,posY,angulo;
	
	obtenerPosicion(nodoFigura,&posX,&posY);
	
	//if sentido es DERECHA se setea el angulo default derecha:
	angulo = ANGULO_BALANCIN_DER;

	if(sentido == IZQUIERDA)
		angulo = ANGULO_BALANCIN_IZQ;

	//if sentido es DERECHA se setea el ID default derecha:
	std::string IDBotonera = ID_BALANCIN_DER;

	if(sentido == IZQUIERDA)
		IDBotonera = ID_BALANCIN_IZQ;

	return new Balancin(IDBotonera.c_str(),posX,posY,angulo);
}

Figura* CargadorYaml::crearPlataforma(const YAML::Node& nodoFigura){
	double posX,posY,angulo,largo;

	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerLargo(nodoFigura, &largo);

	return new Plataforma(largo,posX,posY,angulo);
}

Figura* CargadorYaml::crearTriangulo(const YAML::Node& nodoFigura){
	double posX,posY,angulo,base,altura;
	std::string ID;

	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAngulo(nodoFigura,&angulo);
	obtenerBaseTriangulo(nodoFigura,&base);
	obtenerAlto(nodoFigura,&altura);
	obtenerID(nodoFigura,&ID);

	Dimension* triangulo = new Triangulo(posX,posY,angulo,base,altura);

	if(!triangulo){
		imprimir_error_sin_linea("No se pudo crear la dimension triangulo.");
		return NULL;
	}

	Figura* figura = new Figura(ID.c_str(), triangulo);

	if(!figura)
		delete(triangulo);
	
	return figura; 
}

Figura* CargadorYaml::crearPoligono(const YAML::Node& nodoFigura){

	double posX,posY,angulo,radio;
	int vertices;
	std::string ID;

	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerID(nodoFigura,&ID);
	obtenerRadio(nodoFigura,&radio);
	obtenerVertices(nodoFigura,&vertices);

	Dimension* poligono = new PoligonoRegular(posX,posY,radio,vertices,angulo);

	if(!poligono){
		imprimir_error_sin_linea("No se pudo crear la dimension de poligono regular.");
		return NULL;
	}

	Figura* figura = new Figura(ID.c_str(), poligono);

	if(!figura)
		delete(poligono);
	
	return figura; 
}

Figura* CargadorYaml::crearCirculo(const YAML::Node& nodoFigura){
	
	double posX,posY,angulo,radio;
	std::string ID;
	
	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerID(nodoFigura,&ID);
	obtenerRadio(nodoFigura,&radio);

	Dimension* circulo = new Circulo(radio,posX,posY,angulo);

	if(!circulo){
		imprimir_error_sin_linea("No se pudo crear la dimension del circulo");
		return NULL;
	}

	Figura* figura = new Figura(ID.c_str(),circulo); 

	if(!figura)
		delete(circulo);

	return figura; 
}

Figura* CargadorYaml::crearCuadrado(const YAML::Node& nodoFigura){

	double posX, posY,angulo,ancho,alto;
	std::string ID;

	obtenerAngulo(nodoFigura,&angulo);
	obtenerPosicion(nodoFigura,&posX,&posY);
	obtenerAncho(nodoFigura,&ancho);
	obtenerAlto(nodoFigura,&alto);
	obtenerID(nodoFigura, &ID);

	Dimension* cuadrado = new Cuadrado(ancho,alto,posX,posY,angulo);

	if(!cuadrado){
		imprimir_error_sin_linea("No se pudo crear la dimension de cuadrado.");
		return NULL;
	}

	Figura* figura = new Figura(ID.c_str(), cuadrado);

	if(!figura)
		delete(cuadrado);
	
	return figura; 
}

Figura* CargadorYaml::crearFigura(const YAML::Node& nodoFigura, const char* tipo_figura){

	if (strcmp(tipo_figura,"CUADRADO") == 0){
		Figura* figura = crearCuadrado(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Cuadrada."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CIRCULO") == 0){
		Figura* figura = crearCirculo(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Circular."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"TRIANGULO") == 0){
		Figura* figura = crearTriangulo(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Triangular."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"POLIGONOREGULAR") == 0){
		Figura* figura = crearPoligono(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Poligono Regular."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"BALANCIN_IZQUIERDA") == 0){
		Figura* figura = crearBalancin(nodoFigura, IZQUIERDA);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Balancin."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"BALANCIN_DERECHA") == 0){
		Figura* figura = crearBalancin(nodoFigura, DERECHA);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Balancin."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"PLATAFORMA") == 0){
		Figura* figura = crearPlataforma(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Plataforma."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CINTA_TRANSPORTADORA") == 0){
		Figura* figura = crearCintaTransportadora(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Cinta Transportadora."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"ENGRANAJE") == 0){
		Figura* figura = crearEngranaje(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Engranaje."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"ENGRANAJE2") == 0){ //FIX
		Figura* figura = crearEngranaje2(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Engranaje2."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CORREA") == 0){
		Figura* figura = crearCorrea(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Correa."); 	
		return figura;
	}
		if (strcmp(tipo_figura,"LINEA") == 0){
		Figura* figura = crearCorrea(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Correa."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"SOGA") == 0){
		Figura* figura = crearSoga(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Soga."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"MOTOR") == 0){
		Figura* figura = crearMotor(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Motor."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"PELOTA_BASQUET") == 0){
		Figura* figura = crearPelotaBasquet(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Pelota de Basquet."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"BOLA_BOWLING") == 0){
		Figura* figura = crearBolaBowling(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Bola de Bowling."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"GLOBO_HELIO") == 0){
		Figura* figura = crearGloboHelio(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Globo de Helio."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"PELOTA_TENIS") == 0){
		Figura* figura = crearPelotaTenis(nodoFigura);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Pelota de Tenis."); 	
		return figura;
	}

	//No deberia llegar a este caso porque el error deberia haber saltado antes.
	ErrorLogHandler::addError("CargadorYaml","Error del tipo figura. El tipo de figura no es un tipo valido."); 	
	return NULL;
}

Figura* CargadorYaml::cargar_figura(const YAML::Node& nodoFig){

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
		ErrorLogHandler::addError("CargadorYaml","No se pudo crear la figura. La figura no sera cargada.");
	}

	return figura;
}

void CargadorYaml::cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno){

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

void CargadorYaml::cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera){

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
			imprimir_error_excepcion("No se encontro el nodo figura. El boton no sera cargado.",e.what());
			continue;
		}catch(YAML::InvalidScalar &e){
			imprimir_error_excepcion("No se encontro el nodo figura. El boton no sera cargado.",e.what());
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
bool CargadorYaml::cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	//Abro el archivo Yaml para parsearlo.
	YAML::Node doc;
	std::ifstream mi_archivo;
	mi_archivo.open(file,std::ios::in);
	ruta_archivo = string(file);
	
	if(!mi_archivo.is_open()){
		mi_archivo.open(RUTA_DEFAULT,std::ios::out);
		CargadorYaml::imprimir_error_sin_linea("No se encontro el abrir archivo de juego indicado. Se carga archivo default.");
		if (!mi_archivo.is_open()){
			ErrorLogHandler::addError("CargadorYaml","Error al abrir archivo de juego default."); 
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
bool CargadorYaml::tipo_figura_valida(const char* tipo_figura){ //FIXXXXXXXXXX
	bool cuadrado = (strcmp(tipo_figura,"CUADRADO") == 0);
	bool circulo = (strcmp(tipo_figura,"CIRCULO") == 0);
	bool triangulo = (strcmp(tipo_figura,"TRIANGULO") == 0);
	bool poligono = (strcmp(tipo_figura,"POLIGONOREGULAR") == 0);

	bool figuraSimple = (cuadrado || circulo || triangulo || poligono);

	bool plataforma = (strcmp(tipo_figura,"PLATAFORMA") == 0);
	bool balIzq = (strcmp(tipo_figura,"BALANCIN_IZQUIERDA") == 0);
	bool balDer = (strcmp(tipo_figura,"BALANCIN_DERECHA") == 0);
	bool balancin = (balIzq || balDer);
	bool cintaTrans = (strcmp(tipo_figura,"CINTA_TRANSPORTADORA") == 0);
	bool engranaje = (strcmp(tipo_figura,"ENGRANAJE") == 0);
	bool engranaje2 = (strcmp(tipo_figura,"ENGRANAJE2") == 0); // FIX
	bool correa = (strcmp(tipo_figura,"CORREA") == 0);
	bool linea = (strcmp(tipo_figura,"LINEA") == 0);
	bool soga = (strcmp(tipo_figura,"SOGA") == 0);
	bool motor = (strcmp(tipo_figura,"MOTOR") == 0);
	bool pelotaBask = (strcmp(tipo_figura,"PELOTA_BASQUET") == 0);
	bool bowling = (strcmp(tipo_figura,"BOLA_BOWLING") == 0);
	bool globoHelio = (strcmp(tipo_figura,"GLOBO_HELIO") == 0);
	bool tenis = (strcmp(tipo_figura,"PELOTA_TENIS") == 0);

	bool figuraCompleja = (plataforma || balancin || cintaTrans || engranaje || engranaje2 || correa || linea || soga || motor || pelotaBask || bowling || globoHelio || tenis);

	return (figuraSimple || figuraCompleja);
}

bool CargadorYaml::posicion_validaX(double posX){
	return ((posX >= 0) && (posX <= ANCHO_TERRENO_LOGICO)); //menor estricto o no???
}

bool CargadorYaml::posicion_validaY(double posY){
	return ((posY >= 0) && (posY <= ALTO_TERRENO_LOGICO)); //menor estricto o no???;
}

bool CargadorYaml::angulo_valido(double angulo){
	return ((angulo >=0) && (angulo < 360));
}

bool CargadorYaml::cant_instancias_valida(int instancias){
	return (instancias >= 0);
}

bool CargadorYaml::largo_valido(double largo){
	//FIXME: cuando es un largo valido? //checked. -flor
	return (largo > 0 || largo <= PLATAFORMA_MAXLARGO);
}

bool CargadorYaml::alto_valido(double alto){
	return ((alto > 0) && (alto < ALTO_TERRENO_LOGICO));
}

bool CargadorYaml::ancho_valido(double ancho){
	return ((ancho > 0) && (ancho < ANCHO_TERRENO_LOGICO));
}

bool CargadorYaml::base_triangulo_valida(double base){
	return ancho_valido(base);
}

bool CargadorYaml::radio_valido(double radio){
	return ((radio > 0) && (radio < ANCHO_TERRENO_LOGICO));
}

bool CargadorYaml::cant_vertices_valida(int cant){
	return ((cant >= 3) && (cant < 100));
}
/**********************************************************
**                                                       **
**                    IMPRESIONES                        **
**                                                       **
**********************************************************/

std::string CargadorYaml::concatenar_archivo(std::string mensaje, int linea, std::string archivo){
	char buffer[CANT_CAR];
	itoa(linea,buffer,10);//el ultimo valor es la base
	std::string line = string(buffer);
	std::string msj = mensaje + " Error en archivo Yaml: " + archivo + " - Linea nro: " + line; 
	return msj;
}

std::string CargadorYaml::concatenar_archivo(std::string mensaje, std::string archivo){
	std::string msj = mensaje + " Error en archivo Yaml: " + archivo; 
	return msj;
}

void CargadorYaml::imprimir_error_linea(std::string mensaje, int linea){
	linea = linea + 1; //Porque empieza a contar en 0
	std::string msj = CargadorYaml::concatenar_archivo(mensaje,linea,ruta_archivo);
	ErrorLogHandler::addError("CargadorYaml",msj.c_str());
}

void CargadorYaml::imprimir_error_sin_linea(std::string mensaje){
	std::string msj = CargadorYaml::concatenar_archivo(mensaje,ruta_archivo);
	ErrorLogHandler::addError("CargadorYaml",msj.c_str());
}
void CargadorYaml::imprimir_error_excepcion(std::string mensaje,std::string what){
	std::string msj = CargadorYaml::concatenar_archivo(mensaje,ruta_archivo);
	std::string full_msj = msj + " " + what;
	ErrorLogHandler::addError("CargadorYaml",full_msj.c_str());
}
