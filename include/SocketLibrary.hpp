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
#pragma comment (lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
namespace SocketLibrary
{
	struct Client {
		sockaddr	clientAddress;
		socklen_t	cbClientAddress;
		SOCKET		hAccepted;
		Client() {}
		Client(sockaddr client) : clientAddress( client ), cbClientAddress( sizeof( client ) ) {}
		Client(SOCKET socket) : hAccepted( socket ) {}
		~Client() {}
	};

	class SocketServer {
	private:
		WSADATA _wsaData;
		int _iResult;
		SOCKET _hSocket;
		sockaddr_in _serverAddress;
		std::string _ipAddress;
		USHORT _port;
		IPPROTO _protocol;
		USHORT _socketType;
		ADDRESS_FAMILY _addressFamily;
		Client _client;
		bool _started;
	public:
		SocketServer( std::string ipAddress, USHORT port, IPPROTO protocol );
		SocketServer( std::string ipAddress, USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily );

		~SocketServer();

		void Start();
		void Stop();

		void send_int( const int i );
		void send_string( const char* str );
		int recieve_int();
		std::string recieve_string();
		bool is_started();
	protected:
		void Restart();
	};

	class SocketClient {
		WSADATA _wsaData;
		int _iResult;
		SOCKET _hSocket;
		sockaddr_in _serverAddress;
		std::string _ipAddress;
		USHORT _port;
		IPPROTO _protocol;
		USHORT _socketType;
		ADDRESS_FAMILY _addressFamily;
		bool _started;
	public:
		SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol );
		SocketClient( std::string ipAddress, USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily );

		~SocketClient();

		void Start();
		void Stop();

		void send_int( const int i );
		void send_string( const char* str );
		int recieve_int();
		std::string recieve_string();
		bool is_started();

	protected:
		void Restart();
	};
}
#endif