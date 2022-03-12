#pragma once

#include <Windows.h>


class Timer
{
public:
	Timer();
	virtual ~Timer();

private:
	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_StartingTime;

public:
	void Reset();
	LONGLONG GetMilliseconds();
	LONGLONG GetMicroseconds();
	LONGLONG GetNanoseconds();
};
