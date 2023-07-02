#include "../inc/Server.hpp"

void	Server::authenticate(Command& cmd, Client& client) {
	if (client.getAuth() == true)
		return cmd.setBuffer(ERR_ALREADYREGISTRED());
	if (cmd.params.size() < 1)
		return cmd.setBuffer(ERR_NEEDMOREPARAMS(cmd.getCmdName()));
	if (cmd.params.size() > 1 || cmd.params[0] != _password)
		return cmd.setBuffer(ERR_PASSWDMISMATCH());
	client.setAuth();
	std::cout << "Password successfully authenticated for Client: " << client.getFd() << std::endl;
}

void	Server::setNick(Command& cmd, Client& client) {
	if (cmd.params.size() < 1 || (cmd.params.size() == 1 && cmd.params[0].empty()))
		return cmd.setBuffer(ERR_NONICKNAMEGIVEN());
	if (cmd.params[0].find_first_of("[]\\/^#_`{|}!") != std::string::npos || cmd.params[0].size() < 3 || cmd.params[0].find_first_not_of(' ') == std::string::npos)
		return cmd.setBuffer(ERR_ERRONEUSNICKNAME("User ", cmd.params[0]));
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->user.nick == cmd.params[0])
			return cmd.setBuffer(ERR_NICKNAMEINUSE(cmd.params[0]));
	}
	if (client.getRegistered() == true) // maybe add broadcast to channels
		cmd.setBuffer(RPL_NICKCHANGE(client.user.nick, cmd.params[0], client.user.username));
	else if (!client.user.username.empty()) {
		client.setRegistered();
		cmd.setBuffer(RPL_WELCOME(cmd.params[0], client.user.username));
	}
	client.user.nick = cmd.params[0];
}

void	Server::setUser(Command& cmd, Client& client) {
	if (cmd.params.size() != 3 || cmd.getTrail().empty())
		return cmd.setBuffer(ERR_NEEDMOREPARAMS(cmd.getCmdName()));
	if (client.getRegistered() == true)
		return cmd.setBuffer(ERR_ALREADYREGISTRED());
	client.user.username = cmd.getTrail();
	if (!client.user.nick.empty()) {
		client.setRegistered();
		return cmd.setBuffer(RPL_WELCOME(client.user.nick, client.user.username));
	}
}

bool	validChannelName(std::string const& name) {
	if (name.front() != '#')
		return false;
	if (name.find_first_of("\x00\x07\x0D\x0A") != std::string::npos)
		return false;
	if (name.size() < 2 || name.size() > 50)
		return false;
	return true;
}

Channel*	Server::searchChannelName(std::string& name) {
	for (size_t i = 0; i < _channels.size(); i++) {
		if (_channels[i]->getChName() == name)
			return _channels[i];
	}
	return NULL;
}

void	Server::joinChannel(Command& cmd, Client& client) {
	if (cmd.params.size() == 0)
		return cmd.setBuffer(ERR_NEEDMOREPARAMS(cmd.getCmdName()));
	if (!validChannelName(cmd.params[0]))
		return cmd.setBuffer(ERR_NOSUCHCHANNEL(client.user.nick, cmd.params[0]));
	Channel*	channel = searchChannelName(cmd.params[0]);
	if (channel == NULL) {
		channel = new Channel(client, cmd.params[0]);
		this->_channels.push_back(channel);
		channel->broadcast(RPL_JOIN(client.user.nick, client.user.username, cmd.params[0]));
		if (!channel->getTopic().empty())
			cmd.setBuffer(RPL_TOPIC(client.user.nick, cmd.params[0], channel->getTopic()));
		return ;
	}
	else if (channel->getInviteMode() == true && channel->isInvited(client) == false)
		return cmd.setBuffer(ERR_INVITEONLYCHAN(client.user.nick, channel->getChName()));
	else {
		if (channel->addToChannel(client) == true) {
			channel->broadcast(RPL_JOIN(client.user.nick, client.user.username, cmd.params[0]));
			if (!channel->getTopic().empty())
				return cmd.setBuffer(RPL_TOPIC(client.user.nick, cmd.params[0], channel->getTopic()));
		}
	}
}

