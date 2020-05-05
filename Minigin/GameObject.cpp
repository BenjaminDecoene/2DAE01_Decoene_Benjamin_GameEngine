#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (std::vector<ObjectComponent*>::iterator it{ m_pComponents.begin() }; it != m_pComponents.end(); ++it)
	{
		delete (*it);
	}
	m_pComponents.clear();
};

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();

	for(std::vector<ObjectComponent*>::const_iterator it{ m_pComponents.cbegin() }; it != m_pComponents.cend(); ++it)
	{
		(*it)->Render();
	}
}

void dae::GameObject::AddComponent(ObjectComponent* component)
{
	m_pComponents.push_back(component);
	component->SetParentTransform(m_Transform);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
