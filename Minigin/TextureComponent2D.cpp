#include "pch.h"
#include "TextureComponent2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Object.h"

TextureComponent2D::TextureComponent2D(dae::Object* parent, const std::string& file)
	:Component(parent)
	,m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(file))
{
}

void TextureComponent2D::Update()
{
}

void TextureComponent2D::Render() const
{
	const glm::vec3 parentPos{ m_pParent->GetTransform().GetPosition() };
	
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x, parentPos.y);
}
