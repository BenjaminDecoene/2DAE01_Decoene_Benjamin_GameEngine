#include "pch.h"
#include "Player.h"

Player::Player(const b2Vec2& pos)
	:Object()
	,m_Velocity({{0.f, 0.f}, 5.f})
{
	m_Transform.SetPosition(pos);
}
