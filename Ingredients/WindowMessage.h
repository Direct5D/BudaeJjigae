#pragma once

#include <Windows.h>


// Temporary
typedef struct _WindowMessage
{
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
} WindowMessage;
