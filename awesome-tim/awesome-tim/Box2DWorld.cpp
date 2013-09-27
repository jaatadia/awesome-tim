#include "Box2DWorld.h"

Box2DWorld::Box2DWorld(void)
{
}

Box2DWorld::Box2DWorld(float fuerzaX, float fuerzaY)
{
	this->mundo = new b2World(b2Vec2(fuerzaX,fuerzaY));
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
			
			break;
		case CIRCULO:
			{
				b2CircleShape forma;
				forma.m_radius = ((Circulo *)dim)->getRadio();
				
				b2FixtureDef fD;
				fD.shape = &forma;
				fD.density = 1.0;
				fD.friction = 0.3;
				fD.restitution = 0.6;
				cuerpo->CreateFixture(&fD);
			}
			break;
		case POLIGONOREGULAR:
			break;
	}
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
			dim->setAngulo(cuerpo->GetAngle());
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

Box2DWorld::~Box2DWorld(void)
{
	delete this->mundo;
}
