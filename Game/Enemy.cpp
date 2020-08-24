#include "pch.h"
#include "Enemy.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Tile.h"
#include "Map.h"
#include "GameStats.h"

Enemy::Enemy(Map* map, const b2Vec2& pos)
	:Object()
	,m_pMap(map)
	,m_LastTile(nullptr)
	,m_Target()
{
	m_Transform.SetPosition(pos);

	//	add observer
	AddObserver(&GameStats::GetInstance());

	//	add components
		//	Texture
		AddComponent(new TextureComponent2D(this, "Enemy.png", {40, 40}));
		//	Physx
			//	make physx component
			const float ppm = GameInfo::GetInstance().GetPPM();
			//	make the body
			auto bodyDef = new b2BodyDef();
			bodyDef->type = b2_dynamicBody;
			bodyDef->gravityScale = 0;

			auto physx = new PhysxComponent(this, SceneManager::GetInstance().GetScene().GetWorld(), bodyDef);

			b2PolygonShape boxShape;
			boxShape.SetAsBox((20 / ppm), (20  / ppm));
			const auto fixtureDef = new b2FixtureDef();
			fixtureDef->shape = &boxShape;
			fixtureDef->density = 1.0f;
			fixtureDef->friction = 0.7f;
			fixtureDef->restitution = 0.3f;
			fixtureDef->filter.groupIndex = -1;

			physx->AddFixture(fixtureDef);
			
		AddComponent(physx);

	//	set the initial tile
	m_LastTile = m_pMap->GetTile(m_Transform.GetPosition());
	//	init stat machine
	InitStateMachine();
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Object::Update();

	m_StateMachine.Update();
}

bool Enemy::UpdateTarget()
{
	//	get the neighbouring tiles
	Tile* leftTile = m_pMap->GetTile({m_Transform.GetPosition().x - m_pMap->GetTileSize(), m_Transform.GetPosition().y});
	Tile* rightTile = m_pMap->GetTile({m_Transform.GetPosition().x + m_pMap->GetTileSize(), m_Transform.GetPosition().y});
	Tile* upTile = m_pMap->GetTile({m_Transform.GetPosition().x, m_Transform.GetPosition().y + m_pMap->GetTileSize()});
	Tile* downTile = m_pMap->GetTile({m_Transform.GetPosition().x, m_Transform.GetPosition().y  - m_pMap->GetTileSize()});

	//	hold a vector with the possible tiles
	std::vector<Tile*> tiles;
	tiles.reserve(4);

	//	check all the possible tiles for a broken tile
	if(leftTile)
		if(leftTile->GetState() == TileState::broken)
			tiles.emplace_back(leftTile);
	if(rightTile)
		if(rightTile->GetState() == TileState::broken)
			tiles.emplace_back(rightTile);
	if(upTile)
		if(upTile->GetState() == TileState::broken)
			tiles.emplace_back(upTile);
	if(downTile)	
		if(downTile->GetState() == TileState::broken)
			tiles.emplace_back(downTile);

	//	if there are no tiles available, dont update the target
	if(tiles.empty())
		return false;
	
	//	if there is more then 1 way we dont want to go back
	if(tiles.size() > 1)
	{
		const auto lastTile = std::find(tiles.begin(), tiles.end(), m_LastTile);
		if(lastTile != tiles.end())
			tiles.erase(lastTile);
	}

	//	get a random target tile
	m_Target = tiles[rand() % tiles.size()]->GetTransform().GetPosition();

	//	update last tile
	m_LastTile = m_pMap->GetTile(m_Transform.GetPosition());
	
	return true;
}

bool Enemy::UpdateMoveToTarget()
{
	//	move to target
	auto toTarget = m_Target - m_Transform.GetPosition();
	const auto distToTarget = toTarget.Length();
	toTarget.Normalize();
	
	GetComponent<PhysxComponent>()->SetVelocity(toTarget);

	//	check if close enough
	return distToTarget < 2.f;
}

void Enemy::Kill()
{
	if(!m_IsDead)
	{
		m_IsDead = true;
		Notify(*this, "EnemyKilled");
	}
}

void Enemy::HitPlayer()
{
	if(!m_IsDead)
	{
		m_IsDead = true;
	}
}

void Enemy::InitStateMachine()
{
	const auto startState = new SeekTarget(this);
	m_StateMachine.AddState(startState);
	m_StateMachine.AddState(new MoveToTarget(this));
	m_StateMachine.SetStartState(startState);
}

void SeekTarget::Update(StateMachine* stateMachine)
{
	if(m_pEnemy->UpdateTarget())
		stateMachine->TransitionTo(stateMachine->GetState<MoveToTarget>());
}

void MoveToTarget::Update(StateMachine* stateMachine)
{
	if(m_pEnemy->UpdateMoveToTarget())
		stateMachine->TransitionTo(stateMachine->GetState<SeekTarget>());
}