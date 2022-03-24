#pragma once

#include "Game2D.h"
#include "GamePlayer2D.h"
#include <memory>


class BudaeJjigae : public Game2D
{
public:
	static LRESULT CALLBACK BujjiWndProcW(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

public:
	BudaeJjigae(double _speed);
	virtual ~BudaeJjigae();

private:
	std::shared_ptr<GamePlayer2D> m_PlayerPtr;
	bool m_IsPlayerMoving = false;
	bool m_IsSkillAiming = false;
	ID2D1SolidColorBrush* m_D2DSkillAimingBrushPtr = nullptr;

private:
	void OnKeyDown(WPARAM _vKeyCode);
	void OnLButtonDown(WORD _x, WORD _y);
	void OnRButtonDown(WORD _x, WORD _y);
	void OnRButtonUp(WORD _x, WORD _y);
	bool CastSkill(double _x, double _y);

	// Game2D
protected:
	virtual void RenderD2D(LONGLONG _lagTime, ID2D1HwndRenderTarget* _d2dRenderTargetPtr) override;
private:
	virtual void ProcessInput() override;
	virtual void ReleaseD2DResources() override;
};
