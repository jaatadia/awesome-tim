#include "Terreno.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"
#include <new>

#include "FiguraCompuesta.h"
#include "Soga.h"
#include "Tijera.h"
#include "Huevo.h"
#include "PaletaFlipper.h"
#include "RemoveFigureMessage.h"
#include "ActualizeFigureMessage.h"
#include "CloseScissorMessage.h"
#include "PopBalloonMessage.h"
#include "FireShotgunMessage.h"
#include "BreakEggMessage.h"

Terreno::Terreno(int ancho,int alto,MaquinaEstados* maq,bool fisicaActiva){
	
	this->maq = maq;
	this->fisicaActiva = fisicaActiva;
	
	x1 = 0;
	y1 = 0;
	x2 = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(ancho);
	y2 = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(alto);

	ex1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x1);
	ex2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x2);
	ey1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y1);
	ey2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y2);

	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
	this->figuras = std::list<Figura*>();

	figuraActiva=NULL;
	posAntFigActiva.setX(0);
	posAntFigActiva.setY(0);
	angAntFigActiva = 0;
	largoAntFigActiva = -1;

	img=NULL;
	fondo = NULL;
	fondoID=""; //sin fondo seria asi? (con NULL se rompe)
	this->setCambio(true);

	contEventosMov = 0;

	//Box2D
	if(this->fisicaActiva){
		this->mundoBox2D = new Box2DWorld(GRAVEDADX,GRAVEDADY,fisicaActiva);
		this->mundoBox2D->setFrecuenciaActualizacion(1.0/FPS, 10, 10);
	}else{
		this->mundoBox2D = NULL;
	}
}

Terreno::~Terreno(void){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		Figura* fig = (*iteradorLista);
		delete fig;
	}

	if(fisicaActiva) delete this->mundoBox2D;

	//borro imagen del fondo
	if (img) delete img;
	if (fondo) delete fondo;

	delete sup;
}


void Terreno::setMiPorcion(double x1, double y1, double x2, double y2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	ex1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x1);
	ex2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x2);
	ey1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y1);
	ey2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y2);

}

