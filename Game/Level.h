#pragma once
#include "Tile.h"

class GoldSackManager;
class EnemyManager;
class Player;
class Map;
class Spawner;

class Level
{
public:
	Level(const std::string& path);
	
	void LoadLevel(Map* map, Player* player, EnemyManager* enemyManager, GoldSackManager* goldSackManager);
private:
	void ReadFile(const std::string& path);

	static const UINT m_nrTileColumns = 20;
	static const UINT m_nrTileRows = 17;
	TileState m_Tiles[m_nrTileColumns][m_nrTileRows];
	UINT m_RowIdx = m_nrTileRows - 1;
	b2Vec2 m_PlayerPos;
	std::vector<Spawner*> m_Spawners;
	std::vector<b2Vec2> m_GoldSacks;
};