#include "pch.h"
#include "PhysxComponent.h"
#include "Renderer.h"
#include "Object.h"
#include "Utils.h"

PhysxComponent::PhysxComponent(Object* parent, b2World* world, b2BodyDef* body)
	:Component(parent)
{
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	const auto parentPos = parent->GetTransform().GetPosition();
	body->position.Set(parentPos.x / ppm, parentPos.y / ppm);
	m_Body = world->CreateBody(body);
}

void PhysxComponent::Update()
{
	//	link the physics to the parent
	const auto pos{ m_Body->GetPosition() };
	const auto rot{ m_Body->GetAngle() };
	m_pParent->SetPosition(pos.x * GameInfo::GetInstance().GetPPM(), pos.y * GameInfo::GetInstance().GetPPM());
	m_pParent->SetRotation(-float(rot * 180 / M_PI));
}

void PhysxComponent::Render(float) const
{

	//	Draw the fixtures
	
	auto& renderer = Renderer::GetInstance();
	const float ppm = GameInfo::GetInstance().GetPPM();
	b2CircleShape* circleShape{};
	b2PolygonShape* polygonShape{};
	b2Vec2 points[8];
	
	//	change to red draw color
	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 0, 0, 255);
	
	for(size_t i{}; i < m_Fixtures.size(); i++)
	{
		const auto fixtureShape = m_Fixtures[i]->GetShape();
		
		switch (fixtureShape->m_type)
		{
		case b2Shape::e_circle:
			circleShape = static_cast<b2CircleShape*>(fixtureShape);

			Utils::DrawCircle(renderer.GetSDLRenderer(),
				int32_t((circleShape->m_p.x + m_Body->GetPosition().x) * ppm),
				int32_t(GameInfo::GetWindowSize().y - (circleShape->m_p.y + m_Body->GetPosition().y) * ppm),
				int32_t(fixtureShape->m_radius * ppm));
			break;
		case b2Shape::e_polygon:
			polygonShape = static_cast<b2PolygonShape*>(fixtureShape);
			
			//	8 is the max vertices for box2d
			for(int j{}; j < 8; j++)
			{
				points[j].x = (polygonShape->m_vertices[j].x + m_Body->GetPosition().x) * ppm;
				points[j].y = GameInfo::GetWindowSize().y - (polygonShape->m_vertices[j].y + m_Body->GetPosition().y) * ppm;
			}
			
			Utils::DrawClosedPolygon(renderer.GetSDLRenderer(), points, polygonShape->m_count);
			break;
		default:
			break;
		}
	}
	
	//	change back to black draw color
	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 0, 0, 255);
}

void PhysxComponent::AddFixture(b2FixtureDef* fixture)
{
	m_Fixtures.push_back(m_Body->CreateFixture(fixture));
}

//	ref: https://gamedev.stackexchange.com/questions/47282/moving-player-in-box2d-without-forces
void PhysxComponent::SetDesiredVelocity(const b2Vec2& desiredVelocity) const
{
	const b2Vec2 currentVel = m_Body->GetLinearVelocity();
	
	const b2Vec2 velChange = desiredVelocity - currentVel;
	const b2Vec2 impulse = m_Body->GetMass() * (GameInfo::GetMsPerFrame() / 1000.f) * velChange;

	m_Body->ApplyLinearImpulse(impulse, m_Body->GetWorldCenter(),true);
}

void PhysxComponent::ApplyImpulse(const b2Vec2& force) const
{
	m_Body->ApplyLinearImpulseToCenter(force, true);
}

void PhysxComponent::SetFixedRotation(bool fixed) const
{
	m_Body->SetFixedRotation(fixed);
}

bool PhysxComponent::IsTouching() const
{
	for(b2ContactEdge* edge = m_Body->GetContactList(); edge; edge = edge->next)
	{
		if(edge->contact->IsTouching())
			return true;
	}
	return false;
}