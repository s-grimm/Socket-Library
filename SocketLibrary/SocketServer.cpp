#include <SocketLibrary.hpp>
#include <iostream>
using namespace SocketLibrary;

SocketServer::SocketServer( std::string ipAddress, USHORT port, IPPROTO protocol ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _addressFamily(AF_INET) {
	_client.hAccepted = SOCKET_ERROR;
	if( _protocol == IPPROTO_TCP ) {
		_socketType = SOCK_STREAM;
	}
	else
	{
		_socketType = SOCK_DGRAM;
	}
}
SocketServer::SocketServer( std::string ipAddress, USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(socketType), _addressFamily(addressFamily) {
	_client.hAccepted = SOCKET_ERROR;
}

SocketServer::~SocketServer() { }

void SocketServer::Start() {
	_iResult = WSAStartup( MAKEWORD( 2, 2 ), &_wsaData );
	if ( _iResult != 0 ) {
		throw ERROR_UNHANDLED_EXCEPTION;
	}

	_hSocket = socket( _addressFamily, _socketType, _protocol );
	if( _hSocket == INVALID_SOCKET ) {
		throw ERROR_UNHANDLED_EXCEPTION;
	}

	_serverAddress.sin_family = _addressFamily;
	_serverAddress.sin_port = htons( _port );
	_serverAddress.sin_addr.s_addr = inet_addr( _ipAddress.c_str() );

	int res = bind( _hSocket, (sockaddr*)&_serverAddress, sizeof(sockaddr_in) );
	if( res == SOCKET_ERROR ) {
		Stop();
		throw ERROR_UNHANDLED_EXCEPTION;
	}

	if( _protocol == IPPROTO_TCP ){
		if( listen( _hSocket, 1 ) == SOCKET_ERROR )	{
			Stop();
			throw ERROR_UNHANDLED_EXCEPTION;
		}

		//wait for a connection to the server
		while( _client.hAccepted == SOCKET_ERROR )
			_client.hAccepted = accept( _hSocket, NULL, NULL );
	}
}

void SocketServer::Stop() {
	closesocket( _hSocket );
	WSACleanup();
}

void SocketServer::Process() {
	std::cout << "Waiting for a connection" << std::endl;
	SOCKET hAccepted = SOCKET_ERROR;
	while( hAccepted == SOCKET_ERROR )
		hAccepted = accept( _hSocket, NULL, NULL );
	std::cout << "Client connected" << std::endl;

	unsigned int const MAX = 256;
	char buf[MAX];
	int bytesRecv = recv( hAccepted, buf, MAX, 0 );
	std::cout << "Recieved " << bytesRecv << " bytes" << std::endl;
	std::cout << "Msg: " << buf << std::endl;

	strcpy( buf, "Recieved" );
	int bytesSent = send( hAccepted, buf, strlen( buf ) + 1, 0 );
	std::cout << "Sent: " << bytesSent << " bytes" << std::endl;

	int i = 0;
	recv( hAccepted, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
	i *= 2;
	send( hAccepted, reinterpret_cast<char*>( &i ), sizeof(i), 0 );

	closesocket( hAccepted );
}

void SocketServer::send_int( int i ) {
	if( _protocol == IPPROTO_TCP ) {
		send( _client.hAccepted, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
	}
	else
	{
	}
}

void SocketServer::send_string( char* str ){
	unsigned int const MAX = 256;
	char buf[MAX];
	if( _protocol == IPPROTO_TCP ) {
		strcpy( buf, str );
		send( _client.hAccepted, buf, strlen( buf ) + 1, 0 );
	}
	else
	{
	}
}
int SocketServer::recieve_int(){
	if( _protocol == IPPROTO_TCP ) {
		int i = 0;
		recv( _client.hAccepted, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
		return i;
	}
	else
	{
		int i = 0;
		recvfrom( _hSocket, reinterpret_cast<char*>( &i ), sizeof(i), 0, &_client.clientAddress, &_client.cbClientAddress );
		return i;
	}
}
std::string SocketServer::recieve_string(){
	unsigned int const MAX = 256;
	char buf[MAX] = "";
	if( _protocol == IPPROTO_TCP ) {
		recv( _client.hAccepted, buf, MAX, 0 );
	}
	else
	{
		int n = recvfrom( _hSocket, buf, MAX, 0, &_client.clientAddress, &_client.cbClientAddress );
		buf[min(n,255)] = 0;
	}
	return buf;
}

void SocketServer::Restart() {
	Stop();
	Start();
}