#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Entity.h"
#include "TextureComponent2D.h"
#include "ColliderComponent.h"
#include "SpriteComponent2D.h"

TestScene::TestScene(const std::string& name)
	:Scene(name)
{
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = new dae::TextObject("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	Add(to);

	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	auto bodyDef = new b2BodyDef() ;
	bodyDef->type = b2_dynamicBody;

	auto gameObject2 = new Entity();
	gameObject2->AddComponent(new SpriteComponent2D(gameObject2, "BBSprites/Sprites0.png", {100, 100}, 16, 8, 4, 8, 24));
	//gameObject->SetVelocity({0,5,0});
	auto collider = new ColliderComponent(gameObject2, GetWorld(), {75, 500}, {50,50}, bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox((50 / ppm), (50  / ppm));
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &boxShape;
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 0.3f;
	fixtureDef->restitution = 0.3f;

	collider->AddFixture(fixtureDef);
	
	gameObject2->AddComponent(collider);
	
	
	Add(gameObject2);
}
