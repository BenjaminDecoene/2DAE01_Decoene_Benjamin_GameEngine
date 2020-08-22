#pragma once
#include "Scene.h"

class Player;
class Map;
class TextObject;

class InGameScene : public Scene
{
public:
	InGameScene(const std::string& name);
	~InGameScene() = default;

	void Update() override;
private:
	Player* m_pPlayer;
	Map* m_pMap;
	TextObject* m_pScoreText;
};