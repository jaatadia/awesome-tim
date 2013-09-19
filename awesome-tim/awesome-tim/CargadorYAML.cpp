#include "CargadorYaml.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"

#define RUTA_DEFAULT "../yaml/archivoDefault.yml"

#define CANT_CAR 40

std::string CargadorYaml::ruta_archivo = "";

Dimension* CargadorYaml::crearCirculo(const YAML::Node& dimension, double angulo,double posX,double posY){
	double radio;	
	try{
		dimension["radio"] >> radio;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe radio de dimension circulo. Se carga radio por defecto.",e.what());
		radio = RADIO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del radio de dimension circulo. Se carga radio por defecto.",e.what());
		radio = RADIO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!radio_valido(radio)){
		int linea = dimension["radio"].GetMark().line;
		imprimir_error_linea("Radio de Circulo invalido. Se carga radio por defecto.", linea);
		radio = RADIO_DEFAULT;
	}

	Dimension* dim = new Circulo(radio,posX,posY,angulo);
	
	if(!dim)
		ErrorLogHandler::addError("CargadorYaml","Error al crear la dimension Circulo. La figura no sera cargada."); 
		//Error de memoria, no imprime nro de linea
	return dim;
}

Dimension* CargadorYaml::crearCuadrado(const YAML::Node& dimension, double angulo,double posX,double posY){
	double ancho, alto;	
	try{
		dimension["ancho"] >> ancho;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe ancho de dimension cuadrado. Se carga ancho por defecto.",e.what());
		ancho = ANCHO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del ancho de dimension cuadrado. Se carga ancho por defecto.",e.what());
		ancho = ANCHO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!ancho_cuadrado_valido(ancho)){
		int linea = dimension["ancho"].GetMark().line;
		imprimir_error_linea("Ancho de Cuadrado invalido. Se carga ancho por defecto.",linea);
		ancho = ANCHO_DEFAULT;
	}

	try{
		dimension["alto"] >> alto;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe alto de dimension cuadrado. Se carga alto por defecto.",e.what());
		alto = ALTO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del alto de dimension cuadrado. Se carga alto por defecto.",e.what());
		alto = ALTO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!alto_cuadrado_valido(alto)){
		int linea = dimension["alto"].GetMark().line;
		imprimir_error_linea("Alto de Cuadrado invalido. Se carga alto por defecto.",linea);
		alto = ALTO_DEFAULT;
	}

	Dimension* dim = new Cuadrado(ancho,alto,posX,posY,angulo);

	if(!dim)
		ErrorLogHandler::addError("CargadorYaml","Error al crear la dimension Cuadrado. La figura no sera cargada."); 
		//Error de memoria, no imprime nro de linea
	return dim;

}


