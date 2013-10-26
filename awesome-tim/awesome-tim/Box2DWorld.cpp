#include "Box2DWorld.h"
#include "Engranaje.h"
#include "Motor.h"
#include "Linea.h"
#include "Soga.h"
#include "Balancin.h"
#include "PedacitoSoga.h"
#include "Polea.h"
#include <iostream>

Box2DWorld::Box2DWorld(void)
{
}

Box2DWorld::Box2DWorld(float fuerzaX, float fuerzaY,bool flag = true)
{
	this->activo = flag;
	if(activo){
		this->mundo = new b2World(b2Vec2(fuerzaX,fuerzaY));
		list = new B2ContactListener();
		this->mundo->SetContactListener(list);
	}
	else{
		this->mundo = new b2World(b2Vec2(0,0));
		list = NULL;
	}
	
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
	this->list->terminar();
}

bool Box2DWorld::agregarFigura(Figura * figura)
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
		case CORREA:{
			b2Body * inicio = cuerpo;
			fD.density = 1;
			b2PolygonShape polygonShape;
			polygonShape.SetAsBox(1,0.25);
			fD.shape = &polygonShape;
			
			cuerpo->CreateFixture(&fD);
			b2RevoluteJointDef rJD;
			rJD.localAnchorA.Set( 0.75,0);
			rJD.localAnchorB.Set(-0.75,0);

			// Creacion y union de eslabones
			for (int i = 0; i < 10; i++) {
				b2Body * eslabon = this->mundo->CreateBody(&bD);
				eslabon->CreateFixture(&fD);
				
				rJD.bodyA = cuerpo;
				rJD.bodyB = eslabon;
				this->mundo->CreateJoint(&rJD);
				
				cuerpo = eslabon;
			}

			// Union de ultimo eslabon con el primero
			rJD.bodyA = cuerpo;
			rJD.bodyB = inicio;
			this->mundo->CreateJoint(&rJD);
			break;
		}

		case BALANCIN:{
				
				cuerpo->SetTransform(cuerpo->GetPosition(),0); 

				b2BodyDef ejeDef;
				ejeDef.type = b2_staticBody;
				ejeDef.position.Set(cuerpo->GetPosition().x,cuerpo->GetPosition().y);
												
				b2FixtureDef ejeFix;
				b2CircleShape ejeCirculo;
				ejeCirculo.m_radius = 0.0001;
				ejeFix.shape = &ejeCirculo;
				ejeFix.isSensor = true;
				
				b2Body* eje = this->mundo->CreateBody(&ejeDef);
				eje->CreateFixture(&ejeFix);

				b2PolygonShape forma;
				Balancin* bal = (Balancin*) figura;
				forma.SetAsBox((bal->getTabla()->getDimension()->getAncho())/2,(bal->getTabla()->getDimension()->getAlto())/2);
				fD.shape = &forma;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				cuerpo->CreateFixture(&fD);

				b2RevoluteJointDef joint;
				joint.enableLimit = true;
				joint.Initialize(eje,cuerpo,cuerpo->GetPosition());
				joint.lowerAngle = -PI/4;
				joint.upperAngle = PI/4;
				//joint.maxMotorTorque = 0.5; //???
						
				b2Joint* enlace = this->mundo->CreateJoint(&joint);
				if (figura->getDimension()->getAngulo() < 180){
					cuerpo->SetTransform(cuerpo->GetPosition(),-figura->getDimension()->getAngulo()/180*PI);
				}else{
					cuerpo->SetTransform(cuerpo->GetPosition(),2*PI-figura->getDimension()->getAngulo()/180*PI);
				}

				break;
			}
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
		case YUNQUE:{
				b2PolygonShape forma;
				forma.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
				fD.shape = &forma;
				fD.density = DENSIDAD_YUNQUE;
				fD.friction = FRICCION_YUNQUE;
				fD.restitution = RESTITUCION_YUNQUE;
				cuerpo->CreateFixture(&fD);
				break;
			}
		case GLOBOHELIO:{
				cuerpo->SetGravityScale(-1);
				
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_GLOBOHELIO;
				fD.friction = FRICCION_GLOBOHELIO;
				fD.restitution = RESTITUCION_GLOBOHELIO;
				cuerpo->CreateFixture(&fD);
				
				if(activo){
					//cuerpo->SetLinearVelocity(b2Vec2(0.0, VELOCIDAD_GLOBOHELIO));
					cuerpo->SetFixedRotation(true);
					cuerpo->SetAngularVelocity(0);
				}

				break;
			}
		case POLEA:{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_POLEA;
				fD.friction = FRICCION_POLEA;
				fD.restitution = RESTITUCION_POLEA;
				cuerpo->CreateFixture(&fD);
				cuerpo->SetType(b2_staticBody);
				((Polea*)figura)->miCuerpo = cuerpo;
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
		case LINEA:
			{
				this->mundo->DestroyBody(cuerpo);
				Figura* fig1=NULL;
				b2Body* cuerpo1 = NULL;
				Figura* fig2=NULL;
				b2Body* cuerpo2 = NULL;


				for(b2Body* c = this->mundo->GetBodyList();c;c = c->GetNext()){
					Figura* fig = (Figura*)c->GetUserData();
					if((fig!=NULL)&&(fig!=figura)){
						if(fig->esAtableCorrea()){
							if(fig->esMiPosicion( ((DLinea*)dim)->x1,((DLinea*)dim)->y1) ){
								fig1 = fig;
								cuerpo1 = c;
							}
							else if(fig->esMiPosicion( ((DLinea*)dim)->x2,((DLinea*)dim)->y2) ){
								fig2 = fig;
								cuerpo2 = c;
							}
						}
					}
				}
				if(fig1 && fig2){
					fig1->atarCorrea();
					fig2->atarCorrea();
					figura->setFigura1(fig1);
					figura->setFigura2(fig2);

					if(activo){
						b2GearJointDef joint2;
						joint2.bodyA = cuerpo1;
						joint2.bodyB = cuerpo2;
						b2JointEdge* edge1 = cuerpo1->GetJointList();
						b2JointEdge* edge2 = cuerpo2->GetJointList();
						while(edge1->joint->GetType()!=e_revoluteJoint) {edge1 = edge1->next;}
						while(edge2->joint->GetType()!=e_revoluteJoint) {edge2 = edge2->next;}
						
						joint2.joint1 = edge1->joint;
						joint2.joint2 = edge2->joint;
						//joint2.ratio = -(fig2->getRadio()/fig1->getRadio());
						joint2.ratio = -1;
						
						this->mundo->CreateJoint(&joint2);
					}
				}else{
					return false;
				}
				break;
			}
		case SOGA:
			{
				this->mundo->DestroyBody(cuerpo);
				Figura* fig1=NULL;
				b2Body* cuerpo1 = NULL;
				int num1 = 0;
				Figura* fig2=NULL;
				b2Body* cuerpo2 = NULL;
				int num2 = 0;


				for(b2Body* c = this->mundo->GetBodyList();c;c = c->GetNext()){
					Figura* fig = (Figura*)c->GetUserData();
					if((fig!=NULL)&&(fig!=figura)){
						if(fig->esMiPosicion( ((DLinea*)dim)->x1,((DLinea*)dim)->y1)){
							int atadura = fig->esAtableSoga(((DLinea*)dim)->x1,((DLinea*)dim)->y1);
							if(atadura!=-1){
								fig1 = fig;
								cuerpo1 = c;
								num1 = atadura;
							}
						}
						else if(fig->esMiPosicion( ((DLinea*)dim)->x2,((DLinea*)dim)->y2)){
							int atadura = fig->esAtableSoga(((DLinea*)dim)->x2,((DLinea*)dim)->y2);
							if(atadura!=-1){
								fig2 = fig;
								cuerpo2 = c;
								num2 = atadura;
							}
						}
					
					}
				}
				if(fig1 && fig2){
					bool atar = true;
					fig1->atarSoga(num1);
					fig2->atarSoga(num2);
					figura->setFigura1(fig1);
					figura->setFigura2(fig2);
					((Soga*)figura)->setNumsPosAtable(num1,num2);
					if((fig1->getTipoFigura()==POLEA)||(fig2->getTipoFigura()==POLEA)){
						ponerEnPolea(figura,cuerpo1,fig1,num1,cuerpo2,fig2,num2);
						return true;
					}

					if(activo){
						double cx1,cy1,cx2,cy2;
						double x1,y1,x2,y2; x1=x2=y1=y2=0;
						
						cx1 = fig1->getDimension()->getX();
						cy1 = fig1->getDimension()->getY();
						cx2 = fig2->getDimension()->getX();
						cy2 = fig2->getDimension()->getY();

						fig1->posAtableSoga(num1,&x1,&y1);
						fig2->posAtableSoga(num2,&x2,&y2);

						//---------------------------------------------------------------
						double angf1 = fig1->getDimension()->getAngulo();
						double angf2 = fig2->getDimension()->getAngulo();
						fig1->setAngulo(0);
						fig2->setAngulo(0);
						fig1->posAtableSoga(num1,&x1,&y1);
						fig2->posAtableSoga(num2,&x2,&y2);
						fig1->setAngulo(angf1);
						fig2->setAngulo(angf2);
						////--------------------------------------------------------------


						b2Vec2 anchor1((x1-cx1),(y1-cy1));//los y en box2d son positivos para arriba aca (? creo(?
						b2Vec2 anchor2((x2-cx2),(y2-cy2));
				
						
						b2RopeJointDef unionSoga;
						unionSoga.collideConnected = true;
						unionSoga.bodyA=cuerpo1;
						unionSoga.bodyB=cuerpo2;
						unionSoga.localAnchorA = anchor1;
						unionSoga.localAnchorB = anchor2;
						
						x1 = cuerpo1->GetWorldPoint(anchor1).x;
						x2 = cuerpo2->GetWorldPoint(anchor2).x;
						y1 = cuerpo1->GetWorldPoint(anchor1).y;
						y2 = cuerpo2->GetWorldPoint(anchor2).y;

						
						unionSoga.maxLength = sqrt(pow(x1-x2,2)+pow(y1-y2,2)); 

						b2Joint* jointSoga = NULL;
						jointSoga = this->mundo->CreateJoint(&unionSoga);
						jointSoga->SetUserData(figura);
						return true;
						
						//creacion de los segmentos
						//----------------------------------------
						fig1->posAtableSoga(num1,&x1,&y1);
						fig2->posAtableSoga(num2,&x2,&y2);
						double UNAX = x2 - x1;
						double UNAY = y2 - y1;
						b2Vec2 punto(UNAX,UNAY);
						
							double angulo = atan2(UNAY,UNAX);
						double largo = 1;
						double cantSegmentos = punto.Length()/largo -1 ;
						
						b2PolygonShape shape;
						shape.SetAsBox(0.6f, 0.125f);

						b2FixtureDef fd;
						fd.shape = &shape;
						fd.density = 10.0f;//20
						fd.friction = 0.2f;//0.2 
						fd.restitution = 0;
						fd.isSensor = true;

						b2RevoluteJointDef jd;
						jd.collideConnected = false;

						b2Body* prevBody = cuerpo1;
						b2Joint* jointAnt = NULL;
						Figura* pedacitoAnt = fig1;
						
						for (int i = 0; i < (cantSegmentos+0.9/*-cantSegmentos*6/100*/); ++i)
						{
							double mix = x1 + i*cos(angulo);
							double miy = y1 + i*sin(angulo);
							b2BodyDef bd;
							bd.type = b2_dynamicBody;
							bd.position.Set(mix, miy);
							b2Body* body = mundo->CreateBody(&bd);
							body->CreateFixture(&fd);

							PedacitoSoga* pedacito = new PedacitoSoga(mix,miy,largo+0.1,0);
							body->SetUserData(pedacito);
							((Soga*)figura)->putSegmento(pedacito);

							b2Vec2 anchor(mix, miy);
							jd.Initialize(prevBody, body, anchor);
							b2Joint* joint = mundo->CreateJoint(&jd);
							
							pedacito->jointSoga = jointSoga;
							pedacito->pedacitoIzq = pedacitoAnt;
							pedacito->jointIzq = joint;
							
							if(pedacitoAnt->getTipoFigura()==PEDACITOSOGA){
								((PedacitoSoga*)pedacitoAnt)->pedacitoDer = pedacito;
								((PedacitoSoga*)pedacitoAnt)->jointDer = joint;
							}

							prevBody = body;
							pedacitoAnt = pedacito;
							jointAnt = joint;
						}
						b2Vec2 anchor(x2, y2);
						jd.Initialize(prevBody, cuerpo2, anchor);
						b2Joint* joint = mundo->CreateJoint(&jd);
						if(pedacitoAnt->getTipoFigura()==PEDACITOSOGA){
							((PedacitoSoga*)pedacitoAnt)->pedacitoDer = pedacitoAnt;
							((PedacitoSoga*)pedacitoAnt)->jointDer = joint;
						}
						
						//----------------------------------------

					}
				}else{
					return false;
				}
				break;
			}
		case ENGRANAJE:
			{
				b2BodyDef ejeDef;
				ejeDef.type = b2_staticBody;
				ejeDef.position.Set(cuerpo->GetPosition().x,cuerpo->GetPosition().y);
												
				b2FixtureDef ejeFix;
				b2CircleShape ejeCirculo;
				ejeCirculo.m_radius = ((Circulo *)dim)->getRadio();
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
						
				b2Joint* enlace = this->mundo->CreateJoint(&joint);
				
				if(activo){
					for(b2Body* c = this->mundo->GetBodyList();c;c = c->GetNext()){
						Figura* fig = (Figura*)c->GetUserData();
						if((fig!=NULL)&&(fig!=figura)){
							if((fig->getTipoFigura()==ENGRANAJE)/*||(fig->getTipoFigura()==MOTOR)*/){
								double margen = ((Engranaje*)figura)->getRadio()+((Engranaje*)fig)->getRadio();						
								if(
									sqrt(
									pow(fig->getDimension()->getX()-figura->getDimension()->getX(),2)+
									pow(fig->getDimension()->getY()-figura->getDimension()->getY(),2)
									)<margen
								){
									b2GearJointDef joint2;
									joint2.bodyA = cuerpo;
									joint2.bodyB = c;
									b2JointEdge* edge1 = c->GetJointList();
									while(edge1->joint->GetType()!=e_revoluteJoint) {edge1 = edge1->next;}
									if ((cuerpo!=NULL) &&(c!=NULL)){
										joint2.joint1 = enlace;
										joint2.joint2 = edge1->joint;
										joint2.ratio = fig->getRadio()/figura->getRadio();
										this->mundo->CreateJoint(&joint2);
									}
								}
							}
						}
					}
				}

				break;
			}
		case MOTOR:
			{
				b2BodyDef ejeDef;
				ejeDef.type = b2_staticBody;
				ejeDef.position.Set(figura->getDimension()->getX(),figura->getDimension()->getY());
								
				b2FixtureDef ejeFix;
				b2PolygonShape ejeCirculo;
				ejeCirculo.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
				ejeFix.shape = &ejeCirculo;
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
					cuerpo->SetAngularVelocity(VELOCIDAD_MOTOR*((Motor*)figura)->sentido);
				}
				break;
			}
		/*case MOTOR:{
			b2BodyDef bDBase;
			bDBase.position.Set(dim->getX(), dim->getY());
			bDBase.type = b2_staticBody;

			b2Body * base = this->mundo->CreateBody(&bDBase);
											
			b2FixtureDef fDBase;
			b2PolygonShape polygonShape;
			polygonShape.SetAsBox(1,0.25);
			fDBase.shape = &polygonShape;
			fDBase.isSensor = true;

			base->CreateFixture(&fDBase);
			
			b2CircleShape circleShape;
			circleShape.m_radius = 2;
			fD.shape = &circleShape;
			cuerpo->CreateFixture(&fD);
			
			b2RevoluteJointDef rJD;
			rJD.bodyA = base;
			rJD.bodyB = cuerpo;
			rJD.localAnchorA.Set(dim->getX(), dim->getY());
			rJD.localAnchorB.Set(0,0);
			rJD.enableMotor = true;
			rJD.motorSpeed = 2;
			rJD.maxMotorTorque = 1;
			this->mundo->CreateJoint(&rJD);
			 
			// Conexion entre motor y correa
			// Esta comentado porque se crean por separado y habria que ver donde se deberia ubicar este bloque de codigo
			//rJD.bodyA = eslabon;
			//rJD.bodyB = cuerpo;
			//rJD.localAnchorA.Set(0.75,0);
			//rJD.localAnchorB.Set(1.75,0);
			//this->mundo->CreateJoint(&rJD);
			break;
		}*/
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
		case CINTATRANSPORTADORA:
			{
				if(activo){
					cuerpo->SetType(b2_staticBody);
					b2PolygonShape forma;
					forma.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
					fD.shape = &forma;
					fD.density = PLATAFORMA_DENSIDAD;
					fD.friction = 0;
					cuerpo->CreateFixture(&fD);
					
					//creo un rotador
					b2BodyDef rotador;
					b2CircleShape vForma;
					vForma.m_radius = figura->getRadio();
					b2FixtureDef rotFix;
					rotFix.shape = &vForma;
					rotFix.density = 1;
					rotFix.friction = 100;
					rotFix.restitution = 0;
					rotFix.isSensor = true;
					b2Body* rotAnt = this->mundo->CreateBody(&rotador);
					rotAnt->CreateFixture(&rotFix);
					rotAnt->SetType(b2_dynamicBody);
					

					//lo uno			
					b2RevoluteJointDef joint;
					joint.bodyA = cuerpo;
					joint.bodyB = rotAnt;
					joint.localAnchorA = b2Vec2(0,0);
					joint.collideConnected = false;
					b2Joint* jointAnt = this->mundo->CreateJoint(&joint);
					

				}
				break;
			}
	}
	return true;
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
	b2Body* cuerpo = this->mundo->GetBodyList();

	while(cuerpo)
	{
		Figura* fig  = (Figura*)cuerpo->GetUserData();
		
		if(fig!=NULL){
			
			if((fig->getTipoFigura()==PLATAFORMA)||(fig->getTipoFigura()==POLEA)){
				cuerpo = cuerpo->GetNext();
				continue;
			}
			
			if(fig->getTipoFigura()==CINTATRANSPORTADORA){
				b2JointEdge* edge = cuerpo->GetJointList();
				if(edge == NULL){
					cuerpo = cuerpo->GetNext();
					continue;
				}
				while(edge->joint->GetType()!=e_revoluteJoint) {edge = edge->next;}
				double ang = 0;
				if (edge->joint->GetBodyA() == cuerpo){
					ang = edge->joint->GetBodyB()->GetAngle();
				}else{
					ang = edge->joint->GetBodyA()->GetAngle();
				}
				fig->setAngulo(-(ang)*180/PI);
				cuerpo = cuerpo->GetNext();
				continue;
			}

				fig->setX(cuerpo->GetPosition().x);
				fig->setY(cuerpo->GetPosition().y);
				fig->setAngulo(-(cuerpo->GetAngle())*180/PI);
				
			if(activo){
				if(fig->getTipoFigura()==GLOBOHELIO){
					bool cambiar = false;
					double margen = 5;
					double velX = 0;
					double velY = 0;
					
					if((cuerpo->GetLinearVelocity().x < 0 - margen)||(cuerpo->GetLinearVelocity().x > 0 + margen)){
						velX = int( cuerpo->GetLinearVelocity().x  + (( 0 - cuerpo->GetLinearVelocity().x)/FPS));
						cambiar = true;
					}else{
						velX = cuerpo->GetLinearVelocity().x;
					}
					if(abs(cuerpo->GetLinearVelocity().y) > abs(VELOCIDAD_GLOBOHELIO)){
						velY = VELOCIDAD_GLOBOHELIO;
						cambiar = true;
					}else{
						velY = cuerpo->GetLinearVelocity().y;
					}
					if(cambiar){
						cuerpo->SetLinearVelocity(b2Vec2(velX,velY));
					}
				}
			}
		}
		cuerpo = cuerpo->GetNext();

	}
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
			Figura* figAEliminar = (Figura *)cuerpo->GetUserData();

			//si es un motor o balancin o engranaje borrar el static extra que tiene
			if ( figAEliminar->getTipoFigura() == MOTOR || figAEliminar->getTipoFigura()==BALANCIN || figAEliminar->getTipoFigura()==ENGRANAJE){
				
				b2Body* cuerpoARevisar = this->mundo->GetBodyList();
				
				while (cuerpoARevisar){
					if ( (cuerpoARevisar->GetPosition().x == figAEliminar->getDimension()->getX()) &&
					(cuerpoARevisar->GetPosition().y == figAEliminar->getDimension()->getY()) ){		
						//destruyo la joint
						b2JointEdge* listaUniones = cuerpo->GetJointList();
						mundo->DestroyJoint(listaUniones->joint);
						this->mundo->DestroyBody(cuerpoARevisar);
						break;
					}	
					cuerpoARevisar = cuerpoARevisar->GetNext();
				}
			}

			this->mundo->DestroyBody(cuerpo);
			break;
		}
		cuerpo = cuerpo->GetNext();
	}
}



