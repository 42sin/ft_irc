#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <exception>
#include <vector>
#include <iostream>
#include "Responses.hpp"

class Command {
	std::string					_command;
	std::vector<std::string>	_params;
	std::string					_trailing;
	int							_clientFd;
	std::string					_buffer;
	bool						_authenticated;

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
};

#endif