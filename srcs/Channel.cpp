#include "../inc/Channel.hpp"


Client*		Channel::searchClientByNick(std::string& nick) {
	for (size_t i = 0; i < _connectedClients.size(); i++) {
		if (_connectedClients[i]->getNick() == nick)
			return _connectedClients[i];
	}
	return NULL;
}

Client*		Channel::searchClient(Client &client) {
	for (size_t i = 0; i < _connectedClients.size(); i++) {
		if (_connectedClients[i] == &client)
			return _connectedClients[i];
	}
	return NULL;
}

void		Channel::addToOperators(std::string const& nick) {
	_channelOperators.push_back(nick);
}

void		Channel::removeOperator(std::string const& nick) {
	std::vector<std::string>::iterator it = std::find(_channelOperators.begin(), _channelOperators.end(), nick);
	if (it != _channelOperators.end())
		_channelOperators.erase(it);
}

bool	Channel::isChannelOperator(std::string const& nick) {
	for (size_t i = 0; i < _channelOperators.size(); i++) {
		if (nick == _channelOperators[i])
			return true;
	}
	return false;
}

bool	Channel::isInvited(Client& client) {
	for (size_t i = 0; i < _invitedClients.size(); i++) {
		if (&client == _invitedClients[i])
			return true;
	}
	return false;
}

void	Channel::broadcast(std::string const& message) {
	for (size_t i = 0; i < _connectedClients.size(); i++) {
		Command newMessage;
		newMessage.setClientFd(_connectedClients[i]->getFd());
		newMessage.setBuffer(message);
		_connectedClients[i]->commands.push(newMessage);
	}
}

Channel::Channel(Client& client, std::string channelName) : _topicMode(1), _modes("t") {
	this->_name = channelName;
	_connectedClients.push_back(&client);
	_channelOperators.push_back(client.user.nick);
}

bool	Channel::addToChannel(Client& client) {
	for (size_t i = 0; i < _connectedClients.size(); i++) {
		std::cout << "Connected client: " << _connectedClients[i]->getFd() << std::endl;
		if (_connectedClients[i] == &client)
			return false;
	}
	std::cout << "pushing client on connectedClients" << std::endl;
	_connectedClients.push_back(&client);
	return true;
}

void	Channel::removeFromChannel(Client& client) {
	for (size_t i = 0; i < _connectedClients.size(); i++) {
		if (_connectedClients[i] == &client) {
			_connectedClients.erase(_connectedClients.begin() + i);
			break ;
		}
	}
}
