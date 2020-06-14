#pragma once
#include "Object.h"

class Scene;

class Bullet : public Object
{
public:
	Bullet(const b2Vec2& pos, bool goRight, Scene* scene);
	void Update() override;
private:
	bool m_GoRight;
};
