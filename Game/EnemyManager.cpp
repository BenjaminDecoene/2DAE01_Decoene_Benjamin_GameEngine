#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	//	Check if an enemy is dead
	for(std::vector<Enemy*>::iterator it{m_Enemies.begin()}; it != m_Enemies.end();)
	{
		if((*it)->GetIsDead())
		{
			SceneManager::GetInstance().GetScene().Remove((*it));
			it = m_Enemies.erase(it);			
		}
		else
			++it;
	}
}

void EnemyManager::AddEnemy(const b2Vec2& pos)
{
	auto enemy = new Enemy(m_pMap, pos);
	m_Enemies.emplace_back(enemy);
	SceneManager::GetInstance().GetScene().Add(enemy);
}