void Terreno::redraw(){

	//antes que nada corrijo posiciones para que las sogas se dibujen lindo
	arreglarPosicionSogas();

	//recorro todas las figuras y las voy dibujando

	if(this->img == NULL)
		sup->restoreGris();//antes repinto todo de negro asi no quedan rastros de movimiento
	else{
		sup->restore();//por si la imagen tiene partes transparentes
		sup->dibujarImagen(this->img,NULL,0,0);
	}

	std::list<Figura*> figurasAux;
	std::list<Figura*> figurasFinales;
	std::list<Figura*>::iterator iteradorLista;
	
	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		if((*iteradorLista)->esUnion()){
			double x = (*iteradorLista)->getDimension()->getX();
			double y = (*iteradorLista)->getDimension()->getY();
			double ancho = (*iteradorLista)->getDimension()->getAncho()/2.0;
			double alto = (*iteradorLista)->getDimension()->getAlto()/2.0;
			
			if(((x+ancho)>0)&&((x-ancho)<ANCHO_TERRENO_LOGICO)&&((y+alto)>0)&&((y-alto)<ALTO_TERRENO_LOGICO))
					(*iteradorLista)->dibujar(this->sup);	
			
		}else{
			if (! ( (*iteradorLista)->getTipoFigura()== CANIO||(*iteradorLista)->getTipoFigura()== CODO ) ){
				figurasAux.push_back((*iteradorLista));
			} else {
				figurasFinales.push_back((*iteradorLista));
			}
		}
	}

	for (iteradorLista = figurasAux.begin() ; iteradorLista != figurasAux.end(); iteradorLista++){
		double x = (*iteradorLista)->getDimension()->getX();
		double y = (*iteradorLista)->getDimension()->getY();
		double ancho = (*iteradorLista)->getDimension()->getAncho()/2.0;
		double alto = (*iteradorLista)->getDimension()->getAlto()/2.0;
		
		if(((x+ancho)>0)&&((x-ancho)<ANCHO_TERRENO_LOGICO)&&((y+alto)>0)&&((y-alto)<ALTO_TERRENO_LOGICO)){
			(*iteradorLista)->dibujar(this->sup);
		}
	}
	//dibujo los canios y codos

	for (iteradorLista = figurasFinales.begin() ; iteradorLista != figurasFinales.end(); iteradorLista++){
		double x = (*iteradorLista)->getDimension()->getX();
		double y = (*iteradorLista)->getDimension()->getY();
		double ancho = (*iteradorLista)->getDimension()->getAncho()/2.0;
		double alto = (*iteradorLista)->getDimension()->getAlto()/2.0;
		
		if(((x+ancho)>0)&&((x-ancho)<ANCHO_TERRENO_LOGICO)&&((y+alto)>0)&&((y-alto)<ALTO_TERRENO_LOGICO)){
			(*iteradorLista)->dibujar(this->sup);
		}
	}
	
	//dibujo las sogas extra
	std::list<Soga*>::iterator iteradorLstSogas;
	for (iteradorLstSogas = sogasExtra.begin() ; iteradorLstSogas != sogasExtra.end(); iteradorLstSogas++){
		double x = (*iteradorLstSogas)->getDimension()->getX();
		double y = (*iteradorLstSogas)->getDimension()->getY();
		double ancho = (*iteradorLstSogas)->getDimension()->getAncho()/2.0;
		double alto = (*iteradorLstSogas)->getDimension()->getAlto()/2.0;
		
		if(((x+ancho)>0)&&((x-ancho)<ANCHO_TERRENO_LOGICO)&&((y+alto)>0)&&((y-alto)<ALTO_TERRENO_LOGICO)){
			(*iteradorLstSogas)->dibujar(this->sup);
		}
	}

	//borro las sogas extra
	sogasExtra.clear();

	//por ultimo dibujo la que estoy manipulando;
	if (figuraActiva)
		figuraActiva->dibujar(this->sup);

	//dibujo la zona del jugador en modo edicion
	if(!fisicaActiva){
		
		Superficie super(sup->getAncho(),sup->getAlto());
		super.setTransparency(150);
		Rectangulo rect;
		
		//dibujo arriba
		rect.x =0;
		rect.y =0;
		rect.ancho = sup->getAncho();
		rect.alto = ey1;
		sup->dibujarSupreficie(&super,&rect,0,0);
		
		//dibujo abajo
		rect.x =0;
		rect.y =0;
		rect.ancho = sup->getAncho();
		rect.alto = sup->getAlto()-ey2;
		sup->dibujarSupreficie(&super,&rect,0,ey2);

		//dibujo izquierda
		rect.x =0;
		rect.y =0;
		rect.ancho = ex1;
		rect.alto = ey2-ey1;
		sup->dibujarSupreficie(&super,&rect,0,ey1);
		
		//dibujo derecha
		rect.x =0;
		rect.y =0;
		rect.ancho = sup->getAncho()-ex2;
		rect.alto = ey2-ey1;
		sup->dibujarSupreficie(&super,&rect,ex2,ey1);
		
	}
	
	//dibujo el recuadro
	sup->dibujarLinea(ex1,ey1,ex1,ey2,2,30,30,30);	 
	sup->dibujarLinea(ex1,ey1,ex2,ey1,2,30,30,30);	 
	sup->dibujarLinea(ex1,ey2,ex2,ey2,2,30,30,30);	 
	sup->dibujarLinea(ex2,ey1,ex2,ey2,2,30,30,30);	 
}

Superficie* Terreno::getImpresion(){
	if(this->huboCambios()){
		redraw();
		this->setCambio(false);
	}
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
}

