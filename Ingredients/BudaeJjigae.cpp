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

			//// An application should not call BeginPaint except in response to a WM_PAINT message.
			//PAINTSTRUCT ps;
			//HDC hdc = BeginPaint(hWnd, &ps);

			//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			//// Each call to BeginPaint must have a corresponding call to the EndPaint function.
			//EndPaint(hWnd, &ps);
			//return 0;
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
				pBujji->OnWindowResize(wParam, newWidth, newHeight);

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

		case WM_KEYDOWN:
		{
			// If it's a letter key, you can't distinguish case by case.
			WPARAM vKeyCode = wParam;
			DEBUG_PRINTF_A("WM_KEYDOWN: vKeyCode: 0x%X\n", vKeyCode);
			break;
		}

		case WM_CHAR:
		{
			WPARAM keyCharCode = wParam;
			DEBUG_PRINTF_A("WM_CHAR: keyCharCode: %c\n", keyCharCode);
			break;
		}

		case WM_LBUTTONDOWN:
		{
			DEBUG_PRINTF_A("WM_LBUTTONDOWN\n");
			break;
		}

		case WM_LBUTTONUP:
		{
			DEBUG_PRINTF_A("WM_LBUTTONUP\n");
			break;
		}

		case WM_LBUTTONDBLCLK:
		{
			DEBUG_PRINTF_A("WM_LBUTTONDBLCLK\n");
			break;
		}

		case WM_RBUTTONDOWN:
		{
			DEBUG_PRINTF_A("WM_RBUTTONDOWN\n");

			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);

			// TODO: Consider concurrency.
			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->OnRButtonDown(x, y);

			break;
		}

		case WM_RBUTTONUP:
		{
			DEBUG_PRINTF_A("WM_RBUTTONUP\n");

			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);

			// TODO: Consider concurrency.
			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->OnRButtonUp(x, y);

			break;
		}

		case WM_RBUTTONDBLCLK:
		{
			DEBUG_PRINTF_A("WM_RBUTTONDBLCLK\n");
			break;
		}

		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


BudaeJjigae::BudaeJjigae(double _speed) : Game2D(), m_PlayerPtr(new GamePlayer2D(0, 0, _speed))
{
	DEBUG_PRINTF_A("BudaeJjigae::BudaeJjigae()\n");
	AddGameObject(m_PlayerPtr);
}

BudaeJjigae::~BudaeJjigae()
{
	DEBUG_PRINTF_A("BudaeJjigae::~BudaeJjigae()\n");
}


void BudaeJjigae::OnRButtonDown(WORD _x, WORD _y)
{
	// TODO: Move only when certain conditions are met.
	{
		m_PlayerPtr->Move(_x, _y);
		IsPlayerMoving = true;
	}
}

void BudaeJjigae::OnRButtonUp(WORD _x, WORD _y)
{
	IsPlayerMoving = false;
}

void BudaeJjigae::ProcessInput()
{
	// GetAsyncKeyState(VK_LBUTTON) always returns the state of the left physical mouse button, regardless of whether it is mapped to the left or right logical mouse button.
	// Determine the system's current mapping of physical mouse buttons to logical mouse buttons by calling GetSystemMetrics(SM_SWAPBUTTON).
	bool areMouseButtonsSwapped = (0 != GetSystemMetrics(SM_SWAPBUTTON));
	int vLButton = areMouseButtonsSwapped ? VK_RBUTTON : VK_LBUTTON;
	int vRButton = areMouseButtonsSwapped ? VK_LBUTTON : VK_RBUTTON;

	SHORT rButtonState = GetAsyncKeyState(vRButton);
	if (rButtonState == 0)
	{
		// The return value is zero for the following cases:
		// - The current desktop is not the active desktop
		// - The foreground thread belongs to another processand the desktop does not allow the hook or the journal record.
	}
	else
	{
		bool isRButtonDown = (rButtonState < 0);

		if (isRButtonDown)
		{
			// RButtonDown

			if (IsPlayerMoving)
			{
				POINT cursorPos;
				RECT rect;
				if (0 != GetCursorPos(&cursorPos) && 0 != ScreenToClient(m_WindowHandle, &cursorPos) && 0 != GetClientRect(m_WindowHandle, &rect))
				{
					if (cursorPos.x < rect.left)
						cursorPos.x = rect.left;

					if (rect.right < cursorPos.x)
						cursorPos.x = rect.right;

					if (cursorPos.y < rect.top)
						cursorPos.y = rect.top;

					if (rect.bottom < cursorPos.y)
						cursorPos.y = rect.bottom;

					m_PlayerPtr->Move(cursorPos.x, cursorPos.y);	
				}
			}
		}
		else
		{
			// RButtonUp
		}
	}
}