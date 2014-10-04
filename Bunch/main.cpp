#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <algorithm>
#include "config_reader.hpp"
#include "exceptions.hpp"
#include <gl/GL.h>
#include "wglext.h"
#include "window_manager.hpp"
#include "functions.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
    // Create console and redirect stdout to it
    AllocConsole();
    HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int cOutHandle = _open_osfhandle((intptr_t) outHandle, _O_TEXT);
    FILE *outFile = _fdopen(cOutHandle, "w");
    *stdout = *outFile;

    HANDLE inHandle = GetStdHandle(STD_INPUT_HANDLE);
    int cInHandle = _open_osfhandle((intptr_t) inHandle, _O_TEXT);
    FILE *inFile = _fdopen(cInHandle, "r");
    *stdin = *inFile;

    HANDLE errHandle = GetStdHandle(STD_ERROR_HANDLE);
    int cErrHandle = _open_osfhandle((intptr_t) errHandle, _O_TEXT);
    FILE *errFile = _fdopen(cErrHandle, "w");
    *stderr = *errFile;

    try
    {
        //DWORD threadId;
        //HANDLE threadHandle = CreateThread(
        //    nullptr,
        //    0,
        //    Run,
        //    nullptr,
        //    0,
        //    &threadId
        //);
        //if (!threadHandle)
        //    throw WindowsException("CreateThread");

        WindowMgr *windowMgr = new WindowMgr();
        WindowMgr::GetSingleton().Init();

        Window *dummyWindow = WindowMgr::GetSingleton().CreateNewWindow();
        dummyWindow->Init(L"Dummy");
        dummyWindow->CreateSimpleGlContext();
        LoadGlFunctions();
        dummyWindow->Live();

        Sleep(60000);


        //WindowMgr::GetSingleton().RemoveWindow(dummyWindow);

        //Window *mainWindow = WindowMgr::GetSingleton().CreateNewWindow();
        //mainWindow->Init(L"Real shit");
        //mainWindow->CreateProperGlContext();


        //delete windowMgr;

    }
    catch (WindowsException &wex)
    {
        std::cout << wex;

        std::cin.get();
    }


    //std::cin.get();

    return 0;
}