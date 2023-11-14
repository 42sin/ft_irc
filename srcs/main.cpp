#include "../inc/Server.hpp"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Invalid amount of arguments" << std::endl;
		return 0;
	}
	try {
		int	port = std::atoi(argv[1]);
		if (port <= 0 || port > 65535 || std::string(argv[1]).find_first_not_of("0123456789", 0) != std::string::npos) {
			std::cout << "Invalid port" << std::endl;
			return 0;
		}
		Server server(port, argv[2]);
		server.run();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
    return 0;
}