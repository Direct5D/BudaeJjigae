#pragma once

#include <Windows.h>


namespace Bujji
{
	class Timer
	{
	public:
		Timer();
		virtual ~Timer();

		void Reset();
		LONGLONG GetMilliseconds();
		LONGLONG GetMicroseconds();
		LONGLONG GetNanoseconds();

	private:
		LARGE_INTEGER m_Frequency;
		LARGE_INTEGER m_StartingTime;
	};
}
