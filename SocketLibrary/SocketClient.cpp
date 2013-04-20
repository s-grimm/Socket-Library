#include <SocketLibrary.hpp>
#include <iostream>
using namespace SocketLibrary;
//------------//
//-- C'tors --//
//------------//
SocketClient::SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(SOCK_STREAM), _addressFamily(AF_INET) { }
SocketClient::SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(socketType), _addressFamily(addressFamily) { }

SocketClient::~SocketClient() { }

//----------------------//
//-- Accessor Methods --//
//----------------------//
WSADATA& SocketClient::get_wsaData() { return _wsaData; }

int& SocketClient::get_iResult() { return _iResult; }

SOCKET& SocketClient::get_socket() { return _hSocket; }

sockaddr_in& SocketClient::get_serverAddress() { return _serverAddress; }

void SocketClient::set_port( USHORT port ) { _port = port; }
USHORT& SocketClient::get_port() { return _port; }

void SocketClient::set_protocol( IPPROTO protocol ) { _protocol = protocol; }
IPPROTO& SocketClient::get_protocol() { return _protocol; }

void SocketClient::set_socketType( USHORT socketType ) { _socketType = socketType; }
USHORT& SocketClient::get_socketType() { return _socketType; }

void SocketClient::set_addressFamily( ADDRESS_FAMILY addressFamily ) { _addressFamily = addressFamily; }
ADDRESS_FAMILY& SocketClient::get_addressFamily() { return _addressFamily; }

//--------------------//
//-- Helper Methods --//
//--------------------//
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
}

void SocketClient::Stop() {
	closesocket( _hSocket );
	WSACleanup();
}

void SocketClient::Process() {
	unsigned int const MAX = 256;
	char buf[MAX];
	strcpy( buf, "Hello" );
	int bytesSent = send( _hSocket, buf, strlen( buf ) + 1, 0 );
	std::cout << "Sent: " << bytesSent << " bytes" << std::endl;

	int bytesRecv = recv( _hSocket, buf, MAX, 0 );
	std::cout << "Recieved " << bytesRecv << " bytes" << std::endl;
	std::cout << "Msg: " << buf << std::endl;

	int i = 42;
	send( _hSocket, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
	recv( _hSocket, reinterpret_cast<char*>( &i ), sizeof(i), 0 );
	std::cout << "i = " << i << std::endl;
}

void SocketClient::Restart() {
	Stop();
	Start();
}