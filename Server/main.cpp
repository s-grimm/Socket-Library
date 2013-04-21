#include <SocketLibrary.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Question.hpp"
#include <thread>
#include <mutex>
#include <queue>

using namespace std;
using namespace SocketLibrary;

std::mutex server_lock;
SocketServer server( "127.0.0.1", (USHORT)49153, IPPROTO_TCP );

std::mutex questions_lock;
std::queue<Question> questions;
//std::queue<int> questions;

std::once_flag server_start_flag;

bool done;
int totalQuestions = 0;
int correctQuestions = 0;

void send_question(){
	while( !done && questions.size() > 0 ){
		try{
			Question c_question;
			{
				std::lock_guard<std::mutex> lock(questions_lock);
				c_question = questions.front();
				questions.pop();
			}

			std::lock_guard<std::mutex> lock(server_lock);
			server.send_string( c_question.display.c_str() );
			for(size_t i = 0; i < c_question.answers.size(); ++i )
			{
				Sleep(50); //Sleep for 50ms to avoid spamming client with data
				server.send_string( c_question.answers[i].c_str() );
			}

			int answer = server.recieve_int();
			if( answer == c_question.correct_index )
			{
				server.send_string("Correct!");
				correctQuestions++;
			}
			else
			{
				server.send_string("Wrong!");
			}
			server.recieve_string(); //hold for "ok"
			//this line is lock the thread until the client is ready for the next question
		}
		catch(...)
		{
		}
	}
}

void load_questions()
{
	std::lock_guard<std::mutex> lock(questions_lock);
	//questions.push(1);

	using namespace std;

	string fileName = "../Questions.txt";
	std::fstream leFile(fileName.c_str());

	if(leFile.is_open()){
		string line = "";
		while (!leFile.eof()){
			getline(leFile,line, '\n');
			if(line.length() > 0 && line[0] == '*' && line[1] != '*' )
			{
				Question q;
				
				stringstream convert;
				convert << line[1];
				convert >> q.correct_index;

				getline(leFile,line, '\n'); //display
				q.display = line;

				getline(leFile,line, '\n'); //q1
				q.answers[0] = line;

				getline(leFile,line, '\n'); //q2
				q.answers[1] = line;

				getline(leFile,line, '\n'); //q3
				q.answers[2] = line;

				getline(leFile,line, '\n'); //q4
				q.answers[3] = line;

				getline(leFile,line, '\n'); //pull off ** to denote end of question

				questions.push(q);
			}
		}
	}
	leFile.close();
}

int main(){
	done = false;

	cout << "Server..." << endl;

	thread t(load_questions);
	t.join();

	//send the number of questions to the client
	{
		std::lock_guard<std::mutex> lock(server_lock);
		server.Start();
		totalQuestions = questions.size();
		server.send_int( totalQuestions );
	}

	std::vector<thread> threads;

	for( size_t i = 0; i < 3; ++i ){
		threads.push_back(thread(send_question));
	}

	//clean up on threads
	for(auto& thread : threads){
		thread.join();
	}

	done = true;

	stringstream out;
	out << "You got " << correctQuestions << "/" << totalQuestions << " right. Thank you for playing.";

	server.send_string( out.str().c_str() );

	{
		std::lock_guard<std::mutex> lock(server_lock);
		server.Stop();
	}
}