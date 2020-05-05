#include "MiniginPCH.h"
#include "Time.h"

void Time::Update(float elapsedTime)
{
	m_ElapsedTime = elapsedTime;
	m_TotalTime += elapsedTime;

	if(int(m_TotalTime - elapsedTime) < int(m_TotalTime))
		m_IsNewSecond = true;
	else
		m_IsNewSecond = false;
}