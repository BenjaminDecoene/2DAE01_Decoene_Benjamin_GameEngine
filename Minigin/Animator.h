#pragma once

class SpriteComponent2D;

class Animator
{
public:
	Animator() = default;
	~Animator() = default;

	void Update();

	void SetDefaultSpriteComponent(SpriteComponent2D* spriteComponent);
	void AddSpriteComponent(const std::string& name, SpriteComponent2D* spriteComponent);

	void PlayOnce(const std::string& name);
	void PlayLoop(const std::string& name);
	void PlayDefault();
	bool GetIsDone() const;
private:
	std::vector<std::pair<std::string, SpriteComponent2D*>> m_Sprites;
	SpriteComponent2D* m_pCurrentSprite;
	SpriteComponent2D* m_pdefaultSprite;
};