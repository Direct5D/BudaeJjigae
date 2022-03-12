#pragma once

#include "Game.h"
#include "GamePlayer.h"
#include <memory>


class BudaeJjigae : public Game
{
public:
	static LRESULT CALLBACK BujjiWndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
private:
	static void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
	static void OnResize(HWND _hWnd, UINT _wParam, UINT _width, UINT _height);

public:
	BudaeJjigae(double _speed);
	virtual ~BudaeJjigae();

private:
	std::shared_ptr<GamePlayer> m_PlayerPtr;

public:
	virtual void OnRightClick(WORD _x, WORD _y);
};
