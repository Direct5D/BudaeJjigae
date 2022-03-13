#include "BudaeJjigae.h"
#include "Debug.h"
#include <Windowsx.h>


LRESULT CALLBACK BudaeJjigae::BujjiWndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	//DEBUG_PRINTF_A("BujjiWndProc::~BujjiWndProc()\n");
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
			//DEBUG_PRINTF_A("vKeyCode: 0x%X\n", vKeyCode);
			// If it's a letter key, you can't distinguish case by case.
			WPARAM vKeyCode = wParam;
			break;
		}

		case WM_CHAR:
		{
			//DEBUG_PRINTF_A("keyCharCode: %c\n", keyCharCode);
			WPARAM keyCharCode = wParam;
			break;
		}

		case WM_LBUTTONDOWN:
		{
			//DEBUG_PRINTF_A("WM_LBUTTONDOWN\n");
			break;
		}

		HANDLE_MSG(hWnd, WM_LBUTTONUP, BudaeJjigae::OnLButtonUp);

		case WM_LBUTTONDBLCLK:
		{
			//DEBUG_PRINTF_A("WM_LBUTTONDBLCLK\n");
			break;
		}

		case WM_RBUTTONDOWN:
		{
			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);

			// TODO: Consider concurrency.
			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
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

			OnResize(hWnd, wParam, newWidth, newHeight);

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

WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
void BudaeJjigae::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	DEBUG_PRINTF_A("BujjiWndProc::OnLButtonUp()\n");
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

void BudaeJjigae::OnResize(HWND _hWnd, WPARAM _wParam, UINT _width, UINT _height)
{
	//DEBUG_PRINTF_A("BujjiWndProc::OnResize()\n");
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


BudaeJjigae::BudaeJjigae(double _speed) : Game2D()
{
	DEBUG_PRINTF_A("BudaeJjigae::BudaeJjigae()\n");
	m_PlayerPtr = std::shared_ptr<GamePlayer2D>(new GamePlayer2D(0, 0, _speed));
	AddGameObject(m_PlayerPtr);
}

BudaeJjigae::~BudaeJjigae()
{
	DEBUG_PRINTF_A("BudaeJjigae::~BudaeJjigae()\n");
}


void BudaeJjigae::OnRightClick(WORD _x, WORD _y)
{
	DEBUG_PRINTF_A("BudaeJjigae::OnRightClick()\n");
	m_PlayerPtr->Move(_x, _y);
}
