#include "pch.h"
#include "SpriteComponent2D.h"
#include "Object.h"
#include "Renderer.h"

SpriteComponent2D::SpriteComponent2D(dae::Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows, UINT columns, float fps)
	:TextureComponent2D(parent, file, drawSize)
	,m_Rows(rows)
	,m_Columns(columns)
	,m_Fps(fps)
	,m_CurrentFrame()
	,m_StartPos()
	,m_EndPos(rows * columns)
	,m_ElapsedTime()
{
	int w;
	int h;
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &w, &h);

	m_TextureSize = {float(w), float(h)};
}

SpriteComponent2D::SpriteComponent2D(dae::Object* parent, const std::string& file, const b2Vec2& drawSize, UINT rows,
	UINT columns, float fps, UINT startPos, UINT endPos)
	:SpriteComponent2D(parent, file, drawSize, rows, columns, fps)
{
	m_StartPos = startPos;
	m_EndPos = endPos;
}

void SpriteComponent2D::Update()
{
	m_ElapsedTime += GameInfo::GetInstance().GetMsPerFrame() / 1000.f;
	m_CurrentFrame = m_StartPos + int(m_ElapsedTime * m_Fps) % (m_EndPos - m_StartPos);
}

void SpriteComponent2D::Render(float interpolation) const
{
	UNREFERENCED_PARAMETER(interpolation);
	
	const b2Vec3 parentPos{ m_pParent->GetTransform().GetPosition() };
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
	
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, parentPos.x, GameInfo::GetWindowSize().y - parentPos.y, src, m_Dimensions.x, m_Dimensions.y, parentRot);
}