#include "../inc/Channel.hpp"


Client*		Channel::searchClientByNick(std::string const& nick) {
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
		if (client.getNick() == _invitedClients[i])
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
		if (_connectedClients[i] == &client)
			return false;
	}
	_connectedClients.push_back(&client);
	return true;
}

void	Channel::addToInvites(std::string const& nick) {
	_invitedClients.push_back(nick);
}

void		Channel::removeInvite(std::string const& nick) {
	std::vector<std::string>::iterator it = std::find(_invitedClients.begin(), _invitedClients.end(), nick);
	if (it != _invitedClients.end())
		_invitedClients.erase(it);
}

void	Channel::removeFromChannel(Client& client) {
	if (isChannelOperator(client.getNick())) {
		removeOperator(client.getNick());
	}
	if (isInvited(client)) {
		removeInvite(client.getNick());
	}
	for (size_t i = 0; i < _connectedClients.size(); i++) {
		if (_connectedClients[i] == &client) {
			_connectedClients.erase(_connectedClients.begin() + i);
			break ;
		}
	}
}
