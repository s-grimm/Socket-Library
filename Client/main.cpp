#include <SocketLibrary.hpp>
#include <iostream>
using namespace std;
using namespace SocketLibrary;

int main(){
	cout << "Client..." << endl;	
	SocketClient client( "127.0.0.1", (USHORT)31337, IPPROTO_TCP );
	client.Start();
	client.Process();
	client.Stop();
}