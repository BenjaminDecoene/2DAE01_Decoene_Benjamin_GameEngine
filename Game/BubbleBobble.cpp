#include "pch.h"
#include "BubbleBobble.h"
#include "SceneManager.h"
#include "TestScene.h"

BubbleBobble::BubbleBobble()
{
	dae::SceneManager::GetInstance().AddScene(new TestScene("TestScene"));
	dae::SceneManager::GetInstance().SetActiveScene("TestScene");
}
