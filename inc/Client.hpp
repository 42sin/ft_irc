#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
	int			_fd;

public:
	std::string	buffer;
	Client() {}
	Client(int fd) : _fd(fd) {}
	
	void			setFd(int fd) { _fd = fd; }
	int				getFd() const { return _fd; }
	std::string&	getBuffer() { return buffer; }
	bool			operator== (const int& fd) const { return _fd == fd; }
};


#endif