#include "PaletaFlipper.h"
#include "Sonidos.h"

PaletaFlipper::PaletaFlipper(double posX,double posY,int sentido):Figura(ID_PALETA,new Cuadrado(ANCHO_PALETA,ALTO_PALETA,posX,posY,0),true){

	this->interactua_en_play = true;
	this->is_pushed = false;
	this->sentido = sentido;

	if (sentido == IZQUIERDA) this->setAngulo(PALETA_IZQ_MINANG*180/PI);
	if (sentido == DERECHA) this->setAngulo(PALETA_DER_MINANG*180/PI);

}
PaletaFlipper::~PaletaFlipper(void){
}

Figura* PaletaFlipper::clonar(){
	return new PaletaFlipper(this->dimension->getX(),this->dimension->getY(),this->sentido);
}
int PaletaFlipper::getTipoFigura(){
	return PALETA;
}
int PaletaFlipper::getTipoDimension(){
	return CUADRADO;
}
double PaletaFlipper::getXdeRotacion(){
	double Xc = this->getDimension()->getX();
	double Yc = this->getDimension()->getY();
	double x = 0;
	double XsinRotar = Xc - ANCHO_PALETA*3/8;
	x = Xc + (XsinRotar - Xc)*cos(-(this->getDimension()->getAngulo()*PI/180));
	return x;
}
double PaletaFlipper::getYdeRotacion(){
	double Xc = this->getDimension()->getX();
	double Yc = this->getDimension()->getY();
	double y = 0;
	double XsinRotar = Xc - ANCHO_PALETA*3/8;
	y = Yc + (XsinRotar - Xc)*sin(-(this->getDimension()->getAngulo()*PI/180));
	return y;
}
double PaletaFlipper::getMaxAng(){
	if ((this->sentido) == IZQUIERDA){
		return PALETA_IZQ_MAXANG;
	}
	return PALETA_DER_MAXANG;
}
double PaletaFlipper::getMinAng(){
	if ((this->sentido) == IZQUIERDA){
		return PALETA_IZQ_MINANG;
	}
	return PALETA_DER_MINANG;	
}
int PaletaFlipper::getSentido(){
	return sentido;
}
void PaletaFlipper::shift(){
	//this->sentido = (this->sentido+1) % 2; //porque IZQUIERDA Y DERECHA SON 0 Y 1 //ya no, lo cambie (?)
	if (this->sentido == IZQUIERDA) {
		this->sentido = DERECHA;
		this->setAngulo(PALETA_DER_MINANG*180/PI);
	} else {
		this->sentido = IZQUIERDA;
		this->setAngulo(PALETA_IZQ_MINANG*180/PI);
	}
}
bool PaletaFlipper::estaApretada(){
	return is_pushed;
}
void PaletaFlipper::accionar(){
	if (this->sentido == IZQUIERDA){
		//this->b2dJoint->SetMotorSpeed(-200);
		//this->b2dCuerpo->ApplyTorque(150000);
		//b2dCuerpo->ApplyForce(b2Vec2(0,50),b2dCuerpo->GetPosition());
		if (this->b2dCuerpo->GetAngle() > -7.45)
			this->b2dCuerpo->SetAngularVelocity(-150);
		
		//this->b2dCuerpo->ApplyAngularImpulse(-150);
	} else {
		//std::cout << this->b2dCuerpo->GetAngle() << "\n";
		//this->b2dJoint->SetMotorSpeed(-20.0f);
		//this->b2dCuerpo->ApplyTorque(-150);
		if (this->b2dCuerpo->GetAngle() < -2.34)
			this->b2dCuerpo->SetAngularVelocity(150);
	}
}
void PaletaFlipper::desaccionar(){
		if (this->sentido == IZQUIERDA){
			this->b2dCuerpo->SetAngularVelocity(800);
		} else {
			this->b2dCuerpo->SetAngularVelocity(-800);
		}
}
void PaletaFlipper::interactuar(int accion){

	if (accion == PRESS_SPACE){
		if (!this->is_pushed) Sonidos::playSound(FLIPPER_UP);
		this->is_pushed = true;
		accionar();
	} else if (accion == RELEASE_SPACE){
		if (this->is_pushed) Sonidos::playSound(FLIPPER_DOWN);
		this->is_pushed = false;
		desaccionar();
	}
		//if (((PaletaFlipper*)figura)->estaApretada()){
		//	if (((PaletaFlipper*)figura)->getSentido() == IZQUIERDA){
		//		((b2RevoluteJoint*)enlace)->SetMotorSpeed(20.0f);
		//		//cuerpo->ApplyTorque(150);
		//	} else {
		//		((b2RevoluteJoint*)enlace)->SetMotorSpeed(-20.0f);
		//		//cuerpo->ApplyTorque(-150);
		//	}
		//} else {
		//	//deberia caer sola
		//}
}
void PaletaFlipper::setBox2dData(b2Body* cuerpo,b2RevoluteJoint* enlace){
	this->b2dCuerpo = cuerpo;
	this->b2dJoint = enlace;
};