#pragma once

#include "CreateFigureMessage.h"

class CreateButtonMessage: public CreateFigureMessage
{
public:
	CreateButtonMessage(string msg);
	CreateButtonMessage(void);
	~CreateButtonMessage(void);
};
