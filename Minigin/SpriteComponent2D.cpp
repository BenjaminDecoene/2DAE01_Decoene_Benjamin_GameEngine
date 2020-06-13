#include "pch.h"
#include "SpriteComponent2D.h"
#include "Object.h"
#include "Renderer.h"

SpriteComponent2D::SpriteComponent2D(Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows, UINT columns, float fps)
	:TextureComponent2D(parent, file, drawSize)
	,m_Rows(rows)
	,m_Columns(columns)
	,m_Fps(fps)
	,m_CurrentFrame()
	,m_StartFrame()
	,m_EndFrame(rows * columns)
	,m_ElapsedTime()
{
	int w;
	int h;
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &w, &h);

	m_TextureSize = {float(w), float(h)};
}

SpriteComponent2D::SpriteComponent2D(Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows,
	UINT columns, float fps, UINT startFrame, UINT endFrame)
	:SpriteComponent2D(parent, file, drawSize, rows, columns, fps)
{
	m_StartFrame = startFrame;
	m_EndFrame = endFrame;
}

void SpriteComponent2D::Update()
{
	m_ElapsedTime += GameInfo::GetInstance().GetMsPerFrame() / 1000.f;
	m_CurrentFrame = m_StartFrame + int(m_ElapsedTime * m_Fps) % (m_EndFrame - m_StartFrame);
}

void SpriteComponent2D::Render(float) const
{
	const b2Vec2 parentPos{ m_pParent->GetTransform().GetPosition() };
	const float parentRot{ m_pParent->GetRotation() };
	const float ppm = GameInfo::GetInstance().GetPPM();

	b2Vec2 tile;
	tile.x = m_TextureSize.x / m_Columns;
	tile.y = m_TextureSize.y / m_Rows;
	
	b2Vec2 offset;
	offset.x = (m_CurrentFrame % m_Columns) * tile.x;
	offset.y = (m_CurrentFrame / m_Columns) * tile.y;

	SDL_Rect src;
	src.x = int(offset.x);
	src.y = int(offset.y);
	src.w = int(tile.x);
	src.h = int(tile.y);
	
	Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x - m_Dimensions.x / 2, GameInfo::GetWindowSize().y - parentPos.y - m_Dimensions.y / 2, src, m_Dimensions.x, m_Dimensions.y, parentRot);
}