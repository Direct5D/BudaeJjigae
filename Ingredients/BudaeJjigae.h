#pragma once

#include "Game2D.h"
#include "GamePlayer2D.h"
#include <memory>


class BudaeJjigae : public Game2D
{
public:
	static LRESULT CALLBACK BujjiWndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
private:
	static void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
	static void OnResize(HWND _hWnd, WPARAM _wParam, UINT _width, UINT _height);

public:
	BudaeJjigae(double _speed);
	virtual ~BudaeJjigae();

private:
	std::shared_ptr<GamePlayer2D> m_PlayerPtr;

private:
	virtual void OnRightClick(WORD _x, WORD _y) override;
};
