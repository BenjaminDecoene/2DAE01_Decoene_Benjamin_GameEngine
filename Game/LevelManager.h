#pragma once

class Map;
class Player;
class EnemyManager;
class Level;
class GoldSackManager;

class LevelManager
{
public:
	LevelManager();
	void Init(Map* map, Player* player, EnemyManager* enemyManager, GoldSackManager* goldSackManager);
	void AddLevel(const std::string& path);

	void Update();
	bool GetIsDone() const { return m_LevelIdx >= m_Levels.size(); }
private:
	void AdvanceLevel();
	
	std::vector<Level*> m_Levels;
	UINT m_LevelIdx;
	bool m_FirstLvlLoaded;

	Map* m_pMap;
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
	GoldSackManager* m_pGoldSackManager;
};