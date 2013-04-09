#include "SocketLibrary.hpp"

SocketLibrary::SocketLibrary( unsigned short port, IPPROTO protocol ) {
	_port = port;
	_protocol = protocol;
	_socketType = SOCK_DGRAM;
	_addressFamily = AF_INET;

	//_iResult = WSAStartup( MAKEWORD( 2, 2 ), &_wsaData );
	//
	//	if ( !_iResult ) {
	//		throw ERROR_UNHANDLED_EXCEPTION;
	//	}

	//_hSocket = socket( _addressFamily, _socketType, _protocol );

	//_serverAddress.sin_family = AF_INET;
	//_serverAddress.sin_port = htons( _port );
	//_serverAddress.sin_addr.s_addr = htonl( INADDR_ANY );

	//int res = bind( _hSocket, (sockaddr*)&_serverAddress, sizeof(sockaddr_in) );
	//if( res == SOCKET_ERROR ) {
	//closesocket( _hSocket );
	//throw ERROR_UNHANDLED_EXCEPTION;
	//}
}

SocketLibrary::~SocketLibrary() {

}