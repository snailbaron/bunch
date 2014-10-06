#include <Windows.h>
#include <iostream>
#include <algorithm>
#include "config_reader.hpp"
#include "exceptions.hpp"
#include <gl/GL.h>
#include "wglext.h"
#include "functions.hpp"
#include "console.hpp"
#include "window.hpp"

void Run()
{
    


    while (true) 
    {
    }
}

DWORD WINAPI RunInThread(LPVOID data)
{
    HWND *mainWindowHandle = (HWND *) data;
    Run();
    PostMessage(*mainWindowHandle, WM_CLOSE, 0, 0);
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
    // Create a console, and redirect std streams there
    Console *console = new Console();
    Console::GetSingleton().RedirectStdHere();

    try
    {
        Window *dummyWindow = new Window(L"Dummy Window Class", L"Dummy Window");
        dummyWindow->SetSimpleGlContext();
        LoadGlFunctions();
        delete dummyWindow;

        Window *mainWindow = new Window(L"Main Window Class", L"Main Window", true);
        mainWindow->SetProperGlContext();

        DWORD threadId;
        HWND mainWindowHandle = mainWindow->GetHwnd();
        HANDLE threadHandle = CreateThread(
            NULL,
            0,
            RunInThread,
            &mainWindowHandle,
            0,
            &threadId
        );
        if (!threadHandle)
            throw WindowsException("CreateThread");

        BOOL ret;
        MSG msg;
        while ((ret = GetMessage(&msg, NULL, 0, 0)))
        {
            if (ret == -1)
                throw WindowsException("GetMessage");

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }


        delete mainWindow;

    }
    catch (WindowsException &wex)
    {
        std::cout << wex;

        std::cin.get();
    }


    delete console;

    //std::cin.get();

    return 0;
}