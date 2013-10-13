#include "FiguraCompuesta.h"

FiguraCompuesta::FiguraCompuesta(const char* ID, Dimension* dim):Figura(ID,dim)
{
/*si se usa este inicializar dimensiones,angulos,etc en la figura que hereda*/	
}

FiguraCompuesta::FiguraCompuesta( std::list<Figura*> listaFiguras,double angulo){
	//guardo las figuras en la lista interna
	partesFigura = listaFiguras;

	//buscar x max y min e y max y min y crear el cuadrado

	double xMax,xMin,yMax,yMin;

	iterFig = partesFigura.begin();
//si ya se deberia ordenarla por x y por y,y no hacerlo lineal, pero no tengo ganas
	xMax = (*iterFig)->getDimension()->getX() + (*iterFig)->getDimension()->getAncho()/2;
	xMin = (*iterFig)->getDimension()->getX() - (*iterFig)->getDimension()->getAncho()/2;
	yMax = (*iterFig)->getDimension()->getY() + (*iterFig)->getDimension()->getAlto()/2;
	yMin = (*iterFig)->getDimension()->getY() - (*iterFig)->getDimension()->getAlto()/2;
	
	while( iterFig != partesFigura.end() ) {
		
		if ( (*iterFig)->getDimension()->getX() + (*iterFig)->getDimension()->getAncho()/2 > xMax)
			xMax = (*iterFig)->getDimension()->getX();
		if ( (*iterFig)->getDimension()->getX() - (*iterFig)->getDimension()->getAncho()/2 < xMin)
			xMin = (*iterFig)->getDimension()->getX();
		if ( (*iterFig)->getDimension()->getY() + (*iterFig)->getDimension()->getAlto()/2 > yMax)
			yMax = (*iterFig)->getDimension()->getY();
		if ( (*iterFig)->getDimension()->getY() - (*iterFig)->getDimension()->getAlto()/2 > yMin)
			yMin = (*iterFig)->getDimension()->getY();
	
		iterFig++;
	}

	//obtengo el centro y creo el cuadrado

	double ancho = xMax - xMin;
	double alto = yMax - yMin;
	double x = ancho/2 + xMin;
	double y = alto/2 + yMin;

	dimension = new Cuadrado(ancho,alto,x,y,angulo);

	//guardo los angulos correspondientes
	this->inicAngulosCentro();
	
	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		//y obviamente aca poner en quien herede los que correspondan
		angulos.push_back((*iterFig)->getDimension()->getAngulo());
	}

	myVista = NULL;
	ID = "";
}


FiguraCompuesta::~FiguraCompuesta(void)
{
	delete dimension;
	dimension = NULL;

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		delete (*iterFig);
	}
}

void FiguraCompuesta::cambiarPosicion(double Movx,double Movy){

	iterFig = partesFigura.begin();
	
	while( iterFig != partesFigura.end() ) {
		(*iterFig)->cambiarPosicion(Movx,Movy);
		iterFig++;
	}
//cambio la posicion del cuadrado que tiene por dimension
	this->getDimension()->setX( getDimension()->getX() + Movx);
	this->getDimension()->setY( getDimension()->getY() + Movy);

	setCambio(true);
}


bool FiguraCompuesta::esMiPosicion(double x,double y){

	iterFig = partesFigura.begin();
	bool encontrada = false;
	
	while( (iterFig != partesFigura.end()) && (!encontrada) ){
		encontrada = (*iterFig)->esMiPosicion(x,y);

		iterFig++;
	}

	return encontrada;

}

bool FiguraCompuesta::intersecaCon(double X1, double Y1, double X2, double Y2){

	iterFig = partesFigura.begin();
	bool interseca = false;
	
	while( (iterFig != partesFigura.end()) && (!interseca) ){
		interseca = (*iterFig)->intersecaCon( X1, Y1, X2, Y2);
		iterFig++;
	}

	return interseca;
}


void FiguraCompuesta::dibujarEnPixel(Superficie* superficie){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->dibujarEnPixel(superficie);
		setCambio(false);
	}

}

void FiguraCompuesta::dibujar(Superficie* superficie){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->dibujar(superficie);
		this->setCambio(false);
	}
}

void FiguraCompuesta::dibujar(Superficie* super,int xIni,int yIni){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->dibujar(super,xIni,yIni);
		setCambio(false);
	}
}

void FiguraCompuesta::setTraslucido(bool flag){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->setTraslucido(flag);
	}
	setCambio(true);
}

