#include <SocketLibrary.hpp>
#include <iostream>
using namespace SocketLibrary;

SocketClient::SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _addressFamily(AF_INET), _started(false) {
	if( _protocol == IPPROTO_TCP ) {
		_socketType = SOCK_STREAM;
	}
	else
	{
		_socketType = SOCK_DGRAM;
	}
}
SocketClient::SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(socketType), _addressFamily(addressFamily), _started(false) { }

SocketClient::~SocketClient() { }

void SocketClient::Start() {
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

	int res = connect( _hSocket, (sockaddr*)&_serverAddress, sizeof(_serverAddress) );
	if( res == SOCKET_ERROR ) {
		Stop();
		throw ERROR_UNHANDLED_EXCEPTION;
	}
	_started = true;
}

void SocketClient::Stop() {
	closesocket( _hSocket );
	WSACleanup();
	_started = false;
}

void SocketClient::send_int( int i ) {
	if( _protocol == IPPROTO_TCP ) {
		send( _hSocket, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
	}
	else
	{
	}
}

void SocketClient::send_string( const char* str ){
	unsigned int const MAX = 256;
	char buf[MAX];
	if( _protocol == IPPROTO_TCP ) {
		strcpy_s( buf, str );
		send( _hSocket, buf, (int)strlen( buf ) + 1, 0 );
	}
	else
	{
	}
}

int SocketClient::recieve_int(){
	if( _protocol == IPPROTO_TCP ) {
		int i = 0;
		recv( _hSocket, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
		return i;
	}
	else
	{
		int i = 0;
		recvfrom( _hSocket, reinterpret_cast<char*>( &i ), sizeof(i), 0, NULL, NULL );
		return i;
	}
}

std::string SocketClient::recieve_string(){
	unsigned int const MAX = 256;
	char buf[MAX] = "";
	if( _protocol == IPPROTO_TCP ) {
		recv( _hSocket, buf, MAX, 0 );
	}
	else
	{
		int n = recvfrom( _hSocket, buf, MAX, 0, NULL, NULL );
		buf[min(n,255)] = 0;
	}
	return buf;
}

bool SocketClient::is_started()
{
	return _started;
}

void SocketClient::Restart() {
	Stop();
	Start();
}