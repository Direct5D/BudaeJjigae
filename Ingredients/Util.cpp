#include "Util.h"


namespace Util
{
	// Temporary
	ID2D1SolidColorBrush* CreateD2DBrush(ID2D1HwndRenderTarget* _renderTargetPtr, CONST D2D1_COLOR_F& _colorF)
	{
		// Create a Brush.
		ID2D1SolidColorBrush* d2dBrushPtr = NULL;
		HRESULT hr = _renderTargetPtr->CreateSolidColorBrush(_colorF, &d2dBrushPtr
		);
		if (hr != S_OK)
			return nullptr;

		return d2dBrushPtr;
	}
}
