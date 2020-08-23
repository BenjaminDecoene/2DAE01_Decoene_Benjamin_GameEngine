#include "pch.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Map.h"
#include "Tile.h"

BulletManager::BulletManager()
{
	m_Bullets.reserve(10);
}

BulletManager::~BulletManager()
{
	for(size_t i{}; i < m_Bullets.size(); i++)
	{
		delete m_Bullets[i];
		m_Bullets[i] = nullptr;
	}
	m_Bullets.clear();
}

void BulletManager::Update()
{
	for(std::vector<Bullet*>::iterator it{m_Bullets.begin()}; it != m_Bullets.end();)
	{
		//	Remove bullet if it hits a wall
		if(m_pMap->GetTile((*it)->GetTransform().GetPosition())->GetState() != TileState::broken)
		{
			SceneManager::GetInstance().GetScene().Remove((*it));
			it = m_Bullets.erase(it);
		}
		else
			++it;
	}
}

void BulletManager::AddBullet(const b2Vec2& pos, float direction)
{
	auto bullet = new Bullet(pos, direction);
	m_Bullets.emplace_back(bullet);
	SceneManager::GetInstance().GetScene().Add(bullet);
}