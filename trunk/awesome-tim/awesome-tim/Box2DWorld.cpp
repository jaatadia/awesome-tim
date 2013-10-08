#include "Box2DWorld.h"
#include "Engranaje.h"
#include "Engranaje2.h"

Box2DWorld::Box2DWorld(void)
{
}

Box2DWorld::Box2DWorld(float fuerzaX, float fuerzaY,bool flag = true)
{
	this->activo = flag;
	if(activo)this->mundo = new b2World(b2Vec2(fuerzaX,fuerzaY));
	else this->mundo = new b2World(b2Vec2(0,0));
	//GROUNDBOX
/*
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(50.0f, 100.0f);
	b2Body* groundBody = (this->mundo)->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 0.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
*/
}

void Box2DWorld::setFrecuenciaActualizacion(float tiempoStep, int velIteracion, int posIteracion)
{
	this->tiempoStep = tiempoStep;
	this->velIteracion = velIteracion;
	this->posIteracion = posIteracion;
}

void Box2DWorld::actualizar()
{
	this->mundo->Step(this->tiempoStep, this->velIteracion, this->posIteracion);
}

void Box2DWorld::agregarFigura(Figura * figura)
{
	Dimension * dim = figura->getDimension();
	b2BodyDef bD;
	bD.position.Set(dim->getX(), dim->getY());
	bD.type = b2_dynamicBody;
	b2Body * cuerpo = this->mundo->CreateBody(&bD);

	cuerpo->SetTransform(cuerpo->GetPosition(),-figura->getDimension()->getAngulo()/180*PI); //nuestros angulos son al reves de box2d
	cuerpo->SetUserData(figura);

	b2FixtureDef fD;

	switch(figura->getTipoFigura())
	{
		/*case TRIANGULO:
			break;
		case CUADRADO:{
				b2PolygonShape forma;
				forma.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
				fD.shape = &forma;
				fD.density = 1.0;
				fD.friction = 0.3;
				cuerpo->CreateFixture(&fD);
				break;
			}*/
		case PLATAFORMA:{
				cuerpo->SetType(b2_staticBody);
				b2PolygonShape forma;
				forma.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
				fD.shape = &forma;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				cuerpo->CreateFixture(&fD);
				break;
			}
		case GLOBOHELIO:{
				cuerpo->SetGravityScale(0);
				
				
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_GLOBOHELIO;
				fD.friction = FRICCION_GLOBOHELIO;
				fD.restitution = RESTITUCION_GLOBOHELIO;
				cuerpo->CreateFixture(&fD);
				
				if(activo){
					cuerpo->ApplyLinearImpulse(b2Vec2(0.0, VELOCIDAD_GLOBOHELIO), cuerpo->GetPosition());
					cuerpo->SetFixedRotation(true);
					cuerpo->SetAngularVelocity(0);
				}

				break;
			}
		case PELOTABASQUET:{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_PELOTABASQUET;
				fD.friction = FRICCION_PELOTABASQUET;
				fD.restitution = RESTITUCION_PELOTABASQUET;
				cuerpo->CreateFixture(&fD);
				break;
			}
		case PELOTABOWLING:
			{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_PELOTABOWLING;
				fD.friction = FRICCION_PELOTABOWLING;
				fD.restitution = RESTITUCION_PELOTABOWLING;
				cuerpo->CreateFixture(&fD);
			break;
			}
		case ENGRANAJE:
			{
				b2BodyDef ejeDef;
				ejeDef.type = b2_staticBody;
				ejeDef.position.Set(cuerpo->GetPosition().x,cuerpo->GetPosition().y);
												
				b2FixtureDef ejeFix;
				b2CircleShape ejeCirculo;
				ejeCirculo.m_radius = 0.00001;
				ejeFix.shape = &ejeCirculo;
				ejeFix.isSensor = true;
				
				b2Body* eje = this->mundo->CreateBody(&ejeDef);
				eje->CreateFixture(&ejeFix);
												
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				fD.shape = &forma;
				fD.density = DENSIDAD_ENGRANAJE;
				fD.friction = FRICCION_ENGRANAJE;
				fD.restitution = RESTITUCION_ENGRANAJE;
				cuerpo->CreateFixture(&fD);
				
				b2RevoluteJointDef joint;
				joint.Initialize(eje,cuerpo,cuerpo->GetPosition());
				//joint.bodyA = eje;
				//joint.bodyB = cuerpo;
						
				b2Joint* enlace = this->mundo->CreateJoint(&joint);
				((Engranaje*)figura)->joint = enlace;
				figura->setCuerpo(cuerpo);
				

				for(b2Body* c = this->mundo->GetBodyList();c;c = c->GetNext()){
					Figura* fig = (Figura*)c->GetUserData();
					if((fig!=NULL)&&(fig!=figura)){
						if((fig->getTipoFigura()==ENGRANAJE)||(fig->getTipoFigura()==ENGRANAJE2)){
							double margen = ((Engranaje*)figura)->getRadio()+((Engranaje*)fig)->getRadio();						
							if(
								(sqrt(
								pow(fig->getDimension()->getX()-figura->getDimension()->getX(),2)+
								pow(fig->getDimension()->getY()-figura->getDimension()->getY(),2)
								)<margen)
							){
								b2GearJointDef joint2;
								joint2.bodyA = cuerpo;
								joint2.bodyB = fig->getCuerpo();
								if ((cuerpo!=NULL) &&(fig->getCuerpo()!=NULL)){
									joint2.joint1 = enlace;
									joint2.joint2 = ((Engranaje*)fig)->joint;
									joint2.ratio = ((Engranaje*)fig)->getRadio()/((Engranaje*)figura)->getRadio();

									this->mundo->CreateJoint(&joint2);
									//break;
								}
							}
						}
					}
				}

				((Engranaje*)figura)->joint = enlace;

				break;
			}
		case ENGRANAJE2:
			{
				b2BodyDef ejeDef;
				ejeDef.type = b2_staticBody;
				ejeDef.position.Set(cuerpo->GetPosition().x,cuerpo->GetPosition().y);
								
				b2FixtureDef ejeFix;
				b2CircleShape ejeCirculo;
				ejeCirculo.m_radius = 0.00001;
				ejeFix.shape = &ejeCirculo;
				ejeFix.isSensor = true;
				
				b2Body* eje = this->mundo->CreateBody(&ejeDef);
				eje->CreateFixture(&ejeFix);
												
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				fD.shape = &forma;
				fD.density = DENSIDAD_ENGRANAJE;
				fD.friction = FRICCION_ENGRANAJE;
				fD.restitution = RESTITUCION_ENGRANAJE;
				cuerpo->CreateFixture(&fD);
				
				b2RevoluteJointDef joint;
				joint.Initialize(eje,cuerpo,cuerpo->GetPosition());
				joint.bodyA = eje;
				joint.bodyB = cuerpo;
				b2Joint* enlace = this->mundo->CreateJoint(&joint);

				if(activo){
					cuerpo->SetFixedRotation(true);
					cuerpo->SetAngularVelocity(VELOCIDAD_ENGRANAJE2*((Engranaje2*)figura)->sentido);
				}

				((Engranaje*)figura)->joint = enlace;
				figura->setCuerpo(cuerpo);

				for(b2Body* c = this->mundo->GetBodyList();c;c = c->GetNext()){
					Figura* fig = (Figura*)c->GetUserData();
					if((fig!=NULL)&&(fig!=figura)){
						if((fig->getTipoFigura()==ENGRANAJE)||(fig->getTipoFigura()==ENGRANAJE2)){
							double margen = ((Engranaje*)figura)->getRadio()+((Engranaje*)fig)->getRadio();						
							if(
								(sqrt(
								pow(fig->getDimension()->getX()-figura->getDimension()->getX(),2)+
								pow(fig->getDimension()->getY()-figura->getDimension()->getY(),2)
								)<margen)
							){
								b2GearJointDef joint2;
								joint2.bodyA = cuerpo;
								joint2.bodyB = fig->getCuerpo();
								if ((cuerpo!=NULL) &&(fig->getCuerpo()!=NULL)){
									joint2.joint1 = enlace;
									joint2.joint2 = ((Engranaje*)fig)->joint;
									joint2.ratio = ((Engranaje*)fig)->getRadio()/((Engranaje*)figura)->getRadio();

									this->mundo->CreateJoint(&joint2);
									//break;
								}
							}
						}
					}
				}
				break;
			}
		case PELOTATENIS:
			{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_PELOTATENIS;
				fD.friction = FRICCION_PELOTATENIS;
				fD.restitution = RESTITUCION_PELOTATENIS;
				cuerpo->CreateFixture(&fD);
				break;
			}
		/*case POLIGONOREGULAR:
			{
				b2PolygonShape forma;
				b2Vec2 vertices[4];
				vertices[0].Set(((Cuadrado *) dim)->getX(), ((Cuadrado *) dim)->getY());
				vertices[1].Set(((Cuadrado *) dim)->getX(), ((Cuadrado *) dim)->getY() - 20);
				vertices[2].Set(((Cuadrado *) dim)->getX() + 20, ((Cuadrado *) dim)->getY() - 20);
				vertices[3].Set(((Cuadrado *) dim)->getX() + 20, ((Cuadrado *) dim)->getY());
				forma.Set(vertices,4);
				fD.shape = &forma;
				fD.density = 1.0;
				fD.friction = 0.3;
				cuerpo->CreateFixture(&fD);
				break;
			}*/
		case SOGA:
			{
				b2Body* segmentoAnterior;
				b2Body* segmentoSiguiente;
				//obtengo iterador para recorrer los segmentos de soga
				FiguraCompuesta* fig = (FiguraCompuesta*) figura;
				std::list<Figura*> segmentosSoga = fig->getFigurasComp();

				std::list<Figura*>::iterator iterSegmentos;
				
				//meto el primero
				iterSegmentos = segmentosSoga.begin();

				bD.position.Set((*iterSegmentos)->getDimension()->getX(), (*iterSegmentos)->getDimension()->getY());
				segmentoAnterior = this->mundo->CreateBody(&bD);

				b2PolygonShape forma;

				forma.SetAsBox((*iterSegmentos)->getDimension()->getAncho(),(*iterSegmentos)->getDimension()->getAlto());
				fD.shape = &forma;
//pendientes de AJUSTE luego de experimentar un poco
				fD.density = 1.0; //poner esto en constantes.h!!!
				fD.friction = 0.3;

				segmentoAnterior->CreateFixture(&fD);
				//completo el cuerpo de box2d del 1er segmento de soga
				segmentoAnterior->SetTransform(segmentoAnterior->GetPosition(),(*iterSegmentos)->getDimension()->getAngulo()/180*PI);
				segmentoAnterior->SetUserData((*iterSegmentos));

				iterSegmentos++;

				for (iterSegmentos ; iterSegmentos != segmentosSoga.end(); iterSegmentos++){
					bD.position.Set((*iterSegmentos)->getDimension()->getX(), (*iterSegmentos)->getDimension()->getY());
					segmentoSiguiente = this->mundo->CreateBody(&bD);
//necesario porque el ultimo puede no tener longitud 1
//O podria hacerlo al reves y tener al ultimo de caso aparte lo cual tendria mas sentido
//CAMBIARLO si tengo tiempo
					b2PolygonShape forma;
					forma.SetAsBox((*iterSegmentos)->getDimension()->getAncho(),(*iterSegmentos)->getDimension()->getAlto());
					fD.shape = &forma;

					segmentoSiguiente->CreateFixture(&fD);
					//completo el cuerpo de box2d del segmento en cuestion
					segmentoSiguiente->SetTransform(segmentoSiguiente->GetPosition(),(*iterSegmentos)->getDimension()->getAngulo()/180*PI);
					segmentoSiguiente->SetUserData((*iterSegmentos));

					//los uno
					b2RevoluteJointDef jointDef;

					b2Vec2 puntoAnclaje ((*iterSegmentos)->getDimension()->getX(),(*iterSegmentos)->getDimension()->getY()/2);
					jointDef.Initialize(segmentoAnterior, segmentoSiguiente, segmentoAnterior->GetWorldPoint(puntoAnclaje));

					//guardo el que se unira en el paso siguiente
					segmentoAnterior = segmentoSiguiente;
				}
			break;
			}
	}
}

