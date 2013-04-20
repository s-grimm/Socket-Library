#include <SocketLibrary.hpp>
#include <iostream>
using namespace std;
using namespace SocketLibrary;

int main(){
	cout << "Server..." << endl;
	SocketServer server( "127.0.0.1", (USHORT)31337, IPPROTO_TCP );
	server.Start();
	server.Process();
	server.Stop();
}