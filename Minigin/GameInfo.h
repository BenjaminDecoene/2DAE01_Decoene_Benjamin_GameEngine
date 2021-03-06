#pragma once
#include <SDL.h>
#include "Singleton.h"
#include <box2d.h>

class GameInfo : public Singleton<GameInfo>
{
public:
	static int GetMsPerFrame() { return MsPerFrame; }
	static float GetElapsedSec() { return MsPerFrame / 1000.f; }
	static b2Vec2 GetWindowSize() { return m_WindowSize; }
	static float GetPPM() { return m_PPM; }
private:
	friend class Singleton<GameInfo>;
	GameInfo() = default;
	
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	static const b2Vec2 m_WindowSize;
	static const float m_PPM;
};