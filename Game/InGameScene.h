#pragma once
#include "Scene.h"
#include "BulletManager.h"

class Player;
class Map;
class TextObject;

class InGameScene : public Scene
{
public:
	InGameScene(const std::string& name);
	~InGameScene() = default;
	
	void Init() override;
	void Update() override;
private:
	Player* m_pPlayer;
	Map* m_pMap;
	TextObject* m_pScoreText;
	BulletManager m_BulletManager;
};