bool Terreno::agregarFigura(Figura* fig){

	if(!fisicaActiva){
		if((fig->getTipoFigura()==LINEA)&&(fig->getFigura1()==NULL)&&(fig->getFigura2()==NULL)){
			Linea* linea = (Linea*)fig;
			double x,y;
			linea->getPunto1(&x,&y);
			Figura* result1 = getFiguraAtableCorrea(x,y);
			linea->getPunto2(&x,&y);
			Figura* result2 = getFiguraAtableCorrea(x,y);
			if((result1 == NULL) || (result2 == NULL)){
				delete fig;
				return false;
			}
			linea->setFigura1(result1);
			linea->setFigura2(result2);
			result1->atarCorrea();
			result2->atarCorrea();
		
		}else if((fig->getTipoFigura()==SOGA)&&(fig->getFigura1()==NULL)&&(fig->getFigura2()==NULL)){
			Soga* soga = (Soga*)fig;
			double x1,y1,x2,y2;
			soga->getPunto1(&x1,&y1);
			Figura* result1 = getFiguraAtableSoga(x1,y1);
			soga->getPunto2(&x2,&y2);
			Figura* result2 = getFiguraAtableSoga(x2,y2);
			
			if((result1 == NULL) || (result2 == NULL)){
				delete soga;
				return false;
			}

			double num1 = result1->esAtableSoga(x1,y1);
			double num2 = result2->esAtableSoga(x2,y2);

			soga->setFigura1(result1);
			soga->setFigura2(result2);
			soga->setNumsPosAtable(num1,num2);
			result1->atarSoga(num1);
			result2->atarSoga(num2);
		}
	}

	fig->setTraslucido(false);
	this->setCambio(true);

	//si se fue de rango del terreno lo empujo para dentro
	Dimension* dim = fig->getDimension();
	corregirPosicion(fig);

	try{
		bool aux;
		if(fisicaActiva){
			aux = this->mundoBox2D->agregarFigura(fig);
			if(aux){
				if(fig->getTipoFigura()==SOGA){
					std::list<Figura*> segmentos = ((Soga*)fig)->getSegmentos();
					std::list<Figura*>::iterator iteradorLista;
					bool puestas = false;
					for (iteradorLista = segmentos.begin() ; iteradorLista != segmentos.end(); iteradorLista++){
						(this->figuras).push_back((*iteradorLista));
						puestas = true;
					}
					if (!puestas) (this->figuras).push_back(fig);
				}else{
					(this->figuras).push_back(fig);
					if(fig->esObjetivo()){
						this->objetivos.push_back(fig);
					}
				}
			}else{ 
				delete fig;
			}
		}else{
			(this->figuras).push_back(fig);
			if(fig->esObjetivo()){
						this->objetivos.push_back(fig);
			}
		}
	} catch (...) {
		ErrorLogHandler::addError("agregarFigura","excepcion al agregar en la lista (figuras.push_back)");
	};

	return true;
}

void Terreno::rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY){
	//practicamente lo mismo que arrastraFigura
	if ((figuraActiva != NULL) && (figuraActiva->rotable())){
		//calculo el angulo y se lo pongo a figura
		double X2,Y2;
		X2 = posClickX + cantMovX;
		Y2 = posClickY + cantMovY;

		double ang = calcularAngulo(figuraActiva->getDimension() , posClickX, posClickY, posClickX + cantMovX, posClickY + cantMovY);
		figuraActiva->setAngulo(ang);

		//como ver si se superpone tarda demasiado lo hago solo cada x movimientos!
		if (contEventosMov % 2 == 0){
			//si choca va de rojo
			figuraActiva->setSuperpuesta( this->posicionOcupada(figuraActiva) );						
		}

		contEventosMov++;
		if (contEventosMov > 10000){
			contEventosMov = 0;
		}


		if(fisicaActiva) this->mundoBox2D->cambiarParametros(figuraActiva);
		this->setCambio(true);
	}
}


void Terreno::eliminarFigura(Figura* fig){

	try{
		(this->figuras).remove(fig);
		if(fig->esObjetivo()){
			this->objetivos.remove(fig);
		}
		if(fisicaActiva) this->mundoBox2D->eliminarFigura(fig);
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
		if(fisicaActiva)this->mundoBox2D->cambiarParametros(figuraActiva);

		//como ver si se superpone tarda demasiado lo hago solo cada 5 movimientos!
		if (contEventosMov % ITER_CHOQUE == 0){
			//si choca va de rojo
			figuraActiva->setSuperpuesta( this->posicionOcupada(figuraActiva) );						
		}

		contEventosMov++;

		if (contEventosMov > 10000){
			contEventosMov = 0;
		}

		this->setCambio(true);
	}
}


void Terreno::agrandarFigura()
{
	if (figuraActiva != NULL){
		figuraActiva->agrandar();

		//si se fue el centro del terreno lo vuelvo a meter
		corregirPosicion(figuraActiva);
		if(fisicaActiva)this->mundoBox2D->cambiarParametros(figuraActiva);
		this->setCambio(true);
		bool choca = this->posicionOcupada(figuraActiva);
		figuraActiva->setSuperpuesta(choca);
	}
}

void Terreno::shiftFigura()
{
	if (figuraActiva != NULL){
		figuraActiva->shift();

		//si se fue el centro del terreno lo vuelvo a meter
		corregirPosicion(figuraActiva);
		if(fisicaActiva)this->mundoBox2D->cambiarParametros(figuraActiva);
		this->setCambio(true);
	}
}

void Terreno::achicarFigura()
{
	if (figuraActiva != NULL){

		figuraActiva->achicar();

		if(fisicaActiva)this->mundoBox2D->cambiarParametros(figuraActiva);
		this->setCambio(true);

		bool choca = this->posicionOcupada(figuraActiva);
		figuraActiva->setSuperpuesta(choca);
	}
}

