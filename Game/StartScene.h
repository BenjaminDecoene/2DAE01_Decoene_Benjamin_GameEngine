#pragma once
#include <Scene.h>
#include "TextObject.h"

class Object;

class StartScene : public Scene
{
public:
	StartScene(const std::string& name);

	void Init() override;
private:
	void ReadHighscores();
	
	Object* m_pBackground;
	std::vector<TextObject*> m_Highscores;
	std::vector<std::string> m_HighscoresRead;
};