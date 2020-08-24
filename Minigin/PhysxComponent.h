#pragma once
#include "Component.h"
#include <Box2D.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class PhysxComponent : public Component
{
public:
	PhysxComponent(Object* parent, b2World* world, b2BodyDef* body);
	~PhysxComponent();
	void Update() override;
	void Render(float interpolation) const override;
	
	void AddFixture(b2FixtureDef* fixture);

	void SetDesiredVelocity(const b2Vec2& desiredVelocity) const;
	void SetVelocity(const b2Vec2& velocity) const;
	void ApplyImpulse(const b2Vec2& force) const;
	void SetFixedRotation(bool fixed) const;
	bool IsTouching() const;
	void FixedToParent(bool fixed) { m_FixedToParent = fixed; }
	void SetPosition(const b2Vec2& pos);
private:
	b2Body* m_Body = nullptr;
	std::vector<b2Fixture*> m_Fixtures;
	bool m_FixedToParent;
};