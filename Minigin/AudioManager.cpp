#include "pch.h"
#include "AudioManager.h"
#include <fmod_errors.h>

void AudioManager::Init(const std::string& dataPath)
{	
	m_DataPath = dataPath;
	
	FMOD::System *system = NULL;
	//	Create the main system object.
	FMOD_RESULT result = System_Create(&system);
	if (result != FMOD_OK)
	{
	    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	}
	//	Initialize FMOD.
	result = system->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
	    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	}

	m_pSystem = system;
}

void AudioManager::Update()
{
	m_pSystem->update();
}

void AudioManager::LoadSound(const std::string& name)
{
	//	create the sound and push it in the vector
	FMOD::Sound* sound;
	const FMOD_RESULT result = m_pSystem->createSound((m_DataPath + name).c_str(), FMOD_DEFAULT, NULL, &sound);
	m_pSounds.push_back(std::make_pair(name, sound));
	
	//	check for errors
	if (result != FMOD_OK)
	{
	    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	}
}

void AudioManager::PlaySound(const std::string& name)
{
	FMOD_RESULT result{};

	//	search for the right sound
	for(auto& sound : m_pSounds)
	{
		if(name == sound.first)
		{
			//	play sound
			result = m_pSystem->playSound(sound.second,0, false, 0);
			
			//	check for errors
			if (result != FMOD_OK)
			{
			    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			    exit(-1);
			}
			return;
		}
	}
	
	std::cout << "Sound not found!" << std::endl;
}

void AudioManager::AddEvent(const std::string& name, std::function<void()> event)
{
	m_Events.push_back(std::make_pair(name, event));
}

void AudioManager::Notify(const Object&, const std::string& event)
{
	for(auto& i : m_Events)
	{
		if(i.first == event)
		{
			i.second();
			return;
		}
	}
}

AudioManager::~AudioManager()
{
	m_pSystem->release();
}
