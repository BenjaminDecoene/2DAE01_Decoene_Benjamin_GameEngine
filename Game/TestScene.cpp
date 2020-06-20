#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "AudioManager.h"
#include "Player.h"
#include "Wall.h"
#include "Bullet.h"
#include "SceneManager.h"

TestScene::TestScene(const std::string& name)
	:Scene(name)
{
	//	load sound effect
	AudioManager::GetInstance().LoadSound("shoot.wav");
	AudioManager::GetInstance().AddEvent("Shoot", [](){AudioManager::GetInstance().PlaySound("shoot.wav");});
	AudioManager::GetInstance().LoadSound("theme.mp3");
	AudioManager::GetInstance().SetVolume("theme.mp3", 50);	
	AudioManager::GetInstance().PlaySound("theme.mp3");
	
	//	make the player
	auto player = new Player({75.f, 500.f});

	//	make physx component
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	
	auto physx = new PhysxComponent(player, GetWorld(), bodyDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox((35 / ppm), (35  / ppm));
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &boxShape;
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 0.7f;
	fixtureDef->restitution = 0.3f;

	physx->AddFixture(fixtureDef);

	player->Init(physx);
	
	Add(player);

	const auto windowSize = GameInfo::GetInstance().GetWindowSize();
	
	//	make walls for level
	auto wall0 = new Wall({10, windowSize.y / 2});

	wall0->Init("brick.jpg", {30, windowSize.y}, this);
	Add(wall0);

	//	make walls for level
	auto wall1 = new Wall({windowSize.x - 10, windowSize.y / 2});

	wall1->Init("brick.jpg", {30, windowSize.y}, this);
	Add(wall1);

	auto wall2 = new Wall({windowSize.x / 2, windowSize.y - 15});

	wall2->Init("brick.jpg", {windowSize.x, 30}, this);
	Add(wall2);

	auto wall3 = new Wall({150, 15});

	wall3->Init("brick.jpg", {300, 30}, this);
	Add(wall3);

	//	walls that should only collide when player is falling
	auto wall4 = new Wall({windowSize.x - 150, 15});

	wall4->Init("brick.jpg", {300, 30}, this);
	Add(wall4);

	auto wall5 = new Wall({250, 200});

	wall5->Init("brick.jpg", {150, 30}, this);
	Add(wall5);

	auto wall6 = new Wall({550, 200});

	wall6->Init("brick.jpg", {150, 30}, this);
	Add(wall6);

	auto wall7 = new Wall({400, 350});

	wall7->Init("brick.jpg", {500, 30}, this);
	Add(wall7);

	auto wall8 = new Wall({400, 500});

	wall8->Init("brick.jpg", {500, 30}, this);
	Add(wall8);
}