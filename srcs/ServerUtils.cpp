#include "../inc/Server.hpp"

void	Server::addSocketToPoll(int	socketFd, short events) {
	pollfd	pollFd;
	pollFd.fd = socketFd;
	pollFd.events = events;
	_pollFds.push_back(pollFd);
}

Client*		Server::searchServerForClient(std::string const& nick) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->getNick() == nick)
			return _clients[i];
	}
	return NULL;
}

bool	Server::controlPolls(void) {
	_pollFds.clear();
	addSocketToPoll(_serverSocketFd, POLLIN);
	for (size_t i = 0; i < _clients.size(); i++) {
		addSocketToPoll(_clients[i]->getFd(), POLLIN | POLLOUT);
	}
	if (poll(&_pollFds[0], _pollFds.size(), -1) == -1) {
		if (errno == EINTR) {
			return false;
		}
		throw std::runtime_error("Error in poll()");
	}
	return true;
}

void	newMessage(Client* receiver, std::string const& message) {
	Command newMessage;
	newMessage.setClientFd(receiver->getFd());
	newMessage.setBuffer(message);
	receiver->commands.push(newMessage);
}

void	Server::closeConnection(int index) {
		int clientFd = _pollFds[index].fd;
		close(clientFd);
		_pollFds.erase(_pollFds.begin() + index);
		std::cout << "Client disconnected" << std::endl;
		_disconnectedClients.push_back(clientFd);
}

void	Server::removeDisconnectedClients(void) {
	for (size_t i = 0; i < _channels.size(); i++) {
		for (size_t j = 0; j < _clients.size(); j++) {
			if (std::find(_disconnectedClients.begin(), _disconnectedClients.end(), _clients[j]->getFd()) != _disconnectedClients.end())
				_channels[i]->removeFromChannel(*_clients[j]);
		}
	}
	for (size_t i = 0; i < _disconnectedClients.size(); i++) {
		int clientFd = _disconnectedClients[i];
		std::vector<Client*>::iterator it = _clients.begin();
        for (; it != _clients.end(); ++it)
			if ((*it)->getFd() == clientFd)
				break ;
		if (it != _clients.end()) {
			delete *it;
			_clients.erase(it);
		}
    }
	_disconnectedClients.clear();
}

void	Server::receive(int index) {
	if (_pollFds[index].fd == _serverSocketFd) {
		int clientFd = accept(_serverSocketFd, NULL, NULL);
		if (clientFd == -1)
			std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
		else {
			_clients.push_back(new Client(clientFd));
			std::cout << "New client connected" << std::endl;
		}
	}
	else {
		int clientFd = _pollFds[index].fd;
		Client* currClient = searchClientFd(clientFd);
		if (currClient == NULL) {
			std::cerr << "Critical error: Client not found" << std::endl;
			return ;
		}
		ssize_t bytesRead = 0;
		char	buffer[2048];
		memset(buffer, 0, sizeof(buffer));
		bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
		if (bytesRead > 0) {
			currClient->buffer += std::string(buffer, bytesRead);
			size_t pos = 0;
			while ((pos = currClient->buffer.find("\r\n")) != std::string::npos) {
				std::string	message = currClient->buffer.substr(0, pos);
				if (message.length() > 512)
					std::cerr << "Error: Message exceeds max length" << std::endl;
				else {
					currClient->commands.push(Command(message, clientFd));
					executeCommand(currClient->commands.back(), *currClient);
				}
				currClient->buffer = currClient->buffer.substr(pos + 2);
			}
		}
		if (bytesRead == 0) {
			std::cout << "Client disconnected" << std::endl;
			_disconnectedClients.push_back(clientFd);
		}
		else if (bytesRead < 0) {
			std::cerr << "Error receiving data from client: " << strerror(errno) << std::endl;
		}
	}
}

void	Server::sendToSocket(int index) {
	if (_pollFds[index].fd != _serverSocketFd) {
		Client* client = searchClientFd(_pollFds[index].fd);
		if (client == NULL) {
			std::cerr << "Critical error: client not found" << std::endl;
			return ;
		}
		if (!client->commands.empty()) {
			Command cmd = client->commands.front();
			if (!cmd.getBuffer().empty()) {
				if (send(cmd.getFd(), cmd.getBuffer().data(), cmd.getBuffer().size(), 0) >= 0) {
					client->commands.pop();
				}
			}
			else
				client->commands.pop();
		}
	}


	// if (_pollFds[index].fd != _serverSocketFd) {
	// 	if (!_commands.empty()) {
	// 		Command	cmd = _commands.front();
	// 		if (cmd.getFd() == _pollFds[index].fd) {
	// 			_commands.pop();
	// 			if (!cmd.getBuffer().empty()) {
	// 				send(cmd.getFd(), cmd.getBuffer().data(), cmd.getBuffer().size(), 0);
	// 			}
	// 		}
	// 	}
	// }
}