#ifndef SERVER_HPP
# define SERVER_HPP

#include "headers.hpp"


class Server {
	const int			_port;
	const char*			_password;
	int					_serverSocketFd;
	std::vector<int>	_clients;

	void	initServer(void);
public:
	Server();
	Server(const int port, const char* password);
	~Server();

	void	run(void);
};

#endif 