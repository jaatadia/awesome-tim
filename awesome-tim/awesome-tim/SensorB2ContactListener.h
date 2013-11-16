#pragma once
#include "b2contactlistener.h"
#include "FiguraSensor.h"

class SensorB2ContactListener :
	public b2ContactListener
{
public:
	SensorB2ContactListener(void);
	~SensorB2ContactListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	void terminar();
};
