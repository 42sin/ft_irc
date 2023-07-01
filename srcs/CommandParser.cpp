#include "../inc/Command.hpp"

void	Command::removePrefix(std::string& cmd) {
	if (cmd.front() == ':') {
		size_t end = cmd.find(' ', 0);
		if (end == std::string::npos)
			throw std::runtime_error("Invalid prefix");
		else
			cmd = cmd.substr(end + 1);
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
	if (cmd.empty()) { // removed params.push_back("") because it is not needes as params.size() equals 0 then otherwise it will be 1
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
		params.push_back(cmd.substr(startPos, endPos - startPos));
	}
	if (endPos != std::string::npos) {
		if (cmd[endPos] == ':')
			cmd = cmd.substr(endPos);
		else
			cmd = cmd.substr(endPos + 1);
	}
	else
		cmd = "";
}

void	Command::parseTrailing(std::string &cmd) {
	size_t colonPos = cmd.find_first_of(':', 0);
	if (colonPos != std::string::npos) {
		_trailing = cmd.substr(colonPos + 1);
		cmd = cmd.substr(0, colonPos);
	}
	else
		_trailing = "";
}

void	Command::parseCommand(std::string& cmd) {
	if (cmd.size() > 512)
		throw std::runtime_error("Message too long");
	removePrefix(cmd);
	parseCommandName(cmd);
	std::replace(cmd.begin(), cmd.end(), '\n', ' ');
	parseParameters(cmd);
	parseTrailing(cmd);
	printCmdInfo();
}