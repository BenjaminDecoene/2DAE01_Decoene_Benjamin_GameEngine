#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"


void SceneManager::Update()
{
	m_Scenes[m_ActiveScene]->Update();
}

void SceneManager::Render(float interpolation)
{
	m_Scenes[m_ActiveScene]->Render(interpolation);
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}

void SceneManager::AddScene(Scene* scene)
{
	m_Scenes.push_back(scene);
}

Scene& SceneManager::GetScene()
{
	return *m_Scenes[m_ActiveScene];
}

Scene& SceneManager::GetScene(const std::string& name)
{
	for(size_t i{}; i < m_Scenes.size(); i++)
	{
		if(m_Scenes[i]->GetName() == name)
		{
			return *m_Scenes[i];
		}
	}
	return CreateScene(name);
}

void SceneManager::SetActiveScene(const std::string& name)
{
	for(size_t i{}; i < m_Scenes.size(); i++)
	{
		if(m_Scenes[i]->GetName() == name)
		{
			m_ActiveScene = UINT(i);
			return;
		}
	}
	//	if the scene is not found trow an error
	throw std::runtime_error(std::string("to activate scene not found"));
}
