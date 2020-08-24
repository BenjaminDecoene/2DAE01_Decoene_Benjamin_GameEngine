#pragma once
#include <Object.h>
#include "StateMachine.h"
#include "State.h"

class Map;
class Tile;

class Enemy : public Object
{
public:
	Enemy(Map* map, const b2Vec2& pos);
	~Enemy();

	void Update() override;
	bool UpdateTarget();
	bool UpdateMoveToTarget();

	void Kill();
	void HitPlayer();
	bool GetIsDead() const { return m_IsDead; }
private:
	void InitStateMachine();
	
	Map* m_pMap;
	Tile* m_LastTile;
	b2Vec2 m_Target;
	StateMachine m_StateMachine;
	bool m_IsDead = false;
};

class SeekTarget : public State
{
public:
	SeekTarget(Enemy* enemy) : m_pEnemy{enemy}{}
private:
	void Update(StateMachine* stateMachine) override;
	Enemy* m_pEnemy;
};

class MoveToTarget : public State
{
public:
	MoveToTarget(Enemy* enemy) : m_pEnemy{enemy}{}
private:
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
	
	Enemy* m_pEnemy;
	float m_MaxTime = 0.8f;
	float m_Timer = 0.f;
};