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

using namespace std;
using namespace std::chrono;

dae::Minigin::Minigin()
	:MsPerFrame(GameInfo::GetInstance().GetMsPerFrame())
{
	//	init minigin
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
}

void dae::Minigin::Init()
{
	m_FPSclock.Init();
}


/**
 * Code constructing the scene world starts here
 */
//void dae::Minigin::LoadGame()
//{
//	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<Object>();
	//go->AddComponent(new TextureComponent2D("background.jpg"));
	//scene.Add(go);

	//go = std::make_shared<Object>();
	//go->AddComponent(new TextureComponent2D("logo.png"));
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = new TextObject("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

	//// fps counter
	//auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//m_Fps = new TextObject (std::to_string(Time::GetInstance().GetFps()), fpsFont);
	//m_Fps->SetPosition(10, 10);
	//scene.Add(m_Fps);
//}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	//auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();
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

//void dae::Minigin::UpdateFpsCounter() const
//{
//	const std::string fpsString{std::to_string(Time::GetInstance().GetFps())};
//	const int nrDigits{0};
//
//	// Resize the text
//	m_Fps->SetText(fpsString.substr(0, fpsString.find(".") + nrDigits));
//}
