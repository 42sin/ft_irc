#include "../inc/Responses.hpp"

std::string ERR_NEEDMOREPARAMS(const std::string& command) 
{ 
	std::cout << command << ": more Parameters needed to execute command: " << command << "!" << "\n";
	return std::string(":") + "worst.chat" + " 461 " + command + " :Not enough parameters\r\n";
}

std::string ERR_PASSWDMISMATCH()
{ 
	std::cout << "User provided invalid password!" << "\n";
	return std::string(":") + "worst.chat" + " 464 " + "PASS" + " :Password incorrect\r\n";
}

std::string ERR_ALREADYREGISTRED() 
{ 
	std::cout << "User tried to re-authenticate!" << "\n";
	return std::string(":") + "worst.chat" + " 462 " ":Already registered\r\n";
}

std::string ERR_NICKNAMEINUSE(const std::string& nick) 
{ 
	std::cout << "User tried claiming nickname already in use!" << "\n";
	return std::string(":") + "worst.chat" " 433 " + nick + " :Nickname is already in use\r\n"; 
}

std::string ERR_NONICKNAMEGIVEN() 
{ 
	std::cout << "User did not provide nickname!" << "\n";
	return std::string(":") + "worst.chat" + " 431 " + "NICK" + " :Nickname not given\r\n"; 
}

std::string ERR_NOTREGISTERED(const std::string& command)
{
	std::cout << "User tried executing command " << command << " but was not registered!" << "\n";
	return std::string(":") + "worst.chat" + " 451 " + ":You have not registered\r\n";
}

std::string ERR_NOSUCHCHANNEL(const std::string& nick, const std::string& channel_name)
{
	std::cout << "User tried accessing channel " << channel_name << "\n";
	return std::string(":") + "worst.chat" + " 403 " +  nick + " " + channel_name + " : No such channel\r\n";
}

std::string ERR_ERRONEUSNICKNAME(const std::string& nick, const std::string& wrong_nick)
{
	std::cout << nick << "tried using invalid nick: " << wrong_nick  << "!" << "\n";
	return std::string(":") + "worst.chat" + " 432 " + nick + " " + wrong_nick + " :Erroneous nickname\r\n";
}

std::string ERR_UNKNOWNCOMMAND(const std::string& nick, const std::string& command)
{
	std::cout << "User tried executing unknown command: " << command << "!" << "\n";
	return std::string(":") + "worst.chat" + " 421 " + nick + " " + command + " :Unknown command\r\n";
}

std::string ERR_NOSUCHNICK(const std::string& nick, const std::string channel_name)
{
	std::cout << nick << " was not found " << "\n";
	return std::string(":") + "worst.chat" " 401 " + nick + " " + channel_name + " :No such nick/channel\r\n";
}

std::string ERR_CANNOTSENDTOCHAN(const std::string& nick, const std::string& channel_name)
{
	std::cout << nick << " tried sending message to " << channel_name << " but was not registered to it!" << "\n";
	return std::string(":") + "worst.chat" +  " 404 " + nick + " " + channel_name + " :Cannot send to channel\r\n";
}

std::string ERR_CHANOPRIVSNEEDED(const std::string& nick, const std::string& channel_name)
{
	std::cout << nick << " tried executing a command for " << channel_name << " but did not have op permissions!" << "\n";
	return std::string(":") + "worst.chat" + " 482 " + nick + " " + channel_name + " :You're not channel operator \r\n";
}

std::string ERR_NOPRIVS(const std::string& nick, const std::string& command)
{
	std::cout << nick << " tried executing OP Command " << command << " but is not Operator!" << "\n";
	return std::string(":") + "worst.chat" + " 481 " + command + " :Permission Denied- You're not an IRC operator\r\n";
}

std::string ERR_UMODEUNKNOWNFLAG(const std::string& nick)
{
	std::cout << nick << " used invalid mode flags" << "\n";
	return std::string(":") + "worst.chat" + " 501 " + nick + " :Unknown MODE flags\r\n";
}

std::string ERR_USERONCHANNEL(const std::string& nick, const std::string& channel_name, const std::string& target)
{
	std::cout << nick << " inviting " << target << " to " << channel_name << " but he was already on channel!" << "\n";
	return std::string(":") + "worst.chat" + " 443 " + nick + " " + channel_name + " :Is already on channel \r\n";
}

std::string ERR_INVITEONLYCHAN(const std::string& nick, const std::string& channel_name)
{
	std::cout << nick << " tried joining " << channel_name << " but he was not invited!" << "\n";
	return std::string(":") + "worst.chat" + " 473 " + nick + " " + channel_name + " :Cannot join channel (+i) - you must be invited\r\n";
}

std::string	ERR_BADCHANNELKEY(const std::string &nick, const std::string &channel_name)
{
	std::cout << nick << " tried joining " << channel_name << " but provided the wrong key!" << "\n";
	return std::string(":") + "worst.chat" + " 475 " + nick + " " + channel_name + " :Cannot join channel (+k) - bad key\r\n";
}

std::string	ERR_CHANNELISFULL(const std::string &nick, const std::string &channel_name) {
	std::cout << nick << " tried joining " << channel_name << " but the channel is already full!" << "\n";
	return std::string(":") + "worst.chat" + " 471 " + nick + " " + channel_name + " :Cannot join channel (+l) - channel is full\r\n";
}

