#ifndef _BASE_WINDOW_HPP_
#define _BASE_WINDOW_HPP_

#include <Windows.h>
#include <cassert>

template <class T> class BaseWindow
{
    public:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        BaseWindow();
        ~BaseWindow();

        void Init(const wchar_t *windowName);
        void SetSimpleGlContext();
        void DropGlContext();
        void SetProperGlContext();

    protected:
        virtual const wchar_t * GetWindowClassName() const = 0;
        virtual LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam) = 0;

        HWND m_hwnd;
        HDC m_hdc;
        HGLRC m_hglrc;

    private:
        BaseWindow(const BaseWindow &bw);
        BaseWindow & operator=(const BaseWindow &bw);
};

#endif