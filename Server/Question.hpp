#ifndef __GUARD_QUESTION_HPP__
#define __GUARD_QUESTION_HPP__

#include <string>
#include <vector>

class Question
{
public:
	std::string display;
	std::vector<std::string> answers;
	int correct_index;

	Question() {
		display = "";
		correct_index = 0;
		for( size_t i = 0; i < 4; ++ i )
			answers.push_back("");
	}

	~Question() {}
};
#endif