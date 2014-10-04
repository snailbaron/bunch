#ifndef _BASE_WINDOW_HPP_
#define _BASE_WINDOW_HPP_

#include <Windows.h>
#include <cassert>

template <class T> class BaseWindow
{
    public:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
        {
            T *pThis = nullptr;

            if (msg == WM_CREATE)
            {
                CREATESTRUCT *pCreate = (CREATESTRUCT *) lparam;
                pThis = (T *) pCreate->lpCreateParams;
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pThis);

                pThis->m_hwnd = hwnd;
            }
            else
            {
                pThis = (T *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            }

            if (pThis)
                return pThis->HandleMessage(msg, wparam, lparam);
            else
                return DefWindowProc(hwnd, msg, wparam, lparam);
        }

        BaseWindow() : m_hwnd(nullptr) {}
        ~BaseWindow() { assert(m_hwnd); m_hwnd = nullptr; }

        void Init(const wchar_t *windowName)
        {
            WNDCLASS wc = {};
            wc.style = CS_OWNDC;
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = GetWindowClassName();
            if (!RegisterClass(&wc))
                throw WindowsException("RegisterClass");

            m_hwnd = CreateWindowEx(
                0,
                GetWindowClassName(),
                windowName,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                this
            );
            if (!m_hwnd)
                throw WindowsException("CreateWindowEx");
        }

        void Show(int nCmdShow)
        {
            ShowWindow(m_hwnd, nCmdShow);
        }

    protected:
        virtual const wchar_t * GetWindowClassName() const = 0;
        virtual LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam) = 0;
        HWND m_hwnd;

    private:
        BaseWindow(const BaseWindow &bw);
        BaseWindow & operator=(const BaseWindow &bw);
};

#endif