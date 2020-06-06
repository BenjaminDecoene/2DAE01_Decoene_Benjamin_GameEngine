#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (std::vector<Component*>::iterator it{ m_pComponents.begin() }; it != m_pComponents.end(); ++it)
	{
		delete (*it);
	}
	m_pComponents.clear();
};

void dae::GameObject::Update()
{
	for(auto i : m_pComponents)
	{
		i->Update(this);
	}
}

void dae::GameObject::AddComponent(Component* component)
{
	m_pComponents.push_back(component);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
