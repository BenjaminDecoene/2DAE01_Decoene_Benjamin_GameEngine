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

	void InitBorder(Scene* scene);
	//	Getters setters
	void AddTiles(Scene* scene);
private:
	void Update() override;
	void UpdatePlayer();
	void LoadTiles();

	static const UINT m_TileSize = 40;
	static const UINT m_nrTileColumns = 20;
	static const UINT m_nrTileRows = 18;
	Tile* m_Tiles[m_nrTileColumns][m_nrTileRows];
	Player* m_Player;
};