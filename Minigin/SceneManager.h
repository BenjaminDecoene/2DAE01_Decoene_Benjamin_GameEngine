#pragma once
#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
	void AddScene(Scene* scene);
	//	returns active scene
	Scene& GetScene();
	Scene& GetScene(const std::string& name);
	void SetActiveScene(const std::string& name);

	void Update();
	void Render(float interpolation);
private:
	void DeleteScene(Scene* scene);
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<Scene*> m_Scenes;
	UINT m_ActiveScene = 0;
};