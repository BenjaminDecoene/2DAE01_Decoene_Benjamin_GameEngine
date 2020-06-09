#pragma once
#include "Component.h"
#include <Box2D.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class ColliderComponent : public Component
{
public:
	ColliderComponent(dae::Object* parent, b2World* world, const glm::vec2& position, const glm::vec2& dimensions, b2BodyDef* body);
	void Update() override;
	void Render(float interpolation) const override;

	void AddFixture(b2FixtureDef* fixture);
private:
	b2Body* m_Body = nullptr;
	std::vector<b2Fixture*> m_Fixture;
	b2Vec2 m_Dimensions;
};

