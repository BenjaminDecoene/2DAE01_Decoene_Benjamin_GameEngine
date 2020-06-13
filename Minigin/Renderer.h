#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void Render(float interpolation) const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float angle) const;
	void RenderTexture(const Texture2D& texture, float x, float y, const SDL_Rect& src, float width, float height, float angle) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
private:
	SDL_Renderer* m_Renderer{};
};


