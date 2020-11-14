#ifndef FEGRAPHICS_EXCEPTION_H
#define FEGRAPHICS_EXCEPTION_H

#include <exception>
#include <string>

namespace fegraphics
{

	struct Exception : public std::exception
	{
		Exception(const std::string& message);
		virtual ~Exception() throw();
		virtual const char* what() const throw();

	private:
		std::string message;

	};
}
#endif
