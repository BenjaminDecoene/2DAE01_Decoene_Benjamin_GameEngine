#pragma once
#include <iostream>

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

// example

//class CommandFire : public Command
//{
//public:
//	void Execute() override
//	{
//		ServiceLocator::GetAudio().PlaySound("Fire");
//		std::cout << "Fire" << std::endl;
//	}
//};
