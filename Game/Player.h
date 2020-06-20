#pragma once
#include "State.h"
#include "Animator.h"
#include "Object.h"

class PhysxComponent;
class SpriteComponent2D;
class StateMachine;

class Player : public Object
{
public:
	Player(const b2Vec2& pos);
	void Init(PhysxComponent* physx);
	void Update() override;
	Animator& GetAnimator() { return m_Animator; }
	bool GetLookDirection() const{ return m_LookRight; }
	void SetLookDirection(bool isRight) { m_LookRight = isRight; }
private:
	StateMachine* m_StateMachine;
	Animator m_Animator;
	bool m_LookRight = true;
};

//	playerStates
class PlayerIdle : public State
{
public:
	PlayerIdle(Player* player) : m_pPlayer(player){}
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
private:
	Player* m_pPlayer;
};

class PlayerMove : public State
{
public:
	PlayerMove(Player* player) : m_pPlayer(player){}
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
private:
	Player* m_pPlayer;
};

class PlayerShoot : public State
{
public:
	PlayerShoot(Player* player) : m_pPlayer(player){}
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
private:
	Player* m_pPlayer;
};