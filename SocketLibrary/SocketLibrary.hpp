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
	sockaddr_in _serverAddress;
	USHORT _port;
	IPPROTO _protocol;
	USHORT _socketType;
	ADDRESS_FAMILY _addressFamily;
public:
	//------------//
	//-- C'tors --//
	//------------//
	SocketLibrary( USHORT port, IPPROTO protocol );
	SocketLibrary( USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily );

	~SocketLibrary();

	//----------------------//
	//-- Accessor Methods --//
	//----------------------//
	//void set_wsaData( WSADATA wsaData );
	WSADATA& get_wsaData();

	//void set_iResult( int iResult );
	int& get_iResult();

	//void set_socket( SOCKET hSocket );
	SOCKET& get_socket();

	//void set_serverAddress( sockaddr_in serverAddress );
	sockaddr_in& get_serverAddress();

	void set_port( USHORT port );
	USHORT& get_port();

	void set_protocol( IPPROTO protocol );
	IPPROTO& get_protocol();

	void set_socketType( USHORT set_socketType );
	USHORT& get_socketType();

	void set_addressFamily( ADDRESS_FAMILY );
	ADDRESS_FAMILY& get_addressFamily();

	//--------------------//
	//-- Helper Methods --//
	//--------------------//
	void Start();
	void Stop();
	void Process();

protected:
	void Restart();
};

#endif