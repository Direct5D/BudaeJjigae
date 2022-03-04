#pragma once

#include <Windows.h>


namespace Bujji
{
	DWORD WINAPI GameThreadProc(LPVOID _lpThreadParameter);
	bool GameMessageProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
}
