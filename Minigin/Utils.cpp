#include "pch.h"
#include "Utils.h"

//	i got this function from stackoverflow since sdl can't render a circle...
//	it is widely used and proven to be a good implimentation so i will just copy this one
//	url: https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void Utils::DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void Utils::DrawClosedPolygon(SDL_Renderer* renderer, b2Vec2* points, int amount)
{
	SDL_Point sdlPoints[9];

	//	Convert to sdlPoints
	for(int i{}; i < amount; i++)
	{
		sdlPoints[i].x = int(points[i].x);
		sdlPoints[i].y = int(points[i].y);
	}
	//	Add the first point to the end so the shape is closed
	sdlPoints[amount] = sdlPoints[0];
	
	SDL_RenderDrawLines(renderer, sdlPoints, amount + 1);
}