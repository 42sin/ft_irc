#include "../inc/Command.hpp"

Command::~Command() {
}

Command::Command() {
}

void	Command::printCmdInfo(void) {
	std::cout << std::endl << "----------------------------------------" << std::endl;
	std::cout << "Command name: " << this->_command<< std::endl << "Parameters: ";
	for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << "Trailing: " << _trailing << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}
