#include "pch.h"
#include "TextureComponent2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Object.h"

TextureComponent2D::TextureComponent2D(dae::Object* parent, const std::string& file, const b2Vec2& dimensions)
	:Component(parent)
	,m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(file))
	,m_Dimensions(dimensions)
{
}

void TextureComponent2D::Update()
{
}

void TextureComponent2D::Render(float interpolation) const
{
	UNREFERENCED_PARAMETER(interpolation);
	
	const b2Vec2 parentPos{ m_pParent->GetTransform().GetPosition() };
	const float parentRot{ m_pParent->GetRotation() };
	const float ppm = GameInfo::GetInstance().GetPPM();
	
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x, GameInfo::GetWindowSize().y - parentPos.y, m_Dimensions.x, m_Dimensions.y, parentRot);
}