void Box2DWorld::actualizar(Figura * figura)
{
/*
	b2Body * cuerpo = this->mundo->GetBodyList();

	while(cuerpo)
	{
		if (((Figura *)cuerpo->GetUserData()) == figura)
		{
			Dimension * dim = figura->getDimension();
			if(cuerpo->GetAngle() < 0)
				figura->setAngulo(-(cuerpo->GetAngle())*180/PI);
			else
				figura->setAngulo((cuerpo->GetAngle())*180/PI);
			dim->setX(cuerpo->GetPosition().x);
			dim->setY(cuerpo->GetPosition().y);
			break;
		}
		cuerpo = cuerpo->GetNext();
	}
*/

	//Hago que actualize tooodas las que tenga  << Juan
//PARA DEBUG
	int i=0;
	
	b2Body* cuerpo = this->mundo->GetBodyList();

	while(cuerpo)
	{
		Figura* fig  = (Figura*)cuerpo->GetUserData();
		
		if(fig!=NULL){
			fig->setAngulo(-(cuerpo->GetAngle())*180/PI);

			fig->getDimension()->setX(cuerpo->GetPosition().x);
			fig->getDimension()->setY(cuerpo->GetPosition().y);
		
			if(activo){
				if(fig->getTipoDimension()==GLOBOHELIO){
					bool cambiar = false;
					double margen = 0.4;
					double margenA = 0.1;
					double impulsoX = 0;
					double impulsoY = 0;
					
					if((cuerpo->GetLinearVelocity().x < 0 - margen)||(cuerpo->GetLinearVelocity().x > 0 + margen)){
						impulsoX = 0 - cuerpo->GetLinearVelocity().x;
						cambiar = true;
					}
					if((cuerpo->GetLinearVelocity().y < VELOCIDAD_GLOBOHELIO - margen)||(cuerpo->GetLinearVelocity().y > VELOCIDAD_GLOBOHELIO + margen)){
						impulsoY = VELOCIDAD_GLOBOHELIO - cuerpo->GetLinearVelocity().y;
						cambiar = true;
					}
					if(cambiar){
						cuerpo->ApplyLinearImpulse(b2Vec2(impulsoX,impulsoY),cuerpo->GetPosition());
					}
				}
			}
		}
		cuerpo = cuerpo->GetNext();
//PARA DEBUG
		i++;
	}

	//std::cout<<i<<std::endl;

}

