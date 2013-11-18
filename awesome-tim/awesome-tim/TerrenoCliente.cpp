#include "TerrenoCliente.h"
#include "ErrorLogHandler.h"
#include "Contenedor.h"
#include <new>
#include "FiguraCompuesta.h"
#include "Soga.h"
#include "Tijera.h"
#include "Huevo.h"
#include "GloboHelio.h"
#include "MaquinaEstados.h"
#include "Linea.h"

TerrenoCliente::TerrenoCliente(int ancho,int alto,MaquinaEstados* maq,int numCliente,bool fisicaActiva){
	
	this->numCliente = numCliente;
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
}

TerrenoCliente::~TerrenoCliente(void){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		Figura* fig = (*iteradorLista);
		delete fig;
	}

	//borro imagen del fondo
	if (img) delete img;
	if (fondo) delete fondo;

	delete sup;
}


void TerrenoCliente::setMiPorcion(double x1, double y1, double x2, double y2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	ex1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x1);
	ex2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x2);
	ey1 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y1);
	ey2 = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y2);

}

void TerrenoCliente::redraw(){

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


	//por ultimo dibujo la que estoy manipulando;
	if (figuraActiva)
		figuraActiva->dibujar(this->sup);

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

Superficie* TerrenoCliente::getImpresion(){
	if(fisicaActiva){
		redraw();
	}else if(this->huboCambios()){
		redraw();
		this->setCambio(false);
	}
	return sup;
}

bool TerrenoCliente::setFondo(const char* ruta_img){
	
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

bool TerrenoCliente::agregarFigura(Figura* fig){

	if(!fisicaActiva||fisicaActiva){
		if((fig->getTipoFigura()==LINEA)&&(fig->getFigura1()==NULL)&&(fig->getFigura2()==NULL)){
			Linea* linea = (Linea*)fig;
			double x,y;
			linea->getPunto1(&x,&y);
			Figura* result1 = getFiguraAtableCorrea(x,y,false);
			linea->getPunto2(&x,&y);
			Figura* result2 = getFiguraAtableCorrea(x,y,false);
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
			Figura* result1 = getFiguraAtableSoga(x1,y1,false);
			soga->getPunto2(&x2,&y2);
			Figura* result2 = getFiguraAtableSoga(x2,y2,false);
			
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
		bool aux = true;
		if(fisicaActiva){
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
				}
			}else{ 
				delete fig;
			}
		}else{
			(this->figuras).push_back(fig);
		}
	} catch (...) {
		ErrorLogHandler::addError("agregarFigura","excepcion al agregar en la lista (figuras.push_back)");
	};

	return true;
}

void TerrenoCliente::rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY){
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
			figuraActiva->setSuperpuesta(this->posicionOcupada(figuraActiva));						
		}

		contEventosMov++;
		if (contEventosMov > 10000){
			contEventosMov = 0;
		}

		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(numCliente);
		t_msg->setFigureID(figuraActiva->numero);
		t_msg->setX(figuraActiva->getDimension()->getX());
		t_msg->setY(figuraActiva->getDimension()->getY());
		t_msg->setAngle(figuraActiva->getDimension()->getAngulo());
		t_msg->setSizeChange(T_ROTATE);
		this->maq->pushSendMessage(t_msg,this->numCliente);

		this->setCambio(true);
	}
}


void TerrenoCliente::eliminarFigura(Figura* fig){

	try{
		(this->figuras).remove(fig);
	} catch (...) {
		ErrorLogHandler::addError("eliminarFigura","excepcion al eliminar una figura de la lista (figuras.remove)");
	};
}

void TerrenoCliente::arrastrarFigura(double posClickX,double posClickY,double cantMovX,double cantMovY,std::list<Figura*>* lista)
{
	if (figuraActiva != NULL){

		figuraActiva->cambiarPosicion(cantMovX, cantMovY);

		//si se fue el centro del terreno lo vuelvo a meter
		corregirPosicion(figuraActiva);

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
		
		lista->push_back(figuraActiva);
	}
}


void TerrenoCliente::agrandarFigura()
{
	if (figuraActiva != NULL){
		figuraActiva->agrandar();

		//si se fue el centro del terreno lo vuelvo a meter
		corregirPosicion(figuraActiva);
		this->setCambio(true);
		bool choca = this->posicionOcupada(figuraActiva);
		figuraActiva->setSuperpuesta(choca);

		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(numCliente);
		t_msg->setFigureID(figuraActiva->numero);
		t_msg->setX(figuraActiva->getDimension()->getX());
		t_msg->setY(figuraActiva->getDimension()->getY());
		t_msg->setSizeChange(T_GROW);
		this->maq->pushSendMessage(t_msg,this->numCliente);
	}
}

