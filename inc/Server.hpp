#ifndef SERVER_HPP
# define SERVER_HPP

#include "headers.hpp"

class Server {
	const int			_port;
	const char*			_password;
	int					_serverSocketFd;
	std::vector<pollfd>	_pollFds;
	std::queue<Command>	_commands;
	std::vector<Client>	_clients;
	std::vector<int>	_disconnectedClients;

	void		initServer(void);
	void		addSocketToPoll(int socketFd, short events);
	bool		controlPolls(void);
	void		closeConnection(int index);
	void		receive(int index);
	void		removeDisconnectedClients(void);
	void		sendToSocket(int index);
	std::string	readBuffer(ssize_t& bytesRead, const int& clientFd);
	Client&		searchClientFd(int fd);
public:
	Server();
	Server(const int port, const char* password);
	~Server();

	void	run(void);
};

#endif 