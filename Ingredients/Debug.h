#pragma once


#ifdef _DEBUG
#define DEBUG_PRINTF_A(fmt, ...) DebugPrintfA(fmt, __VA_ARGS__)
#define DEBUG_PRINTF_W(fmt, ...) DebugPrintfW(fmt, __VA_ARGS__)
void DebugPrintfA(const char* fmt, ...);
void DebugPrintfW(const wchar_t* fmt, ...);
#else
#define DEBUG_PRINTF(fmt)
#endif
