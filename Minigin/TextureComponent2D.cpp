#include "pch.h"
#include "TextureComponent2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Object.h"

TextureComponent2D::TextureComponent2D(Object* parent, const std::string& file, const b2Vec2& dimensions)
	:Component(parent)
	,m_pTexture(ResourceManager::GetInstance().LoadTexture(file))
	,m_Dimensions(dimensions)
{
}

void TextureComponent2D::Update()
{
}

void TextureComponent2D::Render(float) const
{
	const b2Vec2 parentPos{ m_pParent->GetTransform().GetPosition() };
	const float parentRot{ m_pParent->GetRotation() };

	Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x - m_Dimensions.x / 2, GameInfo::GetWindowSize().y - parentPos.y - m_Dimensions.y / 2, m_Dimensions.x, m_Dimensions.y, parentRot);
}