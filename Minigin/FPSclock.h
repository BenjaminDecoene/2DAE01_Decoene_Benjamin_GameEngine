#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class TextObject;
	
	class FPSclock
	{
		enum class State
		{
			counting,
			update
		};
	public:
		FPSclock();
		~FPSclock() = default;

		void Init();
		void Update();
	private:
		glm::vec2 m_Transform;
		TextObject* m_pTextObject;
		unsigned int m_FrameCount;
		State m_State = State::counting;
		bool m_HasUpdated = false;
	};
}