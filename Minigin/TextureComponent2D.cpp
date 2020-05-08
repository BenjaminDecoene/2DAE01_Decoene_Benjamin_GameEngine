#include "MiniginPCH.h"
#include "TextureComponent2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Time.h"
#include "GameObject.h"

TextureComponent2D::TextureComponent2D(const std::string& file)
	: m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(file))
{
}

void TextureComponent2D::Update(dae::GameObject* parent)
{
	Render(parent);
}

void TextureComponent2D::Render(dae::GameObject* parent) const
{
	const glm::vec3 parentPos{ parent->GetTransform().GetPosition() };
	
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x, parentPos.y);
}
