#include "pch.h"
#include "Spawner.h"

Spawner::Spawner(UINT nrEnemies, float timeBetween, const b2Vec2& pos)
	:m_NrEnemies(nrEnemies)
	,m_TimeBetween(timeBetween)
	,m_Pos(pos)
	,m_EnemyIdx(0)
	,m_TimeLeft(0)
	,m_IsDone(false)
{
	m_TimeLeft = m_TimeBetween;
}

bool Spawner::Update()
{
	//	Check if all enemies are spawned
	if(m_EnemyIdx == m_NrEnemies)
	{
		m_IsDone = true;
		return false;
	}
	//	if time to spawn an enemy return true and reset the timer, incr enemy idx
	if(m_TimeLeft < 0)
	{
		m_TimeLeft = m_TimeBetween;
		m_EnemyIdx++;
		return true;
	}
	m_TimeLeft -= GameInfo::GetElapsedSec();
	return false;
}
