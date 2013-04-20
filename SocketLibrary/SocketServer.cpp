#include <SocketLibrary.hpp>
#include <iostream>
using namespace SocketLibrary;
//------------//
//-- C'tors --//
//------------//
SocketServer::SocketServer( std::string ipAddress, USHORT port, IPPROTO protocol ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(SOCK_DGRAM), _addressFamily(AF_INET) {}
SocketServer::SocketServer( std::string ipAddress, USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(socketType), _addressFamily(addressFamily) { }

SocketServer::~SocketServer() { }

//----------------------//
//-- Accessor Methods --//
//----------------------//
WSADATA& SocketServer::get_wsaData() { return _wsaData; }

int& SocketServer::get_iResult() { return _iResult; }

SOCKET& SocketServer::get_socket() { return _hSocket; }

sockaddr_in& SocketServer::get_serverAddress() { return _serverAddress; }

void SocketServer::set_port( USHORT port ) { _port = port; }
USHORT& SocketServer::get_port() { return _port; }

void SocketServer::set_protocol( IPPROTO protocol ) { _protocol = protocol; }
IPPROTO& SocketServer::get_protocol() { return _protocol; }

void SocketServer::set_socketType( USHORT socketType ) { _socketType = socketType; }
USHORT& SocketServer::get_socketType() { return _socketType; }

void SocketServer::set_addressFamily( ADDRESS_FAMILY addressFamily ) { _addressFamily = addressFamily; }
ADDRESS_FAMILY& SocketServer::get_addressFamily() { return _addressFamily; }

//--------------------//
//-- Helper Methods --//
//--------------------//
void SocketServer::Start() {
	_iResult = WSAStartup( MAKEWORD( 2, 2 ), &_wsaData );
	if ( !_iResult ) {
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

	if( listen( _hSocket, 1 ) == SOCKET_ERROR )	{
		Stop();
		throw ERROR_UNHANDLED_EXCEPTION;
	}
}

void SocketServer::Stop() {
	closesocket( _hSocket );
	WSACleanup();
}

void SocketServer::Process() {
	for(;;) {
		sockaddr	clientAddress;
		socklen_t	cbClientAddress = sizeof(clientAddress);
		int const MAXLINE = 256;
		char msg[MAXLINE];

		int n = recvfrom( _hSocket, msg, MAXLINE, 0, &clientAddress, &cbClientAddress );
		msg[min(n,255)] = 0;
		std::cout << "Recv: " << msg << std::endl;
		if( !strcmp(msg, "!quit") ) {
			std::string const terminateMsg = "server exit";
			sendto( _hSocket, terminateMsg.c_str(), terminateMsg.size(), 0, &clientAddress, cbClientAddress );
			break;
		}
		msg[0] = toupper( msg[0] );
		sendto( _hSocket, msg, n, 0, &clientAddress, cbClientAddress );
	}
}

void SocketServer::Restart() {
	Stop();
	Start();
}