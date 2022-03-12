#include "Game.h"
#include "Debug.h"
#include "Timer.h"


constexpr auto MICROSECONDS_PER_UPDATE = 1000;

// This is the game thread procedure. It is used when creating a thread using the CreateThread function.
DWORD WINAPI Game::GameThreadProc(LPVOID _lpParameter)
{
	Game* pGame = (Game*)_lpParameter;

	Timer gameTimer;
	LONGLONG previousTime = gameTimer.GetMicroseconds();
	LONGLONG lagTime = 0;

	while (pGame->m_ExitThreadFlag == false)
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

	return 0; // Do not use STILL_ACTIVE (259) as it indicates that the thread is not terminated.
}

Game::Game()
{
	m_WindowHandle = NULL;
	m_ThreadHandle = NULL;
	m_ExitThreadFlag = false;
}

Game::~Game()
{
	if (m_ThreadHandle != NULL)
	{
		m_ExitThreadFlag = true;
		WaitForSingleObject(m_ThreadHandle, INFINITE);
	}

	if (m_WindowHandle != NULL)
	{
		CloseWindow(m_WindowHandle);
		m_WindowHandle = NULL;
	}
}


bool Game::InitWindow(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd)
{
	if (m_WindowHandle != NULL)
		return true;

	// Create the window.
	HWND hWnd = CreateWindowW(_pWndClass->lpszClassName, _wndName, WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX),
									 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
									 NULL, NULL, _pWndClass->hInstance, NULL);

	ShowWindow(hWnd, _nShowCmd);
	UpdateWindow(hWnd);

	m_WindowHandle = hWnd;
	SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)this);

	return true;
}

// Creates and runs a game thread.
bool Game::Run()
{
	if (m_WindowHandle == NULL)
		return false;

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
	}

	return true;
}


bool Game::AddGameObject(std::shared_ptr<GameObject> _gameObjectPtr)
{
	if (_gameObjectPtr == nullptr)
		return false;

	m_GameObjectVector.push_back(_gameObjectPtr);
	return true;
}


void Game::ProcessInput()
{

}

void Game::Update()
{
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		m_GameObjectVector[i]->Update(MICROSECONDS_PER_UPDATE);
	}
}

void Game::Render(LONGLONG _microSeconds)
{
	// Render using the window handle.
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		GameObject* gameObjectPtr = m_GameObjectVector[i].get();

		
	}
}
