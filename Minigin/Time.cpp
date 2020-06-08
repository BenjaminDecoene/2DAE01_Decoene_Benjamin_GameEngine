#include "pch.h"
#include "Time.h"

void Time::Update()
{
	m_TotalTime += float(GameInfo::GetInstance().GetMsPerFrame() / 1000.f);

	//	check if a new second started
	if(m_LastSec < unsigned int(m_TotalTime))
	{
		m_IsNewSecond = true;
		m_LastSec = unsigned int(m_TotalTime);
	}
	else
		m_IsNewSecond = false;
}