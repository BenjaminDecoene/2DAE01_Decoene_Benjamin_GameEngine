#include "pch.h"
#include "Map.h"
#include "Tile.h"
#include "Scene.h"
#include "Player.h"
#include "Renderer.h"
#include "Utils.h"
#include "GameStats.h"
#include "PhysxComponent.h"
#include "SceneManager.h"

Map::Map(Player* player)
	:m_Player(player)
{
	LoadTiles();

	AddObserver(&GameStats::GetInstance());
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

void Map::InitBorder(Scene* scene)
{	
	//	make border so the player cant go outside of the level
	const auto windowSize = GameInfo::GetInstance().GetWindowSize();
	const float ppm = GameInfo::GetInstance().GetPPM();
	
	m_Transform.SetPosition(windowSize.x / 2, windowSize.y / 2);
	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_staticBody;
	bodyDef->position = {(windowSize.x / 2), 0.f};
	
	auto physxComp = new PhysxComponent(this, scene->GetWorld(), bodyDef);
	physxComp->FixedToParent(false);
	
	b2PolygonShape boxShapeLeft;
	boxShapeLeft.SetAsBox((windowSize.x / ppm) / 2, (50  / ppm) / 2, {((-windowSize.x - 25.f) / ppm), 0.f}, float(M_PI / 2));
	const auto fixtureDefLeft = new b2FixtureDef();
	fixtureDefLeft->shape = &boxShapeLeft;
	fixtureDefLeft->density = 1.0f;
	fixtureDefLeft->friction = 0.3f;
	fixtureDefLeft->restitution = 0.3f;
	physxComp->AddFixture(fixtureDefLeft);

	b2PolygonShape boxShapeDown;
	boxShapeDown.SetAsBox((windowSize.x / ppm) / 2, (50  / ppm) / 2, {(-windowSize.x / 2) / ppm, ((-windowSize.y - 25.f) / ppm)}, 0.f);
	const auto fixtureDefDown = new b2FixtureDef();
	fixtureDefDown->shape = &boxShapeDown;
	fixtureDefDown->density = 1.0f;
	fixtureDefDown->friction = 0.3f;
	fixtureDefDown->restitution = 0.3f;
	physxComp->AddFixture(fixtureDefDown);

	b2PolygonShape boxShapeRight;
	boxShapeRight.SetAsBox((windowSize.x / ppm) / 2, (50  / ppm) / 2, {25.f / ppm, 0.f}, float(M_PI / 2));
	const auto fixtureDefRight = new b2FixtureDef();
	fixtureDefRight->shape = &boxShapeRight;
	fixtureDefRight->density = 1.0f;
	fixtureDefRight->friction = 0.3f;
	fixtureDefRight->restitution = 0.3f;
	physxComp->AddFixture(fixtureDefRight);

	b2PolygonShape boxShapeUp;
	boxShapeUp.SetAsBox((windowSize.x / ppm) / 2, (50  / ppm) / 2, {(-windowSize.x / 2) / ppm, ((windowSize.y / 2 + 25.f) / ppm)}, 0.f);
	const auto fixtureDefUp = new b2FixtureDef();
	fixtureDefUp->shape = &boxShapeUp;
	fixtureDefUp->density = 1.0f;
	fixtureDefUp->friction = 0.3f;
	fixtureDefUp->restitution = 0.3f;
	physxComp->AddFixture(fixtureDefUp);

	AddComponent(physxComp);
}

void Map::AddTiles(Scene* scene)
{
	for(int r{}; r < m_nrTileRows; r++)
	{
		for(int c{}; c < m_nrTileColumns; c++)
		{
			if(m_Tiles[c][r])
				scene->Add(m_Tiles[c][r]);
			m_Tiles[c][r]->Break();
		}
	}
}

void Map::LoadTiles()
{
	for(int r{}; r < m_nrTileRows; r++)
	{
		for(int c{}; c < m_nrTileColumns; c++)
		{
			const auto random = rand() % 3;

			if(random == 0)
				m_Tiles[c][r] = new Tile({(m_TileSize / 2.f) + (c * m_TileSize), (m_TileSize / 2.f) + (r * m_TileSize)}, emerald);
			else
				m_Tiles[c][r] = new Tile({(m_TileSize / 2.f) + (c * m_TileSize), (m_TileSize / 2.f) + (r * m_TileSize)}, dirt);
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
	
	switch(diggerTile->Break())
	{
	case emerald:
		Notify(*this, "Emerald");
		break;
	case dirt:
		Notify(*this, "Dirt");
		break;
	case broken:
		break;
	}
}