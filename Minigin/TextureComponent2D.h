#pragma once
#include "Component.h"
#include "Texture2D.h"

class TextureComponent2D final: public Component
{
public:
	TextureComponent2D(const std::string& file);
	
	void Update(dae::GameObject* parent) override;
	void Render(dae::GameObject* parent) const;
private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
};

