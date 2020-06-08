#pragma once
#include "Component.h"
#include "Texture2D.h"

class TextureComponent2D final: public Component
{
public:
	explicit TextureComponent2D(dae::Object* parent, const std::string& file);
	~TextureComponent2D() override = default;
	
	void Update() override;
	void Render() const override;
private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
};

