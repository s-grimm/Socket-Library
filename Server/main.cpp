#include <SocketLibrary.hpp>
#include <iostream>
using namespace std;
using namespace SocketLibrary;

int main(){
	cout << "Server..." << endl;
	SocketServer server( "127.0.0.1", (USHORT)49153, IPPROTO_TCP );
	server.Start();
	//server.Process();
	std::string rec = server.recieve_string();
	cout << "Recieved : " <<  rec << endl;
	cout << "Sending : \"Hello\"" << endl;
	server.send_string( "Hello" );
	int i = server.recieve_int();
	server.send_int( i *= 2 );
	server.Stop();
}