#pragma once

#include "GameObject.h"
#include <d2d1.h>


class GameObject2D : public GameObject
{
public:
	GameObject2D(double _x, double _y, double _speed);
	virtual ~GameObject2D();

protected:
	double m_X, m_Y;
private:
	ID2D1SolidColorBrush* m_D2DBlackBrushPtr = nullptr;
	ID2D1SolidColorBrush* m_D2DGreenBrushPtr = nullptr;

public:
	double GetX();
	double GetY();

public:
	virtual void Render(ID2D1HwndRenderTarget* _d2dRenderTargetPtr);

	// GameObject
public:
	virtual void Update(LONGLONG _microseconds) = 0;
	virtual GameObject* Simulate(LONGLONG _microseconds) = 0;
};
