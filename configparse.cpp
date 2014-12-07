#include "configparse.h"
#include <fstream>
#include <QDebug>
#include <iostream>

ConfigParse::ConfigParse()
{
}
std::vector<encry_pass_host_port>* ConfigParse::operator()(std::string file)
{
    std::vector<encry_pass_host_port> * n = new std::vector<encry_pass_host_port>;
    std::ifstream in(file.c_str());
    std::string tmp;
    while (in)
    {
        std::getline(in, tmp);
        if (!tmp.empty())
        {
            size_t encry = tmp.find_first_of(":", 0);
            size_t pass = tmp.find_first_of("@", encry + 1);
            size_t host = tmp.find_first_of(":", pass + 1);
            n->push_back({
                             tmp.substr(0, encry),
                             tmp.substr(encry + 1, pass - encry - 1),
                             tmp.substr(pass + 1, host - pass - 1),
                             tmp.substr(host + 1, tmp.size())
                         });
        }



    }
    return n;
}