Dimension* CargadorYaml::crearTriangulo(const YAML::Node& dimension, double angulo,double posX,double posY){

	double base;	
	try{
		dimension["base"] >> base;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe base de dimension triangulo. Se carga base por defecto.",e.what());
		base = BASE_TRIANGULO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de la base de dimension triangulo. Se carga base por defecto.",e.what());
		base = BASE_TRIANGULO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una base, entonces el nodo existe y no va a tirar excepcion
	if(!base_triangulo_valida(base)){
		int linea = dimension["base"].GetMark().line;
		imprimir_error_linea("Base de Triangulo invalida. Se carga base por defecto.",linea);
		base = BASE_TRIANGULO_DEFAULT;
	}

	double altura;	
	try{
		dimension["altura"] >> altura;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe altura de dimension triangulo. Se carga altura por defecto.",e.what());
		altura = ALTO_TRIANGULO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de la altura de dimension triangulo. Se carga altura por defecto.",e.what());
		altura = ALTO_TRIANGULO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una altura, entonces el nodo existe y no va a tirar excepcion
	if(!altura_triangulo_valida(altura)){
		int linea = dimension["altura"].GetMark().line;
		imprimir_error_linea("Altura de Triangulo invalida. Se carga altura por defecto.",linea);
		altura = ALTO_TRIANGULO_DEFAULT;
	}

	Dimension* dim = new Triangulo2(posX, posY, angulo,base,altura);
	
	if(!dim)
		ErrorLogHandler::addError("CargadorYaml","Error al crear la dimension Triangulo. La figura no sera cargada."); 
		//Error de memoria, no imprime nro de linea
	return dim;

}

Dimension* CargadorYaml::crearPoligonoRegular(const YAML::Node& dimension, double angulo,double posX,double posY){

	double radio;	
	try{
		dimension["radio"] >> radio;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe radio de dimension poligono regular. Se carga radio por defecto.",e.what());
		radio = RADIO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del radio de dimension poligono regular. Se carga radio por defecto.",e.what());
		radio = RADIO_DEFAULT;
	}

	//Si entro aca es porque lei realmente un radio, entonces el nodo existe y no va a tirar excepcion
	if(!radio_valido(radio)){
		int linea = dimension["radio"].GetMark().line;
		imprimir_error_linea("Radio de Poligono Regular invalido. Se carga radio por defecto.",linea);
		radio = RADIO_DEFAULT;
	}

	int vert;	
	try{
		dimension["cant_vertices"] >> vert;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe nodo vertices de dimension poligono regular. Se carga cantidad de vertices por defecto.",e.what());
		vert = VERTICES_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo de cantidad de vertices de dimension poligono regular. Se carga cantidad de vertices por defecto.",e.what());
		vert = VERTICES_DEFAULT;
	}

	//Si entro aca es porque lei realmente un radio, entonces el nodo existe y no va a tirar excepcion
	if(!cant_vertices_valida(vert)){
		int linea = dimension["vertices"].GetMark().line;
		imprimir_error_linea("Cantidad de Vertices de Poligono Regular invalida. Se carga cantidad de vertices por defecto.",linea);
		vert = VERTICES_DEFAULT;
	}

	Dimension* dim = new PoligonoRegular( posX, posY, radio, vert, angulo);
	
	if(!dim)
		ErrorLogHandler::addError("CargadorYaml","Error al crear la dimension Poligono Regular. La figura no sera cargada."); 
	
	return dim;

}

Dimension* CargadorYaml::crearDimension(const YAML::Node& dimension, double angulo,double posX,double posY, const char* tipo_dimension){

	if(strcmp(tipo_dimension,"CIRCULO") == 0)
		return crearCirculo(dimension,angulo,posX,posY);

	if(strcmp(tipo_dimension,"CUADRADO") == 0)
		return crearCuadrado(dimension,angulo,posX,posY);

	if(strcmp(tipo_dimension,"TRIANGULO") == 0)
		return crearTriangulo(dimension,angulo,posX,posY);

	if(strcmp(tipo_dimension,"POLIGONOREGULAR") == 0)
		return crearPoligonoRegular(dimension,angulo,posX,posY);

	//No deberia llegar a este error porque ya deberia haber saltado antes.
	ErrorLogHandler::addError("CargadorYaml","Error del tipo dimension. El tipo de dimension no es un tipo valido."); 	
	return NULL;
}

Dimension* CargadorYaml::obtener_dimension(const YAML::Node& dimension,const char* tipo_dimension){

	double posX, posY,angulo;

	//Cargo el angulo
	try{
		dimension["angulo"] >> angulo;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No existe angulo de figura. Se carga angulo por defecto en 0 grados.",e.what());
		angulo = ANGULO_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo del angulo de figura. Se carga angulo por defecto en 0 grados.",e.what());
		angulo = ANGULO_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!angulo_valido(angulo)){
		int linea = dimension["angulo"].GetMark().line;
		imprimir_error_linea("Angulo de Figura invalido. Se carga angulo por defecto en 0 grados.", linea);
		angulo = ANGULO_DEFAULT;
	}

	//Cargo posX y posY
	try{
		dimension["posX"] >> posX;
		dimension["posY"] >> posY;
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Posicion de figura no esta definida. Se carga posicion por defecto.",e.what());
		posX = POSX_DEFAULT;
		posY = POSY_DEFAULT;
	}catch(YAML::InvalidScalar &e){
		imprimir_error_excepcion("Dato erroneo en Posicion de figura. Se carga posicion por defecto.",e.what());
		posX = POSX_DEFAULT;
		posY = POSY_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!posicion_validaX(posX)){
		int linea = dimension["posX"].GetMark().line;
		imprimir_error_linea("Posicion X de Figura invalida. Se carga posicion X por defecto.",linea);
		posX = POSX_DEFAULT;
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!posicion_validaY(posY)){
		int linea = dimension["posY"].GetMark().line;
		imprimir_error_linea("Posicion Y de Figura invalida. Se carga posicion Y por defecto.",linea);
		posY = POSY_DEFAULT;
	}

	return crearDimension(dimension, angulo, posX, posY, tipo_dimension);

}

Figura* CargadorYaml::crearFigura(/*const char* tipo_figura,*/const char* ID,Dimension* dimension,int linea){

	Imagen* img = new Imagen(ID);
	if (img->huboFallos()) {
		imprimir_error_linea("No se pudo crear la imagen, ID invalido. La figura no tendra imagen.",linea);
	}
	Contenedor::putMultimedia(ID,img);
	/*
	if (strcmp(tipo_figura,"CUADRADO") == 0){ //no tiene que decir tipo_dimension?
		Figura* figura = new Figura(ID,dimension);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Cuadrada."); 	
		return figura;
	}

	if (strcmp(tipo_figura,"CIRCULO") == 0){
		Figura* figura = new Figura(ID,dimension);
		if(!figura)
			ErrorLogHandler::addError("CargadorYaml","Error al crear figura Circular."); 	
		return figura;
	}
	*/
	return new Figura(ID,dimension);

	//No deberia llegar a este caso porque el error deberia haber saltado antes.
	ErrorLogHandler::addError("CargadorYaml","Error del tipo figura. El tipo de figura no es un tipo valido."); 	
	return NULL;
}
/*
void CargadorYaml::cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno){

	std::string ID,tipo_dimension;

	for(unsigned i=0;i<listaFiguras.size();i++) {
		try{
			listaFiguras[i]["ID"] >> ID;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			ID = ID_DEFAULT;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar ID de figura. La figura no tendra imagen."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			ID = ID_DEFAULT;
		}

		//Va if de ID?????????

		try{
			listaFiguras[i]["tipo_dimension"] >> tipo_dimension;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar dimension para la figura. La figura no sera cargada."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Error al cargar dimension para la figura. La figura no sera cargada."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;	
		}

		//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
		if(!tipo_dimension_valida(tipo_dimension.c_str())){
			int linea = listaFiguras[i]["tipo_dimension"].GetMark().line;
			imprimir_error_linea("Tipo de dimension invalida.", linea);
			//Harcode de figura:
			imprimir_error_linea("Tipo de figura invalida.", linea);
			continue;
		}

		Dimension* dimension = obtener_dimension(listaFiguras[i]["dimension"],tipo_dimension.c_str());
		
		//Si no hay dimension, continuo a la siguiente figura.
		if(!dimension){
			ErrorLogHandler::addError("CargadorYaml","No se pudo crear la dimensión. La figura no sera cargada."); 
			continue;
		}

		//FIXME:
		//Esta linea es HARCODEO!! esta porque no existe el tipo figura todavia!!!
		const char* tipo_figura = tipo_dimension.c_str();
		if(!tipo_figura_valida(tipo_figura)){
			//imprimir_error_linea("Tipo de figura invalida.", linea);
			continue;
		}
		
		Figura* figura = cargarFigura(tipo_figura,ID.c_str(),dimension,listaFiguras[i]["ID"].GetMark().line);

		if(!figura){
			if (dimension) delete(dimension);
			ErrorLogHandler::addError("CargadorYaml","No se pudo crear la figura. La figura no sera cargada.");
			//habria q imprimir el tipo de figura y la ruta de la imagen q no anda
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
		CargadorYaml::imprimir_error_excepcion("Error al cargar terreno. Se carga imagen de fondo default.",e.what());
		img = FONDO_TERRENO;
	}catch(YAML::InvalidScalar &e){
		CargadorYaml::imprimir_error_excepcion("Error al cargar terreno. Se carga imagen de fondo default.",e.what());
		img = FONDO_TERRENO;	
	}

	//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
	if(!terreno->setFondo(img.c_str())){
		int linea = nodoTerreno["fondo"].GetMark().line;
		imprimir_error_linea("Fondo de terreno invalido.", linea);
		img = FONDO_TERRENO;
		terreno->setFondo(img.c_str());
	}

	//Cargo las figuras del terreno
	try{
		const YAML::Node& listaFiguras = nodoTerreno["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de figuras terreno. Se carga terreno sin figuras.");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		return;
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de figuras terreno. Se carga terreno sin figuras.");
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
			ErrorLogHandler::addError("CargadorYaml","Error al tipo de figura de Botonera. No se carga el boton."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Tipo de figura de Botonera invalida. No se carga el boton."); 
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
			ErrorLogHandler::addError("CargadorYaml","No se encontro el nodo cantidad de instancias. Se cargan instancias default."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			instancias = INSTANCIAS_DEFAULT;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Cantidad de instancias invalida. Se carga cantidad de instancias default."); 
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
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de botones de la Botonera. Se carga botonera con botones por default.");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		//botonera->agregarBotonesDefault()
		return;
	}catch(YAML::BadDereference &e){
		ErrorLogHandler::addError("CargadorYaml","Error al cargar lista de botones de la Botonera. Se carga botonera con botones por default.");
		ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
		//botonera->agregarBotonesDefault()
		return;
	}

	const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	
	cargar_figuras_botones(listaFiguras,botonera);
}
*/





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
	
		Figura* fig = cargar_figura(listaFiguras[i]);

		if (!fig) continue;
		
		terreno->agregarFigura(fig);	
	}
}

