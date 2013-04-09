#ifndef GUARD__SocketLibrary_hpp__
#define GUARD__SocketLibrary_hpp__

#if defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt-sgd.lib")
#elif defined(_DEBUG) && defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt-gd.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt-s.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt.lib")
#endif

#include <WinSock2.h>
#include <WS2tcpip.h>

class SocketLibrary
{
private:
	WSADATA _wsaData;
	int _iResult;
	SOCKET _hSocket;
	IPPROTO _protocol;
	unsigned short _port;
	sockaddr_in _serverAddress;
	unsigned short _socketType;
	ADDRESS_FAMILY _addressFamily;
public:
	SocketLibrary( unsigned short port, IPPROTO protocol );

	~SocketLibrary();

	void set_port( unsigned short port );
};

#endif