#include "pch.h"
#include "Digger.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "InGameScene.h"

Digger::Digger()
{
	SceneManager::GetInstance().AddScene(new StartScene("StartScene"));
	SceneManager::GetInstance().AddScene(new InGameScene("InGameScene"));
	SceneManager::GetInstance().SetActiveScene("StartScene");
}
