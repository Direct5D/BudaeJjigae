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
	HWND m_WindowHandle = NULL;
private:
	HANDLE m_ThreadHandle = NULL;
	bool m_TerminateThread = false;

public:
	bool Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd);
	void Terminate();

private:
	// Restrict access to private so that child object cannot call it.
	virtual bool OnInit() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void Render(LONGLONG _lagTime) = 0;
	virtual void OnTerminate() = 0;
};
