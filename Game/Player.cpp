#include "pch.h"
#include "Player.h"
#include "TextureComponent2D.h"

Player::Player(const b2Vec2& pos)
	:Object()
	,m_Velocity({{0.f, 0.f}, 150.f})
	,m_DigOffset(10.f)
{
	m_Transform.SetPosition(pos);

	AddComponent(new TextureComponent2D(this, "Digger.png", {40, 40}));
}

b2Vec2 Player::GetDigPoint() const
{
	b2Vec2 offsetRotated;
	offsetRotated.x = m_DigOffset * float(cos(m_Rotation * M_PI / 180));
	offsetRotated.y = -m_DigOffset * float(sin(m_Rotation * M_PI / 180));
	
	return m_Transform.GetPosition() + offsetRotated;
}

void Player::Update()
{
	Object::Update();

	const auto oldPos = m_Transform.GetPosition();
	const auto newPos = oldPos + (GameInfo::GetElapsedSec() * m_Velocity.w * m_Velocity.v);
	m_Transform.SetPosition(newPos);
	
	UpdateRotation();
}

void Player::UpdateRotation()
{
	auto vel = m_Velocity.v;

	//	if standing still dont change rotation
	if(vel.x == 0 && vel.y == 0)
		return;

	//	set the rotation
	m_Rotation = -float(atan2(vel.y, vel.x) * (180.f / M_PI));
}
