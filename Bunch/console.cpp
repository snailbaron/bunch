#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include "console.hpp"
#include "windows_exception.hpp"

Console::Console() :
    Singleton<Console>()
{
    if (!AllocConsole())
        throw WindowsException("AllocConsole");
}

Console::~Console()
{
    if (!FreeConsole())
        throw WindowsException("FreeConsole");
}

void Console::RedirectStdHere()
{
    HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int cOutHandle = _open_osfhandle((intptr_t)outHandle, _O_TEXT);
    FILE *outFile = _fdopen(cOutHandle, "w");
    *stdout = *outFile;

    HANDLE inHandle = GetStdHandle(STD_INPUT_HANDLE);
    int cInHandle = _open_osfhandle((intptr_t)inHandle, _O_TEXT);
    FILE *inFile = _fdopen(cInHandle, "r");
    *stdin = *inFile;

    HANDLE errHandle = GetStdHandle(STD_ERROR_HANDLE);
    int cErrHandle = _open_osfhandle((intptr_t)errHandle, _O_TEXT);
    FILE *errFile = _fdopen(cErrHandle, "w");
    *stderr = *errFile;
}