void FiguraCompuesta::setAngulo(double angulo){
	
	std::list<double>::iterator iterAngulosLocales;
	iterAngulosLocales = angulos.begin();

	std::list<double>::iterator iterAngulosCentro;
	iterAngulosCentro = angulosCentroIniciales.begin();

	std::list<double> angulosCentroActuales = angulosCentroIniciales;
	std::list<double>::iterator iterAngulosCentroActuales;
	iterAngulosCentroActuales = angulosCentroActuales.begin();

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		//la variacion mas el inicial propio
		(*iterFig)->setAngulo(angulo + (*iterAngulosLocales));
		(*iterAngulosCentroActuales) = (angulo + (*iterAngulosCentro));
		
		iterAngulosLocales++;
		iterAngulosCentro++;
		iterAngulosCentroActuales++;
	}	

	//cambio el angulo del cuadrado que tiene por dimension
	this->getDimension()->setAngulo(angulo);

	//Y tengo que rotar todas las posiciones
	double XRelCentro,YRelCentro,radio;
	double nuevoX,nuevoY;
	double centroX,centroY;

	centroX = this->getDimension()->getX();
	centroY = this->getDimension()->getY();

	double angle ;
	Dimension* dim;

	iterAngulosCentroActuales = angulosCentroActuales.begin();

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		dim = (*iterFig)->getDimension();

		angle = (*iterAngulosCentroActuales)*PI/180;

		XRelCentro = dim->getX()-centroX;
		YRelCentro = dim->getY()-centroY;

		radio = sqrt ( XRelCentro*XRelCentro + YRelCentro*YRelCentro );

		nuevoX = radio*cos(-angle) + centroX;
		nuevoY = radio*sin(-angle) + centroY;
		
		dim->setX(nuevoX);
		dim->setY(nuevoY);

		iterAngulosCentroActuales++;
	}	

	setCambio(true);

}


//para este no devuelve nada valido
const char* FiguraCompuesta::getID(){
	return this->ID.c_str();
}

//para este devuelve un cuadrado con la posicion y angulo de la figura
Dimension* FiguraCompuesta::getDimension(){
	return dimension;
}

void FiguraCompuesta::inicAngulosCentro(){

//calculo el angulo de cada parte respecto del centro y los guardo!
//pasarle el cuadrado y uno horizontal y el centro de la figura componente.
//restarle el que ya tiene por como es el metodo de calcular angulo
//y guardar el resultado.
	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		angulosCentroIniciales.push_back (calcularAngulo(dimension, dimension->getX()+1,dimension->getY(), (*iterFig)->getDimension()->getX(),(*iterFig)->getDimension()->getY()) - dimension->getAngulo());
	}	
}


double FiguraCompuesta::calcularAngulo(Dimension* dim, double XVector1,double YVector1,double XVector2,double YVector2){

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


int FiguraCompuesta::obtenerCuadranteDeClick(double X, double Y){

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

bool FiguraCompuesta::anguloEsPositivo(double X1, double Y1, double X2, double Y2){
	
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


void FiguraCompuesta::setX( double x ){

	double difDePos = x - dimension->getX();

	this->cambiarPosicion(difDePos , 0);
}

void FiguraCompuesta::setY( double y ){

	double difDePos = y - dimension->getY();

	this->cambiarPosicion( 0 , difDePos);
}

bool FiguraCompuesta::choqueConFigura(Figura* fig){

	//me fijo si fig que me pasaron choca con alguna dimension
	bool choca = false;
	
	Dimension* dimensionRotada = NULL;

	iterFig = partesFigura.begin();
	
	while( (iterFig != partesFigura.end()) && (!choca) ){

		dimensionRotada = (*iterFig)->getDimension()->rotarDimension((*iterFig)->getDimension()->getX(),(*iterFig)->getDimension()->getY(),(*iterFig)->getDimension()->getAngulo());

		choca = fig->choqueConDimension(dimensionRotada);

		delete dimensionRotada;
		iterFig++;
	}
	//caso en que una esta dentro de la otra
	if ((!choca) && fig->esMiPosicion(this->getDimension()->getX() , this->getDimension()->getY() ) ){
		choca = true;
	}

	return choca;
}


//de nuevo, pruebo contra todas las dimensiones
bool FiguraCompuesta::choqueConDimension(Dimension* dim){
//como no lo se en la figura delego a la dimension (o dimensiones).
	
	bool choca = false;

	iterFig = partesFigura.begin();
	
	while( (iterFig != partesFigura.end()) && (!choca) ){
		choca = (*iterFig)->getDimension()->choqueConDimension(dim);
		iterFig++;
	}

	return choca;
}