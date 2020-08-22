#include "pch.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Time.h"
#include <iomanip>

#include "SceneManager.h"
#include "AudioManager.h"


using namespace std;
using namespace std::chrono;

dae::Minigin::Minigin()
	:MsPerFrame(GameInfo::GetInstance().GetMsPerFrame())
{
	//	init minigin
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		int(GameInfo::GetInstance().GetWindowSize().x),
		int(GameInfo::GetInstance().GetWindowSize().y),
		SDL_WINDOW_OPENGL
	);

	//	init mixer
	//if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2028) != 0)
	//{
	//	throw std::runtime_error(std::string("Mix_OpenAudio Error: ") + SDL_GetError());
	//}
	
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	//	tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	////	tell the audio manager where the audio is stored
	//AudioManager::GetInstance().Init("../Data/Sound/");
}

void dae::Minigin::Init()
{
	m_FPSclock.Init();
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	//Mix_Quit();
	SDL_Quit();
}

void dae::Minigin::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();
	//AudioManager::GetInstance().Update();
	time.SetMsPerFrame(MsPerFrame);
	
	bool doContinue = true;
	
	high_resolution_clock::time_point previous{ high_resolution_clock::now() };
	milliseconds lag{};
	
	//	Gameloop
	while (doContinue)
	{
		//	update frames, lag
		high_resolution_clock::time_point currentTime = high_resolution_clock::now();
		const milliseconds elapsed = duration_cast<milliseconds>(currentTime - previous);
		previous = currentTime;
		lag += elapsed;
	
		//	process input
		doContinue = input.ProcessInput();
	
		//	if frame takes to long, update till up to date before rendering
		while(lag.count() >= MsPerFrame)
		{
			//	update
			//	now we update at fixed intervals which is nice for consistancy 
			sceneManager.Update();
			time.Update();
			lag -= milliseconds(MsPerFrame);
		}
		
		//	render
		//	updating does require some time so frames will not be rendered at the time of updating.
		//	by giving an interpolation value(normalized)i can calculate where
		//	something should be drawn based on it current velocity.
		renderer.Render(float(lag.count() / MsPerFrame));
		//	update the FPSclock each time a frame gets rendered
		m_FPSclock.Update();
	}
	
	Cleanup();
}

