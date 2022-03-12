#pragma once

#include <cmath>


namespace Util
{
	template<class _Ty>
	bool IsValidNumber(const _Ty& _x)
	{
		return !isnan(_x) && !isinf(_x);
	}

}
