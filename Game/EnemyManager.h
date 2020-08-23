#pragma once

class Enemy;
class Map;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	
	void SetMap(Map* map) {m_pMap = map; }
	void AddEnemy(const b2Vec2& pos);
private:
	std::vector<Enemy*> m_Enemies;
	Map* m_pMap;
};

