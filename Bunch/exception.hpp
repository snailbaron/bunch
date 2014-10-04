#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <ostream>

class Exception
{
    public:
        Exception() {}
        Exception(const Exception &ex) {}
        virtual ~Exception() {}

        friend std::ostream & operator<<(std::ostream &os, const Exception &ex) { return ex.Report(os); }

    protected:
        virtual std::ostream & Report(std::ostream &os) const = 0;
};


#endif