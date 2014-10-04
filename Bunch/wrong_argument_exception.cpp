#include "wrong_argument_exception.hpp"

WrongArgumentException::WrongArgumentException(const std::string &funcName, int argNumber, const std::string &argName) :
    Exception(),
    m_funcName(funcName),
    m_argNumber(argNumber),
    m_argName(argName)
{
}

WrongArgumentException::WrongArgumentException(const WrongArgumentException &e) :
    Exception(e),
    m_funcName(e.m_funcName),
    m_argNumber(e.m_argNumber),
    m_argName(e.m_argName)
{
}

WrongArgumentException::~WrongArgumentException()
{
}

std::ostream & WrongArgumentException::Report(std::ostream &os) const
{
    os << "Wrong argument: " << m_funcName << "[" << m_argNumber << "](" << m_argName << ")" << std::endl;
    return os;
}
