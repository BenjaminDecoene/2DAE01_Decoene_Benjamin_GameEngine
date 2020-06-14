#include "pch.h"
#include "Animator.h"
#include "SpriteComponent2D.h"

void Animator::Update()
{
	if(m_pCurrentSprite->GetIsDone())
	{
		m_pCurrentSprite->Interupt();
		m_pdefaultSprite->PlayLoop();
	}
	else if(m_pCurrentSprite != m_pdefaultSprite)
		m_pdefaultSprite->Interupt();
}

void Animator::SetDefaultSpriteComponent(SpriteComponent2D* spriteComponent)
{
	m_pdefaultSprite = spriteComponent;
	m_pCurrentSprite = m_pdefaultSprite;
}

void Animator::AddSpriteComponent(const std::string& name, SpriteComponent2D* spriteComponent)
{
	m_Sprites.push_back(std::make_pair(name, spriteComponent));
}

void Animator::PlayOnce(const std::string& name)
{
	m_pCurrentSprite->Interupt();
	
	for(auto i : m_Sprites)
	{
		if(name == i.first)
		{
			m_pCurrentSprite = i.second;
			i.second->PlayOnce();
		}
	}
}

void Animator::PlayLoop(const std::string& name)
{
	m_pCurrentSprite->Interupt();
	
	for(auto i : m_Sprites)
	{
		if(name == i.first)
		{
			m_pCurrentSprite = i.second;
			i.second->PlayLoop();
		}
	}
}

void Animator::PlayDefault()
{
	m_pCurrentSprite->Interupt();
	m_pCurrentSprite = m_pdefaultSprite;
}

bool Animator::GetIsDone() const
{	
	return m_pCurrentSprite->GetIsDone();
}