#pragma once

#include "DropFigureMessage.h"

class DeleteFigureMessage: public DropFigureMessage
{
public:
	DeleteFigureMessage(void);
	DeleteFigureMessage(string msg);
	~DeleteFigureMessage(void);
};
