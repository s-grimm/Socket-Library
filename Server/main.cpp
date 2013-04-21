#include <SocketLibrary.hpp>
#include <iostream>
using namespace std;
using namespace SocketLibrary;

int main(){
	cout << "Server..." << endl;
	SocketServer server( "127.0.0.1", (USHORT)49153, IPPROTO_TCP );
	server.Start();
	//server.Process();
	cout << "Recieved : " << server.recieve_string() << endl;
	cout << "Sending : \"Hello\"" << endl;
	server.send_string( "Hello" );
	server.Stop();
}