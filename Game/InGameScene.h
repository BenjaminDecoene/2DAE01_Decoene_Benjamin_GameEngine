#pragma once
#include "Scene.h"

class Player;
class Map;

class InGameScene : public Scene
{
public:
	InGameScene(const std::string& name);
	~InGameScene() = default;
private:
	Player* m_pPlayer;
	Map* m_pMap;
};