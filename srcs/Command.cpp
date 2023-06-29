#include "../inc/Command.hpp"

Command::~Command() {
}

Command::Command() {
}

void	replaceNL(std::string& str) {
	std::replace(str.begin(), str.end(), '\n', ' ');
}

void	Command::removePrefix(std::string& cmd) {
	if (cmd.front() == ':') {
		size_t end = cmd.find(' ', 0);
		if (end == std::string::npos)
			throw std::runtime_error("Invalid prefix");
		else
			cmd = cmd.substr(end + 1); // ignore prefixes because we dont handle it
	}
}

void	Command::parseCommandName(std::string &cmd) {
	size_t end = cmd.find(' ', 0);
	if (end == std::string::npos) {
		_command = cmd;
		cmd = "";
	}
	else {
		this->_command = cmd.substr(0, end);
		cmd = cmd.substr(end + 1);
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
		cmd = cmd.substr(endPos + 1);
	else
		cmd = "";
}

void	Command::parseTrailing(std::string &cmd) {
	size_t colonPos = cmd.find(':', 0);
	if (colonPos != std::string::npos) {
		_trailing = cmd.substr(colonPos + 1);
		cmd = cmd.substr(0, colonPos);
	}
	else
		_trailing = "";
}

void	Command::parseCommand(std::string& cmd) {
	if (cmd.size() <= 2 || cmd.substr(cmd.size() - 2) != "\r\n")
		return ;
	cmd.erase(cmd.size() - 2);
	removePrefix(cmd);
	parseCommandName(cmd);
	replaceNL(cmd);
	parseParameters(cmd);
	parseTrailing(cmd);
	printCmdInfo();
}

void	Command::printCmdInfo(void) {
	std::cout << std::endl << "----------------------------------------" << std::endl;
	std::cout << "Command name: [" << this->_command << "]" << std::endl << "Parameters: ";
	for (std::vector<std::string>::iterator it = _params.begin(); it != _params.end(); it++) {
		std::cout << "[" << *it << "]";
	}
	std::cout << std::endl << "Trailing: [" << _trailing << "]" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}

Command::Command(std::string buf) {
	try {
		parseCommand(buf);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}