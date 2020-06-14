#pragma once
#include "TextureComponent2D.h"

class SpriteComponent2D final : public TextureComponent2D
{
public:
	SpriteComponent2D(Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows, UINT columns, float fps);
	SpriteComponent2D(Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows, UINT columns, float fps
	, UINT startFrame, UINT endFrame);
	~SpriteComponent2D() override = default;
	
	void Update() override;
	void Render(float interpolation) const override;

	void PlayOnce();
	void PlayLoop();
	void Interupt();
	bool GetIsDone() const { return m_IsDone; };
private:
	b2Vec2 m_TextureSize;
	UINT m_Rows;
	UINT m_Columns;
	float m_Fps;
	float m_ElapsedTime;
	UINT m_CurrentFrame;
	UINT m_StartFrame;
	UINT m_EndFrame;
	bool m_Active;
	bool m_Loop;
	bool m_IsDone;
};