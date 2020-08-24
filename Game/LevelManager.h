#pragma once

class Map;
class Player;
class EnemyManager;
class Level;

class LevelManager
{
public:
	LevelManager() = default;
	void Init(Map* map, Player* player, EnemyManager* enemyManager);
	void AddLevel(const std::string& path);

	void Update();
private:
	void AdvanceLevel();
	
	std::vector<Level*> m_Levels;
	UINT m_LevelIdx = 0;
	bool m_FirstLvlLoaded = false;

	Map* m_pMap;
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
};