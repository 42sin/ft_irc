#ifndef BUFFER_HPP
# define BUFFER_HPP

#include <string>

class Buffer {
	std::string _buffer;

	Buffer();
public:
	Buffer(std::string str) : _buffer(str) {};
	~Buffer() { _buffer.clear(); };

	std::string const&	getBuffer(void) const { return _buffer; };
	size_t	size(void) const { return _buffer.size(); };
};

#endif