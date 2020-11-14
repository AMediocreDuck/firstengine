#include "fegraphics/Exception.h"


namespace fegraphics
{

	Exception::Exception(const std::string& message)
	{
		this->message = message;
	}

	Exception::~Exception() throw() { }

	const char* Exception::what() const throw()
	{
		return message.c_str();
	}
}