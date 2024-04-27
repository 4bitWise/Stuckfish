#pragma once

#include <string>
#include <exception>

#define EXCEPTION(ExceptionName)                                        \
    class ExceptionName : public std::exception                         \
    {                                                                   \
        public:                                                         \
            ExceptionName(const std::string& message)                   \
                : _message(message) {}                                  \
                                                                        \
            const char *what() const noexcept                           \
            {                                                           \
                return _message.c_str();                                \
            }                                                           \
                                                                        \
        protected:                                                      \
            std::string _message;                                       \
    };

class Error
{
public:
    EXCEPTION(EmptyInputField);
    EXCEPTION(UsernameNotFound);
};
