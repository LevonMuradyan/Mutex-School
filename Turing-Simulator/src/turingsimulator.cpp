#include "turingsimulator.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

TuringSimulator::TuringSimulator(const std::string &filename)
{
	readFromFile(filename);
}

void TuringSimulator::run()
{
	process();
}

void TuringSimulator::readFromFile(const std::string & filename)
{

	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::ifstream::failure("Can't open input file, check the path.");
	}

	std::string line;
	size_t lineNumber = 1;
	std::vector<std::string> inputAlphabet;

	while (std::getline(file, line)) {

		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

		if (line.empty()) {
			continue;
		}

		std::cout << "line = " << line << std::endl;
        char delim = lineNumber > 2 && lineNumber < 3 + m_states.size() ? '|' : ',';

		std::istringstream ss(line);
		std::string token;
		size_t col = 0;

		while(std::getline(ss, token, delim)) {

			if (token.empty()) {
				throw std::runtime_error("Invalid file format: Alphabet or States can't be empty");
			}

			if (lineNumber == 1) {
				inputAlphabet.push_back(token);
            } else if (lineNumber == 2) {
				m_states.push_back(token);
            } else if (lineNumber > 2 && lineNumber <= 2 + m_states.size()) {
				std::istringstream ld(token);
				std::string ldItem;

				bool isLambda = true;
				while(std::getline(ld, ldItem, ',')) {

					if (ldItem.empty()) {
						throw std::runtime_error("Invalid file format: Lambda or Delta functions can't be empty");
					}

                    std::string key = m_states[lineNumber - 3] + ',' + inputAlphabet[col];
					if (isLambda) {
						if (std::find(outputAlphabet.begin(), outputAlphabet.end(), ldItem) == outputAlphabet.end()) {
							throw std::runtime_error("Invalid file format: Lambda function value isn't from the alphabet");
						}

						m_lambda[key] = ldItem;
						isLambda = false;
					} else {
						if (std::find(m_states.begin(), m_states.end(), ldItem) == m_states.end()) {
							throw std::runtime_error("Invalid file format: Delta function value isn't from the states");
						}

						m_delta[key] = ldItem;
						isLambda = true;
					}
				}
			} else if (lineNumber > 3 + m_states.size()) {
				for (size_t i = 0; i < token.size(); ++i) {
					if (std::find(inputAlphabet.begin(), inputAlphabet.end(), std::string(1, token[i])) == inputAlphabet.end()) {
						throw std::runtime_error("Invalid file format: input element isn't from the alphabet");
					}
				}

				m_input.push_back(token);
			}

			++col;
		}

		++lineNumber;
	}

	file.close();
}

void TuringSimulator::process()
{
	m_output.resize(m_input.size());
	for (size_t i = 0; i < m_input.size(); ++i) {
		std::string state = m_states[0];
		for (size_t j = 0; j < m_input[i].size(); ++j) {
			std::string key = state + ',' + m_input[i][j];
			m_output[i] += m_lambda[key];
			state = m_delta[key];
		}
	}
}
