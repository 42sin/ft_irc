#include "../inc/Server.hpp"

Server::Server() :_port(0), _password(NULL), _serverSocketFd(0), _clients(0, 0) {
}

Server::~Server() {
	for (size_t i = 0; i < _clients.size(); i++) {
		std::cout << "Closing client fd: " << _clients[i] << std::endl;
		if (_clients[i] > 0) {
			close(_clients[i]);
			_clients[i] = -1;
		}
	}
	close(_serverSocketFd);
}

Server::Server(const int port, const char* password) : _port(port), _password(password), _clients(0, 0){
	_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocketFd < 0) {
		throw std::runtime_error("Error creating socket");
	}
	Server::initServer();
}

bool online = true;

void	shutdown(int sig) {
	(void)sig;
	online = false;
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
		std::vector<pollfd> pollFds;
	
		pollfd	serverPollFd;
		serverPollFd.fd = _serverSocketFd;
		serverPollFd.events = POLLIN;
		pollFds.push_back(serverPollFd);

		for (size_t i = 0; i < _clients.size(); i++) {
			pollfd clientPollFd;
			clientPollFd.fd = _clients[i];
			clientPollFd.events = POLLIN;
			pollFds.push_back(clientPollFd);
		}
	
		if (poll(&pollFds[0], pollFds.size(), -1) == -1) {
			if (errno == EINTR) {
				continue ;
			}
			throw std::runtime_error("Error in poll()");
		}

		std::vector<int> clientsToRemove;

		for (size_t i = 0; i < pollFds.size(); i++) {
			if (pollFds[i].revents & POLLIN) {
				if (pollFds[i].fd == _serverSocketFd) {
					int clientFd = accept(_serverSocketFd, NULL, NULL);
					_clients.push_back(clientFd);
					std::cout << "New client connected: " << clientFd << std::endl;
				}
				else {
					int clientFd = pollFds[i].fd;
					char buffer[1028];
					memset(buffer, 0, sizeof(buffer));
					ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
					if (bytesRead > 0) {
						std::cout << "received from client " << clientFd << ": " << buffer;
					}
					else if (bytesRead == 0) {
						// Verbindung vom Client getrennt
						std::cout << "Client disconnected: " << clientFd << std::endl;
						// Markiere den Client zum Entfernen
						clientsToRemove.push_back(clientFd);
					}
					else {
						std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
					}
				}
			}
		}

		// Entferne die markierten Clients
		for (size_t i = 0; i < clientsToRemove.size(); i++) {
			int clientFd = clientsToRemove[i];
			close(clientFd);
			std::vector<int>::iterator it = std::find(_clients.begin(), _clients.end(), clientFd);
			if (it != _clients.end()) {
				_clients.erase(it);
			}
		}
	(void)_password;
	}
}
