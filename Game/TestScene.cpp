#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Entity.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "SpriteComponent2D.h"
#include "InputManager.h"

TestScene::TestScene(const std::string& name)
	:Scene(name)
{
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = new dae::TextObject("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	Add(to);

	auto gameObject2 = new Entity();
	gameObject2->SetPosition(75.f, 500.f);
	//	add sprite component
	gameObject2->AddComponent(new SpriteComponent2D(gameObject2, "BBSprites/Sprites0.png", {100, 100}, 16, 8, 8, 0, 16));

	//	add collider component
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	auto bodyDef = new b2BodyDef() ;
	bodyDef->type = b2_dynamicBody;
	
	auto collider = new PhysxComponent(gameObject2, GetWorld(), bodyDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox((50 / ppm), (50  / ppm));
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &boxShape;
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 0.7f;
	fixtureDef->restitution = 0.3f;

	collider->AddFixture(fixtureDef);

	//b2CircleShape circleShape;
	//circleShape.m_radius = 100 / ppm;
	//circleShape.m_p = b2Vec2(0 / ppm, 75 / ppm) ;
	//const auto fixtureDefCircle = new b2FixtureDef();
	//fixtureDefCircle->shape = &circleShape;
	//fixtureDefCircle->density = 1.0f;
	//fixtureDefCircle->friction = 0.8f;
	//fixtureDefCircle->restitution = 0.3f;

	//collider->AddFixture(fixtureDefCircle);
	
	gameObject2->AddComponent(collider);
	
	dae::InputManager::GetInstance().BindCommand(dae::ControllerButton::KeyD, 
		std::make_unique<CommandFunction>(
			nullptr,
			[gameObject2](){gameObject2->GetComponent<PhysxComponent>()->SetDesiredVelocity({30,0});},
			[gameObject2](){gameObject2->SetVelocity({0, 0});}));

	dae::InputManager::GetInstance().BindCommand(dae::ControllerButton::keyA, 
		std::make_unique<CommandFunction>(
			nullptr,
			[gameObject2](){gameObject2->GetComponent<PhysxComponent>()->SetDesiredVelocity({-30,0});},
			[gameObject2](){gameObject2->SetVelocity({0, 0});}));

	dae::InputManager::GetInstance().BindCommand(dae::ControllerButton::KeyW, 
		std::make_unique<CommandFunction>(
			nullptr,
			[gameObject2](){gameObject2->GetComponent<PhysxComponent>()->SetDesiredVelocity({0,20});},
			[gameObject2](){gameObject2->SetVelocity({0, 0});}));

	dae::InputManager::GetInstance().BindCommand(dae::ControllerButton::KeyS, 
		std::make_unique<CommandFunction>(
			nullptr,
			[gameObject2](){gameObject2->GetComponent<PhysxComponent>()->SetDesiredVelocity({0,-50});},
			[gameObject2](){gameObject2->SetVelocity({0, 0});}));
	
	Add(gameObject2);
}