void Terreno::soltarFigura(bool flag)
{
	if (figuraActiva){
		bool poner = ((flag) || (adentroZonaTerreno(figuraActiva->getDimension()->getX(),figuraActiva->getDimension()->getY())));
		if (!(figuraActiva->superpuesta) && poner ){
			agregarFigura(figuraActiva);
			figuraActiva=NULL;
		}else{
			//la meto con su posicion / angulo / largo anterior
			figuraActiva->setX(posAntFigActiva.getX());
			figuraActiva->setY(posAntFigActiva.getY());
			figuraActiva->setAngulo(angAntFigActiva);
			figuraActiva->setLargo(largoAntFigActiva);
			
			agregarFigura(figuraActiva);

			//y ya no esta chocando
			figuraActiva->setSuperpuesta(false);

			figuraActiva = NULL;
		}
	}
}

bool Terreno::hayFiguras(){

	if ((figuraActiva != NULL)||(!figuras.empty()))
		return true;

	return false;
}

std::vector<int> Terreno::borrarFigura(double posClickX, double posClickY,Figura* vector[]){
//aca ya no puede haber una figura activa, porque solo se llega al hacer un shift-clickt

	std::vector<int> tiposBorradas;

	Figura* figuraABorrar = buscarFigura(posClickX, posClickY);

	if (figuraABorrar){
		//saco de la lista y libero memoria
		eliminarFigura(figuraABorrar);
		setCambio(true);
		
		if(figuraABorrar->esUnion()){
			figuraABorrar->desUnir();
			vector[figuraABorrar->numero] = NULL;
		}else{
			std::list<Figura*>::iterator iteradorLista;
			std::list<Figura*> listaFigAux;
			iteradorLista = figuras.begin();

			//se buscan y desatan sogas y correas
			while (iteradorLista != figuras.end()) {
				if((*iteradorLista)->esUnion()){
					Figura* correa = (*iteradorLista);
					if ((correa->getFigura1() == figuraABorrar)||(correa->getFigura2() == figuraABorrar)){
						listaFigAux.push_back(correa);
					}
				}
				iteradorLista++;
			}

			for(std::list<Figura*>::iterator iter = listaFigAux.begin();iter != listaFigAux.end();iter++){
				eliminarFigura(*iter);
				(*iter)->desUnir();

				tiposBorradas.push_back((*iter)->getTipoFigura());
				
				vector[(*iter)->numero] = NULL;
				delete (*iter);
			}
		}
		
		tiposBorradas.push_back(figuraABorrar->getTipoFigura());
		delete figuraABorrar;
	}

	return tiposBorradas;
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
	
	ex1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x1);
	ex2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x2);
	ey1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y1);
	ey2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y2);

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
		if (!figuraActiva){
			figuraActiva=NULL;
		}else{
			//la pongo traslucida, cambio el terreno y la saco de la lista
			
			figuraActiva->setTraslucido(true);
			this->setCambio(true);
			eliminarFigura(figuraActiva);
			//y me guardo sus parametros por si choca cuando la suelto
			posAntFigActiva.putPos(figuraActiva->getDimension()->getX(),figuraActiva->getDimension()->getY());
			angAntFigActiva = figuraActiva->getDimension()->getAngulo();
			largoAntFigActiva = figuraActiva->getLargo();
		}
	}
}

void Terreno::corregirPosicion(Figura* fig){

	Dimension* dimension = fig->getDimension();

	while (dimension->getX() > ANCHO_TERRENO_LOGICO) fig->setX( dimension->getX() - 1);
	while (dimension->getX() < 0) fig->setX( dimension->getX() + 1);

	while (dimension->getY() > ALTO_TERRENO_LOGICO) fig->setY( dimension->getY() - 1);
	while (dimension->getY() < 0) fig->setY( dimension->getY() + 1);

}

bool Terreno::adentroZonaTerreno(double posX,double posY){

	bool adentro = false;
	double margen = 1;

	if((posX >= (this->x1+margen)) && (posX <= (this->x2-margen))){
		if((posY >= (this->y1+margen)) && (posY <= (this->y2-margen))){
			adentro = true;
		}
	}
	return adentro;

}

Figura* Terreno::buscarFigura(double posClickX, double posClickY){

	if(! adentroZonaTerreno(posClickX,posClickY)){
		return NULL;
	}
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

		if (figuraEncontrada){
			if(figuraBuscada->esFija())
				return NULL;

			return figuraBuscada;
		}
	}
	return NULL;
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

