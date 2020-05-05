#pragma once
#include "Singleton.h"

class Time : public dae::Singleton<Time>
{
public:
	void Update(float elapsedTime);

	float GetElapsedTime() const { return m_ElapsedTime; }
	float GetTotalTime() const { return m_TotalTime; }
	float GetFps() const { return 1 / m_ElapsedTime; }
	bool GetIsNewSecond() const { return m_IsNewSecond; }
private:
	
	float m_ElapsedTime = 0;
	float m_TotalTime = 0;
	int m_IsNewSecond = false;
};