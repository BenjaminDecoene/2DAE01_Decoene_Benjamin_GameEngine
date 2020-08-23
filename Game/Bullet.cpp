#include "pch.h"
#include "Bullet.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "SceneManager.h"
#include "Scene.h"

Bullet::Bullet(const b2Vec2& pos, float direction)
	:Object()
	,m_Vel({float(cos(direction * M_PI / 180)), -float(sin(direction * M_PI / 180))})
	,m_Speed{3}
{
	m_Transform.SetPosition(pos + 30 * m_Vel);
	//	Add texture
	AddComponent(new TextureComponent2D(this, "Bullet.png",{20, 20}));

	//	Add physx component
	const float ppm = GameInfo::GetInstance().GetPPM();

	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->gravityScale = 0;
	bodyDef->linearVelocity = m_Speed * m_Vel;
	
	auto physx = new PhysxComponent(this, SceneManager::GetInstance().GetScene().GetWorld(), bodyDef);
	
	b2CircleShape shape;
	shape.m_radius = 5 / ppm;
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &shape;
	fixtureDef->density = 1.f;

	physx->AddFixture(fixtureDef);

	AddComponent(physx);
}