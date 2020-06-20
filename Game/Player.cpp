#include "pch.h"
#include "Player.h"
#include "SpriteComponent2D.h"
#include "PhysxComponent.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "StateMachine.h"
#include "Command.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Bullet.h"

Player::Player(const b2Vec2& pos)
	:m_StateMachine(new StateMachine())
{
	//	SetPos
	SetPosition(pos.x, pos.y);
	//	Add audiomanager as observer
	AddObserver(&AudioManager::GetInstance());
}

void Player::Init(PhysxComponent* physx)
{	
	//	make sprite components
	const auto spriteLookRight = new SpriteComponent2D(this, "BBSprites/char_run.png", {70, 70}, 2, 8, 16, 0, 1);
	m_Animator.SetDefaultSpriteComponent(spriteLookRight);
	AddComponent(spriteLookRight);
	
	const auto spriteLookLeft = new SpriteComponent2D(this, "BBSprites/char_run.png", {70, 70}, 2, 8, 16, 8, 9);
	AddComponent(spriteLookLeft);
	
	const auto spriteMoveRight = new SpriteComponent2D(this, "BBSprites/char_run.png", {70, 70}, 2, 8, 16, 0, 8);
	AddComponent(spriteMoveRight);
	
	const auto spriteMoveLeft = new SpriteComponent2D(this, "BBSprites/char_run.png", {70, 70}, 2, 8, 16, 8, 16);
	AddComponent(spriteMoveLeft);

	const auto spriteShootRight= new SpriteComponent2D(this, "BBSprites/char_shoot.png", {70, 70}, 5, 8, 32, 0, 16);
	AddComponent(spriteShootRight);

	const auto spriteShootLeft = new SpriteComponent2D(this, "BBSprites/char_shoot.png", {70, 70}, 5, 8, 32, 16, 32);
	AddComponent(spriteShootLeft);

	m_Animator.AddSpriteComponent("LookRight", spriteLookRight);
	m_Animator.AddSpriteComponent("LookLeft", spriteLookLeft);
	m_Animator.AddSpriteComponent("MoveRight", spriteMoveRight);
	m_Animator.AddSpriteComponent("MoveLeft", spriteMoveLeft);
	m_Animator.AddSpriteComponent("ShootRight", spriteShootRight);
	m_Animator.AddSpriteComponent("ShootLeft", spriteShootLeft);
	
	//	AddPhysx
	AddComponent(physx);
	//	Set the rotation fixed so the character cant turn
	physx->SetFixedRotation(true);
	//	AddInput

	//	If not touching be able to jump
	InputManager::GetInstance().BindCommand(ControllerButton::KeyW,
		std::make_unique<CommandFunction>(
			nullptr,
			[physx]()
			{
				if(physx->IsTouching())
					physx->ApplyImpulse({0, 1.8f});
			},
			nullptr 
		)
	);

	m_StateMachine->AddState(new PlayerIdle(this));
	m_StateMachine->AddState(new PlayerMove(this));
	m_StateMachine->AddState(new PlayerShoot(this));
	m_StateMachine->SetStartState(m_StateMachine->GetState<PlayerIdle>());
}

void Player::Update()
{
	Object::Update();

	m_StateMachine->Update();
	m_Animator.Update();
}

//	statemachine
void PlayerMove::OnEntry()
{
	if(InputManager::GetInstance().IsPressed(ControllerButton::KeyD))
	{
		m_pPlayer->GetAnimator().PlayLoop("MoveRight");
		m_pPlayer->SetLookDirection(true);
	}
	if(InputManager::GetInstance().IsPressed(ControllerButton::keyA))
	{
		m_pPlayer->GetAnimator().PlayLoop("MoveLeft");
		m_pPlayer->SetLookDirection(false);
	}
}

void PlayerMove::Update(StateMachine* stateMachine)
{
	const auto physx = m_pPlayer->GetComponent<PhysxComponent>();

	if(InputManager::GetInstance().IsPressed(ControllerButton::Key_Space))
		stateMachine->TransitionTo(stateMachine->GetState<PlayerShoot>());
	
	if(m_pPlayer->GetLookDirection())
	{
		physx->SetDesiredVelocity({20,0});
		if(!InputManager::GetInstance().IsPressed(ControllerButton::KeyD))
			stateMachine->TransitionTo(stateMachine->GetState<PlayerIdle>());
	}
	else
	{
		physx->SetDesiredVelocity({-20,0});
		if(!InputManager::GetInstance().IsPressed(ControllerButton::keyA))
			stateMachine->TransitionTo(stateMachine->GetState<PlayerIdle>());		
	}
}

void PlayerIdle::OnEntry()
{
	if(m_pPlayer->GetLookDirection())
	{
		m_pPlayer->GetAnimator().PlayLoop("LookRight");
	}
	else
	{
		m_pPlayer->GetAnimator().PlayLoop("LookLeft");		
	}
}

void PlayerIdle::Update(StateMachine* stateMachine)
{
	if(InputManager::GetInstance().IsPressed(ControllerButton::Key_Space))
		stateMachine->TransitionTo(stateMachine->GetState<PlayerShoot>());
	
	if(	InputManager::GetInstance().IsPressed(ControllerButton::KeyD) ||
		InputManager::GetInstance().IsPressed(ControllerButton::keyA))
		stateMachine->TransitionTo(stateMachine->GetState<PlayerMove>());
}

void PlayerShoot::OnEntry()
{
	m_pPlayer->Notify(*m_pPlayer, "Shoot");
	
	if(m_pPlayer->GetLookDirection())
	{
		const auto playerPos = m_pPlayer->GetTransform().GetPosition();
		auto& currentScene = SceneManager::GetInstance().GetScene();
		
		m_pPlayer->GetAnimator().PlayOnce("ShootRight");
		currentScene.Add(new Bullet({playerPos.x, playerPos.y}, true, &currentScene));
	}
	else
	{
		const auto playerPos = m_pPlayer->GetTransform().GetPosition();
		auto& currentScene = SceneManager::GetInstance().GetScene();
		
		m_pPlayer->GetAnimator().PlayOnce("ShootLeft");
		currentScene.Add(new Bullet({playerPos.x, playerPos.y}, false, &currentScene));
	}
}

void PlayerShoot::Update(StateMachine* stateMachine)
{
	if(m_pPlayer->GetAnimator().GetIsDone())
		stateMachine->TransitionTo(stateMachine->GetState<PlayerIdle>());
}