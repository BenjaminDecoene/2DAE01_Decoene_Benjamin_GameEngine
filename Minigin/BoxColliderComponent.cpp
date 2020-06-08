#include "pch.h"
#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "Object.h"

BoxColliderComponent::BoxColliderComponent(dae::Object* parent, b2World* world, const glm::vec2& position, const glm::vec2& dimensions)
	:Component(parent)
{
	//	make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_Fixture = m_Body->CreateFixture(&fixtureDef);
}

void BoxColliderComponent::Update()
{
	//	link the physics to the parent
	const auto pos{ m_Body->GetPosition() };
	m_pParent->SetPosition(pos.x, pos.y);
}

void BoxColliderComponent::Render() const
{
	auto& renderer = dae::Renderer::GetInstance();
	
	SDL_Rect debugRect{int(m_Body->GetPosition().x),
		int(GameInfo::GetInstance().GetWindowSize().y - m_Body->GetPosition().y), 10, 10};
	
	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer.GetSDLRenderer(), &debugRect);
	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 0, 0, 255);
}