void Terreno::actualizarModelo(Figura* vector[]){

	if (fisicaActiva){

		std::list<Figura*>::iterator iteradorLista;
		for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
			(*iteradorLista)->corregirEstado();
		}

		this->mundoBox2D->actualizar();
		this->mundoBox2D->actualizar(NULL);
		this->setCambio(true);

		std::list<Soga*> sogas;
		std::list<Figura*> listaCortanSoga;
		std::list<Figura*> nuevasFiguras;
		for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
			
			if((*iteradorLista)->getTipoFigura()==TIJERA){
				if(((Tijera*)(*iteradorLista))->cortaSoga()){
					CloseScissorMessage* c_msg = new CloseScissorMessage();
					c_msg->setFigureID((*iteradorLista)->numero);
					this->maq->pushSendMessage(c_msg);
				}
				((Tijera*)(*iteradorLista))->actualizar();
			}
			if((*iteradorLista)->getTipoFigura()==ESCOPETA){
				Figura* bala = mundoBox2D->dispararEscopeta((Escopeta*)(*iteradorLista));
				if(bala != NULL){
					nuevasFiguras.push_back(bala);
					int i = 0;
					while(true){
						if(vector[i]==NULL) break;
						i++;
					}
					bala->numero = i;
					vector[i] = bala;
					FireShotgunMessage* fs_msg = new FireShotgunMessage();
					fs_msg->setGunID((*iteradorLista)->numero);
					fs_msg->setProyectileID(i);
					this->maq->pushSendMessage(fs_msg);
				}
			}
			if((*iteradorLista)->getTipoFigura()==ARCO){
				Figura* flecha = ((Arco*)(*iteradorLista))->disparar();
				if(flecha != NULL){
					nuevasFiguras.push_back(flecha);
					int i = 0;
					while(true){
						if(vector[i]==NULL) break;
						i++;
					}
					flecha->numero = i;
					vector[i] = flecha;
					FireBowMessage* fb_msg = new FireBowMessage();
					fb_msg->setGunID((*iteradorLista)->numero);
					fb_msg->setProyectileID(i);
					this->maq->pushSendMessage(fb_msg);
				}
			}
			
			if((*iteradorLista)->getTipoFigura()==SOGA){
				((Linea*)(*iteradorLista))->actualizar();
				sogas.push_back((Soga*)(*iteradorLista));
			}else if((*iteradorLista)->getTipoFigura()==LINEA){
				((Linea*)(*iteradorLista))->actualizar();
			}else if((*iteradorLista)->getTipoFigura()==HUEVO){
				if(((Huevo*)(*iteradorLista))->estaRompiendo()){
					BreakEggMessage* be_msg = new BreakEggMessage();
					be_msg->setFigureID((*iteradorLista)->numero);
					this->maq->pushSendMessage(be_msg);
					mundoBox2D->eliminarFigura((*iteradorLista));
				}
				((Huevo*)(*iteradorLista))->actualizar();
				ActualizeFigureMessage* a_msg = new ActualizeFigureMessage();
				a_msg->setFigureID((*iteradorLista)->numero);
				this->maq->pushSendMessage(a_msg);
				if(((Huevo*)(*iteradorLista))->estaRompiendo()){
					mundoBox2D->eliminarFigura((*iteradorLista));
				}
			}else if((*iteradorLista)->getTipoFigura()==GLOBOHELIO){
				if(((GloboHelio*)(*iteradorLista))->estaPinchando()){
					PopBalloonMessage* p_msg = new PopBalloonMessage();
					p_msg->setFigureID((*iteradorLista)->numero);
					this->maq->pushSendMessage(p_msg);
					
					borrarAtadura(*iteradorLista);
					mundoBox2D->eliminarFigura((*iteradorLista));
				}
				((GloboHelio*)(*iteradorLista))->actualizar();
				ActualizeFigureMessage* a_msg = new ActualizeFigureMessage();
				a_msg->setFigureID((*iteradorLista)->numero);
				this->maq->pushSendMessage(a_msg);

			}else if((*iteradorLista)->cortaSoga()){
				listaCortanSoga.push_back((*iteradorLista));
			}
		}
		
		std::list<Soga*>::iterator iterSogas;
		for (iterSogas = sogas.begin();iterSogas != sogas.end();iterSogas++){
			for (iteradorLista = listaCortanSoga.begin() ; iteradorLista != listaCortanSoga.end(); iteradorLista++){
				if( (!(*iterSogas)->estaMarcada())&&
					//(((*iterSogas)->getFigura1()!=(*iteradorLista))&&((*iterSogas)->getFigura2()!=(*iteradorLista)))&&
					//((*iterSogas)->meChoca((*iteradorLista)))){
					((*iterSogas)->meChoca((*iteradorLista)))){
						this->mundoBox2D->eliminarSoga(*iterSogas);
						(*iterSogas)->marcar(true);
				}
			}
		}

		
		std::list<Figura*> listaABorrar;
		std::list<Figura*>::iterator iterLista;
		for (iterLista = figuras.begin();iterLista != figuras.end();iterLista++){
			if((*iterLista)->estaMarcada()){
				listaABorrar.push_back((*iterLista));
			}
		}

		for(iterLista = listaABorrar.begin();iterLista != listaABorrar.end();iterLista++){
			figuras.remove(*iterLista);
			RemoveFigureMessage* r_msg = new RemoveFigureMessage();
			r_msg->setFigureID((*iterLista)->numero);
			this->maq->pushSendMessage(r_msg);
			if(!(*iterLista)->esObjetivo())	delete((*iterLista));
		}

		for(iterLista = nuevasFiguras.begin();iterLista != nuevasFiguras.end();iterLista++){
			mundoBox2D->agregarFigura(*iterLista);
			figuras.push_back(*iterLista);
		}


	}else{
		std::list<Figura*>::iterator iteradorLista;
		for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
			if(((*iteradorLista)->getTipoFigura()==SOGA) ||((*iteradorLista)->getTipoFigura()==LINEA)){
				((Linea*)(*iteradorLista))->actualizar();
				this->setCambio(true);
			}
		}
	}
}

