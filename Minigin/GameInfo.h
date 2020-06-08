#pragma once
#include <SDL.h>
#include "Singleton.h"
#include <box2d.h>

class GameInfo : public dae::Singleton<GameInfo>
{
public:
	static int GetMsPerFrame() { return MsPerFrame; }
	static b2Vec2 GetWindowSize() { return m_WindowSize; }
private:
	friend class Singleton<GameInfo>;
	GameInfo() = default;
	
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	static const b2Vec2 m_WindowSize;
};