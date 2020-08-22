#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(const b2Vec2& pos);
	~Player() = default;

	
	//	Getters setters
	void SetVelocity(const b2Vec2& velocity) { m_Velocity.v = velocity; }
	const b2Vec2& GetVelocity() const { return m_Velocity.v; }
	b2Vec2 GetDigPoint() const;
private:
	void Update() override;
	void UpdateRotation();
	
	b2Velocity m_Velocity;
	float m_DigOffset;
};