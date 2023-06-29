#include "../inc/Server.hpp"

void	Server::addSocketToPoll(int	socketFd, short events) {
	pollfd	pollFd;
	pollFd.fd = socketFd;
	pollFd.events = events;
	_pollFds.push_back(pollFd);
}

bool	Server::controlPolls(void) {
	_pollFds.clear();
	addSocketToPoll(_serverSocketFd, POLLIN);
	for (size_t i = 0; i < _clients.size(); i++) {
		addSocketToPoll(_clients[i], POLLIN | POLLOUT);
	}
	if (poll(&_pollFds[0], _pollFds.size(), -1) == -1) {
		if (errno == EINTR) {
			return false;
		}
		throw std::runtime_error("Error in poll()");
	}
	return true;
}

void	Server::closeConnection(int index) {
		int clientFd = _pollFds[index].fd;
		close(clientFd);
		_pollFds.erase(_pollFds.begin() + index);
		std::cout << "Client disconnected: " << clientFd << std::endl;
		_disconnectedClients.push_back(clientFd);
}

void	Server::removeDisconnectedClients(void) {
	for (size_t i = 0; i < _disconnectedClients.size(); i++) {
		int clientFd = _disconnectedClients[i];
		close(clientFd);
		std::vector<int>::iterator it = std::find(_clients.begin(), _clients.end(), clientFd);
        if (it != _clients.end()) {
            _clients.erase(std::remove(_clients.begin(), _clients.end(), clientFd), _clients.end());
        }
	}
	_disconnectedClients.clear();
}

std::string	Server::readBuffer(ssize_t& bytesRead, const int& clientFd) {
	std::string	receivedData;
	char buffer[2048];

	do {
		memset(buffer, 0, sizeof(buffer));
		bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
		if (bytesRead > 0) {
			buffer[bytesRead] = '\0';
			receivedData += buffer;
		}
		else if (bytesRead == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
			bytesRead = 1;
	} while (bytesRead > 0 && receivedData.find("\r\n") == std::string::npos);
	return receivedData;
}

void	Server::receive(int index) {
	if (_pollFds[index].fd == _serverSocketFd) {
		int clientFd = accept(_serverSocketFd, NULL, NULL);
		if (clientFd == -1)
			std::cerr << "Error acception connection: " << strerror(errno) << std::endl;
		else {
			_clients.push_back(clientFd);
			std::cout << "New client connected: " << clientFd << std::endl;
		}
	}
	else {
		int clientFd = _pollFds[index].fd;
		ssize_t bytesRead = 0;
		std::string buffer = readBuffer(bytesRead, clientFd);
		if (bytesRead > 0) {
			Command	newCmd(buffer);
		}
		else if (bytesRead == 0) {
			std::cout << "Client disconnected: " << clientFd << std::endl;
			_disconnectedClients.push_back(clientFd);
		}
		else {
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
		}
	}
}

// void	Server::sendMessage(std::string msg, int fd) {
// 	ssize_t	bytesSent = send(fd, msg.c_str(), msg.size(), 0);
// 	if (bytesSent > 0) {
// 		std::cout << "Message sent to client: " << fd << std::endl;
// 	}
// 	else if (bytesSent == 0) {
// 		std::cout << "Client disconnected: " << fd << std::endl;
// 		_disconnectedClients.push_back(fd);
// 	}
// 	else {
// 		std::cerr << "Error sending data to client: " << strerror(errno) << std::endl;
// 	}
// }

void	Server::sendToSocket(int index) {
	if (_pollFds[index].fd != _serverSocketFd) {
	}
}