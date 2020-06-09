#pragma once
#include "TextureComponent2D.h"

class SpriteComponent2D final : public TextureComponent2D
{
public:
	SpriteComponent2D(dae::Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows, UINT columns, float fps);
	SpriteComponent2D(dae::Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows, UINT columns, float fps
	, UINT startPos, UINT endPos);
	~SpriteComponent2D() override = default;
	
	void Update() override;
	void Render(float interpolation) const override;
private:
	b2Vec2 m_TextureSize;
	UINT m_Rows;
	UINT m_Columns;
	float m_Fps;
	float m_ElapsedTime;
	UINT m_CurrentFrame;
	UINT m_StartPos;
	UINT m_EndPos;
};

