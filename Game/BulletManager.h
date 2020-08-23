#pragma once

class Bullet;
class Map;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Update();

	void SetMap(Map* map) {m_pMap = map; }
	void AddBullet(const b2Vec2& pos, float direction);
private:
	std::vector<Bullet*> m_Bullets;
	Map* m_pMap;
};