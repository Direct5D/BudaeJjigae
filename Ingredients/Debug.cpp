#include "Debug.h"
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>


#ifdef _DEBUG
void DebugPrintfA(const char* _format, ...)
{
	char buf[1024];

	va_list vaList;
	va_start(vaList, _format);
	vsnprintf(buf, sizeof(buf), _format, vaList);
	va_end(vaList);

	buf[_countof(buf) - 1] = '\0';
	OutputDebugStringA(buf);
}

void DebugPrintfW(const wchar_t* _format, ...)
{
	wchar_t buf[1024];

	va_list vaList;
	va_start(vaList, _format);
	_vsnwprintf_s(buf, sizeof(buf), _format, vaList);
	va_end(vaList);

	buf[_countof(buf) - 1] = '\0';
	OutputDebugStringW(buf);
}
#endif
