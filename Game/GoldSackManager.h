#pragma once
#include <vector>

class GoldSack;
class Map;

class GoldSackManager
{
public:
	GoldSackManager() = default;
	void Update();

	void SetMap(Map* map) {m_pMap = map; }
	void AddGoldSack(const b2Vec2& pos);
	void Empty();
private:
	std::vector<GoldSack*> m_GoldSacks;
	Map* m_pMap;
};