bool Terreno::posEnTerrenoExtendido(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_TERRENO_LOGICO - ANCHO_TERRENO_LOGICO ;
	finalLogicoX = ANCHO_TERRENO_LOGICO + X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO;
	ppioLogicoY = Y_TERRENO_LOGICO - ALTO_TERRENO_LOGICO;
	finalLogicoY = ALTO_TERRENO_LOGICO + Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO;

	//std::cout<<posY<<std::endl; //a ver porque no se va por arriba...

	//return ((posX > ppioLogicoX) || (posX < finalLogicoX) || (posY > ppioLogicoY) || (posY < finalLogicoY)) ;
	return true;
}

void Terreno::dibujate(Superficie* sup,int xIni,int yIni){
	
	sup->dibujarImagen(this->img,NULL,xIni,yIni);
	
	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		double x = (*iteradorLista)->getDimension()->getX();
		double y = (*iteradorLista)->getDimension()->getY();
		double ancho = (*iteradorLista)->getDimension()->getAncho()/2.0;
		double alto = (*iteradorLista)->getDimension()->getAlto()/2.0;
		
		if(((x+ancho)>0)&&((x-ancho)<ANCHO_TERRENO_LOGICO)&&
			((y+alto)>0)&&((y-alto)<ALTO_TERRENO_LOGICO))
				(*iteradorLista)->dibujar(sup,xIni,yIni);
	}
	//por ultimo dibujo la que estoy manipulando;
	if (figuraActiva)
		figuraActiva->dibujar(sup,xIni,yIni);

}


double Terreno::calcularAngulo(Dimension* dim, double XVector1,double YVector1,double XVector2,double YVector2){

	double X1RelCentroFig,Y1RelCentroFig,X2RelCentroFig,Y2RelCentroFig;
	double moduloCuadrado1, moduloCuadrado2;
	double productoModulo;
	double productoEscalar;
	double variacionAngulo;
	double divisionEscalarModulo;

	X1RelCentroFig = XVector1 - dim->getX();
	Y1RelCentroFig = YVector1 - dim->getY();
	X2RelCentroFig = XVector2 - dim->getX();
	Y2RelCentroFig = YVector2 - dim->getY();

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
	}else{
		variacionAngulo = 0;
	}
		return (dim->getAngulo() + variacionAngulo);
}

Figura* Terreno::getFiguraAtableCorrea(double x,double y){
	if(hayFiguras()){	
		Figura* figuraBuscada = NULL;

		bool figuraEncontrada = false;
		//recorro al reves asi "agarro" la figura dibujada arriba
		std::list<Figura*>::reverse_iterator iteradorLista;
		iteradorLista = figuras.rbegin();

		while (iteradorLista != figuras.rend() && !figuraEncontrada ) {
			
			figuraEncontrada = (((*iteradorLista)->esMiPosicion(x,y))&&((*iteradorLista)->esAtableCorrea()));
			figuraBuscada = (*iteradorLista);
			
			iteradorLista++;
		}

		if (figuraEncontrada)
			return figuraBuscada;
	}
	return NULL;
}

