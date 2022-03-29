#include "Game2D.h"
#include "Debug.h"
#include "Util.h"

#pragma comment(lib, "d2d1")


Game2D::Game2D()
{
	DEBUG_PRINTF_A("0x%p Game2D::Game2D()\n", this);
}

Game2D::~Game2D()
{
	DEBUG_PRINTF_A("0x%p Game2D::~Game2D()\n", this);
}


bool Game2D::AddGameObject(std::shared_ptr<GameObject2D> _gameObjectPtr)
{
	DEBUG_PRINTF_A("0x%p Game2D::AddGameObject() ptr = 0x%p\n", this, _gameObjectPtr.get());

	if (_gameObjectPtr == nullptr)
		return false;

	m_GameObjectVector.push_back(_gameObjectPtr);
	return true;
}

void Game2D::ReleaseD2DRenderTarget()
{
	DEBUG_PRINTF_A("0x%p Game2D::ReleaseD2DRenderTarget()\n", this);

	if (m_D2DRenderTargetPtr != nullptr)
	{
		m_D2DRenderTargetPtr->Release();
		m_D2DRenderTargetPtr = nullptr;
	}

	ReleaseD2DResources();
}


//void Game2D::OnWindowResize(WPARAM _wParam, UINT _width, UINT _height)
//{
//	// Stores the size of the window.
//	m_WindowWidth = _width;
//	m_WindowHeight = _height;
//}

void Game2D::RenderD2D(LONGLONG _lagTime)
{
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		GameObject2D* gameObject2DPtr = m_GameObjectVector[i].get();

		// Get simulated information from a 2D game object and render it.
		// TODO: Copying game objects for every simulation is inefficient. Structural change is required.
		GameObject2D* simulatedObject2DPtr = (GameObject2D*)gameObject2DPtr->Simulate(_lagTime);

		// TODO: Change object rendering order based on simulation results.
		
		simulatedObject2DPtr->Render(m_D2DRenderTargetPtr);

		delete simulatedObject2DPtr;
	}
}


bool Game2D::OnInit()
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

	return true;
}

void Game2D::FixedUpdate()
{
	//DEBUG_PRINTF_A("0x%p Game2D::FixedUpdate()\n", this);

	size_t objectCount = m_GameObjectVector.size();
	for (size_t i = 0; i < objectCount; ++i)
	{
		// Update only on valid objects.
		if (true == m_GameObjectVector[i]->GetValid())
			m_GameObjectVector[i]->Update(MICROSECONDS_PER_UPDATE);
	}

	// After the traversal is complete, the invalid objects are removed in batches.
	// TODO: Find out if there is a more efficient way.
	// TODO: Make sure the game object is destroyed correctly. (Easy way to check: Debugging destructors)
	std::vector<std::shared_ptr<GameObject2D>> tmpGameObjectVector;
	for (size_t i = 0; i < m_GameObjectVector.size(); ++i)
	{
		// Get only valid objects.
		if (true == m_GameObjectVector[i]->GetValid())
			tmpGameObjectVector.push_back(m_GameObjectVector[i]); // Initialization using the copy constructor occurs internally.
	}
	m_GameObjectVector = tmpGameObjectVector;
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

	// TODO: Find out how to get window size right after window creation.
	RECT rect;
	GetClientRect(m_WindowHandle, &rect);

	D2D1_SIZE_U size;
	size.width = rect.right - rect.left;
	size.height = rect.bottom - rect.top;
	m_D2DRenderTargetPtr->Resize(size);

	m_D2DRenderTargetPtr->BeginDraw();
	m_D2DRenderTargetPtr->Clear(D2D1::ColorF(D2D1::ColorF::LightGray));

	RenderD2D(_lagTime);

	HRESULT hr = m_D2DRenderTargetPtr->EndDraw();
	if (hr != S_OK)
	{
		if (hr == D2DERR_RECREATE_TARGET)
		{
			// TODO: Also releases the resources for the render target.
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
