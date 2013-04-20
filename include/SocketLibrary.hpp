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
#include <vector>


namespace SocketLibrary
{
	struct ConnectedClient {
		sockaddr	_clientAddress;
		socklen_t	_cbClientAddress;

		ConnectedClient( sockaddr address ) : _clientAddress ( address ) {
			_cbClientAddress = sizeof( _clientAddress );
		}
	};
	
	class SocketServer {	
	private:
			WSADATA _wsaData;
			int _iResult;
			SOCKET _hSocket;
			sockaddr_in _serverAddress;
			std::vector<ConnectedClient> _connectedClients;
			USHORT _port;
			IPPROTO _protocol;
			USHORT _socketType;
			ADDRESS_FAMILY _addressFamily;
		public:
			//------------//
			//-- C'tors --//
			//------------//
			SocketServer( USHORT port, IPPROTO protocol );
			SocketServer( USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily );

			~SocketServer();

			//----------------------//
			//-- Accessor Methods --//
			//----------------------//
			WSADATA& get_wsaData();

			int& get_iResult();

			SOCKET& get_socket();

			sockaddr_in& get_serverAddress();

			void set_port( USHORT port );
			USHORT& get_port();

			void set_protocol( IPPROTO protocol );
			IPPROTO& get_protocol();

			void set_socketType( USHORT socketType );
			USHORT& get_socketType();

			void set_addressFamily( ADDRESS_FAMILY addressFamily );
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

	class SocketClient {
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
			SocketClient( USHORT port, IPPROTO protocol );
			SocketClient( USHORT port, IPPROTO protocol, USHORT socketType, ADDRESS_FAMILY addressFamily );

			~SocketClient();

			//----------------------//
			//-- Accessor Methods --//
			//----------------------//
			WSADATA& get_wsaData();

			int& get_iResult();

			SOCKET& get_socket();

			sockaddr_in& get_serverAddress();

			void set_port( USHORT port );
			USHORT& get_port();

			void set_protocol( IPPROTO protocol );
			IPPROTO& get_protocol();

			void set_socketType( USHORT socketType );
			USHORT& get_socketType();

			void set_addressFamily( ADDRESS_FAMILY addressFamily );
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
}
#endif