Figura* Terreno::getFiguraAtableSoga(double x,double y){
	if(hayFiguras()){	
		
		Figura* figuraBuscada = NULL;
		bool figuraEncontrada = false;
		
		//recorro al reves asi "agarro" la figura dibujada arriba
		std::list<Figura*>::iterator iteradorLista;
		iteradorLista = figuras.begin();

		while ((iteradorLista != figuras.end()) && (!figuraEncontrada)) {
			
			figuraEncontrada = (*iteradorLista)->esMiPosicion(x,y);
			figuraEncontrada &= ((*iteradorLista)->esAtableSoga(x,y)!=-1);
			figuraBuscada = (*iteradorLista);
			
			iteradorLista++;
		}

		if (figuraEncontrada)
			return figuraBuscada;
	}
	return NULL;
}

bool Terreno::posicionOcupada(Figura* figAPosicionar){

	bool choca1 = false;
	bool choca2 = false;

	std::list<Figura*>::iterator iteradorLista;
	iteradorLista = figuras.begin();

	while ( iteradorLista != figuras.end() && !choca1 && !choca2 ) {
		if(!(*iteradorLista)->esUnion()){
			choca1 = figAPosicionar->choqueConFigura((*iteradorLista));
			choca2 = (*iteradorLista)->choqueConFigura(figAPosicionar);
		}
		iteradorLista++;
	}

	return (choca1 || choca2);
}

void Terreno::borrarAtadura(Figura* fig){
	std::list<Figura*>::iterator iter;
	for(iter = figuras.begin();iter!=figuras.end();iter++){
		if((*iter)->getTipoFigura()==SOGA){
			if((*iter)->getFigura1()==fig){
				this->mundoBox2D->eliminarSoga((Soga*)(*iter));
			}else if((*iter)->getFigura2()==fig){
				this->mundoBox2D->eliminarSoga((Soga*)(*iter));
			}
		}
	}
}

void Terreno::interactuar(double posClickX, double posClickY, int accion){

	Figura* figAInteract;
	
	if (this->adentroZonaTerreno(posClickX,posClickY)){
		figAInteract = this->buscarFigura(posClickX,posClickY);
		if(figAInteract != NULL){
			figAInteract->interactuar(accion);
		}
	}

}
void Terreno::interactuar(int accion){

	for (std::list<Figura*>::iterator iter = figuras.begin();iter != figuras.end();iter++){
				(*iter)->interactuar(accion);
	}
}

bool Terreno::objetivosCumplidos(){
	if (this->objetivos.size() == 0) return false;

	std::list<Figura*>::iterator iter;
	for(iter = objetivos.begin();iter != objetivos.end();iter++){
		if(!(*iter)->cumplioObjetivo()) return false;
	}
	return true;
}


