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
	//gameObject->AddComponent(new TextureComponent2D(gameObject, "background.jpg"));
	//gameObject->SetVelocity({0,5,0});
	gameObject->AddComponent(new BoxColliderComponent(gameObject, GetWorld(), {50, 50}, {10, 10}));
	Add(gameObject);
}