#include				"RTypeException.h"

RTypeException::RTypeException(const std::string & message) throw() : _message(message)
{}

RTypeException::~RTypeException() throw()
{}

RTypeException::RTypeException(const std::string & message, int line) throw()
{
	std::ostringstream	ss;
	ss << line;
	this->_message = "Line " + ss.str() + ": " + message;
}

const char				*RTypeException::what() const throw ()
{
	return (this->_message.c_str());
}