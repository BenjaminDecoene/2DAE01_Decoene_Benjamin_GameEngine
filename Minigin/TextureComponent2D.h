#pragma once
#include "ObjectComponent.h"
#include "Texture2D.h"

class TextureComponent2D final: public ObjectComponent
{
public:
	TextureComponent2D(const std::string& file);
	
	void Update() override;
	void Render() const override;
private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	
};

