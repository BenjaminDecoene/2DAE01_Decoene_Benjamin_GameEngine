#include "pch.h"
#include "Commands.h"
#include "Player.h"
#include "SceneManager.h"
#include "InGameScene.h"

void CommandMoveRight::OnPressed()
{
	//	Safety check
	if(!m_pPlayer)
		return;
	
	m_pPlayer->SetVelocity({1.f, 0.f});
}

void CommandMoveRight::Released()
{
	//	Safety check
	if(!m_pPlayer)
		return;

	//	Check if its still going in the right direction otherwise dont reset
	const auto vel = m_pPlayer->GetVelocity();
	if(vel.x > 0.9f)
		m_pPlayer->SetVelocity({0.f, 0.f});
}

void CommandMoveUp::OnPressed()
{
	//	Safety check
	if(!m_pPlayer)
		return;
	
	m_pPlayer->SetVelocity({0.f, 1.f});
}

void CommandMoveUp::Released()
{
	//	Safety check
	if(!m_pPlayer)
		return;

	//	Check if its still going in the right direction otherwise dont reset
	const auto vel = m_pPlayer->GetVelocity();
	if(vel.y > 0.9f)
		m_pPlayer->SetVelocity({0.f, 0.f});
}

void CommandMoveLeft::OnPressed()
{
	//	Safety check
	if(!m_pPlayer)
		return;
	
	m_pPlayer->SetVelocity({-1.f, 0.f});
}

void CommandMoveLeft::Released()
{
	//	Safety check
	if(!m_pPlayer)
		return;

	//	Check if its still going in the right direction otherwise dont reset
	const auto vel = m_pPlayer->GetVelocity();
	if(vel.x < -0.9f)
		m_pPlayer->SetVelocity({0.f, 0.f});
}

void CommandMoveDown::OnPressed()
{
	//	Safety check
	if(!m_pPlayer)
		return;
	
	m_pPlayer->SetVelocity({0.f, -1.f});
}

void CommandMoveDown::Released()
{
	//	Safety check
	if(!m_pPlayer)
		return;

	//	Check if its still going in the right direction otherwise dont reset
	const auto vel = m_pPlayer->GetVelocity();
	if(vel.y < -0.9f)
		m_pPlayer->SetVelocity({0.f, 0.f});
}

void CommandShoot::OnPressed()
{
	//	Safety check
	if(!m_pPlayer)
		return;
	m_pPlayer->Shoot();
}

void CommandStart::OnPressed()
{
	SceneManager::GetInstance().AddScene(new InGameScene("InGameScene"));
	SceneManager::GetInstance().SetActiveScene("InGameScene");
}