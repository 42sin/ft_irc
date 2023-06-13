#ifndef SERVER_HPP
# define SERVER_HPP

#include "headers.hpp"


class Server {
	const int			_port;
	const char*			_password;
	int					_serverSocketFd;
	std::vector<int>	_clients;
	std::vector<pollfd>	_pollFds;
	std::vector<int>	_disconnectedClients;

	void	initServer(void);
	void	addSocketToPoll(int socketFd, short events);
	bool	controlPolls(void);
	void	closeConnection(int index);
	void	receive(int index);
	void	removeDisconnectedClients(void);
public:
	Server();
	Server(const int port, const char* password);
	~Server();

	void	run(void);
};

#endif 