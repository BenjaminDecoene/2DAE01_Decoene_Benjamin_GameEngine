#include "pch.h"
#include "InputManager.h"

void InputManager::ProcessInput()
{
	//	controller support
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
	
	HandleInput();
}

bool InputManager::IsPressed(ControllerButton button) const
{
	//	update the keys
	SDL_PumpEvents();

	//	state of the keys
	const UINT8* state{ SDL_GetKeyboardState(NULL)};

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
	case ControllerButton::KeyW:
		return state[SDL_SCANCODE_W];
	case ControllerButton::keyA:
		return state[SDL_SCANCODE_A];
	case ControllerButton::KeyS:
		return state[SDL_SCANCODE_S];
	case ControllerButton::KeyD:
		return state[SDL_SCANCODE_D];
	default: return false;
	}
}

void InputManager::BindCommand(ControllerButton button, std::unique_ptr<Command> command)
{
	m_pButtons[UINT(button)].pCommand = std::move(command);
}

void InputManager::HandleInput()
{
	for(size_t i{}; i < m_pButtons.size(); i++)
	{
		const bool buttonPressed{ IsPressed(static_cast<ControllerButton>(i)) };

		switch(m_pButtons[i].State)
		{
		case ButtonState::idle:
			if(buttonPressed)
				m_pButtons[i].State = ButtonState::onPressed;
			break;
		case ButtonState::onPressed:
			m_pButtons[i].State = ButtonState::pressed;
			break;
		case ButtonState::pressed:
			if(!buttonPressed)
				m_pButtons[i].State = ButtonState::released;
			break;
		case ButtonState::released:
			m_pButtons[i].State = ButtonState::idle;
			break;
		}
	}

	ExecuteButtonState();
}

void InputManager::ExecuteButtonState() const
{
	for(size_t i{}; i < m_pButtons.size(); i++)
	{
		if(!m_pButtons[i].pCommand)
			continue;
		
		switch(m_pButtons[i].State)
		{
		case ButtonState::released:
			m_pButtons[i].pCommand->Released();
			break;
		case ButtonState::pressed:
			m_pButtons[i].pCommand->Pressed();
			break;
		case ButtonState::onPressed:
			m_pButtons[i].pCommand->OnPressed();
			break;
		case ButtonState::idle:
			break;
		}
	}
}

InputManager::InputManager()
{
	m_pButtons.resize(8);
}

