#include "Game.h"
#include "Debug.h"
#include "Timer.h"


// This is the game thread procedure. It is used when creating a thread using the CreateThread function.
DWORD WINAPI Game::GameThreadProc(LPVOID _lpParameter)
{
	DEBUG_PRINTF_A("Game::GameThreadProc(0x%p)\n", _lpParameter);

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

	pGame->OnTerminate();

	DEBUG_PRINTF_A("Game::GameThreadProc(0x%p): return 0\n", _lpParameter);
	return 0; // Do not use STILL_ACTIVE (259) as it indicates that the thread is not terminated.
}

Game::Game()
{
	DEBUG_PRINTF_A("0x%p Game::Game()\n", this);
}

// You must call the TerminateThread() before calling the destructor.
Game::~Game()
{
	DEBUG_PRINTF_A("0x%p Game::~Game()\n", this);

	if (m_ThreadHandle != NULL)
	{
		CloseHandle(m_ThreadHandle);
		m_ThreadHandle = NULL;
	}

	if (m_WindowHandle != NULL)
	{
		// TODO_CHECK: What if the window is already closed?
		CloseWindow(m_WindowHandle);
		m_WindowHandle = NULL;
	}
}


bool Game::Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd)
{
	DEBUG_PRINTF_A("0x%p Game::Init()\n", this);

	bool result = true;

	if (m_WindowHandle == NULL)
	{
		// Create a game window.
		/*HWND hWnd = CreateWindowW(_pWndClass->lpszClassName, _wndName, WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX),
								  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								  NULL, NULL, _pWndClass->hInstance, NULL);*/
		HWND hWnd = CreateWindowW(_pWndClass->lpszClassName, _wndName, WS_OVERLAPPEDWINDOW,
								 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								 NULL, NULL, _pWndClass->hInstance, NULL);
		if (hWnd == NULL)
		{
			result = false;
		}
		else
		{
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
			ShowWindow(hWnd, _nShowCmd);
			m_WindowHandle = hWnd;
		}
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
		{
			result = false;
		}
		else
		{
			m_ThreadHandle = hThread;
		}
	}

	if (false == OnInit())
		result = false;

	if (result == false)
		Terminate();

	return result;
}

// You must call the Terminate() before calling the destructor.
void Game::Terminate()
{
	DEBUG_PRINTF_A("0x%p Game::Terminate()\n", this);

	if (m_ThreadHandle != NULL)
	{
		m_TerminateThread = true;
		WaitForSingleObject(m_ThreadHandle, INFINITE);
		CloseHandle(m_ThreadHandle);
		m_ThreadHandle = NULL;
	}

	if (m_WindowHandle != NULL)
	{
		CloseWindow(m_WindowHandle);
		m_WindowHandle = NULL;
	}
}