std::string RPL_NICKCHANGE(const std::string& old_nick, const std::string& new_nick, const std::string& user) 
{ 
	std::cout << "User changed his nickname from " << old_nick << " to " << new_nick << "!" << "\n";
	return std::string(":") + old_nick + "!" + user + "@" + "localhost" + " " + "NICK" + " :" + new_nick + "\r\n";
}

std::string RPL_CAP()
{
	std::cout << "Server-capabilities were sent to client!" << "\n";
	return std::string(":") + "worst.chat" + " CAP * LS :cap reply...\r\n"; 
}

std::string RPL_JOIN(const std::string& nick, const std::string& user, const std::string& channel_name)
{
	std::cout << nick << " joined channel " << channel_name << "!" << "\n";
	return std::string(":") + nick + "!" + user + "@" + "localhost" + " JOIN " + channel_name + " * :" + user + "\r\n";
}

std::string RPL_PING(const std::string& nick, const std::string& token)
{
	std::cout << nick << " pinged this server! " << "\n";
	return std::string(":") + "worst.chat" + " PONG " + "worst.chat" + " :" + token + "\r\n";
}

std::string RPL_PART(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string reason)
{
	std::cout << nick << " just parted channel " << channel_name + " ; " + reason + "!" << "\n";
	return std::string(":") + nick + "!" + user + "@" + "localhost" + " PART " + channel_name + " " + reason + "!" +  "\r\n";
}

std::string	RPL_PRIVMSG(const std::string& nick, const std::string& user, const std::string& target, const std::string& msg)
{
	std::cout << nick << " send message " << msg + " to " + target +  "!" << "\n";
	return std::string(":") + nick + "!" + user + "@" + "localhost" + " PRIVMSG " + target + " :" + msg + "\r\n";
}

std::string RPL_TOPICCHANGE(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& topic)
{
	std::cout << nick << " set the topic of " << channel_name << " to " << topic << "!" << "\n";
	return std::string(":") + nick + "!" + user + "@" + "localhost" + " TOPIC " + channel_name + " :" + topic + "\r\n";
}

std::string RPL_KICK(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& target, const std::string reason)
{
	std::cout << nick << " kicked " << target << " of " << channel_name << " because: " << reason << "!" << "\n";
	return std::string(":") +  nick + "!" + user + "@" + "localhost" + " KICK " + channel_name + " " + target + " :" + reason + "\r\n";
}

std::string RPL_BOT(const std::string& nick, const std::string& channel_name, const std::string& msg)
{
	std::cout << nick << " used a bot command on " << channel_name << "!" << "\n";
	return std::string(":COINFLIPBOT!BOT@worst.chat") + " NOTICE " + channel_name + " :" + msg + "\r\n";
}

std::string	RPL_INVITED(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& target)
{
	std::cout << target << " has been invited " << " to " << channel_name << " by " << nick << "!" << "\n";
	return std::string(":") + nick + "!" + user + "@" + "localhost" + " INVITE " + target + " :" + channel_name + "\r\n";
}

std::string RPL_WELCOME(const std::string& nick, const std::string user) 
{
	std::cout << "User: " << user << " succesfully registered to the server, using nick " << nick << "!" << "\n";
	return std::string(":") + "worst.chat" + " 001 " + nick + " :Welcome to the ft_irc network " + nick + "!" + user + "@" + "localhost" + "\r\n";
}

std::string RPL_CHANNELMODEIS(const std::string& nick, const std::string& channel_name, const std::string& mode)
{
	std::cout << nick << " requested " << channel_name << "'s mode: " << mode << "\n";
	return std::string(":") + "worst.chat" + " 324 " + nick + " " + channel_name + " " + mode + "\r\n";
}

std::string RPL_SETMODECHANNEL(const std::string& nick, const std::string& channel_name, const std::string& mode)
{
	std::cout << nick << " set " << channel_name << "'s mode to " << mode << "!" << "\n";
	return std::string(":") + "worst.chat" + " 324 " + nick + " " + channel_name + " " + mode + "\r\n";
}

std::string RPL_YOUREOPER(const std::string& nick, const std::string& target)
{
	std::cout << nick << " make " << target << " a server operator!" << "\n";
	return std::string(":") + "worst.chat" + " 381 " + ":You are now an IRC operator\r\n";
}

std::string	RPL_INVITING(const std::string& nick, const std::string& channel_name, const std::string& target)
{
	std::cout << nick << " invited " << target << " to " << channel_name << "!" << "\n";
	return std::string(":") + "worst.chat" + " 341 " + nick + " " + target + " " + channel_name + "\r\n";
}

std::string RPL_NOTOPIC(const std::string& nick, const std::string& channel_name)
{
	std::cout << nick << " requested the topic of " << channel_name << " but no topic was set!" << "\n";
	return std::string(":") + "worst.chat" + " 331 " + nick + " " + channel_name + " :No topic is set\r\n";
}

std::string RPL_TOPIC(const std::string& nick, const std::string& channel_name, const std::string& topic)
{
	std::cout << nick << " requested the topic of " << channel_name << ": " << topic << "!" << "\n";
	return std::string(":") + "worst.chat" + " 332 " + nick + " " + channel_name + " :" + topic + "\r\n";
}