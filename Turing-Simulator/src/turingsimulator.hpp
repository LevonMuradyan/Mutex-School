#ifndef TURINGSIMULATOR_H
#define TURINGSIMULATOR_H

#include <string>
#include <vector>
#include <unordered_map>

class TuringSimulator
{
public:
	TuringSimulator(const std::string& filename);
	void run();
private:
	void readFromFile(const std::string& filename);
	void process();
private:
	std::vector<std::string> m_states;
	std::vector<std::string> m_input;
	std::vector<std::string> m_output;

	std::unordered_map<std::string, std::string> m_lambda;
	std::unordered_map<std::string, std::string> m_delta;
};

#endif // TURINGSIMULATOR_H
