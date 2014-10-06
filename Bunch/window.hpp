#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <Windows.h>

class Window
{
    public:
        Window(const wchar_t *windowClassName, const wchar_t *windowName, bool exitOnClose = false);
        ~Window();

        const HWND & GetHwnd() const { return m_hwnd; }
        const HDC & GetHdc() const { return m_hdc; }
        const HGLRC & GetHglrc() const { return m_hglrc; }

        void SetSimpleGlContext();
        void SetProperGlContext();
        void DropGlContext();

    private:
        //static const wchar_t * WINDOW_CLASS_NAME;
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
        LRESULT CALLBACK HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam);

        HWND m_hwnd;
        HDC m_hdc;
        HGLRC m_hglrc;
        bool m_exitOnClose;

    private:
        Window(const Window &w);
        Window & operator=(const Window &w);
};

#endif