#pragma once
#include "..\..\Box2D\include\box2d\b2_world_callbacks.h"
class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
};

