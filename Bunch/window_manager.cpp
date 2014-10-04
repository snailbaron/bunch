#include "window_manager.hpp"
#include "exceptions.hpp"
#include <algorithm>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WindowMgr::Init()
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"Main Window Class";
    wc.hIconSm = 0;
    if (!RegisterClassEx(&wc))
        throw WindowsException("RegisterClassEx");
}

Window * WindowMgr::CreateNewWindow()
{
    Window *newWindow = new Window();
    m_presentWindows.push_back(newWindow);
    return newWindow;
}

void WindowMgr::RemoveWindow(Window *wnd)
{
    auto it = m_presentWindows.begin();
    for ( ; it != m_presentWindows.end(); it++)
        if ((*it) == wnd)
            break;

    if (it == m_presentWindows.end())
        throw WrongArgumentException("WindowMgr::RemoveWindow", 1, "wnd");

    m_presentWindows.erase(it);
    delete wnd;
}