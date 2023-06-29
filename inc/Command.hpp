#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <exception>
#include <vector>
#include <iostream>
#include "Responses.hpp"

enum vars {
	AUTHENTICATED = FALSE
}

class Command {
	std::string					_command;
	std::vector<std::string>	_params;
	std::string					_trailing;
	int							_clientFd;
	std::string					_buffer;

	void	removePrefix(std::string&);
	void	parseCommand(std::string&);
	void	parseCommandName(std::string&);
	void	parseParameters(std::string&);
	void	parseTrailing(std::string&);
	void	printCmdInfo(void);
	void	executeCommand(void);
public:
	std::string	getBuffer(void) const { return _buffer; };
	int			getFd(void) const { return _clientFd; };
	Command(std::string, int clientFd);
	Command();
	~Command();

	bool checkPass(std::string input_pass);
	void executePass();
};

#endif