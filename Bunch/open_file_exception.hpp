#ifndef _OPEN_FILE_EXCEPTION_
#define _OPEN_FILE_EXCEPTION_

#include <string>
#include "exception.hpp"

class OpenFileException : public Exception
{
    public:
        OpenFileException(const std::string &filePath) : Exception(), m_filePath(filePath) {}
        OpenFileException(const OpenFileException &ex) : Exception(ex), m_filePath(ex.m_filePath) {}
        virtual ~OpenFileException() {}
        
        virtual std::ostream & Report(std::ostream &os) const {
            os << "Failed to open file: '" << m_filePath << "'" << std::endl;
            return os;
        }

    private:
        std::string m_filePath;
};

#endif