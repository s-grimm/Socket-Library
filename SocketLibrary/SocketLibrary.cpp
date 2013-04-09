#include "SocketLibrary.hpp"

//------------//
//-- C'tors --//
//------------//
SocketLibrary::SocketLibrary( USHORT port, IPPROTO protocol ) :	_port(port), _protocol(protocol), _socketType(SOCK_DGRAM), _addressFamily(AF_INET) { }
SocketLibrary::SocketLibrary( USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily ) :	_port(port), _protocol(protocol), _socketType(socketType), _addressFamily(addressFamily) { }

SocketLibrary::~SocketLibrary() { }

//----------------------//
//-- Accessor Methods --//
//----------------------//
//void SocketLibrary::set_wsaData( WSADATA wsaData ) { _wsaData = wsaData; }
WSADATA& SocketLibrary::get_wsaData() { return _wsaData; }

//void SocketLibrary::set_iResult( int iResult ) { _iResult = iResult; }
int& SocketLibrary::get_iResult() { return _iResult; }

//void SocketLibrary::set_socket( SOCKET hSocket ) { _hSocket = hSocket; }
SOCKET& SocketLibrary::get_socket() { return _hSocket; }

//void SocketLibrary::set_serverAddress( sockaddr_in serverAddress ) { _serverAddress = serverAddress; }
sockaddr_in& SocketLibrary::get_serverAddress() { return _serverAddress; }

void SocketLibrary::set_port( USHORT port ) { _port = port; }
USHORT& SocketLibrary::get_port() { return _port; }

void SocketLibrary::set_protocol( IPPROTO protocol ) { _protocol = protocol; }
IPPROTO& SocketLibrary::get_protocol() { return _protocol; }

void SocketLibrary::set_socketType( USHORT socketType ) { _socketType = socketType; }
USHORT& SocketLibrary::get_socketType() { return _socketType; }

void SocketLibrary::set_addressFamily( ADDRESS_FAMILY addressFamily ) { _addressFamily = addressFamily; }
ADDRESS_FAMILY& SocketLibrary::get_addressFamily() { return _addressFamily; }

//--------------------//
//-- Helper Methods --//
//--------------------//
void SocketLibrary::Start() {
	_iResult = WSAStartup( MAKEWORD( 2, 2 ), &_wsaData );

	if ( !_iResult ) {
		throw ERROR_UNHANDLED_EXCEPTION;
	}

	_hSocket = socket( _addressFamily, _socketType, _protocol );

	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_port = htons( _port );
	_serverAddress.sin_addr.s_addr = htonl( INADDR_ANY );

	int res = bind( _hSocket, (sockaddr*)&_serverAddress, sizeof(sockaddr_in) );
	if( res == SOCKET_ERROR ) {
		closesocket( _hSocket );
		throw ERROR_UNHANDLED_EXCEPTION;
	}
}

void SocketLibrary::Stop() {
	closesocket( _hSocket );
	WSACleanup();
}

void SocketLibrary::Restart() {
	Stop();
	Start();
}