#pragma once
#include <exception>
#include <string>
#include <stdarg.h>

class SDLException : public std::exception {
public:
    SDLException(const std::string& message) : msg(message) {};
    SDLException(const char* message, ...) {
        char msg_buf[300];
        va_list args;
        va_start(args, message);
        vsnprintf(msg_buf, 300, message, args);
        va_end(args);
        msg = std::string(msg_buf);
    };
    const char* what() const noexcept override {
        return msg.c_str();
    }
private:
    std::string msg;
};