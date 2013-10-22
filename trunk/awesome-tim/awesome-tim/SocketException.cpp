#include "SocketException.h"

SocketException::SocketException(string mensaje) : exception(mensaje.c_str())
{
}

SocketException::~SocketException(void)
{
}
