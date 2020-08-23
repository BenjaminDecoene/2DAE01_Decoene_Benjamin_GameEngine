#include "pch.h"
#include "Player.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Bullet.h"
#include "BulletManager.h"

Player::Player(const b2Vec2& pos)
	:Object()
	,m_Velocity({{0.f, 0.f}, 2.f})
	,m_DigOffset(10.f)
	,m_pBulletManager(nullptr)
{
	m_Transform.SetPosition(pos);

	AddComponent(new TextureComponent2D(this, "Digger.png", {40, 40}));

	//	make physx component
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->gravityScale = 0;

	auto physx = new PhysxComponent(this, SceneManager::GetInstance().GetScene().GetWorld(), bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox((20 / ppm), (20  / ppm));
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &boxShape;
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 0.7f;
	fixtureDef->restitution = 0.3f;

	physx->AddFixture(fixtureDef);
	
	AddComponent(physx);
}

void Player::Shoot() const
{
	m_pBulletManager->AddBullet(m_Transform.GetPosition(), m_Rotation);
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

	GetComponent<PhysxComponent>()->SetVelocity(m_Velocity.w * m_Velocity.v);
	
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
