#include "Game.h"
#include "Debug.h"
#include "Timer.h"


// This is the game thread procedure. It is used when creating a thread using the CreateThread function.
DWORD WINAPI Game::GameThreadProc(LPVOID _lpParameter)
{
	DEBUG_PRINTF_A("Game::GameThreadProc()\n");
	Game* pGame = (Game*)_lpParameter;

	Timer gameTimer;
	LONGLONG previousTime = gameTimer.GetMicroseconds();
	LONGLONG lagTime = 0;

	while (pGame->m_TerminateThread == false)
	{
		LONGLONG currentTime = gameTimer.GetMicroseconds();
		LONGLONG elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		lagTime += elapsedTime;

		pGame->ProcessInput();

		// Updates changes during the lag time at once.
		while (MICROSECONDS_PER_UPDATE <= lagTime)
		{
			pGame->Update(); // Fixed time update (MICROSECONDS_PER_UPDATE per update)
			lagTime -= MICROSECONDS_PER_UPDATE;
		}

		pGame->Render(lagTime); // 0 <= (lagTime / MICROSECONDS_PER_UPDATE) < 1
	}

	DEBUG_PRINTF_A("Game::GameThreadProc(): return 0\n");
	return 0; // Do not use STILL_ACTIVE (259) as it indicates that the thread is not terminated.
}

Game::Game()
{
	DEBUG_PRINTF_A("Game::Game()\n");

	m_WindowHandle = NULL;
	m_ThreadHandle = NULL;
	m_TerminateThread = false;
}

// You must call the TerminateThread() before calling the destructor.
Game::~Game()
{
	DEBUG_PRINTF_A("Game::~Game()\n");

	if (m_WindowHandle != NULL)
	{
		// TODO_CHECK: What if the window is already closed?
		CloseWindow(m_WindowHandle);
		m_WindowHandle = NULL;
	}

	if (m_ThreadHandle != NULL)
	{
		CloseHandle(m_ThreadHandle);
		m_ThreadHandle = NULL;
	}
}


bool Game::Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd)
{
	DEBUG_PRINTF_A("Game::Init()\n");
	if (m_WindowHandle != NULL && m_ThreadHandle != NULL)
		return true;

	if (m_WindowHandle == NULL)
	{
		// Create a game window.
		HWND hWnd = CreateWindowW(_pWndClass->lpszClassName, _wndName, WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX),
										 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
										 NULL, NULL, _pWndClass->hInstance, NULL);
		if (hWnd == NULL)
			return false;

		ShowWindow(hWnd, _nShowCmd);

		SetLastError(0);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
		if (0 != GetLastError())
			return false;

		m_WindowHandle = hWnd;
	}

	// Creates and runs a game thread.
	if (m_ThreadHandle == NULL)
	{
		// Create a game thread.
		DWORD stackSize = 0; // Use the default size for the executable.
		LPVOID lpParameter = this;
		DWORD creationFlags = 0; // The thread runs immediately after creation.
		DWORD threadId;

		HANDLE hThread = CreateThread(NULL, stackSize, Game::GameThreadProc, lpParameter, creationFlags, &threadId);
		if (hThread == NULL)
			return false;

		m_ThreadHandle = hThread;
		return true;
	}

	return true;
}

// You must call the TerminateThread() before calling the destructor.
void Game::TerminateThread()
{
	DEBUG_PRINTF_A("Game::TerminateThread()\n");

	if (m_WindowHandle == NULL || m_ThreadHandle == NULL || m_TerminateThread)
		return;

	m_TerminateThread = true;
	WaitForSingleObject(m_ThreadHandle, INFINITE);
}


void Game::ProcessInput()
{
	//DEBUG_PRINTF_A("Game::ProcessInput()\n");
}
