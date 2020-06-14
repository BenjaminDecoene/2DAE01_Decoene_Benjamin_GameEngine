#include "pch.h"
#include "Command.h"
#include "Entity.h"

CommandMoveToRight::CommandMoveToRight(Entity* entity, float speed)
	:m_Entity(entity)
	,m_Speed(speed)
{
}

void CommandMoveToRight::Pressed()
{
	m_Entity->SetVelocity(b2Vec2(m_Speed, 0));
	std::cout << "move right" << std::endl;
}

CommandFunction::CommandFunction(std::function<void()> pressedFunction, std::function<void()> onPressedFunction, std::function<void()> onIdleFunction)
	:m_PressedFunction(pressedFunction)
	,m_OnIdleFunction(onIdleFunction)
	,m_OnPressedFunction(onPressedFunction)
{
}

void CommandFunction::Pressed()
{
	if(!m_PressedFunction)
		return;

	m_PressedFunction();
	std::cout << "ButtonPressed" << std::endl;
}

void CommandFunction::Released()
{
	if(!m_OnIdleFunction)
		return;

	m_OnIdleFunction();
	std::cout << "ButtonOnIdle" << std::endl;

}

void CommandFunction::OnPressed()
{
	if(!m_OnPressedFunction)
		return;
	
	m_OnPressedFunction();
	std::cout << "ButtonOnPressed" << std::endl;

}
