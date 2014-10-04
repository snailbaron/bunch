#ifndef _WRONG_ARGUMENT_EXCEPTION_HPP_
#define _WRONG_ARGUMENT_EXCEPTION_HPP_

#include <string>
#include "exception.hpp"

class WrongArgumentException : public Exception
{
    public:
        WrongArgumentException(const std::string &funcName, int argNumber, const std::string &argName);
        WrongArgumentException(const WrongArgumentException &e);
        virtual ~WrongArgumentException();

    protected:
        virtual std::ostream & Report(std::ostream &os) const;

    private:
        std::string m_funcName;
        int m_argNumber;
        std::string m_argName;
};

#endif