#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <queue>
#include <unistd.h>
#include "Command.hpp"

class Client {
	int			_fd;
	bool		_authenticated;
	bool		_registered;
	bool		_admin;

public:

	struct userData {
		std::string			nick;
		std::string 		username;
		std::vector<int>	channels;

		userData() : nick(""), username("") {}
	} user;

	~Client() { if (_fd != -1) close(_fd); _fd = -1; }
	Client() : _fd(-2), _authenticated(0), user() {}
	Client(int fd) : _fd(fd), _authenticated(0), user() {}


	std::string			buffer;
	std::queue<Command>	commands;

	void			setFd(int fd) { _fd = fd; }
	void			setAuth(void) { _authenticated = 1; }
	void			setRegistered(void) { _registered = 1; }
	void			setAdmin(void) { _admin = 1; }

	int				getFd() const { return _fd; }
	bool			getAdmin() const { return _admin; }
	bool			getAuth() const { return _authenticated; }
	std::string		getNick(void) const {return user.nick;}
	bool			getRegistered() const { return _registered; }
	std::string&	getBuffer(void) { return buffer; }

	bool			operator== (const int& fd) const { return _fd == fd; }
};


#endif