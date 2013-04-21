#include <SocketLibrary.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
using namespace SocketLibrary;

std::mutex console_mutex;

std::mutex client_mutex;
SocketClient client( "127.0.0.1", (USHORT)49153, IPPROTO_TCP );

std::once_flag client_start_flag;

int numQuestions;
int answeredQuestions = 0;
bool done = false;

void get_question()
{
	while(!done && answeredQuestions < numQuestions){
		//lock the client and console to this thread so that we can continue
		std::lock_guard<std::mutex> lock_client(client_mutex);
		std::lock_guard<std::mutex> lock_console(console_mutex);
		if(!done && numQuestions > answeredQuestions){
			cout << client.recieve_string() << endl;
			for(int j = 0; j < 4; ++j){
				cout << client.recieve_string() << endl;
			}
			int c;
			std::cout << "Answer : ";
			std::cin >> c;
			client.send_int( c );
			cout << client.recieve_string() << endl;
			std::cout << std::endl;
			system("pause");
			std::cout << std::endl;
			client.send_string("ok");

			answeredQuestions++;
		}
	}
}

int main(){
	cout << "Client..." << endl;
	{
		std::lock_guard<std::mutex> lock_client(client_mutex);
		client.Start();
		numQuestions = client.recieve_int();
	}

	std::vector<thread> threads;

	for( size_t i = 0; i < 3; ++i ){
		threads.push_back(thread(get_question));
	}

	//clean up on threads
	for(auto& thread : threads){
		thread.join();
	}

	done = true;

	{
		std::lock_guard<std::mutex> lock_client(client_mutex);
		client.Stop();
	}
}