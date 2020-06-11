#pragma once

class Utils
{
public:
	static void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
	static void DrawClosedPolygon(SDL_Renderer* renderer, b2Vec2* points, int amount);
};