void CargadorYaml::cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera){

	try{
		const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("Error al cargar lista de botones de la Botonera. Se carga botonera con botones por default.",e.what());
		//botonera->agregarBotonesDefault();
		return;
	}catch(YAML::BadDereference &e){
		imprimir_error_excepcion("Error al cargar lista de botones de la Botonera. Se carga botonera con botones por default.",e.what());
		//botonera->agregarBotonesDefault();
		return;
	}

	const YAML::Node& listaFiguras = nodoBotonera["lista_figuras"];
	
	for(unsigned i=0;i<listaFiguras.size();i++) {
		
		int instancias;
		/*
		try{
			listaFiguras[i]["tipo_figura"] >> tipo_figura;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			ErrorLogHandler::addError("CargadorYaml","Error al tipo de figura de Botonera. No se carga el boton."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}catch(YAML::InvalidScalar &e){
			ErrorLogHandler::addError("CargadorYaml","Tipo de figura de Botonera invalida. No se carga el boton."); 
			ErrorLogHandler::addError("CargadorYaml: ",e.what()); 
			continue;
		}

		//Si entro aca es porque lei realmente un tipo de figura, entonces el nodo existe y no va a tirar excepcion
		if(!tipo_figura_botonera_valida(tipo_figura)){
			int linea = listaFiguras[i]["tipo_figura"].GetMark().line;
			imprimir_error_linea("Tipo de figura de botonera invalida.", linea);
			continue;
		}
		*/
		
		Figura* fig = cargar_figura(listaFiguras[i]["figura"]);
		
		try{
			listaFiguras[i]["cantidad_de_instancias"] >> instancias;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			imprimir_error_excepcion("No se encontro el nodo cantidad de instancias. Se cargan instancias por defecto.",e.what());
			instancias = INSTANCIAS_DEFAULT;
		}catch(YAML::InvalidScalar &e){
			imprimir_error_excepcion("Cantidad de instancias invalida. Se carga cantidad de instancias por defecto.",e.what());
			instancias = INSTANCIAS_DEFAULT;		
		}
		//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
		if(!cant_instancias_valida(instancias)){
			int linea = listaFiguras[i]["cantidad_de_instancias"].GetMark().line;
			imprimir_error_linea("Cantidad de instancias invalida. Se carga cantidad de instancias por defecto.",linea);
			instancias = INSTANCIAS_DEFAULT;
		}
		
		botonera->agregarBoton(fig,instancias);
	}
}

