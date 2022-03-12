#include "Timer.h"


Timer::Timer()
{
	// TODO_LATER: Support for hardware that does not support QPC
	QueryPerformanceFrequency(&m_Frequency);
	Reset();
}

Timer::~Timer()
{

}


void Timer::Reset()
{
	QueryPerformanceCounter(&m_StartingTime);
}

LONGLONG Timer::GetMilliseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	LONGLONG elapsedMicroseconds;
	elapsedMicroseconds = (perfomanceCount.QuadPart - m_StartingTime.QuadPart);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	elapsedMicroseconds *= 1000;
	elapsedMicroseconds /= m_Frequency.QuadPart;

	return elapsedMicroseconds;
}

LONGLONG Timer::GetMicroseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	LONGLONG elapsedMicroseconds;
	elapsedMicroseconds = (perfomanceCount.QuadPart - m_StartingTime.QuadPart);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	elapsedMicroseconds *= 1000000;
	elapsedMicroseconds /= m_Frequency.QuadPart;

	return elapsedMicroseconds;
}

LONGLONG Timer::GetNanoseconds()
{
	LARGE_INTEGER perfomanceCount;
	QueryPerformanceCounter(&perfomanceCount);

	LONGLONG elapsedNanoseconds;
	elapsedNanoseconds = (perfomanceCount.QuadPart - m_StartingTime.QuadPart);

	// To guard against loss-of-precision, we convert to microseconds *before* dividing by ticks-per-second.
	elapsedNanoseconds *= 1000000000;
	elapsedNanoseconds /= m_Frequency.QuadPart;

	return elapsedNanoseconds;
}
