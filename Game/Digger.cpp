#include "pch.h"
#include "Digger.h"
#include "SceneManager.h"
#include "InGameScene.h"

Digger::Digger()
{
	SceneManager::GetInstance().AddScene(new InGameScene("InGameScene"));
	SceneManager::GetInstance().SetActiveScene("InGameScene");
}