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
	std::vector<std::string>	_invitedClients;
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
	std::string	getPassword(void) const { return _password; }
	size_t		getAmountUsers(void) const { return _connectedClients.size(); }
	int			getUserlimit(void) const { return _userLimit; }

	void		appendToMode(char c) { _modes += c; }
	void		eraseFromMode(size_t i) { _modes.erase(i, 1); }

	void		setInviteOnly(bool b) { _inviteOnlyMode = b; }
	void		setTopicRestrictions(bool b) { _topicMode = b; }
	void		setPasswordMode(bool b) { _channelKeyMode = b; }
	void		setUserLimitMode(bool b) { _userLimitMode = b; }
	void		setUserLimit(int userLimit) { _userLimit = userLimit; }
	void		setPassword(std::string const& password) { _password = password; }

	void		setTopic(std::string const& topic) { _topic = topic; }

	bool		isInvited(Client& client);
	bool		isChannelOperator(std::string const& nick);

	void		addToInvites(std::string const& nick);
	void		addToOperators(std::string const& nick);
	void		removeOperator(std::string const& nick);
	void		removeInvite(std::string const& nick);


	bool		addToChannel(Client& client);
	Client*		searchClient(Client& client);
	Client*		searchClientByNick(std::string const& nick);
	void		removeFromChannel(Client& client);
};

#endif