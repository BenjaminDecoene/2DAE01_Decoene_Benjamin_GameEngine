#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "TextureComponent2D.h"
#include "InputManager.h"
#include "Commands.h"
#include <fstream>
#include "ResourceManager.h"

StartScene::StartScene(const std::string& name)
	:Scene(name)
	,m_pBackground(new Object())
{
	//	Init highscore texts
	m_Highscores.resize(5, nullptr);
}

void StartScene::Init()
{
	const auto windowSize = GameInfo::GetWindowSize();
	//	Background
	m_pBackground->SetPosition(windowSize.x / 2, windowSize.y / 2);
	m_pBackground->AddComponent(new TextureComponent2D(m_pBackground, "StartScreenBackground.png", windowSize));
	Add(m_pBackground);

	//	Add command to start the game
	InputManager::GetInstance().BindCommand(ControllerButton::Key_Space, std::make_unique<CommandStart>());

	//	Highscores
	ReadHighscores();
	const auto highscoreFont = ResourceManager::GetInstance().LoadFont("Font/OrangeJuice.ttf", 50);
	for(size_t i{}; i < m_Highscores.size(); i ++)
	{
		if(i < m_HighscoresRead.size())
		{
			if(!m_Highscores[i])
			{
				m_Highscores[i] = new TextObject(m_HighscoresRead[i], highscoreFont);
				Add(m_Highscores[i]);
			}
			else
				m_Highscores[i]->SetText(m_HighscoresRead[i]);

			m_Highscores[i]->SetPosition(50.f, 300.f + i * 50.f);
		}
	}
}

void StartScene::ReadHighscores()
{
	m_HighscoresRead.clear();
	
	std::ifstream input{ "../Data/HighScores.txt" };
	//	check if the stream is succesfull
	if (input.is_open())
	{
		std::string line{};

		while (std::getline(input, line))
		{
			if(line.empty())
				continue;
			
			m_HighscoresRead.push_back(line);
		}
	}
}
