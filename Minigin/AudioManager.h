#pragma once
#include <fmod.hpp>
#include "Observer.h"
#include <functional>

class AudioManager : public Observer, public Singleton<AudioManager>
{
public:
	void Init(const std::string& dataPath);
	void Update();
	void LoadSound(const std::string& name);
	void PlaySound(const std::string& name);

	void AddEvent(const std::string& name, std::function<void()> event);
	void Notify(const Object& object, const std::string& event) override;
private:
	std::vector<std::pair<std::string, FMOD::Sound*>> m_pSounds;
	FMOD::System* m_pSystem;
	std::string m_DataPath;
	std::vector<std::pair<std::string, std::function<void()>>> m_Events;

	friend class Singleton<AudioManager>;
	AudioManager() = default;
	~AudioManager();
};