Box2DWorld::~Box2DWorld(void)
{
	delete this->mundo;
	delete list;
}


void Box2DWorld::ponerEnPolea(Figura* soga,b2Body* cuerpo1,Figura* fig1,int num1,b2Body* cuerpo2,Figura* fig2,int num2){
	
	((Soga*)soga)->marcar(true);
	
	Polea* pol = NULL;
	int numPol;
	Figura* fig;
	int numFig;
	b2Body* cuerpoFig;

	if(fig1->getTipoFigura()==POLEA){
		pol = (Polea*) fig1;
		numPol = num1;
		fig = fig2;
		numFig = num2;
		cuerpoFig = cuerpo2;

		if (numPol==1){
			pol->setFigura1(fig);
			pol->numIzq = numFig;
			pol->cuerpoIzq = cuerpoFig;
			pol->sogaIzq = (Soga*) soga;
		}else{
			pol->setFigura2(fig);
			pol->numDer = numFig;
			pol->cuerpoDer = cuerpoFig;
			pol->sogaDer = (Soga*) soga;
		}
	}
	if(fig2->getTipoFigura()==POLEA){
		pol = (Polea*) fig2;
		numPol = num2;
		fig = fig1;
		numFig = num1;
		cuerpoFig = cuerpo1;

		if (numPol==1){
			pol->setFigura1(fig);
			pol->numIzq = numFig;
			pol->cuerpoIzq = cuerpoFig;
			pol->sogaIzq = (Soga*) soga;
		}else{
			pol->setFigura2(fig);
			pol->numDer = numFig;
			pol->cuerpoDer = cuerpoFig;
			pol->sogaDer = (Soga*) soga;
		}
	}
	if(pol == NULL)	return;


	if((pol->getIzq(NULL)!=NULL)&&(pol->getDer(NULL)!=NULL)){
		
		if(pol->getIzq(NULL)==pol->getDer(NULL)) return;

		pol->marcarSogas(false);

		int numIzq,numDer;
		double x1Polea,y1Polea,x2Polea,y2Polea;
		double xFig1,yFig1,xFig2,yFig2;
		b2Body* cuerpoA,* cuerpoB;
		
		//busco las poleas mas extremas
 		Polea* poleaIzq = pol->getPolIzq(NULL,&numIzq);
		Polea* poleaDer = pol->getPolDer(NULL,&numDer);
		
		//busco cuales son los lugares de donde se van a atar las poleas
		poleaIzq->posAtableSoga(numIzq,&x1Polea,&y1Polea);
		poleaDer->posAtableSoga(numDer,&x2Polea,&y2Polea);

		//busco los lugares de donde atar los cuerpos
		if(numIzq == 1){
			pol->getIzq(NULL)->posAtableSoga(poleaIzq->numIzq,&xFig1,&yFig1);
			cuerpoA = poleaIzq->cuerpoIzq;
		}else{
			pol->getIzq(NULL)->posAtableSoga(poleaDer->numIzq,&xFig1,&yFig1);
			cuerpoA = poleaIzq->cuerpoDer;
		}
		if(numDer == 1){
			pol->getDer(NULL)->posAtableSoga(poleaDer->numIzq,&xFig2,&yFig2);
			cuerpoB = poleaDer->cuerpoIzq;
		}else{
			pol->getDer(NULL)->posAtableSoga(poleaDer->numDer,&xFig2,&yFig2);
			cuerpoB = poleaDer->cuerpoDer;
		}

		b2PulleyJointDef joint;
		joint.Initialize(cuerpoA,cuerpoB,b2Vec2(x1Polea,y1Polea),b2Vec2(x2Polea,y2Polea),b2Vec2(xFig1,yFig1),b2Vec2(xFig2,yFig2),1);
		
		b2Joint* pulleyJ = mundo->CreateJoint(&joint);

		pol->setJoint(pulleyJ);
	}
}

void Box2DWorld::eliminarSoga(Soga *figura){
	
	figura->marcar(true);

	if((figura->getFigura1()->getTipoFigura()!=POLEA)&&(figura->getFigura2()->getTipoFigura()!=POLEA)){
		b2Joint* joint = mundo->GetJointList();
		b2Joint* prox;
		while(joint){
			prox = joint->GetNext();
			if(joint->GetUserData()==figura){
				mundo->DestroyJoint(joint);
			}
			joint = prox;
		}
	}else{
		Polea* pol;
		if(figura->getFigura1()->getTipoFigura()==POLEA){
			pol = (Polea*) figura->getFigura1();
		}else{
			pol = (Polea*) figura->getFigura2();
		}
		pol->marcarSogas(true);

		mundo->DestroyJoint(pol->joint);

	}
}