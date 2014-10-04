#ifndef _WINDOW_MANAGER_HPP_
#define _WINDOW_MANAGER_HPP_

#include <vector>
#include "window.hpp"
#include "singleton.hpp"

class WindowMgr : public Singleton<WindowMgr>
{
    public:
        WindowMgr() : Singleton() {}
        ~WindowMgr() {}

        void Init();
        Window * CreateNewWindow();
        void RemoveWindow(Window *wnd);

    private:
        std::vector<Window *> m_presentWindows;
        
    private:
        WindowMgr(const WindowMgr &wm);
        WindowMgr & operator=(const WindowMgr &wm);
};

#endif