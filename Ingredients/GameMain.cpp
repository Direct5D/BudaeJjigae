#include "GameMain.h"
#include "Timer.h"
#include "Debug.h"


constexpr auto MICROSECONDS_PER_UPDATE = 1000;

namespace Bujji
{
	void ProcessInput();
	void Update();
	void Render(HWND _hMainWindow, double _frame);

	// This is the game thread procedure. It is used when creating a thread using the CreateThread function.
	// Please pass the handle of the window in which to display the game to _lpThreadParameter.
	DWORD WINAPI GameThreadProc(LPVOID _lpThreadParameter)
	{
		HWND hMainWindow = (HWND)_lpThreadParameter;

		Timer globalGameTimer;
		LONGLONG previousTime = globalGameTimer.GetMicroseconds();
		LONGLONG lagTime = 0;

		while (true)
		{
			LONGLONG currentTime = globalGameTimer.GetMicroseconds();
			LONGLONG elapsedTime = currentTime - previousTime;
			previousTime = currentTime;
			lagTime += elapsedTime;

			ProcessInput();

			while (MICROSECONDS_PER_UPDATE <= lagTime)
			{
				Update();
				lagTime -= MICROSECONDS_PER_UPDATE;
			}

			Render(hMainWindow, (double)lagTime / (double)MICROSECONDS_PER_UPDATE); // 0 <= (lagTime / MICROSECONDS_PER_UPDATE) < 1
		}

		return 0; // Do not use STILL_ACTIVE as it indicates that the thread is not terminated.
	}

	// Returns whether the message is processed.
	bool GameMessageProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
	{
		switch (_uMsg)
		{
			// The user closed an application window by clicking the Close button, or by using a keyboard shortcut such as ALT + F4.
			case WM_CLOSE:
			{
				const int result = MessageBoxW(_hWnd, L"Are you sure you want to quit?", L"Warning", MB_YESNO);
				if (IDYES != result)
				{
					return true;
				}

				// DefWindowProc automatically calls DestroyWindow.
				// DestroyWindow destroys the window and sends WM_DESTROY and WM_NCDESTROY messages
				break;
			}

			case WM_KEYDOWN:
			{
				// If it's a letter key, you can't distinguish case by case.
				WPARAM vKeyCode = _wParam;

				// Use skills (Q, W, E ,R)

#ifdef _DEBUG
				DebugPrintf("vKeyCode: 0x%X\n", vKeyCode);
#endif
				break;
			}

			case WM_CHAR:
			{
				WPARAM keyCharCode = _wParam;

#ifdef _DEBUG
				DebugPrintf("keyCharCode: %c\n", keyCharCode);
#endif
				break;
			}

			case WM_LBUTTONDOWN:
			{
#ifdef _DEBUG
				DebugPrintf("WM_LBUTTONDOWN\n");
#endif
				break;
			}

			case WM_LBUTTONUP:
			{
#ifdef _DEBUG
				DebugPrintf("WM_LBUTTONUP\n");
#endif
				break;
			}

			case WM_LBUTTONDBLCLK:
			{
#ifdef _DEBUG
				DebugPrintf("WM_LBUTTONDBLCLK\n");
#endif
				break;
			}

			case WM_RBUTTONDOWN:
			{
#ifdef _DEBUG
				DebugPrintf("WM_RBUTTONDOWN\n");
#endif
				break;
			}

			case WM_RBUTTONUP:
			{
#ifdef _DEBUG
				DebugPrintf("WM_RBUTTONUP\n");
#endif
				break;
			}

			case WM_RBUTTONDBLCLK:
			{
#ifdef _DEBUG
				DebugPrintf("WM_RBUTTONDBLCLK\n");
#endif
				break;
			}

			default:
				break;
		}

		return false;
	}

	void ProcessInput()
	{

	}

	void Update()
	{
		// Update every MICROSECONDS_PER_UPDATE

	}

	void Render(HWND _hMainWindow, double _frame)
	{

	}
}
