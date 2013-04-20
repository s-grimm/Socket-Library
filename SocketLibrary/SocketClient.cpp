#include <SocketLibrary.hpp>
#include <iostream>
using namespace SocketLibrary;
//------------//
//-- C'tors --//
//------------//
SocketClient::SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol ) :	_ipAddress(ipAddress), _port(port), _protocol(protocol), _socketType(SOCK_DGRAM), _addressFamily(AF_INET) { }
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

void SocketClient::Stop() {
	closesocket( _hSocket );
	WSACleanup();
}

void SocketClient::Process() {
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

void SocketClient::Restart() {
	Stop();
	Start();
}