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
	if (end == std::string::npos)
		throw std::runtime_error("No parameters");
	else {
		this->command = cmd.substr(0, end);
		cmd.erase(0, end + 1);
	}
}

void	Command::parseParameters(std::string& cmd) { // still needs to be edited because there can be multiple parameters each separated with space
	size_t end = cmd.find(' ', 0);
	if (end == std::string::npos)
		this->params = std::string("");
	else {
		this->params = cmd.substr(0, end);
		cmd.erase(0, end + 1);
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
	this->trailing = cmd;
}

Command::Command(std::string buf) {
	try {
		parseCommand(buf);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}