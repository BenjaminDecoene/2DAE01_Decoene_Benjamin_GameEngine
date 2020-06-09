#pragma once
#include "Component.h"
#include "Texture2D.h"

class TextureComponent2D: public Component
{
public:
	explicit TextureComponent2D(dae::Object* parent, const std::string& file, const b2Vec2& dimensions);
	~TextureComponent2D() override = default;
	
	void Update() override;
	void Render(float interpolation) const override;
protected:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	b2Vec2 m_Dimensions;
};

