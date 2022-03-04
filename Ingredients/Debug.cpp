#include "Debug.h"
#include <stdarg.h>


void DebugPrintf(const char* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	char dbg_out[4096];
	vsprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugStringA(dbg_out);
}

void DebugPrintW(const wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugStringW(dbg_out);
}
