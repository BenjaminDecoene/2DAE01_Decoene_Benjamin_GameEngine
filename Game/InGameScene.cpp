#include "pch.h"
#include "InGameScene.h"
#include "InputManager.h"
#include "Commands.h"
#include "Player.h"
#include "Map.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameStats.h"

InGameScene::InGameScene(const std::string& name)
	:Scene(name)
	,m_pPlayer(new Player({100.f, 100.f}))
	,m_pMap(new Map(m_pPlayer))
{
	//	Add the map
	Add(m_pMap);
	m_pMap->AddTiles(this);
	m_pMap->InitBorder(this);
	
	//	Bind commands for the player
	InputManager::GetInstance().BindCommand(ControllerButton::keyA, std::make_unique<CommandMoveLeft>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::KeyD, std::make_unique<CommandMoveRight>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::KeyW, std::make_unique<CommandMoveUp>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::KeyS, std::make_unique<CommandMoveDown>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::Key_Space, std::make_unique<CommandShoot>(m_pPlayer));
	
	Add(m_pPlayer);
	m_pPlayer->Init(this);

	//	Score
	const auto scoreFont = ResourceManager::GetInstance().LoadFont("Font/OrangeJuice.ttf", 50);
	m_pScoreText = new TextObject (std::to_string(GameStats::GetInstance().GetScore()), scoreFont);
	m_pScoreText->SetPosition(50.f, 0.f);

	Add(m_pScoreText);

	//	BulletManager
	m_BulletManager.SetMap(m_pMap);
	m_pPlayer->SetBulletManager(&m_BulletManager);
}

void InGameScene::Update()
{
	Scene::Update();

	m_pScoreText->SetText(std::to_string(GameStats::GetInstance().GetScore()));

	m_BulletManager.Update();
}