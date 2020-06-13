#include "pch.h"
#include "Player.h"
#include "SpriteComponent2D.h"
#include "PhysxComponent.h"
#include "InputManager.h"
#include "AudioManager.h"

Player::Player(const b2Vec2& pos)
{
	//	SetPos
	SetPosition(pos.x, pos.y);
	//	Add audiomanager as observer
	AddObserver(&AudioManager::GetInstance());
}

void Player::Init(SpriteComponent2D* sprite, PhysxComponent* physx, float moveSpeed)
{
	//	AddSprite
	AddComponent(sprite);
	//	AddPhysx
	AddComponent(physx);
	//	AddInput
		//	MoveRight
		InputManager::GetInstance().BindCommand(ControllerButton::KeyD, 
			std::make_unique<CommandFunction>(
				nullptr,
				[this, moveSpeed](){GetComponent<PhysxComponent>()->SetDesiredVelocity({moveSpeed,0});},
				[this](){SetVelocity({0, 0});}
			)
		);
	
		//	MoveLeft
		InputManager::GetInstance().BindCommand(ControllerButton::keyA, 
			std::make_unique<CommandFunction>(
				nullptr,
				[this, moveSpeed](){GetComponent<PhysxComponent>()->SetDesiredVelocity({-moveSpeed,0});},
				[this](){SetVelocity({0, 0});}
			)
		);
	
		//	Jump
		InputManager::GetInstance().BindCommand(ControllerButton::KeyW, 
			std::make_unique<CommandFunction>(
				nullptr,
				[this, moveSpeed]()
				{
					if(GetComponent<PhysxComponent>())
					this->GetComponent<PhysxComponent>()->SetDesiredVelocity({0, moveSpeed});
					Notify(*this, "PlayerUp");
				},
				[this](){SetVelocity({0, 0});}
			)
		);

		//	descent
		InputManager::GetInstance().BindCommand(ControllerButton::KeyS, 
			std::make_unique<CommandFunction>(
				nullptr,
				[this, moveSpeed](){GetComponent<PhysxComponent>()->SetDesiredVelocity({0,-moveSpeed});},
				[this](){SetVelocity({0, 0});}
			)
		);
}