void	Server::executeTopic(Command &cmd, Client &client)
{
	if (cmd.params.size() <= 0)
		return cmd.setBuffer(ERR_NEEDMOREPARAMS(cmd.getCommand()));
	Channel* ch = searchChannelName(cmd.params[0]);
	if (ch->getTopicMode() == false && ch->isChannelOperator(client.user.nick) == false)
		return cmd.setBuffer(ERR_CHANOPRIVSNEEDED(client.user.nick, cmd.params[0]));
	if (cmd.params.size() == 1) {
		if (ch == NULL)
			return (cmd.setBuffer(ERR_NOSUCHCHANNEL(client.getNick(), cmd.params[0])));
		else {
			if (ch->getTopic().empty())
				return (cmd.setBuffer(RPL_NOTOPIC(client.getNick(), ch->getChName())));
			else
				return (cmd.setBuffer(RPL_TOPIC(client.getNick(), ch->getChName(), ch->getTopic())));
		}
	}
	else if (cmd.params.size() == 2){
		ch->setTopic(cmd.params[1]);
		return cmd.setBuffer(RPL_TOPICCHANGE(client.getNick(), client.user.username, ch->getChName(), ch->getTopic()));
	}
}

void	Server::kickUser(Command &cmd, Client &client) {
	if (cmd.params.size() < 2)
		return (cmd.setBuffer(ERR_NEEDMOREPARAMS(cmd.getCommand())));
	Channel* ch = searchChannelName(cmd.params[0]);
	if (ch == NULL)
		return (cmd.setBuffer(ERR_NOSUCHCHANNEL(client.getNick(), cmd.params[0])));
	else if (ch->isChannelOperator(client.user.nick) == false)
		return (cmd.setBuffer(ERR_CHANOPRIVSNEEDED(client.user.nick, cmd.params[0])));
	Client *ClientToKick = ch->searchClientByNick(cmd.params[1]);
	if (ClientToKick == NULL)
		return ;
	ch->broadcast(RPL_KICK(client.user.nick, client.user.username, ch->getChName(), cmd.params[1], "please contact your channel operator!"));
	ch->removeFromChannel(*ClientToKick);
}

void Server::sendInvite(Command &cmd, Client &client) {
	if (cmd.params.size() < 2)
	return (cmd.setBuffer(ERR_NEEDMOREPARAMS(cmd.getCommand())))
	Channel* ch = searchChannelName(cmd.params[1]);
	if (ch == NULL)
		return (ERR_NOSUCHCHANNEL(client.getNick(), cmd.params[1]));
	if (client.isChannelOperator() == FALSE)
		return (ERR_CHANOPRIVSNEEDED(client.user.nick, cmd.params[1]));
	std::vector<std::string> it = std::find(ch->connectedClients.begin(), ch->connectedClients.end(), cmd->params[0])
	if (it == ch->connectedClients.end())
		return (ERR_NOTONCHANNEL(client.getNick(), ch->getChName()));
	ch->_invitedClients.push_back(cmd.params[0])
	return (SPL_INVITED);
}

void 	sendPrivateMessage(Command &cmd, Client &client) {
	
}

void	Server::executeCommand(Command& cmd, Client& client) {
	if (cmd == "PASS")
		return authenticate(cmd, client);
	if (cmd == "CAP")
		return ;
	if (client.getAuth() == false)
		return cmd.setBuffer(ERR_NOTREGISTERED(cmd.getCmdName()));
	if (cmd == "NICK")
		return setNick(cmd, client);
	if (cmd == "USER")
		return setUser(cmd, client);
	if (client.getRegistered() == false)
		return cmd.setBuffer(ERR_NOTREGISTERED(cmd.getCmdName()));
	if (cmd == "JOIN")
		return joinChannel(cmd, client);
	if (cmd == "PING")
		return cmd.setBuffer(RPL_PING(client.user.nick, cmd.getCmdName()));
	if (cmd == "TOPIC")
		return executeTopic(cmd, client);
	// if (cmd == "MODE")
	// 	return setMode(cmd, client);
	// if (cmd == "PRIVMSG")
	// 	return sendMessage(cmd, client);
	if (cmd == "INVITE")
		return sendInvite(cmd, client);
	if (cmd == "KICK")
		return kickUser(cmd, client);
	// if (cmd == "OPER")
	// 	return makeAdmin(cmd, client);
	// if (cmd == "PART")
	// 	return leaveChannel(cmd, client);
	// if (cmd == "QUIT")
	// 	return leaveServer(cmd, client);
	return cmd.setBuffer(ERR_UNKNOWNCOMMAND(client.user.nick, cmd.getCmdName()));
}