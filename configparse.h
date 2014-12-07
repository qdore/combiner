#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H
#include <vector>
#include <tuple>
#include <string>
#include <exception>

typedef std::tuple<std::string, std::string, std::string, std::string> encry_pass_host_port;

class ConfigParse
{
public:
    ConfigParse();
    std::vector<encry_pass_host_port>* operator()(std::string file);
};

class ConfigParseEx:public std::exception
{
public:
    std::string message;
    ConfigParseEx(std::string msg):message(msg){}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

#endif // CONFIGPARSE_H
