#include <fstream>
#include <regex>
#include <iostream>
#include "config_reader.hpp"
#include "exceptions.hpp"

Config * ConfigReader::ReadFile(const std::string &fileName)
{
    Config *config = new Config();
  
    std::ifstream ifs(fileName);
    if (ifs.fail())
        throw OpenFileException(fileName);

        
    while (ifs.good())
    {
        std::string line;
        std::getline(ifs, line);

        std::smatch m;
        if (std::regex_match(line, m, std::regex("^([^#]*)#.*$")))
            line = m[1];

        if (std::regex_match(line, m, std::regex("^\\s*([^=\\s]+)\\s*=\\s*([^=\\s]*)\\s*$")))
            config->SetProperty(m[1], m[2]);
    }
    ifs.close();

    return config;
}