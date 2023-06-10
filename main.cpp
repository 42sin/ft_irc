#include <iostream>
#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>

void	createSocket(int port, std::string password) {
	int	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		throw std::runtime_error("Error creating socket");
	}
	struct sockaddr_in	socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);
	socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
		throw std::runtime_error("Bind failed");
	}
	if (listen(socket_fd, 128) < 0) {
		throw std::runtime_error("Listening on port failed");
	}
	int	addrlen = 0;
	int clientSocket_fd = accept(socket_fd, (struct sockaddr*)&socket_address, (socklen_t *)&addrlen);
	if (clientSocket_fd < 0) {
		throw std::runtime_error("Accepting connection failed");
	}
	(void)password;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Invalid amount of arguments" << std::endl;
		return 0;
	}
	try {
		createSocket(argc, argv[2]);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return -1;
	}

    return 0;
}