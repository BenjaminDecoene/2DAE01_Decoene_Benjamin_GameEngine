#include "pch.h"
#include "InGameScene.h"
#include "InputManager.h"
#include "Commands.h"
#include "Player.h"
#include "Map.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameStats.h"
#include "ContactListener.h"
#include "SceneManager.h"
#include "StartScene.h"
#include <fstream>
#include <list>
#include "TextureComponent2D.h"

InGameScene::InGameScene(const std::string& name)
	:Scene(name)
	,m_pPlayer(nullptr)
	,m_pMap(nullptr)
	,m_pScoreText()
	,m_pContactListener(new ContactListener())
	,m_LevelManager()
	,m_GoldSackManager()
	,m_pBackground(new Object())
{
	m_LevelManager.AddLevel("../Data/Levels/Level1.txt");
	m_LevelManager.AddLevel("../Data/Levels/Level2.txt");
	m_LevelManager.AddLevel("../Data/Levels/Level3.txt");
}

InGameScene::~InGameScene()
{
	delete m_pContactListener;
	m_pContactListener = nullptr;
}

void InGameScene::Init()
{
	const auto windowSize = GameInfo::GetWindowSize();
	//	Background
	m_pBackground->SetPosition(windowSize.x / 2, windowSize.y / 2);
	m_pBackground->AddComponent(new TextureComponent2D(m_pBackground, "Background.png", windowSize));
	Add(m_pBackground);
	
	//	Add the contactlistener
	GetWorld()->SetContactListener(m_pContactListener);
	
	//	Player
	m_pPlayer = new Player({100.f, 100.f});
		//	Bind commands for the player
		InputManager::GetInstance().BindCommand(ControllerButton::keyA, std::make_unique<CommandMoveLeft>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::KeyD, std::make_unique<CommandMoveRight>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::KeyW, std::make_unique<CommandMoveUp>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::KeyS, std::make_unique<CommandMoveDown>(m_pPlayer));
		InputManager::GetInstance().BindCommand(ControllerButton::Key_Space, std::make_unique<CommandShoot>(m_pPlayer));
	
	//	Map
	m_pMap = new Map(m_pPlayer);
		//	Add the map
		Add(m_pMap);
		//	Add the player after the map so its drawn in front of the tiles
		Add(m_pPlayer);

	//	Score
	const auto scoreFont = ResourceManager::GetInstance().LoadFont("Font/OrangeJuice.ttf", 50);
	m_pScoreText = new TextObject (std::to_string(GameStats::GetInstance().GetScore()), scoreFont);
	m_pScoreText->SetPosition(20.f, 0.f);

	Add(m_pScoreText);

	//	BulletManager
	m_BulletManager.SetMap(m_pMap);
	m_pPlayer->SetBulletManager(&m_BulletManager);

	//	EnemyManager
	m_EnemyManager.SetMap(m_pMap);

	//	Init gold sack manager
	m_GoldSackManager.SetMap(m_pMap);
	
	//	Init levelManager
	m_LevelManager.Init(m_pMap, m_pPlayer, &m_EnemyManager, &m_GoldSackManager);

	//	Init hearths
	m_Hearths.resize(GameStats::GetInstance().GetLives());
	for(size_t i{}; i < m_Hearths.size(); i++)
	{
		m_Hearths[i] = new Object();
		m_Hearths[i]->AddComponent(new TextureComponent2D(m_Hearths[i], "Hearth.png", {40, 40}));
		m_Hearths[i]->SetPosition(180.f + 40.f * i, GameInfo::GetWindowSize().y - 20.f);
		Add(m_Hearths[i]);
	}

}

void InGameScene::Update()
{
	Scene::Update();

	UpdateHearths();
	m_pScoreText->SetText(std::to_string(GameStats::GetInstance().GetScore()));

	m_GoldSackManager.Update();
	m_LevelManager.Update();
	m_BulletManager.Update();
	m_EnemyManager.Update();
	UpdateGameOver();
}

void InGameScene::UpdateGameOver()
{
	if(GameStats::GetInstance().GetLives() <= 0 || m_LevelManager.GetIsDone())
	{
		UpdateHighscore();
		SceneManager::GetInstance().AddScene(new StartScene("StartScene"));
		SceneManager::GetInstance().SetActiveScene("StartScene");
		GameStats::GetInstance().GetLives() = 3;
		GameStats::GetInstance().GetScore() = 0;
	}
}

void InGameScene::UpdateHighscore()
{
	const UINT nrScores = 5;
	std::list<UINT> scores{};
	UINT idx = 0;
	const auto score = GameStats::GetInstance().GetScore();
	
	std::ifstream input{ "../Data/HighScores.txt" };
	//	check if the stream is succesfull
	if (input.is_open())
	{
		std::string line{};
		while (std::getline(input, line))
		{
			if(line.empty())
				continue;

			scores.push_back(std::stoi(line));
			idx++;
			
			if(idx >= nrScores)
				break;
		}
		input.close();
	}

	//	put your own score in the list and sort in decending order
	scores.push_back(score);
	scores.sort(std::greater<int>());
	//	pop the 6th element of the list
	if(idx >= 5)
		scores.pop_back();

	//	write the new highscores to the file
	std::ofstream output{ "../Data/HighScores.txt" };
	if(output.is_open())
	{
		for(std::list<UINT>::const_iterator it{scores.begin()}; it != scores.end(); ++it)
		{
			output << std::to_string(*it) << std::endl;
		}
	}
}

void InGameScene::UpdateHearths()
{
	if(GameStats::GetInstance().GetLives() < m_Hearths.size())
	{
		auto heart = m_Hearths.back();
		Remove(heart);
		m_Hearths.erase(m_Hearths.end() - 1);
	}
}
