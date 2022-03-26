#include "Timer.h"
#include "Debug.h"


Timer::Timer()
{
	DEBUG_PRINTF_A("0x%p Timer::Timer()\n", this);
	// TODO_LATER: Support for hardware that does not support QPC
	QueryPerformanceFrequency(&m_Frequency);
	Reset();
}

Timer::~Timer()
{
	DEBUG_PRINTF_A("0x%p Timer::~Timer()\n", this);
}


void Timer::Reset()
{
	QueryPerformanceCounter(&m_StartingTime);
}

LONGLONG Timer::GetMilliseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	return (perfomanceCount.QuadPart * 1000) / m_Frequency.QuadPart;
}

LONGLONG Timer::GetMicroseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	return (perfomanceCount.QuadPart * 1000000) / m_Frequency.QuadPart;
}

LONGLONG Timer::GetNanoseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	return (perfomanceCount.QuadPart * 1000000000) / m_Frequency.QuadPart;
}

LONGLONG Timer::GetElapsedMilliseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	return ((perfomanceCount.QuadPart - m_StartingTime.QuadPart) * 1000) / m_Frequency.QuadPart;
}

LONGLONG Timer::GetElapsedMicroseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	return ((perfomanceCount.QuadPart - m_StartingTime.QuadPart) * 1000000) / m_Frequency.QuadPart;
}

LONGLONG Timer::GetElapsedNanoseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	return ((perfomanceCount.QuadPart - m_StartingTime.QuadPart) * 1000000000) / m_Frequency.QuadPart;
}
