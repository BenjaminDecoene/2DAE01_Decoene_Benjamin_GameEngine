#include "pch.h"
#include "FPSclock.h"
#include "Time.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "SceneManager.h"
#include "Scene.h"


FPSclock::FPSclock()
	:m_Transform{10.f, 10.f}
	,m_pTextObject()
	,m_FrameCount()
{
}

void FPSclock::Init()
{
	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pTextObject = new TextObject (std::to_string(m_FrameCount), fpsFont);
	m_pTextObject->SetPosition(m_Transform.x, m_Transform.y);

	SceneManager::GetInstance().GetScene().Add(m_pTextObject);
}

void FPSclock::Update()
{
	//	if a new second started reset framecount
	if(Time::GetInstance().GetIsNewSecond())
	{
		if(!m_HasUpdated)
			m_State = State::update;
	}
	else
		m_HasUpdated = false;

	switch(m_State)
	{
	case State::counting:
		//	each time update is called increase the framecount
		m_FrameCount++;
		break;
	case State::update:
		//	update the text
		const std::string fpsString{ std::to_string(m_FrameCount) };
		m_pTextObject->SetText(fpsString);
		//	reset the framecount
		m_FrameCount = 0;
		m_HasUpdated = true;
		m_State = State::counting;
		break;
	}
}
