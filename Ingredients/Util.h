#pragma once

#include <cmath>
#include <d2d1.h>


namespace Util
{
	template<class _Ty>
	bool IsValidNumber(const _Ty& _x)
	{
		return !isnan(_x) && !isinf(_x);
	}

	// Temporary
	ID2D1SolidColorBrush* CreateD2DBrush(ID2D1HwndRenderTarget* _renderTargetPtr, CONST D2D1_COLOR_F& _colorF);
}
