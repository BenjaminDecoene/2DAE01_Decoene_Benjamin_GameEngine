#pragma once
#include "Transform.h"

namespace dae {
	class GameObject;
}

class Component
{
public:
	virtual ~Component() = 0;
	virtual void Update(dae::GameObject* parent) = 0;
};
