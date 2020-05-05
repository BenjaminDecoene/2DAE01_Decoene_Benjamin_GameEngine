#include "MiniginPCH.h"
#include "InputManager.h"
#include <iostream>

void dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	HandleInput();
	// todo: read the input
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	// todo: return whether the given button is pressed or not.
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

void dae::InputManager::BindCommand(ControllerButton button, std::unique_ptr<Command> command)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		m_pButtonA = std::move(command);
		break;
	case ControllerButton::ButtonB:
		m_pButtonB = std::move(command);
		break;
	case ControllerButton::ButtonX:
		m_pButtonX = std::move(command);
		break;
	case ControllerButton::ButtonY:
		m_pButtonY = std::move(command);		
		break;
	}
}

void dae::InputManager::HandleInput() const
{
	if(IsPressed(ControllerButton::ButtonA))
	{
		if(m_pButtonA)
			m_pButtonA->Execute();
	}
	if(IsPressed(ControllerButton::ButtonB))
	{
		if(m_pButtonB)
			m_pButtonB->Execute();
	}
	if(IsPressed(ControllerButton::ButtonX))
	{
		if(m_pButtonX)
			m_pButtonX->Execute();
	}
	if(IsPressed(ControllerButton::ButtonY))
	{
		if(m_pButtonY)
			m_pButtonY->Execute();
	}
}

