#pragma once
#include "Object.h"

class Scene;
class BulletManager;

class Player : public Object
{
public:
	Player(const b2Vec2& pos);
	~Player() = default;

	void SetBulletManager(BulletManager* manager) { m_pBulletManager = manager; }
	void Shoot();
	void Kill();
	//	Getters setters
	void SetPosition(const b2Vec2& pos);
	void SetVelocity(const b2Vec2& velocity) { m_Velocity.v = velocity; }
	const b2Vec2& GetVelocity() const { return m_Velocity.v; }
	b2Vec2 GetDigPoint() const;
private:
	void Update() override;
	void UpdateRotation();

	BulletManager* m_pBulletManager;
	b2Velocity m_Velocity;
	float m_DigOffset;
	float m_ReloadTime;
	float m_ReloadTimeLeft;
};