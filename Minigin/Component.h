#pragma once

namespace dae {
	class Object;
}

class Component
{
public:
	explicit Component(dae::Object* parent) :m_pParent{parent}{};
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual void Render(float interpolation) const = 0;
protected:
	dae::Object* m_pParent;
};
