#pragma once
#include <stdexcept>
#include <string>

namespace ce
{
	class CustomError : public std::exception
	{
		std::string errorMsg;
	public:
		explicit CustomError(){}

		explicit CustomError(const std::string& errorMsg){
			this->errorMsg = errorMsg;
		}

		virtual ~CustomError() throw (){}

		virtual const char* what() const throw (){
			return errorMsg.c_str();
		}
	};
}