#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"

class Channel {
	bool						_inviteOnlyMode;
	bool						_topicMode;
	bool						_channelKeyMode;
	bool						_userLimitMode;

	std::string					_password;
	std::string					_name;
	std::string					_topic;
	std::string					_modes;
	std::vector<Client*>		_invitedClients;
	std::vector<Client*>		_connectedClients;
	std::vector<std::string>	_channelOperators;
	int							_userLimit;

public:
	Channel() {}
	Channel(Client& client, std::string channelName);
	~Channel() {}

	void		broadcast(std::string const& message);

	std::string	getChName(void) const { return _name; }
	bool		getTopicMode(void) const { return _topicMode; }
	bool		getKeyMode(void) const { return _channelKeyMode; }
	bool		getInviteMode(void) const { return _inviteOnlyMode; }
	bool		getUserLimitMode(void) const { return _userLimitMode; }
	std::string	getTopic(void) const { return _topic; }
	std::string	getModeStr(void) const { return _modes; }

	void		setInviteOnly(void) { _inviteOnlyMode == false ? _inviteOnlyMode = true : _inviteOnlyMode = false; }
	void		setTopicRestrictions(void) { _topicMode == false ? _topicMode = true : _topicMode = false; }
	void		setPasswordMode(void) { _channelKeyMode == false ? _channelKeyMode = true : _channelKeyMode = false; }
	void		setUserLimitMode(void) { _userLimitMode == false ? _userLimitMode = true : _userLimitMode = false; }
	void		setUserLimit(int userLimit) { _userLimit = userLimit; }
	void		setPassword(std::string const& password) { _password = password; }

	void		setTopic(std::string const& topic) { _topic = topic; }

	bool		isInvited(Client& client);
	bool		isChannelOperator(std::string const& nick);

	void		addToOperators(std::string const& nick);
	void		removeOperator(std::string const& nick);

	bool		addToChannel(Client& client);
	Client*		searchClient(Client& client);
	Client*		searchClientByNick(std::string& nick);
	void		removeFromChannel(Client& client);
};

#endif