#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#include "singleton.hpp"

class Console : public Singleton<Console>
{
    public:
        Console();
        ~Console();

        // Redirect stdout, stderr, stdin to this console
        void RedirectStdHere();
};

#endif