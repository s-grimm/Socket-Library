#include <SocketLibrary.hpp>
#include <iostream>
using namespace std;
using namespace SocketLibrary;

int main(){
	cout << "Client..." << endl;

	int x = 10;

	SocketClient client( "127.0.0.1", (USHORT)49153, IPPROTO_TCP );
	client.Start();
	for(int i = 0; i < 3; ++i){
		/*client.send_string("Testing....");
		cout << "Recieved : " << client.recieve_string() << endl;
		client.send_int( x );
		x = client.recieve_int();
		cout << "Recieved : " << x << endl;
		int c;
		std::cin >> c;
		client.send_int( c );
		c = client.recieve_int();
		cout << "Recieved : " << c << endl;*/

		cout << client.recieve_string() << endl;
		for(int j = 0; j < 4; ++j){
			cout << client.recieve_string() << endl;
		}
		int c;
		std::cin >> c;
		client.send_int( c );
		cout << client.recieve_string() << endl;
		std::cin;
		client.send_string("ok");
	}
	client.Stop();
}