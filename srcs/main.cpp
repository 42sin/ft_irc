#include "../inc/headers.hpp"

void	createSocket(int port, std::string password) {
	int	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		throw std::runtime_error("Error creating socket");
	}
	if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) < 0) {
		throw std::runtime_error("Error setting socket to non-blocking mode");
	}

	struct sockaddr_in	socket_address;
	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);
	socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
		throw std::runtime_error("Bind failed");
	}
	if (listen(socket_fd, 128) < 0) {
		throw std::runtime_error("Listening on port failed");
	}

	while (1) {
		int	addrlen = 0;
		int clientSocket_fd = accept(socket_fd, (struct sockaddr*)&socket_address, (socklen_t *)&addrlen);
		if (clientSocket_fd < 0) {
			continue ;
		}
		std::cout << "Connected client fd: " << clientSocket_fd << std::endl;
		fcntl(clientSocket_fd, F_SETFL, O_NONBLOCK);

		close(clientSocket_fd);
	}
	(void)password;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Invalid amount of arguments" << std::endl;
		return 0;
	}
	try {
		int	port = std::atoi(argv[1]);
		if (port <= 0 || std::string(argv[1]).find_first_not_of("0123456789", 0) != std::string::npos) {
			std::cout << "Invalid port" << std::endl;
			return 0;
		}
		createSocket(port, argv[2]);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
    return 0;
}