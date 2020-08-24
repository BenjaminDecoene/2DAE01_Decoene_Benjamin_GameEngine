#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Spawner.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	//	Update the spawners
	for(std::vector<Spawner*>::iterator it{m_Spawners.begin()}; it != m_Spawners.end();)
	{
		if((*it)->Update())
		{
			AddEnemy((*it)->GetPos());
		}
		
		//	Check for if a spawner is done spawning
		if((*it)->GetIsDone())
		{
			it = m_Spawners.erase(it);
		}
		else
			++it;
	}
	
	//	Check if an enemy is dead
	for(std::vector<Enemy*>::iterator it{m_Enemies.begin()}; it != m_Enemies.end();)
	{
		if((*it)->GetIsDead())
		{
			auto enemy = (*it);
			SceneManager::GetInstance().GetScene().Remove((*it));
			it = m_Enemies.erase(it);
			delete enemy;
			enemy = nullptr;		
		}
		else
			++it;
	}
}

bool EnemyManager::IsDone() const
{
	if(m_Enemies.empty() && m_Spawners.empty())
		return true;
	return false;
}

void EnemyManager::AddEnemy(const b2Vec2& pos)
{
	auto enemy = new Enemy(m_pMap, pos);
	m_Enemies.emplace_back(enemy);
	SceneManager::GetInstance().GetScene().Add(enemy);
}

void EnemyManager::AddSpawner(UINT nrEnemies, float timeBetween, const b2Vec2& pos)
{
	m_Spawners.push_back(new Spawner(nrEnemies, timeBetween, pos));
}

void EnemyManager::AddSpawner(Spawner* spawner)
{
	m_Spawners.push_back(spawner);
}

void EnemyManager::Empty()
{
	for(std::vector<Enemy*>::iterator it{m_Enemies.begin()}; it != m_Enemies.end();)
	{
		auto enemy = (*it);
		SceneManager::GetInstance().GetScene().Remove((*it));
		it = m_Enemies.erase(it);
		delete enemy;
		enemy = nullptr;
	}

	for(std::vector<Spawner*>::iterator it{m_Spawners.begin()}; it != m_Spawners.end();)
	{
		it = m_Spawners.erase(it);			
	}
}