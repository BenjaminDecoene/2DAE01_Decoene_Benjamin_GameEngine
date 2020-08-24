#include "pch.h"
#include "GoldSackManager.h"
#include "GoldSack.h"
#include "SceneManager.h"
#include "Scene.h"

void GoldSackManager::Update()
{
	//	Remove goldSack if broken
	for(std::vector<GoldSack*>::iterator it{m_GoldSacks.begin()}; it != m_GoldSacks.end();)
	{
		if((*it)->GetDestroyed())
		{
			auto sack = (*it);
			SceneManager::GetInstance().GetScene().Remove((*it));
			it = m_GoldSacks.erase(it);
			delete sack;
			sack = nullptr;
		}
		else
			++it;
	}
}

void GoldSackManager::AddGoldSack(const b2Vec2& pos)
{
	auto goldSack = new GoldSack(m_pMap, pos);
	m_GoldSacks.emplace_back(goldSack);
	SceneManager::GetInstance().GetScene().Add(goldSack);
}

void GoldSackManager::Empty()
{
	for(std::vector<GoldSack*>::iterator it{m_GoldSacks.begin()}; it != m_GoldSacks.end(); ++it)
	{
		(*it)->Destroy();
	}
}