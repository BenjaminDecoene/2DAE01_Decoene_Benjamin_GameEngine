#pragma once
#include "Object.h"

class Entity final: public dae::Object
{
public:
	Entity();
	//	Base functions
	void Update() override;
	void Render(float interpolation) const override;
	//	Getters, setters
	void SetVelocity(b2Vec3 velocity) { m_Velocity = velocity; }
private:
	b2Vec3 m_Velocity;
};