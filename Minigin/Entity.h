#pragma once
#include "Object.h"

class Entity : public Object
{
public:
	Entity();
	//	Base functions
	void Update() override;
	void Render(float interpolation) const override;
	//	Getters, setters
	void SetVelocity(b2Vec2 velocity) { m_Velocity = velocity; }
private:
	b2Vec2 m_Velocity;
};