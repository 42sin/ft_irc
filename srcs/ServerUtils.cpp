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
		addSocketToPoll(_clients[i].getFd(), POLLIN | POLLOUT);
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
		std::vector<Client>::iterator it = std::find(_clients.begin(), _clients.end(), clientFd);
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
			std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
		else {
			_clients.push_back(Client(clientFd));
			std::cout << "New client connected: " << clientFd << std::endl;
		}
	}
	else {
		int clientFd = _pollFds[index].fd;
		Client& currClient = searchClientFd(clientFd);

		ssize_t bytesRead = 0;
		char	buffer[2048];
		do {
			memset(buffer, 0, sizeof(buffer));
			bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
			if (bytesRead > 0)
				currClient.buffer += std::string(buffer, bytesRead);
		} while (bytesRead > 0);
		if (bytesRead == 0) {
			std::cout << "Client disconnected: " << clientFd << std::endl;
			_disconnectedClients.push_back(clientFd);
		}
		else if (bytesRead < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
		}
		size_t pos = 0;
		while ((pos = currClient.buffer.find("\r\n")) != std::string::npos) {
			std::string	message = currClient.buffer.substr(0, pos);
			_commands.push(Command(message, clientFd));
			currClient.buffer = currClient.buffer.substr(pos + 2);
		}
	}
}

void	Server::sendToSocket(int index) {
	if (_pollFds[index].fd != _serverSocketFd) {
		if (!_commands.empty()) {
			Command	cmd = _commands.front();
			_commands.pop();
			if (!cmd.getBuffer().empty()) {
				send(cmd.getFd(), cmd.getBuffer().data(), cmd.getBuffer().size(), 0);
			}
		}
	}
}