#include "../inc/Command.hpp"

Command::~Command() {
}

Command::Command() {
}

void	Command::removePrefix(std::string& cmd) {
	if (cmd.front() == ':') {
		size_t end = cmd.find(' ', 0);
		if (end == std::string::npos)
			throw std::runtime_error("Invalid prefix");
		else
			cmd.erase(0, end + 1); // ignore prefixes because we dont handle it
	}
}

void	Command::parseCommandName(std::string &cmd) {
	size_t end = cmd.find(' ', 0);
	if (end == std::string::npos) {
		_command = cmd;
		cmd.erase(0);
	}
	else {
		this->_command = cmd.substr(0, end);
		cmd.erase(0, end + 1);
	}
}

void	Command::parseParameters(std::string& cmd) {
	if (cmd.empty()) {
		_params.push_back("");
		return ;
	}
	size_t startPos = 0;
	size_t endPos = 0;
	while (endPos != std::string::npos) {
		startPos = cmd.find_first_not_of(' ', endPos);
		if (startPos == std::string::npos)
			break ;
		if (cmd[startPos] == ':')
			break ;
		endPos = cmd.find(' ', startPos);
		_params.push_back(cmd.substr(startPos, endPos - startPos));
	}
	if (endPos != std::string::npos)
		cmd.erase(0, endPos + 1);
	else
		cmd.clear();
}

void	Command::parseTrailing(std::string &cmd) {
	if (cmd.empty()) {
		_trailing = std::string("");
		return ;
	}
	size_t colonPos = cmd.find(':', 0);
	if (colonPos == std::string::npos)
		_trailing = std::string("");
	else {
		_trailing = cmd.substr(colonPos + 1);
		cmd.erase(colonPos);
	}
}


void	Command::parseCommand(std::string& cmd) {
	if (cmd.size() <= 2 || cmd.substr(cmd.size() - 2) != "\r\n")
		// check for empty input and that its terminated with CRLF
		return ;
	cmd.erase(cmd.size() - 2); // remove \r\n
	removePrefix(cmd);
	parseCommandName(cmd);
	parseParameters(cmd);
	parseTrailing(cmd);
	printCmdInfo();
}

void	Command::printCmdInfo(void) {
	std::cout << std::endl << "Command name: [" << this->_command << "]" << std::endl << "Parameters: ";
	for (std::vector<std::string>::iterator it = _params.begin(); it != _params.end(); it++) {
		std::cout << "[" << *it << "]";
	}
	std::cout << std::endl << "Trailing: [" << _trailing << "]" << std::endl;
}

Command::Command(std::string buf) {
	try {
		parseCommand(buf);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}