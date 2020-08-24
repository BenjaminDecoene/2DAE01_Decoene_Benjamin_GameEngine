#include "pch.h"
#include "Level.h"
#include <fstream>
#include "Player.h"
#include "Map.h"
#include "Scene.h"
#include "Spawner.h"
#include "EnemyManager.h"
#include "GoldSackManager.h"

Level::Level(const std::string& path)
{
	m_GoldSacks.reserve(20);
	ReadFile(path);
}

void Level::LoadLevel(Map* map, Player* player, EnemyManager* enemyManager, GoldSackManager* goldSackManager)
{
	//	Set player pos
	player->SetPosition(m_PlayerPos);
	//	Load tiles
	for(UINT r{}; r < m_nrTileRows; r++)
	{
		for(UINT c{}; c < m_nrTileColumns; c++)
		{
			auto tile = map->GetTile(c,r);
			tile->SetState(m_Tiles[c][r]);
		}
	}
	//	Add spawners
	for(size_t i{}; i < m_Spawners.size(); i++)
	{
		enemyManager->AddSpawner(m_Spawners[i]);
	}
	//	Add goldSacks
	for(size_t i{}; i < m_GoldSacks.size(); i++)
	{
		goldSackManager->AddGoldSack(m_GoldSacks[i]);
	}
}

void Level::ReadFile(const std::string& path)
{
	std::ifstream input{ path };
	//	check if the stream is succesfull
	if (input.is_open())
	{
		std::string line{};

		while (std::getline(input, line))
		{
			if(line[0] == 'P')
			{
				std::stringstream playerStream{ line };
				std::string trash;
				std::string posX;
				std::string posY;
				std::getline(playerStream, trash, '(');
				std::getline(playerStream, posX, ',');
				std::getline(playerStream, posY, ')');

				m_PlayerPos = {std::stof(posX), std::stof(posY)};
			}
			else if(line[0] == 'S')
			{
				std::stringstream SpawnerStream{ line };
				std::string trash;
				std::string nrEnemies;
				std::string timeInBetween;
				std::string posX;
				std::string posY;
				
				std::getline(SpawnerStream, trash, '(');
				std::getline(SpawnerStream, nrEnemies, ',');
				std::getline(SpawnerStream, timeInBetween, ',');
				std::getline(SpawnerStream, posX, ',');
				std::getline(SpawnerStream, posY, ')');

				m_Spawners.push_back(new Spawner(std::stoi(nrEnemies), std::stof(timeInBetween), {std::stof(posX), std::stof(posY)}));
			}
			else if(line[0] == 'M')
			{
				std::stringstream mapStream{ line };
				std::string string;
				std::getline(mapStream, string, '\n');
				std::string tiles = string.substr(2, m_nrTileColumns);

				for(int i{}; i < tiles.size(); i++)
				{
					switch(tiles[i])
					{
					case 'D':
						m_Tiles[i][m_RowIdx] = TileState::dirt;
						break;
					case 'G':
						m_Tiles[i][m_RowIdx] = TileState::dirt;
						m_GoldSacks.emplace_back(i * 40.f + 20.f, m_RowIdx * 40.f + 20.f);
						break;
					case 'E':
						m_Tiles[i][m_RowIdx] = TileState::emerald;
						break;
					case 'B':
						m_Tiles[i][m_RowIdx] = TileState::broken;
						break;
					default:
						break;
					}
				}
				m_RowIdx--;
			}
		}
		return;
	}
}
