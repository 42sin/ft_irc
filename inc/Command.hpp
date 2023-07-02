#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <exception>
#include <vector>
#include <iostream>

class Client;

class Command {
	std::string					_command;
	int							_clientFd;
	std::string					_trailing;
	std::string					_buffer;

	void	removePrefix(std::string&);
	void	parseCommand(std::string&);
	void	parseCommandName(std::string&);
	void	parseParameters(std::string&);
	void	parseTrailing(std::string&);
	void	printCmdInfo(void);
public:
	std::vector<std::string>	params;

	Command(std::string, int clientFd);
	Command();
	~Command();

	void		setBuffer(std::string str) { _buffer = str; }
	void		setClientFd(int fd) { _clientFd = fd; }

	std::string	getBuffer(void) const { return _buffer; }
	std::string	getCmdName(void) const { return _command; }
	std::string	getTrail(void) const { return _trailing; }
	int			getFd(void) const { return _clientFd; }
	std::string getCommand(void) const {return _command; }

	bool		operator== (const std::string& name) const { return _command == name; }
};

#endif