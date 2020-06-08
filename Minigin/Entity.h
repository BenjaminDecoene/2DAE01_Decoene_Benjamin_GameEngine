#pragma once
#include "Object.h"

class Entity final: public dae::Object
{
public:
	Entity();
	//	Base functions
	void Update() override;
	void Render() const override;
	//	Getters, setters
	void SetVelocity(glm::vec3 velocity) { m_Velocity = velocity; }
private:
	glm::vec3 m_Velocity;
};