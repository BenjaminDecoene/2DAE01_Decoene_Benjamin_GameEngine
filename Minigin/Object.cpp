#include "pch.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Renderer.h"

Object::~Object()
{
	for (std::vector<Component*>::iterator it{ m_pComponents.begin() }; it != m_pComponents.end(); ++it)
	{
		delete (*it);
	}
	m_pComponents.clear();
};

void Object::Update()
{
	for(auto i : m_pComponents)
	{
		i->Update();
	}
}

void Object::Render(float interpolation) const
{
	for(auto i : m_pComponents)
	{
		i->Render(interpolation);
	}
}

void Object::AddComponent(Component* component)
{
	m_pComponents.push_back(component);
}

void Object::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y);
}