Figura* CargadorYaml::cargar_figura(const YAML::Node& nodoFig/*listaFiguras[i]*/){

	std::string ID, tipo_dimension;

	try{
			nodoFig["ID"] >> ID;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			imprimir_error_excepcion("Error al cargar ID de figura. La figura no tendra imagen.",e.what());
			ID = ID_DEFAULT;
		}catch(YAML::InvalidScalar &e){
			imprimir_error_excepcion("Error al cargar ID de figura. La figura no tendra imagen.",e.what());
			ID = ID_DEFAULT;
		}
		//El ID se chequea al crear la imagen, si no es valido hace la crucesita

		try{
			nodoFig["tipo_dimension"] >> tipo_dimension;
		}catch(YAML::TypedKeyNotFound<std::string> &e){
			imprimir_error_excepcion("Error al cargar dimension para la figura. La figura no sera cargada.",e.what());
			return NULL;
		}catch(YAML::InvalidScalar &e){
			imprimir_error_excepcion("Error al cargar dimension para la figura. La figura no sera cargada.",e.what());
			return NULL;
		}

		//Si entro aca es porque lei realmente una cantidad de instancias, entonces el nodo existe y no va a tirar excepcion
		if(!tipo_dimension_valida(tipo_dimension.c_str())){
			int linea = nodoFig["tipo_dimension"].GetMark().line;
			imprimir_error_linea("Tipo de dimension invalida. La figura no sera cargada.",linea);
			//Harcode de figura:
			//imprimir_error_linea("Tipo de figura invalida.", linea);
			return NULL;
		}

		Dimension* dimension = obtener_dimension(nodoFig["dimension"],tipo_dimension.c_str());
		
		//Si no hay dimension, continuo a la siguiente figura.
		if(!dimension){
			ErrorLogHandler::addError("CargadorYaml","No se pudo crear la dimensión. La figura no sera cargada."); 
			return NULL;
		}

		//FIXME:
		//Esta linea es HARCODEO!! esta porque no existe el tipo figura todavia!!!
		const char* tipo_figura = tipo_dimension.c_str();
		if(!tipo_figura_valida(tipo_figura)){
			//imprimir_error_linea("Tipo de figura invalida.", linea);
			return NULL;
		}
		
		Figura* figura = crearFigura(/*tipo_figura,*/ID.c_str(),dimension,nodoFig["ID"].GetMark().line);

		if(!figura){
			if (dimension) delete(dimension);
			ErrorLogHandler::addError("CargadorYaml","No se pudo crear la figura. La figura no sera cargada.");
			return NULL;
		}
		return figura;
}





