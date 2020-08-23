#pragma once
#include <Object.h>
class Bullet : public Object
{
public:
	Bullet(const b2Vec2& pos, float direction);

	void Hit() { m_Hit = true; }
	bool GetIsHit() const { return m_Hit; }
private:
	b2Vec2 m_Vel;
	float m_Speed;
	bool m_Hit = false;
};