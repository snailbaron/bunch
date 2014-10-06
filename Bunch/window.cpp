#include <cassert>
#include "window.hpp"
#include "windows_exception.hpp"
#include "functions.hpp"

//const wchar_t * Window::WINDOW_CLASS_NAME = L"Window Class";

Window::Window(const wchar_t *windowClassName, const wchar_t *windowName, bool exitOnClose) :
    m_hwnd(NULL),
    m_hdc(NULL),
    m_hglrc(NULL),
    m_exitOnClose(exitOnClose)
{
    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = windowClassName;
    if (!RegisterClass(&wc))
        throw WindowsException("RegisterClass");

    m_hwnd = CreateWindowEx(
        0,
        windowClassName,
        windowName,
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        this
        );
    if (!m_hwnd)
        throw WindowsException("CreateWindowEx");
}

Window::~Window()
{
    if (m_hglrc)
    {
        assert(m_hdc);
        if (!wglMakeCurrent(m_hdc, NULL))
            throw WindowsException("wglMakeCurrent");
        if (!wglDeleteContext(m_hglrc))
            throw WindowsException("wglDeleteContext");
        m_hglrc = NULL;
    }

    if (m_hdc)
    {
        if (!DeleteDC(m_hdc))
            throw WindowsException("DeleteDC");
        m_hdc = NULL;
    }

    if (m_hwnd)
    {
        if (!DestroyWindow(m_hwnd))
            throw WindowsException("DestroyWindow");
        m_hwnd = NULL;
    }
}

void Window::SetSimpleGlContext()
{
    assert(m_hwnd);
    m_hdc = GetDC(m_hwnd);
    if (!m_hdc)
        throw WindowsException("GetDC");

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    if (!pixelFormat)
        throw WindowsException("ChoosePixelFormat");

    if (!SetPixelFormat(m_hdc, pixelFormat, &pfd))
        throw WindowsException("SetPixelFormat");

    m_hglrc = wglCreateContext(m_hdc);
    if (!m_hglrc)
        throw WindowsException("wglCreateContext");

    if (!wglMakeCurrent(m_hdc, m_hglrc))
        throw WindowsException("wglCreateContext");
}

void Window::SetProperGlContext()
{
    assert(m_hwnd);
    m_hdc = GetDC(m_hwnd);
    if (!m_hdc)
        throw WindowsException("GetDC");

    int attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };
    int pixelFormat;
    UINT formatCount;
    if (!wglChoosePixelFormatARB(m_hdc, attribs, nullptr, 1, &pixelFormat, &formatCount))
        throw WindowsException("wglChoosePixelFormatARB");

    PIXELFORMATDESCRIPTOR pfd;
    if (!DescribePixelFormat(m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
        throw WindowsException("DescribePixelFormat");

    if (!SetPixelFormat(m_hdc, pixelFormat, &pfd))
        throw WindowsException("SetPixelFormat");

    int createContextAttribs[] = { 0 };
    m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, createContextAttribs);
    if (!m_hglrc)
        throw WindowsException("wglCreateContextAttribsARB");

    if (!wglMakeCurrent(m_hdc, m_hglrc))
        throw WindowsException("wglMakeCurrent");
}

void Window::DropGlContext()
{
    assert(m_hglrc);
    assert(m_hdc);

    if (!wglMakeCurrent(m_hdc, NULL))
        throw WindowsException("wglMakeCurrent");
    if (wglDeleteContext(m_hglrc))
        throw WindowsException("wglDeleteContext");
    m_hglrc = NULL;

    if (!DeleteDC(m_hdc))
        throw WindowsException("DeleteDC");
    m_hdc = NULL;
}

LRESULT CALLBACK Window::HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (msg == WM_CLOSE && m_exitOnClose)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(m_hwnd, msg, wparam, lparam);
}


LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window *thisWindow = nullptr;
    if (msg == WM_CREATE)
    {
        thisWindow = (Window *) ((CREATESTRUCT *) lparam)->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) thisWindow);
        thisWindow->m_hwnd = hwnd;
    }
    else
        thisWindow = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);

    if (thisWindow)
        return thisWindow->HandleMessage(msg, wparam, lparam);
    else
        return DefWindowProc(hwnd, msg, wparam, lparam);
}