void Box2DWorld::cambiarParametros(Figura * figura)
{
	b2Body * cuerpo = this->mundo->GetBodyList();
	while(cuerpo)
	{
		if (((Figura *)cuerpo->GetUserData()) == figura)
		{
			Dimension * dim = figura->getDimension();
			cuerpo->SetTransform(b2Vec2(dim->getX(), dim->getY()), dim->getAngulo()); // Analizar esto posteriormente
			switch(dim->getTipoDimension())
			{
				case TRIANGULO:
					break;
				case CUADRADO:
					break;
				case CIRCULO:
					((b2CircleShape *)cuerpo->GetFixtureList()->GetShape())->m_radius = ((Circulo *)dim)->getRadio();
					break;
				case POLIGONOREGULAR:
					break;
			}
			break;
		}
		cuerpo = cuerpo->GetNext();
	}
}

void Box2DWorld::eliminarFigura(Figura * figura)
{
	b2Body * cuerpo = this->mundo->GetBodyList();
	while(cuerpo)
	{
		if (((Figura *)cuerpo->GetUserData()) == figura)
		{
			this->mundo->DestroyBody(cuerpo);
			break;
		}
		cuerpo = cuerpo->GetNext();
	}
}

#include <iostream>

Box2DWorld::~Box2DWorld(void)
{
	delete this->mundo;
}
