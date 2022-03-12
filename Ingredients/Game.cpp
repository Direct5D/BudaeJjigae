#include "Game.h"
#include "Debug.h"
#include "Timer.h"


constexpr auto MICROSECONDS_PER_UPDATE = 1000;

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

	// Create the main window. (메인 스레드의 윈도우)
	HWND hWnd = CreateWindowW(_pWndClass->lpszClassName, _wndName, WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX),
									 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
									 NULL, NULL, _pWndClass->hInstance, NULL);

	ShowWindow(hWnd, _nShowCmd);
	UpdateWindow(hWnd);

	m_WindowHandle = hWnd;
	//SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)((LONG_PTR)this - 8));
	SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)this);

	return true;
}

// 각 게임에 대한 스레드를 생성 및 실행합니다.
bool Game::Run()
{
	if (m_WindowHandle == NULL)
		return false;

	if (m_ThreadHandle == NULL)
	{
		// Create the game thread.
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

void Game::Render(double _frame)
{
	// m_HWnd 사용
}


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

		pGame->Render((double)lagTime / MICROSECONDS_PER_UPDATE); // 0 <= (lagTime / MICROSECONDS_PER_UPDATE) < 1
	}

	return 0; // Do not use STILL_ACTIVE (259) as it indicates that the thread is not terminated.
}


//void ProcessInput()
//{
//	// 입력된 모든 메시지를 뽑아서 처리합니다.
//	while (false == g_GameMessageQueue.empty())
//	{
//		GameMessage* pGameMessage = g_GameMessageQueue.front();
//		g_GameMessageQueue.pop();
//
//		/*ProcessMessage(pGameMessage);*/
//		switch (pGameMessage->uMsg)
//		{
//			case WM_KEYDOWN:
//			{
//				WPARAM vKeyCode = pGameMessage->wParam;
//
//				if ('S' == vKeyCode)
//				{
//					g_playerState = PLAYER_STATE::STOP;
//				}
//
//				// Use skills (Q, W, E ,R)
//				break;
//			}
//
//			case WM_RBUTTONDOWN:
//			{
//				LPARAM point = pGameMessage->lParam;
//
//				g_playerState = PLAYER_STATE::MOVE;
//				g_moveX = LOWORD(point);
//				g_moveY = HIWORD(point);
//				break;
//			}
//
//			default:
//				break;
//		}
//
//		delete pGameMessage;
//	}
//}
//
