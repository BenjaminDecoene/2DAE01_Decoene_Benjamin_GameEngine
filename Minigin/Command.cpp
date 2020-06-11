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
	:m_pressedFunction(pressedFunction)
	,m_onIdleFunction(onIdleFunction)
	,m_onPressedFunction(onPressedFunction)
{
}

void CommandFunction::Pressed()
{
	if(!m_onPressedFunction)
		return;

	m_onPressedFunction();
	std::cout << "ButtonPressed" << std::endl;
}

void CommandFunction::Released()
{
	if(!m_onIdleFunction)
		return;

	m_onIdleFunction();
	std::cout << "ButtonOnIdle" << std::endl;

}

void CommandFunction::OnPressed()
{
	if(!m_onPressedFunction)
		return;
	
	m_onPressedFunction();
	std::cout << "ButtonOnPressed" << std::endl;

}
