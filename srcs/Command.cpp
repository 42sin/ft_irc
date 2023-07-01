#include "../inc/Command.hpp"

Command::Command(std::string buf, int clientFd) : _buffer("") {
	_clientFd = clientFd;
	try {
		parseCommand(buf);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}