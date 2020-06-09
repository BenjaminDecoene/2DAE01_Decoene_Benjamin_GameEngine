#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Entity.h"
#include "TextureComponent2D.h"
#include "BoxColliderComponent.h"

TestScene::TestScene(const std::string& name)
	:Scene(name)
{
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = new dae::TextObject("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	Add(to);

	auto gameObject = new Entity();
	gameObject->AddComponent(new TextureComponent2D(gameObject, "brick.jpg", {50, 50}));
	//gameObject->SetVelocity({0,5,0});
	gameObject->AddComponent(new BoxColliderComponent(gameObject, GetWorld(), {50, 300}, {25,25}));
	Add(gameObject);

	auto gameObject2 = new Entity();
	gameObject2->AddComponent(new TextureComponent2D(gameObject2, "brick.jpg", {100, 100}));
	//gameObject->SetVelocity({0,5,0});
	gameObject2->AddComponent(new BoxColliderComponent(gameObject2, GetWorld(), {75, 500}, {50,50}));
	Add(gameObject2);
}