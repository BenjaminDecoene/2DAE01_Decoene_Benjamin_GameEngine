#include "pch.h"
#include "GameStats.h"

void GameStats::Notify(const Object&, const std::string& event)
{
	if(event == "Emerald")
	{
		m_EmStreak++;
		if(m_EmStreak == 8)
		{
			m_EmStreak = 0;
			m_Score += 250;
		}
		else
			m_Score += 25;
	}
	else if(event == "Dirt")
	{
		m_EmStreak = 0;
	}
	else if(event == "EnemyKilled")
	{
		m_Score += 250;		
	}
}
