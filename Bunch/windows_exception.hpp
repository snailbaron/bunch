#ifndef _WINDOWS_EXCEPTION_HPP_
#define _WINDOWS_EXCEPTION_HPP_

#include <string>
#include <Windows.h>
#include "exception.hpp"

class WindowsException : public Exception
{
    public:
        WindowsException(const std::string funcName);
        WindowsException(const WindowsException &wex);
        virtual ~WindowsException();

        const std::string & GetFuncName() const { return m_funcName; }
        const DWORD & GetErrCode() const { return m_errCode; }

    protected:
        virtual std::ostream & Report(std::ostream &os) const;

    private:
        std::string m_funcName;
        DWORD m_errCode;
};

#endif