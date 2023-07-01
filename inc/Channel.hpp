#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"

class Channel {
	bool						_inviteOnlyMode;
	bool						_topicMode;
	bool						_channelKeyMode;

	std::string					_name;
	std::string					_topic;
	std::vector<Client*>		_invitedClients;
	std::vector<Client*>		_connectedClients;
	std::vector<std::string>	_channelOperators;
	//unsigned int				_userLimit;

public:
	Channel() {}
	Channel(Client& client, std::string channelName);
	~Channel() {}

	void		broadcast(std::string const& message);

	std::string	getChName(void) const { return _name; }
	bool		getTopicMode(void) const { return _topicMode; }
	bool		getKeyMode(void) const { return _channelKeyMode; }
	bool		getInviteMode(void) const { return _inviteOnlyMode; }
	std::string	getTopic(void) const { return _topic; }

	bool		isInvited(Client& client);
	bool		isChannelOperator(std::string nick);

	bool		addToChannel(Client& client);
	void		removeFromChannel(Client& client);
};

#endif