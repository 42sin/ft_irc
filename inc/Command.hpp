#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <exception>
#include <vector>
#include <iostream>

class Command {
	std::string					_command;
	std::vector<std::string>	_params;
	std::string					_trailing;

	void	removePrefix(std::string&);
	void	parseCommand(std::string&);
	void	parseCommandName(std::string&);
	void	parseParameters(std::string&);
	void	parseTrailing(std::string&);
	void	printCmdInfo(void);
	void	executeCommand(void);
public:
	Command(std::string);
	Command();
	~Command();
};

#endif