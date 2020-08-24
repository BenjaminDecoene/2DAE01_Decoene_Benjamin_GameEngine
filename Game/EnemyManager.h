#pragma once

class Enemy;
class Map;
class Spawner;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();

	bool IsDone() const;
	void SetMap(Map* map) {m_pMap = map; }
	void AddEnemy(const b2Vec2& pos);
	void AddSpawner(UINT nrEnemies, float timeBetween, const b2Vec2& pos);
	void AddSpawner(Spawner* spawner);
	void Empty();
private:
	std::vector<Enemy*> m_Enemies;
	std::vector<Spawner*> m_Spawners;
	Map* m_pMap;
};