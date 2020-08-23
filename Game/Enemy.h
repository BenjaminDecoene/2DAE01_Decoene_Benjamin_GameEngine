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

	void Update() override;
	bool UpdateTarget();
	bool UpdateMoveToTarget();
private:
	void InitStateMachine();
	
	Map* m_pMap;
	Tile* m_LastTile;
	b2Vec2 m_Target;
	StateMachine m_StateMachine;
};

class SeekTarget : public State
{
public:
	SeekTarget(Enemy* enemy) : m_pEnemy{enemy}{}
	void Update(StateMachine* stateMachine) override;
private:
	Enemy* m_pEnemy;
};

class MoveToTarget : public State
{
public:
	MoveToTarget(Enemy* enemy) : m_pEnemy{enemy}{}
	void Update(StateMachine* stateMachine) override;
private:
	Enemy* m_pEnemy;	
};