#include "pch.h"
#include "InGameScene.h"
#include "InputManager.h"
#include "Commands.h"
#include "Player.h"
#include "Map.h"

InGameScene::InGameScene(const std::string& name)
	:Scene(name)
	,m_pPlayer(new Player({10.f, 10.f}))
	,m_pMap(new Map(m_pPlayer))
{
	//	Add the map
	Add(m_pMap);
	m_pMap->AddTiles(this);
	
	//	Bind commands for the player
	InputManager::GetInstance().BindCommand(ControllerButton::keyA, std::make_unique<CommandMoveLeft>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::KeyD, std::make_unique<CommandMoveRight>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::KeyW, std::make_unique<CommandMoveUp>(m_pPlayer));
	InputManager::GetInstance().BindCommand(ControllerButton::KeyS, std::make_unique<CommandMoveDown>(m_pPlayer));

	Add(m_pPlayer);
}