//*******Abre un archivo Yaml en el que se encuentre el estado del juego guardado***************
bool CargadorYaml::cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno){

	//Abro el archivo Yaml para parsearlo.
	YAML::Node doc;
	std::ifstream mi_archivo;
	mi_archivo.open(file,std::ios::in);
	ruta_archivo = string(file);
	
	if(!mi_archivo.is_open()){
		mi_archivo.open(RUTA_DEFAULT,std::ios::out);
		CargadorYaml::imprimir_error_sin_linea("Error al abrir archivo de juego. Se carga archivo default.");
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
		imprimir_error_excepcion("Error al parsear el archivo. Se continua con archivo default.",e.what());
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	//Busco el nodo raiz, al que estan asociados los demas nodos
	try{
		const YAML::Node& nodoRaiz = doc["juego"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No se encontro nodo raiz juego. Se carga archivo default.",e.what());
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		imprimir_error_excepcion("No hay nodo raiz juego. Se carga archivo default.",e.what());
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
		imprimir_error_excepcion("No se encontro nodo botonera. Se carga archivo default.",e.what());
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		imprimir_error_excepcion("No se encontro nodo botonera. Se carga archivo default.",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoBotonera = nodoRaiz["botonera"];

	//Busco nodo Terreno

	try{
		const YAML::Node& nodoBotonera = nodoRaiz["terreno"];
	}catch(YAML::TypedKeyNotFound<std::string> &e){
		imprimir_error_excepcion("No se encontro nodo terreno. Se carga archivo default.",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}catch(YAML::BadDereference &e){
		imprimir_error_excepcion("No se encontro nodo terreno. Se carga archivo default.",e.what()); 
		mi_archivo.close();
		return cargarJuego(RUTA_DEFAULT,botonera,terreno);
	}

	const YAML::Node& nodoTerreno = nodoRaiz["terreno"];

	//Cargo la botonera	
	cargar_botones(nodoBotonera,botonera);

	//Cargo el terreno
	cargar_terreno(nodoTerreno,terreno);

	mi_archivo.close();

	return true;

}





bool CargadorYaml::tipo_dimension_valida(const char* tipo_dimension){
	return ((strcmp(tipo_dimension,"TRIANGULO") == 0) || (strcmp(tipo_dimension,"CUADRADO") == 0) || (strcmp(tipo_dimension,"CIRCULO") == 0) || (strcmp(tipo_dimension,"POLIGONOREGULAR") == 0)); 
}


bool CargadorYaml::tipo_figura_valida(const char* tipo_figura){return true;}
bool CargadorYaml::tipo_figura_botonera_valida(int tipo_figura){return true;}
bool CargadorYaml::radio_valido(double radio){
	return ((radio > 0) && (radio < ANCHO_TERRENO_LOGICO));
}

bool CargadorYaml::alto_cuadrado_valido(double alto){
	return ((alto > 0) && (alto < ALTO_TERRENO_LOGICO));
}

bool CargadorYaml::ancho_cuadrado_valido(double ancho){
	return ((ancho > 0) && (ancho < ANCHO_TERRENO_LOGICO));
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

bool CargadorYaml::altura_triangulo_valida(double altura){
	return ((altura > 0) && (altura < ALTO_TERRENO_LOGICO));
}

bool CargadorYaml::base_triangulo_valida(double base){
	return ((base > 0) && (base < ANCHO_TERRENO_LOGICO));
}

bool CargadorYaml::cant_vertices_valida(int vertices){
	return ((vertices >= 3) && (vertices < 100));
}

//Impresiones
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
	std::string full_msj = msj + what;
	ErrorLogHandler::addError("CargadorYaml",full_msj.c_str());
}

void CargadorYaml::pruebaCargador(){

	BotoneraController* bot = new BotoneraController(20,20,3);
	Terreno* terr = new Terreno(80,80);

	//habria q imprimir en el error el nombre del archivo que no se pudo cargar, no?
	CargadorYaml::cargarJuego("../yaml/pruebacargar.yml",bot,terr); //no existe archivo
	CargadorYaml::cargarJuego("../yaml/sinNodoJuego.yml",bot,terr); 
	CargadorYaml::cargarJuego("../yaml/vacio.yml",bot,terr); //arch vacio
	CargadorYaml::cargarJuego("../yaml/sinTerreno.yml",bot,terr);
	CargadorYaml::cargarJuego("../yaml/sinBotonera.yml",bot,terr);
	CargadorYaml::cargarJuego("../yaml/terrenoVacio.yml",bot,terr);
	CargadorYaml::cargarJuego("../yaml/pruebacargar4.yml",bot,terr);

}