#pragma once

#include "Box2D/Box2D.h"
#include "Figura.h"
#include "MotorRaton.h"

class RatonB2ContactListener : public b2ContactListener{

public:
	RatonB2ContactListener(void);
	~RatonB2ContactListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	void terminar();
};
