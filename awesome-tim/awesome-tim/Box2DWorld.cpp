#include "Box2DWorld.h"

Box2DWorld::Box2DWorld(void)
{
}

Box2DWorld::Box2DWorld(float fuerzaX, float fuerzaY)
{
	this->mundo = new b2World(b2Vec2(fuerzaX,fuerzaY));
	//GROUNDBOX
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(50.0f, 100.0f);
	b2Body* groundBody = (this->mundo)->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 0.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

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
	switch(dim->getTipoDimension())
	{
		case TRIANGULO:
			break;
		case CUADRADO:
			{
				b2PolygonShape forma;
				forma.SetAsBox(((Cuadrado *) dim)->getAncho()/2, ((Cuadrado *) dim)->getAlto()/2);
				b2FixtureDef fD;
				fD.shape = &forma;
				fD.density = 1.0;
				fD.friction = 0.3;
				cuerpo->CreateFixture(&fD);
			}
			break;
		case GLOBOHELIO:
			cuerpo->SetGravityScale(0);
			cuerpo->ApplyLinearImpulse(b2Vec2(0.0, VELOCIDAD_GLOBOHELIO), cuerpo->GetWorldCenter());
		case PELOTABASQUET:
		case PELOTABOWLING:
			{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				b2FixtureDef fD;
				fD.shape = &forma;
				fD.density = dim->getDensidad();
				fD.friction = 0.3;
				fD.restitution = dim->getRestitucion();
				cuerpo->CreateFixture(&fD);
			}
			break;
		case POLIGONOREGULAR:
			{
				b2PolygonShape forma;
				b2Vec2 vertices[4];
				vertices[0].Set(((Cuadrado *) dim)->getX(), ((Cuadrado *) dim)->getY());
				vertices[1].Set(((Cuadrado *) dim)->getX(), ((Cuadrado *) dim)->getY() - 20);
				vertices[2].Set(((Cuadrado *) dim)->getX() + 20, ((Cuadrado *) dim)->getY() - 20);
				vertices[3].Set(((Cuadrado *) dim)->getX() + 20, ((Cuadrado *) dim)->getY());
				forma.Set(vertices,4);
				b2FixtureDef fD;
				fD.shape = &forma;
				fD.density = 1.0;
				fD.friction = 0.3;
				cuerpo->CreateFixture(&fD);
			}
			break;
		case SOGA:
			{
				b2Body* segmentoAnterior;
				b2Body* segmentoSiguiente;

				FiguraCompuesta* fig = (FiguraCompuesta*) figura;
				std::list<Figura*> segmentosSoga = fig->getFigurasComp();

				std::list<Figura*>::iterator iterSegmentos;
				
				//meto el primero
				iterSegmentos = segmentosSoga.begin();

				bD.position.Set((*iterSegmentos)->getDimension()->getX(), (*iterSegmentos)->getDimension()->getY());
				segmentoAnterior = this->mundo->CreateBody(&bD);

				b2PolygonShape forma;
				
				b2FixtureDef fD;

				forma.SetAsBox((*iterSegmentos)->getDimension()->getAncho(),(*iterSegmentos)->getDimension()->getAlto());
				fD.shape = &forma;
				//pendientes de ajuste luego de experimentar un poco
				fD.density = 1.0;
				fD.friction = 0.3;

				segmentoAnterior->CreateFixture(&fD);

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

					//los uno
					b2RevoluteJointDef jointDef;

					b2Vec2 puntoAnclaje ((*iterSegmentos)->getDimension()->getAncho(),(*iterSegmentos)->getDimension()->getAlto()/2);
					jointDef.Initialize(segmentoAnterior, segmentoSiguiente, segmentoAnterior->GetWorldPoint(puntoAnclaje));

					//guardo el que se unira en el paso siguiente
					segmentoAnterior = segmentoSiguiente;
				}

			}
			break;
	}
	//Vos que queres eficiencia, esto no va en body definition?
	cuerpo->SetTransform(cuerpo->GetPosition(),figura->getDimension()->getAngulo()/180*PI);
	cuerpo->SetUserData(figura);
}

void Box2DWorld::actualizar(Figura * figura)
{
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
