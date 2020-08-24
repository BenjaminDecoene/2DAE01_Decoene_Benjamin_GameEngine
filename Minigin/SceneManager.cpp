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

void SceneManager::DeleteScene(Scene* scene)
{
	for(std::vector<Scene*>::iterator it{m_Scenes.begin()}; it != m_Scenes.end();)
	{
		if((*it) == scene)
		{
			auto toDelete = (*it);
			it = m_Scenes.erase(it);
			delete toDelete;
			toDelete = nullptr;		
		}
		else
			++it;
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}

void SceneManager::AddScene(Scene* scene)
{
	//	Check if the scene already exists, if so overwrite the scene
	for(size_t i{}; i < m_Scenes.size(); i++)
	{
		if(scene->GetName() == m_Scenes[i]->GetName())
		{
			DeleteScene(m_Scenes[i]);
		}
	}
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
			m_Scenes[i]->Init();
			return;
		}
	}
	//	if the scene is not found trow an error
	throw std::runtime_error(std::string("to activate scene not found"));
}
