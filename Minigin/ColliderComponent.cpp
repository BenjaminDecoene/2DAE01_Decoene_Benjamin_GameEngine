#include "pch.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "Object.h"

ColliderComponent::ColliderComponent(dae::Object* parent, b2World* world, const glm::vec2& position, const glm::vec2& dimensions, b2BodyDef* body)
	:Component(parent)
	,m_Dimensions(dimensions.x, dimensions.y)
{
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	body->position.Set(position.x / ppm, position.y / ppm);
	m_Body = world->CreateBody(body);
}

void ColliderComponent::Update()
{
	//	link the physics to the parent
	const auto pos{ m_Body->GetPosition() };
	const auto rot{ m_Body->GetAngle() };
	m_pParent->SetPosition(pos.x * GameInfo::GetInstance().GetPPM(), pos.y * GameInfo::GetInstance().GetPPM() + m_Dimensions.y);
	m_pParent->SetRotation(-float(rot * 180 / M_PI));
}

void ColliderComponent::Render(float interpolation) const
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

void ColliderComponent::AddFixture(b2FixtureDef* fixture)
{
	m_Fixture.push_back(m_Body->CreateFixture(fixture));
}