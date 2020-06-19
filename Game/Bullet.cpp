#include "pch.h"
#include "Bullet.h"
#include "SpriteComponent2D.h"
#include "PhysxComponent.h"
#include "Scene.h"

Bullet::Bullet(const b2Vec2& pos, bool goRight, Scene* scene)
	:m_GoRight(goRight)
{
	//	set pos
	if(goRight)
	{
		SetPosition(pos.x + 10, pos.y);		
	}
	else
		SetPosition(pos.x - 10, pos.y);	
	
	//	make sprite
	const auto sprite = new SpriteComponent2D(this, "BBSprites/char_shoot.png", {40, 40}, 5, 8, 16, 32, 40);
	sprite->PlayLoop();
	AddComponent(sprite);

	//	make physx component
	const float ppm = GameInfo::GetInstance().GetPPM();

	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	
	auto physx = new PhysxComponent(this, scene->GetWorld(), bodyDef);
	
	b2CircleShape shape;
	shape.m_radius = 20 / ppm;
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &shape;
	fixtureDef->density = 1.f;

	physx->AddFixture(fixtureDef);

	physx->SetFixedRotation(true);

	AddComponent(physx);
}

void Bullet::Update()
{
	Object::Update();
	
	const auto physx = GetComponent<PhysxComponent>();

	//	set velocity
	if(m_GoRight)
		physx->SetDesiredVelocity({10, 9.81f});
	else
		physx->SetDesiredVelocity({-10, 9.81f});

	////	if touched delete
	//if(physx->IsTouching())
	//	Manager
}