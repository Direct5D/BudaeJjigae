#pragma once

#include <Windows.h>
#include "Timer.h"
#include <deque>
#include "WindowMessage.h"
#include <vector>
#include <memory> // shared_ptr
#include "GameObject.h"


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
	Timer m_RealTimer;
private:
	HANDLE m_ThreadHandle = NULL;
	bool m_TerminateThread = false;
	std::deque<WindowMessage> m_WindowMessageQueue;

public:
	bool Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd);
	void Terminate();
protected:
	void PushWindowMessage(WindowMessage _windowMessagae);
private:
	void ProcessInput(LONGLONG _gameTime);

private:
	virtual bool OnInit() = 0; // Initialize the resources required for the game. All resources must be released on failure.
	virtual void Update(LONGLONG _gameTime) = 0; // Game
	virtual void ProcessWindowMessage(LONGLONG _gameTime, WindowMessage& _windowMessage) = 0;
	virtual void FixedUpdate() = 0; // Physics
	virtual void Render(LONGLONG _lagTime) = 0;
	virtual void OnTerminate() = 0;
};
