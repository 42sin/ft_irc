#include "../inc/Command.hpp"

Command::Command(std::string buf) {
	try {
		parseCommand(buf);
		executeCommand();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}