#include "pch.h"
#include "GoldSack.h"
#include "TextureComponent2D.h"
#include "PhysxComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Map.h"
#include "Tile.h"

GoldSack::GoldSack(Map* map, const b2Vec2& pos)
	:Object()
	,m_pMap(map)
	,m_Falling(false)
	,m_FallingDelay(0.5f)
	,m_FallingDelayTimer(0.f)
	,m_Destroyed(false)
{
	//	Set initalial timer
	m_FallingDelayTimer = m_FallingDelay;
	
	//	Set init pos
	m_Transform.SetPosition(pos);

	//	Add texture
	AddComponent(new TextureComponent2D(this, "GoldSack.png", {36, 36}));

	//	Physx
		//	make physx component
		const float ppm = GameInfo::GetInstance().GetPPM();
		//	make the body
		auto bodyDef = new b2BodyDef();
		bodyDef->type = b2_dynamicBody;
		bodyDef->gravityScale = 0;

		auto physx = new PhysxComponent(this, SceneManager::GetInstance().GetScene().GetWorld(), bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox((18 / ppm), (18  / ppm));
		const auto fixtureDef = new b2FixtureDef();
		fixtureDef->shape = &boxShape;
		fixtureDef->friction = 0.0f;
		fixtureDef->restitution = 0.3f;
		fixtureDef->density = 100.f;
		fixtureDef->filter.groupIndex = -2;

		physx->AddFixture(fixtureDef);
			
	AddComponent(physx);

	//	Init stat machine
	InitStateMachine();
}

void GoldSack::InitStateMachine()
{
	const auto startState = new Stable(this);
	m_StateMachine.AddState(startState);
	m_StateMachine.AddState(new Falling(this));
	m_StateMachine.AddState(new Torn(this));
	m_StateMachine.SetStartState(startState);
}

void GoldSack::Update()
{
	Object::Update();

	m_StateMachine.Update();
}

bool GoldSack::IsStable() const
{
	//	Check if the tile bellow the chest is broken
	const auto tileUnder = m_pMap->GetTile({m_Transform.GetPosition().x, m_Transform.GetPosition().y - m_pMap->GetTileSize() / 2 - 4});

	if(!tileUnder)
		return true;
	
	if( tileUnder->GetState() == TileState::broken)
	{
		return false;
	}
	return true;
}

Stable::Stable(GoldSack* goldSack)
	:m_pGoldSack(goldSack)
	,m_FallingDelay(0.5f)
	,m_FallingDelayTimer(0.f)
{
	m_FallingDelayTimer = m_FallingDelay;
}

void Stable::OnEntry()
{
	m_FallingDelayTimer = m_FallingDelay;
	m_pGoldSack->GetComponent<PhysxComponent>()->SetVelocity({0.f, 0.f});
	m_pGoldSack->SetFalling(false);
}

void Stable::Update(StateMachine* stateMachine)
{
	m_pGoldSack->GetComponent<PhysxComponent>()->SetVelocity({0.f, 0.f});
	
	if(m_pGoldSack->IsStable())
		return;

	m_FallingDelayTimer -= GameInfo::GetElapsedSec();
	if(m_FallingDelayTimer < 0.f)
		stateMachine->TransitionTo(stateMachine->GetState<Falling>());
}

void Falling::OnEntry()
{
	m_pGoldSack->SetFalling(true);
	m_pGoldSack->GetComponent<PhysxComponent>()->SetVelocity({0.f, -1.f});
	m_TimeFalling = 0;
}

void Falling::Update(StateMachine* stateMachine)
{
	m_TimeFalling += GameInfo::GetElapsedSec();
	
	if(m_pGoldSack->IsStable())
	{
		if(m_TimeFalling > m_TimeBeforeTorn)
		{
			stateMachine->TransitionTo(stateMachine->GetState<Torn>());			
		}
		else
			stateMachine->TransitionTo(stateMachine->GetState<Stable>());			
	}
}

void Torn::OnEntry()
{
	m_pGoldSack->RemoveComponent(m_pGoldSack->GetComponent<TextureComponent2D>());
	m_pGoldSack->AddComponent(new TextureComponent2D(m_pGoldSack, "PileOfGold.png", {36, 36}));
	m_pGoldSack->GetComponent<PhysxComponent>()->SetVelocity({0.f, 0.f});
	m_pGoldSack->SetTorn(true);
	m_pGoldSack->SetFalling(false);
}

void Torn::Update(StateMachine*)
{
	m_pGoldSack->GetComponent<PhysxComponent>()->SetVelocity({0.f, 0.f});
}
