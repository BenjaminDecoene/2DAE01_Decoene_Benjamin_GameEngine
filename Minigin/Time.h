#pragma once
#include "Singleton.h"

class Time : public dae::Singleton<Time>
{
public:
	void SetMsPerFrame(int msPerFrame) { m_MsPerFrame = msPerFrame; }
	void Update();

	float GetTotalTime() const { return m_TotalTime; }
	bool GetIsNewSecond() const { return m_IsNewSecond; }
	
	int GetMsPerFrame() const { return m_MsPerFrame; }
private:
	int m_MsPerFrame = 0;
	float m_TotalTime = 0;
	bool m_IsNewSecond = false;
	unsigned int m_LastSec = 0;
};