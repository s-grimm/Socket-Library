#include "SocketLibrary.hpp"

SocketLibrary::SocketLibrary() {
	unsigned short const PORT = 49153;
	_iResult = WSAStartup( MAKEWORD(2,2), &_wsaData );

	if (_iResult != 0 ) {
		throw ERROR_UNHANDLED_EXCEPTION;
	}

	_hSocket = socket( AF_INET, SOCK_DGRAM, 0 );

	sockaddr_in _serverAddress = { 0 };
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_port = htons(PORT);
	_serverAddress.sin_addr.s_addr = htonl( INADDR_ANY );

	int res = bind( _hSocket, (sockaddr*)&_serverAddress, sizeof(sockaddr_in) );
	if( res == SOCKET_ERROR ) {
		closesocket( _hSocket );
		throw ERROR_UNHANDLED_EXCEPTION;
	}
}

SocketLibrary::~SocketLibrary() {

}