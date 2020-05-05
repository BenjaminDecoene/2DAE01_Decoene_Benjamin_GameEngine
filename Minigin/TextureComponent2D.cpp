#include "MiniginPCH.h"
#include "TextureComponent2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Time.h"

TextureComponent2D::TextureComponent2D(const std::string& file)
	: ObjectComponent("Texture2D")
	, m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(file))
{
}

void TextureComponent2D::Update()
{
	std::cout << Time::GetInstance().GetElapsedTime() << std::endl;
}

void TextureComponent2D::Render() const
{
	const glm::vec3 parentPos{ m_pParentTransform->GetPosition() };
	
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x, parentPos.y);
}
