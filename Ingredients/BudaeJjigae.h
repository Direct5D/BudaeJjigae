#pragma once

#include "Game2D.h"
#include "GamePlayer2D.h"
#include <memory> // shared_ptr
#include "Timer.h"


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
	bool m_IsSkillColldown = false;
	LONGLONG m_SkillCooldownEnd = 0;
	ID2D1SolidColorBrush* m_D2DSkillAimingBrushPtr = nullptr;

private:
	void ProcessKeyDown(LONGLONG _gameTime, WPARAM _vKeyCode);
	void ProcessLButtonDown(LONGLONG _gameTime, WORD _x, WORD _y);
	void ProcessRButtonDown(LONGLONG _gameTime, WORD _x, WORD _y);
	void ProcessRButtonUp(LONGLONG _gameTime, WORD _x, WORD _y);
	bool TryCastSkill(LONGLONG _gameTime, double _x, double _y);

	// Game2D
protected:
	virtual void RenderD2D(LONGLONG _lagTime) override;
private:
	virtual void Update(LONGLONG _gameTime) override;
	virtual void ProcessWindowMessage(LONGLONG _gameTime, WindowMessage& _windowMessage) override;
	virtual void ReleaseD2DResources() override;
};
