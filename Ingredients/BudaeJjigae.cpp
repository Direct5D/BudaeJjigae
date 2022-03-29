#include "BudaeJjigae.h"
#include "Debug.h"
#include "Util.h"
#include <Windowsx.h>
#include "Projectile2D.h"
#include "Wall2D.h"


LRESULT CALLBACK BudaeJjigae::BujjiWndProcW(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	WindowMessage windowMessage{ hWnd, uMsg, wParam, lParam };

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

			//UINT newWidth = LOWORD(lParam);
			//UINT newHeight = HIWORD(lParam);

			//// TODO: Consider concurrency.
			//BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			//if (pBujji != nullptr)
			//	pBujji->OnWindowResize(wParam, newWidth, newHeight);

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
			//DEBUG_PRINTF_A("WM_KEYDOWN\n");

			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->PushWindowMessage(windowMessage);

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
			//DEBUG_PRINTF_A("WM_LBUTTONDOWN\n");

			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->PushWindowMessage(windowMessage);

			break;
		}

		case WM_LBUTTONUP:
		{
			//DEBUG_PRINTF_A("WM_LBUTTONUP\n");
			break;
		}

		case WM_LBUTTONDBLCLK:
		{
			DEBUG_PRINTF_A("WM_LBUTTONDBLCLK\n");
			break;
		}

		case WM_RBUTTONDOWN:
		{
			//DEBUG_PRINTF_A("WM_RBUTTONDOWN\n");

			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->PushWindowMessage(windowMessage);

			break;
		}

		case WM_RBUTTONUP:
		{
			//DEBUG_PRINTF_A("WM_RBUTTONUP\n");

			BudaeJjigae* pBujji = (BudaeJjigae*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pBujji != nullptr)
				pBujji->PushWindowMessage(windowMessage);

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
	DEBUG_PRINTF_A("0x%p BudaeJjigae::BudaeJjigae()\n", this);
	AddGameObject(m_PlayerPtr);

	// Temporary
	std::shared_ptr<GameObject2D> wallPtr((GameObject2D*)new Wall2D(300.0, 300.0));
	AddGameObject(wallPtr);
}

BudaeJjigae::~BudaeJjigae()
{
	DEBUG_PRINTF_A("0x%p BudaeJjigae::~BudaeJjigae()\n", this);
}


void BudaeJjigae::ProcessKeyDown(LONGLONG _gameTime, WPARAM _vKeyCode)
{
	DEBUG_PRINTF_A("0x%p BudaeJjigae::OnKeyDown(0x%02X)\n", this, _vKeyCode);

	if ('Q' <= _vKeyCode && _vKeyCode <= 'R')
	{
		if (m_IsSkillAiming == false)
		{
			if (!m_IsSkillColldown)
				m_IsSkillAiming = true;
		}
		/*else
		{
			m_IsSkillAiming = false;
		}*/
	}
	else if (_vKeyCode == VK_ESCAPE)
	{
		m_IsSkillAiming = false;
	}
}

void BudaeJjigae::ProcessLButtonDown(LONGLONG _currentTime, WORD _x, WORD _y)
{
	DEBUG_PRINTF_A("0x%p BudaeJjigae::OnLButtonDown(%d, %d)\n", this, _x, _y);

	if (m_IsSkillAiming)
	{
		if (false == TryCastSkill(_currentTime, _x, _y))
		{
			// TODO: If necessary, notify the user of the cause of the casting failure.
		}
		else
		{
			m_IsSkillAiming = false;
		}
	}
}

void BudaeJjigae::ProcessRButtonDown(LONGLONG _gameTime, WORD _x, WORD _y)
{
	DEBUG_PRINTF_A("0x%p BudaeJjigae::OnRButtonDown(%d, %d)\n", this, _x, _y);

	// TODO: Move only when certain conditions are met.
	{
		// TODO: Convert screen pos to game pos.
		m_PlayerPtr->Move(_x, _y);
		m_IsPlayerMoving = true;
	}
}

void BudaeJjigae::ProcessRButtonUp(LONGLONG _gameTime, WORD _x, WORD _y)
{
	DEBUG_PRINTF_A("0x%p BudaeJjigae::OnRButtonUp(%d, %d)\n", this, _x, _y);
	m_IsPlayerMoving = false;
}

enum class RangeType
{
	Fixed,
	MinMax
};

