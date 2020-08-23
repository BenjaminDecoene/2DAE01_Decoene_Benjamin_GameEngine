#include "pch.h"
#include "InGameScene.h"
#include "InputManager.h"
#include "Commands.h"
#include "Player.h"
#include "Map.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameStats.h"
#include "Enemy.h"
#include "ContactListener.h"

InGameScene::InGameScene(const std::string& name)
	:Scene(name)
	,m_pPlayer(nullptr)
	,m_pMap(nullptr)
	,m_pScoreText()
	,m_pContactListener(new ContactListener())
{
}

InGameScene::~InGameScene()
{
	delete m_pContactListener;
	m_pContactListener = nullptr;
}

void InGameScene::Init()
{
	//	Add the contactlistener
	GetWorld()->SetContactListener(m_pContactListener);
	
	//	Player
	m_pPlayer = new Player({100.f, 100.f});
		//	Bind commands for the player
		InputManager::GetInstance().BindCommand(ControllerButton::keyA, std::make_unique<CommandMoveLeft>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::KeyD, std::make_unique<CommandMoveRight>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::KeyW, std::make_unique<CommandMoveUp>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::KeyS, std::make_unique<CommandMoveDown>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::Key_Space, std::make_unique<CommandShoot>(m_pPlayer));
	
	//	Map
	m_pMap = new Map(m_pPlayer);
		//	Add the map
		Add(m_pMap);
		//	Add the player after the map so its drawn in front of the tiles
		Add(m_pPlayer);

	//	Score
	const auto scoreFont = ResourceManager::GetInstance().LoadFont("Font/OrangeJuice.ttf", 50);
	m_pScoreText = new TextObject (std::to_string(GameStats::GetInstance().GetScore()), scoreFont);
	m_pScoreText->SetPosition(50.f, 0.f);

	Add(m_pScoreText);

	//	BulletManager
	m_BulletManager.SetMap(m_pMap);
	m_pPlayer->SetBulletManager(&m_BulletManager);

	//	EnemyManager
	m_EnemyManager.SetMap(m_pMap);
	m_EnemyManager.AddEnemy({500.f, 500.f});
}

void InGameScene::Update()
{
	Scene::Update();

	m_pScoreText->SetText(std::to_string(GameStats::GetInstance().GetScore()));

	m_BulletManager.Update();
	m_EnemyManager.Update();
}
