#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <string>
#include <map>
#include <vector>

class Config
{
    public:
        Config() {}
        ~Config() {}

        void SetProperty(std::string name, std::string value) {
            m_properties[name] = value;
        }

        std::string GetProperty(std::string name) {
            return m_properties[name];
        }

        std::vector<std::string> GetPropNames() {
            std::vector<std::string> keyNames;
            for (auto it = m_properties.begin(); it != m_properties.end(); it++)
                keyNames.push_back(it->first);
            return keyNames;
        }


    private:
        std::map<std::string, std::string> m_properties;

    private:
        Config(const Config &config);
        Config & operator=(const Config &config);
};

#endif