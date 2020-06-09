#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update()
{
	m_Scenes[m_ActiveScene]->Update();
}

void dae::SceneManager::Render(float interpolation)
{
	m_Scenes[m_ActiveScene]->Render(interpolation);
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::AddScene(Scene* scene)
{
	m_Scenes.push_back(scene);
}

dae::Scene& dae::SceneManager::GetScene()
{
	return *m_Scenes[m_ActiveScene];
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
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

void dae::SceneManager::SetActiveScene(const std::string& name)
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
