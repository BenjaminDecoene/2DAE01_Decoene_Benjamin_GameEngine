#pragma once
#include "Component.h"
#include <Box2D.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class BoxColliderComponent : public Component
{
public:
	BoxColliderComponent(dae::Object* parent, b2World* world, const glm::vec2& position, const glm::vec2& dimensions);
	void Update() override;
	void Render(float interpolation) const override;
private:
	b2Body* m_Body = nullptr;
	b2Fixture* m_Fixture = nullptr;
	b2Vec2 m_Dimensions;
};

