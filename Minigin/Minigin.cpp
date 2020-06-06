#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "ObjectComponents.h"
#include <iomanip>
#include "TextObject.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<GameObject>();
	//go->AddComponent(new TextureComponent2D("background.jpg"));
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//go->AddComponent(new TextureComponent2D("logo.png"));
	//go->SetPosition(216, 180);
	//scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = new TextObject("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	// fps counter
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_Fps = new TextObject (std::to_string(Time::GetInstance().GetFps()), fpsFont);
	m_Fps->SetPosition(10, 10);
	scene.Add(m_Fps);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		//auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			
			//doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
			time.Update(sleepTime.count());

			if(Time::GetInstance().GetIsNewSecond())
			{
				UpdateFpsCounter();
			}
		}
	}

	Cleanup();
}

void dae::Minigin::UpdateFpsCounter() const
{
	const std::string fpsString{std::to_string(Time::GetInstance().GetFps())};
	const int nrDigits{0};

	// Resize the text
	m_Fps->SetText(fpsString.substr(0, fpsString.find(".") + nrDigits));
}
