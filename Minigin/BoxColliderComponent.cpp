#include "pch.h"
#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "Object.h"

BoxColliderComponent::BoxColliderComponent(dae::Object* parent, b2World* world, const glm::vec2& position, const glm::vec2& dimensions)
	:Component(parent)
	,m_Dimensions(dimensions.x, dimensions.y)
{
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / ppm, position.y / ppm);
	m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox((dimensions.x / ppm), (dimensions.y  / ppm));
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.3f;
	m_Fixture = m_Body->CreateFixture(&fixtureDef);
}

void BoxColliderComponent::Update()
{
	//	link the physics to the parent
	const auto pos{ m_Body->GetPosition() };
	const auto rot{ m_Body->GetAngle() };
	m_pParent->SetPosition(pos.x * GameInfo::GetInstance().GetPPM(), pos.y * GameInfo::GetInstance().GetPPM() + m_Dimensions.y);
	m_pParent->SetRotation(-float(rot * 180 / M_PI));
}

void BoxColliderComponent::Render(float interpolation) const
{
	UNREFERENCED_PARAMETER(interpolation);
	
	auto& renderer = dae::Renderer::GetInstance();
	const float ppm = GameInfo::GetInstance().GetPPM();
	
	SDL_Rect debugRect{int(m_Body->GetPosition().x * ppm),
		int(GameInfo::GetInstance().GetWindowSize().y - m_Dimensions.x - m_Body->GetPosition().y * ppm), int(m_Dimensions.x) * 2, int(m_Dimensions.y) * 2};
	
	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer.GetSDLRenderer(), &debugRect);
	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 0, 0, 255);
}