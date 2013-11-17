#include "UnionMessage2.h"

UnionMessage2::UnionMessage2(void)
{
	this->type = MSG_TYPE_UNION2;
}

UnionMessage2::UnionMessage2(string msg):UnionMessage(msg)
{
	this->type = MSG_TYPE_UNION2;
}

UnionMessage2::~UnionMessage2(void)
{
}
