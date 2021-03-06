#pragma once
#include <memory>
#include "Command.h"
#include "Singleton.h"

enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	KeyW,
	keyA,
	KeyS,
	KeyD,
	Key_Space
	//...
};

enum class ButtonState
{
	idle,
	onPressed,
	pressed,
	released
};

struct Button
{
	ButtonState State;
	std::unique_ptr<Command> pCommand;
};

class InputManager : public Singleton<InputManager>
{
public:
	bool ProcessInput();
	bool IsPressed(ControllerButton button) const;
	void BindCommand(ControllerButton button, std::unique_ptr<Command> command);
private:
	XINPUT_STATE m_CurrentState;
	std::vector<Button> m_pButtons;

	void HandleInput();
	void ExecuteButtonState() const;

	friend class Singleton<InputManager>;
	InputManager();
};