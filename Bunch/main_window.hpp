#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include "base_window.hpp"

class MainWindow : public BaseWindow<MainWindow>
{
    public:
        MainWindow() : BaseWindow<MainWindow>() {}
        ~MainWindow() {}

        const wchar_t * GetWindowClassName() const { return L"Main Window Class"; }
        LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam);

    private:
        MainWindow(const MainWindow &mw);
        MainWindow & operator=(const MainWindow &mw);
};

#endif