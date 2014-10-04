#ifndef _CONFIG_READER_HPP_
#define _CONFIG_READER_HPP_

#include "config.hpp"

class ConfigReader
{
    public:
        ConfigReader() {}
        ~ConfigReader() {}

        static Config * ReadFile(const std::string &fileName);

    private:
        ConfigReader(const ConfigReader &cr);
        ConfigReader & operator=(const ConfigReader &cr);
};

#endif