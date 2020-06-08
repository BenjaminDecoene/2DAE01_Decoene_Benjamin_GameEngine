#include "pch.h"
#include "Entity.h"

Entity::Entity()
	:Object()
	,m_Velocity()
{
}

void Entity::Update()
{
	//	Update pos
	const float timePassed{ GameInfo::GetInstance().GetMsPerFrame() / 1000.f };
	const glm::vec3 newPos{ m_Transform.GetPosition() + m_Velocity * timePassed };
	m_Transform.SetPosition(newPos);

	//	Update components
	for(auto i : m_pComponents)
	{
		i->Update();
	}
}

void Entity::Render() const
{
	//	Render components
	for(auto i : m_pComponents)
	{
		i->Render();
	}
}
