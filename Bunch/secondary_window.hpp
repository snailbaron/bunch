#ifndef _SECONDARY_WINDOW_HPP_
#define _SECONDARY_WINDOW_HPP_

#include "base_window.hpp"

class SecondaryWindow : public BaseWindow<SecondaryWindow>
{
    public:
        SecondaryWindow() : BaseWindow<SecondaryWindow>() {}
        ~SecondaryWindow() {}

        const wchar_t * GetWindowClassName() const { return L"Secondary Window Class"; }
        LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam) { return DefWindowProc(m_hwnd, msg, wparam, lparam); }

    private:
        SecondaryWindow(const SecondaryWindow &sw);
        SecondaryWindow & operator=(const SecondaryWindow &sw);
};

#endif