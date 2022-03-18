#include "Game2D.h"
#include "Debug.h"

#pragma comment(lib, "d2d1")


Game2D::Game2D() : m_D2DFactoryPtr(nullptr), m_D2DRenderTargetPtr(nullptr), m_BrushPtr(nullptr)
{
	m_Width = 0;
	m_Height = 0;
	DEBUG_PRINTF_A("Game2D::Game2D()\n");
}

Game2D::~Game2D()
{
	DEBUG_PRINTF_A("Game2D::~Game2D()\n");

	if (m_D2DFactoryPtr != nullptr)
	{
		m_D2DFactoryPtr->Release();
		m_D2DFactoryPtr = nullptr;
	}

	if (m_D2DRenderTargetPtr != nullptr)
	{
		m_D2DRenderTargetPtr->Release();
		m_D2DRenderTargetPtr = nullptr;
	}

	if (m_BrushPtr != nullptr)
	{
		m_BrushPtr->Release();
		m_BrushPtr = nullptr;
	}
}


bool Game2D::Init(WNDCLASSW* _pWndClass, LPCWSTR _wndName, int _nShowCmd)
{
	if (false == Game::Init(_pWndClass, _wndName, _nShowCmd))
		return false;

	if (m_D2DFactoryPtr == nullptr)
	{
		// Create an ID2D1Factory.
		ID2D1Factory* d2dFactoryPtr = NULL;
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&d2dFactoryPtr
		);
		if (hr != S_OK)
			return false;

		m_D2DFactoryPtr = d2dFactoryPtr;
	}

	if (m_D2DRenderTargetPtr == nullptr)
	{
		// Create a Direct2D render target.
		ID2D1HwndRenderTarget* renderTargetPtr = NULL;
		HRESULT hr = m_D2DFactoryPtr->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(), // Creates a structure with default values specifying the properties of the render target.
			D2D1::HwndRenderTargetProperties(m_WindowHandle),
			&renderTargetPtr
		);
		if (hr != S_OK)
			return false;

		m_D2DRenderTargetPtr = renderTargetPtr;
	}
	
	if (m_BrushPtr == nullptr)
	{
		// Create a Brush.
		ID2D1SolidColorBrush* brushPtr = NULL;
		HRESULT hr = m_D2DRenderTargetPtr->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&brushPtr
		);
		if (hr != S_OK)
			return false;

		m_BrushPtr = brushPtr;
	}

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

void Game2D::OnResize(WPARAM _wParam, UINT _width, UINT _height)
{
	// Reisze the Direct2D render target.
	m_Width = _width;
	m_Height = _height;
}

void Game2D::Update()
{
	//DEBUG_PRINTF_A("Game2D::Update()\n");
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		m_GameObjectVector[i]->Update(MICROSECONDS_PER_UPDATE);
	}
}

void Game2D::Render(LONGLONG _microSeconds)
{
	// TODO: Change the structure so that it must be initialized before Render is called.
	if (m_D2DRenderTargetPtr == nullptr || m_BrushPtr == nullptr)
		return;

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
		GameObject2D* gameObjectPtr = m_GameObjectVector[i].get();

		// Get information from a 2D game object and render it.
		double x = gameObjectPtr->GetX();
		double y = gameObjectPtr->GetY();
		double speed = gameObjectPtr->GetSpeed();

		// Draw the Circle.
		m_D2DRenderTargetPtr->DrawEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(x, y),
				50.0f, 50.0f),
			m_BrushPtr,
			1.0f);
		{
			//// Draw the Rectangle.
			//m_D2DRenderTargetPtr->DrawRectangle(
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
		hr = S_OK;
	}
}
