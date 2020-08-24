#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "EnemyManager.h"
#include "Map.h"

void LevelManager::Init(Map* map, Player* player, EnemyManager* enemyManager)
{
	m_pMap = map;
	m_pPlayer = player;
	m_pEnemyManager = enemyManager;
}

void LevelManager::AddLevel(const std::string& path)
{
	m_Levels.push_back(new Level(path));
}

void LevelManager::Update()
{
	//	load first level
	if(!m_FirstLvlLoaded)
	{
		m_Levels[0]->LoadLevel(m_pMap, m_pPlayer, m_pEnemyManager);
		m_FirstLvlLoaded = true;
		return;
	}
	//	check if ready to advance level
	if(m_pEnemyManager->IsDone() || m_pMap->GetIsDone())
	{
		if(m_LevelIdx < m_Levels.size())
		{
			AdvanceLevel();	
		}
	}
}

void LevelManager::AdvanceLevel()
{
	m_LevelIdx++;
	m_pEnemyManager->Empty();
	//	check if reached end of levels
	if(m_LevelIdx < m_Levels.size())
		m_Levels[m_LevelIdx]->LoadLevel(m_pMap, m_pPlayer, m_pEnemyManager);
}