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
	bool IsPlayerMoving = false;

private:
	virtual void OnRButtonDown(WORD _x, WORD _y) override;
	virtual void OnRButtonUp(WORD _x, WORD _y) override;
	virtual void ProcessInput() override;
};
