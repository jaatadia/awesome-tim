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
	fondo = NULL;
	fondoID=""; //sin fondo seria asi? (con NULL se rompe)
	//Box2D
	this->mundoBox2D = new Box2DWorld(0.0f,9.81f);
	this->mundoBox2D->setFrecuenciaActualizacion(1.0/FPS, 8, 3);
}

Terreno::~Terreno(void){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		delete (*iteradorLista);
	}

	delete this->mundoBox2D;

	//borro imagen del fondo
	if (img) delete img;
	if (fondo) delete fondo;

	delete sup;
}

void Terreno::redraw(){

	//recorro todas las figuras y las voy dibujando

	if(this->img == NULL)
		sup->restoreGris();//antes repinto todo de negro asi no quedan rastros de movimiento
	else{
		sup->restore();//por si la imagen tiene partes transparentes
		sup->dibujarImagen(this->img,NULL,0,0);
	}

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		this->mundoBox2D->actualizar((*iteradorLista));
		(*iteradorLista)->dibujar(this->sup);
	}
	//por ultimo dibujo la que estoy manipulando;
	if (figuraActiva)
		figuraActiva->dibujar(this->sup);

	this->mundoBox2D->actualizar();
}

Superficie* Terreno::getImpresion(){
	if(this->huboCambios()) redraw();
	this->setCambio(false);
	return sup;
}

bool Terreno::setFondo(const char* ruta_img){
	
	Imagen* temp = new Imagen(ruta_img);
	
	if(!temp->huboFallos()){
		delete this->fondo;
		delete this->img;
		
		fondo = temp;
		this->setCambio(true);
		this->img = fondo->scaleImagen(this->ancho,this->alto);
		fondoID = ruta_img;
	} else {
		delete temp;
		return false;
	}
	return true;
/*
	//para no abrir el archivo una y otra vez lo guardo en el contenedor
	if (Contenedor::estaMultimedia(ruta_img) == false){
		Imagen* temp = new Imagen(ruta_img);
		if(!temp->huboFallos())
			Contenedor::putMultimedia(ruta_img,temp);
	//no libero temp o borro lo del contenedor!
	}

	if (ruta_img != fondoID){
		//es distinto al fondo puesto
		Imagen* temp = (Imagen*)(Contenedor::getMultimedia(ruta_img));

		if(temp){
			this->setCambio(true);
		//	delete this->fondo;  //si hago esto la borro del contenedor!
			if (img){
				delete this->img;
				img = NULL;
			}

			fondo = temp; //guardo la original (se usa para que no se pixele con distintos resize)
			this->img = fondo->scaleImagen(this->ancho,this->alto);
			std::string ruta_temp = ruta_img;
			fondoID = ruta_temp.c_str();
		}
	//no libero temp o borro lo del contenedor!
	}
*/
}

void Terreno::agregarFigura(Figura* fig){

	fig->setTraslucido(false);
	this->setCambio(true);

//si se fue de rango del terreno lo empujo para dentro
	Dimension* dim = fig->getDimension();
	corregirPosicion(fig);

	try{
		(this->figuras).push_back(fig);
		this->mundoBox2D->agregarFigura(fig);
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

		double ang = calcularAngulo(figuraActiva , posClickX, posClickY, posClickX + cantMovX, posClickY + cantMovY);
		figuraActiva->setAngulo(ang);

		this->mundoBox2D->cambiarParametros(figuraActiva);
		this->setCambio(true);
	}
}


void Terreno::eliminarFigura(Figura* fig){

	try{
		(this->figuras).remove(fig);
		this->mundoBox2D->eliminarFigura(fig);
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
		this->mundoBox2D->cambiarParametros(figuraActiva);

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
}

int Terreno::getAlto(){
	return (this->alto);
}

std::string Terreno::getFondo(){ //si es "" es porq no pusieron ningun fondo (esta el default)
	return this->fondoID;
}

std::list<Figura*> Terreno::getListaFigs(){
	return this->figuras;
}


void Terreno::cambioVistaFiguras(){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		(*iteradorLista)->setCambio(true);
	}

}

void Terreno::resizear(){

	this->setCambio(true);

	//si cambiaron las escalas...consigo una nueva superficie del tamanio correcto
	ancho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(ANCHO_TERRENO_LOGICO);
	alto =  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(ALTO_TERRENO_LOGICO);

	delete sup;
	sup = new Superficie(ancho,alto);

	if (img != NULL){
		delete img;
		img = fondo->scaleImagen(ancho,alto);
	}
}

