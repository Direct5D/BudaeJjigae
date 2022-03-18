#pragma once

#include <Windows.h>
#include <vector>
#include <memory>


constexpr auto MICROSECONDS_PER_UPDATE = 1000;

class Game
{
private:
	static DWORD(WINAPI GameThreadProc)(LPVOID _lpThreadParameter);

public:
	Game();
	virtual ~Game();

protected:
	HWND m_WindowHandle;

private:
	HANDLE m_ThreadHandle;
	bool m_TerminateThread;

public:
	virtual bool Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd);
	void TerminateThread();
protected:
	virtual void OnResize(WPARAM _wParam, UINT _width, UINT _height) = 0;
	virtual void OnRightClick(WORD _x, WORD _y) = 0;
private:
	void ProcessInput();
	virtual void Update() = 0;
	virtual void Render(LONGLONG _microSeconds) = 0;
};