void TerrenoCliente::shiftFigura()
{
	if (figuraActiva != NULL){
		figuraActiva->shift();

		//si se fue el centro del terreno lo vuelvo a meter
		corregirPosicion(figuraActiva);
		this->setCambio(true);

		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(numCliente);
		t_msg->setFigureID(figuraActiva->numero);
		t_msg->setX(figuraActiva->getDimension()->getX());
		t_msg->setY(figuraActiva->getDimension()->getY());
		t_msg->setAngle(figuraActiva->getDimension()->getAngulo());
		t_msg->setSizeChange(T_SHIFT);
		this->maq->pushSendMessage(t_msg,this->numCliente);
	}
}

void TerrenoCliente::achicarFigura()
{
	if (figuraActiva != NULL){

		figuraActiva->achicar();

		this->setCambio(true);

		bool choca = this->posicionOcupada(figuraActiva);
		figuraActiva->setSuperpuesta(choca);

		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(numCliente);
		t_msg->setFigureID(figuraActiva->numero);
		t_msg->setX(figuraActiva->getDimension()->getX());
		t_msg->setY(figuraActiva->getDimension()->getY());
		t_msg->setSizeChange(T_SHRINK);
		this->maq->pushSendMessage(t_msg,this->numCliente);

	}
}

void TerrenoCliente::soltarFigura(bool flag)
{
	if (figuraActiva){
		bool poner = ((flag) || (adentroZonaTerreno(figuraActiva->getDimension()->getX(),figuraActiva->getDimension()->getY())));
		if (!(figuraActiva->superpuesta)&& poner ){
			agregarFigura(figuraActiva);

			TransformFigureMessage* t_msg = new TransformFigureMessage();
			t_msg->setClientID(numCliente);
			t_msg->setFigureID(figuraActiva->numero);
			t_msg->setX(figuraActiva->getDimension()->getX());
			t_msg->setY(figuraActiva->getDimension()->getY());
			t_msg->setSizeChange(T_NONE);
			this->maq->pushSendMessage(t_msg,this->numCliente);

			figuraActiva=NULL;
		}else{
			//la meto con su posicion / angulo / largo anterior
			figuraActiva->setX(posAntFigActiva.getX());
			figuraActiva->setY(posAntFigActiva.getY());
			figuraActiva->setAngulo(angAntFigActiva);
			figuraActiva->setLargo(largoAntFigActiva);
			
			TransformFigureMessage* t_msg = new TransformFigureMessage();
			t_msg->setClientID(numCliente);
			t_msg->setFigureID(figuraActiva->numero);
			t_msg->setX(figuraActiva->getDimension()->getX());
			t_msg->setY(figuraActiva->getDimension()->getY());
			t_msg->setAngle(figuraActiva->getDimension()->getAngulo());
			t_msg->setLength(figuraActiva->getLargo());
			t_msg->setSizeChange(T_RESTORE);
			this->maq->pushSendMessage(t_msg,this->numCliente);

			agregarFigura(figuraActiva);

			//y ya no esta chocando
			figuraActiva->setSuperpuesta(false);

			figuraActiva = NULL;
		}
	}
}

bool TerrenoCliente::hayFiguras(){

	if ((figuraActiva != NULL)||(!figuras.empty()))
		return true;

	return false;
}

std::vector<int> TerrenoCliente::borrarFigura(double posClickX, double posClickY,Figura* vec[]){
//aca ya no puede haber una figura activa, porque solo se llega al hacer un shift-click

	std::vector<int> tiposBorradas;

	Figura* figuraABorrar = buscarFigura(posClickX, posClickY,true);
	if (figuraABorrar==NULL) return tiposBorradas;

	//no le deja si no la cero el
	if(figuraABorrar->numero/(LARGO/(MAX_CLIENTES+1)) != this->numCliente){
		return tiposBorradas;
	}

	if (figuraABorrar){
		//saco de la lista y libero memoria
		eliminarFigura(figuraABorrar);
		setCambio(true);
		
		if(figuraABorrar->esUnion()){
			figuraABorrar->desUnir();
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
				
				vec[(*iter)->numero] = NULL;

				TransformFigureMessage* t_msg = new TransformFigureMessage();
				t_msg->setClientID(numCliente);
				t_msg->setFigureID((*iter)->numero);
				t_msg->setSizeChange(T_REMOVE);
				this->maq->pushSendMessage(t_msg,this->numCliente);
				
				
				eliminarFigura(*iter);
				(*iter)->desUnir();
				tiposBorradas.push_back((*iter)->getTipoFigura());

				delete (*iter);
			}
		}
		
		
		
		vec[figuraABorrar->numero] = NULL;
		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(numCliente);
		t_msg->setFigureID(figuraABorrar->numero);
		t_msg->setSizeChange(T_REMOVE);
		this->maq->pushSendMessage(t_msg,this->numCliente);

		tiposBorradas.push_back(figuraABorrar->getTipoFigura());
		delete figuraABorrar;
	}

	return tiposBorradas;
}

int TerrenoCliente::getAncho(){
	return (this->ancho);
}

int TerrenoCliente::getAlto(){
	return (this->alto);
}