void Terreno::arreglarPosicionSogas(){
//todo el metodo es horrible pero no se como mas hacerlo
	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		if ((*iteradorLista)->esPolea()){

			//obtengo las sogas y seteo sus extremos a las esquinas de arriba de la polea
			//luego creo una soga entre ellos
			Soga* sogaIzq = ((Polea*)(*iteradorLista))->getSogaIzq();
			Soga* sogaDer = ((Polea*)(*iteradorLista))->getSogaDer();

			double xIzq1,yIzq1,xIzq2,yIzq2;
			double xDer1,yDer1,xDer2,yDer2;
			double nuevoXIzq,nuevoYIzq,nuevoXDer,nuevoYDer;
			//si no estan ambas sogas no necesito hacer nada (ya se dibuja "bien") 
			if ((sogaIzq) && (sogaDer)){
				//obtengo los puntos de las sogas
				sogaIzq->getPunto1(&xIzq1, &yIzq1);
				sogaIzq->getPunto2(&xIzq2, &yIzq2);
				//analogo para la soga derecha
				sogaDer->getPunto1(&xDer1,&yDer1);
				sogaDer->getPunto2(&xDer2,&yDer2);

				Dimension* dim = (*iteradorLista)->getDimension();
				//me quedo con el punto que esta en el centro de la polea
				//mejor dicho el que este a menor distancia del centro porque aparentemente
				//ninguno esta en el centro, pero sí es casi una disposicion radial
				double dist1, dist2;

				dist1 = sqrt ( (xIzq1-dim->getX()) * (xIzq1-dim->getX()) + (yIzq1-dim->getY()) * (yIzq1-dim->getY()));
				dist2 = sqrt ( (xIzq2-dim->getX()) * (xIzq2-dim->getX()) + (yIzq2-dim->getY()) * (yIzq2-dim->getY()));

				if ( dist1 <= dist2 ){
					//lo corro a la izq y arriba de la polea
					nuevoXIzq = xIzq1;
					nuevoYIzq = yIzq1;
					//sogaIzq->setPunto1(nuevoXIzq, nuevoYIzq);
				}else{
				//si no era el otro punto mas vale que este sea
					nuevoXIzq = xIzq2;
					nuevoYIzq = yIzq2;
					//sogaIzq->setPunto2(nuevoXIzq, nuevoYIzq);
				}
	
				//altero el punto que esta en el centro de la polea
				//mejor dicho el que este a menor distancia del centro porque aparentemente
				//ninguno esta en el centro

				dist1 = sqrt ( (xDer1-dim->getX()) * (xDer1-dim->getX()) + (yDer1-dim->getY()) * (yDer1-dim->getY()));
				dist2 = sqrt ( (xDer2-dim->getX()) * (xDer2-dim->getX()) + (yDer2-dim->getY()) * (yDer2-dim->getY()));

				if ( dist1 <= dist2 ){
					//lo corro a la der y arriba de la polea
					nuevoXDer = xDer1;
					nuevoYDer = yDer1;
					//sogaIzq->setPunto1(nuevoXDer, nuevoYDer);
				}else{
				//si no era el otro punto mas vale que este sea
					nuevoXDer = xDer2;
					nuevoYDer = yDer2;
					//sogaIzq->setPunto2(nuevoXDer, nuevoYDer);
				}
			
				//verifico que soga es en realidad la izq y la der porque los nombres de javier
				//no significan nada
				if (nuevoXDer < nuevoXIzq){
					//si estan al reves swapeo
					Soga* sogaAux = sogaIzq;
					sogaIzq = sogaDer;
					sogaDer = sogaAux;
				}

				//corro los puntos a las esquinas de arriba de la polea
				//de nuevo tengo que verificar cual es el mas cercano al centro
				dist1 = sqrt ( (xIzq1-dim->getX()) * (xIzq1-dim->getX()) + (yIzq1-dim->getY()) * (yIzq1-dim->getY()));
				dist2 = sqrt ( (xIzq2-dim->getX()) * (xIzq2-dim->getX()) + (yIzq2-dim->getY()) * (yIzq2-dim->getY()));

				if ( dist1 <= dist2 ){
					nuevoXIzq = xIzq1 + dim->getAncho()/2 - 3;
					nuevoYIzq = yIzq1 - dim->getAlto()/2 ;
					sogaIzq->setPunto1(nuevoXIzq, nuevoYIzq);
				}else{
					nuevoXIzq = xIzq2 + dim->getAncho()/2 - 3;
					nuevoYIzq = yIzq2 - dim->getAlto()/2 ;
					sogaIzq->setPunto2(nuevoXIzq, nuevoYIzq);
				}
	
				dist1 = sqrt ( (xDer1-dim->getX()) * (xDer1-dim->getX()) + (yDer1-dim->getY()) * (yDer1-dim->getY()));
				dist2 = sqrt ( (xDer2-dim->getX()) * (xDer2-dim->getX()) + (yDer2-dim->getY()) * (yDer2-dim->getY()));

				if ( dist1 <= dist2 ){
					nuevoXDer = xDer1 - dim->getAncho()/2 + 3;
					nuevoYDer = yDer1 - dim->getAlto()/2 ;
					sogaDer->setPunto1(nuevoXDer, nuevoYDer);
				}else{
					nuevoXDer = xDer2 - dim->getAncho()/2 + 3;
					nuevoYDer = yDer2 - dim->getAlto()/2;
					sogaDer->setPunto2(nuevoXDer, nuevoYDer);
				}

				//ahora creo una soga que une los puntos
				//se eliminan luego de dibujar (en el metodo redraw())
				Soga* sogaUnion = new Soga(nuevoXIzq, nuevoYIzq, nuevoXDer, nuevoYDer);
				
				//tengo que hacer esto para que cambie la vista...
				sogaUnion->setPunto1(nuevoXIzq, nuevoYIzq);

				sogasExtra.push_back(sogaUnion);
			}
		}
	}

}