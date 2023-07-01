#ifndef SERVER_HPP
# define SERVER_HPP

#include "headers.hpp"

class Server {
	const int				_port;
	const char*				_password;
	int						_serverSocketFd;
	std::vector<pollfd>		_pollFds;
	std::vector<Client*>	_clients;
	std::vector<int>		_disconnectedClients;
	std::vector<Channel*>	_channels;

	void		initServer(void);
	void		addSocketToPoll(int socketFd, short events);
	bool		controlPolls(void);
	void		closeConnection(int index);
	void		receive(int index);
	void		removeDisconnectedClients(void);
	void		sendToSocket(int index);
	Client*		searchClientFd(int fd);
	void		executeCommand(Command& cmd, Client& client);
	Channel*	searchChannelName(std::string name);


	// Commands
	void	authenticate(Command& cmd, Client& client);
	void	makeAdmin(Command& cmd, Client& client);

	void	setNick(Command& cmd, Client& client);
	void	setUser(Command& cmd, Client& client);
	void	setMode(Command& cmd, Client& client);
	void	setTopic(Command& cmd, Client& client);

	void	sendPing(Command& cmd, Client& client);
	void	sendMessage(Command& cmd, Client& client);
	void	sendInvite(Command& cmd, Client& client);

	void	kickUser(Command& cmd, Client& client);
	void	joinChannel(Command& cmd, Client& client);
	void	leaveChannel(Command& cmd, Client& client);
	void	leaveServer(Command& cmd, Client& client);

	Channel getChanel(std::string chanel);

public:
	Server();
	Server(const int port, const char* password);
	~Server();

	bool getPassword();

	void	run(void);
};

#endif 