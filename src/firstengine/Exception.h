#ifndef FIRSTENGINE_EXCEPTION_H
#define FIRSTENGINE_EXCEPTION_H

#include <exception>
#include <string>

namespace firstengine
{
	/********************************************//**
	* \brief Error Handling
	***********************************************/
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