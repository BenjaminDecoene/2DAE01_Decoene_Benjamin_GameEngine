#include "pch.h"
#include "Scene.h"
#include "Object.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
: m_Name(name)
{
	//	Create world for box2d with gravity
	const b2Vec2 gravity(0.0f, -9.81f);
	m_World = new b2World(gravity);
}

void Scene::Add(SceneObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Remove(SceneObject* object)
{
	m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), object));
}

void Scene::Update()
{
	//	update the world
	m_World->Step(GameInfo::GetInstance().GetElapsedSec(), 6, 2);

	const size_t nrObjects{m_Objects.size()};
	
	for(size_t i{}; i < nrObjects; i++)
	{
		m_Objects[i]->Update();
	}
}

void Scene::Render(float interpolation) const
{
	for (const auto& object : m_Objects)
	{
		object->Render(interpolation);
	}
}
