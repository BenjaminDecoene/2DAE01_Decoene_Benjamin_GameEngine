#pragma once
#include <windows.h>
#include <Xinput.h>
#include <memory>
#include "Command.h"
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		//...
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		void ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void BindCommand(ControllerButton button, std::unique_ptr<Command> command);
	private:
		XINPUT_STATE m_CurrentState;
		std::unique_ptr<Command> m_pButtonX;
		std::unique_ptr<Command> m_pButtonY;
		std::unique_ptr<Command> m_pButtonA;
		std::unique_ptr<Command> m_pButtonB;

		void HandleInput() const;

		friend class Singleton<InputManager>;
	};
}
