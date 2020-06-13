#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
: m_Name(name)
{
	//	Create world for box2d with gravity
	const b2Vec2 gravity(0.0f, -9.81f);
	m_World = new b2World(gravity);

	const auto windowSize{ GameInfo::GetInstance().GetWindowSize() };

	const float ppm = GameInfo::GetInstance().GetPPM();
	//	Ground test
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.f, 0.f / ppm);
	b2Body* groundBody = m_World->CreateBody(&groundBodyDef);
	//	Make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(windowSize.x, 0.0f / ppm);
	groundBody->CreateFixture(&groundBox, 0.0f);

	//auto gameObject = new Object();
	//gameObject->AddComponent(new TextureComponent2D(gameObject, "brick.jpg", {windowSize.x, 50}));
	////gameObject->SetVelocity({0,5,0});
	//gameObject->AddComponent(new PhysxComponent(gameObject, GetWorld(), {0, 10}, {windowSize.x,5}));
	//Add(gameObject);
}

Scene::~Scene() = default;

void Scene::Add(SceneObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	//	update the world
	m_World->Step(GameInfo::GetInstance().GetMsPerFrame() / 1000.f, 6, 2);
	
	for(auto& object : m_Objects)
	{
		object->Update();
	}
	
}

void Scene::Render(float interpolation) const
{
	for (const auto& object : m_Objects)
	{
		object->Render(interpolation);
	}
}