#ifndef __SOCKETEXCEPTION_H__
#define __SOCKETEXCEPTION_H__

#include <exception>
#include <string>

using namespace std;

class SocketException : public exception
{
public:
	SocketException(string mensaje);
	~SocketException(void);
};

#endif // __SOCKETEXCEPTION_H__