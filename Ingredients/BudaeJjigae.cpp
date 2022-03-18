#include "BudaeJjigae.h"
#include "Debug.h"
#include <Windowsx.h>


LRESULT CALLBACK BudaeJjigae::BujjiWndProcW(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			DEBUG_PRINTF_A("WM_CREATE\n");
			break;
		}

		case WM_PAINT:
		{
			//DEBUG_PRINTF_A("WM_PAINT\n");
		//	// An application should not call BeginPaint except in response to a WM_PAINT message.
		//	PAINTSTRUCT ps;
		//	HDC hdc = BeginPaint(hWnd, &ps);

		//	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		//	// Each call to BeginPaint must have a corresponding call to the EndPaint function.
		//	EndPaint(hWnd, &ps);
		//	return 0;
			break;
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

		case WM_LBUTTONUP:
		{
			//DEBUG_PRINTF_A("WM_LBUTTONUP\n");
			break;
		}

		case WM_LBUTTONDBLCLK:
		{
			//DEBUG_PRINTF_A("WM_LBUTTONDBLCLK\n");
			break;
		}

		case WM_RBUTTONDOWN:
		{
			//DEBUG_PRINTF_A("WM_RBUTTONDOWN\n");
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
			//DEBUG_PRINTF_A("WM_RBUTTONUP\n");
			break;
		}

		case WM_RBUTTONDBLCLK:
		{
			//DEBUG_PRINTF_A("WM_RBUTTONDBLCLK\n");
			break;
		}

		// The window size has changed.
		case WM_SIZE:
		{
			//DEBUG_PRINTF_A("WM_SIZE\n");
			UINT newWidth = LOWORD(lParam);
			UINT newHeight = HIWORD(lParam);

			// TODO: Consider concurrency.
			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->OnResize(wParam, newWidth, newHeight);

			return 0; // If an application processes this message, it should return zero.
		}

		// The user closed an application window by clicking the Close button, or by using a keyboard shortcut such as ALT + F4.
		case WM_CLOSE:
		{
			DEBUG_PRINTF_A("WM_CLOSE\n");
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
			DEBUG_PRINTF_A("WM_DESTROY\n");
			// Posts a WM_QUIT message to the thread's message queue to break out the message loop.
			PostQuitMessage(0);

			return 0;
		}

		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
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
