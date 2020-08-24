#pragma once
#include "Observer.h"

class GameStats : public Observer, public Singleton<GameStats>
{
public:
	UINT& GetScore() { return m_Score; }
	UINT& GetLives() { return m_Lives; }
	
	void Notify(const Object& object, const std::string& event) override;
private:
	friend class Singleton<GameStats>;
	GameStats() = default;
	
	UINT m_Score = 0;
	UINT m_Lives = 3;
	UINT m_EmStreak = 0;
};