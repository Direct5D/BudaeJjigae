#include <Windows.h>
#include <Windowsx.h>
#include "Debug.h"
#include "BudaeJjigae.h"


LRESULT CALLBACK BujjiWndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
void BujjiWndOnResize(HWND _hWnd, UINT _wParam, UINT _width, UINT _height);
int RunMessageLoop();

int WINAPI wWinMain(_In_ HINSTANCE _hInstance,
					_In_opt_ HINSTANCE _hPrevInstance,
					_In_ LPWSTR _lpCmdLine,
					_In_ int _nShowCmd
)
{
	double playerSpeed = 300.0;
	LPCWSTR wndName = L"Window";
	LPCWSTR wndClassName = L"Window Class";

	// Register the window class.
	WNDCLASSW wc = { };
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = BujjiWndProc;
	wc.hInstance = _hInstance;
	wc.lpszClassName = wndClassName;
	RegisterClassW(&wc);

	// 게임 생성/초기화 및 실행
	BudaeJjigae bujji(playerSpeed);
	bujji.InitWindow(&wc, wndName, _nShowCmd);
	bujji.Run();

	// 모든 게임이 종료되기를 기다려야 함
	// 그리고 스레드도 종료해줘야함

	return RunMessageLoop();
}

WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if (dwStyle & WS_OVERLAPPEDWINDOW)
	{
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(hwnd, &g_wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(hwnd,
											 MONITOR_DEFAULTTOPRIMARY), &mi))
		{
			SetWindowLong(hwnd, GWL_STYLE,
				dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else
	{
		SetWindowLong(hwnd, GWL_STYLE,
			dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hwnd, &g_wpPrev);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

LRESULT CALLBACK BujjiWndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			// An application should not call BeginPaint except in response to a WM_PAINT message.
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			// Each call to BeginPaint must have a corresponding call to the EndPaint function.
			EndPaint(hWnd, &ps);

			return 0;
		}

		case WM_KEYDOWN:
		{
			// If it's a letter key, you can't distinguish case by case.
			WPARAM vKeyCode = wParam;

			DEBUG_PRINTF_A("vKeyCode: 0x%X\n", vKeyCode);
			break;
		}

		case WM_CHAR:
		{
			WPARAM keyCharCode = wParam;

			DEBUG_PRINTF_A("keyCharCode: %c\n", keyCharCode);
			break;
		}

		case WM_LBUTTONDOWN:
		{
			DEBUG_PRINTF_A("WM_LBUTTONDOWN\n");
			break;
		}

		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);

		case WM_LBUTTONDBLCLK:
		{
			DEBUG_PRINTF_A("WM_LBUTTONDBLCLK\n");
			break;
		}

		case WM_RBUTTONDOWN:
		{
			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);

			// TODO: 동시성 고려
			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->OnRightClick(x, y);

			break;
		}

		case WM_RBUTTONUP:
		{
			break;
		}

		case WM_RBUTTONDBLCLK:
		{
			break;
		}

		// The window size has changed.
		case WM_SIZE:
		{
			UINT newWidth = LOWORD(lParam);
			UINT newHeight = HIWORD(lParam);

			BujjiWndOnResize(hWnd, wParam, newWidth, newHeight);

			return 0; // If an application processes this message, it should return zero.
		}

		case WM_CREATE:
		{
			break;
		}

		// The user closed an application window by clicking the Close button, or by using a keyboard shortcut such as ALT + F4.
		case WM_CLOSE:
		{
			const int result = MessageBoxW(hWnd, L"Are you sure you want to quit?", L"Warning", MB_YESNO);
			if (IDYES != result)
			{
				return true;
			}

			// DefWindowProc automatically calls DestroyWindow.
			// DestroyWindow destroys the window and sends WM_DESTROY and WM_NCDESTROY messages
			break;
		}

		// The window is being destroyed.
		// This message is sent after the window is removed from the screen.
		case WM_DESTROY:
		{
			// Posts a WM_QUIT message to the thread's message queue to break out the message loop.
			PostQuitMessage(0);

			return 0;
		}

		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void BujjiWndOnResize(HWND _hWnd, UINT _wParam, UINT _width, UINT _height)
{
	switch (_wParam)
	{
		case SIZE_RESTORED: // The window has been resized, but neither the SIZE_MINIMIZED nor SIZE_MAXIMIZED value applies.
			break;
		case SIZE_MINIMIZED:
			break;
		case SIZE_MAXSHOW:
			break;
		case SIZE_MAXIMIZED:
			break;
		case SIZE_MAXHIDE:
			break;
		default:
			break;
	}
}

// Run the message loop. When the loop ends, it returns an exit code.
int RunMessageLoop()
{
	BOOL bRet;
	MSG msg;

	// If the GetMessage retrieves the WM_QUIT message, the return value is zero.
	while (0 != (bRet = GetMessageW(&msg, NULL, 0, 0)))
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg); // Dispatch the message to the target window.
		}
	}

	// The exit code given in the PostQuitMessage function.
	return (int)msg.wParam;
}