bool BudaeJjigae::TryCastSkill(LONGLONG _gameTime, double _x, double _y)
{
	if (m_IsSkillColldown)
		return false;

	double srcX = m_PlayerPtr->GetX();
	double srcY = m_PlayerPtr->GetY();

	double dstX;
	double dstY;

	double deltaX = (_x - srcX);
	double deltaY = (_y - srcY);

	if (deltaX == 0 && deltaY == 0)
		return false;

	double squaredHypotenuse = (deltaX * deltaX) + (deltaY * deltaY); // squaredHypotenuse > 0

	RangeType rangeType = RangeType::Fixed;
	switch (rangeType)
	{
		case RangeType::Fixed:
		{
			// fixed distance
			double fixedRange = 500.0;

			double distance = sqrt(squaredHypotenuse);

			dstX = srcX + fixedRange * (deltaX / distance);
			dstY = srcY + fixedRange * (deltaY / distance);

			break;
		}

		case RangeType::MinMax:
		{
			bool hasMinRange = true;
			bool hasMaxRange = true;

			double minRange = 100.0;
			double maxRange = 500.0;

			if (hasMinRange && squaredHypotenuse <= minRange * minRange)
			{
				// interpolation of minimum distance
				double distance = sqrt(squaredHypotenuse);

				dstX = srcX + minRange * (deltaX / distance);
				dstY = srcY + minRange * (deltaY / distance);
			}
			else if (hasMaxRange && maxRange * maxRange < squaredHypotenuse)
			{
				// interpolation of maximum distance
				double distance = sqrt(squaredHypotenuse);

				dstX = srcX + maxRange * (deltaX / distance);
				dstY = srcY + maxRange * (deltaY / distance);
			}
			else
			{
				dstX = _x;
				dstY = _y;
			}

			break;
		}

		default:
			return false;
	}

	double abilitySpeed = 1200.0;

	Projectile2D* projectile = new Projectile2D(srcX, srcY, dstX, dstY, abilitySpeed);
	AddGameObject(std::shared_ptr<GameObject2D>(projectile));

	// Set the cooldown end time.
	m_IsSkillColldown = true;
	m_SkillCooldownEnd = _gameTime + (LONGLONG)(0.5 * 1000 * 1000);
	return true;
}


void BudaeJjigae::RenderD2D(LONGLONG _lagTime)
{
	// TODO: Creates an AimingObject2D class that renders the range during aiming.
	Game2D::RenderD2D(_lagTime);

	if (m_IsSkillAiming)
	{
		if (m_D2DSkillAimingBrushPtr == nullptr)
		{
			// Create a Brush.
			ID2D1SolidColorBrush* d2dBrushPtr = Util::CreateD2DBrush(m_D2DRenderTargetPtr, D2D1::ColorF(D2D1::ColorF::Blue, 0.2f));
			if (d2dBrushPtr == nullptr)
				return;

			m_D2DSkillAimingBrushPtr = d2dBrushPtr;
		}

		// Draw the aiming circle.
		D2D1_ELLIPSE aimingCircle = D2D1::Ellipse(D2D1::Point2F((float)m_PlayerPtr->GetX(), (float)m_PlayerPtr->GetY()), 500.0f, 500.0f);
		m_D2DRenderTargetPtr->FillEllipse(aimingCircle, m_D2DSkillAimingBrushPtr);
	}
}

void BudaeJjigae::Update(LONGLONG _gameTime)
{
	if (m_IsSkillColldown)
	{
		if (m_SkillCooldownEnd <= _gameTime)
			m_IsSkillColldown = false;
	}

	// Continue to issue a move command while holding the move click. (regardless of the player's movement state)
	if (m_IsPlayerMoving)
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

void BudaeJjigae::ProcessWindowMessage(LONGLONG _gameTime, WindowMessage& _windowMessage)
{
	HWND& hWnd = _windowMessage.hWnd;
	UINT& uMsg = _windowMessage.uMsg;
	WPARAM& wParam = _windowMessage.wParam;
	LPARAM& lParam = _windowMessage.lParam;

	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			//DEBUG_PRINTF_A("WM_KEYDOWN\n");

			// If it's a letter key, you can't distinguish case by case.
			WPARAM vKeyCode = wParam;
			ProcessKeyDown(_gameTime, vKeyCode);

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
			//DEBUG_PRINTF_A("WM_LBUTTONDOWN\n");

			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);
			ProcessLButtonDown(_gameTime, x, y);

			break;
		}

		case WM_LBUTTONUP:
		{
			//DEBUG_PRINTF_A("WM_LBUTTONUP\n");
			break;
		}

		case WM_LBUTTONDBLCLK:
		{
			DEBUG_PRINTF_A("WM_LBUTTONDBLCLK\n");
			break;
		}

		case WM_RBUTTONDOWN:
		{
			//DEBUG_PRINTF_A("WM_RBUTTONDOWN\n");

			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);
			ProcessRButtonDown(_gameTime, x, y);

			break;
		}

		case WM_RBUTTONUP:
		{
			//DEBUG_PRINTF_A("WM_RBUTTONUP\n");

			WORD x = GET_X_LPARAM(lParam);
			WORD y = GET_Y_LPARAM(lParam);
			ProcessRButtonUp(_gameTime, x, y);

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
}

void BudaeJjigae::ReleaseD2DResources()
{
	DEBUG_PRINTF_A("0x%p BudaeJjigae::ReleaseD2DResources()\n", this);

	if (m_D2DSkillAimingBrushPtr != nullptr)
	{
		m_D2DSkillAimingBrushPtr->Release();
		m_D2DSkillAimingBrushPtr = nullptr;
	}
}
