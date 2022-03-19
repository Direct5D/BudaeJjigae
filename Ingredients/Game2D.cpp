#include "Game2D.h"
#include "Debug.h"

#pragma comment(lib, "d2d1")


Game2D::Game2D()
{
	DEBUG_PRINTF_A("Game2D::Game2D()\n");
}

Game2D::~Game2D()
{
	DEBUG_PRINTF_A("Game2D::~Game2D()\n");
}


bool Game2D::Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd)
{
	if (m_D2DFactoryPtr == nullptr)
	{
		// Create an ID2D1Factory.
		ID2D1Factory* d2dFactoryPtr = NULL;
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&d2dFactoryPtr
		);
		if (hr != S_OK || d2dFactoryPtr == nullptr)
			return false;

		m_D2DFactoryPtr = d2dFactoryPtr;
	}

	if (false == Game::Init(_pWndClass, _wndName, _nShowCmd))
		return false;

	return true;
}

bool Game2D::AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr)
{
	DEBUG_PRINTF_A("Game2D::AddGameObject()\n");

	if (_gameObjectPtr == nullptr)
		return false;

	m_GameObjectVector.push_back(_gameObjectPtr);
	return true;
}

void Game2D::OnWindowResize(WPARAM _wParam, UINT _width, UINT _height)
{
	// Reisze the Direct2D render target.
	//m_WindowWidth = _width;
	//m_WindowHeight = _height;
}

void Game2D::Update()
{
	//DEBUG_PRINTF_A("Game2D::Update()\n");

	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		m_GameObjectVector[i]->Update(MICROSECONDS_PER_UPDATE);
	}
}

void Game2D::Render(LONGLONG _lagTime)
{
	if (m_D2DFactoryPtr == nullptr || m_WindowHandle == NULL)
		return; // The game is not initialized.

	// Get the Direct2D render target.
	// A render target may not exist if it's the first render or if EndDraw() returned D2DERR_RECREATE_TARGET.
	if (m_D2DRenderTargetPtr == nullptr)
	{
		// Create a Direct2D render target if it doesn't exist.
		ID2D1HwndRenderTarget* renderTargetPtr = NULL;
		HRESULT hr = m_D2DFactoryPtr->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(), // Creates a structure with default values specifying the properties of the render target.
			D2D1::HwndRenderTargetProperties(m_WindowHandle),
			&renderTargetPtr
		);
		if (hr != S_OK)
			return;

		m_D2DRenderTargetPtr = renderTargetPtr;
	}

	// Get the brushes
	if (m_D2DBlackBrushPtr == nullptr)
	{
		// Create a Brush.
		ID2D1SolidColorBrush* d2dBlackBrushPtr = CreateD2DBrush(m_D2DRenderTargetPtr, D2D1::ColorF(D2D1::ColorF::Black));
		if (d2dBlackBrushPtr == nullptr)
			return;

		m_D2DBlackBrushPtr = d2dBlackBrushPtr;
	}

	if (m_D2DGreenBrushPtr == nullptr)
	{
		ID2D1SolidColorBrush* d2dGreenBrushPtr = CreateD2DBrush(m_D2DRenderTargetPtr, D2D1::ColorF(D2D1::ColorF::Green));
		if (d2dGreenBrushPtr == nullptr)
			return;

		m_D2DGreenBrushPtr = d2dGreenBrushPtr;
	}

	// TODO: Find out how to get window size right after window creation.
	RECT rect;
	GetClientRect(m_WindowHandle, &rect);

	D2D1_SIZE_U size;
	size.width = rect.right - rect.left;
	size.height = rect.bottom - rect.top;
	m_D2DRenderTargetPtr->Resize(size);

	m_D2DRenderTargetPtr->BeginDraw();
	m_D2DRenderTargetPtr->Clear(D2D1::ColorF(D2D1::ColorF::LightGray));

	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		GameObject2D* gameObject2DPtr = m_GameObjectVector[i].get();

		// Get simulated information from a 2D game object and render it.
		double x, y;
		gameObject2DPtr->SimulatePos(_lagTime, x, y);

		// Draw the Circle.
		D2D1_ELLIPSE playerCircle = D2D1::Ellipse(D2D1::Point2F((float)x, (float)y), 47.5f, 47.5f);
		m_D2DRenderTargetPtr->DrawEllipse(
			playerCircle,
			m_D2DBlackBrushPtr,
			5.0f);
		m_D2DRenderTargetPtr->FillEllipse(
			playerCircle,
			m_D2DGreenBrushPtr);
		{
			//// Draw the Rectangle.
			//renderTargetPtr->DrawRectangle(
			//	D2D1::RectF(
			//		rect.left + 100,
			//		rect.top + 100,
			//		rect.right - 100,
			//		rect.bottom - 100),
			//		m_BrushPtr);
		}
	}

	HRESULT hr = m_D2DRenderTargetPtr->EndDraw();
	if (hr != S_OK)
	{
		if (hr == D2DERR_RECREATE_TARGET)
		{
			ReleaseD2DRenderTarget();
		}
	}
}


void Game2D::OnTerminate()
{
	// Since it is not an object created by new, delete should not be used, and should call Release() to release the resource.
	if (m_D2DFactoryPtr != nullptr)
	{
		m_D2DFactoryPtr->Release();
		m_D2DFactoryPtr = nullptr;
	}

	ReleaseD2DRenderTarget();
}

void Game2D::ReleaseD2DRenderTarget()
{
	if (m_D2DRenderTargetPtr != nullptr)
	{
		m_D2DRenderTargetPtr->Release();
		m_D2DRenderTargetPtr = nullptr;
	}

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

ID2D1SolidColorBrush* Game2D::CreateD2DBrush(ID2D1HwndRenderTarget* _renderTargetPtr, CONST D2D1_COLOR_F& _colorF)
{
	// Create a Brush.
	ID2D1SolidColorBrush* d2dBrushPtr = NULL;
	HRESULT hr = _renderTargetPtr->CreateSolidColorBrush(_colorF, &d2dBrushPtr
	);
	if (hr != S_OK)
		return nullptr;

	return d2dBrushPtr;
}
