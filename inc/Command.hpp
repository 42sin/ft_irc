#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <exception>
#include <iostream>

class Command {
	std::string command;
	std::string params;
	std::string	trailing;

	void	removePrefix(std::string&);
	void	parseCommand(std::string&);
	void	parseCommandName(std::string&);
	void	parseParameters(std::string&);
public:
	Command(std::string);
	Command();
	~Command();
};

#endif