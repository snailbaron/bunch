#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "wglext.h"

extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

void LoadGlFunctions();

#endif