#ifndef RTYPEEXCEPTION_H_
# define RTYPEEXCEPTION_H

# include													<iostream>
# include													<sstream>
# include													<vector>

class RTypeException :										public std::exception
{
public:
	RTypeException(const std::string &message)				throw();
	RTypeException(const std::string &message, int line)	throw();
	virtual ~RTypeException()								throw ();
	const char												*what() const throw();

protected:
	std::string												_message;
};

#endif /* !RTYPEEXCEPTION_H_ */