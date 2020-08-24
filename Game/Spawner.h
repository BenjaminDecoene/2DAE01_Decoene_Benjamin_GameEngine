#pragma once
class Spawner
{
public:
	Spawner(UINT nrEnemies, float timeBetween, const b2Vec2& pos);
	//	returns true if an enemy has to be spawned
	bool Update();

	bool GetIsDone() const { return m_IsDone; }
	const b2Vec2& GetPos() const { return m_Pos; }
private:
	UINT m_NrEnemies;
	float m_TimeBetween;
	b2Vec2 m_Pos;

	float m_TimeLeft;
	UINT m_EnemyIdx;
	bool m_IsDone;
};

