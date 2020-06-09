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
	const b2Vec3 newPos{ m_Transform.GetPosition() + timePassed * m_Velocity };
	m_Transform.SetPosition(newPos);

	//	Update components
	for(auto i : m_pComponents)
	{
		i->Update();
	}
}

void Entity::Render(float interpolation) const
{
	//	Render components
	for(auto i : m_pComponents)
	{
		i->Render(interpolation);
	}
}
