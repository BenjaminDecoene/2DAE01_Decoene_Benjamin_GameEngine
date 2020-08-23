#pragma once
#include <Object.h>

class Scene;
class Tile;
class Player;

class Map : public Object
{
public:
	Map(Player* player);
	~Map();

	//	Getters setters
	Tile* GetTile(const b2Vec2& pos);
	static UINT GetTileSize() { return m_TileSize; }
private:
	void Update() override;
	void UpdatePlayer();
	void InitBorder();
	void LoadTiles();
	void AddTiles();

	static const UINT m_TileSize = 40;
	static const UINT m_nrTileColumns = 20;
	static const UINT m_nrTileRows = 17;
	Tile* m_Tiles[m_nrTileColumns][m_nrTileRows];
	Player* m_Player;
};