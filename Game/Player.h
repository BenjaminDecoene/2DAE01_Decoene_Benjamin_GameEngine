#pragma once
#include <Entity.h>

class PhysxComponent;
class SpriteComponent2D;

class Player : public Entity
{
public:
	Player(const b2Vec2& pos);
	void Init(SpriteComponent2D* sprite, PhysxComponent* physx, float moveSpeed);
private:
	
};
