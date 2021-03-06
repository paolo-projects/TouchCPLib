#pragma once

/**
 * @file TouchCPException.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <exception>
#include <string>
#include <stdarg.h>

class TouchCPException : public std::exception
{
public:
	TouchCPException(const std::string &message) : msg(message){};
	TouchCPException(const char *message, ...)
	{
		char msg_buf[300];
		va_list args;
		va_start(args, message);
		vsnprintf(msg_buf, 300, message, args);
		va_end(args);
		msg = std::string(msg_buf);
	};
	const char *what() const noexcept override
	{
		return msg.c_str();
	}

private:
	std::string msg;
};
