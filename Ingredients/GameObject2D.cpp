#include "GameObject2D.h"
#include "Debug.h"
#include "Util.h"


GameObject2D::GameObject2D(double _x, double _y, double _speed)
{
	DEBUG_PRINTF_A("0x%p GameObject2D::GameObject2D()\n", this);
	m_X = _x;
	m_Y = _y;
	m_Speed = _speed;
}

GameObject2D::~GameObject2D()
{
	DEBUG_PRINTF_A("0x%p GameObject2D::~GameObject2D()\n", this);

	if (m_D2DBlackBrushPtr != nullptr)
	{
		m_D2DBlackBrushPtr->Release();
		m_D2DBlackBrushPtr = nullptr;
	}

	if (m_D2DGreenBrushPtr != nullptr)
	{
		m_D2DGreenBrushPtr->Release();
		m_D2DGreenBrushPtr = nullptr;
	}
}


double GameObject2D::GetX()
{
	return m_X;
}

double GameObject2D::GetY()
{
	return m_Y;
}


void GameObject2D::Render(ID2D1HwndRenderTarget* _d2dRenderTargetPtr)
{
	// Get the brushes.
	if (m_D2DBlackBrushPtr == nullptr)
	{
		// Create a Brush.
		ID2D1SolidColorBrush* d2dBlackBrushPtr = Util::CreateD2DBrush(_d2dRenderTargetPtr, D2D1::ColorF(D2D1::ColorF::Black));
		if (d2dBlackBrushPtr == nullptr)
			return;

		m_D2DBlackBrushPtr = d2dBlackBrushPtr;
	}

	if (m_D2DGreenBrushPtr == nullptr)
	{
		ID2D1SolidColorBrush* d2dGreenBrushPtr = Util::CreateD2DBrush(_d2dRenderTargetPtr, D2D1::ColorF(D2D1::ColorF::Green));
		if (d2dGreenBrushPtr == nullptr)
			return;

		m_D2DGreenBrushPtr = d2dGreenBrushPtr;
	}

	// Draw the Circle.
	D2D1_ELLIPSE playerCircle = D2D1::Ellipse(D2D1::Point2F((float)m_X, (float)m_Y), 37.5f, 37.5f);
	_d2dRenderTargetPtr->DrawEllipse(
		playerCircle,
		m_D2DBlackBrushPtr,
		5.0f);
	_d2dRenderTargetPtr->FillEllipse(
		playerCircle,
		m_D2DGreenBrushPtr);
}
