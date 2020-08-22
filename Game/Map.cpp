#include "pch.h"
#include "Map.h"
#include "Tile.h"
#include "Scene.h"
#include "Player.h"
#include "Renderer.h"
#include "Utils.h"

Map::Map(Player* player)
	:m_Player(player)
{
	LoadTiles();
}

Map::~Map()
{
	for(int r{}; r < m_nrTileRows; r++)
	{
		for(int c{}; c < m_nrTileColumns; c++)
		{
			delete m_Tiles[c][r];
			m_Tiles[c][r] = nullptr;
		}
	}
}

void Map::AddTiles(Scene* scene)
{
	for(int r{}; r < m_nrTileRows; r++)
	{
		for(int c{}; c < m_nrTileColumns; c++)
		{
			if(m_Tiles[c][r])
				scene->Add(m_Tiles[c][r]);
		}
	}
}

void Map::LoadTiles()
{
	for(int r{}; r < m_nrTileRows; r++)
	{
		for(int c{}; c < m_nrTileColumns; c++)
		{
			m_Tiles[c][r] = new Tile({(m_TileSize / 2.f) + (c * m_TileSize), (m_TileSize / 2.f) + (r * m_TileSize)});
		}
	}
}

void Map::Update()
{
	Object::Update();

	UpdatePlayer();
}

void Map::UpdatePlayer()
{
	const auto diggerPoint = m_Player->GetDigPoint();
	Tile* diggerTile = m_Tiles[int(diggerPoint.x) / m_TileSize][int(diggerPoint.y) / m_TileSize];

	diggerTile->Break();
}