std::string TerrenoCliente::getFondo(){ //si es "" es porq no pusieron ningun fondo (esta el default)
	return this->fondoID;
}

std::list<Figura*> TerrenoCliente::getListaFigs(){
	return this->figuras;
}


void TerrenoCliente::cambioVistaFiguras(){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		(*iteradorLista)->setCambio(true);
	}

}

void TerrenoCliente::resizear(){

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

void TerrenoCliente::buscarActiva(double posClickX ,double posClickY){
	//si todavia no hay una
	if (!figuraActiva){ 

		figuraActiva = buscarFigura(posClickX ,posClickY,true);
		//si no la encontre confirmo que es null (o podria no hacer nada...)
		if (!figuraActiva){
			figuraActiva=NULL;
		}else{

			//Si no es mia vuelvo
			if(figuraActiva->numero/(LARGO/(MAX_CLIENTES+1)) != this->numCliente){
				figuraActiva=NULL;
				return;
			}

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

void TerrenoCliente::corregirPosicion(Figura* fig){

	Dimension* dimension = fig->getDimension();

	while (dimension->getX() > ANCHO_TERRENO_LOGICO) fig->setX( dimension->getX() - 1);
	while (dimension->getX() < 0) fig->setX( dimension->getX() + 1);

	while (dimension->getY() > ALTO_TERRENO_LOGICO) fig->setY( dimension->getY() - 1);
	while (dimension->getY() < 0) fig->setY( dimension->getY() + 1);

}

bool TerrenoCliente::adentroZonaTerreno(double posX,double posY){

	bool adentro = false;
	double margen = 1;

	if((posX >= (this->x1+margen)) && (posX <= (this->x2-margen))){
		if((posY >= (this->y1+margen)) && (posY <= (this->y2-margen))){
			adentro = true;
		}
	}
	return adentro;

}

Figura* TerrenoCliente::buscarFigura(double posClickX, double posClickY,bool soloMias){

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
			if(figuraBuscada->esFija()){
				return NULL;
			}

			if(soloMias){
				if(figuraBuscada->numero/(LARGO/(MAX_CLIENTES+1)) != this->numCliente){
					return NULL;
				}
			}
			return figuraBuscada;
		}
	}
	return NULL;
}

int TerrenoCliente::obtenerCuadranteDeClick(double X, double Y){

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

bool TerrenoCliente::anguloEsPositivo(double X1, double Y1, double X2, double Y2){
	
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

void TerrenoCliente::actualizarModelo(Figura* vector[]){
	for(std::list<Figura*>::iterator iter = figuras.begin(); iter != figuras.end();iter++){
		if(((*iter)->getTipoFigura()==SOGA)||((*iter)->getTipoFigura()==LINEA)){
			((Linea*)(*iter))->actualizar();
			this->setCambio(true);
		}
	}
}

bool TerrenoCliente::posEnTerrenoExtendido(double posX,double posY){
	return true;
}



double TerrenoCliente::calcularAngulo(Dimension* dim, double XVector1,double YVector1,double XVector2,double YVector2){

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


Figura* TerrenoCliente::getFiguraAtableCorrea(double x,double y,bool soloMias){
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

		if (figuraEncontrada){
			if(soloMias){
				if(figuraBuscada->numero/(LARGO/(MAX_CLIENTES+1)) != this->numCliente){
					return NULL;
				}
			}
			return figuraBuscada;
		}
	}
	return NULL;
}


Figura* TerrenoCliente::getFiguraAtableSoga(double x,double y,bool soloMias){
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

		if (figuraEncontrada){
			if(soloMias){
				if(figuraBuscada->numero/(LARGO/(MAX_CLIENTES+1)) != this->numCliente){
					return NULL;
				}
			}
			return figuraBuscada;
		}
	}
	return NULL;
}


bool TerrenoCliente::posicionOcupada(Figura* figAPosicionar){

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


void TerrenoCliente::borrarAtadura(Figura* fig){
}


void TerrenoCliente::interactuar(double posClickX, double posClickY){
	Figura* figAInteract;
	
	if (this->adentroZonaTerreno(posClickX,posClickY)){
		figAInteract = this->buscarFigura(posClickX,posClickY,false);
		if(figAInteract!=NULL){
			InteractMessage* i_msg = new InteractMessage();
			i_msg->setFigureID(figAInteract->numero);
			i_msg->setAction(CLICK_MOUSE);
			this->maq->pushSendMessage(i_msg,this->numCliente);
		}
	}

}

void TerrenoCliente::interactuar(int accion){

	for (std::list<Figura*>::iterator iter = figuras.begin();iter != figuras.end();iter++){
		if((*iter)->numero/(LARGO/(MAX_CLIENTES+1)) == this->numCliente){
			InteractMessage* i_msg = new InteractMessage();
			i_msg->setFigureID((*iter)->numero);
			i_msg->setAction(accion);
			this->maq->pushSendMessage(i_msg,this->numCliente);
		}
	}
}