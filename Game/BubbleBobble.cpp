#include "pch.h"
#include "BubbleBobble.h"
#include "SceneManager.h"
#include "TestScene.h"

BubbleBobble::BubbleBobble()
{
	SceneManager::GetInstance().AddScene(new TestScene("TestScene"));
	SceneManager::GetInstance().SetActiveScene("TestScene");
}
