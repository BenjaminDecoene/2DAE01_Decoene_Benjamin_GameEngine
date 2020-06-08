#pragma once
#include "FPSclock.h"

struct SDL_Window;
namespace dae
{
	class Scene;

	class Minigin
	{
	public:
		Minigin();
		void Init();
		void Cleanup();
		void Run();
	private:
		const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		FPSclock m_FPSclock;
	};
}