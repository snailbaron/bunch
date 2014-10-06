#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"

extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;

void LoadGlFunctions();

#endif