#include "../inc/Server.hpp"

Server::Server() :_port(0), _password(NULL), _serverSocketFd(0), _clients(0, 0) {
}

Server::~Server() {
	std::cout << std::endl;
	for (size_t i = 0; i < _clients.size(); i++) {
		std::cout << "Closing client fd: " << _clients[i]->getFd() << std::endl;
		delete _clients[i];
	}
	for (size_t i = 0; i < _channels.size(); i++)
		delete _channels[i];
	_channels.clear();
	close(_serverSocketFd);
}

Client*	Server::searchClientFd(int fd) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->getFd() == fd)
			return _clients[i];
	}
	return NULL;
}

Server::Server(const int port, const char* password) : _port(port), _password(password), _clients(0, 0) {
	_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocketFd < 0) {
		throw std::runtime_error("Error creating socket");
	}
	Server::initServer();
}

void	Server::initServer(void) {
	if (fcntl(_serverSocketFd, F_SETFL, O_NONBLOCK) < 0) {
		throw std::runtime_error("Error setting socket to non-blocking mode");
	}

	struct sockaddr_in socketAdress;
	memset(&socketAdress, 0, sizeof(socketAdress));
	socketAdress.sin_family = AF_INET;
	socketAdress.sin_port = htons(_port);
	socketAdress.sin_addr.s_addr = htonl(INADDR_ANY);

	int value = 1;
	if (setsockopt(_serverSocketFd, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value)) == -1)
		throw std::runtime_error("setsockopt(fd, SOL_SOCKET, ...) returned Error");
	if (bind(_serverSocketFd, (struct sockaddr*)&socketAdress, sizeof(socketAdress)) < 0) {
		throw std::runtime_error("Bind failed");
	}
	if (listen(_serverSocketFd, 128) < 0) {
		throw std::runtime_error("Listening on port failed");
	}
	signal(SIGINT, shutdown);
}

void	Server::run(void) {
	while (online) {
		if (controlPolls() == false)
			continue ;
		for (size_t i = 0; i < _pollFds.size(); i++) {
			if (_pollFds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				closeConnection(i);
				i--;
				continue ;
			}
			if (_pollFds[i].revents & POLLIN) {
				receive(i);
			}
			if (_pollFds[i].revents & POLLOUT) {
				sendToSocket(i);
			}
		}
		removeDisconnectedClients();
	}
}
