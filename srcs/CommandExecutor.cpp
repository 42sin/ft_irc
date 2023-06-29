#include "../inc/Command.hpp"

void	Command::executeCommand() {
	if (_command == "EXIT") {
		std::cout << "EXIT COMMAND LOL" << std::endl;
		_buffer = "testmessage\r\n";
	}
	// if abfragen auf commands, etc
}