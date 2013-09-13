#include "Terreno.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"
#include <new>

Terreno::Terreno(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
	this->figuras = std::list<Figura*>();
	figuraActiva=NULL;
	img=NULL;
	fondoID=""; //sin fondo seria asi? (con NULL se rompe)
}

Terreno::~Terreno(void){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		delete (*iteradorLista);
	}
	//borro imagen del fondo
	if (img)
		delete img;

	delete sup;
}

void Terreno::redraw(EscalasDeEjes* escalas){

	//recorro todas las figuras y las voy dibujando

	if(this->img == NULL)
		sup->restore();//antes repinto todo de negro asi no quedan rastros de movimiento
	else{
		sup->restore();//por si la imagen tiene partes transparentes
		sup->dibujarImagen(this->img,NULL,0,0);
	}

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		(*iteradorLista)->dibujar(this->sup, escalas);
	}
	//por ultimo dibujo la que estoy manipulando;
	if (figuraActiva)
		figuraActiva->dibujar(this->sup,escalas);
}

Superficie* Terreno::getImpresion(EscalasDeEjes* escalas){
	if(this->huboCambios()) redraw(escalas);
	this->setCambio(false);
	return sup;
}

void Terreno::redraw(){}

Superficie* Terreno::getImpresion(){
	if(this->huboCambios()) redraw();
	this->setCambio(false);
	return sup;
}

void Terreno::setFondo(const char* ruta_img){
	
	Imagen* temp = new Imagen(ruta_img);
	if(!temp->huboFallos()){
		this->setCambio(true);
		delete this->img;
		this->img = temp->scaleImagen(this->ancho,this->alto);
		fondoID = ruta_img;
	}
	delete temp;
}
/* ESTUPIDOS PUNTEROS!!!!!!!!!!!!!!!!!!!!
	//para no abrir el archivo una y otra vez lo guardo en el contenedor
	if (Contenedor::estaMultimedia(ruta_img) == false){
		Imagen* temp = new Imagen(ruta_img);
		if(!temp->huboFallos())
			Contenedor::putMultimedia(ruta_img,temp);
	//no libero temp o borro lo del contenedor!!!
	}

	if (ruta_img != fondoID){
		//es distinto al fondo puesto
		Imagen* temp = (Imagen*)(Contenedor::getMultimedia(ruta_img));

		if(temp){
			this->setCambio(true);
			delete this->img;
			this->img = temp->scaleImagen(this->ancho,this->alto);
			fondoID = ruta_img;
		}
	//no libero temp o borro lo del contenedor!!!
	}
}*/

void Terreno::agregarFigura(Figura* fig){

//si se fue de rango del terreno lo empujo para dentro
	Dimension* dim = fig->getDimension();
	corregirPosicion(fig);

	try{
	(this->figuras).push_back(fig);
	} catch (...) {
		ErrorLogHandler::addError("agregarFigura","excepcion al agregar en la lista (figuras.push_back)");
		//si hay error, tira la excepcion nomas? y termina no haciendo nada???
	};
}

void Terreno::rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY){
	//practicamente lo mismo que arrastraFigura
	if (figuraActiva != NULL){
		//calculo el angulo y se lo pongo a figura
		double X2,Y2;
		X2 = posClickX + cantMovX;
		Y2 = posClickY + cantMovY;

		figuraActiva->cambiarAngulo(posClickX,posClickY,X2,Y2);
		this->setCambio(true);
	}
}


void Terreno::eliminarFigura(Figura* fig){

	try{
	(this->figuras).remove(fig);
	} catch (...) {
		ErrorLogHandler::addError("eliminarFigura","excepcion al eliminar una figura de la lista (figuras.remove)");
	};
}

void Terreno::arrastrarFigura(double posClickX,double posClickY,double cantMovX,double cantMovY)
{
	if (figuraActiva != NULL){

		figuraActiva->cambiarPosicion(cantMovX, cantMovY);
		//si se fue el centro del terreno lo vuelvo a meter

		corregirPosicion(figuraActiva);

		this->setCambio(true);
	}
}

void Terreno::soltarFigura()
{
	if (figuraActiva){
		agregarFigura(figuraActiva);
		figuraActiva=NULL;
	}
}

bool Terreno::hayFiguras(){

	if ((figuraActiva != NULL)||(!figuras.empty()))
		return true;

	return false;
}

void Terreno::borrarFigura(double posClickX, double posClickY){
//aca ya no puede haber una figura activa, porque solo se llega al hacer un shift-click

	Figura* figuraABorrar = buscarFigura(posClickX, posClickY);

	if (figuraABorrar){
		//saco de la lista y libero memoria
		eliminarFigura(figuraABorrar);
		setCambio(true);
		delete figuraABorrar;
	}

}

int Terreno::getAncho(){
	return (this->ancho);
};
int Terreno::getAlto(){
	return (this->alto);
};
const char* Terreno::getFondo(){ //si es "" es porq no pusieron ningun fondo (esta el default)
	return this->fondoID;
};
std::list<Figura*> Terreno::getListaFigs(){
	return this->figuras;
};


void Terreno::cambioVistaFiguras(){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		(*iteradorLista)->setCambio(true);
	}

}

void Terreno::resizear(EscalasDeEjes* escalas){

	//si cambiaron las escalas...consigo una nueva superficie del tamanio correcto
	ancho = escalas->getCantidadUnidadesFisicasX(ANCHO_TERRENO_LOGICO);
	alto =  escalas->getCantidadUnidadesFisicasY(ALTO_TERRENO_LOGICO);

	delete sup;
	sup = new Superficie(ancho,alto);

	Imagen* temp = NULL;

	temp = img->scaleImagen(ancho,alto);

	delete img;

	img = temp;

}

void Terreno::buscarActiva(double posClickX ,double posClickY){
	//si todavia no hay una
	if (!figuraActiva){ 

		figuraActiva = buscarFigura(posClickX ,posClickY);
		//si no la encontre confirmo que es null (o podria no hacer nada...)
		if (!figuraActiva)
			figuraActiva=NULL;
		else
			eliminarFigura(figuraActiva);
	}
}

void Terreno::corregirPosicion(Figura* fig){

	Dimension* dimension = fig->getDimension();

	while (dimension->getX() > ANCHO_TERRENO_LOGICO) dimension->setX( dimension->getX() - 1);
	while (dimension->getX() < 0) dimension->setX( dimension->getX() + 1);

	while (dimension->getY() > ALTO_TERRENO_LOGICO) dimension->setY( dimension->getY() - 1);
	while (dimension->getY() < 0) dimension->setY( dimension->getY() + 1);

}

Figura* Terreno::buscarFigura(double posClickX, double posClickY){

	if(hayFiguras()){	
		Figura* figuraBuscada = NULL;

		bool figuraEncontrada = false;
		//recorro al reves asi "agarro" la figura dibujada arriba
		std::list<Figura*>::reverse_iterator iteradorLista;
		iteradorLista = figuras.rbegin();

		while (iteradorLista != figuras.rend() && !figuraEncontrada ) {
			
			figuraEncontrada = (*iteradorLista)->esMiPosicion(posClickX,posClickY);
			figuraBuscada = (*iteradorLista);
			
			iteradorLista++;
		}

		if (figuraEncontrada)
			return figuraBuscada;
	}
		return NULL;
}