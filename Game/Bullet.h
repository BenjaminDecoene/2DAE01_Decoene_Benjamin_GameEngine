#pragma once
#include <Object.h>
class Bullet : public Object
{
public:
	Bullet(const b2Vec2& pos, float direction);
private:
	b2Vec2 m_Vel;
	float m_Speed;
};