void Terreno::buscarActiva(double posClickX ,double posClickY){
	//si todavia no hay una
	if (!figuraActiva){ 

		figuraActiva = buscarFigura(posClickX ,posClickY);
		//si no la encontre confirmo que es null (o podria no hacer nada...)
		if (!figuraActiva)
			figuraActiva=NULL;
		else
			figuraActiva->setTraslucido(true);
			this->setCambio(true);
			
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

bool Terreno::huboCambios(){
	return true;
}


double Terreno::calcularAngulo(Figura* fig, double XVector1,double YVector1,double XVector2,double YVector2){

	double X1RelCentroFig,Y1RelCentroFig,X2RelCentroFig,Y2RelCentroFig;
	double moduloCuadrado1, moduloCuadrado2;
	double productoModulo;
	double productoEscalar;
	double variacionAngulo;
	double divisionEscalarModulo;

	X1RelCentroFig = XVector1 - fig->getDimension()->getX();
	Y1RelCentroFig = YVector1 - fig->getDimension()->getY();
	X2RelCentroFig = XVector2 - fig->getDimension()->getX();
	Y2RelCentroFig = YVector2 - fig->getDimension()->getY();

	moduloCuadrado1 = X1RelCentroFig*X1RelCentroFig + Y1RelCentroFig*Y1RelCentroFig;
	moduloCuadrado2 = X2RelCentroFig*X2RelCentroFig + Y2RelCentroFig*Y2RelCentroFig;
	//if necesario o puede romperse la raiz, en resumen, si pasa por el centro no cambio el angulo
	if ((moduloCuadrado1 != 0) && (moduloCuadrado2 != 0)){
		productoModulo = sqrt(moduloCuadrado1*moduloCuadrado2);

		productoEscalar = X1RelCentroFig*X2RelCentroFig + Y1RelCentroFig*Y2RelCentroFig;
		
		//por que si por redondeo extraño es mayor que 1 devuelve NaN el acos. 
		divisionEscalarModulo = productoEscalar/productoModulo;

		if (divisionEscalarModulo > 1)
			divisionEscalarModulo = 0.99999999999999999999999999999999999;
	
		variacionAngulo = acos(divisionEscalarModulo);

		//dado que el movimiento puede haber sido horario o antihorario y ambos dan el mismo valor averiguo hacia que lado fue
		bool esPositivo = anguloEsPositivo(X1RelCentroFig,Y1RelCentroFig,X2RelCentroFig,Y2RelCentroFig);

		if (!esPositivo)
			variacionAngulo = -variacionAngulo;

		//Paso el angulo a grados desde radianes
		variacionAngulo = (variacionAngulo*180/PI);
	}
		return (fig->getDimension()->getAngulo() + variacionAngulo);
}

int Terreno::obtenerCuadranteDeClick(double X, double Y){

	if (X>=0 && Y>=0)
		return CUADRANTE4;

	if (X<=0 && Y>=0)
		return CUADRANTE3;

	if (X<=0 && Y<=0)
		return CUADRANTE2;

	if (X>=0 && Y<=0)
		return CUADRANTE1;

	return -1;
}

bool Terreno::anguloEsPositivo(double X1, double Y1, double X2, double Y2){
	
	int cuadrante1 = obtenerCuadranteDeClick(X1,Y1);
	int cuadrante2 = obtenerCuadranteDeClick(X2,Y2);
	
	Recta recta1(X1,Y1,0,0);

	if (cuadrante1 == cuadrante2){
		//verificar con las rectas
		switch (cuadrante1){
			case CUADRANTE1: case CUADRANTE4:
			{
				if(recta1.puntoPorDebajo(X2,Y2))
					return false;
				else
					return true;
				break;
			}
			case CUADRANTE2: case CUADRANTE3:
			{
				if(recta1.puntoPorDebajo(X2,Y2))
					return true;
				else
					return false;
				break;
			}
		}
	}else
		switch (cuadrante1){
			case CUADRANTE1:
			{
				if (cuadrante2 == CUADRANTE2)
					return true;
				else
					if (cuadrante2 == CUADRANTE4)
						return false;
				break;
			}
			case CUADRANTE2:
			{
				if (cuadrante2 == CUADRANTE3)
					return true;
				else
					if (cuadrante2 == CUADRANTE1)
						return false;
				break;
			}
			case CUADRANTE3:
			{
				if (cuadrante2 == CUADRANTE4)
					return true;
				else
					if (cuadrante2 == CUADRANTE2)
						return false;
				break;
			}
			case CUADRANTE4:
			{
				if (cuadrante2 == CUADRANTE1)
					return true;
				else
					if (cuadrante2 == CUADRANTE3)
						return false;
				break;
			}
		}
	//por defecto asumo que es positivo
	return true;
}
