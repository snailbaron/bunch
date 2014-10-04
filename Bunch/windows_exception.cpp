#include "windows_exception.hpp"

WindowsException::WindowsException(const std::string funcName) :
    Exception(),
    m_funcName(funcName)
{
    m_errCode = GetLastError();
}

WindowsException::WindowsException(const WindowsException &wex) :
    Exception(wex),
    m_funcName(wex.m_funcName),
    m_errCode(wex.m_errCode)
{
}

WindowsException::~WindowsException()
{
}

std::ostream & WindowsException::Report(std::ostream &os) const
{
    os <<
        "Windows exception occured" << std::endl <<
        "    Function: " << m_funcName << std::endl <<
        "    Error code: " << m_errCode << " (0x" << std::hex << m_errCode << ")" << std::endl;
    return os;
}
