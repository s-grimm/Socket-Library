#include <SocketLibrary.hpp>
#include <iostream>
using namespace std;
using namespace SocketLibrary;

int main(){
	cout << "Client..." << endl;

	SocketClient client( "127.0.0.1", (USHORT)49153, IPPROTO_TCP );
	client.Start();
	client.send_string("Testing....");
	cout << "Recieved : " << client.recieve_string() << endl;
	client.send_int( 10 );
	cout << "Recieved : " << client.recieve_int() << endl;

	client.Stop();
}