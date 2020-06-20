#pragma once
#include <fmod.hpp>
#include "Observer.h"
#include <functional>

struct Sound
{
	std::string name;
	FMOD::Sound* pSound;
	FMOD::Channel* pChannel;
	float volume = 1.f;
};

class AudioManager : public Observer, public Singleton<AudioManager>
{
public:
	void Init(const std::string& dataPath);
	void Update();
	void LoadSound(const std::string& name);
	void PlaySound(const std::string& name);
	void SetVolume(const std::string& name, int volume);

	void AddEvent(const std::string& name, std::function<void()> event);
	void Notify(const Object& object, const std::string& event) override;
private:
	std::vector<Sound> m_pSounds;
	FMOD::System* m_pSystem;
	std::string m_DataPath;
	std::vector<std::pair<std::string, std::function<void()>>> m_Events;

	friend class Singleton<AudioManager>;
	AudioManager() = default;
	~AudioManager();
};
