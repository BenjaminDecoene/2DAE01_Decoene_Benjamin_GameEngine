#pragma once
#include <iostream>
#include <functional>

class Entity;

class Command
{
public:
	virtual ~Command() = default;
	virtual void Pressed() = 0;
	virtual void Released() = 0;
	virtual void OnPressed() = 0;
};

// example

class CommandFire : public Command
{
public:
	void Pressed() override
	{
		//ServiceLocator::GetAudio().PlaySound("Fire");
		std::cout << "Fire" << std::endl;
	}
	void Released() override {};
	void OnPressed() override {};
};

class CommandMoveToRight : public Command
{
public:
	CommandMoveToRight(Entity* entity, float speed);
	
	void Pressed() override;
	void Released() override {};
	void OnPressed() override {};
private:
	Entity* m_Entity;
	float m_Speed;
};

class CommandFunction : public Command
{
public:
	CommandFunction(std::function<void()> pressedFunction, std::function<void()> onPressedFunction, std::function<void()> onIdleFunction);
	
	void Pressed() override;
	void Released() override;
	void OnPressed() override;
private:
	std::function<void()> m_pressedFunction;
	std::function<void()> m_onIdleFunction;
	std::function<void()> m_onPressedFunction;
};