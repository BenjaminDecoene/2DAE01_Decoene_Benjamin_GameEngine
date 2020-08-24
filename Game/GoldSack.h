#pragma once
#include <Object.h>
#include "StateMachine.h"
#include "State.h"

class Map;

class GoldSack : public Object
{
public:
	GoldSack(Map* map, const b2Vec2& pos);

	void Update() override;

	void Destroy() { m_Destroyed = true; }
	bool GetDestroyed() const { return m_Destroyed; }
	bool IsFalling() const { return m_Falling; }
	void SetFalling(bool falling) { m_Falling = falling; }
	bool IsStable() const;
	void SetTorn(bool torn) { m_Torn = torn; }
	bool IsTorn() const { return m_Torn; }
private:
	void InitStateMachine();
	Map* m_pMap;
	bool m_Falling;
	bool m_Torn;
	bool m_Destroyed;
	StateMachine m_StateMachine;

	float m_FallingDelay;
	float m_FallingDelayTimer;
};

class Stable : public State
{
public:
	Stable(GoldSack* goldSack);
private:
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
	GoldSack* m_pGoldSack;
	float m_FallingDelay;
	float m_FallingDelayTimer;
};

class Falling : public State
{
public:
	Falling(GoldSack* goldSack) :m_pGoldSack(goldSack){}
private:
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
	float m_TimeFalling = 0.f;
	float m_TimeBeforeTorn = 0.5f;
	GoldSack* m_pGoldSack;
};

class Torn : public State
{
public:
	Torn(GoldSack* goldSack) :m_pGoldSack(goldSack){}
private:
	void OnEntry() override;
	void Update(StateMachine* stateMachine) override;
	GoldSack* m_pGoldSack;
};
