#include "pch.h"
#include "AudioManager.h"

void AudioManager::Init(const std::string& dataPath)
{	
	m_DataPath = dataPath;
	
	//FMOD::System *system = NULL;
	////	Create the main system object.
	//FMOD_RESULT result = System_Create(&system);
	//if (result != FMOD_OK)
	//{
	//    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	//    exit(-1);
	//}
	////	Initialize FMOD.
	//result = system->init(512, FMOD_INIT_NORMAL, 0);
	//if (result != FMOD_OK)
	//{
	//    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	//    exit(-1);
	//}

	//m_pSystem = system;
}

void AudioManager::Update()
{
	//m_pSystem->update();
}

void AudioManager::LoadSound(const std::string&)
{
	////	create the sound and push it in the vector
	//Sound sound{};
	////	name
	//sound.name = name;
	////	sound
	//const FMOD_RESULT result = m_pSystem->createSound((m_DataPath + name).c_str(), FMOD_DEFAULT, NULL, &sound.pSound);
	//m_pSounds.push_back(sound);
	//
	////	check for errors
	//if (result != FMOD_OK)
	//{
	//    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	//    exit(-1);
	//}
}

void AudioManager::PlaySound(const std::string&)
{
	//FMOD_RESULT result{};

	////	search for the right sound
	//for(auto& sound : m_pSounds)
	//{
	//	if(name == sound.name)
	//	{
	//		//	play sound
	//		result = m_pSystem->playSound(sound.pSound,0, false, &sound.pChannel);

	//		//	adjust volume
	//		sound.pChannel->setVolume(sound.volume);
	//		
	//		//	check for errors
	//		if (result != FMOD_OK)
	//		{
	//		    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	//		    exit(-1);
	//		}
	//		return;
	//	}
	//}
	
	std::cout << "Sound not found!" << std::endl;
}

void AudioManager::SetVolume(const std::string&, int)
{
		//	search for the right sound
	//for(auto& sound : m_pSounds)
	//{
	//	if(name == sound.name)
	//	{
	//		int channelIdx{};
	//		sound.pChannel->getIndex(&channelIdx);
	//		
	//		sound.volume = float(volume / 100.f);
	//	}
	//}
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
	//m_pSystem->release();
}
