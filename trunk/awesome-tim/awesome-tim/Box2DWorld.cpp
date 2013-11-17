#include "Box2DWorld.h"
#include "Engranaje.h"
#include "Motor.h"
#include "MotorRaton.h"
#include "Linea.h"
#include "Soga.h"
#include "Balancin.h"
#include "PedacitoSoga.h"
#include "Polea.h"
#include "PaletaFlipper.h"
#include "Carrito.h"
#include "Canio.h"
#include "Codo.h"
#include <iostream>

Box2DWorld::Box2DWorld(void){
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
		case FIG_SENSOR:{

			cuerpo->SetType(b2_staticBody);
			b2PolygonShape forma;
			double ancho = (dim)->getAncho();
			double alto = (dim)->getAlto();
			forma.SetAsBox(ancho/2,alto/2);
			fD.shape = &forma;
			fD.isSensor = true;
			cuerpo->CreateFixture(&fD);			

			break;
		}
		case BALA:{

			Bala* bala = (Bala*) figura;
			
			b2PolygonShape forma;
			
			b2Vec2 vertices[3];
			vertices[0] = b2Vec2(-dim->getAncho()/2,-dim->getAlto());
			vertices[1] = b2Vec2(dim->getAncho()/2,0);
			vertices[2] = b2Vec2(-dim->getAncho()/2,+dim->getAlto());
			forma.Set(vertices,3);

			fD.shape = &forma;
			fD.density = DENSIDAD_BALA;
			fD.restitution = RESTITUCION_BALA;
			fD.friction = FRICCION_BALA;
			cuerpo->CreateFixture(&fD);
			
			b2Vec2 fuerza = b2Vec2(bala->fuerzaX,bala->fuerzaY);
			cuerpo->SetLinearVelocity(fuerza);
			cuerpo->SetBullet(true);

			break;
		}
		case ESCOPETA:{

			cuerpo->SetType(b2_staticBody);

			b2PolygonShape forma;
			b2Vec2 vertices[4];
			vertices[0] = b2Vec2(-dim->getAncho()/2,-dim->getAlto()/2);
			vertices[1] = b2Vec2(dim->getAncho()/2,-dim->getAlto()/2);
			vertices[2] = b2Vec2(dim->getAncho()/2,-dim->getAlto()/4);
			vertices[3] = b2Vec2(-dim->getAncho()/2,+dim->getAlto()/2);
			forma.Set(vertices,4);

			fD.shape = &forma;
			fD.density = DENSIDAD_ARCO;
			fD.restitution = RESTITUCION_ARCO;
			fD.friction = FRICCION_ARCO;
			cuerpo->CreateFixture(&fD);
			((Escopeta*)figura)->cuerpo = cuerpo;

			break;
		}
		case FLECHA:{

			Flecha* flecha = (Flecha*) figura;
			
			b2PolygonShape forma;
			
			b2Vec2 vertices[4];
			vertices[0] = b2Vec2(-dim->getAncho()/2,0);
			vertices[1] = b2Vec2(dim->getAncho()/4,-dim->getAlto());
			vertices[2] = b2Vec2(+dim->getAncho()/2,0);
			vertices[3] = b2Vec2(dim->getAncho()/4,dim->getAlto());

			forma.Set(vertices,4);

			fD.shape = &forma;
			fD.density = 0;
			fD.restitution = RESTITUCION_FLECHA;
			fD.friction = FRICCION_FLECHA;
			cuerpo->CreateFixture(&fD);
			
			b2Vec2 fuerza = b2Vec2(flecha->fuerzaX,flecha->fuerzaY);
			cuerpo->SetLinearVelocity(fuerza);

			break;
		}
		case ARCO:{

			cuerpo->SetType(b2_staticBody);

			b2PolygonShape forma;
			b2Vec2 vertices[3];
			vertices[0] = b2Vec2(0,-dim->getAlto()/2);
			vertices[1] = b2Vec2(+dim->getAncho()/2,0);
			vertices[2] = b2Vec2(0,+dim->getAlto()/2);
			forma.Set(vertices,3);

			fD.shape = &forma;
			fD.density = DENSIDAD_ARCO;
			fD.restitution = RESTITUCION_ARCO;
			fD.friction = FRICCION_ARCO;
			cuerpo->CreateFixture(&fD);

			break;
		}
		case TIJERA:{

			cuerpo->SetType(b2_staticBody);

			b2PolygonShape forma;
			forma.SetAsBox(dim->getAncho()/2,dim->getAlto()/2);

			fD.shape = &forma;
			fD.density = DENSIDAD_TIJERA;
			fD.restitution = RESTITUCION_TIJERA;
			fD.friction = FRICCION_TIJERA;
			cuerpo->CreateFixture(&fD);

			break;
		}
		case CLAVO:{

			b2PolygonShape forma;

			b2Vec2 vertices[3];
			vertices[0] = b2Vec2(0,-dim->getAlto()/2);
			vertices[1] = b2Vec2(+dim->getAncho()/2,dim->getAlto()/2);
			vertices[2] = b2Vec2(-dim->getAncho()/2,dim->getAlto()/2);
			forma.Set(vertices,3);

			fD.shape = &forma;
			fD.density = DENSIDAD_CLAVO;
			fD.restitution = RESTITUCION_CLAVO;
			fD.friction = FRICCION_CLAVO;
			cuerpo->CreateFixture(&fD);
			
			break;
		}
		case CHINCHE:{
			
			cuerpo->SetType(b2_staticBody);

			b2PolygonShape forma;

			b2Vec2 vertices[3];
			vertices[0] = b2Vec2(-dim->getAncho()/2,-dim->getAlto()/2);
			vertices[1] = b2Vec2(+dim->getAncho()/2,-dim->getAlto()/2);
			vertices[2] = b2Vec2(0,+dim->getAlto()/2);
			forma.Set(vertices,3);

			fD.shape = &forma;
			fD.density = DENSIDAD_CHINCHE;
			fD.restitution = RESTITUCION_CHINCHE;
			fD.friction = FRICCION_CHINCHE;
			cuerpo->CreateFixture(&fD);
			
			break;
		}
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
		case CODO:{
				//fondo
				cuerpo->SetType(b2_staticBody);
				b2PolygonShape forma;
				double ancho = (dim)->getAncho();
				double alto = (dim)->getAlto();
				forma.SetAsBox(ancho/2,alto/2);
				fD.shape = &forma;
				fD.isSensor = true;
				cuerpo->CreateFixture(&fD);
				
				double x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6;
				((Codo*)figura)->calcularPuntosRotados(&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4,&x5,&y5,&x6,&y6);
				
				//pared12
				b2BodyDef pared12;
				pared12.position.Set(x1+(x2-x1)/2,y1+(y2-y1)/2);
				pared12.angle = ((Codo*)figura)->calcularAngulo(x1,y1,x2,y2);
				pared12.type = b2_staticBody;
				b2Body* cuerpo_pared12 = this->mundo->CreateBody(&pared12);

				b2PolygonShape forma_pared12;
				forma_pared12.SetAsBox((((Codo*)figura)->calcularAncho(x1,y1,x2,y2)-CODO_CORRECCION_UNION)/2,CANIO_BORDE/2);

				fD.shape = &forma_pared12;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				fD.isSensor = false;
				cuerpo_pared12->CreateFixture(&fD);

				//la uno al fondo
				b2WeldJointDef joint12;
				joint12.Initialize(cuerpo_pared12,cuerpo,cuerpo_pared12->GetPosition());
				b2Joint* enlace12 = this->mundo->CreateJoint(&joint12);

				//pared23
				b2BodyDef pared23;
				pared23.position.Set(x2+(x3-x2)/2,y2+(y3-y2)/2);
				pared23.angle = ((Codo*)figura)->calcularAngulo(x2,y2,x3,y3);
				pared23.type = b2_staticBody;
				b2Body* cuerpo_pared23 = this->mundo->CreateBody(&pared23);

				b2PolygonShape forma_pared23;
				forma_pared23.SetAsBox((((Codo*)figura)->calcularAncho(x2,y2,x3,y3)-CODO_CORRECCION_UNION)/2,CANIO_BORDE/2);

				fD.shape = &forma_pared23;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				fD.isSensor = false;
				cuerpo_pared23->CreateFixture(&fD);

				//la uno al fondo
				b2WeldJointDef joint23;
				joint23.Initialize(cuerpo_pared23,cuerpo,cuerpo_pared23->GetPosition());
				b2Joint* enlace23 = this->mundo->CreateJoint(&joint23);

				//pared54
				b2BodyDef pared54;
				pared54.position.Set(x5+(x4-x5)/2,y5+(y4-y5)/2);
				pared54.angle = ((Codo*)figura)->calcularAngulo(x5,y5,x4,y4);
				pared54.type = b2_staticBody;
				b2Body* cuerpo_pared54 = this->mundo->CreateBody(&pared54);

				b2PolygonShape forma_pared54;
				forma_pared54.SetAsBox((((Codo*)figura)->calcularAncho(x5,y5,x4,y4)-CODO_CORRECCION_UNION)/2,CANIO_BORDE/2);

				fD.shape = &forma_pared54;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				fD.isSensor = false;
				cuerpo_pared54->CreateFixture(&fD);

				//la uno al fondo
				b2WeldJointDef joint54;
				joint54.Initialize(cuerpo_pared54,cuerpo,cuerpo_pared54->GetPosition());
				b2Joint* enlace54 = this->mundo->CreateJoint(&joint54);

				//pared65
				b2BodyDef pared65;
				pared65.position.Set(x6+(x5-x6)/2,y6+(y5-y6)/2);
				pared65.angle = ((Codo*)figura)->calcularAngulo(x6,y6,x5,y5);
				pared65.type = b2_staticBody;
				b2Body* cuerpo_pared65 = this->mundo->CreateBody(&pared65);

				b2PolygonShape forma_pared65;
				forma_pared65.SetAsBox((((Codo*)figura)->calcularAncho(x6,y6,x5,y5)-CODO_CORRECCION_UNION)/2,CANIO_BORDE/2);

				fD.shape = &forma_pared65;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				fD.isSensor = false;
				cuerpo_pared65->CreateFixture(&fD);

				//la uno al fondo
				b2WeldJointDef joint65;
				joint65.Initialize(cuerpo_pared65,cuerpo,cuerpo_pared65->GetPosition());
				b2Joint* enlace65 = this->mundo->CreateJoint(&joint65);

				break;
			}
		case CANIO:{
				cuerpo->SetType(b2_staticBody);
				b2PolygonShape forma;
				double ancho = (dim)->getAncho();
				double alto = (dim)->getAlto();
				forma.SetAsBox(ancho/2,alto/2);
				fD.shape = &forma;
				fD.isSensor = true;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				cuerpo->CreateFixture(&fD);
				//std::cout << cuerpo->GetAngle() << "\n";

				b2BodyDef pared1;
				double x,y;
				((Canio*)figura)->getPosPared1(&x,&y);
				pared1.position.Set(x,y);
				//pared1.angle = -(dim->getAngulo()/180*PI);
				pared1.angle = cuerpo->GetAngle();
				pared1.type = b2_staticBody;
				b2Body* cuerpo_pared1 = this->mundo->CreateBody(&pared1);

				b2PolygonShape forma_pared1;
				b2PolygonShape forma_pared2;
				forma_pared1.SetAsBox(ancho/2,CANIO_BORDE/2);
				forma_pared2.SetAsBox(ancho/2,CANIO_BORDE/2);

				fD.shape = &forma_pared1;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				fD.isSensor = false;
				cuerpo_pared1->CreateFixture(&fD);
				//std::cout << cuerpo_pared1->GetAngle() << "\n";

				b2BodyDef pared2;
				((Canio*)figura)->getPosPared2(&x,&y);
				pared2.position.Set(x,y);
				//pared2.angle = -(dim->getAngulo()/180*PI);
				pared2.angle = cuerpo->GetAngle();
				pared2.type = b2_staticBody;
				b2Body* cuerpo_pared2 = this->mundo->CreateBody(&pared2);
				
				fD.shape = &forma_pared2;
				fD.density = PLATAFORMA_DENSIDAD;
				fD.friction = PLATAFORMA_FRICCION;
				fD.isSensor = false;
				cuerpo_pared2->CreateFixture(&fD);
				//std::cout << cuerpo_pared2->GetAngle() << "\n";

				//union del canio
				b2WeldJointDef joint1;
				joint1.Initialize(cuerpo_pared1,cuerpo,cuerpo_pared1->GetPosition());
				b2Joint* enlace1 = this->mundo->CreateJoint(&joint1);

				b2WeldJointDef joint2;
				joint2.Initialize(cuerpo_pared2,cuerpo,cuerpo_pared2->GetPosition());
				b2Joint* enlace2 = this->mundo->CreateJoint(&joint2);
					
				break;
			}
		case PALETA:{

				b2PolygonShape forma;
				forma.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
				fD.shape = &forma;
				fD.density = PALETA_DENSIDAD;
				fD.restitution = PALETA_RESTITUTION;
				fD.friction = PALETA_FRICCION;
				cuerpo->CreateFixture(&fD);
				cuerpo->SetBullet(true);

				b2BodyDef ejeDef;
				ejeDef.type = b2_staticBody;
				ejeDef.position.Set(((PaletaFlipper*)figura)->getXdeRotacion(),((PaletaFlipper*)figura)->getYdeRotacion());
				//ejeDef.position.Set(((PaletaFlipper*)figura)->getDimension()->getX()-3*((PaletaFlipper*)figura)->getDimension()->getAncho()/8,((PaletaFlipper*)figura)->getDimension()->getY());
												
				b2FixtureDef ejeFix;
				b2CircleShape ejeCirculo;
				ejeCirculo.m_radius = 0.0001;
				ejeFix.density = 9999999;
				ejeFix.shape = &ejeCirculo;
				ejeFix.isSensor = true;
				
				b2Body* eje = this->mundo->CreateBody(&ejeDef);
				eje->CreateFixture(&ejeFix);

				b2RevoluteJointDef joint;
				joint.Initialize(eje,cuerpo,eje->GetPosition());
				joint.enableLimit = true;
				
				if (((PaletaFlipper*)figura)->getSentido() == IZQUIERDA){
					joint.lowerAngle = -PI/2;
					joint.upperAngle = 0;
				}else{
					joint.lowerAngle = 0;
					joint.upperAngle = PI/2;
				}
				joint.enableMotor = true;
				joint.maxMotorTorque = 1000.0f;
				joint.motorSpeed = 0.0f;
						
				b2Joint* enlace = this->mundo->CreateJoint(&joint);

				((PaletaFlipper*)figura)->setBox2dData(cuerpo,(b2RevoluteJoint*)enlace);

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
		case QUESO:{
				b2PolygonShape forma;
				forma.SetAsBox((dim)->getAncho()/2,(dim)->getAlto()/2);
				fD.shape = &forma;
				fD.density = DENSIDAD_QUESO;
				fD.friction = FRICCION_QUESO;
				fD.restitution = RESTITUCION_QUESO;
				cuerpo->CreateFixture(&fD);
				break;
			}
		case VELA:{
				b2PolygonShape forma;
				double ancho = (dim)->getAncho()/2;
				double alto = (dim)->getAlto()/2;
				forma.SetAsBox(ancho,alto);

				fD.shape = &forma;
				fD.density = DENSIDAD_VELA;
				fD.friction = FRICCION_VELA;
				fD.restitution = RESTITUCION_VELA;
				cuerpo->CreateFixture(&fD);

				break;
			}
		case DOMINO:{
				b2PolygonShape forma;
				double ancho = (dim)->getAncho()/2;
				double alto = (dim)->getAlto()/2;
				forma.SetAsBox(ancho,alto);

				fD.shape = &forma;
				fD.density = DENSIDAD_DOMINO;
				fD.friction = FRICCION_DOMINO;
				fD.restitution = RESTITUCION_DOMINO;
				cuerpo->CreateFixture(&fD);

				break;
			}
		case CARRITO:{

				Sonidos::playMusic(CARRITO_MUSIC);
				//forma del carro con sus partes
				b2PolygonShape forma_base;
				//b2PolygonShape forma_pared1;
				//b2PolygonShape forma_pared2;
				double ancho = ((Carrito*)figura)->getCarro()->getDimension()->getAncho()/2;
				double alto = ((Carrito*)figura)->getCarro()->getDimension()->getAlto()/2;
				//forma_base.SetAsBox(ancho,alto/2);
				//forma_pared1.SetAsBox(ancho/8,alto);
				//forma_pared2.SetAsBox(ancho/8,alto);
				forma_base.SetAsBox(ancho,alto);

				fD.shape = &forma_base;
				fD.density = DENSIDAD_CARRITO;
				fD.friction = FRICCION_CARRITO;
				fD.restitution = RESTITUCION_CARRITO;
				//cuerpo->SetTransform(b2Vec2(((Carrito*)figura)->getCarro()->getDimension()->getX(),((Carrito*)figura)->getCarro()->getDimension()->getY()+alto/2),cuerpo->GetAngle());
				cuerpo->CreateFixture(&fD);
				cuerpo->SetUserData(((Carrito*)figura)->getCarro());

				//b2BodyDef pared1;
				//pared1.position.Set(((Carrito*)figura)->getCarro()->getDimension()->getX()-ancho+ancho/8,((Carrito*)figura)->getCarro()->getDimension()->getY());
				//pared1.type = b2_dynamicBody;
				//b2Body* cuerpo_pared1 = this->mundo->CreateBody(&pared1);

				//fD.shape = &forma_pared1;
				//cuerpo_pared1->CreateFixture(&fD);

				//b2BodyDef pared2;
				//pared2.position.Set(((Carrito*)figura)->getCarro()->getDimension()->getX()+ancho-ancho/8,((Carrito*)figura)->getCarro()->getDimension()->getY());
				//pared2.type = b2_dynamicBody;
				//b2Body* cuerpo_pared2 = this->mundo->CreateBody(&pared2);
				//
				//fD.shape = &forma_pared2;
				//cuerpo_pared2->CreateFixture(&fD);

				//union del carro
				//b2WeldJointDef jointcarro1;
				//jointcarro1.Initialize(cuerpo_pared1,cuerpo,b2Vec2(((Carrito*)figura)->getCarro()->getDimension()->getX()-ancho+ancho/8,((Carrito*)figura)->getCarro()->getDimension()->getY()-alto/2));
				//b2Joint* enlace_carro1 = this->mundo->CreateJoint(&jointcarro1);

				//b2WeldJointDef jointcarro2;
				//jointcarro2.Initialize(cuerpo_pared2,cuerpo,b2Vec2(((Carrito*)figura)->getCarro()->getDimension()->getX()+ancho-ancho/8,((Carrito*)figura)->getCarro()->getDimension()->getY()-alto/2));
				//b2Joint* enlace_carro2 = this->mundo->CreateJoint(&jointcarro2);

				//def de cuerpo de rueda izq
				b2BodyDef rueda1;
				rueda1.position.Set(((Carrito*)figura)->getRuedaIzq()->getDimension()->getX(),((Carrito*)figura)->getRuedaIzq()->getDimension()->getY());
				rueda1.type = b2_dynamicBody;
				b2Body* cuerpo_rueda1 = this->mundo->CreateBody(&rueda1);
				cuerpo_rueda1->SetUserData(((Carrito*)figura)->getRuedaIzq());

				//def de cuerpo de rueda der
				b2BodyDef rueda2;
				rueda2.position.Set(((Carrito*)figura)->getRuedaDer()->getDimension()->getX(),((Carrito*)figura)->getRuedaDer()->getDimension()->getY());
				rueda2.type = b2_dynamicBody;
				b2Body* cuerpo_rueda2 = this->mundo->CreateBody(&rueda2);
				cuerpo_rueda2->SetUserData(((Carrito*)figura)->getRuedaDer());
				
				//forma de las ruedas y asignacion
				b2CircleShape forma_rueda;
				forma_rueda.m_radius = ((Carrito*)figura)->getRuedaIzq()->getRadio();
				fD.shape = &forma_rueda;
				fD.density = DENSIDAD_CARRITO;
				fD.friction = FRICCION_CARRITO;
				fD.restitution = RESTITUCION_CARRITO;
				cuerpo_rueda1->CreateFixture(&fD);
				cuerpo_rueda2->CreateFixture(&fD);

				//union izq
				b2RevoluteJointDef joint1;
				joint1.Initialize(cuerpo_rueda1,cuerpo,cuerpo_rueda1->GetPosition());
				joint1.collideConnected = false;
				b2Joint* enlace1 = this->mundo->CreateJoint(&joint1);

				//union der
				b2RevoluteJointDef joint2;
				joint2.Initialize(cuerpo_rueda2,cuerpo,cuerpo_rueda2->GetPosition());
				joint2.collideConnected = false;
				b2Joint* enlace2 = this->mundo->CreateJoint(&joint2);
				
				Sonidos::stopMusic();

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
			
				//cuerpo->SetLinearVelocity(b2Vec2(0.0, VELOCIDAD_GLOBOHELIO));
				cuerpo->SetFixedRotation(true);
				cuerpo->SetAngularVelocity(0);
				
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
	   	case ARO:{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_ARO;
				fD.friction = FRICCION_ARO;
				fD.restitution = RESTITUCION_ARO;
				cuerpo->CreateFixture(&fD);
				cuerpo->SetType(b2_staticBody);
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
		case HUEVO:{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				fD.shape = &forma;
				fD.density = DENSIDAD_HUEVO;
				fD.friction = FRICCION_HUEVO;
				fD.restitution = RESTITUCION_HUEVO;
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
						if((fig1->getTipoFigura()!=TIJERA)&&(fig1->getTipoFigura()!=ESCOPETA)){
							unionSoga.bodyA=cuerpo1;
							unionSoga.bodyB=cuerpo2;
							unionSoga.localAnchorA = anchor1;
							unionSoga.localAnchorB = anchor2;
						}else{
							unionSoga.bodyA=cuerpo2;
							unionSoga.bodyB=cuerpo1;
							unionSoga.localAnchorA = anchor2;
							unionSoga.localAnchorB = anchor1;
						}
						
						x1 = cuerpo1->GetWorldPoint(anchor1).x;
						x2 = cuerpo2->GetWorldPoint(anchor2).x;
						y1 = cuerpo1->GetWorldPoint(anchor1).y;
						y2 = cuerpo2->GetWorldPoint(anchor2).y;

						
						unionSoga.maxLength = sqrt(pow(x1-x2,2)+pow(y1-y2,2)); 

						b2Joint* jointSoga = NULL;
						jointSoga = this->mundo->CreateJoint(&unionSoga);
						jointSoga->SetUserData(figura);
						return true;
						
						
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
		case MOTOR_RATON:
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

				MotorRaton* motor = (MotorRaton*)figura;
				if(activo && motor->motorActivo()){
					cuerpo->SetFixedRotation(true);
					cuerpo->SetAngularVelocity(VELOCIDAD_MOTOR*((MotorRaton*)figura)->sentido);
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

void Box2DWorld::actualizar(Figura * figura){

	//Hago que actualize tooodas las que tenga  << Juan	
	b2Body* cuerpo = this->mundo->GetBodyList();

	while(cuerpo)
	{
		Figura* fig  = (Figura*)cuerpo->GetUserData();
		
		if(fig!=NULL){
			
			if((fig->getTipoFigura()==PLATAFORMA)||(fig->getTipoFigura()==POLEA)||(fig->getTipoFigura()==CHINCHE)||(fig->getTipoFigura()==ARCO)){
				cuerpo = cuerpo->GetNext();
				continue;
			}
			

			if(fig->getTipoFigura()==TIJERA){
				actuarTijera(cuerpo,(Tijera*)fig);
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
			}else if(fig->getTipoFigura()==FLECHA){
				b2Vec2 vel = cuerpo->GetLinearVelocity();
				if (abs(vel.x)>1&&abs(vel.y)>1){
					double ang = atan2(vel.y,vel.x);
					cuerpo->SetTransform(cuerpo->GetPosition(),ang);
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
		if((pol->getIzq(NULL)->getTipoFigura()!=TIJERA)&&(pol->getIzq(NULL)->getTipoFigura()!=ESCOPETA)){
			joint.Initialize(cuerpoA,cuerpoB,b2Vec2(x1Polea,y1Polea),b2Vec2(x2Polea,y2Polea),b2Vec2(xFig1,yFig1),b2Vec2(xFig2,yFig2),1);
		}else{
			joint.Initialize(cuerpoB,cuerpoA,b2Vec2(x2Polea,y2Polea),b2Vec2(x1Polea,y1Polea),b2Vec2(xFig2,yFig2),b2Vec2(xFig1,yFig1),1);
		}
		joint.collideConnected = true;
		
		b2Joint* pulleyJ = mundo->CreateJoint(&joint);

		pol->setJoint(pulleyJ);
	}
}

void Box2DWorld::eliminarSoga(Soga *figura){
	
	figura->marcar(true);
	Figura* figura1;
	Figura* figura2;

	if((figura->getFigura1()->getTipoFigura()!=POLEA)&&(figura->getFigura2()->getTipoFigura()!=POLEA)){
		
		figura1 = figura->getFigura1();
		figura2 = figura->getFigura2();

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
		
		figura1 = pol->getIzq(NULL);
		figura2 = pol->getDer(NULL);
		pol->marcarSogas(true);

		mundo->DestroyJoint(pol->joint);

	}

	if(figura1->getTipoFigura()==ARCO){
		((Arco*)figura1)->desatarSoga(1);
	}
	if(figura2->getTipoFigura()==ARCO){
		((Arco*)figura2)->desatarSoga(1);
	}
}

void Box2DWorld::actuarTijera(b2Body* cuerpo, Tijera* fig){
	
	b2JointEdge* joint = cuerpo->GetJointList();
	bool cerrar = false;
	int mult = 1;
	double fuerzaLimite = 1;
	
	
	while(joint){
		b2Joint* una_joint = joint->joint;

		double anchor = una_joint->GetBodyB()->GetLocalPoint(una_joint->GetAnchorB()).y;
		double fuerzaY = una_joint->GetReactionForce(tiempoStep).y;
		double fuerzaX = una_joint->GetReactionForce(tiempoStep).x;
		double fuerza = ((fig->pos == 0)||(fig->pos==2)) ? fuerzaY:fuerzaX;

		int esSoga = (una_joint->GetType()==e_ropeJoint) ? 1:-1;
		int condicion = (anchor>0) ? 1:-1;
		int esPrimero = ((fig->pos==0)||(fig->pos==1)) ? 1:-1;
		
		
		if(fuerza*esSoga*condicion*esPrimero < -fuerzaLimite){
			cerrar = true;
		}
		joint = joint->next;
	}
				
	if (cerrar){
		((Tijera*)fig)->cerrar();
	}
}

void Box2DWorld::dispararEscopeta(Escopeta* escopeta,std::list<Figura*>* lista){
	if(escopeta->disparada)return;
	
	double angulo = -escopeta->getDimension()->getAngulo()*PI/180;
	b2Body* cuerpo = escopeta->cuerpo;
	double fuerzaLimite = 1;
	bool disparar = false;

	b2JointEdge* joint = cuerpo->GetJointList();

	while(joint){
		b2Joint* una_joint = joint->joint;
		b2Vec2 fuerza = una_joint->GetReactionForce(this->tiempoStep);

		if (fuerza.x*cos(angulo)+fuerza.y*sin(angulo)<-fuerzaLimite){
			disparar=true;
		}
		joint = joint->next;
	}
	if(disparar){
		lista->push_back(escopeta->disparar());
	}
}