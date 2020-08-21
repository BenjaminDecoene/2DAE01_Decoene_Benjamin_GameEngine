#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(const b2Vec2& pos);

	void SetVelocity(const b2Vec2& velocity) { m_Velocity.v = velocity; }
	const b2Vec2& GetVelocity() const { return m_Velocity.v; }
private:
	b2Velocity m_Velocity;
};
