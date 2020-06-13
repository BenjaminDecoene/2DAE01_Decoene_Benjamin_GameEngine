#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "SpriteComponent2D.h"
#include "AudioManager.h"
#include "Player.h"
#include "Wall.h"

TestScene::TestScene(const std::string& name)
	:Scene(name)
{
	AudioManager::GetInstance().LoadSound("death.mp3");

	//	make the background
	auto background = new Object();
	background->SetPosition(GameInfo::GetWindowSize().x / 2, GameInfo::GetWindowSize().y / 2);
	background->AddComponent(new TextureComponent2D(background, "background.jpg", GameInfo::GetWindowSize()));
	Add(background);

	//	make the player
	auto player = new Player({75.f, 500.f});
	
	//	make sprite component
	const auto sprite = new SpriteComponent2D(player, "BBSprites/Sprites0.png", {100, 100}, 16, 8, 8, 0, 16);

	//	make physx component
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	
	auto physx = new PhysxComponent(player, GetWorld(), bodyDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox((50 / ppm), (50  / ppm));
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &boxShape;
	fixtureDef->density = 100.0f;
	fixtureDef->friction = 0.7f;
	fixtureDef->restitution = 0.3f;

	physx->AddFixture(fixtureDef);

	
	player->Init(sprite, physx, 10);
	
	Add(player);

	AudioManager::GetInstance().AddEvent("PlayerUp", [](){AudioManager::GetInstance().PlaySound("death.mp3");});

	//	make some walls
	auto wall = new Wall({200, 50});

	wall->Init("brick.jpg", {400, 100}, this);
	Add(wall);
}
