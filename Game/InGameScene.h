#pragma once
#include "Scene.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "LevelManager.h"

class Player;
class Map;
class TextObject;
class ContactListener;

class InGameScene : public Scene
{
public:
	InGameScene(const std::string& name);
	~InGameScene();
	
	void Init() override;
	void Update() override;
private:
	void UpdatePlayerDeath();
	void UpdateHighscore();
	
	Player* m_pPlayer;
	Map* m_pMap;
	TextObject* m_pScoreText;
	BulletManager m_BulletManager;
	EnemyManager m_EnemyManager;
	LevelManager m_LevelManager;
	ContactListener* m_pContactListener;
};