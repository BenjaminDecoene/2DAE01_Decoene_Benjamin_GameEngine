#pragma once

class Object;

class Component
{
public:
	explicit Component(Object* parent) :m_pParent{parent}{};
	virtual ~Component() = default;
	virtual void Update() = 0;
	virtual void Render(float interpolation) const = 0;
protected:
	Object* m_pParent;
};
