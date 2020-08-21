#pragma once
#include "Scene.h"

class Player;

class InGameScene : public Scene
{
public:
	InGameScene(const std::string& name);
	void Update() override;
private:
	Player* m_pPlayer;
};